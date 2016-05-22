# 数组
first <- matrix(nrow=3, ncol=2)

first[1,1] <- 46
first[2,1] <- 21
first[3,1] <- 50

first[1,2] <- 30
first[2,2] <- 25
first[3,2] <- 50

second <- matrix(nrow=3, ncol=2)

second[1,1] <- 46
second[2,1] <- 41
second[3,1] <- 50

second[1,2] <- 43
second[2,2] <- 35
second[3,2] <- 50


# 创建数组
r_array <- array(data=c(first, second), dim=c(3,2,2))
print(r_array)

# 这里创建数组的方法是将两个矩阵合成一个三维数组
# 同样可以将两个三维数组合成一个四维数组

# dim参数： 矩阵的行数，矩阵的列数，数组的层数


# 创建一个四维数组
array4d <- array(data=c(r_array, r_array), dim=c(2, 3, 2, 2))