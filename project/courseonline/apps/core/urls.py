# -*- coding:utf-8 -*-

'''
__author__ : ilib0x00000000
__datetime__ : 2017/7/23 10:57
'''

from django.conf.urls import url

from .views import SearchView, SearchCourseView, SearchTeacherView, SearchOrgView

urlpatterns = [
    url(r'^$', SearchView.as_view(), name='all'),
    url(r'^course/$', SearchCourseView.as_view(), name='course'),
    url(r'^teacher/$', SearchTeacherView.as_view(), name='teacher'),
    url(r'^org/$', SearchOrgView.as_view(), name='org'),
]

