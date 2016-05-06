#!/usr/bin/env  python
# -*- coding:utf-8 -*-


"""
itertools模块:
	chain:	将多个迭代器合并成一个迭代器
	izip:	将两个长度相同的迭代器合并成一个包含元组的迭代器,如果两个迭代器的长度不一样，就取最短的迭代器
	islice: 接收一个迭代器为参数，同时接收类似切片的3个参数，表示对迭代器切片
	tee:	返回迭代器参数的多个副本，默认两个，新创建的迭代器共享输入迭代器，当迭代原迭代器到某个位置时，新迭代器就保存该状态
	imap: 	参数是一个函数和迭代器，返回函数作用于迭代器的元素后的结果
	starmap:参数是一个函数和迭代器，类似与imap，但是并不是由多个迭代器构建一个tuple，而是将一个迭代器中的元素作为映射函数的参数
"""


import itertools



def print_iter(itertor):
	for item in itertor:
		print item,
	print 

# 将两个迭代器合并成一个新的迭代器
num = itertools.chain(xrange(5), xrange(5,10))
print_iter(num)

# 将两个迭代器合并成一个包含元组的迭代器
tpl = itertools.izip(xrange(1,10), ['a', 'b', 'c', 'd'])
print_iter(tpl)

# 对迭代器切片
res = itertools.islice(itertools.count(), 5, 50, 5)
print_iter(res)

# 创建迭代器的副本,如果原迭代器已经遍历了一部分，则迭代器的副本会接着遍历的位置，继续遍历
origin = iter(['a', 'b', 'c', 'd', 'e'])
cp1,cp2 = itertools.tee(origin)
for c in origin:
	if c == 'c':
		break

print_iter(cp1)


# 定义一个函数作用在迭代器元素上，并返回一个新的迭代器
res = itertools.imap(lambda x:''.join([x,'......']), cp2)
print_iter(res)


"""
	count:  函数返回一个迭代器，可以无限的生成连续整数，默认参数为0，即从0开始
	cycle:  函数返回一个迭代器，它会无限的循环给定的参数的内容，由于要记住迭代器的全部内容，如果迭代器很长会占用很多内存
	repeat: 函数接收一个值，和一个可选的参数time重复次数，返回一个迭代器
	dropwhile: 函数参数是一个函数和迭代器，返回该迭代器中条件第一次为False及之后的元素
	takewhile: 函数参数是一个函数和迭代器，返回该迭代器中条件第一次为false之前的全部元素
	ifilter: 返回一个迭代器，参数是一个函数和迭代器，返回函数作用在迭代器为True的元素
	ifilterfalse: 返回一个迭代器，与ifilter相反
"""

# 生成一个整数迭代器
num = itertools.count(10)
print_iter(itertools.islice(num,10))


# 循环一个迭代器
rp = iter(['a', 'b', 'c'])
res = itertools.izip(itertools.cycle(rp), xrange(10))
print_iter(res)


# 重复一个值指定次数
res = itertools.repeat('a', 10)
print_iter(res)



# 过滤，返回一个迭代器，会生成输入迭代器中条件第一次为False及其之后的元素
res = itertools.dropwhile(lambda x: isinstance(x, str), ['a','b',1,2,'c',5,3])
print_iter(res)


# 过滤，返回一个迭代器，与dropwhile函数作用恰好相反
res = itertools.takewhile(lambda x: isinstance(x, str), ['a','b',1,2,'c',5,3])
print_iter(res)


# 过滤，返回一个迭代器，元素为输入迭代器中条件为True的元素
res = itertools.ifilter(lambda x : x%2, xrange(10))
print_iter(res)


# 过滤，返回一个迭代器，元素为输入迭代器中条件为False的元素
res = itertools.ifilterfalse(lambda x : x%2, xrange(10))
print_iter(res)



"""
groupby: 参数是迭代器和函数，根据函数的返回值将迭代器的元素分组，返回的迭代器的元素是(标签，迭代器)，
标签是函数的返回值内容
"""
things = [('2009-09-02', 11),
          ('2009-09-02', 3),
          ('2009-09-03', 10),
          ('2009-09-03', 4),
          ('2009-09-03', 22),
          ('2009-09-06', 33)]

import datetime

def str2time(s):
	"""将字符串格式的时间转换成时间对象
	"""
	return datetime.datetime.strptime(s, '%Y-%m-%d')

for tag,itor in itertools.groupby(iter(things) ,lambda s: datetime.datetime.strptime(s[0],'%Y-%m-%d')):
	print 'tag:%s' % tag,
	print list(itor)
print 