#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>
#include <sched.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


/**
 * #define _GNU_SOURCE
 * #include<sched.h>
 * int clone(int (*func)(void *), void *child_stack, int flags, void *func_arg, ... /pid_t *ptid, struct user_desc *tls, pid_t *ctid/);
 * 			返回值：若成功，返回子进程的PID，若失败，返回-1
 *
 * Linux系统特有的clone()可以创建一个新进程，与fork()/vfork()不同的是，clone()在进程创建期间对步骤的控制更为精确。clone()主要用于线程库的实现
 * Linux最常用的pthread线程库就是系统调用clone()实现的
 * 
 * clone()        fork()     vfork()
 *   |              |           |
 *   \              |           |
 *    \             |           |
 * sys_clone()      |           |
 *      \           |           |
 *       \          |           |
 *       do_fork()(kernel/fork.c)
 *
 * 当func()返回或者调用_exit()之后，克隆产生的子进程就会终止，照例，父进程可以通过wait()一类函数来等待子进程
 *
 * 参数flags有双重作用：
 * 1. 低字节中存放着子进程的终止信号，子进程在退出时，父进程将收到这一信号。如果该字节为0，这时将不产生任何信号
 * 2. 剩余字节则存放了位掩码，用于控制clone()的操作。
 * 
 */

#ifndef CHILD_SIG
#define CHILD_SIG SIGUSR1
#endif

static int child_func(void *arg)
{
	if(close(*((int *)arg)) == -1)
	{
		printf("关闭文件描述符失败\n");
		_exit(EXIT_FAILURE);
	}

	_exit(EXIT_SUCCESS);
}

void sigusr_handler(int sig)
{
	printf("捕捉到SIGUSR1信号\n");
}

int main(int argc, char const *argv[])
{
	int s, fd, flags;
	const int STACK_SIZE = 65536;
	char *stack;
	char *stackTop;
	struct sigaction sa;

	fd = open("/dev/null", O_RDWR);
	if(fd == -1)
	{
		printf("打开/dev/null文件失败\n");
		_exit(EXIT_FAILURE);
	}

	// 是否共享父进程打开的文件，如果共享，在子进程中关闭文件，则父进程中也同样会被关闭文件
	// 即子进程中的操作文件也就是父进程中操作文件
	flags = (argc>1) ? CLONE_FILES : 0;

	stack = malloc(STACK_SIZE);
	assert(stack != NULL);
	stackTop = stack+STACK_SIZE;


	if(CHILD_SIG!=0 && CHILD_SIG!=SIGCHLD)
	{
		// 如果信号不是SIGCHLD并且信号不为0，则设置信号的处理程序为忽略该信号
		if(signal(CHILD_SIG, SIG_IGN) == SIG_ERR)
		{
			printf("设置信号处理程序失败\n");
			_exit(EXIT_FAILURE);
		}
	}


	/**
	 * 设置SIGUSR1信号处理器
	 */
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigusr_handler;
	if(sigaction(CHILD_SIG, &sa, NULL) == -1)
	{
		printf("为SIGUSR1信号设置处理器失败\n");
		_exit(EXIT_FAILURE);
	}


	// 子进程结束时，向父进程发送一个SIGUSR1信号
	if(clone(child_func, stackTop, flags|CHILD_SIG, (void *)&fd) == -1)
	{
		printf("调用clone()失败\n");
		_exit(EXIT_FAILURE);
	}

	if(waitpid(-1, NULL, (CHILD_SIG != SIGCHLD)?__WCLONE:0) == -1)
	{
		printf("waitpid调用失败\n");
		_exit(EXIT_FAILURE);
	}

	s = write(fd, "x", 1);
	if(s==-1 && errno==EBADF)
		printf("文件描述符已经被关闭\n");
	else
	if(s == -1)
	{
		printf("文件描述符写入失败\n");
		_exit(EXIT_FAILURE);
	}else
	{
		printf("向文件描述符中写入成功\n");
	}

	return 0;
}


/**
 * ilib0x00000000@touch:~/linux$ ./a.out 
 * 捕捉到SIGUSR1信号
 * 向文件描述符中写入成功
 * ilib0x00000000@touch:~/linux$ ./a.out dsasd
 * 捕捉到SIGUSR1信号
 * 文件描述符已经被关闭
 */


