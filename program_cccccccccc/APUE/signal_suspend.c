#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>


/**
 * 在一个原子操作中先恢复信号屏蔽字，然后使进程休眠
 * #include<signal.h>
 * int sigsuspend(const sigset_t *sigmask);
 *
 * 1.将进程的信号屏蔽字设置为由sigmask指向的值。
 * 2.在捕捉到一个信号之前/发生了一个会终止该进程的信号之前，该进程会被挂起。
 * 3.如果捕捉到一个信号而且从该信号处理程序返回，则sigsuspend返回，并且该进程的信号
 * 屏蔽字设置为调用sigsuspend之前的值。
 */

static void sig_int(int signo);

int main(int argc, char const *argv[])
{
	sigset_t newmask;
	sigset_t oldmask;
	sigset_t waitmask;
	
	printf("program start:\n");

	if( signal(SIGINT, sig_int) == SIG_ERR)
		perror("siganl(SIGINT) error");

	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	if( sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		perror("SIG_BLOCK error");
	}

	printf("in critical region:\n");
	if(sigsuspend(&waitmask) != -1)
	{
		perror("sigsuspend error");
	}
	printf("after return from sigsuspend\n");

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		perror("SIG_SETMASK error");

	printf("program exit\n");

	return 0;
}

static void sig_int(int signo)
{
	printf("\nin sig_int\n");
}
