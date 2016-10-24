#!/usr/bin/env  python
# -*- coding:utf-8 -*-


'''
Python多线程编程：
threading模块的几种常用对象：
	Thread              表示一个执行线程的对象
	Lock                锁原语对象
	RLock               可重入锁对象，使单一线程可以再次获得已持有的锁
	Condition           条件变量对象，使得一个线程可以等待另一个线程满足特定的条件
	Event               条件变量的通用版本，任意数量的线程等待某个事件的发生，在该事件之后所有的线程将被激活
	Semaphore           为线程间共享的有限资源提供了一个计数器，如果没有可用资源时会被阻塞
	BoundedSemaphore    与Semaphore相似
	Timer               与Thread相似，不过他要早运行前等待一段时间
	Barrier             创建一个屏障，必须达到指定数量的线程后才可运行

threading模块的一些函数：
	active_count()      返回当前活动的Thread对象个数
	current_thread()    返回当前的Thread对象
	enumerate()         返回当前所有活动的Thread对象列表
	settrace(func)      为所有线程设置一个trace函数
	setprofile(func)    为所有线程设置一个profile函数
	stack_size(size=0)  返回新创建的线程的栈的大小，或为后续创建的线程设定栈的大小为size

Thread对象的属性和方法:
	name
	ident
	daemon

	start()
	run()
	join(timeout=None)
	is_alive()

创建线程的第二种方式：
	继承Thread类
	重写run方法
'''

import time
import Queue
import threading


class DefinedThreadRead(threading.Thread):
	'''继承Thread
	初始化该实例时，传递一个线程安全的队列，从队列中读取一句话
	'''
	def __init__(self, queue, name=''):
		threading.Thread.__init__(self)    # 调用父类的构造方法
		self.name  = name
		self.queue = queue

	def run(self):
		while not self.queue.empty():
			line = self.queue.get()
			print line
			# run方法的返回值会被忽略



class DefinedThreadWrite(threading.Thread):
	'''继承Thread
	初始化该实例时，传递一个线程安全的队列，向该队列中写入一句话
	'''
	def __init__(self, queue, name=''):
		threading.Thread.__init__(self)
		self.name  = name
		self.queue = queue
		self.i = 1

	def run(self):
		'''向队列写入一句话
		'''
		while True:
			self.queue.put('write line %d' % self.i)
			self.i += 1



if __name__ == '__main__':
	queue = Queue.Queue()       # 创建一个线程安全的队列

	read = DefinedThreadRead(queue)
	write = DefinedThreadWrite(queue)
	
	# 将子线程设置为守护进程，主线程退出，子线程就结束
	read.daemon  = True
	write.daemon = True

	write.start()
	read.start()

	time.sleep(2)       # 主线程睡眠2s让子线程运行