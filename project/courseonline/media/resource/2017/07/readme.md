1. 将二级目录设置为source root
2. run/edit config


Django目录

project_name/
		|-------manage.py
		|-------templates/
		|-------project_name/

添加app
	tools/run manage task
	---startapp app_name
project_name/
		|-------manage.py
		|-------templates/
		|-------project_name/
		|-------app_name

创建静态目录
	static
project_name/
		|-------manage.py
		|-------templates/
		|-------project_name/
		|-------app_name
		|-------static

新建日志目录 /log
新建上传目录 /media
project_name/
		|-------manage.py
		|-------templates/
		|-------project_name/
		|-------app_name/
		|-------static/
		|-------log/
		|-------media/

新建文件夹 apps/
把app应用拖到apps/文件夹中
project_name/
		|-------manage.py
		|-------templates/
		|-------project_name/
		|-------apps/
					|-------app1_name/
		|-------static/
					|-----css/
					|-----js/
					|-----imgs/
		|-------log/
		|-------media/



# 2创建app
1. 在配置文件中注册该app  
2. 创建model之后执行：
		makemigration app_name
		migrate
在model定义时：
	1. 字段类型
	2. 字段参数
	3. Meta
		verbose_name
		verbose_name_plural  ---- 保持和verbose_name一致就行
		ordering


# 3生成数据库
	1. makemigrations
	2. migrate


# 4整合app
	1. 新建python package-------apps
	2. 将所有app拖到apps文件夹中，不要选择提示框中的选项
	3. 将apps mark成resource root


# 5安装xadmin
	1. 下载源码(最新的源码包存在问题)
	2. pip install xadmin(下载依赖包)
	   pip uninstall xadmin(删除xadmin，但是保留依赖包)
	3. 在settings文件中配置，
		xadmin
		crispy_forms


# 6向xadmin注册model
	1. 新建adminx.py-------(文件名是固定的)
	2. class ModelAdmin(object):
			list_display = ['field1', 'field2', 'field3', 'field4']  # 可选
 			search_fields = ['field1', 'field2', 'field3', 'field4'] # 可选
			list_filter = ['field1', 'field2', 'field3', 'field4']   # 可选
	3. xadmin.site.register(Model, ModelAdmin)






# 7配置静态文件
	settings:
		STATICFILES_DIRS = [
		    os.path.join(BASE_DIR, 'static')
		]
	在HTML文件中：
		/static/css/....
		/static/js/...
		/static/images/....



# 8使用类实现view
	from django.views.generic.base import View

	class LoginView(View):
		def get(self, request):
			pass
		def post(self, request):
			pass

	在url中：
		LoginView.as_view()


# 9使用Forms验证表单数据
	1. 新建forms.py-------在app目录下
	2. from django import forms
		class LoginForm(forms.Form):
			pass
	3. 在view中调用


# 10使用验证码插件
	1. pip install django-simple-captcha==0.4.6
	2. 创建form，在form中添加字段captcha = captcha.fields.CaptchaField()
	3. 创建form实例，fi = XxxForm()
	4. 将实例传递给HTML文件
	5. HTML中使用： fi.captcha------------------------------这里会自动生成验证码
	

# 11在ajax请求中设置csrf token
```JavaScript
function add_fav(current_elem, fav_id, fav_type){
    $.ajax({
        cache: false,
        type: "POST",
        url:"{% url 'org:collect' %}",
        data:{'fav_id':fav_id, 'fav_type':fav_type},
        async: true,
        beforeSend:function(xhr, settings){
            xhr.setRequestHeader("X-CSRFToken", "{{ csrf_token }}");  /* ajax中设置csrf_token */
        },
        success: function(data) {
            if(data.status == 'fail'){
                if(data.msg == '用户未登录'){
                    window.location.href="{% url 'login' %}";
                }else{
                    alert(data.msg)
                }

            }else if(data.status == 'success'){
                current_elem.text(data.msg)
            }
        },
    });
}
```


******************************************************
certifi (2017.4.17)
chardet (3.0.4)
Django (1.9.8)
django-crispy-forms (1.6.1)
django-formtools (2.0)
httplib2 (0.9.2)
idna (2.5)
MySQL-python (1.2.5)
olefile (0.44)
Pillow (4.2.1)
pip (9.0.1)
requests (2.18.1)
setuptools (7.0)
urllib3 (1.21.1)
xadmin (0.6.1)