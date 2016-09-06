#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

/**
 * 多线程：
 * #include<pthread.h>
 * int pthread_equal(pthread_t tid1, pthread_t tid2);
 * 								返回值：若相等，返回非0值，否则，返回0
 *
 * #include<pthread.h>
 * pthread_t pthread_self(void);
 * 								返回值：调用线程的线程ID
 *
 * #include<pthread.h>
 * int pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, 
 * 						void *(*start_rtn)(void *), void *restrict arg);
 * 								返回值：若成功，返回0，否则，返回错误编号 
 */

pthread_t ntid;

void printids(const char *s);
void *thr_fn(void *arg);

int main(int argc, char const *argv[])
{
	int err;

	err = pthread_create(&ntid, NULL, thr_fn, NULL);	// 创建一个线程
	if(err != 0)
		perror("can't create thread");

	printids("main thread: ");
	sleep(1);

	return 0;
}


void printids(const char *s)
{
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	printf("%s pid: %lu,  tid:%lu,  (0x%lx)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

void *thr_fn(void *arg)
{
	printids("new thread: ");

	return (void *)0;
}

/**
 * 编译多线程程序的命令： gcc -o file_name resource.c -l pthread
 */