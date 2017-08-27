打包静态库/动态库
*************************************************************************************************
1. gcc编译
	1.1> -I dir     指定自定义的头文件目录
	1.2> -D xxxx    定义宏
	1.3> -c         生成二进制文件.o
	1.4> -Wall      输出警告信息
	1.5> -g         使用gdb调试
	1.6> libxxx.a   使用静态库中的函数
	1.7> -L lib -l xxx     -L指定静态库的目录 -l指定静态库的名字 



2. 静态库
	2.1> 命名规则    lib+库名+.a   例如： libtouch.a
	2.2> 生成静态库
			1. 生成.o    $ gcc -c *.c
			2. .o  --> libxxx.a    使用工具ar  $ar rcs libxxx.a  (all).o
	2.3> 发布静态库
			1. 静态库
			2. 头文件    暴露接口
	2.4> 查看静态库内容    nm libxxx.a   nm也可以查看可执行文件
	2.5> 静态库被打包到可执行文件中了，库的加载速度比较快，如果库代码修改，需要重新编译文件



3. 动态库（共享库） share object
	3.1> 命名规则    lib+库名+.so    例如： libdynamic.so
	3.2> 生成动态库
			1. 生成位置无关的代码 .o     $ gcc -fPIC -c *.c
			2. 将.o生成动态库           $ gcc -shared libxxx.so *.o
	3.3> 发布动态库
			1. libxxx.so
			2. 头文件
	3.4> 使用动态库    gcc dir/libxxx.so  -o ... -I (头文件目录)
	                  gcc -Ldir -lxxxx ...      // dir动态库所在的目录  xxxx动态库的名字
	3.5> ldd exe 查看可执行程序所依赖的动态库  动态连接器 /lib64/ld
	3.6> 动态链接器根据环境变量查找so库，   /lib   ---> 存放动态库
	      解决动态库找不到的方法：
	      		1. 将自己创建的动态库拷贝到/lib下面
	      		2. $export LD_LIBRARY_PATH=dir/.....      将自定义的so动态库路径加到环境变量LD_LIBRARY_PATH中
	      		3. $vim .bashrc  新增环境变量   export LD_LIBRARY_PATH=.../dir/.....
	      		   $source
	      		4. 动态链接器配置文件 #sudo vim /etc/ld.so.conf   更新文件 #sudo ldconfig -v