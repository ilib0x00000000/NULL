# -*- coding:utf-8 -*-

'''
编写Django中间件
Django中间件类不能继承任何类
Django中间件就是一个普通的Python类，类中实现以下一个或多个方法：
	o process_request(request)
	o process_view(request, view_func, view_args, view_kwargs)
	o process_template_response(request, response)
	o process_response(request, response)
	o process_exception(request, exception)

Django v1.10.x 与 之前的中间件有变化
参考[http://www.ziqiangxuetang.com/django/django-middleware.html]

使用中间件：
在settings.py文件中的
MIDDLEWARE = [
    'uttest.middleware.ShowServer',
    'uttest.middleware.DisableSpider',
    'uttest.middleware.StatisticsVisit',
]
'''

import datetime

from django.http import Http404

from . import models as uttest_models

# 编写兼容旧版本的Django中间件
try:
	from django.utils.deprecation import MiddlewareMixin # Django -v 1.10.x
except ImportError:
	MiddlewareMixin = object   # Django -v 1.4.x - 1.9.x


class DisableSpider(MiddlewareMixin):
	'''禁止爬虫访问
	'''
	def process_request(self, request):
		user_agent = request.META.get('HTTP_USER_AGENT', None)
		if user_agent == None:
			raise Http404

		return None


class StatisticsVisit(MiddlewareMixin):
	'''统计访问流量的信息
	'''
	def process_request(self, request):
		ip = request.META.get('REMOTE_ADDR', 'null')
		path = request.path
		refer = request.META.get('HTTP_REFERER', 'null')
		user_agent = request.META.get('HTTP_USER_AGENT', 'null')

		try:
			uttest_models.VisitorRecond.objects.create(
					ip = ip,
					path = path,
					refer = refer,
					user_agent = user_agent,
				)
		except Exception:
			# 无法将数据写进数据库
			print '[%s] %s:%s <- %s %s' % (datetime.datetime.now(), ip, path, refer, user_agent)

		return None

class ShowServer(MiddlewareMixin):
	'''显示服务端的server信息
	'''
	def process_response(self, request, response):
		response['Server'] = 'Apache 2.4.2'

		return response