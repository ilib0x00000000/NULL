#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-10 14:07:03 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

"""
共享资源池Semaphore：
			创建一个指定容量的资源池，所有线程去争抢资源池，抢到了，就先执行任务，未抢到的就处于等待状态
			如果多线程需要共享某个对象，需要新建一个类去维护该共享对象
"""

import time
import Queue
import threading


def download(spe):
	with spe:
		print threading.currentThread().getName(), time.ctime(), ' : downloading '
		time.sleep(10)
		print threading.currentThread().getName(), time.ctime(), ' : download over'

def no_share_object():
	# 设置资源池同时容纳的对象为5
	spe = threading.Semaphore(5)

	for i in xrange(10):
		t = threading.Thread(name=str(i), target=download, args=(spe,))
		t.start()



class Hall(object):
	'''假设有一家餐厅，共有num张桌子，但是客人数目大于桌子数目，就需要维护一个资源池
	'''
	def __init__(self, num):
		self.desks = Queue.Queue()
		for i in xrange(num):
			self.desks.put(i)
		self.lock = threading.Lock()

	def entry(self, guest):
		with self.lock:
			print guest, ' 号进入餐厅，就坐 ', self.desks.get(), ' 号桌'

	def dinner(self, guest):
		time.sleep(4)

	def exit(self, guest):
		with self.lock:
			print guest, ' 离开餐厅 桌空出来' 
			self.desks.put(guest)


def share_object(spe, guest, hall):
	'''这里一定要通过资源池维护各线程的等待顺序
	'''
	with spe:
		hall.entry(guest)
		hall.dinner(guest)
		hall.exit(guest)


if __name__ == '__main__':
	# no_share_object()
	spe = threading.Semaphore(5)
	hall = Hall(5)

	for i in xrange(10):
		t = threading.Thread(target=share_object, args=(spe, i, hall))
		t.start()


