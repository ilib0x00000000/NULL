# -*- coding:utf-8 -*-

import json

from django.shortcuts import render
from django.contrib.auth import authenticate
from django.contrib.auth import login as xlogin
from django.contrib.auth.backends import ModelBackend
from django.contrib.auth.hashers import make_password
from django.db.models import Q
from django.views.generic.base import View
from django.http import HttpResponse, HttpResponseRedirect, HttpResponseForbidden
from pure_pagination import Paginator, PageNotAnInteger
from django.core.urlresolvers import reverse    # 逆向解析URL配置


from .models import UserProfile
from operation.models import UserCourse, UserFavorite, UserMessage
from courses.models import Course, Teacher, CourseOrg
from .forms import UpdatePasswordForm, RegisterForm, UpdateImageForm, UpdateEmailForm
from .forms import ResetPasswordForm, UpdateProfileForm, LoginForm
from utils.mail import email_send
from utils.auth import LoginRequiredMixin
from users.models import EmailVerifyRecond
from courseonline.settings import MEDIA_URL, JSON_TYPE
# Create your views here.


class CustomBackend(ModelBackend):
    # 自定义一个类用于用户登录校验
    '''
    默认的自带用户校验只能使用用户名登录，自定义一个类扩展该方法
    使得既可以使用用户名又可以使用邮箱登录

    在自定义完校验方法之后，需要在setting中设置
    '''
    def authenticate(self, username=None, password=None, **kwargs):
        try:
            user = UserProfile.objects.get(Q(username=username) | Q(email=username))
            if user.check_password(password):
                return user
        except Exception as e:
            return None


class LoginView(View):
    '''
    使用类来实现view
    '''
    def get(self, request):
        return render(request, 'login.html', {})

    def post(self, request):
        lf = LoginForm(request.POST)
        username = request.POST.get('username', '')
        password = request.POST.get('password', '')

        if lf.is_valid():
            user = authenticate(username=username, password=password)

            if user:
                xlogin(request, user)  # 用户登录
                return HttpResponseRedirect(reverse('index'))
            else:
                return render(request, 'login.html', {'error_msg':'该用户不存在，请确认输出是否正确'})
        else:
            return render(request, 'login.html', {'error_msg':'输入数据不合法'})




class RegisterView(View):
    '''
    使用类来实现view注册
    '''
    @staticmethod
    def get(request):
        register_form = RegisterForm()
        return render(request, 'register.html', {'register_form':register_form})

    @staticmethod
    def post(request):
        register_form = RegisterForm(request.POST)
        if register_form.is_valid():
            email = request.POST.get('email', '')

            exist = False
            if UserProfile.objects.filter(email=email):
                exist = True
            if exist:
                register_form = RegisterForm()
                return render(request, 'register.html', {
                    'error_msg' : '该邮箱已被注册，请重新输入一个邮箱',
                    'register_form': register_form,
                })

            user = UserProfile()
            user.username = email
            user.email = request.POST.get('email', '')
            user.password = make_password(request.POST.get('password', ''))
            user.save()

            # 向邮箱发送验证码
            # 发送存在问题
            state = email_send(user.email, send_type='register', length=16)
            if state:
                # 邮箱发送成功，跳转到邮箱登录页面
                if email.endswith('@126.com') or email.endswith('@163.com') or email.endswith('@yeah.net'):
                    return HttpResponseRedirect('http://email.163.com/')
                elif email.endswith('@qq.com'):
                    return HttpResponseRedirect('http://email.qq.com')
                elif email.endswith('@sina.com') or email.endswith('@sina.cn'):
                    return HttpResponseRedirect('http://mail.sina.com.cn/')
                else:
                    return render(request, 'skip.html', {})
            else:
                register_form = RegisterForm()
                return render(request, 'register.html', {
                    'error_msg' : '系统出现错误，请稍后再试！',
                    'register_form' : register_form,
                })
        else:
            register_form = RegisterForm()
            return render(request, 'register.html', {
                'error_msg': '输入数据有误，请重新输入',
                'register_form': register_form,
                'email' : request.POST.get('email', ''),
                'password' : request.POST.get('password', '')
            })


