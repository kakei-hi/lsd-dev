# -*- coding: utf-8 -*-
"""主な支出・収入グラフ生成スクリプト（直近12か月、日本語フォント対応）"""

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
RECENT_MONTHS = 12       # 集計対象の直近月数
TOP_N = 7                # 表示する上位件数
FIGURE_SIZE = (12, 5)
TITLE_FONTSIZE = 14
LABEL_FONTSIZE = 12
COLOR_OUTFLOW = "#d62728"  # 赤（支出）
COLOR_INFLOW = "#2ca02c"   # 緑（収入）
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
    for col in ["Deposit", "Withdrawal"]:
        df[col] = pd.to_numeric(df[col], errors="coerce")
    return df.sort_values("Date").reset_index(drop=True)

def aggregate_top_flows(df: pd.DataFrame) -> tuple:
    """直近N月の Description 単位で支出・収入を集計し、上位を抽出"""
    last_date = df["Date"].max()
    cutoff = last_date - pd.DateOffset(months=RECENT_MONTHS)
    df_recent = df[df["Date"] >= cutoff].copy()
    
    # 支出上位（Withdrawal）
    outflows = (
        df_recent.groupby("Description", dropna=False)["Withdrawal"]
        .sum()
        .sort_values(ascending=False)
        .dropna()
    )
    top_outflows = outflows.head(TOP_N)
    
    # 収入上位（Deposit）
    inflows = (
        df_recent.groupby("Description", dropna=False)["Deposit"]
        .sum()
        .sort_values(ascending=False)
        .dropna()
    )
    top_inflows = inflows.head(TOP_N)
    
    return top_outflows, top_inflows

# ========= グラフ描画 =========
def plot_top_flows_chart(top_outflows: pd.Series, top_inflows: pd.Series) -> tuple:
    """支出・収入を横棒グラフで描画（2面構成）"""
    def yen_fmt(v, pos):
        return f"¥{int(v):,}"
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=FIGURE_SIZE)
    
    # --- 左：支出 ---
    ax1.barh(top_outflows.index[::-1], top_outflows.values[::-1], 
             color=COLOR_OUTFLOW)
    ax1.xaxis.set_major_formatter(FuncFormatter(yen_fmt))
    ax1.set_title(f"主な支出（直近{RECENT_MONTHS}か月）", 
                  fontsize=TITLE_FONTSIZE, fontfamily=JP_FONT)
    ax1.set_xlabel("金額（円）", fontsize=LABEL_FONTSIZE, fontfamily=JP_FONT)
    
    # 目盛ラベルにフォント適用
    for label in ax1.get_xticklabels() + ax1.get_yticklabels():
        label.set_fontfamily(JP_FONT)
    
    # --- 右：収入 ---
    ax2.barh(top_inflows.index[::-1], top_inflows.values[::-1], 
             color=COLOR_INFLOW)
    ax2.xaxis.set_major_formatter(FuncFormatter(yen_fmt))
    ax2.set_title(f"主な収入（直近{RECENT_MONTHS}か月）", 
                  fontsize=TITLE_FONTSIZE, fontfamily=JP_FONT)
    ax2.set_xlabel("金額（円）", fontsize=LABEL_FONTSIZE, fontfamily=JP_FONT)
    
    for label in ax2.get_xticklabels() + ax2.get_yticklabels():
        label.set_fontfamily(JP_FONT)
    
    fig.tight_layout()
    return fig, (ax1, ax2)

# ========= メイン処理 =========
def main():
    """メイン処理"""
    # データ読込と前処理
    df = load_and_prepare_data(BASE_DIR / "raw_data.csv")
    
    # 支出・収入を集計
    top_outflows, top_inflows = aggregate_top_flows(df)
    
    # グラフ描画
    fig, (ax1, ax2) = plot_top_flows_chart(top_outflows, top_inflows)
    
    # 保存
    out_path = BASE_DIR / "chart_top_flows_12months.pdf"
    fig.savefig(out_path, format='pdf')
    print(f"saved: {out_path}")

if __name__ == "__main__":
    main()
