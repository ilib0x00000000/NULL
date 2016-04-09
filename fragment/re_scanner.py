#!/usr/bin/env python3
# -*- coding:utf-8 -*-

"""
正则表达式对象的扫描:（编译----->扫描------>匹配）
	正则表达式会使用编译好的正则对象去扫描字符串，得到一个扫描对象，调用该对象的match()方法，
	如果有匹配中，则返回第一个匹配的匹配对象，否则报异常。
	当匹配达到最后一个符合条件的对象之后，	再去匹配将会引发异常
注：开发环境
			os : ubuntu14.04
			py version : 3.4.3 
"""

"""
	@author : ilib0x00000000
	@email  : ilib0x00000000@gmail.com
	@version: 1.0
	@date	: 2016/04/08
	@project: 正则表达式学习
"""


import re

def main():
	#创建一个命名捕获组
	WS = r"(?P<WS>\s+)"
	NUM = r"(?P<NUM>\d+)"
	PLUS = r"(?P<PLUS>\+)"
	MINUS = r"(?P<MINUS>-)"
	TIMES = r"(?P<TIMES>\*)"
	DIVIDE = r"(?P<DIVIDE>/)"
	LPAREN = r"(?P<LPAREN>\()"
	RPAREN = r"(?P<RPAREN>\))"

	master_pat = re.compile("|".join([WS,NUM,PLUS,MINUS,TIMES,DIVIDE,LPAREN,RPAREN]))	# 编译正则表达式

	scanner = master_pat.scanner("1 + 1")

	# scanner不是迭代器，直接 迭代会报异常
	# for m in scanner.match():
	# 	print(m.lastgroup, m.group())

	iter_flag = ".."

	if iter_flag == "":
		m = scanner.match()
		print(m.lastgroup, m.group())		# lastgroup得到的是命名的子组，group()得到的是子组的值

		m = scanner.match()
		print(m.lastgroup, m.group())

		m = scanner.match()
		print(m.lastgroup, m.group())

		m = scanner.match()
		print(m.lastgroup, m.group())

		m = scanner.match()
		print(m.lastgroup, m.group())
	else:
		scanner_iter = iter(scanner.match, None)
		for m in scanner_iter:
			print(m.lastgroup, m.group())

if __name__ == '__main__':
	main()