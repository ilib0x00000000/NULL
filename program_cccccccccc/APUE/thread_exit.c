#include<stdio.h>
#include<error.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

/**
 * 线程终止：如果进程中的任意线程调用了exit,_Exit或者_exit，那么整个进程就会终止。
 * 线程有3种方式可以在不终止整个进程的情况下退出，停止控制流。
 * 			1.线程可以简单的从启动例程中返回，返回值是线程的退出码。
 * 			2.线程可以被同一进程中的其他线程取消。
 * 			3.线程调用pthread_exit。
 *
 * #include<pthread.h>
 * void pthread_exit(void *rval_ptr);
 *
 * int pthread_join(pthread_t thread, void **rval_ptr);
 * 							返回值：若成功，返回0，否则，返回错误编号
 *
 * 调用线程将一直阻塞，直到指定的线程调用pthread_exit、从启动例程中返回或者被取消。
 * 如果线程简单的从它的启动例程返回，rval_ptr就包含返回码。
 * 如果线程被取消，由rval_ptr指定的内存单元就设置为PTHREAD_CANCELED。
 *
 * 可以通过调用pthread_join自动将线程设置于分离状态，这样资源就可以恢复。
 * 如果线程已经处于分离状态，pthread_join调用就会失败，返回EINVAL。
 */

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
		perror("can't create thread");

	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if(err != 0)
		perror("can't create thread");

	err = pthread_join(tid1, &tret);		// 等待线程1执行完
	if(err != 0)
		perror("can't join with thread 1");
	printf("thread1 exit code : %ld\n", (long)tret);

	err = pthread_join(tid2, &tret);		// 等待线程2执行完
	if(err != 0)
		perror("can't join with thread 2");
	printf("thread2 exit code : %ld\n", (long)tret);

	return 0;
}

void *thr_fn1(void *arg)
{
	printf("thread 1 returning\n");
	sleep(4);
	return (void *)1;
}

void *thr_fn2(void *arg)
{
	printf("thread 2 exiting\n");
	sleep(2);
	pthread_exit((void *)2);
}
