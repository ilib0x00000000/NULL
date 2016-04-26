#!/usr/bin/env  python
# -*- coding:utf-8 -*-


"""
使用NumPy数组中的方法加载CSV文件，并对文件做简单的统计计算
"""

import numpy
from scipy.stats import scoreatpercentile


def main():
	"""从文件中加载数据
	loadtxt(fname, dtype=<type 'float'>, comments='#', delimiter=None, converters=None,
			skiprows=0, usecols=None, unpack=False, ndmin=0)

	Paramenters:
		o fname: 文件名
		o dtype: 返回的数组中的数值的数据类型，默认float
		o comments: 文件中以该参数值开始的行都是注释，默认是'#',该注释行会被忽视
		o delimiter: 以说明符号问分隔符
		o converters: dict或者函数，用来将列数据转换成指定的数据
		o skiprows: int 跳过指定的行数
		o usecols: 元组， 读取哪些列的信息，默认从0开始
		o unpack: 是否转置
		o ndmin: 返回的数组的最小尺寸，合法值：0(默认),1,2

	Return:
		object: ndarray
	"""
	# 读取文件，得到一个二维数组，每个数组元素都是一个数组，包含指定的列的元素
	data_obj = numpy.loadtxt('MDR-TB_burden_estimates_2016-04-26.csv', delimiter=',', usecols=(1,),
						comments='#', skiprows=1, unpack=True)

	# 得到数组最大值
	print data_obj.max()

	# 得到数组的最小值
	print data_obj.min()

	# 得到数组的平均值
	print data_obj.mean()

	# 得到数组的标准差
	print data_obj.std()

	print numpy.max(data_obj)
	print numpy.min(data_obj)
	print numpy.mean(data_obj)
	print numpy.std(data_obj)

	# 得到数组的中位数
	print numpy.median(data_obj)


if __name__ == '__main__':
	main()