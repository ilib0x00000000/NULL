#include<time.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

/*
条件变量被用来阻塞一个线程，当条件不满足时，线程往往解开相应的互斥锁并等待条件发生变化。
一旦其他的某个线程改变了条件变量，他通知相应的条件变量唤醒一个或多个正在被此条件变量阻塞的线程
pthread_cond_signal
pthread_cond_broadcast
条件变量只是起阻塞和唤醒线程的作用，具体的判断条件还是要用户给出
线程被唤醒后，重新判断条件是否满足，如果不满足，一般线程应该仍阻塞在这里，等待被下一次唤醒
*/

int count = 5;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *decrement(void *arg);
void *increment(void *arg);

int main(int argc, char const *argv[])
{
	int i1 = 1;
	int i2 = 1;
	pthread_t tid1;
	pthread_t tid2;

	pthread_mutex_init(&mutex, NULL);			// 初始化一个互斥量
	pthread_cond_init(&cond, NULL);				// 初始化一个条件变量

	pthread_create(&tid1, NULL, decrement, NULL);
	pthread_create(&tid2, NULL, increment, NULL);

	i2 = pthread_join(tid2, NULL);
	i1 = pthread_join(tid1, NULL);

	if( (i1==0) && (i2==0))
	{
		printf("count = %d, the main thread!\n", count);
		pthread_cond_destroy(&cond);
		pthread_mutex_destroy(&mutex);
	}
	
	return 0;
}

void *increment(void *arg)
{
	sleep(1);

	while(1)
	{
		pthread_mutex_lock(&mutex);

		count += 1;
		if(count > 0)
		{
			printf("count = %d, change cond state!\n", count);
			pthread_cond_signal(&cond);					// 唤醒等待线程
		}

		pthread_mutex_unlock(&mutex);

		if(count == 10)
		{
			printf("count = 10, thread 2 is over!\n");
			return NULL;
		}
	}
}

void *decrement(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);						// 对互斥量加锁

		while(count <= 0)
		{
			printf("count <= 0,thread1 is hanging\n");
			pthread_cond_wait(&cond, &mutex);			// 阻塞，等待条件变量，释放互斥量
			sleep(1);
			printf("sleep!\n");
		}
		count -= 1;

		pthread_mutex_unlock(&mutex);

		if(count == 9)
		{
			printf("count = 9, thread 1 is over\n");
			return NULL;
		}
	}
}