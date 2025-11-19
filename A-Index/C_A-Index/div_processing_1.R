# A-Index（仮）計算 1
# 前処理
# 入力データの生成
pckg <- "tidyverse"
if(!require(pckg, character.only = TRUE)){
    install.packages(pckg, type = "source")
    if (!require(pckg, character.only = TRUE)){
          str = paste0("could not install ", pckg)
          stop(str)
    }
}

pckg <- "devtools"
if(!require(pckg, character.only = TRUE)){
  install.packages(pckg, type = "binary")
  # install.packages(pckg, type = "source")
  if (!require(pckg, character.only = TRUE)){
    str = paste0("could not install ", pckg)
    stop(str)
  }
}

devtools::install_github( "ingewortel/celltrackR" )
library(celltrackR)

pckg <- "pracma"
if(!require(pckg, character.only = TRUE)){
  install.packages(pckg, type = "source")
  if (!require(pckg, character.only = TRUE)){
    str = paste0("could not install ", pckg)
    stop(str)
  }
}

pckg <- "sf"
if(!require(pckg, character.only = TRUE)){
  install.packages(pckg, type = "binary")
  # install.packages(pckg, type = "source")
  if (!require(pckg, character.only = TRUE)){
          str = paste0("could not install ", pckg)
          stop(str)
    }
}

# for 処理時間測定
pckg <- "tictoc"
if(!require(pckg, character.only = TRUE)){
  install.packages(pckg, type = "source")
  if (!require(pckg, character.only = TRUE)){
    str = paste0("could not install ", pckg)
    stop(str)
  }
}

# 外周および遮蔽物を構成する
# 辺を取得する
# 始点(x0, y0)
# 終点(x1, y1)
disassenble_poly <- function(poly_outer, poly_obstruction){
  edge.tbl <-
    as_tibble(st_coordinates(poly_outer[[1]])) %>%
    select(-c(L1, L2)) %>%
    rename(
      "x0" = X,
      "y0" = Y
    ) %>%
    mutate(x1 = lead(x0, n = 1), y1 = lead(y0, n = 1)) %>%
    drop_na()
  
  for (i in 1:length(poly_obstruction)) {
    tmp.tbl <- 
      as_tibble(st_coordinates(poly_obstruction[[i]])) %>%
      select(-c(L1, L2)) %>%
      rename(
        "x0" = X,
        "y0" = Y
      ) %>%
      mutate(x1 = lead(x0, n = 1), y1 = lead(y0, n = 1)) %>%
      drop_na()
    
    edge.tbl <- bind_rows(edge.tbl, tmp.tbl)
  }
  
  return(edge.tbl)
  
}

# 内外判定（ベクトル化により処理）
# poly1の要素ポリゴンの内，
# 1つでも"INSIDE"となったら
# "INSIDE"を返す
# すべてのポリゴンで"outside"となった場合のみ
# "OUTSIDE"を返す
# 遮蔽物ポリゴンは複数の可能性もあるが
# 外周を構成するポリゴンは1つである
# ことを利用
in_out_judge <- function(xx, yy, poly1){
  for (i in 1:length(poly1)) {
    winding_angle <- 0
    v.tbl <- as_tibble(st_coordinates(poly1[[i]])) 
    n <- nrow(v.tbl)
    
    vec0 <- cbind(v.tbl$X[1:(n - 1)] - xx,
                  v.tbl$Y[1:(n - 1)] - yy,
                  rep(0, n - 1))
    vec1 <- cbind(v.tbl$X[2:(n)] - xx,
                  v.tbl$Y[2:(n)] - yy,
                  rep(0, n - 1))
    theta <- sign(pracma::cross(vec0[1:(n - 1),], vec1[1:(n - 1),])[,3]) * 
      vecAngle(vec0[1:(n - 1),], vec1[1:(n - 1),], degrees = FALSE)
    winding_angle <- sum(theta)
    
    # 計算誤差によりabs(winding_angke) > 0では
    # OUTSIDEの点がINSIDEになることがある
    # if (!is.na(winding_angle) && winding_angle != 0){
    if (!is.na(winding_angle) && winding_angle > 1.0e-10){
        # INSIDE
      return("INSIDE")
    }
  }
  return("OUTSIDE")
}

