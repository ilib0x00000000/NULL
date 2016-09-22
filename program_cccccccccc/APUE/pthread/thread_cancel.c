#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

/**
 * 有两个线程属性，没有包含在pthread_attr_t结构中，可取消状态和可取消类型
 * 这两个属性影响着线程pthread_cancel函数调用时所呈现的行为
 *
 * int pthread_setcancelstate(int state, int *oldstate);
 * void pthread_testcancel(void);
 * int pthread_setcanceltype(int type, int *oldtype);
 *
 * pthread_cancel调用并不等待线程终止，它只是提出请求，线程在取消请求发出后会继续执行，直到到达某个
 * 取消点，取消点是线程检查是否被取消并按照请求进行动作的一个位置
 *
 * pthread_cancel:发送终止信号给thread线程，如果成功返回0，否则为非0值，发送成功并不意味着thread会终止
 * pthread_setcancelstate:设置本线程对cancel信号的反应，state有两种值：PTHREAD_CANCEL_ENABLE()和
 * 				PTHREAD_CANCEL_DISABLE，分别表示收到信号后设为CANCLED状态和忽略CANCEL信号继续运行，
 * 				如果第二个参数非NULL，则表示存入原来的cancel状态以便恢复
 * pthread_setcanceltype:设置本线程取消动作的执行时机，有两种取值，分别表示收到信号后继续执行至下一个取消点
 * 				再退出和立即执行取消动作退出，第二个参数非NULL则存入原来的取消动作类型
 * pthread_testcancel:在不包含取消点，但有需要取消点的地方创建一个取消点，以便在一个没有包含取消点的执行代码
 * 				线程中响应取消请求，如果取消功能处于启用状态且设置为延迟状态时，该函数有效
 */

void *thr_with_cancelpoint(void *arg);          // 有取消点
void *thr_without_cancelpoint(void *arg);       // 没有取消点
void *thr_async_cancel(void *arg);              // 异步取消
void *thr_set_cancelpoint(void *arg);           // 设置取消点

int main(int argc, char const *argv[])
{
	int err;
	pthread_t tid1;

	err = pthread_create(&tid1, NULL, thr_set_cancelpoint, NULL);
	if(err == 0)
	{
		pthread_cancel(tid1);		// 请求取消线程
		pthread_join(tid1, NULL);	// 等待线程结束

		printf("main thread is exit\n");
	}

	return 0;
}

void *thr_set_cancelpoint(void *arg)
{
	/**
	 * 如果在线程中没有包含取消点的函数，可以自己设置取消点
	 */
	int i;

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

	for(i = 0; i < 1000000; i++)
	{
		;
		pthread_testcancel();
	}

	printf("thread x is over ... \n");
}

void *thr_async_cancel(void *arg)
{
	/**
	 * 异步取消是立即取消
	 * 所以不需要取消点也能退出
	 */
	int i;

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);    // 设置取消退出为异步（立即）退出

	for(i = 0; i<1000000; i++)
		;

	printf("thread x is over\n");
}

void *thr_without_cancelpoint(void *arg)
{
	int i = 0;
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);	// 设置对取消线程的信号的状态（默认/忽略）
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);	// 设置处理取消线程的类型（立即/等到下一个取消点）

	/**
	 * 没有取消点，不能printf，printf包含取消点
	 * 线程无法被退出，只能正常结束
	 */
	for(i = 0 ; i < 1000000; i++)
		;

	printf("thread is over....\n");
}

void *thr_with_cancelpoint(void *arg)
{
	int i;

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);	// 设置处理线程取消状态
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

	/*printf函数中会出现取消点*/
	for(i = 0 ; i < 1000000; i++)
		printf("%d\n", i);

	printf("thread is over....\n");
}