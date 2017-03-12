#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


/**
 * 线程同步：互斥量
 * 临界区：是指访问某一共享资源的代码片段，并且这段代码的执行应该是原子操作。
 *
 * 为了避免在某个线程进入临界区时，被其他线程中断，必须使用互斥量。来确保同时只有一个线程可以访问某项共享资源。
 * 可以使用互斥量来保证对临界区的原子操作。
 *
 * 互斥量有两种状态：已锁定和未锁定。
 * 任何时候，至多只有一个线程可以锁住该互斥量。视图对已经锁定的某一互斥量再次加锁，将可能阻塞线程或者报错失败。
 *
 * 互斥量类型：
 * pthread_mutex_t
 * pthread_mutexattr_t
 *
 * 加锁或解锁互斥量：
 * #include <pthread.h>
 * int pthread_mutex_lock(pthread_mutex_t *mtx);
 * int pthread_mutex_unlock(pthread_mutex_t *mtx);
 * 			返回值：若成功，返回0，若失败，返回一个正数
 * 变体：
 * 		pthread_mutex_trylock()
 * 		pthread_mutex_timedlock()
 *
 * 
 * 动态初始化互斥量：如果要指定互斥量的属性
 * #include <pthread.h>
 * int pthread_mutex_init(pthread_mutex_t *mtx, const ptherad_mutexattr_t *attr);
 * int pthread_mutex_destroy(pthread_mutex_t *mtx);
 * 			返回值：若成功，返回0，若失败，返回一个正数
 */
static int share = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;   // 静态初始化互斥量值

void *subthread_with_lock(void *arg)
{
	int i = 0;
	int ret = 0;

	ret = pthread_mutex_lock(&mtx);    // 对互斥量加锁
	if(ret != 0)
	{
		printf("对互斥量加锁失败\n");
		_exit(EXIT_FAILURE);
	}

	for(i = 0; i < 1000000; i++)
	{
		share += 1;
	}


	ret = pthread_mutex_unlock(&mtx);  // 对互斥量解锁
	if(ret != 0)
	{
		printf("对互斥量解锁失败\n");
		_exit(EXIT_FAILURE);
	}

	return (void *)EXIT_SUCCESS;
}

void *subthread(void *arg)
{
	// 子线程对一个共享资源持续加1
	int i = 0;

	for(i = 0; i < 1000000; i++)
		share += 1;

	return (void *)EXIT_SUCCESS;
}


int main(int argc, char const *argv[])
{
	int i;
	int ret;
	pthread_t tid;

	printf("共享变量的初值是： %d\n", share);

	for(i = 0; i < 10; i++)
	{
		/**
		 * 创建10个子线程对共享资源加1
		 */
		// ret = pthread_create(&tid, NULL, subthread, NULL);
		ret = pthread_create(&tid, NULL, subthread_with_lock, NULL);
		if(ret != 0)
		{
			printf("创建子线程失败\n");
			_exit(EXIT_FAILURE);
		}
	}

	sleep(10); // 主线程休眠5秒，等待子线程都结束

	printf("共享变量最终的值是： %d\n", share);

	return 0;
}