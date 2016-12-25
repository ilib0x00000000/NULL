# -*- coding:utf-8 -*-

import sys
import datetime
import logging
import traceback

from django.http import Http404, HttpResponse
from django.core import exceptions
from django.shortcuts import render

# 编写兼容旧版本的Django中间件
try:
	from django.utils.deprecation import MiddlewareMixin # Django -v 1.10.x
except ImportError:
	MiddlewareMixin = object   # Django -v 1.4.x - 1.9.x


error_log = logging.getLogger('log_error')
access_log = logging.getLogger('log_access')


class StatisticsError(MiddlewareMixin):
	"""统计服务端异常出现的数据
	当一个视图抛出异常时，Django会调用process_exception()来处理。
	process_exception()应该返回一个None或者一个HttpResponse对象。
	如果返回的是HttpResponse对象，模板响应和响应中间件会被调用，响应结果会返回给浏览器。
	否则，默认的异常处理机制将会被触发。

	异常出现时，需要记下异常的类型，请求的数据，程序的上下文

	Django异常列表： [https://segmentfault.com/a/1190000003783438]
	"""
	def process_exception(self, request, exception):
		"""这里的异常是在视图函数中出现的未解决的异常，都是5XX异常
		如果客户端请求的资源不存在，则在URLconf层面的异常处理将会启动，直接调用默认或指定的异常处理方式
		
		异常出现时，记录内容如下：
			1. 时间
			2. 异常类型
			3. 异常出现时的堆栈信息
			4. 请求的全部信息

		可以参照[https://github.com/ilib0x00000000/NULL/blob/master/project/spider/moji/mailto.py]发送邮箱给管理员
		"""

		request_content_type         = request.META.get('CONTENT_TYPE', 'null')
		request_http_accept          = request.META.get('HTTP_ACCEPT', 'null')
		request_http_accept_encoding = request.META.get('HTTP_ACCEPT_ENCODING', 'null')
		request_http_accept_language = request.META.get('HTTP_ACCEPT_LANGUAGE', 'null')
		request_http_host            = request.META.get('HTTP_HOST', 'null')
		request_http_referer         = request.META.get('HTTP_REFERER', 'null')
		request_http_user_agent      = request.META.get('HTTP_USER_AGENT', 'null')
		request_query_string         = request.META.get('QUERY_STRING', 'null')
		request_remote_addr          = request.META.get('REMOTE_ADDR', 'null')
		request_method               = request.method
		request_path                 = request.path   # 无法写到日志中
		request_cookies              = request.COOKIES
		request_body                 = request.GET if request_method=='GET' else request.POST

		error_msg = """************************ %s ************************\n异常类型： %s\n%s\n
		request:
			header:
				content_type: %s
				http_accept: %s
				http_accept_encoding: %s
				http_accept_language: %s
				http_host: %s
				http_referer: %s
				http_user_agent: %s
				query_string: %s
				remote_addr: %s
				method: %s
				cookies: %s

			--------------------------------------------------------
			body: %s
			url: 
		""" % 	(datetime.datetime.now(), sys.exc_info()[0], traceback.format_exc(), request_content_type, \
				request_http_accept, request_http_accept_encoding, request_http_accept_language, request_http_host, \
				request_http_referer, request_http_user_agent, request_query_string, request_remote_addr, request_method, \
				request_cookies, request_body)

		error_msg += request_path.encode('utf-8')
		error_log.error(error_msg)


		return render(request, '500.html')  # 返回准备好的500错误网页