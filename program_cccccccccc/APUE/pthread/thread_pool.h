#ifndef _THREADPOOL_H
#define _THREADPOOL_H

typedef struct runner
{
	void *(*callback)(void *arg);
	void *arg;
	struct runner *next;
}thread_runner;

/**
 * 线程池数据结构
 */
typedef struct
{
	int shutdown;                  // 线程池是否销毁
	int max_thread_size;           // 线程池中允许的活动线程数目
	pthread_t *threads;            // 所有线程
	pthread_mutex_t mutex;         // 互斥量
	pthread_cond_t  cond;          // 条件变量
	thread_runner  *runner_head;   // 线程池中所有等待任务的头指针
	thread_runner  *runner_tail;   // 线程池中所有等待任务的尾指针
}thread_pool;

/*创建线程时，各线程执行的函数，主要是等待任务池的条件变量信号*/
void *run(void *arg);
void *run(void *arg)
{
	thread_pool *pool = (thread_pool *)arg;
	thread_runner *runner = NULL;

	while(1)
	{
		pthread_mutex_lock(&(pool->mutex));   // 加锁
		#ifdef DEBUG
		printf("run -> locked\n");
		#endif

		while(pool->runner_head == NULL && !pool->shutdown)
		{
			// 如果等待队列为0并且线程池未销毁，则处于阻塞状态
			pthread_cond_wait(&(pool->cond), &(pool->mutex));
		}

		if(pool->shutdown)  // 如果线程池已经销毁
		{
			pthread_mutex_unlock(&(pool->mutex));  // 解锁
			#ifdef DEBUG
			printf("run -> unlocked and thread exit\n");
			#endif
			pthread_exit(NULL);
		}

		runner = pool->runner_head;
		pool->runner_head = runner->next;

		pthread_mutex_unlock(&(pool->mutex));   // 解锁
		#ifdef DEBUG
		printf("run -> unlocked\n");
		#endif

		(runner->callback)(runner->arg);        // 调用回调函数

		#ifdef DEBUG
		printf("run -> runned and free runner\n");
		#endif
	}

	pthread_exit(NULL);
}

/*初始化线程池*/
void threadpool_init(thread_pool *pool, int max_thread_size);
void threadpool_init(thread_pool *pool, int max_thread_size)
{
	int i;
	pthread_attr_t attr;

	pthread_mutex_init(&(pool->mutex), NULL);        // 初始化互斥量
	pthread_cond_init(&(pool->cond), NULL);          // 初始化条件变量
	pool->runner_head = NULL;
	pool->runner_tail = NULL;
	pool->max_thread_size = max_thread_size;
	pool->shutdown = 0;
	/*创建所有分离态线程*/
	pool->threads = (pthread_t *)malloc(max_thread_size * sizeof(pthread_t));
	for(i = 0; i < max_thread_size; i++)
	{
		pthread_attr_init(&attr);                   // 初始化线程的属性
		pthread_attr_setdetachstat(&attr, PTHREAD_CREATE_DETACHED);
		pthread_create(&(pool->threads[i]), &attr, run, (void *)pool);
	}

	#ifdef DEBUG
	printf("threadpool create %d detached thread\n", max_thread_size);
	#endif
}

/*向线程池中加入任务*/
void threadpool_add_runner(thread_pool *pool, void *(*callback)(void *arg), void *arg);
void threadpool_add_runner(thread_pool *pool, void *(*callback)(void *arg), void *arg)
{
	// 构造一个新任务
	thread_runner *newrunner = (thread_runner *)malloc(sizeof(thread_runner));
	newrunner -> callback = callback;
	newrunner -> arg = arg;
	newrunner -> next = NULL;

	// 加锁
	pthread_mutex_lock(&(pool->mutex));

	#ifdef DEBUG
	printf("threadpool_add_runner locked\n");
	#endif

	// 将任务加入到等待队列中
	if(pool->runner_head != NULL)
	{
		pool->runner_tail->next = newrunner;
		pool->runner_tail = newrunner;
	}else
	{
		pool->runner_head = newrunner;
		pool->runner_tail = newrunner;
	}

	// 解锁
	pthread_mutex_unlock(&(pool->mutex));

	#ifdef DEBUG
	printf("threadpool_add_runner unlocked\n");
	#endif

	// 唤醒一个等待线程
	pthread_cond_signal(&(pool->cond));
}

/*销毁线程池*/
void threadpool_destroy(thread_pool **ppool);
void threadpool_destroy(thread_pool **ppool)
{
	thread_pool *pool = *ppool;
	thread_runner *head = NULL;

	if(!pool->shutdown)
	{
		pool->shutdown = 1;

		// 唤醒所有等待线程，线程池要销毁了
		pthread_cond_broadcast(&(pool->cond));

		// 等待所有线程终止
		sleep(1);

		free(pool->threads);

		while(pool->runner_head != NULL)
		{
			head = pool->runner_head;
			pool->runner_head = pool->runner_head->next;
			free(head);
		}

		pthread_mutex_destroy(&(pool->mutex));
		pthread_cond_destroy(&(pool->cond));

		free(pool);
		(*ppool) = NULL;
	}
}

#endif