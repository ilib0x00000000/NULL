# -*- coding:utf-8 -*-

"""
__author__ : ilib0x00000000
__datetime__ : 2017/7/27 8:32
"""

import xadmin
from .models import DjangoAdminAccessIPWhitelist


class DjangoAdminAccessIPWhitelistAdmin(object):
    pass


xadmin.site.register(DjangoAdminAccessIPWhitelist, DjangoAdminAccessIPWhitelistAdmin)
