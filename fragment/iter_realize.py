#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
Python的迭代协议要求__iter__()返回一个特殊的迭代器对象，该对象必须实现__next__()方法，
并使用StopIteration异常来通知迭代的完成
迭代器：就是实现__iter__()方法的对象
注：开发环境
			os : ubuntu14.04
			py version : 3.4.3 
"""

"""
	@author : ilib0x00000000
	@email  : ilib0x00000000@gmail.com
	@version: 1.0
	@date	: 2016/04/10
	@project: Python迭代器的实现(yield实现版)
"""

class Node(object):
	def __init__(self, value):
		self._value = value
		self._children = []

	def __str__(self):
		return "Node({value})".format(value=self._value)

	__repr__ = __str__

	def add_child(self,node):
		self._children.append(node)

	def __iter__(self):
		return iter(self._children)

	def depth_first(self):
		"""
			这里实际是一个递归调用，这里先返回一个对象self（Node0），而Node0又是一个迭代器，
			迭代Node0时，实际得到的是Node0中的其他对象（Node1,Node2），然后继续调用该对象的
			depth_first方法，进入递归
			递归树：
					 Node(0)
			   		/	    \
				Node(1)	   Node(2)
				/    \       |
			Node(3) Node(4) Node(5)
		"""
		yield self
		for c in self:						# self本身就是一个迭代器
			yield from c.depth_first()		# yield from 是Python3的特性

if __name__ == '__main__':
	root = Node(0)

	child1 = Node(1)
	child2 = Node(2)

	root.add_child(child1)
	root.add_child(child2)

	child1.add_child(Node(3))
	child1.add_child(Node(4))
	child2.add_child(Node(5))

	for ch in root.depth_first():
		print(ch)

	# output
	# Node(0) , Node(1), Node(3), Node(4), Node(2), Node(5)
