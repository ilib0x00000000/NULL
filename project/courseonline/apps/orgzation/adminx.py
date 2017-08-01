# -*- coding:utf-8 -*-

'''
__author__ : ilib0x00000000
__datetime__ : 2017/7/17 10:08
'''

import xadmin

from .models import City, CourseOrg, Teacher


class CityAdmin(object):
    pass


class CourseOrgAdmin(object):
    pass


class TeacherAdmin(object):
    pass


xadmin.site.register(City, CityAdmin)
xadmin.site.register(CourseOrg, CourseOrgAdmin)
xadmin.site.register(Teacher, TeacherAdmin)

