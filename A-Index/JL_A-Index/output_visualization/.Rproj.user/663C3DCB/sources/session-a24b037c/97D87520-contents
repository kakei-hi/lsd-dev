# Juliaよりデータフレームを受け取り
# 可視化する

pckg <- "tidyverse"
if(!require(pckg, character.only = TRUE)){
    install.packages(pckg, type = "source")
    if (!require(pckg, character.only = TRUE)){
          str = paste0("could not install ", pckg)
          stop(str)
    }
}

df <- read_csv("../subject_cal_df.csv")
p <-
  df %>%
  ggplot(aes(x = xx, y = yy, z = cal)) +
  stat_contour_filled(bins = 15)
plot(p)

# df <-
#   df %>%
#   filter((cal != 1) & 
#            (xx >= 14.5) & (xx <= 15.5) &
#            (yy == 5))
# 
# df
