# -*- coding:utf-8 -*-

"""
__author__ : ilib0x00000000
__datetime__ : 2017/7/27 7:50

中间件：
Django中的中间件在版本1.10时发生了改变，所以要区别于版本
"""
import os
import logging

import django

from django.utils.cache import patch_vary_headers
from django.core.cache import cache
from django.core.exceptions import MiddlewareNotUsed
from django.http import HttpResponseForbidden

from courseonline.settings import LOGGING_ROOT, ADMIN_ACCESS_WHITELIST_ENABLED, FLOW_LOGGER
from core.models import DjangoAdminAccessIPWhitelist, ADMIN_ACCESS_WHITELIST_PREFIX

try:
    from django.utils.deprecation import MiddlewareMixin   # Django V1.10
except ImportError:
    _base_class = object
else:
    _base_class = MiddlewareMixin

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s %(filename)s [line:%(lineno)d] %(levelname)s %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S',
    filename= os.path.join(LOGGING_ROOT, 'access.log'),
    filemode='a'
)
log = logging.getLogger(__name__ + 'access')


class DoNotTrackMiddleware(_base_class):
    def process_request(self, request):
        if 'HTTP_DNT' in request.META and request.META['HTTP_DNT'] == '1':
            request.DNT = True
        else:
            request.DNT = False

    def process_response(self, request, response):
        patch_vary_headers(response, ['DNT'])
        return response


class AdminAccessIPWhiteListMiddleware(_base_class):
    """
    允许登录后台的IP白名单中间件
    """
    def __init__(self):
        self.ENABLED = ADMIN_ACCESS_WHITELIST_ENABLED
        self.USE_HTTP_X_FORWARDED_FOR = True  # 是否允许代理
        self.ADMIN_ACCESS_WHITELIST_MESSAGE = 'You are banned'

        if not self.ENABLED:
            raise MiddlewareNotUsed('白名单检测中间件没有注册')

        self.ABUSE_PREFIX = 'DJANGO_ADMIN_ACCESS_WHITELIST_ABUSE:'
        self.WHITELIST_PREFIX = ADMIN_ACCESS_WHITELIST_PREFIX

        for whitelist in DjangoAdminAccessIPWhitelist.objects.all():
            cache_key = self.WHITELIST_PREFIX + whitelist.ip
            cache.set(cache_key, '1')

    def _get_ip(self, request):
        ip = request.META['REMOTE_ADDR']
        if self.USE_HTTP_X_FORWARDED_FOR or not ip or ip=='127.0.0.1':
            ip = request.META.get('HTTP_X_FORWARDED_FOR', ip).split(',')[0].strip()
        return ip

    def is_whitelisted(self, ip):
        # 检测IP是否在缓存中
        is_cache = cache.get(self.WHITELIST_PREFIX + ip)
        if is_cache:
            log.info('**ip: ' + self.WHITELIST_PREFIX + ip + '访问了 /xadmin')
        else:
            log.warning('非允许IP：! %s !试图访问后台系统' % ip)
        return is_cache

    @staticmethod
    def http_response_forbidden(message, content_type):
        if django.VERSION[:2] > (1, 3):
            kwargs = {'content_type' : content_type}
        else:
            kwargs = {'mimetype' : content_type}
        return HttpResponseForbidden(message, **kwargs)

    def process_request(self, request):
        if not request.path.startswith('/xadmin'):
            return None

        ip = self._get_ip(request)
        user_agent = request.META.get('HTTP_USER_AGENT', None)

        log.info('Request from ip: %s and User-Agent: %s' % (ip, user_agent))

        if self.is_whitelisted(ip):
            return None
        else:
            # IP不在白名单中，禁止访问
            return self.http_response_forbidden(self.ADMIN_ACCESS_WHITELIST_MESSAGE + '\n<!-- {} -->'.format(ip), content_type="text/html")


class DisableSpiderMiddleware(_base_class):
    """
    反爬虫中间件
    """
    def process_request(self, request):
        user_agent = request.META.get('HTTP_USER_AGENT', None)

        ip = request.META['REMOTE_ADDR']
        if not ip or ip=='127.0.0.1':
            ip = request.META.get('HTTP_X_FORWARDED_FOR', ip).split(',')[0].strip()

        if user_agent:
            log.info('IP: %s 请求了 ** %s **' % (ip, request.path))
            return None
        else:
            log.warning('***请求没有携带 User-Agent *** : [ %s ] url: %s' % (ip, request.path))
            return HttpResponseForbidden('请重新使用浏览器打开')


class LogReferMiddleware(_base_class):
    """
    记录Http请求的refer
    """
    def process_request(self, request):
        refer = request.META.get('HTTP_REFERER ', '')

        if refer:
            log.info('--- %s --- : 请求来自网页： * %s *' % (request.META.get('REMOTE_ADDR ', ''), refer))

        return None


class FlowStatisticsMiddleware(_base_class):
    """
    流量统计
    时间  IP URL
    """
    def process_request(self, request):

        if request.path.startswith('/static') or request.path.startswith('/media'):
            return None

        ip = request.META['REMOTE_ADDR']
        if not ip or ip=='127.0.0.1':
            ip = request.META.get('HTTP_X_FORWARDED_FOR', ip).split(',')[0].strip()

        FLOW_LOGGER.info('**%s** < %s >' % (ip, request.path))
        return None