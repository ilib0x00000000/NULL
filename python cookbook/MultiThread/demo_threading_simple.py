#!/usr/bin/env  python
# -*- coding:utf-8 -*-

import threading

def worker():
	print 'worker'
	return

threads = []

for i in  range(5):
	t = threading.Thread(target=worker)
	threads.append(t)
	t.start()
