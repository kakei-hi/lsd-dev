# Juliaソース検証
# A-Index（仮）計算
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

# 低減回帰関数
f <- function(x){
  nu <- 1.1915889
  mu <- 0.1697106
  sig <- 2.2166964
  
  t <- (x - mu) / sig
  
  return((1 + t^2 / nu)^(-(nu + 1) / 2))
  
}

# 外周および遮蔽物を構成する
# 辺を取得する
# 始点(x0, y0)
# 終点(x1, y1)
disassenble_poly <- function(poly_outer, poly_obstruction){
  sides.tbl <-
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
    
    sides.tbl <- bind_rows(sides.tbl, tmp.tbl)
  }
  
  return(sides.tbl)
  
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
if (xx == 1 && yy == 1){
  print(winding_angle)
}
    
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


# 点Xの指標値
indeces <- function(xx, yy, sides.tbl){
  # div_n <- 2000 # スキャン角 分割数
  div_n <- 200 # スキャン角 分割数
  # ll <- 999       # 半直線方向ベクトル用定数
  ll <- 99999       # 半直線方向ベクトル用定数
  
  index_x <- 0    # 点Xの指標値 初期化
  
  n <- nrow(sides.tbl)
  
  vertex.x <- vector()
  vertex.y <- vector()
  adjustment.x <- vector()
  adjustment.y <- vector()
  
  # 半直線とX軸のなす角がthの時
  for (k in 0:(div_n - 1)) {
    th <- k * (2 * pi / div_n)
    dist_crossing <- ll
    
    # ポリゴンを構成する辺の端点を取り出す
    x0 <- sides.tbl$x0
    y0 <- sides.tbl$y0
    x1 <- sides.tbl$x1
    y1 <- sides.tbl$y1
    
    ab.vec <- cbind(rep(ll * cos(th), n),
                    rep(ll * sin(th), n),
                    rep(0, n))
    ac.vec <- cbind(x0 - xx,
                    y0 - yy,
                    0)
    cd.vec <- cbind(x1 - x0,
                    y1 - y0,
                    0)
    ca.vec <- cbind(xx - x0,
                    yy - y0,
                    0)
    # 交点を示すパラメータ(s, t)
    s <- pracma::cross(ac.vec[1:n,], cd.vec[1:n,])[,3] / 
      pracma::cross(ab.vec[1:n,], cd.vec[1:n,])[,3]
    t <- pracma::cross(ca.vec[1:n,], ab.vec[1:n,])[,3] / 
      pracma::cross(cd.vec[1:n,], ab.vec[1:n,])[,3]
    now_dist <- s * ll
    
    # for (i in 1:n) {
    #   if (!is.nan(s[i])  &&
    #       s[i] >= 0 && s[i] <= 1 &&
    #       t[i] >= 0 && t[i] <= 1 &&
    #       dist_crossing > now_dist[i]){
    #     crossing.x <- now_dist[i] * cos(th)
    #     crossing.y <- now_dist[i] * sin(th)
    #     dist_crossing <- now_dist[i]
    #   }
    # }
    
    # ベクトル化による高速化
    s_valid <- !is.nan(s) & s >= 0 & s <= 1
    t_valid <- t >= 0 & t <= 1
    # now_dist_valid <- dist_crossing > now_dist
    
    # 条件判定をベクトル演算で行う
    crossing_idx <- which(s_valid & t_valid)
    # crossing_idx <- which(s_valid & t_valid & now_dist_valid)
    # 有効な点のみ処理
    if (length(crossing_idx) > 0) {
      dist_crossing <- min(now_dist[crossing_idx])
      crossing.x <- dist_crossing * cos(th)
      crossing.y <- dist_crossing * sin(th)
    }
    
    vertex.x <- c(vertex.x, crossing.x)
    vertex.y <- c(vertex.y, crossing.y)
    
    # 積分値
    int_v <- (integrate(f, lower = 0, upper = dist_crossing))$value
    # print(str_c("th = ", 180 * th / pi, "int_v = ", int_v))
    adjustment.x <- c(adjustment.x, int_v * cos(th))
    adjustment.y <- c(adjustment.y, int_v * sin(th))
  }
  isovist <- polyarea(vertex.x, vertex.y)
  a_index <- polyarea(adjustment.x, adjustment.y)
  
  # 点Xにおける指標値
  return(list("isovist" = isovist, "a_index" = a_index))
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
sides_poly.tbl <- disassenble_poly(outer, obstruction)

# 指標計算
index.tbl <-
  data.frame(matrix(rep(NA, 4), nrow = 1))[-1, ] %>%
  as_tibble() %>%
  rename("x" = X1, 
         "y" = X2, 
         "isovist" = X3,
         "a_index" = X4)


# dd <- 0.5 # dd m間隔で計算
dd <- 1.0 # dd m間隔で計算
# dd <- 0.1 # dd m間隔で計算

#測定開始
tic()
for (yy in seq(ymin_outer, ymax_outer, by = dd)) {
  # print(yy)
  for (xx in seq(xmin_outer, xmax_outer, by = dd)){
    if (in_out_judge(xx, yy, outer) == "INSIDE" &&
        in_out_judge(xx, yy, obstruction) == "OUTSIDE"){
      index <- indeces(xx, yy, sides_poly.tbl)
      # index <- indeces(vp[[1]], outer, obstruction)
      index.tbl <-
        index.tbl %>%
        add_row(
          x = xx,
          y = yy,
          isovist = index$isovist,
          a_index = index$a_index
        )
    } else{
      index.tbl <-
        index.tbl %>%
        add_row(
          x = xx,
          y = yy,
          isovist = NA,
          a_index = NA
        )
    }
  }
}
#測定終了
toc()

ggplot() +
  geom_sf(data = outer, colour = "transparent",aes(fill = "Outer")) +
  scale_fill_manual(values = c("Outer" = "grey"),
                    guide = guide_legend(override.aes = list(linetype = c("blank"), shape = c(NA)))) +
  theme_minimal() +
  coord_sf(datum = NA) +
  theme(legend.title=element_blank())

p <-
  index.tbl %>%
  ggplot(aes(x = x, y = y, z = isovist)) +
  stat_contour_filled(bins = 15) + 
  ggtitle("Isovist") +
  theme(aspect.ratio = (ymax_outer - ymin_outer) / (xmax_outer - xmin_outer))
plot(p)

p <-
  index.tbl %>%
  ggplot(aes(x = x, y = y, z = a_index)) +
  stat_contour_filled(bins = 15) + 
  ggtitle("A-Index") +
  theme(aspect.ratio = (ymax_outer - ymin_outer) / (xmax_outer - xmin_outer))
plot(p)