# 外周の生成
# outer <- rbind(c(0, 0, 1), c(30, 0, 1), c(30, 20, 1), c(0, 20, 1), c(0, 0, 1))
# outer <- rbind(c(0, 0, 1), c(30, 0, 1), c(30, 20, 1), c(15, 10, 1), c(0, 20, 1), c(0, 0, 1))
# outer <- rbind(c(0, 0, 1), c(30, 0, 1), c(30, 20, 1), c(15, 20, 1), c(15, 10, 1), c(0, 10, 1), c(0, 0, 1))
outer <- rbind(c(0, 0, 1), c(30, 0, 1), c(30, 20, 1), c(20, 20, 1), c(20, 10, 1), c(10, 10, 1), c(10, 20, 1), c(0, 20, 1), c(0, 0, 1))
outer <- lapply(split(outer[,1:2], outer[,3]), matrix, ncol=2)
outer <- lapply(X = 1:length(outer), FUN = function(x) {
    st_polygon(outer[x])
})

outer <- st_sfc(outer)
st_crs(outer) <- 3035 
outer <- st_cast(outer,"POLYGON")
bbox_outer <- st_bbox(outer)
xmin_outer <- bbox_outer['xmin']
xmax_outer <- bbox_outer['xmax']
ymin_outer <- bbox_outer['ymin']
ymax_outer <- bbox_outer['ymax']

# 遮蔽物の生成
# obstruction <- rbind(c(0.1, 0.1, 1), c(0.2, 0.1, 1), c(0.2, 0.2, 1), c(0.1, 0.2, 1), c(0.1, 0.1, 1))
obstruction <- rbind(c(5.5, 7.75, 1), c(5.5, 8.25, 1), c(4.5, 8.25, 1), c(4.5, 7.75, 1),
                   c(5.5, 7.75, 1)) %>%
  rbind(c(15.5, 5.0, 2), c(15.5, 6.0, 2), c(14.5, 6.0, 2), c(14.5, 5.0, 2), c(15.5, 5.0, 2))
obstruction <- lapply(split(obstruction[, 1:2], obstruction[,3]), matrix, ncol = 2)
obstruction <- lapply(X = 1:length(obstruction), FUN = function(x){
  st_polygon(obstruction[x])
})
obstruction <- st_sfc(obstruction)
st_crs(obstruction) <- 3035
obstruction <- st_cast(obstruction, "POLYGON")

# 外周および遮蔽物を構成する
# 辺を取得する
edge_poly.tbl <- disassenble_poly(outer, obstruction)

dd <- 0.25 # dd m間隔で計算
# dd <- 0.1 # dd m間隔で計算

# 計算対象点座標格納用tibble
in_out.tbl <- 
  data.frame(matrix(rep(NA, 2), nrow = 1))[-1, ] %>%
  as_tibble() %>%
  rename("x" = X1,
         "y" = X2)

#測定開始
tic()
for (yy in seq(ymin_outer, ymax_outer, by = dd)) {
  # print(yy)
  for (xx in seq(xmin_outer, xmax_outer, by = dd)){
    if (in_out_judge(xx, yy, outer) == "INSIDE" &&
        in_out_judge(xx, yy, obstruction) == "OUTSIDE"){
      in_out.tbl <-
        in_out.tbl %>%
        add_row(
          x = xx,
          y = yy)
    }
    # else {
    #   print(paste("FALSE: ", xx))
    # }
  }
}

#測定終了
toc()

# 辺の端点の座標
# x0, y0, x1, y1
edge_poly.tbl %>%
  write_csv("delivery/edge.csv", col_names = FALSE)

# 外周バウンディングボックス(xmin, ymin, xmax, ymax)
# 格子点間隔 dd
# スキャン角分割数 div_n
tibble(xmin = xmin_outer,
       ymin = ymin_outer,
       xmax = xmax_outer,
       ymax = ymax_outer,
       dd = dd,
       div_n = 200) %>%
  write_csv("delivery/cond.csv", col_names = FALSE)

# 内外判定結果出力
# 計算対象となる点の座標(x, y)
in_out.tbl %>%
  write_csv("delivery/in_out.csv", col_names = FALSE)
