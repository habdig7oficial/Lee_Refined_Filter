# Custom

size <- 11

#1
window1 <- matrix(FALSE, nrow = size, ncol = size)
window1[5:7,1:11]<- TRUE


#2
# This window was wrong is all one square down in y
window2 <- matrix(FALSE, nrow = size, ncol = size)
window2[8,1:4]  <- TRUE
window2[7,1:7]  <- TRUE
window2[6,1:11] <- TRUE
window2[5,5:11] <- TRUE
window2[4,8:11] <- TRUE

#3
window3 <- matrix(FALSE, nrow = size, ncol = size)
window3[3,10:11] <- TRUE
window3[4,8:11]  <- TRUE
window3[5,5:11]  <- TRUE
window3[6,4:8]   <- TRUE
window3[7,1:7]   <- TRUE
window3[8,1:4]   <- TRUE
window3[9,1:2]   <- TRUE
#4
window4 <- matrix(FALSE, nrow = size, ncol = size)
window4[2,11]    <- TRUE
window4[3,10:11] <- TRUE
window4[4,8:11]  <- TRUE
window4[5,5:10]  <- TRUE
window4[6,4:8]   <- TRUE
window4[7,2:7]   <- TRUE
window4[8,1:4]   <- TRUE
window4[9,1:2]   <- TRUE
window4[10,1]    <- TRUE
#5
window5 <- matrix(FALSE, nrow = size, ncol = size)
window5[11,1]    <- TRUE
window5[10,1:2]  <- TRUE
window5[9,1:3]   <- TRUE
window5[8,2:4]   <- TRUE
window5[7,3:7]   <- TRUE
window5[6,4:8]   <- TRUE
window5[5,5:9]   <- TRUE
window5[4,8:10]  <- TRUE
window5[3,9:11]  <- TRUE
window5[2,10:11] <- TRUE
window5[1,11]    <- TRUE
#6
window6 <- matrix(FALSE, nrow = size, ncol = size)
window6[11,1:2]  <- TRUE
window6[10,1:3]  <- TRUE
window6[9,2:4]   <- TRUE
window6[8,3:5]   <- TRUE
window6[7,4:6]   <- TRUE
window6[6,5:7]   <- TRUE
window6[5,6:8]   <- TRUE
window6[4,7:9]   <- TRUE
window6[3,8:10]  <- TRUE
window6[2,9:11]  <- TRUE
window6[1,10:11] <- TRUE
#7
window7 <- matrix(FALSE, nrow = size, ncol = size)
window7[11,1:3] <- TRUE
window7[10,2:4] <- TRUE
window7[9,3:5]  <- TRUE
window7[8,3:5]  <- TRUE
window7[7,3:6]  <- TRUE
window7[6,4:8]  <- TRUE
window7[5,6:9]  <- TRUE
window7[4,7:9]  <- TRUE
window7[3,7:9]  <- TRUE
window7[2,8:10] <- TRUE
window7[1,9:11] <- TRUE
#8
# Potencially wrong, this point was asymmetrical
window8 <- matrix(FALSE, nrow = size, ncol = size)
window8[11,2:4] <- TRUE
window8[10,3:5] <- TRUE
window8[9,4:5]  <- TRUE
window8[8,4:5]  <- TRUE
window8[7,4:6]  <- TRUE
window8[6,4:8]  <- TRUE # This point
window8[5,6:8]  <- TRUE
window8[4,7:8]  <- TRUE
window8[3,7:8]  <- TRUE
window8[2,7:9]  <- TRUE
window8[1,8:10] <- TRUE
#9
# this matrix was also wrong because it follow the article
window9 <- matrix(FALSE, nrow = size, ncol = size)
window9[11,3:5] <- TRUE
window9[10,4:6] <- TRUE
window9[9,4:6]  <- TRUE
window9[8,5:6]  <- TRUE
window9[7,5:6]  <- TRUE
window9[6,5:7]  <- TRUE
window9[5,6:7]  <- TRUE
window9[4,6:7]  <- TRUE
window9[3,6:8]  <- TRUE
window9[2,6:8]  <- TRUE 
window9[1,7:9] <- TRUE 
#10
window10 <- matrix(FALSE, nrow = size, ncol = size)
window10[11,4:6] <- TRUE 
window10[10,4:6] <- TRUE 
window10[9,4:6] <- TRUE 
window10[8,5:6] <- TRUE 
window10[7,5:7] <- TRUE 
window10[6,5:7] <- TRUE 
window10[5,5:7] <- TRUE 
window10[4,6:7] <- TRUE 
window10[3,6:8] <- TRUE 
window10[2,6:8] <- TRUE 
window10[1,6:8] <- TRUE 
#11
window11 <- matrix(FALSE, nrow = size, ncol = size)
window11[1:11,5:7]<- TRUE 
#12
window12 <- matrix(FALSE, nrow = size, ncol = size)
window12[11,6:8] <- TRUE 
window12[10,6:8] <- TRUE 
window12[9,6:8]  <- TRUE 
window12[8,6:8]  <- TRUE 
window12[7,5:7]  <- TRUE 
window12[6,5:7]  <- TRUE 
window12[5,5:7]  <- TRUE 
window12[4,4:6]  <- TRUE 
window12[3,4:6]  <- TRUE 
window12[2,4:6]  <- TRUE 
window12[1,4:6]  <- TRUE 
#13
window13 <- matrix(FALSE, nrow = size, ncol = size)
window13[11,7:9] <- TRUE 
window13[10,7:9] <- TRUE 
window13[9,7:8]  <- TRUE 
window13[8,6:8]  <- TRUE 
window13[7,5:7]  <- TRUE 
window13[6,5:7]  <- TRUE 
window13[5,5:7]  <- TRUE
window13[4,4:6]  <- TRUE
window13[3,4:5]  <- TRUE 
window13[2,3:5]  <- TRUE 
window13[1,3:5]  <- TRUE
#14
window14 <- matrix(FALSE, nrow = size, ncol = size)
window14[11,8:10] <- TRUE 
window14[10,7:9] <- TRUE 
window14[9,7:8]  <- TRUE 
window14[8,6:8]  <- TRUE 
window14[7,5:7]  <- TRUE 
window14[6,5:7]  <- TRUE 
window14[5,5:7]  <- TRUE
window14[4,4:6]  <- TRUE 
window14[3,4:5]  <- TRUE 
window14[2,3:5]  <- TRUE 
window14[1,2:4]  <- TRUE 
#15
window15 <- matrix(FALSE, nrow = size, ncol = size)
window15[11,9:11] <- TRUE
window15[10,8:10] <- TRUE 
window15[9,7:9]  <- TRUE 
window15[8,6:8]  <- TRUE 
window15[7,5:7]  <- TRUE
window15[6,5:7]  <- TRUE 
window15[5,5:7]  <- TRUE 
window15[4,4:6]  <- TRUE 
window15[3,3:5]  <- TRUE 
window15[2,2:4]  <- TRUE 
window15[1,1:3]  <- TRUE 
#16
window16 <- matrix(FALSE, nrow = size, ncol = size)
window16[11,10:11] <- TRUE 
window16[10,9:11] <- TRUE 
window16[9,8:10]  <- TRUE 
window16[8,7:9]  <- TRUE 
window16[7,6:8]  <- TRUE 
window16[6,5:7]  <- TRUE 
window16[5,4:6]  <- TRUE 
window16[4,3:5]  <- TRUE 
window16[3,2:4]  <- TRUE 
window16[2,1:3]  <- TRUE 
window16[1,1:2]  <- TRUE 
#17
window17 <- matrix(FALSE, nrow = size, ncol = size)
window17[11,11] <- TRUE 
window17[10,10:11] <- TRUE 
window17[9,7:11]  <- TRUE 
window17[8,6:10]  <- TRUE 
window17[7,6:9]  <- TRUE 
window17[6,5:7]  <- TRUE 
window17[5,3:6]  <- TRUE 
window17[4,2:6]  <- TRUE 
window17[3,1:5]  <- TRUE 
window17[2,1:2]  <- TRUE 
window17[1,1]  <- TRUE 
#18
window18 <- matrix(FALSE, nrow = size, ncol = size)
window18[10,11] <- TRUE 
window18[9,10:11]  <- TRUE 
window18[8,6:11]  <- TRUE
window18[7,6:10]  <- TRUE 
window18[6,5:7]  <- TRUE 
window18[5,2:6]  <- TRUE 
window18[4,1:6]  <- TRUE 
window18[3,1:2]  <- TRUE 
window18[2,1]  <- TRUE 
#19
# This is also not symmetric
window19 <- matrix(FALSE, nrow = size, ncol = size)
window19[9,11]  <- TRUE
window19[8,9:11]  <- TRUE 
window19[7,6:11]  <- TRUE # Another asymmetrical point
window19[6,2:10]  <- TRUE
window19[5,1:6]  <- TRUE
window19[4,1:3]  <- TRUE
window19[3,1]  <- TRUE 
#20
window20 <- matrix(FALSE, nrow = size, ncol = size)
window20[8,9:11]  <- TRUE 
window20[7,5:11]  <- TRUE 
window20[6,1:11]  <- TRUE 
window20[5,1:7]  <- TRUE
window20[4,1:3]  <- TRUE 

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
    window12, window13, window14, window15, window16, window17, window18, window19, window20)