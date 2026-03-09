# -*- coding: utf-8 -*-
"""秀夫統合口座 支出増加率グラフ生成スクリプト（日本語フォント対応）"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter, MaxNLocator
from matplotlib import font_manager as fm
from pathlib import Path

# ========= 定数定義 =========
JP_FONT_CANDIDATES = [
    "Hiragino Sans", "Hiragino Kaku Gothic ProN", "Hiragino Kaku Gothic Pro",
    "Yu Gospel", "YuGothic",
    "IPAexGothic", "IPAGothic", "Noto Sans CJK JP", "Source Han Sans JP"
]
TOP_N = 5                # 表示する上位件数
FIGURE_SIZE = (14, 8)    # グラフサイズ
TITLE_FONTSIZE = 14
LABEL_FONTSIZE = 12
COLOR_OUTFLOW = "#d62728"  # 赤（支出）
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

def calculate_withdrawal_growth_rates(df: pd.DataFrame) -> pd.DataFrame:
    """支出項目ごとの月別集計と増加率を計算"""
    
    # 月ごとの支出を集計
    df['YearMonth'] = df['Date'].dt.to_period('M')
    monthly_withdrawals = (
        df[df['Withdrawal'].notna() & (df['Withdrawal'] > 0)]
        .groupby(['Description', 'YearMonth'])['Withdrawal']
        .sum()
        .reset_index()
    )
    
    # 各項目について、最初と最後の月の支出額を取得
    results = []
    for description in monthly_withdrawals['Description'].unique():
        desc_data = monthly_withdrawals[monthly_withdrawals['Description'] == description].sort_values('YearMonth')
        
        if len(desc_data) >= 2:
            first_amount = desc_data.iloc[0]['Withdrawal']
            last_amount = desc_data.iloc[-1]['Withdrawal']
            
            # 増加率を計算（%)
            if first_amount > 0:
                growth_rate = ((last_amount - first_amount) / first_amount) * 100
            else:
                growth_rate = 0
            
            # 増加額
            increase_amount = last_amount - first_amount
            
            # 全期間合計
            total_amount = desc_data['Withdrawal'].sum()
            
            results.append({
                'Description': description,
                'FirstAmount': first_amount,
                'LastAmount': last_amount,
                'GrowthRate': growth_rate,
                'IncreaseAmount': increase_amount,
                'TotalAmount': total_amount
            })
    
    results_df = pd.DataFrame(results)
    
    # 増加率の降順でソート（負の増加率も含める）
    results_df = results_df.sort_values('GrowthRate', ascending=False)
    
    return results_df

# ========= グラフ描画 =========
def plot_growth_rate_chart(top_items: pd.DataFrame) -> tuple:
    """支出増加率と増加額を2面グラフで描画"""
    
    def rate_fmt(v, pos):
        return f"{v:.0f}%"
    
    def yen_fmt(v, pos):
        return f"¥{int(v):,}"
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=FIGURE_SIZE)
    
    # 項目名の順序を確保
    items = top_items['Description'].values
    indices = np.arange(len(items))
    
    # --- 左：増加率 ---
    colors = ["#2ca02c" if x >= 0 else "#d62728" for x in top_items['GrowthRate'].values]
    ax1.barh(indices, top_items['GrowthRate'].values, color=colors)
    ax1.set_yticks(indices)
    ax1.set_yticklabels(items)
    ax1.xaxis.set_major_formatter(FuncFormatter(rate_fmt))
    ax1.set_title(f"支出増加率（増加率が大きい上位{TOP_N}項目）", 
                  fontsize=TITLE_FONTSIZE, fontfamily=JP_FONT)
    ax1.set_xlabel("増加率（%）", fontsize=LABEL_FONTSIZE, fontfamily=JP_FONT)
    ax1.axvline(x=0, color='black', linestyle='-', linewidth=0.8)
    
    # 目盛ラベルにフォント適用
    for label in ax1.get_xticklabels() + ax1.get_yticklabels():
        label.set_fontfamily(JP_FONT)
    
    # --- 右：増加額 ---
    colors2 = ["#2ca02c" if x >= 0 else "#d62728" for x in top_items['IncreaseAmount'].values]
    ax2.barh(indices, top_items['IncreaseAmount'].values, color=colors2)
    ax2.set_yticks(indices)
    ax2.set_yticklabels(items)
    ax2.xaxis.set_major_formatter(FuncFormatter(yen_fmt))
    ax2.set_title(f"支出増加額（増加率が大きい上位{TOP_N}項目）", 
                  fontsize=TITLE_FONTSIZE, fontfamily=JP_FONT)
    ax2.set_xlabel("増加額（円）", fontsize=LABEL_FONTSIZE, fontfamily=JP_FONT)
    ax2.axvline(x=0, color='black', linestyle='-', linewidth=0.8)
    
    for label in ax2.get_xticklabels() + ax2.get_yticklabels():
        label.set_fontfamily(JP_FONT)
    
    fig.tight_layout(pad=1.5)
    return fig

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
    
    # 支出増加率を計算
    growth_rates = calculate_withdrawal_growth_rates(df)
    
    # 増加率が大きい上位N項目を抽出
    top_growth = growth_rates.head(TOP_N)
    
    print(f"\n支出増加率が大きい上位{TOP_N}項目:")
    for idx, row in top_growth.iterrows():
        print(f"  {row['Description']}: "
              f"初月 ¥{row['FirstAmount']:,.0f} → 最終月 ¥{row['LastAmount']:,.0f} "
              f"({row['GrowthRate']:+.1f}%, 増加額 ¥{row['IncreaseAmount']:+,.0f})")
    
    # グラフ描画
    fig = plot_growth_rate_chart(top_growth)
    
    # 保存
    out_path = OUTPUT_DIR / "hideo_chart_decrease_ratet.pdf"
    out_path.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(out_path, format='pdf')
    print(f"\nグラフを保存しました: {out_path}")
    plt.close(fig)

if __name__ == "__main__":
    main()
