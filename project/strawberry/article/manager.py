# -*- coding:utf-8 -*-

'''
为自定义的模型添加管理器
'''

from django.db import models

class Python(models.Manager):
	'''编写一个管理器，当搜索时，只返回关于Python的文章
	'''
	# 重写父类的get_queryset()方法
	def get_queryset(self):
		super(Python, self).get_queryset().filter(blog_category__icontains='python')

class Linux(models.Manager):
	'''编写一个管理器，当搜索时，只返回关于Linux的文章
	'''
	# 重写父类的get_queryset()方法	
	def get_queryset(self):
		super(Linux, self).get_queryset().filter(blog_category__icontains='linux')