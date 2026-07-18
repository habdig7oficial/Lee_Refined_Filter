#1
window1 <- matrix(FALSE, nrow = size, ncol = size)
window1[5:7,1:11] <- matrix[5:7,1:11]


#2
# This window was wrong is all one square down in y
window2 <- matrix(FALSE, nrow = size, ncol = size)
window2[8,1:4]  <- matrix[8,1:4]
window2[7,1:7]  <- matrix[7,1:7]
window2[6,1:11] <- matrix[6,1:11]
window2[5,5:11] <- matrix[5,5:11]
window2[4,8:11] <- matrix[4,8:11]

#3
window3 <- matrix(FALSE, nrow = size, ncol = size)
window3[3,10:11] <- matrix[3,10:11]
window3[4,8:11]  <- matrix[4,8:11]
window3[5,5:11]  <- matrix[5,5:11]
window3[6,4:8]   <- matrix[6,4:8]
window3[7,1:7]   <- matrix[7,1:7]
window3[8,1:4]   <- matrix[8,1:4]
window3[9,1:2]   <- matrix[9,1:2]

#4
window4 <- matrix(FALSE, nrow = size, ncol = size)
window4[2,11]    <- matrix[2,11]
window4[3,10:11] <- matrix[3,10:11]
window4[4,8:11]  <- matrix[4,8:11]
window4[5,5:10]  <- matrix[5,5:10]
window4[6,4:8]   <- matrix[6,4:8]
window4[7,2:7]   <- matrix[7,2:7]
window4[8,1:4]   <- matrix[8,1:4]
window4[9,1:2]   <- matrix[9,1:2]
window4[10,1]    <- matrix[10,1]

#5
window5 <- matrix(FALSE, nrow = size, ncol = size)
window5[11,1]    <- matrix[11,1]
window5[10,1:2]  <- matrix[10,1:2]
window5[9,1:3]   <- matrix[9,1:3]
window5[8,2:4]   <- matrix[8,2:4]
window5[7,3:7]   <- matrix[7,3:7]
window5[6,4:8]   <- matrix[6,4:8]
window5[5,5:9]   <- matrix[5,5:9]
window5[4,8:10]  <- matrix[4,8:10]
window5[3,9:11]  <- matrix[3,9:11]
window5[2,10:11] <- matrix[2,10:11]
window5[1,11]    <- matrix[1,11]

#6
window6 <- matrix(FALSE, nrow = size, ncol = size)
window6[11,1:2]  <- matrix[11,1:2]
window6[10,1:3]  <- matrix[10,1:3]
window6[9,2:4]   <- matrix[9,2:4]
window6[8,3:5]   <- matrix[8,3:5]
window6[7,4:6]   <- matrix[7,4:6]
window6[6,5:7]   <- matrix[6,5:7]
window6[5,6:8]   <- matrix[5,6:8]
window6[4,7:9]   <- matrix[4,7:9]
window6[3,8:10]  <- matrix[3,8:10]
window6[2,9:11]  <- matrix[2,9:11]
window6[1,10:11] <- matrix[1,10:11]

#7
window7 <- matrix(FALSE, nrow = size, ncol = size)
window7[11,1:3] <- matrix[11,1:3]
window7[10,2:4] <- matrix[10,2:4]
window7[9,3:5]  <- matrix[9,3:5]
window7[8,3:5]  <- matrix[8,3:5]
window7[7,3:6]  <- matrix[7,3:6]
window7[6,4:8]  <- matrix[6,4:8]
window7[5,6:9]  <- matrix[5,6:9]
window7[4,7:9]  <- matrix[4,7:9]
window7[3,7:9]  <- matrix[3,7:9]
window7[2,8:10] <- matrix[2,8:10]
window7[1,9:11] <- matrix[1,9:11]

