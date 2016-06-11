#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-11 16:26:59 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

import time
import multiprocessing

def worker_with(lock):
	with lock:
		print '这是输出的开始'
		time.sleep(3)
		print '这是输出的结束'

def worker_no_with(lock):
	lock.acquire()

	try:
		print '已获得锁，为所欲为的执行代码'
		time.sleep(2)
		print '执行结束，释放锁'
	finally:
		lock.release()

if __name__ == '__main__':
	lock = multiprocessing.Lock()
	p1 = multiprocessing.Process(target=worker_with, args=(lock,))
	p2 = multiprocessing.Process(target=worker_no_with, args=(lock,))

	p1.start()
	p2.start()

	p1.join()
	p2.join()
