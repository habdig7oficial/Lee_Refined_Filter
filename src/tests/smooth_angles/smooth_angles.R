window_angle <- seq(0,19)*pi/20
w <- 1 / sqrt((1:13 - 6)^2 + (1:13 - 6)^2)
w[6] <- 0  # Delete masked pixels

validate <- function(arr, angle_selected){
  expValues <- exp(1i *  angle_selected)
  weightedSum <- sum(w * expValues)
  weightedSum <- weightedSum / sum(w)

  norm <- arr / sum(w)

  s <- sum(norm * sin(angle_selected))
  c <- sum(norm * cos(angle_selected))

  or <- atan2(s, c)

  adjustedAngle <- Arg(weightedSum)
  differences<-(window_angle - adjustedAngle)
  index_closest_to_zero <- which.min(abs(differences))



  print(adjustedAngle )
  return(adjustedAngle)
}

validate_diff <- function(arr, angle_selected){
  expValues <- exp(1i *  angle_selected)
  weightedSum <- sum(w * expValues)
  weightedSum <- weightedSum / sum(w)

  norm <- arr / sum(w)

  s <- sum(norm * sin(angle_selected))
  c <- sum(norm * cos(angle_selected))

  or <- atan2(s, c)

  adjustedAngle <- Arg(weightedSum)
  differences<-(window_angle - adjustedAngle)
  index_closest_to_zero <- which.min(abs(differences))



  print(differences)
  return(differences)
}

