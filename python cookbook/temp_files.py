#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
使用tempfile库创建临时文件：
	o TemporaryFile()			创建未命名的临时文件
	o NamedTemporaryFile()		创建临时的命名文件
	o mkstemp()					创建临时文件
	o mkdtemp()					创建临时目录
	o gettempdir()				获得临时文件所在的目录
"""

import os
from tempfile import TemporaryFile,NamedTemporaryFile,mkstemp,mkdtemp,gettempdir


def create_tempfiles():
	"""创建的临时文件，可以是命名的，也可以是未命名的
	"""
	# 得到临时文件创建时所在的目录
	print gettempdir()

	# 创建一个未命名的临时文件
	with TemporaryFile('w+b') as f:
		f.write('Hello world\n')
		f.write('.......')

		f.seek(0)
		data = f.read()
		print data
	# 结束上下文环境后，临时文件销毁



	# 创建命名的临时文件
	with NamedTemporaryFile('w+b') as f:
		f.write('NamedTemporaryFile')

		f.seek(0)
		print f.read()
	# 临时文件被销毁


	# mkstemp创建临时文件，但是不会自动删除，需要手工处理
	file_temp = mkstemp()
	print os.path.abspath(file_temp[1])
	# 删除文件
	os.remove(file_temp[1])


	# mkdtemp创建临时目录，但是不会自动删除，需要手工处理
	dir_temp = mkdtemp()
	print dir_temp
	# 删除目录
	os.removedirs(dir_temp)


if __name__ == '__main__':
	create_tempfiles()