#!/usr/bin/env  python
# -*- coding:utf-8 -*-

'''
网站在登录时生成验证码
使用PIL生成图片：[https://github.com/ilib0x00000000/NULL/blob/master/python%20cookbook/authcode.py]

由于在登录时生成的验证码都是一次性的，所以无需保存，因此生成之后使用内存流直接将图片返回给浏览器
'''

import cStringIO

from django.http import HttpResponse

import authcode 


def captche(request):
	'''处理验证码
	'''
	
	img, strs = authcode.create_authcode()


	# 创建一个内存流存放图片
	buf = cStringIO.StringIO()
	img.save(buf, 'png')


	return HttpResponse(buf.getvalue(), 'image/png')