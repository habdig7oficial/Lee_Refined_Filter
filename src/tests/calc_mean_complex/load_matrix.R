calculate_mean_complex <- function(window) {
    complex_values <- exp(1i * window)
    print("COMPLEX")
    #print(complex_values)
    mean_complex <- mean(complex_values)
    print(mean_complex)
    mean_phase <- Arg(mean_complex)
    return(mean_phase)
}


size <- 11

#1
window1 <- matrix(FALSE, nrow = size, ncol = size)
window1[5:7,1:11]<- TRUE


#2
# This window was wrong is all one square down in y
window2 <- matrix(FALSE, nrow = size, ncol = size)


#3
window3 <- matrix(FALSE, nrow = size, ncol = size)

#4
window4 <- matrix(FALSE, nrow = size, ncol = size)

#5
window5 <- matrix(FALSE, nrow = size, ncol = size)
#6
window6 <- matrix(FALSE, nrow = size, ncol = size)

#7
window7 <- matrix(FALSE, nrow = size, ncol = size)

#8
# Potencially wrong, this point was asymmetrical
window8 <- matrix(FALSE, nrow = size, ncol = size)


# this matrix was also wrong because it follow the article
window9 <- matrix(FALSE, nrow = size, ncol = size)

#10
window10 <- matrix(FALSE, nrow = size, ncol = size)

#11
window11 <- matrix(FALSE, nrow = size, ncol = size)

#12
window12 <- matrix(FALSE, nrow = size, ncol = size)

#13
window13 <- matrix(FALSE, nrow = size, ncol = size)

#14
window14 <- matrix(FALSE, nrow = size, ncol = size)

#15
window15 <- matrix(FALSE, nrow = size, ncol = size)

#16
window16 <- matrix(FALSE, nrow = size, ncol = size)

#17
window17 <- matrix(FALSE, nrow = size, ncol = size)

#18
window18 <- matrix(FALSE, nrow = size, ncol = size)

#19
# This is also not symmetric
window19 <- matrix(FALSE, nrow = size, ncol = size)

#20
window20 <- matrix(FALSE, nrow = size, ncol = size)


all_windows<-list(
    window1, 
    window2, 
    window3, 
    window4, 
    window5, 
    window6, 
    window7, 
    window8, 
    window9, 
    window10, 
    window11, 
    window12, 
    window13, window14, window15, window16, window17, window18, window19, window20)