# R语言中的数据结构：
# 	向量
# 	列表
# 	数组
# 	矩阵

# R语言中没有标量，所有的数值/字符串/布尔/复数都是一元向量

# 查看变量的模式和类型：
# 	mode(var_d)
# 	typeof(var_d)


# R语言中的向量是连续存储的，不能插入或删除元素

# 建立一个空向量
v <- vector(length=10)
v[1] <- 10.5
v[2] <- 24



# 建立带初始值的向量
a <- c(1, 2, 3, 4, 5)
b <- c(10:14)

print(a)
print(b)

c <- c(a, b)
print(c)


# 获取向量的长度:length(v)
find4 <- function(x)
{
	# 参数x是向量
	for (i in 1:length(x)) 
	{
		if(x[i] == 4)
			break
	}

	return(i)
}

index <- find4(c)
print(index)


# 循环补齐
# 当两个向量使用运算符时，要求两个向量有相同的长度，否则R会自动循环补齐较短的向量，即重复向量的元素，直至两个向量长度相同
v1 <- c(1, 2, 3, 4)
v2 <- c(10, 9, 8, 7, 6, 5, 4, 3)
vn <- v1 + v2
print(vn)


# 向量运算 + - × / %%(取余)
# 向量之间的运算，实际是对应元素之间的运算
x <- c(1, 2, 4)
print(x + c(5, 0, -1))
print(x - c(5, 0, -1))
print(x * c(5, 0, -1))
print(x / c(5, 0, -1))
print(x %% c(5, 0, -1))


# 向量索引
# R语言中的向量的索引是从1开始的，且在R语言中向量的切片是闭区间
v <- c(1:12)
print(v)

index <- 3:8

if(is.vector(index))
{
	print(v[index])
}


# 负数下标代表把相应元素剔除
z <- c(5, 12, 13)
print(z[-1])
print(z[-1:-2])



# 用：创建向量，：的优先级高于负号
a <- 1:10
print(a)
print(is.vector(a))



# 用seq创建向量，等差数列
b1 <- seq(10, 100, by=10)		# by指定步长
print(b1)
print(is.vector(b1))

b2 <- seq(10, 100, length = 3)	# length指定向量长度
print(b2)
print(is.vector(b2))



# 使用rep重复向量常数
s <- rep(3, 5)
print(s)
is.vector(s)


# any/all(exp)	判断对应向量，是否存在至少一个/全部元素对条件成立，如果成立返回TRUE，否则返回FALSE
z <- c(1:20)

# all
r1 = all(z%%2 == 0)
print(r1)

# any
r2 = any(z%%2 == 0)
print(r2)

