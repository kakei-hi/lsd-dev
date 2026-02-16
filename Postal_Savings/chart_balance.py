# -*- coding: utf-8 -*-
"""残高推移グラフ生成スクリプト（日本語フォント対応・ゼロ到達予測付き）"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter
from matplotlib import font_manager as fm
from pathlib import Path

# ========= 定数定義 =========
JP_FONT_CANDIDATES = [
    "Hiragino Sans", "Hiragino Kaku Gothic ProN", "Hiragino Kaku Gothic Pro",
    "Yu Gospel", "YuGothic",
    "IPAexGothic", "IPAGothic", "Noto Sans CJK JP", "Source Han Sans JP"
]
REGRESSION_DAYS = 365  # 回帰分析に使う直近日数
MIN_DATA_POINTS = 30    # 回帰に必要な最小データ数
FORECAST_DAYS = 180     # 予測期間（日）
FIGURE_SIZE = (10, 4.2)
TITLE_FONTSIZE = 14
LABEL_FONTSIZE = 12
BASE_DIR = Path("/Users/hidekazukakei/Library/Mobile Documents/com~apple~CloudDocs/上柚木/義母ゆうちょ")

# ========= 日本語フォントの自動選択 =========
def resolve_jp_font() -> str:
    """システムフォントから日本語フォントを自動選択"""
    fonts = fm.findSystemFonts(fontext="ttf") + fm.findSystemFonts(fontext="otf")
    for p in fonts:
        try:
            name = fm.get_font(p).family_name
            if any(cand.lower() in name.lower() for cand in JP_FONT_CANDIDATES):
                return name
        except Exception:
            continue
    return "IPAexGothic"

# フォント・グラフスタイル設定
plt.style.use("seaborn-v0_8")
JP_FONT = resolve_jp_font()
print(f"Using Japanese font: {JP_FONT}")
plt.rcParams["font.sans-serif"] = [JP_FONT] + plt.rcParams["font.sans-serif"]
plt.rcParams["font.family"] = "sans-serif"
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["pdf.fonttype"] = 42

# ========= データ処理 =========
def load_and_prepare_data(csv_path: Path) -> pd.DataFrame:
    """CSVファイルを読込んでデータを前処理"""
    df = pd.read_csv(csv_path, parse_dates=["Date"])
    for col in ["Deposit", "Withdrawal", "Balance"]:
        df[col] = pd.to_numeric(df[col], errors="coerce")
    return df.sort_values("Date").reset_index(drop=True)

def create_daily_balance(df: pd.DataFrame) -> pd.DataFrame:
    """不規則なデータを日次ベースに補間"""
    bal_df = (
        df[["Date", "Balance"]]
        .dropna()
        .drop_duplicates(subset=["Date"], keep="last")
        .set_index("Date")
        .sort_index()
    )
    idx = pd.date_range(bal_df.index.min(), bal_df.index.max(), freq="D")
    daily = bal_df.reindex(idx).ffill().reset_index()
    daily.columns = ["Date", "Balance"]
    return daily

# ========= 線形回帰と予測 =========
def perform_linear_regression(daily_bal: pd.DataFrame) -> tuple:
    """直近の期間で線形回帰を実施し、傾きと切片を返す"""
    max_date = daily_bal["Date"].max()
    recent = daily_bal[daily_bal["Date"] >= (max_date - pd.Timedelta(days=REGRESSION_DAYS))]
    
    if len(recent) < MIN_DATA_POINTS:
        recent = daily_bal.copy()
    
    x = (recent["Date"] - recent["Date"].min()).dt.days.values.astype(float)
    y = recent["Balance"].values.astype(float)
    
    A = np.vstack([x, np.ones_like(x)]).T
    slope, intercept = np.linalg.lstsq(A, y, rcond=None)[0]
    
    return recent, slope, intercept

def estimate_zero_date(recent: pd.DataFrame, slope: float, intercept: float) -> dict:
    """ゼロ到達日を推定"""
    if slope >= 0:
        return {"zero_date": None, "slope": slope, "intercept": intercept}
    
    x_zero = -intercept / slope
    zero_date = (recent["Date"].min() + pd.Timedelta(days=float(x_zero))).date()
    return {"zero_date": zero_date, "slope": slope, "intercept": intercept}

def generate_forecast(daily_bal: pd.DataFrame, recent: pd.DataFrame, 
                     slope: float, intercept: float) -> tuple:
    """将来の予測直線を生成"""
    t0 = recent["Date"].min()
    t_last = daily_bal["Date"].max()
    future_idx = pd.date_range(
        t_last + pd.Timedelta(days=1),
        t_last + pd.Timedelta(days=FORECAST_DAYS),
        freq="D"
    )
    t_future = (future_idx - t0).days.values.astype(float)
    y_future = slope * t_future + intercept
    return future_idx, y_future

# ========= グラフ描画 =========
def plot_balance_chart(daily_bal: pd.DataFrame, future_idx: pd.Index, 
                       y_future: np.ndarray, zero_date, slope: float) -> tuple:
    """残高推移グラフを描画"""
    def yen_fmt(v, pos):
        return f"¥{int(v):,}"
    
    fig, ax = plt.subplots(figsize=FIGURE_SIZE)
    
    # 実績残高
    ax.plot(daily_bal["Date"], daily_bal["Balance"], 
            color="#1f77b4", lw=2.0, label="残高（実績）")
    
    # 予測直線
    if slope < 0:
        ax.plot(future_idx, y_future, color="red", ls="--", 
                lw=2.0, label="トレンド予測")
    
    # ゼロ到達日の垂直線
    if zero_date is not None:
        ax.axvline(pd.to_datetime(zero_date), color="red", ls="--", lw=2.0,
                   label=f"ゼロ到達予測: {zero_date}")
    
    # 基準線
    ax.axhline(0, color="black", lw=1.0)
    
    # グラフの装飾
    ax.set_title("口座残高の推移（実績）", fontsize=TITLE_FONTSIZE, fontfamily=JP_FONT)
    ax.set_xlabel("日付", fontsize=LABEL_FONTSIZE, fontfamily=JP_FONT)
    ax.set_ylabel("残高（円）", fontsize=LABEL_FONTSIZE, fontfamily=JP_FONT)
    ax.yaxis.set_major_formatter(FuncFormatter(yen_fmt))
    ax.legend(loc="upper left", frameon=True, prop={"family": JP_FONT})
    fig.tight_layout()
    
    return fig, ax

# ========= メイン処理 =========
def main():
    """メイン処理"""
    # データ読込と前処理
    df = load_and_prepare_data(BASE_DIR / "raw_data.csv")
    daily_bal = create_daily_balance(df)
    
    # 回帰分析
    recent, slope, intercept = perform_linear_regression(daily_bal)
    
    # ゼロ到達日推定
    result = estimate_zero_date(recent, slope, intercept)
    zero_date, slope, intercept = result["zero_date"], result["slope"], result["intercept"]
    
    # 予測直線生成
    future_idx, y_future = generate_forecast(daily_bal, recent, slope, intercept)
    
    # グラフ描画
    fig, ax = plot_balance_chart(daily_bal, future_idx, y_future, zero_date, slope)
    
    # 保存
    out_path = BASE_DIR / "chart_balance.pdf"
    fig.savefig(out_path, format='pdf')
    print(f"saved: {out_path}")

if __name__ == "__main__":
    main()
