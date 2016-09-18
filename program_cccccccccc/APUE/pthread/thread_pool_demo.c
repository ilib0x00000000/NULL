#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#include"thread_pool.h"

/**
 * 创建线程或者进程的开销是很大的，为了防止频繁的创建线程，往往都会建立一个线程池用于多线程程序
 */


typedef struct runner
{
	void *(*callback)(void *arg);		// 回调函数指针
	void *arg;                   		// 回调函数的参数
	struct runner *next;        		// 
}thread_runner;

/**
 * 线程池数据结构
 */
typedef struct
{
	int shutdown;                       // 线程池是否销毁
	int max_thread_size;                // 线程池中允许的活动线程数目
	pthread_t *threads;                 // 所有线程
	pthread_mutex_t mutex;              // 互斥量
	pthread_cond_t  cond;               // 条件变量
	thread_runner *runner_head;         // 线程池中所有等待任务的头指针
	thread_runner *runner_tail;         // 线程池中所有等待任务的尾指针
}thread_pool;

/**
 * 初始化线程池
 */
void threadpool_init(thread_pool *pool, int max_thread_size);
/**
 * 向线程池加入任务
 */
void threadpool_add_runner(thread_pool *pool, void (*callback)(void *arg), void *arg);
/**
 * 销毁线程池
 */

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}
