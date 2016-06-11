#!/usr/bin/env python
# -*- coding: utf-8 -*-

#*************************************************************************************
# @Date    : 2016-06-11 10:18:34 
# @Author  : ilib0x00000000
# @Email   : ilib0x00000000@gmail.com
# @github  : https://github.com/ilib0x00000000
# @Version : 0.1
#*************************************************************************************

import time
import multiprocessing

class Consunmer(multiprocessing.Process):
	def __init__(self, task_queue, result_queue):
		super(self.__class__, self).__init__()
		self.task_queue = task_queue
		self.result_queue = result_queue

	def run(self):
		proc_name = self.name

		while True:
			next_task = self.task_queue.get()
			if next_task is None:
				print proc_name, ' exiting....'
				self.task_queue.task_done()
				break
			print '%s : %s' % (proc_name, next_task)
			answer = next_task()
			self.task_queue.task_done()
			self.result_queue.put(answer)

class Task(object):
	def __init__(self, a, b):
		self.a = a
		self.b = b

	def __call__(self):
		time.sleep(1)
		return '%s * %s = %s' % (self.a, self.b, self.a * self.b)

	def __str__(self):
		return '%s * %s' % (self.a, self.b)

if __name__ == '__main__':
	tasks = multiprocessing.JoinableQueue()
	results = multiprocessing.Queue()

	num_consumers = multiprocessing.cpu_count() * 2
	consumers = [Consunmer(tasks, results) for i in xrange(num_consumers)]

	for w in consumers:
		w.start()

	for i in xrange(10):
		tasks.put(Task(i,i))

	for i in xrange(num_consumers):
		tasks.put(None)

	tasks.join()

	num_jobs = 10

	while num_jobs:
		result = results.get()
		print 'result: ',result
		num_jobs -= 1
