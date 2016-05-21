# 矩阵：一种特殊的向量，包含两个特殊的属性，行数和列数
# 数组：数组可以是多维的

# 创建矩阵：
matrix(vector, nrow, ncol, byrow=FALSE, dimnames=NULL)

x <- matrix(c(1:10), nrow=2, byrow=TRUE)
y <- matrix(c(1:6), ncol = 3)


# 创建一个空矩阵，通过下标赋值(注意：下标的取值方式)
matrix(nrow=m, ncol=n)

z <- matrix(nrow=3, ncol=2)
z[1,1] <- 2
z[2,1] <- 5
z[3,1] <- 8

z[1,2] <- 3
z[2,2] <- 6
z[3,2] <- 9

# 矩阵运算
# 矩阵线性相乘
a = matrix(c(1:4), nrow=2)
print(z %*% a)

# 矩阵乘以常数
print(z*3)



# 矩阵索引：
# 取出矩阵z的第二列
print(z[,2])

# 取出矩阵第二和第三行
print(z[2:3,])

# 矩阵的索引是通过在[]中以,分隔行列取值的

# 对子矩阵赋值
z[2:3,] <- matrix(c(100, 200, 300, 400), nrow=2)

# 可以通过负数排除掉某些元素
print(z[,-1])


# 矩阵元素筛选
x <- matrix(nrow=3, ncol=2)

x[1,1] <- 1
x[2,1] <- 2
x[3,1] <- 3

x[1,2] <- 2
x[2,2] <- 3
x[3,2] <- 4

# 选出第二列大于等于3的行
print(x[x[, 2]>=3, ])




# 对矩阵调用apply函数
# apply(m, dimcode, f, fargs)
# m:矩阵
# dimcode：1代表对每一行应用函数，2代表对每一列应用函数
# f：应用在行或列上的函数
# fargs：函数的可选参数集
x <- matrix(nrow=3, ncol=2)

x[1, 1] <- 1
x[2, 1] <- 2
x[3, 1] <- 3

x[1, 2] <- 4
x[2, 2] <- 5
x[3, 2] <- 6

print(apply(x, 2, mean))

div48 <- function(x) 
{
	return(x/c(4, 8))
}

print(apply(x, 1, div48))

# 带参数的回调函数
tavg <- function(x, n) 
{
	avg <- sum(x[1:n])/n
	if(avg>0.5)
		return(1)
	else
		return(0)
}

m = matrix(nrow=4, ncol=5)
m[,] = 1

m[1,2] <- m[1,5] <- 0
m[2,5] <- 0
m[3,2:3] <- 0
m[4,1] <- m[4,5] <- 0

print(apply(m, 1, tavg, 3))
print(apply(m, 1, tavg, 2))