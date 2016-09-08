#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define NHASH 29
#define HASH(id) (((unsigned long)id) % NHASH)

struct foo{
	int f_id;
	int f_count;
	struct foo *f_next;
	pthread_mutex_t f_lock;
}

struct foo *fh[NHASH];

pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo *foo_alloc(int id);
void foo_hold(struct foo *fp);
struct foo *foo_find(int id);
void foo_rele(struct foo *fp);

int main(int argc, char const *argv[])
{

	
	return 0;
}

void foo_rele(struct foo *fp)
{
	int idx;
	struct foo *tfp;

	pthread_mutex_lock(&fp->f_lock);

	if(fp->f_count == 1)
	{
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_lock(&hashlock);
		pthread_mutex_lock(&fp->f_lock);

		if(fp->f_count != 1)
		{
			fp->f_count --;
			pthread_mutex_unlock(&fp->f_lock);
			pthread_mutex_lock(&hashlock);
			pthread_mutex_lock(&fp->f_lock);

			if(fp->f_count != 1)
			{
				fp->f_count--;
				
			}
		}
	}
}

struct foo *foo_find(int id)
{
	struct foo *fp;

	pthread_mutex_lock(&hashlock);

	for(fp=fh[HASH(id)]; fp!=NULL; fp=fp->f_next)
	{
		if(fp->f_id == id)
		{
			foo_hold(fp);
			break;
		}
	}

	pthread_mutex_unlock(&hashlock);

	return fp;
}

void foo_hold(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);		// 给指定的数据结构中的互斥量加锁
	fp->f_count ++ ;
	pthread_mutex_unlock(&fp->f_lock);		// 释放锁
}

struct foo *foo_alloc(int id)
{
	int idx;
	struct foo *fp;

	if((fp = malloc(sizeof(struct foo))) != NULL)
	{
		fp->f_count = 1;
		fp->f_id = id;
		if(pthread_mutex_init(&fp->f_lock, NULL) != 0){
			free(fp);
			return NULL;
		}
		idx = HASH(id);

		pthread_mutex_lock(&hashlock);		// 给互斥量hashlock加锁
		fp->f_next = fh[idx];
		fh[idx] = fp;
		pthread_mutex_lock(&fp->f_lock);
		pthread_mutex_unlock(&hashlock);

		pthread_mutex_unlock(&fp->f_lock);
	}

	return fp;
}
