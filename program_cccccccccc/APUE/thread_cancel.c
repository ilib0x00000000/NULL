#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

/**
 * 线程可以通过调用pthread_cancel()函数来请求取消同一进程中的其他线程
 * #include<pthread.h>
 * int pthread_cancel(pthread_t tid);
 * 						返回值：若成功，返回0，若失败，返回错误编号
 *
 * 线程清理处理程序
 * #include<pthread.h>
 * void pthread_cleanup_push(void (*rtn)(void *), void *arg);
 * void pthread_cleanup_pop(int execute);
 */

void cleanup(void *arg);
void *thr_fn1(void *arg);
void *thr_fn2(void *arg);

int main(int argc, char const *argv[])
{
	int err;
	void *tret;
	pthread_t tid1;
	pthread_t tid2;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if(err != 0)
		perror("pthread_create error");

	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if(err != 0)
		perror("pthread_create error");

	err = pthread_join(tid1, &tret);
	if(err != 0)
		perror("pthread_join error");
	printf("thread1 exit code: %ld\n", (long)tret);

	err = pthread_join(tid2, &tret);
	if(err != 0)
		perror("pthread_join error");
	printf("thread2 exit code: %ld\n", (long)tret);

	return 0;
}

void *thr_fn1(void *arg)
{
	printf("thread1 start\n");

	pthread_cleanup_push(cleanup, "thread 1 first handler");
	pthread_cleanup_push(cleanup, "thread 1 second handler");

	printf("thread1 push complete\n");

	if(arg)
		return (void *)1;

	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);

	return (void *)0;
}

void *thr_fn2(void *arg)
{
	printf("thread2 start\n");

	pthread_cleanup_push(cleanup, "thread 2 first handler");
	pthread_cleanup_push(cleanup, "thread 2 second handler");

	printf("thread2 push complete\n");

	if(arg)
		pthread_exit((void *)2);

	pthread_cleanup_pop(0);		// pthread_cleanup_pop()将删除上次pthread_cleanup_push调用建立的清理处理程序
	pthread_cleanup_pop(0);

	pthread_exit((void *)2);
}

void cleanup(void *arg)
{
	printf("cleanup: %s\n", (char *)arg);
}
