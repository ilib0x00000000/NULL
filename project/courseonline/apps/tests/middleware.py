# -*- coding:utf-8 -*-

"""
__author__ : ilib0x00000000
__datetime__ : 2017/7/27 12:00
"""


try:
    from django.utils.deprecation import MiddlewareMixin   # Django V1.10
except ImportError:
    _base_class = object
else:
    _base_class = MiddlewareMixin


class TestMiddleware(_base_class):
    """
    中间件就是包含下列4个方法中的一个或多个
    """
    def process_request(self, request):
        pass

    def process_view(self, view_func, func_args, func_kwargs):
        pass

    def process_exception(self):
        pass

    def process_response(self, request, response):
        pass