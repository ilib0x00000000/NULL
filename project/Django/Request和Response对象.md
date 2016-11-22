# Request对象和Response对象
***
Django使用Request对象和Response对象在系统间传递状态
当请求一个页面时，Django会建立一个包含请求元数据的HttpRequest对象。当Django加载对应的视图
时，HttpRequest对象将作为视图函数的第一个参数，每个视图会返回一个HttpResponse对象。
HttpRequest和HttpResponse对象的API定义在django.http模块中。

## HttpRequest对象
***
class HttpRequest
属性：
    * scheme: 一个字符串，表示请求的方案，http或https
    * body: 一个字节字符串，表示原始HTTP请求的正文，对处理非HTML形式的数据非常有用：二进制图像、XML等。
    * path: 一个字符串，表示请求的页面的完整路径，不包含域名。
    * path_info: 在某些Web服务器配置下，主机名后的URL部分被分成脚本前缀部分和路径信息部分
    * method: 一个字符串，表示请求使用的HTTP方法，必须大写
    * encoding: 一个字符串，表示提交的数据的编码方式。这个属性是可写的。
    * GET: 一个类似于字典的对象，包含HTTP GET的所有参数。参见<QueryDict>
    * POST: 一个包含所有给定的HTTP POST参数的类字典对象，提供了包含表单数据的请求，参见<QueryDict>，如果需要访问请求中的原始或非表单数据，可以使用body属性
    * REQUEST: 不建议使用
    * COOKIES: 一个标准的Python字典，包含所有的cookie，键和值都为字符串。
    * FILES: 一个类似于字典的对象，包含所有的上传文件。
    * META: 一个标准的Python字典，包含所有的HTTP头部。
        - CONTENT_LENGTH: 请求的正文的长度
        - CONTENT_TYPE: 请求的正文的MIME类型
        - HTTP_ACCEPT: 响应可接收的Content-Type
        - HTTP_ACCEPT_ENCODING: 响应可接收的编码
        - HTTP_ACCEPT_LANGUAGE: 响应可接收的语言
        - HTTP_HOST: 客户端发送的HTTP Host头部
        - HTTP_REFERER: Referring页面
        - HTTP_USER_AGENT: 客户端的user-agent字符串
        - QUERY_STRING: 单个字符串形式的查询字符串（未解析过的形式）
        - REMOTE_ADDR: 客户端的IP地址
        - REMOTE_HOST: 客户端的主机名
        - REMOTE_USER: 服务器认证后的用户
        - REQUEST_METHOD: 一个字符串，“GET”或“POST”
        - SERVER_NAME: 服务器的主机名
        - SERVER_PORT: 服务器的端口
    * user: 一个AUTH_USER_MODEL类型的对象，表示当前登录的用户。如果用户当前没有登录，user将设置
    为django.contrib.auth.models.AnonymousUser的实例。
    * session: 一个既可读又可写的类似于字典的对象，表示当前的会话。
    * urlconf: 不是由Django自身定义的，但是如果其他代码设置了它，Django就会读取它。
    * resolver_match: 一个Resolver
    * upload_handlers: 文件上传处理器
方法：
    * get_host(): 根据从HTTP_X_FORWARDED_HOST和HTTP_HOST头部信息返回请求的原始主机。
    * get_full_path(): 返回path，如果可以将加上查询字符串
    * build_absolute_uri(): 返回location的绝对URI，如果location没有提供，则设置
    request.get_full_path()
    * get_signed_cookie(): 返回签名过的Cookie对应的值，如果签名不再合法则返回
    django.core.signing.BadSignature。如果提供default参数，将不会引发异常并返回
    default的值
    * is_secure(): 如果请求是通过HTTPS发起的，则返回True
    * is_ajax(): 如果请求是通过XMLHttpRequest发起的，则返回True，方法是检查
    HTTP_X_REQUESTED_WITH头部是否是字符串'XMLHttpRequest'。
    * read():
    * readline():
    * readlines():
    * xreadlines():
    这几个方法实现类文件的接口用于读取HttpRequest实例。

