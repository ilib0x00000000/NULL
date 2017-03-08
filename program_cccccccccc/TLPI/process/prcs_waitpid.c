#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


/**
 * waitpid()系统调用API
 * #include<sys/wait.h>
 * pid_t waitpid(pid_t pid, int *status, int options);
 * 			返回值：若成功，返回子进程，失败返回-1，某些情况下会返回0
 * 参数pid:
 * 		* 如果pid大于0： 表示等待进程ID等于pid的子进程
 * 		* 如果pid等于0： 则等待与调用进程（父进程）同一个进程组的所有子进程
 * 		* 如果pid小于-1： 则会等待进程组标识符与pid的绝对值相等的所有子进程
 * 		* 如果pid等于-1： 则等待任意子进程
 *
 * 参数options：
 * 		* WUNTRACED： 除了返回终止子进程的信息外，还返回因信号而停止的子进程信息
 * 		* WCONTINUED： 返回那些因收到SIGCONT信号而恢复执行的已停止子进程的状态信息
 * 		* WNOHANG： 如果参数pid指定的子进程并未发生状态改变，则立即返回，而不会阻塞，亦即poll(轮询)。
 * 			在这种情况下，waitpid()返回0。如果调用进程并无于pid匹配的子进程，则waitpid()报错，将错误号置为ECHILD。
 *
 *
 * 对于exit()中返回的值，不能直接判断使用，需要使用系统定义的宏来判断使用
 * WIFEXITED(status)    若子进程正常结束返回真
 * WIFSIGNALED(status)  若子进程被信号杀死返回真
 * WIFSTOPPED(status)   若子进程因为信号而停止，返回真
 * WIFCONTINUED(status) 若子进程收到SIGCONT而恢复执行，则返回真
 * 
 */

void print_wait_status(char *msg, int status);

int main(int argc, char const *argv[])
{
	int status;
	pid_t child_pid;

	switch(fork())
	{
		case -1:
			printf("创建子进程失败\n");
			exit(EXIT_FAILURE);
		case 0:    // 子进程
			printf("子进程开始运行， PID：%ld\n", (long)getpid());
			if(argc > 1)
				exit(atoi(argv[1]));
			else
			{
				for(;;)
					pause();
			}
			exit(EXIT_FAILURE);
		default:
			/**
			 * 检测子进程的状态
			 * 如果子进程的状态没有发生改变，立即返回
			 * 子进程收到信号停止也会返回
			 */
			for(;;)
			{
				child_pid = waitpid(-1, &status, WUNTRACED
#ifdef WCONTINUED
				| WCONTINUED
#endif
				);

				if(child_pid == -1)
				{
					printf("waitpid调用失败\n");
					exit(EXIT_FAILURE);
				}

				printf("waitpid() 返回： PID=%ld； status=0x%04x (%d, %d)\n", (long)child_pid, (unsigned int)status, status>>8, status&0xff);

				print_wait_status(NULL, status);

				if(WIFEXITED(status) || WIFSIGNALED(status))
				{
					exit(EXIT_SUCCESS);
				}
			}

	}

	return 0;
}

void print_wait_status(char *msg, int status)
{
	if(msg != NULL)
	{
		printf("%s", msg);
	}

	if(WIFEXITED(status))
	{
		// 子进程正常结束
		printf("子进程正常结束，结束状态值： %d\n", WEXITSTATUS(status));
	}else
	if(WIFSIGNALED(status))
	{
		// 子进程被信号杀死
		printf("子进程被信号%d杀死\n", WTERMSIG(status));
#ifdef WCOREDUMP
		if(WCOREDUMP(status))
			printf("产生了核心转储文件\n");
#endif
	}else
	if(WIFSTOPPED(status))
	{
		// 子进程因为信号而停止
	}else
	if(WIFCONTINUED(status))
	{
		// 子进程因为收到SIGCONT信号而继续执行
	}
}