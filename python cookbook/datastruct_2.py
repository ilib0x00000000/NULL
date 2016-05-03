#!/usr/bin/env  python
# -*- coding:utf-8 -*-



"""
常用的数据结构
"""


import heapq
import random


def show_heap(heap):
	"""堆是一个树形数据结构，保存父节点与子节点的关系
		o 最小堆：父节点的值小于等于子节点
		o 最大堆：父节点的值大于等于子节点

		Python的heapq库实现的是最小堆
	"""

	i = 0
	k = 0
	s = 1
	length = len(heap)

	while True:
		if i+s < length:
			print heap[i:s+i]
			k += 1
			i += s
			s *= 2
		else:
			print heap[i:]
			break



def create_heap():
	"""创建堆的2种方式：
	1.heapq.heappush():创建一个空列表，将列表作为堆，直接向堆中添加元素 
	2.heapq.heapify()：直接将含有数据的列表转化成堆
	"""
	
	heap1 = []

	for x in xrange(10):
		heapq.heappush(heap1, random.randint(0,20))
	print heap1

	heap2 = [random.randint(0,20) for x in xrange(14)]
	print 'before heapify: ', heap2
	heapq.heapify(heap2)
	print 'finished heapify: ',heap2

	return heap2


def heap_func(heap):
	"""堆中常用的方法：
		o heappop(heap):					删除堆中最小的元素	
		o heapreplace(heap, value):			用value替换掉堆中最小值
		o nlargest(n, heap):				返回堆中最大的n个值
		o nsmallest(n, heap):				返回堆中最小的n个值
	"""
	print 'initial: ',heap
	
	heapq.heappop(heap)
	print 'pop: ',heap

	heapq.heapreplace(heap, random.randint(0,100))
	print 'replace: ',heap

	print 'largest 3: ', heapq.nlargest(3, heap)
	print 'smallest 3: ', heapq.nsmallest(3, heap)
	return 0


if __name__ == '__main__':
	
	heap = create_heap()
	show_heap(heap)
	heap_func(heap)