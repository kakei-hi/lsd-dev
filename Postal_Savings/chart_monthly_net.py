# -*- coding: utf-8 -*-
# 月次の純増減（直近12か月）グラフを生成して PDF 保存
# 前提: raw_data.csv が同ディレクトリに存在
# 環境: macOS（日本語フォント自動解決）

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter
from matplotlib import font_manager as fm
from matplotlib.font_manager import FontProperties
import datetime as dt
import os

# ===== 1) 日本語フォントの解決（macOS優先） =====
CANDIDATES = [
    "Hiragino Sans", "Hiragino Kaku Gothic ProN", "Hiragino Kaku Gothic Pro",
    "Yu Gothic", "YuGothic",
    "IPAexGothic", "Noto Sans CJK JP", "Source Han Sans JP", "IPAGothic"
]

def resolve_jp_fontprop():
    for name in CANDIDATES:
        try:
            path = fm.findfont(FontProperties(family=name), fallback_to_default=False)
            # DejaVu等の英字フォントに落ちていないことを確認
            if path and "DejaVuSans" not in path and "LastResort" not in path:
                return FontProperties(fname=path)
        except Exception:
            pass
    # 最終手段
    return FontProperties(family="IPAexGothic")

FP = resolve_jp_fontprop()
plt.rcParams["axes.unicode_minus"] = False
plt.style.use("seaborn-v0_8")

# ===== 2) データ読み込み・前処理 =====
# 必須列: Date, Deposit, Withdrawal
df = pd.read_csv("raw_data.csv", parse_dates=["Date"])
for c in ["Deposit", "Withdrawal"]:
    df[c] = pd.to_numeric(df[c], errors="coerce").fillna(0.0)
df = df.sort_values("Date").reset_index(drop=True)

# 月単位へ集計
df["year_month"] = df["Date"].dt.to_period("M")
monthly = df.groupby("year_month").agg(
    Deposit=("Deposit", "sum"),
    Withdrawal=("Withdrawal", "sum")
).reset_index()
monthly["Net"] = monthly["Deposit"] - monthly["Withdrawal"]

# 直近12か月に絞る（不足分は0で埋めない＝実在月のみ）
if not monthly.empty:
    last_month = df["Date"].max().to_period("M")
    months = pd.period_range(last_month - 11, last_month, freq="M")
    # reindexして欠測月は0にしたい場合は以下を使用:
    # m12 = monthly.set_index("year_month").reindex(months, fill_value=0).reset_index()
    # 実データがある月のみ表示するなら:
    m12 = monthly[monthly["year_month"].isin(months)].copy()
else:
    m12 = monthly.copy()

# x軸ラベル（文字列）を整える
m12["ym_str"] = m12["year_month"].astype(str)  # 'YYYY-MM'

# ===== 3) プロット =====
def yen_fmt(v, pos):
    return f"¥{int(v):,}"

fmt = FuncFormatter(yen_fmt)

fig, ax = plt.subplots(figsize=(10, 4.2))

# プラス/マイナスで色を変える
colors = ["#2ca02c" if v >= 0 else "#d62728" for v in m12["Net"]]

ax.bar(m12["ym_str"], m12["Net"], color=colors, width=0.6)

# 体裁（日本語フォントを強制適用）
ax.set_title("月次の純増減（直近12か月）", fontproperties=FP, fontsize=14)
ax.set_xlabel("年月", fontproperties=FP, fontsize=12)
ax.set_ylabel("純増減（円）", fontproperties=FP, fontsize=12)
ax.yaxis.set_major_formatter(fmt)

# 目盛ラベルにもフォント適用
for label in ax.get_xticklabels() + ax.get_yticklabels():
    label.set_fontproperties(FP)

# x軸ラベルの回転
plt.setp(ax.get_xticklabels(), rotation=45, ha="right")

# ゼロライン
ax.axhline(0, color="black", lw=1.0)

fig.tight_layout()

# ===== 4) PDF保存 =====