class ActiveView(View):
    def get(self, request):
        code = request.GET.get('code', '')
        obj = EmailVerifyRecond.objects.get(code=code)
        print obj

        if obj:
            # 如果激活链接是有效的
            email = obj.email
            user = UserProfile.objects.get(email=email)
            user.has_active = True
            user.save()
            return HttpResponseRedirect(reverse('login'))
        else:
            return HttpResponseRedirect(reverse('register'))


class UpdatePasswordView(View):
    def get(self, request):
        upf = UpdatePasswordForm()
        return render(request, 'forgetpwd.html', {
            'upf' : upf,
        })

    def post(self, request):
        upf = UpdatePasswordForm(request.POST)
        email = request.POST.get('email', '')
        
        if upf.is_valid():
            # 输入数据合法
            user = UserProfile.objects.filter(email=email)
            if user:
                # 如果用户存在
                upf.save()
                if email_send(email, send_type='forget', length=16):
                    return render(request, 'skip.html', {})
                else:
                    error_msg = '发送邮箱失败，请稍后再试'
            else:
                error_msg = '该邮箱尚未注册用户，请重新输入邮箱！'
        else:
            error_msg = json.dumps(upf.errors)
            upf = UpdatePasswordForm()
            # error_msg = '验证码错误，请重新输入！'

        return render(request, 'forgetpwd.html', {
                'upf' : upf,
                'error_msg' : error_msg,
                'email' : email
            })


class UserProfileView(LoginRequiredMixin, View):
    """
    获取个人信息首页和修改个人信息
    """
    def get(self, request):
        return render(request, 'usercenter-info.html', {
            'MEDIA_URL' : MEDIA_URL,
        })

    def post(self, request):
        uuf = UpdateProfileForm(request.POST, instance=request.user)

        if uuf.is_valid():
            request.user.save()
            return HttpResponse('{"status":"success"}',content_type=JSON_TYPE)
        else:
            return HttpResponse(json.dumps(uuf.errors), content_type=JSON_TYPE)


class UpdateUserImageView(LoginRequiredMixin, View):
    """
    修改用户头像
    """
    def post(self, request):
        uif = UpdateImageForm(request.POST, request.FILES, instance=request.user) # 使用ModelForm的实例化对象
        if uif.is_valid():
            # request.user.image = uif.cleaned_data['image']
            # request.user.save()
            uif.save()
            return HttpResponse('{"status":"success"}', content_type=JSON_TYPE)
        else:
            return HttpResponse('{"status":"fail", "msg":"更换头像失败"}', content_type=JSON_TYPE)


class UpdateUserPwdView(LoginRequiredMixin, View):
    """
    修改用户密码
    """
    def post(self, request):
        password1 = request.POST.get('password1', '')
        password2 = request.POST.get('password2', '')

        if password1 != password2:
            return HttpResponse('{"status":"fail", "msg":"密码不一致"}', content_type=JSON_TYPE)

        if len(password1) < 6:
            return HttpResponse('{"status":"fail", "msg":"密码长度太短，请重新输入"}', content_type=JSON_TYPE)

        try:
            request.user.password = make_password(password1)
            request.user.save()
            return HttpResponse('{"status":"success"}', content_type=JSON_TYPE)
        except Exception:
            return HttpResponse('{"status":"fail", "msg":"数据库写入失败"}', content_type=JSON_TYPE)


