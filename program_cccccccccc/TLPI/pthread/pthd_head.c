#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


/**
 * Linux两种主流的线程实现：
 * 	1. LinuxThreads
 * 	2. NativePOSIXThreadsLibrary   NPTL
 *
 * 同一程序中的所有线程均会独立执行相同程序，且共享同一份全局内存区域，其中包括初始化数据段，未初始化数据段，以及堆内存段。
 *
 * 线程共享：
 * 		* 进程ID和父进程ID
 * 		* 进程组ID与会话ID
 * 		* 控制终端
 * 		* 进程凭证
 * 		* 打开的文件描述符
 * 		* 由fcntl()创建的记录锁
 * 		* 信号处置
 * 		* 文件系统相关信息：文件权限掩码、当前工作目录和根目录
 * 		* 间隔定时器和POSIX定时器
 * 		* System V信号量撤销值
 * 		* 资源限制
 * 		* CPU时间消耗
 * 		* 资源消耗
 * 		* nice值
 * 线程独占：
 * 		* 线程ID
 * 		* 信号掩码
 * 		* 线程特有数据
 * 		* 备选信号栈
 * 		* errno变量
 * 		* 浮点型环境
 * 		* 实时调度策略和优先级
 * 		* CPU亲和力
 * 		* 能力
 * 		* 栈
 */

void *subthread(void *arg)
{
	// int retval;
	pthread_t self;



	printf("在子进程中\n");
	
	/**
	 * 获取调用线程自己的线程ID
	 * #include <pthread.h>
	 * pthread_t pthread_self(void);
	 * 			返回值：返回调用线程的线程ID
	 */
	self = pthread_self();
	printf("当前线程的线程ID是: %ld\n", (long)self);

	
	printf("子进程执行完毕\n");

	/**
	 * 线程终止的方式：
	 * 		1. 线程start函数执行return语句并返回指定值
	 * 		2. 线程调用pthread_exit()
	 * 		3. 调用pthread_cancel()取消线程
	 * 		4. 任意线程调用了exit()，或者主线程执行了return语句，都会导致进程中的所有线程立即终止
	 *
	 * #include <pthread.h>
	 * void pthread_exit(void *retval);
	 */
	pthread_exit(arg);

	return (void *)EXIT_SUCCESS;
}


int main(int argc, char const *argv[])
{
	int ret;
	pthread_t tid;

	/**
	 * 创建一个线程
	 * #include <pthread.h>
	 * int pthread_create(pthread_t *tid, const pthread_attr_t *attr, void *(*start)(void *), void *);
	 * 			返回值：若成功，返回0，若失败，返回一个正值
	 */
	ret = pthread_create(&tid, NULL, subthread, (void *)5);
	if(ret != 0)
	{
		printf("创建子进程失败\n");
		_exit(EXIT_FAILURE);
	}


	/**
	 * 连接已终止的线程
	 * #include <pthread.h>
	 * int pthread_join(pthread_t tid, void **retval);
	 * 			返回值：若成功，返回0，若失败，返回一个正值
	 *
	 * 如果一个线程已经分离，则不能再join()
	 * pthread_join()连接一个线程时，只能阻塞调用，直到线程终止
	 * 如果调用pthread_join()时，该线程已经终止，则立即返回
	 */
	ret = pthread_join(tid, NULL);
	if(ret == 0)
	{
		printf("子线程ID： %ld 已经终止\n", (long)tid);
	}else
	{
		printf("pthread_join()调用失败\n");
	}
	

	return 0;
}







