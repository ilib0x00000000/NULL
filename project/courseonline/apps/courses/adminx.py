# -*- coding:utf-8 -*-

'''
__author__ : ilib0x00000000
__datetime__ : 2017/7/17 10:08
'''


import xadmin

from .models import Course, CourseResource, Lesson, Video, CourseClass


class CourseAdmin(object):
    pass


class CourseResourceAdmin(object):
    pass


class LessonAdmin(object):
    pass


class VideoAdmin(object):
    pass


class CourseClassAdmin(object):
    pass


xadmin.site.register(Course, CourseAdmin)
xadmin.site.register(CourseResource, CourseResourceAdmin)
xadmin.site.register(Lesson, LessonAdmin)
xadmin.site.register(Video, VideoAdmin)
xadmin.site.register(CourseClass, CourseClassAdmin)