# -*- coding:utf-8 -*-

'''
__author__ : ilib0x00000000
__datetime__ : 2017/7/17 10:08
'''

import xadmin

from .models import CourseComment,UserAsk,UserCourse,UserFavorite,UserMessage


class CourseCommentAdmin(object):
    pass


class UserAskAdmin(object):
    pass


class UserCourseAdmin(object):
    pass


class UserFavoriteAdmin(object):
    pass


class UserMessageAdmin(object):
    pass

xadmin.site.register(CourseComment, CourseCommentAdmin)
xadmin.site.register(UserAsk, UserAskAdmin)
xadmin.site.register(UserCourse, UserCourseAdmin)
xadmin.site.register(UserFavorite, UserFavoriteAdmin)
xadmin.site.register(UserMessage, UserMessageAdmin)