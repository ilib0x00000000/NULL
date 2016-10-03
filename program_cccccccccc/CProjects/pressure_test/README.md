# C语言测压工具
***
参考：https://github.com/EZLippi/WebBench
Webbench是一个在linux下使用的非常简单的网站压测工具。它使用fork()模拟多个客户端同时访问我们设定的URL，测试网站在压力下工作的性能，最多可以模拟3万个并发连接去测试网站的负载能力。

源码分析：http://blog.csdn.net/kangroger/article/details/42500703

## 2016-10-3 update(beta1)
***
代码初步编译运行成功，但是存在如下问题：
* 命令行参数解析存在问题，部分参数无法解析
* getnetbyname函数调用失败，不得不调用过期gethostbyname函数
* 源码太乱

`
./webbench --force http://www.ruanyifeng.com/blog/2015/02/make.html
`
