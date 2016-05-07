#!/usr/bin/env  python
# -*- coding:utf-8 -*-


"""
operator模块:
	序列操作：
			concat(iter1, iter2): 将两个序列合并成一个序列
			repeat(iter, time):	返回指定次数的序列
			contains(iter, item): 判断序列是否包含指定元素
			countOf(iter, item): 返回指定元素在序列中出现的次数
			indexOf(iter, item): 返回指定元素在序列中出现的下标
			
			getitem(iter, index): 返回序列中指定下标处的元素
			getslice(iter, start, end, step): 返回序列中指定的子序列
			setitem(iter, index, value): 将序列中指定的下标赋值
			setslice(iter, start, end, sub_iter): 给序列的子序列赋新值
			delitem(iter, index): 删除序列中指定下标处的元素
			delslice(iter, start, end): 删除序列中指定位置处的子序列
	原地操作：
			iconcat(iter1, iter2): 将iter2添加到iter1的末尾
	获取元素或属性：
			attrgetter:
			itemgetter:
	判断对象类型：
			isMappingType:
			isNumberType:
			isSequenceType:
"""

import operator

a = [1, 2, 3]
b = ['a', 'b', 'c']

print operator.concat(a,b)
print operator.repeat(b, 3)
print operator.contains(a, 2)
print operator.contains(b, 'hhhhhh')
print operator.countOf(operator.repeat(b, 4), 'a')
print operator.countOf(a, 8)
print operator.indexOf(a, 2)
# output
# [1, 2, 3, 'a', 'b', 'c']
# ['a', 'b', 'c', 'a', 'b', 'c', 'a', 'b', 'c']
# True
# False
# 4
# 0
# 1

c = [1, 'a', None, 10.01, {'key':'value'}]


# 通过下标操作序列
print operator.getitem(c, 4)
print operator.getslice(c, 1, 4)

operator.setitem(c, 2, 9999)
print c
operator.setslice(c, 3,-1, [10,20,30,40,50])
print c

operator.delitem(c, 0)
print c
operator.delslice(c, 2, 7)
print c
# output
# {'key': 'value'}
# ['a', None, 10.01]
# [1, 'a', 9999, 10.01, {'key': 'value'}]
# [1, 'a', 9999, 10, 20, 30, 40, 50, {'key': 'value'}]
# ['a', 9999, 10, 20, 30, 40, 50, {'key': 'value'}]
# ['a', 9999, {'key': 'value'}]


"""
获取对象元素或属性方法：
	1.创建一个回调函数，
	2.将对象传入回调函数
"""

class Host(object):
	"""创建一个带显性属性的类
	"""
	def __init__(self, name):
		super(self.__class__, self).__init__()
		self.name = name

	def __str__(self):
		return '<object of %s>' % self.__class__.__name__


h = Host('test')
hook = operator.attrgetter('name')
print hook(h)


dicts = [
	{'key':1},
	{'key':2},
	{'key':3},
	{'key':4},
	{'key':5}
]

hook = operator.itemgetter('key')
for item in dicts:
	print hook(item),
print 
# output
# test
# 1 2 3 4 5


"""
operator模块还包含一些函数来测试映射，数字和序列类型的API兼容性
"""
class NoType(object):
	"""什么特性都没去实现的类
	"""

class MultiType(object):
	"""实现部分特性的类
	"""
	def __len__(self):
		return 0

	def __getitem__(self, key):
		return 'mapping'

	def __int__(self):
		return 0

n = NoType()
m = MultiType()

# 检测实例是否实现了哪些功能
print 'NoType: '
print '\t', operator.isNumberType(n)
print '\t', operator.isMappingType(n)
print '\t', operator.isSequenceType(n)


print 'MultiType: '
print '\t', operator.isNumberType(m)
print '\t', operator.isMappingType(m)
print '\t', operator.isSequenceType(m)
# output:
# NoType: 
# 	False
# 	False
# 	False
# MultiType: 
# 	True
# 	True
# 	True
