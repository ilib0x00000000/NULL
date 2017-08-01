# -*- coding:utf-8 -*-

"""
__author__ : ilib0x00000000
__datetime__ : 2017/7/19 18:09
"""

from django.conf.urls import url

from .views import OrgView, UserAskView, OrgHomeView, OrgCourseView, OrgDescView, OrgTeacherView, CollectView

urlpatterns = [
    url(r'^list$', OrgView.as_view(), name='orglist'),
    url(r'^userask$', UserAskView.as_view(), name='userask'),

    url(r'^home/(?P<orgid>\d+)', OrgHomeView.as_view(), name='orghome'),
    url(r'^course/(?P<orgid>\d+)', OrgCourseView.as_view(), name='orgcourse'),
    url(r'^desc/(?P<orgid>\d+)', OrgDescView.as_view(), name='orgdesc'),
    url(r'^teacher/(?P<orgid>\d+)', OrgTeacherView.as_view(), name='orgteacher'),
    url(r'^collect/$', CollectView.as_view(), name='collect'),
]
