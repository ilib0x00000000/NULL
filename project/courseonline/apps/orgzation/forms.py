# -*- coding:utf-8 -*-

'''
__author__ : ilib0x00000000
__datetime__ : 2017/7/19 18:00
'''

import re
from django import forms

from operation.models import UserAsk


class UserAskForm(forms.Form):
    name = forms.CharField(required=True, min_length=2, max_length=20)
    phone = forms.CharField(required=True, min_length=11, max_length=11)
    course_name = forms.CharField(required=True, min_length=5, max_length=50)


class UserAskModelForm(forms.ModelForm):
    """
    ModelForm集成Model的Form

    自定义表单数据验证

    def clean_xxx(self):
        # 函数名是固定形式的， clean_加要验证的字段
        xxx = self.cleaned_data['xxx']   # 取出要验证的字段
        do(xxx)
        if valid:
            return xxx
        else:
            raise forms.ValidationError(..., ...)    # 如果字段不合法，抛出该异常就可以了
    """
    # add_field = forms.CharField(required=True, max_length=10)
    class Meta:
        model = UserAsk
        fields = ['name', 'mobile', 'course_name']  # 需要的字段
        # fields = ['name', 'mobile', 'course_name', 'add_field']  # 需要的字段

    def clean_mobile(self):
        """
        验证mobile字段的合法性
        :return:
        """
        mobile = self.cleaned_data['mobile']
        regex = re.compile(r'^0\d{2,3}\d{7,8}$|^1[358]\d{9}$|^147\d{8}')
        if regex.match(mobile):
            return mobile
        else:
            raise forms.ValidationError('手机号有误', code='mobile valid')


