# -*- coding:utf-8 -*-

from __future__ import unicode_literals

from django.db import models

import hashlib
import manager

# Create your models here.
class Article(models.Model):
	blog_id      = models.CharField(primary_key=True, db_index=True, max_length=32, blank=True) # 将博客的征文内容哈希出一个值，作为模型的外键及索引
	blog_title   = models.CharField(max_length=50)    # 博客标题
	blog_preview = models.CharField(max_length=200, blank=True, null=True)  # 博客预览，可为空
	blog_picture = models.CharField(max_length=200, blank=True, null=True)  # 博客配图，可为空
	blog_read    = models.PositiveIntegerField(default=0)   # 浏览量
	blog_category= models.CharField(max_length=50)          # 博客的分类
	blog_datetime= models.DateTimeField(auto_now_add=True)  # 博客日期
	blog_love    = models.PositiveIntegerField(default=0)   # 点赞数
 	blog_reward  = models.FloatField(default=0.0)           # 打赏
	blog_text    = models.TextField()                       # 博客正文

	# 设置模型的管理器
	objects = models.Manager()  # 默认管理器
	python = manager.Python()   # 自定义管理器
	linux  = manager.Linux()    # 自定义管理器

	def save(self, *args, **kwargs):
		'''重写父类的save()方法
		'''
		text_hash = hashlib.md5(self.blog_text.decode('utf-8'))
		self.blog_id = text_hash

		super(Article, self).save(*args, **kwargs)

	def __unicode__(self):
		'''Python2
		'''
		return u'%s %s' % (self.blog_title, self.blog_preview)

	__str__ = __unicode__  # Python3

	class Meta:
		ordering = ['-blog_datetime']   # 以博客的发表日期倒序

class Comment(models.Model):
	'''将博客的征文哈希的值作为博客与之对应的外键
	'''
	comment_blogid = models.ForeignKey(Article)
	comment_er     = models.CharField(max_length=60) # 评论者
	comment_time   = models.DateTimeField()
	comment_text   = models.CharField(max_length=500) # 评论的内容

