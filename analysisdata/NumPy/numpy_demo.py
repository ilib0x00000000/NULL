#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
NumPy处理数组形状的方法,所有的方法都是作用在数组对象上
	
	o ravel() 			拆解，将多维数组拆成一维数组
	o flatten()			拉直，与ravel类似(两者区别暂且不知)
	o reshape()			将n维数组变成m维数组
	o transpose()		转置
	o resize()			类似reshape，但是会改变数组本身
"""

from numpy import arange

def main():
	#初始化一个数组:a=[0,1,2,....23]
	a = arange(24)
	print a
	#output:  [ 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23]


	#将a变成2个三维数组，即每个数组里面有3个元素，每个元素是一个包含4个值的数组
	b = a.reshape(2,3,4)
	print b
	#output: [[[ 0  1  2  3]
  	#			[ 4  5  6  7]
  	#			[ 8  9 10 11]]
  	#
  	#			[[12 13 14 15]
  	#			[16 17 18 19]
  	#			[20 21 22 23]]]




	#将b拆解
	c = b.ravel()
	d = b.flatten()
	print c
	print d
	#output: [ 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23]
	#output: [ 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23]


	#转置
	e = c.reshape(6,4).transpose()
	print e
	#output: [[ 0  4  8 12 16 20]
	#			[ 1  5  9 13 17 21]
	#			[ 2  6 10 14 18 22]
	#			[ 3  7 11 15 19 23]]


	#将b变成二维数组
	b.resize((4,6))
	print b
	# #output: [[ 0  1  2  3  4  5]
 	#			[ 6  7  8  9 10 11]
	#			[12 13 14 15 16 17]
	#			[18 19 20 21 22 23]]





if __name__ == '__main__':
	main()