#include<sys/resource.h>

#include"apue.h"
/**
 * 每个进程都有一组资源限制，其中一些可以用getrlimit和setrlimit函数查询和更改
 * #include<sys/resource.h>
 * int getrlimit(int resource, struct rlimit *rlptr)
 * int setrlimit(int resource, const struct rlimit *rlptr)
 *
 * struct rlimit{
 * 		rlim_t rlim_cur;  // 软限制值 实现是unsigned long long/unsigned long
 * 		rlim_t rlim_max;  // 硬限制值 实现是unsigned long long/unsigned long
 * }
 *
 * 在更改资源时，须遵循以下3个规则：
 * 	1.任何一个进程都可以将一个软限制值更改为小于或等于其硬限制值
 * 	2.任何一个进程都可以降低其硬限制值，但它必须大于或等于其软限制值，这种降低，对普通用户是不可逆的
 * 	3.只有root用户可以提高硬限制值
 *
 * resource的取值如下(与内核实现有关)：
 * 		RLIMIT_AS: 进程总的可用存储空间的最大长度，这影响到sbrk函数和mmap函数
 * 		RLIMIT_CORE: core文件的最大字节数，若其值为0则阻止创建core文件
 * 		RLIMIT_CPU: CPU时间的最大量值，当超过此限制时，向该线程发送SIGXCPU信号
 * 		RLIMIT_DATA: 数据段的最大字节长度，为初始化数据，未初始化数据和堆的总和
 * 		RLIMIT_FSIZE: 可以创建的文件的最大字节长度，当超过此限制时，向该线程发送SIGXFSZ信号
 * 		RLIMIT_MEMLOCK: 一个进程使用mlock能够锁定在存储空间中的最大字节长度
 * 		RLIMIT_MSGQUEUE: 进程为POSIX消息队列可分配的最大存储字节数
 * 		RLIMIT_NICE: 为了影响进程的调度优先级，nice值可设置的最大值
 *
 * 		RLIMIT_NOFILE: 每个进程能打开的最多文件数，更改此值将影响到sysconf函数在参数_SC_OPEN_MAX中返回的值
 * 		RLIMIT_NPROC: 每个实际用户ID可拥有的最大子进程数，更改此值将影响到sysconf函数_SC_CHILD_MAX返回的值
 * 		RLIMIT_NPTS: 用户可同时打开的伪终端的最大数量
 * 		RLIMIT_RSS: 最大驻内存集字节长度，如果可用的物理存储器非常少，则内核将从进程处取回超过RSS的部分
 * 		RLIMIT_SIGPENDING: 一个进程可排队的信号最大数量
 * 		RLIMIT_STACK: 栈的最大字节长度
 */

#define doit(name) pr_limits(#name, name)

static void pr_limits(char *, int);

int main(int argc, char const *argv[])
{
	#ifdef RLIMIT_AS
		doit(RLIMIT_AS);
	#endif

	doit(RLIMIT_CORE);
	doit(RLIMIT_CPU);
	doit(RLIMIT_DATA);
	doit(RLIMIT_FSIZE);
	doit(RLIMIT_STACK);
	
	#ifdef RLIMIT_MEMLOCK
		doit(RLIMIT_MEMLOCK);
	#endif

	#ifdef RLIMIT_MSGQUEUE
		doit(RLIMIT_MSGQUEUE);
	#endif

	#ifdef RLIMIT_NICE
		doit(RLIMIT_NICE);
	#endif

	#ifdef RLIMIT_NPROC
		doit(RLIMIT_NPROC);
	#endif

	#ifdef RLIMIT_RSS
		doit(RLIMIT_RSS);
	#endif

	#ifdef RLIMIT_SIGPENDING
		doit(RLIMIT_SIGPENDING);
	#endif


	return 0;
}

static void pr_limits(char *name, int resource)
{
	struct rlimit limit;
	unsigned long long lim;

	if(getrlimit(resource, &limit) < 0)
	{
		printf("error\n");
		exit(0);
	}

	printf("%-14s  ", name);

	if(limit.rlim_cur == RLIM_INFINITY)
	{
		printf("(infinite)");
	}else
	{
		lim = limit.rlim_cur;
		printf("%10lld  ", lim);
	}

	if(limit.rlim_max == RLIM_INFINITY)
	{
		printf("(infinite)");
	}else
	{
		lim = limit.rlim_max;
		printf("%10lld  ", lim);
	}
	printf("\n");
}


/**
 * Ubuntu 14.04 LTS X86_64
 * Linux 4.4.0-36-generic
 * output:
 * RLIMIT_AS       (infinite)  (infinite)
 * RLIMIT_CORE              0  (infinite)
 * RLIMIT_CPU      (infinite)  (infinite)
 * RLIMIT_DATA     (infinite)  (infinite)
 * RLIMIT_FSIZE    (infinite)  (infinite)
 * RLIMIT_STACK       8388608  (infinite)
 * RLIMIT_MEMLOCK       65536       65536  
 * RLIMIT_MSGQUEUE     819200      819200  
 * RLIMIT_NICE              0           0  
 * RLIMIT_NPROC         23435       23435  
 * RLIMIT_RSS      	(infinite)  (infinite)
 * RLIMIT_SIGPENDING     23435       23435 
 */