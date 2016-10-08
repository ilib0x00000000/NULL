#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>


/**
 * 参考：
 * http://blog.csdn.net/beginning1126/article/details/8680757
 * http://www.cnblogs.com/lidabo/p/4581202.html
 * 
 * sigaction函数：检查或修改与指定信号相关联的处理动作
 * int sigaction(int signo, const struct sigaction *restrict act, struct sigaction *restrict oact);
 * 														返回值：若成功，返回0，若失败，返回-1
 * signo:要检测或修改具体动作的信号编号
 * 若act指针非空：则要修改其动作
 * 如果oact指针非空： 则系统经由oact指针返回该信号的上一个动作
 *
 * struct sigaction{
 * 		void    (*sa_handler)(int);
 * 		sigset_t  sa_mask;
 * 		int       sa_flags;
 * 		void    (*sa_sigaction)(int, siginfo_t *, void *);
 * };
 *
 * 当更改信号动作时：
 * sa_handler:  包含一个信号捕捉函数的地址
 * sa_mask:     说明一个信号集，在调用信号捕捉函数之前，这一信号集要加到进程的信号屏蔽字中，
 * 				这样，在调用信号处理程序时就能阻塞某些信号，
 * sa_flags:    指定对信号进行处理的各个选项
 * sa_sigaction:是一个替代的信号处理程序，在sigaction结构中指定了SA_SIGINFO标志时，使用该信号的处理程序
 *
 * 一般调用的信号处理程序格式：void handler(int signo)
 * 但是指定了sa_flags标志之后，调用方式：void handler(int signo, siginfo_t *info, void *context)
 *
 * struct siginfo{
 * 		int    si_signo;
 * 		int    si_errno;
 * 		int    si_code;
 * 		pid_t  si_pid;
 * 		uid_t  si_uid;
 * 		void   *si_addr;
 * 		int    si_status;
 * 		union sigval si_value;
 * };
 */

typedef void (*Sigfunc)(int);
void handler(int signo);


int main(int argc, char const *argv[])
{
	struct sigaction act;
	struct sigaction act2;

	/* 处理SIGINT信号，屏蔽SIGQUIT信号 */
	act.sa_handler = handler;

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGQUIT);    // 向进程的信号屏蔽字中加入SIGQUIT信号

	act.sa_flags = 0;

	sigaction(SIGINT, &act, NULL);

	/* 处理SIGQUIT信号 */
	act2.sa_handler = handler;
	sigemptyset(&act2.sa_mask);
	act2.sa_flags = 0;
	sigaction(SIGQUIT, &act2, NULL);

	while(1)
	{
		sleep(5);
	}

	return 0;
}

/**************************************************signal函数的实现********************************************************/
Sigfunc *signal(int signo, Sigfunc *func)
{
	struct sigaction act;
	struct sigaction oact;

	act.sa_handler = func;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if(singo == SIGALRM)
	{
		#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
		#endif
	}else
	{
		act.sa_flags |= SA_RESTART;
	}

	if(sigaction(signo, &act, &oact) < 0)
		return SIG_ERR;

	return oact.sa_handler;
}

/**
 * Linux下sa_flags取值如下：
 *******SA_NODEFER:   当捕捉到此信号时，在执行其信号捕捉函数时，系统不自动阻塞此信号
 *******SA_RESETHAND: 当用户注册的信号处理函数被执行过一次后，该信号的处理函数被设为系统默认的处理函数
 * 		SA_INTERRUPT: 由此信号中断的系统调用不自动重启动
 * 		SA_NOCLDSTOP: 若signo是SIGCHLD，当子进程停止时，不产生此信号。当子进程结束时，仍旧产生此信号
 * 		SA_NOCLDWAIT: 若signo是SIGCHLD，则当调用进程的子进程终止时，不创建僵尸进程。若调用进程随后调用wait，则阻塞到所有子进程都结束，此时返回-1，errno设置为ECHILD
 * 		SA_ONSTACK:   
 * 		SA_RESTART:   由此信号中断的系统调用自动重启动
 * 		SA_SIGINFO:   此选项对信号处理程序提供了附加信息
 */

void handler(int signo)
{
	int i;

	printf("Received signal: -%2d-\n", signo);

	for(i = 0; i < 5; i++)
	{
		printf("In Signal Handler: %d\n", i);
		sleep(1);
	}
}


/**
 * 处理SIGINT信号时，如果后面再有SIGINT信号产生，其将会被阻塞，而且如果是多个SIGINT一起产生，
 * 在当前信号处理程序之后只会接收到1个SIGINT信号。
 *
 * 在处理SIGINT信号时，屏蔽了SIGQUIT信号，所以在SIGINT信号处理程序返回之前，SIGQUIT信号是被阻塞的(未决的/屏蔽的)
 *
 * 在处理SIGQUIT信号时，没有指定进程的信号屏蔽字，所以进程是没有屏蔽的信号，当调用SIGQUIT信号处理程序时如果再产生
 * SIGINT信号，则进程会先处理SIGINT信号。
 *
 * SIGINT   2
 * SIGQUIT  3
 *
 * 测试：
 * 在运行程序之后：首先按下Crtl+c，由于SIGINT信号处理程序屏蔽了SIGQUIT信号，所以在调用SIGINT信号处理程序时，按Ctrl+\是
 * 没有用的，直到SIGINT信号处理程序结束之后，才会处理SIGQUIT信号，且多个SIGQUIT信号都只会调用一次该信号处理程序。
 *
 * 在按下Ctrl+\之后，如果再按Ctrl+c，则SIGQUIT处理程序会停下，先处理SIGINT信号处理程序，直到SIGINT信号处理程序执行完毕，
 * 再继续执行SIGQUIT信号处理程序。
 */