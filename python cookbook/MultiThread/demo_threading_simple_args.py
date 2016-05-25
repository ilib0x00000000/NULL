#!/usr/bin/env  python
# -*- coding:utf-8 -*-


import threading


def worker(num):
	print 'worker: %s' % num
	return

threads = []

for i in  range(5):
	t = threading.Thread(target=worker, args=(i,))
	threads.append(t)
	t.start()