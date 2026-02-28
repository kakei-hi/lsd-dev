# -*- coding: utf-8 -*-
"""支出増加率グラフ生成スクリプト（日本語フォント対応）"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter
from matplotlib import font_manager as fm
from pathlib import Path


JP_FONT_CANDIDATES = [
	"Hiragino Sans", "Hiragino Kaku Gothic ProN", "Hiragino Kaku Gothic Pro",
	"Yu Gospel", "YuGothic",
	"IPAexGothic", "IPAGothic", "Noto Sans CJK JP", "Source Han Sans JP"
]
TOP_N = 5
FIGURE_SIZE = (14, 8)
TITLE_FONTSIZE = 14
LABEL_FONTSIZE = 12
BASE_DIR = Path("/Users/hidekazukakei/Library/Mobile Documents/com~apple~CloudDocs/上柚木/義母ゆうちょ")


def resolve_jp_font() -> str:
	"""システムフォントから日本語フォントを自動選択"""
	fonts = fm.findSystemFonts(fontext="ttf") + fm.findSystemFonts(fontext="otf")
	for font_path in fonts:
		try:
			name = fm.get_font(font_path).family_name
			if any(cand.lower() in name.lower() for cand in JP_FONT_CANDIDATES):
				return name
		except Exception:
			continue
	return "IPAexGothic"


plt.style.use("seaborn-v0_8-darkgrid")
JP_FONT = resolve_jp_font()
print(f"Using Japanese font: {JP_FONT}")
plt.rcParams["font.sans-serif"] = [JP_FONT] + plt.rcParams["font.sans-serif"]
plt.rcParams["font.family"] = "sans-serif"
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["pdf.fonttype"] = 42


def load_and_prepare_data(csv_path: Path) -> pd.DataFrame:
	"""CSVファイルを読み込み、前処理を行う"""
	df = pd.read_csv(csv_path, parse_dates=["Date"])
	for col in ["Deposit", "Withdrawal"]:
		df[col] = pd.to_numeric(df[col], errors="coerce")

	if "Description" in df.columns:
		df["Description"] = df["Description"].replace("レッツ永山", "リコーリース")

	return df.sort_values("Date").reset_index(drop=True)


def calculate_withdrawal_growth_rates(df: pd.DataFrame) -> pd.DataFrame:
	"""支出項目ごとの月別集計と増加率を計算"""
	df = df.copy()
	df["YearMonth"] = df["Date"].dt.to_period("M")

	monthly_withdrawals = (
		df[df["Withdrawal"].notna() & (df["Withdrawal"] > 0)]
		.groupby(["Description", "YearMonth"])["Withdrawal"]
		.sum()
		.reset_index()
	)

	rows = []
	for description in monthly_withdrawals["Description"].unique():
		desc_data = monthly_withdrawals[monthly_withdrawals["Description"] == description].sort_values("YearMonth")

		if len(desc_data) < 2:
			continue

		first_amount = float(desc_data.iloc[0]["Withdrawal"])
		last_amount = float(desc_data.iloc[-1]["Withdrawal"])
		increase_amount = last_amount - first_amount
		growth_rate = ((increase_amount / first_amount) * 100) if first_amount > 0 else 0.0

		rows.append(
			{
				"Description": description,
				"FirstAmount": first_amount,
				"LastAmount": last_amount,
				"GrowthRate": growth_rate,
				"IncreaseAmount": increase_amount,
			}
		)

	if not rows:
		return pd.DataFrame(columns=["Description", "FirstAmount", "LastAmount", "GrowthRate", "IncreaseAmount"])

	result = pd.DataFrame(rows)
	return result.sort_values("GrowthRate", ascending=False).reset_index(drop=True)


def plot_growth_rate_chart(top_items: pd.DataFrame):
	"""支出増加率と増加額を2面グラフで描画"""

	def rate_fmt(value, _pos):
		return f"{value:.0f}%"

	def yen_fmt(value, _pos):
		return f"¥{int(value):,}"

	fig, (ax1, ax2) = plt.subplots(1, 2, figsize=FIGURE_SIZE)

	items = top_items["Description"].values
	indices = np.arange(len(items))

	colors_rate = ["#2ca02c" if x >= 0 else "#d62728" for x in top_items["GrowthRate"].values]
	ax1.barh(indices, top_items["GrowthRate"].values, color=colors_rate)
	ax1.set_yticks(indices)
	ax1.set_yticklabels(items)
	ax1.xaxis.set_major_formatter(FuncFormatter(rate_fmt))
	ax1.set_title(f"支出増加率（増加率が大きい上位{TOP_N}項目）", fontsize=TITLE_FONTSIZE, fontfamily=JP_FONT)
	ax1.set_xlabel("増加率（%）", fontsize=LABEL_FONTSIZE, fontfamily=JP_FONT)
	ax1.axvline(x=0, color="black", linestyle="-", linewidth=0.8)

	colors_amount = ["#2ca02c" if x >= 0 else "#d62728" for x in top_items["IncreaseAmount"].values]
	ax2.barh(indices, top_items["IncreaseAmount"].values, color=colors_amount)
	ax2.set_yticks(indices)
	ax2.set_yticklabels(items)
	ax2.xaxis.set_major_formatter(FuncFormatter(yen_fmt))
	ax2.set_title(f"支出増加額（増加率が大きい上位{TOP_N}項目）", fontsize=TITLE_FONTSIZE, fontfamily=JP_FONT)
	ax2.set_xlabel("増加額（円）", fontsize=LABEL_FONTSIZE, fontfamily=JP_FONT)
	ax2.axvline(x=0, color="black", linestyle="-", linewidth=0.8)

	for label in ax1.get_xticklabels() + ax1.get_yticklabels() + ax2.get_xticklabels() + ax2.get_yticklabels():
		label.set_fontfamily(JP_FONT)

	fig.tight_layout(pad=1.5)
	return fig


def main():
	csv_path = BASE_DIR / "raw_data.csv"
	out_path = BASE_DIR / "chart_decrease_ratet.pdf"

	df = load_and_prepare_data(csv_path)
	growth_rates = calculate_withdrawal_growth_rates(df)
	top_growth = growth_rates.head(TOP_N)

	print(f"データ読込完了: {csv_path}")
	print(f"データ期間: {df['Date'].min().date()} ～ {df['Date'].max().date()}")
	print(f"\n支出増加率が大きい上位{TOP_N}項目:")
	for _, row in top_growth.iterrows():
		print(
			f"  {row['Description']}: 初月 ¥{row['FirstAmount']:,.0f} → 最終月 ¥{row['LastAmount']:,.0f} "
			f"({row['GrowthRate']:+.1f}%, 増加額 ¥{row['IncreaseAmount']:+,.0f})"
		)

	fig = plot_growth_rate_chart(top_growth)
	out_path.parent.mkdir(parents=True, exist_ok=True)
	fig.savefig(out_path, format="pdf")
	plt.close(fig)
	print(f"\nグラフを保存しました: {out_path}")


if __name__ == "__main__":
	main()
