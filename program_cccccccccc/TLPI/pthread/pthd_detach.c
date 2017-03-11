#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


/**
 * 在任意一个时间点上，线程是可连接的(join)或者是可分离的(detached)。
 * 一个可连接的线程是可以被其他线程收回资源和杀死的。在被收回之前，该线程的存储器资源（栈等）是不释放的。
 * 而对于detached状态的线程，其资源不能被别的线程收回和杀死，只有等到线程结束才能由系统自动释放
 *
 * 默认情况下，线程状态被设置为可连接的。所以为了避免资源泄漏等问题，一个线程应当是被显式的join或者detach的，否则就变成了僵尸线程
 *
 * 当某个线程调用pthread_join()时，如果被连接的线程没有终止，调用线程就会被阻塞。
 * 如果不需要线程的返回值，可以调用pthread_detach(tid)避免僵尸线程且不阻塞某个线程
 *
 * 其他线程调用了exit()，或者主线程执行return语句时，可连接或分离线程都会立即终止。
 */

/**
 * #include <pthread.h>
 * int pthread_detach(pthread_t tid);
 * 			返回值：若成功，返回0，若失败，返回一个正值
 *
 * int pthread_join(pthread_t thread, void **retval);   一直阻塞调用，直到连接的线程终止
 * 			返回值：若成功，返回0，若失败，返回一个正值
 */


void *subthread(void *arg)
{
	// 将线程自己设置成分离线程
	int ret;

	ret = pthread_detach(pthread_self());

	if(ret != 0)
	{
		printf("设置分离线程失败\n");
		pthread_exit((void *)EXIT_FAILURE);
	}


	return (void *)EXIT_SUCCESS;
}


int main(int argc, char const *argv[])
{
	int ret;
	pthread_t tid;

	ret = pthread_create(&tid, NULL, subthread, NULL);
	if(ret != 0)
	{
		printf("创建子进程失败\n");
		_exit(EXIT_FAILURE);
	}

	sleep(1);

	ret = pthread_join(tid, NULL);  // 连接指定的子线程，这里的调用会失败，因为该子线程被设置成分离的
	if(ret != 0)
	{
		printf("连接子线程失败，因为该线程已经是分离的线程\n");
	}

	return 0;
}

