#include<signal.h>

/**
 * 函数signal
 * void (*signal(int signo, void (*func)(int)))(int);
 * 返回值：若成功，返回以前的信号处理配置，若出错，返回SIG_ERR
 * 		参数：1.整型
 * 			  2.函数指针------->指向的函数需要一个整型参数，无返回值
 * 	    返回值：函数指针------->指向的函数有一个整型参数，且无返回值
 * 
 * signal第一个参数是信号量的值，表示当接收到该信号时，会调用第二个参数。
 * 第二个参数有3种情况：
 * 		1.参数为：SIG_IGN，表示忽略该信号（但是有两种信号不能忽略）
 * 		2.参数为：SIG_DFL，表示按默认方法处理该信号
 * 		3.参数为回调函数，表示使用回调函数处理该信号
 */

static void sig_usr(int);

int main(int argc, char const *argv[])
{
	if(signal(SIGUSR1, sig_usr) == SIG_ERR)
	{
		perror("can\'t catch SIGUSR1");
	}

	if(signal(SIGUSR2, sig_usr) == SIG_ERR)
	{
		perror("can\'t catch SIGUSR2");
	}

	for(; ;)
	{
		pause();
	}
	
	return 0;
}

static void sig_usr(int signo)
{
	if(signo == SIGUSR1)
	{
		printf("received SIGUSR1\n");
	}else
	if(signo == SIGUSR2)
	{
		printf("received SIGUSR2\n");
	}else
	{
		printf("received signal %d\n", signo);
	}
}
