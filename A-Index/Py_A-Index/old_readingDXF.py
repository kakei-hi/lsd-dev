# DXFファイルの読み込み
## 10分でわかるDXFファイル
##  https://qiita.com/catallaxy/items/2eb2825518ca259ed8f5
## Tutorial for Getting Data from DXF Filrs
## https://ezdxf.readthedocs.io/en/stable/tutorials/getting_data.html#tut-getting-data

import ezdxf
import pandas as pd

## DXFファイルを読み込む
try:
  doc = ezdxf.readfile("../Plan/Test_0215.dxf")
# doc = ezdxf.readfile("../Plan/25F_layout_0903.dxf")
except IOError:
  print(f"Not a DXF file or a generic I/O error.")
  sys.exit(1)
except ezdxf.DXFStructureError:
  print(f"Invalid or corrupted DXF file.")
  sys.exit(1)
  
# モデルベースを取得
msp = doc.modelspace()

# Polyline Entityを取得
polylines = msp.query("LWPOLYLINE")

# Polygonごとに座標を取得
polygons = []
data = []
for polyline in polylines:
  points = polyline.get_points()
  polygons.append(points)

# 各Polygonの座標を表示
for i, polygon in enumerate(polygons):
  print(f"Polygon {i + 1}: ")
  for point in polygon:
    print(point)
    data.append([i, point[0], point[1]])

df = pd.DataFrame(data, columns = ["Polygon", "X", "Y"])
print(df)

# Polygonの値ごとの最初の行を取得
first_rows = df.groupby('Polygon').first().reset_index()

# 始点座標を追加
df = pd.concat([df, first_rows], ignore_index = True)
print(df)
df.to_csv("../Plan/polygons_coordinate.csv", index = False)

# # データフレームに格納するためのリストを作成
# data = []

# # Polygonごとに座標を取得
# for polyline in enumerate(polylines):
#   points = polyline.get_points()
#   for point in points:
#     data.append([f"Polygon {i + 1}", point[0], point[1]])
#   
# # データフレームを作成
# df = pd.DataFrame(data, columns = ["Polygon", "X", "Y"])
# 
# # データフレームを表示
# print(df)
