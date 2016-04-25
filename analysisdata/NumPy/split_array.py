#!/usr/bin/env  python
# -*- coding:utf-8 -*-


"""
NumPy中拆分数组的方法：
	o hsplit()			横向拆分
	o vsplit()			纵向拆分
	o dsplit()			深向拆分
	o split()			横向拆分或纵向拆分，通过参数axis指定
"""

from numpy import arange,hsplit,vsplit,dsplit,split


def main():
	# 构造一个数组
	a = arange(9).reshape(3,3)
	print a
	# [[0 1 2]
	#  [3 4 5]
	#  [6 7 8]]


	# 横向拆分
	hs = hsplit(a,3)
	print hs
	# [
	# 	array([[0],[3],[6]]), 
	# 	array([[1],[4],[7]]), 
	# 	array([[2], [5], [8]])
	# ]


	# 纵向拆分
	vs = vsplit(a,3)
	print vs
	# [
	# 	array([[0, 1, 2]]), 
	# 	array([[3, 4, 5]]), 
	# 	array([[6, 7, 8]])
	# ]


	# 深向拆分,数组需要为三维数组
	b = arange(27).reshape(3,3,3)
	ds = dsplit(b,3)
	print ds
	# [
	# 	array([[[ 0],[ 3],[ 6]],   [[ 9],[12],[15]],   [[18],[21],[24]]]), 
	# 	array([[[ 1],[ 4],[ 7]],   [[10],[13],[16]],   [[19],[22],[25]]]), 
	# 	array([[[ 2],[ 5],[ 8]],   [[11],[14],[17]],   [[20],[23],[26]]])
	# ]



if __name__ == '__main__':
	main()