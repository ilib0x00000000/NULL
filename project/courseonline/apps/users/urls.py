# -*- coding:utf-8 -*-

'''
__author__ : ilib0x00000000
__datetime__ : 2017/7/23 16:30
'''

from django.conf.urls import url

from .views import UserProfileView, UpdateUserImageView, UpdateUserPwdView
from .views import UpdateEmailView, UserCourseView, UserLoveinView, UserMessageView
from .views import UserMessageDetailView

urlpatterns = [
    url(r'^profile$', UserProfileView.as_view(), name='profile'),
    url(r'^course$', UserCourseView.as_view(), name='course'),
    url(r'^lovein$', UserLoveinView.as_view(), name='lovein'),
    url(r'^message/(?P<msgid>\d+)$', UserMessageDetailView.as_view, name='msgid'),
    url(r'^message$', UserMessageView.as_view(), name='message'),
    url(r'^update/pwd$', UpdateUserPwdView.as_view(), name='update_pwd'),
    url(r'^update/image$', UpdateUserImageView.as_view(), name='update_image'),
    url(r'^update/email$', UpdateEmailView.as_view(), name='update_email'),
]