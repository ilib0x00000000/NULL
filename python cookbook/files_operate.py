#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
1.改变Python系统的默认编码
2.关于文件与路径的操作
"""

import os
import sys
import itertools


def setCharset():
	"""改变Python的系统的默认字符集：
	sys.setdefaultencoding(name) 
	直接调用sys.setdefaultencoding()方法会出错，官方文档中"This function is only intended to be used by the site module implementation and,
	where needed, by sitecustomize. "说明只有在启动Python时才能使用
	"""
	if sys.getdefaultencoding() != 'utf-8':
		reload(sys)
		sys.setdefaultencoding('utf-8')



def file_operate():
	"""文件的操作：
	open(file_name, operate_model[, buffering])
	"""

	with open('database.py', 'rb') as f:
		"""with创建了一个上下文环境，即：打开了一个文件句柄，
		离开这个上下文环境（with语句），文件句柄就会被销毁
		"""
		lines = itertools.dropwhile(lambda line:line.strip().startswith('#'), f)	# 跳过以#开头的行
		for line in lines:
			print line.encode('utf-8')


def path_operate():
	# 得到完整的绝对路径
	abspath = os.path.abspath('test.txt')
	print abspath

	# 将path切割成目录和文件名，返回元组
	dir_name,file_name = os.path.split(abspath)
	print dir_name
	print file_name

	# 返回path最后的文件名或目录名，如果path以目录分隔符结果，则返回空
	print os.path.basename(dir_name)
	print os.path.basename(abspath)

	# 如果path存在，返回True，否则返回False
	os.path.exista(abspath)

	# 如果path是绝对路径，返回True，否则返回False
	os.path.isabs(dir_name)

	# 如果文件是一个已存在的文件，返回True，否则返回False
	os.path.isfile(file_name)

	# 如果path是一个目录，返回True，否则返回False
	os.path.isdir(dir_name)





if __name__ == '__main__':
	setCharset()
	# print sys.getdefaultencoding()
	file_operate()

