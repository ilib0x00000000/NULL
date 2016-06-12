#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-12 20:32:11 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

"""
创建进程池：
		1. pool = multiprocessing.Pool()					创建进程池，需要指定进程的数目
		2. ouputs = pool.map(函数,inputs)					这里的map与普通的map函数一样，只是并行运行
		3. pool.close()										当进程没有进程再加入时，关闭进程池
		4. pool.join()										等待进程池中的进程结束
"""

import time
import multiprocessing

def do_calculation(data):
	return data*2

def start_process():
	print 'starting: ', multiprocessing.current_process().name

if __name__ == '__main__':
	inputs = list(xrange(10))
	print 'Input: ', inputs

	builtin_outputs = map(do_calculation, inputs)

	print 'Build-in: ', builtin_outputs

	pool_size = multiprocessing.cpu_count() * 2

	pool = multiprocessing.Pool(processes = pool_size, initializer=start_process)

	pool_outputs = pool.map(do_calculation, inputs)

	pool.close()
	pool.join()

	print 'Pool: ', pool_outputs