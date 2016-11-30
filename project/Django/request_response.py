HttpRequest对象
	属性：
		request.scheme: 可以用来判断请求的方案，http还是https
		request.body: 一个字节字符串，表示原始HTTP请求的正文，对于处理非HTML形式的数据非常有用，像是二进制图片、XML等
		request.path: 一个字符串，表示请求的页面的完整路径，不包含域名
		request.path_info: 将始终包含路径信息部分，不论使用的Web服务器是什么
		request.method: 一个字符串，表示请求使用的HTTP方法，必须使用大写
		request.encoding: 一个字符串，表示提交的数据的编码方式
		request.GET: 一个类似字典的对象，包含GET所有的参数
		request.POST: 一个包含所有POST参数的类字典对象
		request.COOKIES: 一个标准的Python字典，包含所有的cookie，键和值都为字符串
		request.FILES: 一个类似字典的对象，包含所有上传的文件
		request.META: 一个标准的Python字典，包含所有的HTTP头部
		request.user: 一个AUTH_USER_MODEL类型的对象，表示当前登录的用户
		request.session: 一个既可读又可写的类似于字典的对象，表示当前的会话
		request.urlconf: 不是Django自身定义的
		reuqest.resolver_match: 一个ResolverMatch的实例
	
	方法：
		request.get_host()
		request.get_full_path()
		request.build_absolute_uri(location)
		request.get_signed_cookie(key, default=RAISE_ERROR, salt='', max_age=None)
		request.is_secure()
		request.is_ajax()
		request.read*()





HttpResponse对象
	属性：
		response.content: 一个用来代替content的字节字符串
		response.charset: 一个字符串，用来表示response将会被编码的字符集
		response.status_code: 响应的状态码
		response.reason_phrase: The HTTP reason phrase for the response
		response.streaming: 这个选项总是False
		response.closed: 如果响应被关闭则为True
	方法：
		response.__init__(content='', content_type=None, status=200, reason=None, charset=None)
			使用页面的内容(content)和content_type来实例化一个HttpResponse对象
		response.__setitem__(header, value): 由给定的首部名称和值设定相应的报文首部
		response.__delitem__(header): 根据给定的首部名称来删除报文中的首部，如果首部不存在将沉默的失败
		response.__getitem__(header): 根据首部名称返回其值，不区分大小写
		response.has_header(header): 通过检查首部中是否有给定的首部名称，来返回True或False
		response.setdefault(header, value): 设置一个首部，除非该首部header已经存在了
		response.set_cookie(key, value='', max_age=None, expires=None, path='/', domain=None, secure=None, httponly=False): 设置cookie
		response.set_signed_cookie(key, value, salt='', max_age=None, expires=None, path='/', domain=None, secure=None, httponly=True): 与set_cookie类似，但是在设置之前将用密钥签名
		response.delete_cookie(key, path='/', domain=None): 删除指定key的Cookie，如果key不存在则什么也不发生
		response.write(content): 此方法使HttpResponse实例是一个类似文件的对象
		response.flush(): 此方法使HttpResponse实例是一个类似文件的对象
		response.tell(): 此方法使HttpResponse实例是一个类似文件的对象
		response.getvalue(): 返回HttpResponse.content的值，此方法使HttpResponse实例是一个类似流的对象
		response.writable(): 始终为True，此方法使HttpResponse实例是一个类似流的对象
		response.writelines(lines): 将一个包含行的列表写入响应，不添加行分隔符，此方法使HttpResponse实例是一个类似流的对象



HttpResponse的子类
这些衍生类存在于django.http之中
	class HttpResponseRedirect()
	class HttpResponsePermanentRedirect()
	class HttpResponseNotModified()
	class HttpResponseBadRequest()
	class HttpResponseNotFound()
	class HttpResponseForbidden()
	class HttpResponseNotAllowed()
	class HttpResponseGone()
	class HttpResponseServerError()

	class JsonResponse()
	class StreamingHttpResponse()
	class FileResponse()


QueryDict对象：
class QueryDict():
	__init__(query_string=None, mutable=False, encoding=None)
	__getitem__(key)
	__setitem__(key, value)
	__contains__(key)
	get(key, default)
	setdefault(key, default)
	update(other_dict)
	items()
	iteritems()
	iterlists()
	values()
	itervalues()
	copy()
	getlist(key, default)
	setlist(key, list_)
	appendlist(key, item)
	setlistdefault(key, default_list)
	lists()
	pop(key)
	popitem()
	dict()
	urlencode([safe])

















