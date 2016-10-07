#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

/**
 * 参考：
 * http://www.jianshu.com/p/2f6948d885cb#
 *
 * Linux下支持的信号在/usr/include/asm-generic/signal.h文件中定义，提供了大概31种信号编码
 * 
 * 信号是软件中断，每个信号都有一个名字
 * 		SIGABRT是夭折信号，当调用abort函数时，产生此信号
 * 		SIGALRM是定时器信号，由alarm函数设置的定时器函数超时后产生此信号
 * 不存在编号为0的信号，因为kill函数对信号编号0有特殊应用
 *
 * 信号的3种处理方式：
 * 		1. 忽略此信号，有两种信号不能忽略：SIGKILL和SIGSTOP
 * 		2. 捕捉信号，通知内核在某种信号发生时，调用一个用户函数，SIGKILL和SIGSTOP信号不能捕捉
 * 		3. 执行默认动作
 *
 * signal函数的原型
 * #include<signal.h>
 * void (*signal(int signo, void (*handler)(int)))(int);
 *
 * 若signal函数返回SIG_ERR，则表示signal函数调用失败
 *
 * 当一个进程调用fork时，其子进程继承父进程的信号处理方式。
 */

static void sig_usr(int signo);


int main(int argc, char const *argv[])
{
	if(signal(SIGUSR1, sig_usr) == SIG_ERR)
	{
		fprintf(stderr, "%s\n", "signal函数调用失败");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGUSR2, sig_usr) == SIG_ERR)
	{
		fprintf(stderr, "%s\n", "signal函数调用失败");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		pause();         // 进程一直挂起，直到接收到一个信号
	}

	return 0;
}

static void sig_usr(int signo)
{
	if(signo == SIGUSR1)
	{
		printf("收到信号SIGUSR1\n");
	}else
	if(signo == SIGUSR2)
	{
		printf("收到信号SIGUSR2\n");
	}else
	{
		printf("收到信号编号： %d\n", signo);
		return ;
	}
}


/**
 * 编译完执行测试：
 * ./a.out &           后台运行
 *
 * kill -USR1   pid    向程序发送USR1信号
 * kill -USR2   pid    向程序发送USR2信号
 * kill pid            结束进程
 */