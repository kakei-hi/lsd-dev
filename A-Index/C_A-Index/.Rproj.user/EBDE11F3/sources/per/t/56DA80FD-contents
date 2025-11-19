# Rcppテスト
pckg <- "tidyverse"
if(!require(pckg, character.only = TRUE)){
    install.packages(pckg, type = "source")
    if (!require(pckg, character.only = TRUE)){
          str = paste0("could not install ", pckg)
          stop(str)
    }
}

pckg <- "rbenchmark"
if(!require(pckg, character.only = TRUE)){
    install.packages(pckg, type = "source")
    if (!require(pckg, character.only = TRUE)){
          str = paste0("could not install ", pckg)
          stop(str)
    }
}

pckg <- "Rcpp"
if(!require(pckg, character.only = TRUE)){
    install.packages(pckg, type = "source")
    if (!require(pckg, character.only = TRUE)){
          str = paste0("could not install ", pckg)
          stop(str)
    }
}

# Rcppを使用した場合
with_rcpp <- function(n){
  x <- 0
  sourceCpp("calculation.cpp")
  
  return(loop(x, n))
  
}

# Rのみの場合
only_r <- function(n){
  for (i in 1:n) {
    for (j in 1:n) {
      x <- x +1
    }
  }
  return(x)
}

loop_num <- 10000
benchmark(with_rcpp(loop_num), only_r(loop_num),
          replications = 10)
