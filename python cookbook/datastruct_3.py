#!/usr/bin/env  python
# -*- coding:utf-8 -*-


"""
队列(Queue)：
	先进先出：Queue.Queue
	先进后出：Queue.LifoQueue
	优先级队列：Queue.PriorityQueue
"""

import Queue
import threading


def queue_test():
	"""创建一个FIFO队列，队列是线程安全的
		o put()	:	向队列中添加一个对象
		o get()	:	返回队列中的一个对象并删除
		o empty()	判断队列是否为空
	"""
	queue = Queue.Queue()

	for x in xrange(1,5):
		queue.put(x)
	print queue

	while not queue.empty():
		print queue.get()



def lifoqueue_test():
	"""创建一个LIFO队列，队列是线程安全的
		o put()	:	向队列中添加一个对象
		o get()	:	返回队列中的一个对象并删除
		o empty()	判断队列是否为空
	"""
	lifoqueue = Queue.LifoQueue()

	for x in xrange(1,6):
		lifoqueue.put(x)
	print lifoqueue

	while not lifoqueue.empty():
		print lifoqueue.get()



class Job(object):
	def __init__(self, priority, description):
		self.priority = priority
		self.description = description
		print 'New job: ', description

	def __cmp__(self, other):
		return cmp(self.priority, other.priority)


def process_job(q):
	while True:
		next_job = q.get()
		print 'Processing job: ', next_job.description
		q.task_done()


def priorityqueue_test():
	"""优先级队列：优先级队列中的对象要实现__cmp__()方法
		较FIFO和LIFO队列新增：
				task_done()
				join()
	"""
	q = Queue.PriorityQueue()

	q.put(Job(3, 'Mid-level job'))
	q.put(Job(10, 'Height-level job'))
	q.put(Job(1, 'Lower-level job'))

	workers = [
		threading.Thread(target=process_job, args=(q,)),
		threading.Thread(target=process_job, args=(q,))
	]

	for w in workers:
		w.setDaemon(True)
		w.start()

	q.join()

if __name__ == '__main__':
	queue_test()
	lifoqueue_test()
	priorityqueue_test()