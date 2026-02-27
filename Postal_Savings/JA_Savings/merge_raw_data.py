import pandas as pd
from pathlib import Path

# ソースディレクトリ
source_dir = Path("/Users/hidekazukakei/Library/Mobile Documents/com~apple~CloudDocs/上柚木/秀夫JA_ゆうちょ")

# 出力ディレクトリ（現在のスクリプトと同じディレクトリ）
output_dir = Path(__file__).parent

# CSVファイルを読み込む
ja_file = source_dir / "JA_raw_data.csv"
post_file = source_dir / "POST_raw_data.csv"

print(f"読み込み中: {ja_file}")
ja_df = pd.read_csv(ja_file)

print(f"読み込み中: {post_file}")
post_df = pd.read_csv(post_file)

# 日付型に変換
ja_df['Date'] = pd.to_datetime(ja_df['Date'])
post_df['Date'] = pd.to_datetime(post_df['Date'])

# 2023年7月31日時点の残高を取得
# JA: 2023年7月31日の残高
ja_july_31 = ja_df[ja_df['Date'] == '2023-07-31']
if len(ja_july_31) > 0:
    ja_balance_july_31 = ja_july_31.iloc[0]['Balance']
else:
    ja_balance_july_31 = 0

# POST: 2023年7月31日以前の最後の残高
post_july = post_df[post_df['Date'] <= '2023-07-31']
if len(post_july) > 0:
    post_balance_july_31 = post_july.iloc[-1]['Balance']
else:
    post_balance_july_31 = 0

# 初期残高（2023年7月31日時点の合計）
initial_balance = ja_balance_july_31 + post_balance_july_31

print(f"\n2023年7月31日時点の残高:")
print(f"  JA口座: {ja_balance_july_31:,.0f} 円")
print(f"  POST口座: {post_balance_july_31:,.0f} 円")
print(f"  合計（初期残高）: {initial_balance:,.0f} 円")

# 2023年8月1日以降のデータのみ抽出
ja_filtered = ja_df[ja_df['Date'] >= '2023-08-01'].copy()
post_filtered = post_df[post_df['Date'] >= '2023-08-01'].copy()

# 必要なカラムを選択
ja_selected = ja_filtered[['Date', 'Description', 'Deposit', 'Withdrawal']].copy()
post_selected = post_filtered[['Date', 'Description', 'Deposit', 'Withdrawal']].copy()

# データを統合
combined_df = pd.concat([ja_selected, post_selected], ignore_index=True)

# 日付でソート
combined_df = combined_df.sort_values(by='Date').reset_index(drop=True)

# 日付を文字列形式に戻す
combined_df['Date'] = combined_df['Date'].dt.strftime('%Y-%m-%d')

# NaNを0に変換（計算のため）
combined_df['Deposit'] = combined_df['Deposit'].fillna(0)
combined_df['Withdrawal'] = combined_df['Withdrawal'].fillna(0)

# 先頭に繰越行を追加
carryover_row = pd.DataFrame({
    'Date': ['2023-07-31'],
    'Description': ['繰越'],
    'Deposit': [0],
    'Withdrawal': [0]
})
combined_df = pd.concat([carryover_row, combined_df], ignore_index=True)

# 残高を再計算
balance = initial_balance
balances = []

for idx, row in combined_df.iterrows():
    if idx == 0:
        # 最初の行（繰越）は初期残高のみ
        balances.append(balance)
    else:
        # 入金と出金を適用
        balance = balance + row['Deposit'] - row['Withdrawal']
        balances.append(balance)

# 残高列を追加
combined_df['Balance'] = balances

# 入金・出金がゼロの場合は空欄に戻す（表示用）
combined_df['Deposit'] = combined_df['Deposit'].replace(0, '')
combined_df['Withdrawal'] = combined_df['Withdrawal'].replace(0, '')

# カラムの順序を調整
combined_df = combined_df[['Date', 'Description', 'Deposit', 'Withdrawal', 'Balance']]

# 出力ファイル名
output_file = output_dir / "Hideo_balance.csv"

# CSVファイルとして保存
combined_df.to_csv(output_file, index=False)

print(f"\n統合完了！")
print(f"出力ファイル: {output_file}")
print(f"開始日: 2023年8月1日")
print(f"初期残高（2023年7月31日）: {initial_balance:,.0f} 円")
print(f"最終残高: {balance:,.0f} 円")
print(f"総レコード数: {len(combined_df)}")
print(f"  - JA: {len(ja_selected)} レコード（2023年8月1日以降）")
print(f"  - POST: {len(post_selected)} レコード（2023年8月1日以降）")
print(f"\n最初の5行:")
print(combined_df.head())
print(f"\n最後の5行:")
print(combined_df.tail())
