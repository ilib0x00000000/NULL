# -*- coding:utf-8 -*-

'''
__author__ : ilib0x00000000
__datetime__ : 2017/7/17 18:54
'''


from django import forms
from captcha.fields import CaptchaField

from users.models import UserProfile, EmailVerifyRecond



class LoginForm(forms.Form):
    username = forms.EmailField(required=True)
    password = forms.CharField(required=True)


class RegisterForm(forms.Form):
    email = forms.EmailField(required=True)
    password = forms.CharField(required=True, min_length=6)
    captcha = CaptchaField(error_messages={'invalid':'验证码错误'})


class UpdateImageForm(forms.ModelForm):
    class Meta:
        model = UserProfile
        fields = ['image']


class UpdateEmailForm(forms.ModelForm):
    class Meta:
        model = EmailVerifyRecond
        fields = ['email', 'code']


class UpdateProfileForm(forms.ModelForm):
    class Meta:
        model = UserProfile
        fields = ['nick_name', 'birthday', 'gender', 'address', 'mobile']


class UpdatePasswordForm(forms.ModelForm):
    captcha = CaptchaField(error_messages={'invalid':'验证码错误'})

    class Meta:
        model = EmailVerifyRecond
        fields = ['email', 'captcha']


class ResetPasswordForm(forms.Form):
    password = forms.CharField(required=True)
    password2 = forms.CharField(required=True)
    email = forms.EmailField(required=True)
