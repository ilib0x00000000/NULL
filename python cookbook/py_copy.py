#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
可变对象:list, dict
不可变对象:str, tuple, num(少量)

深浅拷贝，既适用于序列，也适用于字典
深拷贝:拷贝所有对象，顶级对象及其嵌套对象（父级容器中还要包含容器）
浅拷贝:只拷贝顶级的对象（父级对象）
赋值操作:不同于深浅拷贝

id(): 显示其变量所指向的内存空间
"""

import copy

def test_shallowcopy():
	"""浅拷贝：拷贝顶级对象
	对列表浅拷贝时，其实是将列表中的指针赋值一份给另一个变量，所以通过变量修改列表中的值时，
	实际是修改列表中指针的指向，所以两个变量的值会变不同
	"""
	lists = ['a', 1, [0, 3, 'c']]
	scopy = copy.copy(lists)

	print 'lists: ', lists
	print 'scopy: ', scopy

	print '-'*30, '\nlists:'
	print id(lists)
	print [id(x) for x in lists]


	print '-'*30, '\nscopy:'
	print id(scopy)
	print [id(x) for x in scopy] 

	scopy[0] = 'test'
	print 'lists: ', lists
	print 'scopy: ', scopy

	print '-'*30, '\nlists:'
	print id(lists)
	print [id(x) for x in lists]


	print '-'*30, '\nscopy:'
	print id(scopy)
	print [id(x) for x in scopy] 



def test_deepcopy():
	"""深拷贝：只有容器对象中包含容器对象时，才能实现深拷贝
	深拷贝与浅拷贝不同的地方就是：浅拷贝时，容器中的容器对象指向不变，而深拷贝时，容器中的容器对象指向发生变化
	"""
	lists = ['a', 1, [0, 3, 'c']]
	dcopy = copy.deepcopy(lists)

	print 'lists: ', lists
	print 'dcopy: ', dcopy

	print '*'*30
	print id(lists[2])
	print id(dcopy[2])



def test_evalue():
	"""通过赋值操作拷贝
	新变量和原变量指向相同，只是拷贝了原变量的指向，所以修改新变量指向的元素就是修改原变量指向的元素
	"""
	a = [1, 2, 3]
	b = a

	print 'id(a) == id(b): ', id(a) == id(b)

	print '*'*30
	print 'a:', a
	print 'b:', b

	print '*'*30
	a[1] = 'test'
	print 'a:', a
	print 'b:', b





if __name__ == '__main__':
	test_deepcopy()
	test_shallowcopy()
	test_evalue()