# -*- coding:utf-8 -*-

from django.shortcuts import render
from django.views.generic import View
from django.http import HttpResponse
from pure_pagination import Paginator, PageNotAnInteger


from courseonline.settings import MEDIA_URL
from orgzation.models import Teacher
from courses.models import Course

# Create your views here.


class TeacherListView(View):
    def get(self, request):
        teachers = Teacher.objects.all()
        count = teachers.count()
        hot_teacher = Teacher.objects.all().order_by('-click_nums')[:3]

        # 按热门排序
        order = request.GET.get('order', '')
        if order == 'hot':
            teachers = teachers.order_by('click_nums')

        # 分页设置
        try:
            page = request.GET.get('page', 1)
        except PageNotAnInteger:
            page = 1

        p = Paginator(teachers, 4, request=request)

        all_teachers = p.page(page)

        return render(request, 'teachers-list.html', {
            'teachers' : all_teachers,
            'MEDIA_URL' : MEDIA_URL,
            'count' : count,
            'hot_teacher' : hot_teacher,
        })


class TeacherDetailView(View):
    def get(self, request, teacher_id):
        tid = int(teacher_id)

        teacher = Teacher.objects.get(id=tid)
        teacher.click_nums += 1
        teacher.save()

        courses = Course.objects.filter(teacher=teacher)
        hot_teacher = Teacher.objects.all().order_by('-click_nums')[:3]

        return render(request, 'teacher-detail.html', {
            'teacher' : teacher,
            'MEDIA_URL' : MEDIA_URL,
            'courses' : courses,
            'hot_teacher' : hot_teacher,
        })