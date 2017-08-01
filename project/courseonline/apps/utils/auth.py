# -*- coding:utf-8 -*-

'''
__author__ : ilib0x00000000
__datetime__ : 2017/7/22 10:32
'''


from django.contrib.auth.decorators import login_required
from django.utils.decorators import method_decorator


class LoginRequiredMixin(object):
    """
    登录验证类
    """
    @method_decorator(login_required(login_url='/login.html'))
    def dispatch(self, request, *args, **kwargs):
        return super(LoginRequiredMixin, self).dispatch(request, *args, **kwargs)
