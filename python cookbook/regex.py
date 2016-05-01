#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
正则表达式的应用：
	正则表达式中的对象：
		regex：编译的正则表达式
		match：匹配对象

	重复模式元字符（贪婪匹配符）：
		*	表示前面的模式出现0次或多次
		+	表示前面的模式出现至少1次
		?	表示前面的模式出现0次或1次
	   {N}	表示前面的模式出现N次
	  {M,N}	表示前面的模式出现M到N次


	编译对象常用的方法（匹配对象非None）：
		match 	匹配
		search	搜索
		sub		替换
		subn	替换，返回替换的次数
		split	切割
		start	搜索到的起始下标
		end		结束位置的下一个下标
		findall	查找到所有匹配的对象
		finditer查找到所有匹配的对象，返回的是迭代器

	编译对象的属性：
		pattern	返回正则表达式


	组解析匹配：
			编译对象
				|
				V
			匹配对象
			/	   \
		  None 	  非None
		  		 /		\
		  	有子组		无子组
		  	/	 \
		  group groups

	正则表达式的选项：
		re.IGNORECASE		忽略大小写
		re.MULTILINE		多行
		re.DOTALL			
		re.UNICODE 			指定非unicode模式匹配
		re.VERBOSE			详细模式表达式

	详细模式表达式：
		给正则表达式加注释
		需要指定 re.VERBOSE
"""

import re


def test_patterns(text, patterns=[]):
	"""子组：
	group():
			1> match.group(): 返回匹配的全部对象
			2> match.group(n): 返回第n个匹配的子组
	groups():
			返回一个元组，包含各子组匹配的对象
	"""

	for pattern in patterns:
		match = re.search(pattern, text)

		if match:
			print 'group: ', match.group()
			print match.group(1)
			print match.group(2)
			print match.groups()
		else:
			print 'no match'




def test_namesgroup(text, patterns):
	"""命名子组：
	语法：(?P<name>pattern)

	可以通过匹配结果的groupdict()获得名称与子串的映射
	"""

	for pattern in patterns:
		match = re.search(pattern, text)

		if match:
			print match.groupdict()
		else:
			print 'no match'





def test_chinese(text, patterns=[]):
	"""匹配非ASCII码时，需要指定参数re.UNICODE来匹配unicode字符
	"""

	for pattern in patterns:
		chinese = re.compile(pattern, re.UNICODE)

		match = chinese.search(text)

		if match:
			print match.group() or text[match.start() : match.end()]
		else:
			print 'no match'





if __name__ == '__main__':
	text = "To close out the day, GitHub's VP of Social Impact, Nicole Sanchez, will lead a session featuring"

	# patterns = [r'^[dws](\w)*', r'(\bG)(\w*)']
	# test_patterns(text, patterns)

	patterns = [r'(?P<begin_with_G>\bG)(?P<end_with_char>\w*)']
	test_namesgroup(text, patterns)


	text = '这是一段中文测试字符'
	patterns = [r'测试']
	test_chinese(text, patterns)