class UpdateEmailView(LoginRequiredMixin, View):
    """
    修改用户邮箱------待完善
    """
    def get(self, request):
        """
        获取验证码
        :param request:
        :return:
        """
        email = request.GET.get('email', '')

        # 验证该邮箱是否存在
        if UserProfile.objects.filter(email=email):
            return HttpResponse('{"status":"fail", "email":"该邮箱已存在"}', content_type=JSON_TYPE)

        status = email_send(email, send_type='update', length=4)
        if status:
            print '发送成功'
        else:
            print '发送失败'
        return HttpResponse('{"status":"success"}', content_type=JSON_TYPE)

    def post(self, request):
        """
        输入验证码
        :param request:
        :return:
        """
        email = request.POST.get('email', '')
        code = request.POST.get('code', '')

        uef = UpdateEmailForm(request.POST)
        if uef.is_valid():
            # 数据是合法的
            if EmailVerifyRecond.objects.get(email=email, code=code, send_type='update'):
                # 说明验证码正确
                request.user.email = email
                request.user.save()
                return HttpResponse('{"status":"success"}', content_type=JSON_TYPE)
            else:
                return HttpResponse('{"status":"fail", "email":"验证码错误"}', content_type=JSON_TYPE)
        else:
            return HttpResponse(json.dumps(uef.errors), content_type=JSON_TYPE)


class UserCourseView(LoginRequiredMixin, View):
    """
    获取个人课程信息
    """
    def get(self, request):
        courses = UserCourse.objects.filter(user=request.user)
        return render(request, 'usercenter-mycourse.html', {
            'courses' : courses,
            'MEDIA_URL' : MEDIA_URL,
        })


class UserLoveinView(LoginRequiredMixin, View):
    """
    用户收藏显示
    """
    def get(self, request):
        key = request.GET.get('key', '')

        if key=='':
            html = 'usercenter-fav-org.html'    # 筛选出收藏的机构
            objs_id = UserFavorite.objects.filter(user=request.user, fav_type=2)
            objs = [CourseOrg.objects.get(id=oid.id) for oid in objs_id]
        elif key == 'teacher':
            html = 'usercenter-fav-teacher.html' # 筛选出收藏的讲师
            objs_id = UserFavorite.objects.filter(user=request.user, fav_type=3)
            objs = [Teacher.objects.get(id=oid.id) for oid in objs_id]
        else:
            html = 'usercenter-fav-course.html' # 筛选出收藏的课程
            objs_id = UserFavorite.objects.filter(user=request.user, fav_type=1)
            objs = [Course.objects.get(id=oid.id) for oid in objs_id]

        return render(request, html, {
            'objs' : objs,
            'MEDIA_URL' : MEDIA_URL,
        })


class UserMessageView(LoginRequiredMixin, View):
    """
    用户消息显示
    """
    def get(self, request):
        messages = UserMessage.objects.filter(user=request.user.id)

        # 分页设置
        try:
            page = request.GET.get('page', 1)
        except PageNotAnInteger:
            page = 1

        msg = Paginator(messages, 9, request=request)

        msgs = msg.page(page)
        return render(request, 'usercenter-message.html', {
            'messages' : msgs
        })


class UserMessageDetailView(LoginRequiredMixin, View):
    def get(self, request, msgid):
        pass


class ResetPasswordView(View):
    """
    重置密码
    """
    def get(self, request):
        code = request.GET.get('code', '')
        obj = EmailVerifyRecond.objects.filter(code=code, send_type='forget')[0]
        if obj:
            email = obj.email
            obj.delete()
            return render(request, 'password_reset.html', {
                'email' : email,
                'error' : False,
            })
        else:
            return HttpResponseForbidden('无权访问')

    def post(self, request):
        password = request.POST.get('password', '')
        password2 = request.POST.get('password2', '')
        email = request.POST.get('email', '')
        rpf = ResetPasswordForm(request.POST)
        if rpf.is_valid():
            # 数据合法
            if password != password2:
                return render(request, 'password_reset.html', {
                    'error' : True,
                    'error_msg' : '两次密码输入不一致',
                })
            else:
                user = UserProfile.objects.filter(email=email)[0]
                user.password = make_password(password)
                user.save()
                return HttpResponseRedirect(reverse('login'))
        else:
            return render(request, 'password_reset.html', {
                'error' : True,
                'error_msg': '输入的数据有误，请重新输入！',
            })
