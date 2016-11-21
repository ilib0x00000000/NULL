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

## QueryDict对象
***















