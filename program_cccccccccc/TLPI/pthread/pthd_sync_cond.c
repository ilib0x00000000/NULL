#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/**
 * 线程同步---条件变量
 * 条件变量允许一个线程就某个共享变量（或其他共享资源）的状态变化通知其他线程，并让其他线程等待（堵塞于）这一通知
 *
 * 数据类型：
 * pthread_cond_t     条件变量类型
 * pthread_condattr_t 条件变量属性类型
 *
 * API
 * #include <pthread.h>
 * int pthread_cond_signal(pthread_cond_t *cond);
 * int pthread_cond_broadcast(pthread_cond_t *cond);
 * int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mtx);
 *                      返回值：若成功，返回0，若失败，返回一个正数
 *
 * #include <pthread.h>
 * int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime);
 *                      返回值：若成功，返回0，若失败，返回一个正数
 *
 * 动态分配的条件变量
 * #include <pthread.h>
 * int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
 *                      返回值：若成功，返回0，若失败，返回一个正数
 *
 * int pthread_cond_destroy(pthread_cond_t *cond);
 *                      返回值：若成功，返回0，若失败，返回一个正数
 */

static pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
static pthread_cond_t  tcond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mtx   = PTHREAD_MUTEX_INITIALIZER;

static int cycle = 2; // 总共10次轮回

struct share_pool
{
        int size;
        // Queue queue;   // 生产队列
};

struct share_pool pool = {10}; // 定义一个资源共享池

void *product(void *arg)
{
        int ret;

        // 消费者线程
        while(cycle > 0)
        {
                ret = pthread_mutex_lock(&mtx);
                if(ret != 0)
                {
                        printf("对共享资源加锁失败\n");
                        _exit(EXIT_FAILURE);
                }

                /**
                 * 重点：pthread_cond_wait()的使用
                 *
                 * 一般调用过程：
                 * pthread_mutex_lock(&mtx);
                 * 
                 * pthread_cond_wait(&cond, &mtx);   
                 *              如果没有达到预期，则pthread_cond_wait()会原子性释放锁和陷入等待
                 *              当接收到别的线程的信号时，pthread_cond_wait()会重新获得锁
                 * 
                 * pthread_mutex_unlock(&mtx);
                 */
                while(pool.size <= 0)
                {
                        ret = pthread_cond_wait(&cond, &mtx); // 当资源共享池的元素<=0时，消费者等待生产者
                        assert(ret == 0);
                }

                while(pool.size > 0)
                {
                        pool.size -= 1;
                        // pool.queue.pop();
                        printf("消费者%ld消费了1个元素\n", (long)pthread_self());
                }

                cycle -= 1;

                ret = pthread_mutex_unlock(&mtx);
                assert(ret == 0);

                ret = pthread_cond_signal(&tcond);   // 唤醒任意一个生产者
                assert(ret == 0);
        }

        return NULL;
}

void *consume(void *arg)
{
        int ret;
        // 生产者线程

        while(1)
        {
                ret = pthread_mutex_lock(&mtx);  // 对共享资源加锁
                assert(ret == 0);

                while(pool.size >= 10)
                {
                        ret = pthread_cond_wait(&tcond, &mtx);
                        assert(ret == 0);
                }

                while(pool.size < 10)
                {
                        // pool.queue.append()
                        pool.size += 1;
                        printf("生产者%ld生产了1个元素\n", (long)pthread_self());
                }

                ret = pthread_mutex_unlock(&mtx);
                assert(ret == 0);

                ret = pthread_cond_signal(&cond);
                assert(ret == 0);
        }

        return NULL;
}


int main(int argc, char const *argv[])
{
        int i;
        int ret;
        pthread_t prothreads[4];  // 4个消费者
        pthread_t conthreads[3];  // 3个生产者

        for(i=0; i<4; i++)
        {
                ret = pthread_create(&prothreads[i], NULL, product, NULL);
                if(ret != 0)
                {
                        printf("创建消费者失败\n");
                        _exit(EXIT_FAILURE);
                }
        }

        for(i=0; i<3; i++)
        {
                ret = pthread_create(&conthreads[i], NULL, consume, NULL);
                if(ret != 0)
                {
                        printf("创建生产者失败\n");
                        _exit(EXIT_FAILURE);
                }
        }

        for(i = 0; i < 4; i++)
        {
                ret = pthread_join(prothreads[i], NULL);
                assert(ret == 0);
        }

        for(i = 0; i < 3; i++)
        {
                ret = pthread_join(conthreads[i], NULL);
                assert(ret == 0);
        }

        // 线程最后会阻塞在生产者那里

        return 0;
}


