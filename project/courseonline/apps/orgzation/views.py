# -*- coding:utf-8 -*-
from django.shortcuts import render
from django.views.generic import View
from django.http import HttpResponse
from pure_pagination import Paginator, PageNotAnInteger
from courseonline.settings import MEDIA_URL

from .models import CourseOrg, City
from .forms import UserAskModelForm

# Create your views here.


class OrgView(View):
    def get(self, request):
        all_city = City.objects.all()
        all_orgs = CourseOrg.objects.all()
        total = all_orgs.count()
        cityid = request.GET.get('city', 1)

        # 机构排名
        org_order = all_orgs.order_by('-click_nums')[:3]


        # 分页设置
        try:
            page = request.GET.get('page', 1)
        except PageNotAnInteger:
            page = 1

        p = Paginator(all_orgs, 5, request=request)

        orgs = p.page(page)


        return render(request, 'org-list.html', {'all_city':all_city, 'all_orgs' : orgs, 'total' : total, 'MEDIA_URL':MEDIA_URL,
                            'cityid' : cityid, 'org_order':org_order})


class UserAskView(View):
    """
    处理用户表单提交
    """
    @staticmethod
    def post(request):
        ua = UserAskModelForm(request.POST)
        if ua.is_valid():
            state = ua.save(commit=True)  # 直接保存到数据库
            if state:
                return HttpResponse('{"status":"success"}', content_type='application/json')   # 返回json数据
            else:
                return HttpResponse('{"status":"fail", "msg":"{0}"}'.format(ua.errors), content_type='application/json')
        else:
            return HttpResponse('{"status":"fail", "msg":"数据非法"}', content_type='application/json')


class OrgHomeView(View):
    """
    机构显示首页
    """
    def get(self, request, orgid):
        current_page = 'home'
        org = CourseOrg.objects.get(id=int(orgid))
        all_teacher = org.teacher_set.all()[:3]
        all_course = []
        for teacher in all_teacher:
            for tc in teacher.course_set.all():
                all_course.append(tc)
        print all_course
        return render(request, 'org-detail-homepage.html',
                      {
                          'request' : request,
                          'all_course':all_course[:4],
                          'all_teacher':all_teacher,
                          'org':org,
                          'MEDIA_URL' : MEDIA_URL,
                          'current_page' : current_page,
                      }
            )


class OrgCourseView(View):
    """
    机构-课程显示
    """
    def get(self, request, orgid):
        current_page = 'course'
        org = CourseOrg.objects.get(id=int(orgid))
        all_teacher = org.teacher_set.all()
        all_course = []
        # all_course = teacher.course_set.all() for teacher in all_teacher
        for teacher in all_teacher:
            for tc in teacher.course_set.all():
                all_course.append(tc)

        return render(request, 'org-detail-course.html', {
            'request': request,
            'current_page' : current_page,
            'all_course' : all_course,
            'MEDIA_URL': MEDIA_URL,
            'org': org,
        })


class OrgDescView(View):
    """
    机构-详情显示
    """
    def get(self, request, orgid):
        current_page = 'desc'
        org = CourseOrg.objects.get(id=int(orgid))
        org.click_nums += 1
        org.save()
        return render(request, 'org-detail-desc.html', {
            'request': request,
            'current_page' : current_page,
            'org' : org,
            'MEDIA_URL': MEDIA_URL,
        })


class OrgTeacherView(View):
    """
    机构-教师显示
    """
    def get(self, request, orgid):
        current_page = 'teacher'
        org = CourseOrg.objects.get(id=int(orgid))
        all_teacher = org.teacher_set.all()
        return render(request, 'org-detail-teachers.html', {
            'request': request,
            'current_page' : current_page,
            'org': org,
            'MEDIA_URL': MEDIA_URL,
            'all_teacher' : all_teacher,
        })


class CollectView(View):
    """
    收藏或者取消收藏
    """
    def post(self, request):
        pass