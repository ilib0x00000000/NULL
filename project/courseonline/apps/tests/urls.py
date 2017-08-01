# -*- coding:utf-8 -*-

'''
__author__ : ilib0x00000000
__datetime__ : 2017/7/26 9:09
'''


from django.conf.urls import url

from .views import ErrorView, SQLView, XSSView, CSRFView
from .views import CacheView, cache, test_signal

urlpatterns = [
    url(r'^error$',ErrorView.as_view(), name='error'),
    url(r'^sql$', SQLView.as_view(), name='sql'),
    url(r'^xss$', XSSView.as_view(), name='xss'),
    url(r'^csrf$', CSRFView.as_view(), name='csrf'),
    url(r'^cache$', cache, name='cache'),
    url(r'^singal$', test_signal, name='signal'),
]
