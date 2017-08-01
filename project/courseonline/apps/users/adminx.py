# -*- coding:utf-8 -*-

'''
__author__ : ilib0x00000000
__datetime__ : 2017/7/17 10:08
'''

import xadmin

from .models import UserProfile, EmailVerifyRecond, Banner


# class UserProfileAdmin(object):
#     pass


class EmailVerifyRecondAdmin(object):
    pass


class BannerAdmin(object):
    pass

# xadmin.site.register(UserProfile, UserProfileAdmin)
xadmin.site.register(EmailVerifyRecond, EmailVerifyRecondAdmin)
xadmin.site.register(Banner, BannerAdmin)










