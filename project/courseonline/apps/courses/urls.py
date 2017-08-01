# -*- coding:utf-8 -*-

'''
__author__ : ilib0x00000000
__datetime__ : 2017/7/20 17:20
'''


from django.conf.urls import url

from .views import CourseListView, CourseDetailView, CourseCollectView, CourseVideoView, CourseCommentView, AddCommentView
from .views import VideoPlayView, VideoCommentView


urlpatterns = [
    url(r'^list$', CourseListView.as_view(), name='list'),
    url(r'^detail/(?P<curid>\d+)$', CourseDetailView.as_view(), name='detail'),
    url(r'^collect$', CourseCollectView.as_view(), name='collect'),
    url(r'^video/(?P<curid>\d+)$', CourseVideoView.as_view(), name='video'),
    url(r'^comment/(?P<curid>\d+)$', CourseCommentView.as_view(), name='comment'),
    url(r'^addcomment$', AddCommentView.as_view(), name='addcomment'),
    url(r'^video/play/(?P<videoid>\d+)$', VideoPlayView.as_view(), name='videoplay'),
    url(r'^video/comment$', VideoCommentView.as_view(), name='videocomment'),
]