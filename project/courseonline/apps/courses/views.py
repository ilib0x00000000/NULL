# -*- coding:utf-8 -*-

from django.shortcuts import render
from django.views.generic import View
from django.http import HttpResponse
from pure_pagination import Paginator, PageNotAnInteger


from courseonline.settings import MEDIA_URL
from .models import Course, Video
from operation.models import CourseComment
from utils.auth import LoginRequiredMixin

# Create your views here.


class CourseListView(View):
    """
    处理公开课页面
    """
    def get(self, request):
        all_course = Course.objects.all().order_by('-add_time')
        hot_course = all_course.order_by('-click_nums')[:3]   # 热门课程

        sort = request.GET.get('order', '')

        if sort == 'hot':
            all_course = all_course.order_by('-click_nums')         # 按热门排序
        elif sort == 'students':
            all_course = all_course.order_by('-students')          # 按人数排序
       
        # 分页设置
        try:
            page = request.GET.get('page', 1)
        except PageNotAnInteger:
            page = 1

        p = Paginator(all_course, 9, request=request)

        courses = p.page(page)
    
        return render(request, 'course-list.html', {
            'all_course' : courses,
            'MEDIA_URL' : MEDIA_URL,
            'sort' : sort,
            'hot_course' : hot_course,
        })


class CourseDetailView(View):
    """
    课程详情页
    """
    def get(self, request, curid):
        course_id = int(curid)
        try:
            course = Course.objects.get(id=course_id)
            course.click_nums += 1
            course.save()

            tag = course.tags
            if tag:
                pass
            else:
                tag = course.name
            relate_course = Course.objects.filter(tags=tag)[:1]
        except Exception as e:
            pass
        return render(request, 'course-detail.html', {
            'course' : course,
            'MEDIA_URL' : MEDIA_URL,
            'relate_course' : relate_course,
        })


class CourseCollectView(View):
    """
    课程详情页的收藏
    """
    def post(self, request):
        print '收到请求'
        # TODO
        return HttpResponse('{"status" : "success"}', content_type='application/json')


class CourseVideoView(LoginRequiredMixin, View):
    """
    课程播放页------需要登录
    """
    def get(self, request, curid):
        course_id = int(curid)
        try:
            course = Course.objects.get(id=course_id)
        except Exception as e:
            pass
        return render(request, 'course-video.html', {
            'course' : course,
            'MEDIA_URL' : MEDIA_URL,
        })


class CourseCommentView(LoginRequiredMixin, View):
    """
    课程评论-------需要登录
    """
    def get(self, request, curid):
        course_id = int(curid)
        course = Course.objects.get(id=course_id)
        comments = CourseComment.objects.filter(course=course).order_by('-add_time')

        return render(request, 'course-comment.html', {
            'course' : course,
            'MEDIA_URL' : MEDIA_URL,
            'comments' : comments,
        })


class AddCommentView(LoginRequiredMixin,View):
    """
    新增评论
    """
    @staticmethod
    def post(request):
        if not request.user.is_authenticated():
            # 判断用户是否登录
            return HttpResponse('{"status":"fail", "msg":"用户未登录"}', content_type='application/json')

        course_id = int(request.POST.get('curid', 0))
        comment = request.POST.get('comment', "")

        if comment == '':
            return HttpResponse('{"status":"fail", "msg":"评论不能为空"}', content_type='application/json')

        if course_id > 0:
            ccts = CourseComment()
            ccts.course = Course.objects.get(id=course_id)
            ccts.comment = comment
            ccts.user = request.user
            ccts.save()
            return HttpResponse('{"status":"success", "msg":"添加成功"}', content_type='application/json')
        else:
            return HttpResponse('{"status":"fail", "msg":"添加失败"}', content_type='application/json')


class VideoPlayView(LoginRequiredMixin, View):
    """
    视频播放页面
    """
    def get(self, request, videoid):
        vid = int(videoid)
        video = Video.objects.get(id=vid)
        course = video.lesson.course
        return render(request, 'video-play.html', {
            'video' : video,
            'MEDIA_URL' : MEDIA_URL,
            'course' : course,
        })


class VideoCommentView(LoginRequiredMixin, View):
    """
    播放视频时，获取评论
    需要两个参数： courseid videoid
    """
    def get(self, request):
        courseid = request.GET.get('courseid', '')
        videoid = request.GET.get('videoid', '')

        if not courseid or not videoid:
            return render(request, '404.html', {})

        video = Video.objects.get(id=videoid)
        course = Course.objects.get(id=courseid)

        return render(request, 'video-play-comment.html', {
            'MEDIA_URL' : MEDIA_URL,
            'video' : video,
            'course' : course,
        })

