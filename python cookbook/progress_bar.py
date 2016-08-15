# /usr/bin/env  python
# -*- coding:utf-8 -*-


'''
显示进度条
	1.直接使用stdout，显示时需要flush
	2.使用外部库tqdm，安装： pip install tqdm
'''

import sys
import time


def view_bar():
	output = sys.stdout

	for i in range(0,100):
		second = 0.1
		time.sleep(0.1)
		output.write('\rcomplete percent:%.0f%%' % i)
		output.flush()


def use_tqdm():
	try:
		import tqdm

		for i in tqdm.tqdm(range(0, 100)):
			time.sleep(0.1)
	except:
		print "can't load tqdm"

if __name__ == '__main__':
	use_tqdm()