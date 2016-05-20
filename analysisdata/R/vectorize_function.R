# 向量化运算:向量之间的运算实际是向量的每个元素之间的运算
# R语言中 + - * / > < == 都是向量化运算符


# 向量输入，向量输出
u <- c(5, 6, 8)
v <- c(1, 7, 4)

print(u>v)


# 向量输入，矩阵输出

vtom <- function(x) 
{
	return(c(x, x*10))
}

v = c(1, 2, 3, 4)
print(matrix(vtom(v), nrow=2))


# NA:缺失值
# 在R中，许多函数无法处理带NA的向量，需要指定参数na.rm=T忽略NA
x <- c(88, 16, NA, 64)
mean(x)
mean(x, na.rm=T)


# NULL:不存在的值
x <- c(88, 16, NULL, 64)
mean(x)


getodd <- function(x) 
{
	r = NULL

	for (i in x) 
	{
		if(i %% 2 ==0)
			r = c(r, i)
	}
	return(r)
}

x = 1:10
print(getodd(x))


# 筛选，无法处理NA
z <- c(13, 1, 6, 21)
print(z[z>10])
print(z[c(FALSE, FALSE, TRUE, TRUE)])

#subset筛选，自动忽略NA
t <- c(13, 1, NA, 6, 21)
subset(t, t>10)

# 条件索引
t <- c(13, 1, NA, 6, 21)
print(which(t%%2==0))
print(which(t>8))

#ifelse(v1, v2, v3)如果v1中的元素为TRUE，则返回v2中相应位置的元素，否则返回v3中相应位置的元素
ifelse(c(TRUE, FALSE, TRUE, FALSE, TRUE, FALSE), 1, 0)


# 判断向量相等
x <- 1:3
y <- c(1, 2, 3)
z <- c(1, 3, 4)

print(x == y)
print(x == z)

# 因为==是向量化的运算符
# 所以返回的bool向量
# 判断向量对象是否相同应该使用identical函数
print(identical(x, y))
print(typeof(x))
print(typeof(y))

n <- x
print(identical(x, n))


# 给向量命名
x <- c(1, 2, 4)
print(names(x))

names <- c('name', 'sex', 'age')
print(names(x))

print(x)

print(x['name'])
print(x['sex'])
print(x['age'])