#!/usr/bin/env  python
# -*- coding:utf-8 -*-

'''
Python多线程编程：
threading模块的几种常用对象：
	Thread:         表示一个执行线程的对象
	Lock:           锁原语对象
	RLock:          可重入锁对象，使单一线程可以再次获得已持有的锁
	Condition:      条件变量对象，使得一个线程可以等待另一个线程满足特定的条件
	Event:          条件变量的通用版本，任意数量的线程等待某个事件的发生，在该事件之后所有的线程将被激活
	Semaphore:      为线程间共享的有限资源提供了一个计数器，如果没有可用资源时会被阻塞
	BoundedSemaphore: 与Semaphore相似
	Timer:          与Thread相似，不过他要在运行前等待一段时间
	Barrier:        创建一个“屏障”，必须达到指定数量的线程后才可运行

Thread对象的属性和方法：
	name
	ident
	daemon

	start()
	run()
	join(timeout=None)
	is_alive()

threading模块的一些函数：
	active_count()            当前活动的Thread对象个数
	current_thread()          返回当前的Thread对象
	enumerate()               返回当前活动的Thread对象列表
	settrace(func)            为所有线程设置一个trace函数
	setprofile(func)          为所有线程设置一个profile函数
	stack_size(size=0)        返回新创建的线程的栈大小，或为后续创建的线程设定栈的大小为size

创建线程的第一种方式:
	传递一个函数给Thread类，且把该函数的参数一并传递过去
'''

import time
import threading


def thread_doing(waittime=5):
	'''主线程创建的子线程，默认在执行时睡眠5秒
	'''
	print '子线程-%s-开始运行了...' % threading.current_thread().name
	time.sleep(waittime)
	print '子线程-%s-运行结束了...' % threading.current_thread().name


if __name__ == '__main__':
	t = threading.Thread(name='child', target=thread_doing, args=(6, ))   # 创建子线程
	t.daemon = True   # 将子线程设置成守护进程
	t.start()         # 启动子线程

	time.sleep(1)     # 让主线程睡眠1秒

	print '子线程是否还运行着: %s' % t.is_alive()

	t.join()          # 等待子线程运行结束

