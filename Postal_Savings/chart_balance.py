# -*- coding: utf-8 -*-
# macOS向け：日本語フォント対応／ゼロ到達予測付きの残高推移グラフ

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter
from matplotlib import font_manager as fm
from datetime import datetime

# ========= 1) 日本語フォントの自動選択（macOS想定） =========
# 優先: Hiragino Sans → Yu Gothic → IPAexGothic
JP_CANDIDATES = [
    "Hiragino Sans", "Hiragino Kaku Gothic ProN", "Hiragino Kaku Gothic Pro",
    "Yu Gothic", "YuGothic",
    "IPAexGothic", "IPAGothic", "Noto Sans CJK JP", "Source Han Sans JP"
]

def resolve_jp_font():
    fonts = fm.findSystemFonts(fontext="ttf") + fm.findSystemFonts(fontext="otf")
    resolved = None
    for p in fonts:
        try:
            name = fm.get_font(p).family_name
            for cand in JP_CANDIDATES:
                if cand.lower() in name.lower():
                    resolved = name
                    return resolved
        except Exception:
            continue
    # 最後の保険
    return "IPAexGothic"

# スタイルを先に適用してから、フォント設定で上書き
plt.style.use("seaborn-v0_8")

JP_FONT = resolve_jp_font()
print(f"Using Japanese font: {JP_FONT}")  # デバッグ用
plt.rcParams["font.sans-serif"] = [JP_FONT] + plt.rcParams["font.sans-serif"]
plt.rcParams["font.family"] = "sans-serif"
plt.rcParams["axes.unicode_minus"] = False  # マイナス記号の豆腐回避
plt.rcParams["pdf.fonttype"] = 42  # TrueTypeフォントをPDFに埋め込む

# ========= 2) データ読込 =========
# raw_data.csv は以下の列名を想定:
# Date, Deposit, Withdrawal, Balance, Description
df = pd.read_csv(r"/Users/hidekazukakei/Library/Mobile Documents/com~apple~CloudDocs/上柚木/義母ゆうちょ/raw_data.csv", parse_dates=["Date"])
for c in ["Deposit", "Withdrawal", "Balance"]:
    df[c] = pd.to_numeric(df[c], errors="coerce")
df = df.sort_values("Date").reset_index(drop=True)

# ========= 3) 日次残高系列の作成（前方補間で日次化） =========
bal_df = (
    df[["Date", "Balance"]]
    .dropna()
    .drop_duplicates(subset=["Date"], keep="last")
    .set_index("Date")
    .sort_index()
)
idx = pd.date_range(bal_df.index.min(), bal_df.index.max(), freq="D")
daily_bal = bal_df.reindex(idx).ffill().reset_index()
daily_bal.columns = ["Date", "Balance"]

# ========= 4) 直近365日で線形回帰し、将来に外挿 =========
recent = daily_bal[daily_bal["Date"] >= (daily_bal["Date"].max() - pd.Timedelta(days=365))]
if len(recent) < 30:
    # 1年未満のデータしかないときは全期間で回帰
    recent = daily_bal.copy()

x = (recent["Date"] - recent["Date"].min()).dt.days.values.astype(float)
y = recent["Balance"].values.astype(float)

# 単回帰（最小二乗）
A = np.vstack([x, np.ones_like(x)]).T
slope, intercept = np.linalg.lstsq(A, y, rcond=None)[0]   # y = slope*x + intercept

# ゼロ到達日を推定（y=0 => x_zero = -intercept/slope）
zero_date = None
if slope < 0:
    x_zero = -intercept / slope
    zero_date = (recent["Date"].min() + pd.Timedelta(days=float(x_zero))).date()

# 将来の予測直線（図示用）：直近実績の最終日から180日先まで
t0 = recent["Date"].min()
t_last = daily_bal["Date"].max()
future_idx = pd.date_range(t_last + pd.Timedelta(days=1), t_last + pd.Timedelta(days=180), freq="D")
t_future = (future_idx - t0).days.values.astype(float)
y_future = slope * t_future + intercept

# ========= 5) 図の描画 =========
def yen_fmt(v, pos):
    return f"¥{int(v):,}"

fmt = FuncFormatter(yen_fmt)

fig, ax = plt.subplots(figsize=(10, 4.2))

# 実績残高
ax.plot(daily_bal["Date"], daily_bal["Balance"], color="#1f77b4", lw=2.0, label="残高（実績）")

# 予測直線（赤の破線）
if slope < 0:
    ax.plot(future_idx, y_future, color="red", ls="--", lw=2.0, label="トレンド予測")

# ゼロ到達日の縦線（赤の破線）
if zero_date is not None:
    ax.axvline(pd.to_datetime(zero_date), color="red", ls="--", lw=2.0,
               label=f"ゼロ到達予測: {zero_date}")

# 0円の基準線（横線）
ax.axhline(0, color="black", lw=1.0)

# 体裁（日本語フォントを明示的に指定）
ax.set_title("口座残高の推移（実績）", fontsize=14, fontfamily=JP_FONT)
ax.set_xlabel("日付", fontsize=12, fontfamily=JP_FONT)
ax.set_ylabel("残高（円）", fontsize=12, fontfamily=JP_FONT)
ax.yaxis.set_major_formatter(fmt)
ax.legend(loc="upper left", frameon=True, prop={"family": JP_FONT})
fig.tight_layout()

# 保存
out_path = "/Users/hidekazukakei/Library/Mobile Documents/com~apple~CloudDocs/上柚木/義母ゆうちょ/chart_balance.pdf"
fig.savefig(out_path, format='pdf')
print(f"saved: {out_path}")
