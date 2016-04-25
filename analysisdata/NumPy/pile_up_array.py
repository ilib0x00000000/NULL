#!/usr/bin/env  python
# -*- coding:utf-8 -*-


"""
NumPy中堆叠数组的方法：注 下面的方法的参数都是元组
	o vstack()				垂直叠加			
	o dstack()				深度叠加			
	o hstack()				水平叠加			
	o column_stack()		列式堆叠			
	o row_stack()			行式堆叠			
	o concatenate()			垂直或水平叠加，参数是一个元组和标记，如果标记axis=0,则为水平叠加，如果axis=1，则为垂直叠加
"""

from numpy import arange,hstack,vstack,dstack,column_stack,row_stack


def main():
	# 初始化一个数组
	a = arange(9).reshape(3,3)
	print a
	# [[0 1 2]
	#  [3 4 5]
	#  [6 7 8]]


	b = a * 2
	print b
	# [[ 0  2  4]
	#  [ 6  8 10]
	#  [12 14 16]]


	# 水平叠加
	hc = hstack((a,b))
	print hc
	# [[ 0  1  2  0  2  4]
	#  [ 3  4  5  6  8 10]
	#  [ 6  7  8 12 14 16]]


	# 垂直叠加
	vc = vstack((a,b))
	print vc
	# [[ 0  1  2]
	#  [ 3  4  5]
	#  [ 6  7  8]
	#  [ 0  2  4]
	#  [ 6  8 10]
	#  [12 14 16]]


	#深度叠加:沿第三个坐标轴叠加数组
	dc = dstack((a,b))
	print dc
	# [ [ [ 0  0],[ 1  2],[ 2  4] ]

	#  [ [ 3  6],[ 4  8],[ 5 10] ]

	#  [ [ 6 12],[ 7 14],[ 8 16] ]  ]


	# 列式堆叠：就是将两个数组的各个元素合并成一个数组,仅仅是将第一个元素合并成数组，元素是什么类型都不影响
	cc = column_stack((a,b))
	print cc
	# [[ 0  1  2  0  2  4]
	#  [ 3  4  5  6  8 10]
	#  [ 6  7  8 12 14 16]]

	# 行式堆叠
	rc = row_stack((a,b))
	print rc
	# [[ 0  1  2]
	#  [ 3  4  5]
	#  [ 6  7  8]
	#  [ 0  2  4]
	#  [ 6  8 10]
	#  [12 14 16]]


if __name__ == '__main__':
	main()