#include<time.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<setjmp.h>

/**
 * sigsetjmp和siglongjmp函数
 * 非局部转移：setjmp和longjmp函数
 * 在信号处理程序中经常调用longjmp函数以返回到程序的主循环中，而不是从该处理程序返回。
 * sigsetjmp和siglongjmp函数，在信号处理程序中进行非局部转移时应当使用这两个函数。
 *
 * #include<setjmp.h>
 * int sigsetjmp(sigjmp_buf env, int savemask);
 * 								返回值：若直接调用，返回0，若从siglongjmp调用返回，则返回非0
 * void siglongjmp(sigjmp_buf env, int val);
 *
 * 如果savemask非0，则sigsetjmp在env中保存进程的当前信号屏蔽字。调用siglongjmp时，如果带非0savemask
 * 的sigsetjmp调用已经保存了env，则siglongjmp从其中恢复保存的信号屏蔽字。
 */


static void 		sig_usr1(int);
static void 		sig_alrm(int);


static sigjmp_buf	jmpbuf;
static volatile sig_atomic_t canjump;

int main(int argc, char const *argv[])
{
	if( signal(SIGUSR1, sig_usr1) == SIG_ERR)
	{
		perror("signal(SIGUSR1) error");
	}

	if( signal(SIGALRM, sig_alrm) == SIG_ERR)
	{
		perror("signal(SIGALRM) error");
	}

	printf("starting main:\n");

	if(sigsetjmp(jmpbuf, 1))		// sigsetjmp函数在第二个参数不为0的情况下，会将进程的当前信号屏蔽字保存在第一个参数中
	{
		printf("ending main\n");
		exit(0);
	}

	canjump = 1;
	for(; ;)
	{
		pause();
	}

	return 0;
}


static void sig_usr1(int signo)
{
	/**
	 * 在执行SIGUSR1信号处理程序时，SIGUSR1信号是被阻塞的
	 */
	time_t starttime;

	if(canjump == 0)
		return ;

	printf("start sig_usr1\n");
	alarm(3);

	starttime = time(NULL);
	for(; ;)
	{
		if(time(NULL) > starttime + 5)
			break;
	}

	printf("finish sig_usr1\n");
	canjump = 0;
	siglongjmp(jmpbuf, 1);		// 会跳回到main中的sigsetjmp函数地方，然会sigsetjmp返回1
}

static void sig_alrm(int signo)
{
	printf("in sig_alrm\n");
}
