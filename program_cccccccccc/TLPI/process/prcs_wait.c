#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>


/**
 * wait()调用API
 * 系统调用wait()等待调用进程的任一子进程终止，同时在参数status所指向的缓冲区中返回该子进程的终止状态
 * #include<sys/wait.h>
 * pid_t wait(int *status);
 * 			返回值：若调用成功，返回子进程的PID，若失败，返回-1
 *
 * 系统调用wait()执行如下动作：
 * 1. 如果调用之前进程没有终止且被等待的子进程，调用将一直阻塞，直至某个子进程终止。如果调用时已有子进程终止或被等待，则立即返回
 * 2. 如果status非空，则子进程的终止状态会通过status指向的整型变量返回
 * 3. 内核将会为父进程下所有子进程的运行总量追加进程CPU时间以及资源使用数据
 * 4. 将子进程的PID作为返回值返回
 *
 * 出错时，返回-1，可能的原因是调用进程再无被等待的子进程，此时会将errno置为ECHILD
 */



int main(int argc, char const *argv[])
{
	int status;
	pid_t ret_pid;
	pid_t child_pid;

	/**
	 * 先让一个子进程终止，变成僵尸进程，
	 * 父进程调用wait()，得到终止子进程的信息
	 * 继续fork()出两个子进程，
	 * 父进程调用wait(),并阻塞等待子进程终止
	 */
	
	switch(child_pid=fork())
	{
		case -1:
			printf("创建子进程失败\n");
			exit(EXIT_FAILURE);
		case 0:   // 在子进程中
			printf("这是第一个子进程,PID:%ld.....运行结束\n", (long)getpid());
			break;
		default:
			sleep(1);
			ret_pid = wait(&status);
			if(ret_pid==-1)
			{
				if(errno == ECHILD)
				{
					printf("没有被等待的子进程了\n");
					exit(EXIT_SUCCESS);
				}else
				{
					printf("等待子进程时出错\n");
					exit(EXIT_FAILURE);					
				}
			}else
			{
				printf("wait() 返回一个PID：%ld\n", (long)ret_pid);
			}

			switch(child_pid=fork())
			{
				case -1:
					printf("创建子进程失败\n");
					exit(EXIT_FAILURE);
				case 0:
					printf("这是最后一个进程PID: %ld....睡眠中\n", (long)getpid());
					sleep(5);
					exit(10);
				default:
					ret_pid = wait(&status);
					if(ret_pid != -1)
					{
						printf("wait() 返回一个PID: %ld， 该进程的结束状态值是： %d\n", (long)ret_pid, status);
					}
			}
	}

	return 0;
}