#8
# Potencially wrong, this point was asymmetrical
window8 <- matrix(FALSE, nrow = size, ncol = size)
window8[11,2:4] <- matrix[11,2:4]
window8[10,3:5] <- matrix[10,3:5]
window8[9,4:5]  <- matrix[9,4:5]
window8[8,4:5]  <- matrix[8,4:5]
window8[7,4:6]  <- matrix[7,4:6]
window8[6,4:8]  <- matrix[6,4:8] # This point
window8[5,6:8]  <- matrix[5,6:8]
window8[4,7:8]  <- matrix[4,7:8]
window8[3,7:8]  <- matrix[3,7:8]
window8[2,7:9]  <- matrix[2,7:9]
window8[1,8:10] <- matrix[1,8:10]

#9
# this matrix was also wrong because it follow the article
window9 <- matrix(FALSE, nrow = size, ncol = size)
window9[11,3:5] <- matrix[11,3:5]
window9[10,4:6] <- matrix[10,4:6]
window9[9,4:6]  <- matrix[9,4:6]
window9[8,5:6]  <- matrix[8,5:6]
window9[7,5:6]  <- matrix[7,5:6]
window9[6,5:7]  <- matrix[6,5:7]
window9[5,6:7]  <- matrix[5,6:7]
window9[4,6:7]  <- matrix[4,6:7]
window9[3,6:8]  <- matrix[3,6:8]
window9[2,6:8]  <- matrix[2,6:8] 
window9[1,7:9]  <- matrix[1,7:9] 

#10
window10 <- matrix(FALSE, nrow = size, ncol = size)
window10[11,4:6] <- matrix[11,4:6] 
window10[10,4:6] <- matrix[10,4:6] 
window10[9,4:6]  <- matrix[9,4:6] 
window10[8,5:6]  <- matrix[8,5:6] 
window10[7,5:7]  <- matrix[7,5:7] 
window10[6,5:7]  <- matrix[6,5:7] 
window10[5,5:7]  <- matrix[5,5:7] 
window10[4,6:7]  <- matrix[4,6:7] 
window10[3,6:8]  <- matrix[3,6:8] 
window10[2,6:8]  <- matrix[2,6:8] 
window10[1,6:8]  <- matrix[1,6:8] 

#11
window11 <- matrix(FALSE, nrow = size, ncol = size)
window11[1:11,5:7] <- matrix[1:11,5:7] 

#12
window12 <- matrix(FALSE, nrow = size, ncol = size)
window12[11,6:8] <- matrix[11,6:8] 
window12[10,6:8] <- matrix[10,6:8] 
window12[9,6:8]  <- matrix[9,6:8] 
window12[8,6:8]  <- matrix[8,6:8] 
window12[7,5:7]  <- matrix[7,5:7] 
window12[6,5:7]  <- matrix[6,5:7] 
window12[5,5:7]  <- matrix[5,5:7] 
window12[4,4:6]  <- matrix[4,4:6] 
window12[3,4:6]  <- matrix[3,4:6] 
window12[2,4:6]  <- matrix[2,4:6] 
window12[1,4:6]  <- matrix[1,4:6] 

#13
window13 <- matrix(FALSE, nrow = size, ncol = size)
window13[11,7:9] <- matrix[11,7:9] 
window13[10,7:9] <- matrix[10,7:9] 
window13[9,7:8]  <- matrix[9,7:8] 
window13[8,6:8]  <- matrix[8,6:8] 
window13[7,5:7]  <- matrix[7,5:7] 
window13[6,5:7]  <- matrix[6,5:7] 
window13[5,5:7]  <- matrix[5,5:7]
window13[4,4:6]  <- matrix[4,4:6]
window13[3,4:5]  <- matrix[3,4:5] 
window13[2,3:5]  <- matrix[2,3:5] 
window13[1,3:5]  <- matrix[1,3:5]

#14
window14 <- matrix(FALSE, nrow = size, ncol = size)
window14[11,8:10] <- matrix[11,8:10] 
window14[10,7:9]  <- matrix[10,7:9] 
window14[9,7:8]   <- matrix[9,7:8] 
window14[8,6:8]   <- matrix[8,6:8] 
window14[7,5:7]   <- matrix[7,5:7] 
window14[6,5:7]   <- matrix[6,5:7] 
window14[5,5:7]   <- matrix[5,5:7]
window14[4,4:6]   <- matrix[4,4:6] 
window14[3,4:5]   <- matrix[3,4:5] 
window14[2,3:5]   <- matrix[2,3:5] 
window14[1,2:4]   <- matrix[1,2:4] 

