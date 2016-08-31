#include<unistd.h>
#include<signal.h>

#include"apue.h"

/**
 * 与信号相关的函数：
 * 		int kill(pid_t pid, int signo);
 * 		int raise(int signo);
 * 		unsigned int alarm(unsigned int seconds);
 * 		int pause(void)
 *
 * kill函数将信号发给进程或进程组
 * raise允许进程向自身发送信号
 * alarm函数可以设置一个定时器，在将来的某个时刻该定时器会超时。当定时器超时时，会产生SIGALRM信号。如果忽略或不捕捉此信号，
 * 则其默认动作是终止调用alarm函数的进程
 * pause函数使调用进程挂起直至捕捉到一个信号
 */

// 模拟sleep函数
static void sig_alrm(int signo);

unsigned int similar_sleep(unsigned int seconds);

unsigned int similar_sleep(unsigned int seconds)
{
	if( (signal(SIGALRM, sig_alrm)) == SIG_ERR)
		return seconds;

	alarm(seconds);		// 设置一个定时器

	pause();			// 使进程挂起，直至捕捉到一个信号

	return (alarm(0));	// 清除以前的定时
}

static void sig_alrm(int signo)
{
	// 这个信号处理函数什么也不干
}


/**
 * 用以上的函数去模拟sleep会出现如下问题：
 * 		1.如果在调用模拟的sleep函数之前调用了alarm函数，则之前的定时器会被清除
 * 		2.该程序修改了对SIGALRM的配置，应该在调用之后恢复该配置
 * 		3.在调用alarm和pause之间有一个竞争条件，如果CPU在调用alarm之后切换上下文，则有可能导致进程永远挂起
 */
