# 列表：类似Python中的字典

# 创建列表
dict <- list(name="mac", salary=4535, union=T)
print(dict)


# 访问列表中组件的3中方法：

# 通过$索引
print(dict$name)
print(dict$salary)
print(dict$union)

# 通过关键字
print(dict[["name"]])
print(dict[["salary"]])
print(dict[["union"]])

# 通过下标
print(dict[[1]])
print(dict[[2]])
print(dict[[3]])

# 注意：通过双[]返回的是列表的元素，通过单[]返回的是列表的子列表
print(typeof(dict[[2]]))
print(typeof(dict[2]))


# 列表的增加与删除元素
# 增加
dict$newe <- 'abcd'
dict[[5]] <- 123
dict[6:8] <- c(TRUE, FALSE, TRUE)
print(dict)

# 删除
dict[[5]] <- NULL
print(dict)