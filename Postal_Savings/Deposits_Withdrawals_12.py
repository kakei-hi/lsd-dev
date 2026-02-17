# -*- coding: utf-8 -*-
"""直近12か月の支出・収入上位5つを抽出・表示するスクリプト"""

import pandas as pd
from pathlib import Path

# ========= 定数定義 =========
TOP_N = 5  # 表示する上位件数
RECENT_MONTHS = 12  # 集計対象の直近月数
BASE_DIR = Path("/Users/hidekazukakei/Library/Mobile Documents/com~apple~CloudDocs/上柚木/義母ゆうちょ")

# ========= データ処理 =========
def load_and_prepare_data(csv_path: Path) -> pd.DataFrame:
    """CSVファイルを読込んでデータを前処理"""
    df = pd.read_csv(csv_path, parse_dates=["Date"])
    for col in ["Deposit", "Withdrawal"]:
        df[col] = pd.to_numeric(df[col], errors="coerce")
    
    # 適用の統一処理：「レッツ永山」を「リコーリース」として集計
    if "Description" in df.columns:
        df["Description"] = df["Description"].replace("レッツ永山", "リコーリース")
    
    return df.sort_values("Date").reset_index(drop=True)

def aggregate_top_flows(df: pd.DataFrame, top_n: int = TOP_N) -> tuple:
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
    top_outflows = outflows.head(top_n)
    
    # 収入上位（Deposit）
    inflows = (
        df_recent.groupby("Description", dropna=False)["Deposit"]
        .sum()
        .sort_values(ascending=False)
        .dropna()
    )
    top_inflows = inflows.head(top_n)
    
    return top_outflows, top_inflows, cutoff

def display_results(top_outflows: pd.Series, top_inflows: pd.Series, cutoff_date: pd.Timestamp):
    """結果を表示"""
    print("=" * 60)
    print(f"直近{RECENT_MONTHS}か月での支出上位{TOP_N}つの適用")
    print(f"（{cutoff_date.strftime('%Y-%m-%d')} 以降）")
    print("=" * 60)
    for i, (desc, amount) in enumerate(top_outflows.items(), 1):
        print(f"{i}. {desc:30s} ¥{int(amount):,}")
    
    print("\n" + "=" * 60)
    print(f"直近{RECENT_MONTHS}か月での収入上位{TOP_N}つの適用")
    print(f"（{cutoff_date.strftime('%Y-%m-%d')} 以降）")
    print("=" * 60)
    for i, (desc, amount) in enumerate(top_inflows.items(), 1):
        print(f"{i}. {desc:30s} ¥{int(amount):,}")
    print("=" * 60)

# ========= メイン処理 =========
def main():
    """メイン実行"""
    # CSVファイルパスを探索
    csv_files = list(BASE_DIR.glob("*.csv"))
    
    if not csv_files:
        print(f"エラー: {BASE_DIR} にCSVファイルが見つかりません")
        return
    
    # 最初のCSVファイルを使用（複数ある場合は最新のものを選択）
    csv_path = sorted(csv_files, key=lambda x: x.stat().st_mtime)[-1]
    print(f"データファイル: {csv_path.name}\n")
    
    # データ読込
    df = load_and_prepare_data(csv_path)
    print(f"データ期間: {df['Date'].min().strftime('%Y-%m-%d')} ～ {df['Date'].max().strftime('%Y-%m-%d')}")
    print(f"総レコード数: {len(df)}\n")
    
    # 上位を集計
    top_outflows, top_inflows, cutoff_date = aggregate_top_flows(df)
    
    # 結果表示
    display_results(top_outflows, top_inflows, cutoff_date)

if __name__ == "__main__":
    main()
