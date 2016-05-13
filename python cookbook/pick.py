#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
数据持久存储：
	串行化：将一个任意的Python对象转换成一系列字节。
	cPickle(pickle)模块：
		o dumps(obj): 将一个Python对象串行化，返回一个pickle对象
		o loads(pickle_obj): 加载一个pickle对象，返回对象的原始状态
		o dump(obj, stream): 将对象串行化后，写入流
		o load(stream): 从流中加载pickle对象，返回对象的原始状态
"""

import os
try:
	import cPickle as pickle
except:
	import pickle


data = {'a':'A', 'b':1, 'c':2.0}

# 将对象串行化后，会产生一个pickle格式的对象
pick_data = pickle.dumps(data)
print pick_data

data2 = pickle.loads(pick_data)
print data2

print 'data2 is data: ', data2 is data
print 'data2 == data: ', data2 == data

# *************************************************************************************

class SimpleObject(object):
	def __init__(self, name):
		self.name = name
		self.reverse_name = name[::-1]

	def __str__(self):
		return '<object of %s>' % self.__class__.__name__

	repr = __str__


obj_list = []
obj_list.append(SimpleObject('flied1'))
obj_list.append(SimpleObject('flied2'))
obj_list.append(SimpleObject('flied3'))


with open('temp.txt', 'wb') as f:
	for obj in obj_list:
		print obj.name, obj.reverse_name
		pickle.dump(obj, f)
		f.flush() 				# 将一个对象串行化后，写入流，需要刷新流的输出


load_obj = []


# 当从流中加载pickle对象时，需要保证该对象反串行化后的类定义在读取pickle的进程所在的命名空间
with open('temp.txt', 'rb') as f:
	while True:
		try:
			load_obj.append(pickle.load(f))
		except EOFError:
			break

for obj in load_obj:
	print obj.name, obj.reverse_name

os.remove('temp.txt')

