# DXFファイルの読み込み

import ezdxf
import pandas as pd
import sys

def process_dxf(dxf_filepath, output_csv_filepath):
  """
  DXFファイルを読み込む
  ポリゴンごとの始点座標をデータに追加する
  CSVファイルに出力する
  """
  try:
    doc = ezdxf.readfile(dxf_filepath)
  except IOError:
    print(f"Error: Not a DXF file or a generic I/O error: {dxf_filepath}")
    sys.exit(1)
  except ezdxf.DXFStructureError:
    print(f"Error: Invalid or corrupted DXF file: {dxf_filepath}")
    sys.exit(1)
    
  msp = doc.modelspace()
  polylines = msp.query("LWPOLYLINE")
  
  data = []
  for i, polyline in enumerate(polylines):
    points = polyline.get_points()
    for point in points:
      data.append([i, point[0], point[1]])
      
    # # 始点座標を追加（pointsが空でない場合のみ）
    # if points:
    #   first_point = points[0]
    #   data.append([i, first_point[0], first_point[1]])
        
  df = pd.DataFrame(data, columns = ["PolygonID", "X", "Y"])
  df.to_csv(output_csv_filepath, index = False)
  print(f"Successfully wrote polygon coordinates to {output_csv_filepath}")

if __name__ == "__main__":
  dxf_filepath = "../Plan/25F_3.dxf"
  csv_filepath = "../Plan/25F_3.csv"
  process_dxf(dxf_filepath, csv_filepath)
  
