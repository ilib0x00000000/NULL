#include<errno.h>
#include<sys/time.h>

#include"apue.h"

/**
 * 进程调度：调度策略和调度优先级是由内核确定的，进程可以通过调整nice值选择更低优先级运行，
 * 通过调整nice值降低它对CPU的占有，只有特权进程允许提高调度权限。
 *
 * #include<unistd.h>
 * int nice(int incr);
 *
 * nice值越小，优先级越高
 *
 * getpriority函数可以获取进程的nice值，但是getpriority还可以获取一组相关进程的nice值。
 * #include<sys/resource.h>
 * int getpriority(int which, id_t who);
 * int setpriority(int which, id_t who, int value);
 *
 * which的取值：
 * 		PRIO_PROCESS: 表示进程
 * 		PRIO_PGRP:    表示进程组
 * 		PRIO_USER: 	  表示用户ID
 *
 * NZERO是系统默认的nice值，有些实现支持0-2*NZERO
 */

#if defined(MACOS)
#include<sys/syslimits.h>
#elif defined(SOLARIS)
#include<limits.h>
#elif defined(BSD)
#include<sys/param.h>
#endif


int main(int argc, char const *argv[])
{
	int nzero;
	int ret;
	int adj = 0;
	char *s;
	pid_t pid;

	setbuf(stdout, NULL);
	
#if defined(NZERO)
	nzero = NZERO;
#elif defined(_SC_NZERO)
	nzero = sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif

	printf("NZERO = %d\n", nzero);

	if(argc == 2)
	{
		adj = strtol(argv[1], NULL, 10);
	}

	gettimeofday(&end, NULL);
	end.tv_sec += 10;

	if((pid=fork()) < 0)
	{
		perror("fork error");
	}else
	if(pid == 0)
	{
		// 子进程中
		s = "child";

		printf("current nice value in child is %d, adjusting by %d\n", nice(0)+nzero, adj);
		errno = 0;
		/**
		 * int nice(int incr);
		 * 返回值：若成功，返回新的nice值NZERO，若出错，返回-1
		 * 由于-1是合法的返回值，因此在调用之前因设定errno的值为0，然后检查errno的值是否改变，以判断是否函数调用成功
		 */
		if((ret=nice(adj)) == -1 && errno != 0)
		{
			perror("child set scheduing priority");
		}

		printf("now child nice value is %d\n", ret+nzero);
	}else{
		s = "parent";

		printf("current nice value in parent is %d\n", nice(0)+nzero);
	}

	return 0;
}
