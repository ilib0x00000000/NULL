## django.http
***
    HttpResponse
    HttpResponseNotFound
    Http404(help_text)
    HttpResponseNotAllowed

## django.shortcuts
***
* render(request, template [, context][, content_type][, status][, current_app][, dirs][, using])
结合一个给定的模板和一个给定的上下文字典，返回一个渲染后的HttpResponse对象
必选的参数：
    * request: 该request用于生成response
    * template_name: 要使用的模板的完整名称或者模板名称的一个序列
可选的参数：
    * context: 添加到模板上下文的一个字典。默认是一个空字典。
    * content_type: 生成的文档要使用的MIME类型，默认为DEFAULT_CONTENT_TYPE设置的值。
    * status: 响应的状态码，默认为200.
    * current_app: 指示哪个应用包含当前的视图。
    * dirs: 
    * using: 用于加载模板使用的模板引擎的名称。


* render_to_response(template_filename [, context][, content_type][, status][, dirs][, using])  
根据一个给定的上下文字典渲染一个给定的目标，并返回渲染后的HttpResponse
必须的参数
    * template_name: 使用的模板的完整名称或者模板名称的序列。如果给出的是一个序列，将使用
存在的第一个模板
可选的参数
    * context: 添加到模板上下文中的字典，默认是个空字典。
    * content_type: 生成文档使用的MIME类型，默认为DEFAULT_CONTENT_TYPE设置的值
    * status: 相应的状态码，默认为200.
    * using: 加载模板使用的模板引擎的名称。


* redirect(to [, permanent=False,] *args, **kwargs)
为传递进来的参数返回HttpResponseRedirect给正确的URL
参数可以是：
    * 一个模型：将调用模型的get_absolute_url()函数
    * 一个视图，可以带有参数：将使用urlresolvers.reverse()来反向解析名称
    * 一个绝对的或相对的URL，将原样作为重定向的位置
默认返回一个临时的重定向，传递permanent=True可以返回一个永久的重定向。

* get_object_or_404(klass, *args, **kwargs)
在一个给定的模型管理器上调用get()，但是引发Http404而不是DoesNotExist异常
必选参数
    klass：获取该对象的一个Model类，Manager或QuerySet实例
    **kwargs: 查询的参数，格式应该可以被get()和filter()接受
注：与get()一样，如果找到多个对象将引发一个MultipleObjectsReturned异常


* get_list_or_404(klass, *args, **kwargs)
返回一个给定模型管理器上filter()的结果，并将结果映射为一个列表，如果结果为空则返回Http404
必选参数
    * klass：获取该列表的一个Model、Manager或QuerySet实例
    * **kwargs: 查询的参数，格式应该可以被get()和filter()接受


## django.views.decorators
***
* http.require_http_methods(reuqest_method_list)： 限制视图只能服务规定的http方法 
* http.require_GET()： 只允许视图接受GET方法的装饰器
* http.require_POST()： 只允许视图接受POST方法的装饰器
* http.require_safe()： 只允许视图接受GET和HEAD方法的装饰器

* http.condition(etag_func=None, last_modified_func=None)
* http.etag(etag_func)
* http.last_modified(last_modified_func)
这些装饰器可以用于生成ETag和Last-Modified头部

* gzip.gzip_page()： 如果浏览器允许gzip压缩，这个装饰器将对内容进行压缩。它设置相应的
Vary头部，以使得缓存根据Accept-Encoding头来存储信息

* vary.vary_on_cookie(func)
* vary.vary_on_headers(*headers)
可以用来基于特定的请求头部来控制缓存











