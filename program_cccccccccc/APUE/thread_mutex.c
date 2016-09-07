#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

/**
 * 线程互斥量：互斥量就是一个数据结构，可以被包含在一个结构体中。
 * #include<pthread.h>
 * int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
 * int pthread_mutex_destroy(pthread_mutex_t *mutex);
 * 								返回值：若成功，返回0，否则，返回错误编号。
 *
 * 锁：
 * int pthread_mutex_lock(pthread_mutex_t *mutex);
 * int pthread_mutex_trylock(pthread_mutex_t *mutex);
 * int pthread_mutex_unlock(pthread_mutex_t *mutex);
 * 								返回值：若成功，返回0，否则，返回错误编号。
 */

struct foo{
	int f_count;
	int f_id;
	pthread_mutex_t f_lock;
};

struct foo *foo_alloc(int id);
void foo_hold(struct foo *fp);
void foo_rele(struct foo *fp);

void foo_rele(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);

	if(--fp->f_lock == 0){
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	}
	else{
		pthread_mutex_unlock(&fp->f_lock);
	}
}

void foo_hold(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);				// 对互斥量加锁
	fp->f_count ++;
	pthread_mutex_unlock(&fp->f_lock);				// 对互斥量释放锁
}

struct foo *foo_alloc(int id)
{
	struct foo *fp;

	if( (fp = malloc(sizeof(struct foo))) != NULL)
	{
		fp->f_count = 1;
		fp->f_id = id;
		if(pthread_mutex_init(&fp->f_lock, NULL) != 0)		// 初始化一个互斥量
		{
			free(fp);
			return NULL;
		}
	}

	return fp;
}

/**
 * 互斥量与锁：
 * 		1.创建一个互斥量
 * 		2.初始化该互斥量
 * 		3.对互斥量加锁
 * 		4.执行代码
 * 		5.释放互斥量的锁
 * 		6.销毁互斥量
 */