#15
window15 <- matrix(FALSE, nrow = size, ncol = size)
window15[11,9:11] <- matrix[11,9:11]
window15[10,8:10] <- matrix[10,8:10] 
window15[9,7:9]   <- matrix[9,7:9] 
window15[8,6:8]   <- matrix[8,6:8] 
window15[7,5:7]   <- matrix[7,5:7]
window15[6,5:7]   <- matrix[6,5:7] 
window15[5,5:7]   <- matrix[5,5:7] 
window15[4,4:6]   <- matrix[4,4:6] 
window15[3,3:5]   <- matrix[3,3:5] 
window15[2,2:4]   <- matrix[2,2:4] 
window15[1,1:3]   <- matrix[1,1:3] 

#16
window16 <- matrix(FALSE, nrow = size, ncol = size)
window16[11,10:11] <- matrix[11,10:11] 
window16[10,9:11]  <- matrix[10,9:11] 
window16[9,8:10]   <- matrix[9,8:10] 
window16[8,7:9]    <- matrix[8,7:9] 
window16[7,6:8]    <- matrix[7,6:8] 
window16[6,5:7]    <- matrix[6,5:7] 
window16[5,4:6]    <- matrix[5,4:6] 
window16[4,3:5]    <- matrix[4,3:5] 
window16[3,2:4]    <- matrix[3,2:4] 
window16[2,1:3]    <- matrix[2,1:3] 
window16[1,1:2]    <- matrix[1,1:2] 

#17
window17 <- matrix(FALSE, nrow = size, ncol = size)
window17[11,11]    <- matrix[11,11] 
window17[10,10:11] <- matrix[10,10:11] 
window17[9,7:11]   <- matrix[9,7:11] 
window17[8,6:10]   <- matrix[8,6:10] 
window17[7,6:9]    <- matrix[7,6:9] 
window17[6,5:7]    <- matrix[6,5:7] 
window17[5,3:6]    <- matrix[5,3:6] 
window17[4,2:6]    <- matrix[4,2:6] 
window17[3,1:5]    <- matrix[3,1:5] 
window17[2,1:2]    <- matrix[2,1:2] 
window17[1,1]      <- matrix[1,1] 

#18
window18 <- matrix(FALSE, nrow = size, ncol = size)
window18[10,11]    <- matrix[10,11] 
window18[9,10:11]  <- matrix[9,10:11] 
window18[8,6:11]   <- matrix[8,6:11]
window18[7,6:10]   <- matrix[7,6:10] 
window18[6,5:7]    <- matrix[6,5:7] 
window18[5,2:6]    <- matrix[5,2:6] 
window18[4,1:6]    <- matrix[4,1:6] 
window18[3,1:2]    <- matrix[3,1:2] 
window18[2,1]      <- matrix[2,1] 

#19
# This is also not symmetric
window19 <- matrix(FALSE, nrow = size, ncol = size)
window19[9,11]   <- matrix[9,11]
window19[8,9:11] <- matrix[8,9:11] 
window19[7,6:11] <- matrix[7,6:11] # Another asymmetrical point
window19[6,2:10] <- matrix[6,2:10]
window19[5,1:6]  <- matrix[5,1:6]
window19[4,1:3]  <- matrix[4,1:3]
window19[3,1]    <- matrix[3,1] 

#20
window20 <- matrix(FALSE, nrow = size, ncol = size)
window20[8,9:11] <- matrix[8,9:11] 
window20[7,5:11] <- matrix[7,5:11] 
window20[6,1:11] <- matrix[6,1:11] 
window20[5,1:7]  <- matrix[5,1:7]
window20[4,1:3]  <- matrix[4,1:3] 

all_windows <- list(
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
    window13,
    window14,
    window15, 
    window16, 
    window17, 
    window18, 
    window19, 
    window20
)