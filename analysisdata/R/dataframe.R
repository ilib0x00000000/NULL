# 数据框

# 创建数据框
names <- c('Jack', 'Jill')
ages <- c(12, 10)

d <- data.frame(names, ages, stringsAsFactors=FALSE)
print(d)

# d
#   names ages
# 1  Jack   10
# 2  Jill   20

# 获取数据框对象的元素

# 得到第一列元素
print(d$names)
print(d[[1]])	
print(d[,1])

# 得到第二列元素
print(d$ages)
print(d[[2]])	
print(d[,2])



Exam1 <- c(2.0, 3.3, 4.0, 2.3, 2.3, 3.3)
Exam2 <- c(3.3, 2.0, 4.0, 0.0, 1.0, 3.7)
Quiz <- c(4.0, 3.7, 4.0, 3.3, 3.3, 4.0)

examsquiz <- data.frame(Exam1, Exam2, Quiz, stringsAsFactors=FALSE)

# 提取子数据框
print(examsquiz[2:5,2])
print(class(examsquiz[2:5,2]))

print(examsquiz[2:5,2, drop=FALSE])
print(class(examsquiz[2:5,2, drop=FALSE]))


# 向数据框中添加行rbind()或者列cbind()
# 注意：这两个函数不改变原来的数据框，而是产生新的数据框
r_add <- list(2.8, 3.6, 3.4)
rbind(examsquiz, r_add)
print(examsquiz)

# 这样增加列有问题
# c_add <- list(3.3, 4.0, 2.3, 1.0, 3.7, 3.7)
# cbind(examsquiz, c_add)
# print(examsquiz)

examsquiz$test <- list(3.3, 4.0, 2.3, 1.0, 3.7, 3.7)
print(examsquiz)


# 合并数据框
kids <- c('Jack', 'Jill', 'Jillian', 'John')
states <- c('CA', 'MA', 'MA', 'HI')
d1 <- data.frame(kids, states, stringsAsFactors=FALSE)

ages <- c(10, 7, 10)
kids <- c('Jill', 'Lillian', 'Jack')
d2 <- data.frame(ages, kids, stringsAsFactors=FALSE)

d <- merge(d1, d2)		# merge会合并列名相同且值相同的数据，其余行抛弃
print(d)


# merge可以通过by.x和by.y指定不同名的列来合并数据框
pals <- c('Jack', 'Jill', 'Lillian')
d3 <- data.frame(ages, pals, stringsAsFactors=FALSE)

d <- merge(d1, d3, by.x='kids', by.y='pals')
print(d)

# 注意：如果在一个数据框内有重复的值，则该重复的值会与另一个数据框内的值匹配多次