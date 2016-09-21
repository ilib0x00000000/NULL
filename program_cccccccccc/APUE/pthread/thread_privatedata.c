#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<limits.h>
#include<pthread.h>

/**
 * 线程特定数据（线程私有数据）：是存储和查询某个特定线程相关数据的一种机制
 * 在分配线程特定数据前，需要创建与该数据相关联的键，这个键将用于获取对线程特定数据的访问
 * int pthread_key_create(pthread_key_t *keyp, void (*destructor)(void *));
 * 除了创建键以外，pthread_key_create可以为该键关联一个可选择的析构函数，线程退出时，如果数据被置为非空值，则析构函数会被调用
 *
 * 对于所有线程，可以通过调用pthread_key_delete来取消键与线程特定数据值之间的关联关系
 * int pthread_key_delete(pthread_key_t key);
 *
 * pthread_once_t intflag = PTHREAD_ONCE_INIT;
 * int pthread_key_once(pthread_once_t *intflag, void (*intfn)(void));
 *
 * 键创建之后，可以通过pthread_getspecific函数获得线程特定数据的地址
 * pthread_setspecific函数把键和线程特定数据关联起来
 * void *pthread_getspecific(pthread_key_t key);
 * int   pthread_setspecific(pthread_key_t key, const void *value);

 * 在单线程程序中，全局变量可以实现多个函数间共享数据。在多线程环境中，由于数据空间是共享的，因此全局
 * 变量也是为所有线程共享的。现在有一全局变量，所有线程都可以使用它，改变它的值。而如果每个线程希望能
 * 单独拥有它，那就需要使用线程存储了。表面上看起来这是一个全局变量，所有线程都可以使用它，而它的值在
 * 每一个线程中又是单独存储的。这就是线程存储的意义
 *
 * 1.创建一个类型为pthread_key_t类型的变量
 * 2.调用pthread_key_create()来创建该变量，该函数有两个参数，一个是pthread_key_t变量，另一个是析构回调函数
 * 3.当线程中需要存储特殊值的时候，可以调用pthread_setspecific()函数，该函数有两个参数，第一个是
 * pthread_key_t变量，第二个是void *变量，这样可以存储任何类型的值
 * 4.如果需要取出所存储的值，调用pthread_getspecific()函数，参数为pthread_key_t变量，返回值为void *类型。
 * 5.调用pthread_key_delete()函数来取消键与特定线程之间的数据关联
 */

pthread_key_t key;

void *child1(void *arg);
void *child2(void *arg);
void echomsg(void *arg);

int main(int argc, char const *argv[])
{
	long tid1;
	long tid2;

	printf("hello\n");

	pthread_key_create(&key, echomsg);      // 创建一个键，并指定析构函数
	pthread_create(&tid1, NULL, child1, NULL);
	pthread_create(&tid2, NULL, child2, NULL);
	sleep(10);
	pthread_key_delete(key);
	printf("main thread exit\n");

	return 0;
}

void *child2(void *arg)
{
	long tid = pthread_self();
	printf("thread %d enter\n", tid);
	pthread_setspecific(key, (void *)tid);			// 设置此线程的私有数据
	sleep(1);
	printf("thread %ld returns %ld\n", tid, (long)pthread_getspecific(key)); // 获取此线程的私有数据
	sleep(5);
}

void *child1(void *arg)
{
	long tid = pthread_self();
	printf("thread %d enter\n", tid);
	pthread_setspecific(key, (void *)tid);
	sleep(2);
	printf("thread %ld returns %ld\n", tid, (long)pthread_getspecific(key));
	sleep(5);
}

void echomsg(void *arg)
{
	printf("thread: %ld exit\n", pthread_self());
}