## HttpResponse对象
***
class HttpResponse
设置Response对象的头部：
    response['Age'] = 20
    response['Content-Disposition'] = 'attachment; filename="foo.xls"'

Response对象的属性：
    response.content
    response.charset
    response.status_code
    response.reason_phrase
    response.streaming
    response.closed

Response对象的方法：
    * HttpResponse.__init__(content='', content_type=None, status=200,
    reason=None, charset=None)
    * HttpResponse.__setitem__(header, value)
    * HttpResponse.__delitem__(header)
    * HttpResponse.__getitem__(header)
    * HttpResponse.has_header(header)
    * HttpResponse.setdefault(header, value)
    * HttpResponse.set_cookie(key, value='', max_age=None, expires=None, 
    path='/', domain=None, secure=None, httponly=False)
    * HttpResponse.set_signed_cookie(key, value, salt='', max_age=None, 
    expires=None, path='/', domain=None, secure=None, httponly=True)
    * HttpResponse.delete_cookie(key, path='/', domain=None)
    * HttpResponse.write()
    * HttpResponse.tell()
    * HttpResponse.flush()
    * HttpResponse.getvalue()
    * HttpResponse.writable()
    * HttpResponse.writelines(lines)

HttpResponse的子类
    * HttpResponseRedirect
    * HttpResponsePermanentRedirect
    * HttpResponseNotModified
    * HttpResponseBadRequest
    * HttpResponseNotFound
    * HttpResponseForbidden
    * HttpResponseNotAllowed
    * HttpResponseGone
    * HttpResponseServerError
    * JsonResponse
    * StreamingHttpResponse
    * FileResponse


## QueryDict对象
***
class QueryDict-----django.http.QueryDict
在HttpRequest对象中，GET和POST属性是django.http.QueryDict的实例，它是一个自定义的类似
字典的类，用来处理同一个键带有多个值。

方法：
* QueryDict.__init__(query_string=None, mutable=False, encoding=None)
* QueryDict.__getitem__(key)
* QueryDict.__setitem__(key, value)
* QueryDict.__contains__(key)
* QueryDict.get(key, default)
* QueryDict.setdefault(key, default)
* QueryDict.update(other_dict)
* QueryDict.items()
* QueryDict.iteritems()
* QueryDict.iterlists()
* QueryDict.values()
* ...


# TemplateResponse和SimpleTemplateResponse
***
标准的HttpResponse对象是静态的结构。在构造的时候提供一个渲染好的内容，但是当内容改变时却不能容易的完成相应的改变。然而，有时候允许装饰器或者中间件在响应构造之后修改它是很有用的。

## SimpleTemplateResponse
***
属性：
    * template_name: 渲染的模板的名称。接收一个与后端有关的模板对象、模板的名称或是一个
    模板列表
    * context_data: 渲染模板时用到的上下文数据，必须是一个dict
    * rendered_content: 使用当前的模板和上下文数据渲染出来的响应内容
    * is_rendered: 一个布尔值，表示响应内容是否已经渲染

方法：
* __init__(template, context=None, content_type=None, status=None, charset=None, using=None)
    * template
    * context
    * content_type
    * status
    * charset
    * using
* resolve_context(context)
    * context
* resolve_template(template)
    * template
* add_post_render_callback()
* render()


## TemplateResponse对象
***
TemplateResponse是SimpleTemplateResponse的子类，而且能知道当前的HttpRequest
方法：
* __init__(request, template, context=None, content_type=None, status=None, current_app=None, charset=None, using=None)
有三种情况会渲染TemplateResponse：
    * 使用SimpleTemplateResponse.render()方法显示渲染TemplateResponse实例的时候
    * 通过给request.content赋值显示设置响应内容的时候
    * 传递给模板响应中间件之后，响应中间件之前






























