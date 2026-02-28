# -*- coding: utf-8 -*-
"""残高推移グラフ生成スクリプト（170万入金シミュレーション・ゼロ到達予測付き）"""

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
REGRESSION_DAYS = 365 * 3  # 回帰分析に使う直近日数
MIN_DATA_POINTS = 30    # 回帰に必要な最小データ数
FORECAST_DAYS = 1200    # 予測期間（日）
DEPOSIT_AMOUNT = 1700000  # シミュレーション用入金額
FIGURE_SIZE = (12, 5)
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

def create_simulated_balance(daily_bal: pd.DataFrame, deposit: float) -> pd.DataFrame:
    """最終日翌日に入金を加えたシミュレーション用データを作成"""
    last_date = daily_bal["Date"].max()
    last_balance = daily_bal[daily_bal["Date"] == last_date]["Balance"].iloc[0]
    
    # 最終日翌日のデータを追加
    deposit_date = last_date + pd.Timedelta(days=1)
    new_balance = last_balance + deposit
    
    new_row = pd.DataFrame({
        "Date": [deposit_date],
        "Balance": [new_balance]
    })
    
    simulated = pd.concat([daily_bal, new_row], ignore_index=True)
    return simulated

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

def estimate_zero_date_from_simulation(simulated_bal: pd.DataFrame, slope: float) -> dict:
    """シミュレーション後のデータからゼロ到達日を推定"""
    if slope >= 0:
        return {"zero_date": None, "slope": slope}
    
    # 入金後の残高を取得
    sim_start = simulated_bal.iloc[-1]  # 最後の行（入金後）
    balance_after_deposit = sim_start["Balance"]
    
    # ゼロに到達するまでの日数を計算（入金後の残高から傾きで減少）
    days_to_zero = -balance_after_deposit / slope
    zero_date = (sim_start["Date"] + pd.Timedelta(days=float(days_to_zero))).date()
    
    return {"zero_date": zero_date, "slope": slope, "balance_after_deposit": balance_after_deposit}

def generate_forecast_from_simulation(simulated_bal: pd.DataFrame, slope: float) -> tuple:
    """シミュレーション後の将来予測直線を生成"""
    sim_start = simulated_bal.iloc[-1]
    balance_start = sim_start["Balance"]
    t_last = sim_start["Date"]
    
    future_idx = pd.date_range(
        t_last + pd.Timedelta(days=1),
        t_last + pd.Timedelta(days=FORECAST_DAYS),
        freq="D"
    )
    
    # 入金後のポイントからの経過日数
    days_from_start = (future_idx - t_last).days.values.astype(float)
    y_future = balance_start + slope * days_from_start
    
    return future_idx, y_future

# ========= グラフ描画 =========
def plot_balance_chart(daily_bal: pd.DataFrame, simulated_bal: pd.DataFrame,
                       future_idx: pd.Index, y_future: np.ndarray, zero_date, slope: float) -> tuple:
    """残高推移グラフを描画（実績とシミュレーション）"""
    def yen_fmt(v, pos):
        return f"¥{int(v):,}"
    
    fig, ax = plt.subplots(figsize=FIGURE_SIZE)
    
    # 実績残高
    ax.plot(daily_bal["Date"], daily_bal["Balance"], 
            color="#1f77b4", lw=2.0, label="残高（実績）")
    
    # シミュレーション後のデータ（入金部分）
    sim_date = simulated_bal["Date"].iloc[-1]
    sim_balance = simulated_bal["Balance"].iloc[-1]
    ax.plot([sim_date], [sim_balance],
            color="#2ca02c", marker="o", markersize=8, linestyle="none", label="170万入金")
    
    # 予測直線（入金後の点から接続）
    if slope < 0 and len(future_idx) > 0:
        # 入金後の点と予測直線を接続
        forecast_dates = pd.concat([pd.Series([sim_date]), pd.Series(future_idx)])
        forecast_values = np.concatenate([[sim_balance], y_future])
        ax.plot(forecast_dates, forecast_values, color="red", ls="--", 
                lw=2.0, label="トレンド予測")
    
    # ゼロ到達日の垂直線
    if zero_date is not None:
        ax.axvline(pd.to_datetime(zero_date), color="red", ls="--", lw=2.0,
                   label=f"ゼロ到達予測: {zero_date}")
    
    # 基準線
    ax.axhline(0, color="black", lw=1.0)
    
    # グラフの装飾
    ax.set_title("口座残高の推移（170万入金シミュレーション）", fontsize=TITLE_FONTSIZE, fontfamily=JP_FONT)
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
    
    # 回帰分析（元のデータのみを使用して傾きを算出）
    recent, slope, intercept = perform_linear_regression(daily_bal)
    
    # シミュレーション用データ作成（最終日翌日に170万入金）
    simulated_bal = create_simulated_balance(daily_bal, DEPOSIT_AMOUNT)
    
    # ゼロ到達日推定（入金後の残高から元の傾きで予測）
    result = estimate_zero_date_from_simulation(simulated_bal, slope)
    zero_date = result["zero_date"]
    
    # 予測直線生成（入金後の残高から元の傾きで予測）
    future_idx, y_future = generate_forecast_from_simulation(simulated_bal, slope)
    
    # グラフ描画
    fig, ax = plot_balance_chart(daily_bal, simulated_bal, future_idx, y_future, zero_date, slope)
    
    # 保存
    out_path = BASE_DIR / "chart_balance_reg3years_170.pdf"
    fig.savefig(out_path, format='pdf')
    print(f"saved: {out_path}")
    print(f"Deposit: ¥{DEPOSIT_AMOUNT:,}")
    print(f"Slope: {slope:.4f} yen/day")
    if zero_date:
        print(f"Estimated zero date: {zero_date}")

if __name__ == "__main__":
    main()
