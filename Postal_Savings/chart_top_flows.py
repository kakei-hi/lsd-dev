# -*- coding: utf-8 -*-
# 直近6か月の主な支出・収入を横棒グラフ（2面）で描画し、PDF保存します。
# 前提: raw_data.csv がカレントディレクトリに存在
# 環境: macOS（日本語フォントを自動解決して豆腐を防止）

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter
from matplotlib import font_manager as fm
from matplotlib.font_manager import FontProperties
from datetime import timedelta
import os

# ===== 1) 日本語フォントの解決（macOS優先） =====
CANDIDATES = [
    "Hiragino Sans", "Hiragino Kaku Gothic ProN", "Hiragino Kaku Gothic Pro",
    "Yu Gothic", "YuGothic",
    "IPAexGothic", "Noto Sans CJK JP", "Source Han Sans JP", "IPAGothic"
]

def resolve_jp_fontprop():
    """候補フォントから最初に見つかった日本語フォントを返す。"""
    for name in CANDIDATES:
        try:
            path = fm.findfont(FontProperties(family=name), fallback_to_default=False)
            # DejaVu/LastResort 等の非日本語フォントに落ちていないか確認
            if path and "DejaVuSans" not in path and "LastResort" not in path:
                return FontProperties(fname=path)
        except Exception:
            pass
    # 最終手段（環境により表示できることがある）
    return FontProperties(family="IPAexGothic")

FP = resolve_jp_fontprop()
plt.rcParams["axes.unicode_minus"] = False
plt.style.use("seaborn-v0_8")

# ===== 2) データ読み込み・直近6か月抽出 =====
df = pd.read_csv("raw_data.csv", parse_dates=["Date"])
for c in ["Deposit", "Withdrawal"]:
    df[c] = pd.to_numeric(df[c], errors="coerce")

df = df.sort_values("Date").reset_index(drop=True)

# 直近6か月の期間
last_date = df["Date"].max()
cutoff = last_date - pd.DateOffset(months=6)
df6 = df[df["Date"] >= cutoff].copy()

# ===== 3) 集計（Description単位） =====
# 支出上位（Withdrawalの合計が大きい順）
outflows = (
    df6.groupby("Description", dropna=False)["Withdrawal"]
       .sum()
       .sort_values(ascending=False)
       .dropna()
)
# 収入上位（Depositの合計が大きい順）
inflows = (
    df6.groupby("Description", dropna=False)["Deposit"]
       .sum()
       .sort_values(ascending=False)
       .dropna()
)

# 上位件数（必要に応じて変更可）
TOP_N = 7
top_out = outflows.head(TOP_N)
top_in  = inflows.head(TOP_N)

# 欠損やゼロ表記を避けたい場合は、以下で0超のみを対象にすることも可能
# top_out = top_out[top_out > 0]
# top_in  = top_in[top_in > 0]

# ===== 4) プロット（横棒・2面） =====
def yen_fmt(v, pos):
    return f"¥{int(v):,}"

fmt = FuncFormatter(yen_fmt)

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

# --- 左：支出 ---
ax1.barh(top_out.index[::-1], top_out.values[::-1], color="#d62728")  # 赤
ax1.xaxis.set_major_formatter(fmt)
ax1.set_title("主な支出（直近6か月）", fontproperties=FP, fontsize=14)
ax1.set_xlabel("金額（円）", fontproperties=FP, fontsize=12)
# 目盛ラベルにフォント適用
for label in ax1.get_xticklabels() + ax1.get_yticklabels():
    label.set_fontproperties(FP)

# --- 右：収入 ---
ax2.barh(top_in.index[::-1], top_in.values[::-1], color="#2ca02c")   # 緑
ax2.xaxis.set_major_formatter(fmt)
ax2.set_title("主な収入（直近6か月）", fontproperties=FP, fontsize=14)
ax2.set_xlabel("金額（円）", fontproperties=FP, fontsize=12)
for label in ax2.get_xticklabels() + ax2.get_yticklabels():
    label.set_fontproperties(FP)

fig.tight_layout()

# ===== 5) PDF保存 =====
out_pdf = "chart_top_flows_6months.pdf"
fig.savefig(out_pdf, dpi=300)  # PDFで保存（埋め込みフォントは環境依存）
plt.close(fig)
print(f"Saved: {os.path.abspath(out_pdf)}")
