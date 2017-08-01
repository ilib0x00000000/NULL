# -*- coding:utf-8 -*-

'''
__author__ : ilib0x00000000
__datetime__ : 2017/7/22 16:54
'''


from django.conf.urls import url

from .views import TeacherListView, TeacherDetailView

urlpatterns = [
    url(r'^list/$', TeacherListView.as_view(), name='list'),
    url(r'^detail/(?P<teacher_id>\d+)$', TeacherDetailView.as_view(), name='detail'),
]