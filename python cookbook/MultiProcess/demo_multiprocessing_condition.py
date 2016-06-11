#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-11 16:36:55 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

"""
同步操作----Condition对象
"""

import time
import multiprocessing

def stage_1(cond):
	name = multiprocessing.current_process().name
	print 'starting: ', name

	with cond:
		print '这里设置了一个同步信息量'
		time.sleep(2)
		print '首要步骤执行完毕'
		cond.notify_all()

def stage_2(cond):
	name = multiprocessing.current_process().name
	print 'starting: ', name

	with cond:
		print name, ' 等待中...'
		cond.wait()
		print name, ' 执行完毕，释放cond'

if __name__ == "__main__":
	condition = multiprocessing.Condition()

	s1 = multiprocessing.Process(name="s1", target=stage_1, args=(condition,))
	clients = [multiprocessing.Process(name='client'+str(i), target=stage_2, args=(condition,)) for i in xrange(1,3)]

	for p in clients:
		p.start()
		time.sleep(1)

	s1.start()

	s1.join()

	for p in clients:
		p.join()
