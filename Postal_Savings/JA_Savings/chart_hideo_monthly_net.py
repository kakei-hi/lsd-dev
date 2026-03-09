# -*- coding: utf-8 -*-
"""秀夫統合口座月次の純増減グラフ生成スクリプト（日本語フォント対応）"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter
from matplotlib import font_manager as fm
from pathlib import Path

# ========= 定数定義 =========
JP_FONT_CANDIDATES = [
    "Hiragino Sans", "Hiragino Kaku Gothic ProN", "Hiragino Kaku Gothic Pro",
    "Yu Gothic", "YuGothic",
    "IPAexGothic", "IPAGothic", "Noto Sans CJK JP", "Source Han Sans JP"
]
RECENT_MONTHS = 12       # 表示する直近月数
FIGURE_SIZE = (12, 5)
TITLE_FONTSIZE = 14
LABEL_FONTSIZE = 12
BAR_WIDTH = 0.6
COLOR_POSITIVE = "#2ca02c"
COLOR_NEGATIVE = "#d62728"
SCRIPT_DIR = Path(__file__).parent
OUTPUT_DIR = Path("/Users/hidekazukakei/Library/Mobile Documents/com~apple~CloudDocs/上柚木/秀夫JA_ゆうちょ")
ANCHOR_DATE = pd.Timestamp("2023-07-31")  # この日のBalanceのみ基準値として使用

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
plt.style.use("seaborn-v0_8-darkgrid")
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
    df[["Deposit", "Withdrawal"]] = df[["Deposit", "Withdrawal"]].fillna(0.0)
    return df.sort_values("Date").reset_index(drop=True)

def create_daily_balance(df: pd.DataFrame) -> pd.DataFrame:
    """2023-07-31のBalanceを基準に、入出金から日次残高を再構築"""
    df = df.copy()
    df["Date"] = pd.to_datetime(df["Date"]).dt.normalize()

    anchor_rows = df[(df["Date"] == ANCHOR_DATE) & (df["Balance"].notna())]
    if anchor_rows.empty:
        raise ValueError(f"Anchor Balance not found for {ANCHOR_DATE.date()}")
    anchor_balance = float(anchor_rows.iloc[-1]["Balance"])

    txn_daily = (
        df.groupby("Date", as_index=False)[["Deposit", "Withdrawal"]]
        .sum(min_count=1)
        .fillna(0.0)
        .sort_values("Date")
    )
    txn_daily["NetCashflow"] = txn_daily["Deposit"] - txn_daily["Withdrawal"]

    start_date = min(txn_daily["Date"].min(), ANCHOR_DATE)
    end_date = max(txn_daily["Date"].max(), ANCHOR_DATE)
    idx = pd.date_range(start_date, end_date, freq="D")

    daily = pd.DataFrame({"Date": idx})
    daily = daily.merge(txn_daily[["Date", "NetCashflow"]], on="Date", how="left")
    daily["NetCashflow"] = daily["NetCashflow"].fillna(0.0)
    daily["Balance"] = np.nan

    anchor_idx = daily.index[daily["Date"] == ANCHOR_DATE]
    if len(anchor_idx) != 1:
        raise ValueError(f"Anchor date index error: {ANCHOR_DATE.date()}")
    anchor_idx = int(anchor_idx[0])
    daily.at[anchor_idx, "Balance"] = anchor_balance

    for i in range(anchor_idx + 1, len(daily)):
        daily.at[i, "Balance"] = daily.at[i - 1, "Balance"] + daily.at[i, "NetCashflow"]

    for i in range(anchor_idx - 1, -1, -1):
        daily.at[i, "Balance"] = daily.at[i + 1, "Balance"] - daily.at[i + 1, "NetCashflow"]

    return daily[["Date", "Balance"]]

def aggregate_monthly_data(df: pd.DataFrame) -> pd.DataFrame:
    """日次データを月単位に集計し、直近Nか月に絞る"""
    df["year_month"] = df["Date"].dt.to_period("M")
    monthly = df.groupby("year_month").agg(
        Deposit=("Deposit", "sum"),
        Withdrawal=("Withdrawal", "sum")
    ).reset_index()
    monthly["Net"] = monthly["Deposit"] - monthly["Withdrawal"]
    
    # 直近指定期間のみ抽出
    if not monthly.empty:
        last_month = df["Date"].max().to_period("M")
        months = pd.period_range(last_month - (RECENT_MONTHS - 1), last_month, freq="M")
        result = monthly[monthly["year_month"].isin(months)].copy()
    else:
        result = monthly.copy()
    
    # x軸ラベル用に文字列化（'YYYY-MM'形式）
    result["ym_str"] = result["year_month"].astype(str)
    return result

# ========= グラフ描画 =========
def plot_monthly_chart(monthly_data: pd.DataFrame) -> tuple:
    """月次純増減グラフを描画"""
    def yen_fmt(v, pos):
        return f"¥{int(v):,}"
    
    fig, ax = plt.subplots(figsize=FIGURE_SIZE)
    
    # プラス/マイナスで色を変える
    colors = [COLOR_POSITIVE if v >= 0 else COLOR_NEGATIVE for v in monthly_data["Net"]]
    
    ax.bar(monthly_data["ym_str"], monthly_data["Net"], 
           color=colors, width=BAR_WIDTH)
    
    # グラフの装飾
    title = f"秀夫統合口座 月次の純増減（直近{RECENT_MONTHS}か月）"
    ax.set_title(title, fontsize=TITLE_FONTSIZE, fontfamily=JP_FONT)
    ax.set_xlabel("年月", fontsize=LABEL_FONTSIZE, fontfamily=JP_FONT)
    ax.set_ylabel("純増減（円）", fontsize=LABEL_FONTSIZE, fontfamily=JP_FONT)
    ax.yaxis.set_major_formatter(FuncFormatter(yen_fmt))
    
    # 目盛ラベルにもフォント適用
    for label in ax.get_xticklabels() + ax.get_yticklabels():
        label.set_fontfamily(JP_FONT)
    
    # x軸ラベルの回転
    plt.setp(ax.get_xticklabels(), rotation=45, ha="right")
    
    # ゼロライン
    ax.axhline(0, color="black", lw=1.0)
    
    fig.tight_layout()
    return fig, ax

# ========= メイン処理 =========
def main():
    """メイン処理"""
    # データ読込と前処理
    csv_path = SCRIPT_DIR / "Hideo_balance.csv"
    df = load_and_prepare_data(csv_path)
    daily_bal = create_daily_balance(df)
    
    print(f"データ読込完了: {csv_path}")
    print(f"データ期間: {df['Date'].min().date()} ～ {df['Date'].max().date()}")
    print(f"再構築残高期間: {daily_bal['Date'].min().date()} ～ {daily_bal['Date'].max().date()}")
    
    # 月単位に集計
    monthly_data = aggregate_monthly_data(df)
    
    print(f"\n月次集計結果（直近{RECENT_MONTHS}か月）:")
    for _, row in monthly_data.iterrows():
        print(f"  {row['ym_str']}: 入金=¥{row['Deposit']:,.0f}, 出金=¥{row['Withdrawal']:,.0f}, 純増減=¥{row['Net']:,.0f}")
    
    # グラフ描画
    fig, ax = plot_monthly_chart(monthly_data)
    
    # 保存
    out_path = OUTPUT_DIR / "hideo_chart_monthly_net.pdf.pdf"
    fig.savefig(out_path, format='pdf')
    print(f"\nグラフを保存しました: {out_path}")

if __name__ == "__main__":
    main()
