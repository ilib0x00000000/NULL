#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


/**
 * 僵尸进程：
 * 存在的意义：每当一个进程结束时，内核会为该进程保存一些信息，包括进程的PID，退出时状态以及资源使用情况等。
 * 如果进程在终止时，内核不释放该资源，则该进程会变成僵尸进程
 * 内核允许最大进程数可以通过 ulimit -u查看，如果不处理僵尸进程，就会导致内核的进程表满，而无法创建更多的进程
 *
 * 处理僵尸进程的方法：
 * 进程终止的时候，内核会向该进程的父进程发送一个SIGCHLD信号，在父进程中处理该信号即可。
 * SIGCHLD是标准信号，不会排队，所以在信号处理程序运行时，如果同时过来N个信号，进程只会让其中一个信号等待。
 * 因此在信号处理程序中要循环调用waitpid()，直到没有要被等待的子进程
 *
 * 子进程监控系统调用
 * #include <sys/wait.h>
 * pid_t waitpid(pid_t pid, int *status, int options);
 * 参数pid：
 * 		如果pid大于0，表示等待进程ID为pid的子进程
 * 		如果pid等于0，则等待与调用进程同一个进程组的所有子进程
 * 		如果pid小于-1，则会等待进程组标识符与pid相等的所有子进程
 * 		如果pid等于-1，则等待任意子进程
 * 参数options：
 * 		WUNTRACED：除了返回终止子进程的信息外，还返回因信号而停止的子进程信息
 * 		WCONTINUED：返回那些因受到SIGCONT信号而恢复执行的已停止子进程的状态信息
 * 		WNOHANG：如果参数pid所指定的子进程并未发生状态改变，则立即返回，而不会阻塞，亦即poll(轮询)。
 * 				在这种情况下，waitpid()返回0。如果调用进程并无与pid匹配的子进程，则waitpid()报错，将errno设置为ECHILD
 *
 * 返回值：若检测到子进程的状态改变，返回该子进程的pid
 * 		如果没有检测到子进程的状态改变，且调用没有出错，则返回0
 * 		如果调用指定的pid没有匹配的进程，则返回-1，且将errno设置为ECHILD
 * 
 * 系统调用waitpid()不是可重入函数，需要为errno保存副本
 *
 * 宏：
 * 	WIFEXITED(status)
 * 	WIFSIGNALED(status)
 * 	WIFSTOPPED(status)
 * 	WIFCONTINUED(status)
 * 	可以分析进程终止时的状态值
 */

static volatile int numLiveChildren = 0;

void sigchld_handler(int sig)
{
	int status;
	int savedErrno;
	pid_t child_pid;

	savedErrno = errno;

	while((child_pid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		/**
		 * 检测所有所有子进程，以不阻塞的方式
		 * 说明检测到有子进程状态改变
		 */
		printf("检测到进程ID为： %ld的进程终止，终止状态值是%d\n", (long)child_pid, WIFEXITED(status) ? WEXITSTATUS(status) : -127);
		numLiveChildren--; 

	}

	if(child_pid==-1 && errno==ECHILD)
	{
		printf("调用waitpid()失败，指定的pid不存在或没有权限\n");
		_exit(EXIT_FAILURE);
	}

	if(child_pid == 0)
	{
		printf("没有子进程的状态发生改变\n");
	}

	sleep(10);     // 这里休眠的原因是要在信号处理期间，接收到至少一个SIGCHLD信号

	errno = savedErrno;
}

int main(int argc, char const *argv[])
{
	int i;
	int sigCnt;
	sigset_t blockMask;
	sigset_t emptyMask;
	struct sigaction sa;

	setbuf(stdout, NULL);  // 禁用stdio缓冲区

	numLiveChildren = 4; // 创建4个子进程

	// 设置信号处理函数
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigchld_handler;
	if(sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		printf("信号处理函数设置失败\n");
		exit(EXIT_FAILURE);
	}


	// 设置进程掩码
	sigemptyset(&blockMask);
	sigaddset(&blockMask, SIGCHLD);
	if(sigprocmask(SIG_SETMASK, &blockMask, NULL) == -1)
	{
		printf("设置进程掩码失败\n");
		exit(EXIT_FAILURE);
	}

	for(i=0; i<4; i++)
	{
		/**
		 * 创建子进程
		 */
		switch(fork())
		{
			case -1:
				printf("创建子进程失败\n");
				exit(EXIT_FAILURE);
			case 0:  // 子进程
				sleep(3);
				printf("子进程PID：%ld终止\n", (long)getpid());
				_exit(EXIT_SUCCESS);
			default:
				break;
		}
	}

	sigemptyset(&emptyMask);
	while(numLiveChildren>0)
	{
		/**
		 * 暂时将进程掩码设置为空，即不阻塞任何信号，等待一个信号处理函数运行结束，再恢复原来的进程掩码
		 */
		if(sigsuspend(&emptyMask)==-1 && errno!=EINTR)
		{
			printf("调用sigsuspend失败\n");
			_exit(EXIT_FAILURE);
		}
	}

	printf("所有的子进程都运行结束\n");

	return 0;
}


