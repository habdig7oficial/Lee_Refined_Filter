
#pacotes
library(terra)
library(raster)
library(circular)
library(filters)


load <- function(path){
  img <- raster(path)
  img <- as.matrix(img)
  return(img)
#
}

