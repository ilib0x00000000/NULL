# -*- coding:utf-8 -*-


from django.shortcuts import render, render_to_response
from django.views.generic import View
from django.db.models import Q
from django.http import HttpResponseRedirect
from django.contrib.auth import logout
from django.core.urlresolvers import reverse    # 逆向解析URL配置

from courses.models import Course
from orgzation.models import CourseOrg, Teacher
from courseonline.settings import MEDIA_URL
from utils.auth import LoginRequiredMixin
from users.models import Banner

# Create your views here.


class SearchView(View):
    def get(self, request):
        keyword = request.GET.get('keyword', '')

        if keyword:
            # keyword有值
            courses = Course.objects.filter(Q(name__icontains=keyword) | Q(desc__icontains=keyword))
            courseorgs = CourseOrg.objects.filter(Q(name__icontains=keyword)|Q(desc__icontains=keyword))
            teachers = Teacher.objects.filter(Q(name__icontains=keyword) | Q(points__icontains=keyword))
            total = courses.count() + courseorgs.count() + teachers.count()
            courses = courses[:6]
            courseorgs = courseorgs[:6]
            teachers = teachers[:6]
        else:
            courses = Course.objects.all().order_by('-click_nums')[:6]
            courseorgs = CourseOrg.objects.all().order_by('-click_nums')[:6]
            teachers = Teacher.objects.all().order_by('-click_nums')[:6]
            total = courses.count() + courseorgs.count() + teachers.count()

        return render(request, 'search.html', {
            'MEDIA_URL' : MEDIA_URL,
            'courses' : courses,
            'courseorgs' : courseorgs,
            'teachers' : teachers,
            'keyword' : keyword,
            'total' : total,
        })


class SearchCourseView(View):
    def get(self, request):
        keyword = request.GET.get('keyword', '')
        return render(request, 'search.html', {})


class SearchTeacherView(View):
    def get(self, request):
        keyword = request.GET.get('keyword', '')
        return render(request, 'search.html', {})


class SearchOrgView(View):
    def get(self, request):
        keyword = request.GET.get('keyword', '')
        return render(request, 'search.html', {})


class LogoutView(LoginRequiredMixin, View):
    def get(self, request):
        refer = request.GET.get('refer', '')    # 记住退出时的页面，退出后重定向到该页面
        # refer = request.META.get('HTTP_REFERER ', '')
        logout(request)

        if refer:
            return HttpResponseRedirect(refer)
        else:
            return HttpResponseRedirect(reverse('index'))


class MessageView(LoginRequiredMixin, View):
    def get(self, request):
        return render(request, 'usercenter-message.html', {})


class IndexView(View):
    def get(self, request):
        # 轮播图
        bans = Banner.objects.all().order_by('index')[:5]
        courses = Course.objects.filter(is_advan=False)[:6]
        bans_courses = Course.objects.filter(is_advan=True)[:3]
        orgs = CourseOrg.objects.all()[:15]

        return render(request, 'index.html', {
            'bans' : bans,
            'MEDIA_URL' : MEDIA_URL,
            'courses' : courses,
            'bans_courses' : bans_courses,
            'orgs' : orgs,
        })


# 处理404页面
def response404(request):
    response = render_to_response('404.html', {})
    response.status_code = 404
    return response


# 处理500页面
def response500(request):
    response = render_to_response('500.html', {})
    response.status_code = 500
    return response


# 处理403页面
def response403(request):
    response = render_to_response('403.html', {})
    response.status_code = 403
    return response
