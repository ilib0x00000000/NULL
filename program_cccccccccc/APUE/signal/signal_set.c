#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>

/**
 * 函数：
 * int kill(pid_t pid, int signo);            // 将信号发送给进程或进程组
 * int raise(int signo);                      // 进程向自身发送信号
 * unsigned int alarm(unsigned int seconds);  // 设置一个定时器，超时之后，会产生一个SIGALRM信号
 * int pause(void);                           // 调用进程挂起直到捕捉到一个信号
 *
 * 数据类型：
 * sigset_t: 表示多个信号的集合
 *
 * 函数：
 * int sigemptyset(sigset_t *set);                    // 初始化信号集，清除所有的信号
 * int sigfillset(sigset_t *set);                     // 初始化信号集，使其包含所有的信号
 * int sigaddset(sigset_t *set, int signo);           // 将一个指定的信号添加到信号集中
 * int sigdelset(sigset_t *set, int singo);           // 从信号集中删除一个指定的信号
 * 											返回值：若成功，返回0，若失败，返回-1
 * 											
 * int sigismember(const sigset_t *set, int signo);   // 检测信号集中某个信号位是否被设置
 * 											返回值：若真，返回1，若假，返回0
 *
 * 信号屏蔽字：规定了当前阻塞而不能递送给该进程的信号集
 * int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);     // 可以检测或更改进程的信号屏蔽字(只针对单线程进程)
 * 											返回值：若成功，返回0，若失败，返回-1
 * 若oset非空：进程的当前屏蔽字通过oset返回
 * 若set非空：
 * 		how=SIG_BLOCK: 该进程新的信号屏蔽字是当前信号屏蔽字与set指向信号集的并集。
 * 		how=SIG_UNBLOCK: 该进程新的信号屏蔽字是当前信号屏蔽字与set指向信号集的交集。
 * 		how=SIG_SETMASK: 该进程新的信号屏蔽字是set指向的值。
 * 若set为空：则不改变进程的信号屏蔽字，how的值也无意义
 * 											
 * int sigpending(sigset_t *set);                     // 
 * int sigaction(int signo, const struct sigaction *restrict act, struct sigaction *restrict oact);
 *
 * struct sigaction{
 * 		void      (*sa_handler)(int);
 * 		sigset_t    sa_mask;
 * 		int         sa_flags;
 * 		void      (*sa_sigaction)(int, siginfo_t *, void *);
 * };
 *
 * 进程默认不屏蔽字任何信号，即信号屏蔽字为空
 */

void sigset_base_func(void);
int  print_sigset(void);


int main(int argc, char const *argv[])
{
	print_sigset();

	return 0;
}

int print_sigset(void)
{
	/* 打印进程信号屏蔽字 */
	int i;
	int sum = 0;
	int errno_save;
	sigset_t set;

	errno_save = errno;

	/* 清空进程的信号屏蔽字集 */
	sigemptyset(&set);
	if(sigprocmask(0, NULL, &set) == -1)
	{
		fprintf(stderr, "获取进程的信号屏蔽字失败");
	}else
	{
		for(i = 1; i < 31; i++)
		{
			if(sigismember(&set, i))
			{
				printf("信号：-%2d-在进程屏蔽字中\n", i);
				sum += 1;
			}else
			{
				printf("信号：-%2d-不在进程屏蔽字中\n", i);
			}
		}
	}

	errno = errno_save;

	return sum;
}

void sigset_base_func(void)
{
	int rtn;
	sigset_t set;

	/* 初始化信号集，清空所有信号位 */
	if((rtn = sigemptyset(&set)) == -1)
	{
		fprintf(stderr, "初始化信号集失败\n");
		exit(EXIT_FAILURE);
	}

	/* 向信号集中添加某个信号量 */
	if((rtn = sigaddset(&set, SIGCHLD)) == -1)
	{
		fprintf(stderr, "向信号集中添加SIGCHLD信号量失败\n");
		exit(EXIT_FAILURE);
	}

	/* 检测信号集中是否包含某个信号量 */
	if(sigismember(&set, SIGCHLD))
	{
		printf("信号集中包含SIGCHLD信号量\n");
	}else
	{
		printf("信号集中不包含SIGCHLD信号量\n");
	}

	if(sigismember(&set, SIGBUS))
	{
		printf("信号集中包含SIGBUS信号量\n");
	}else
	{
		printf("信号集中不包含SIGBUS信号量\n");
	}

	/* 删除信号集中的某个信号量 */
	if((rtn = sigdelset(&set, SIGCHLD)) == -1)
	{
		fprintf(stderr, "删除信号量SIGCHLD失败\n");
		exit(EXIT_FAILURE);
	}

	/* 检测信号集中是否包含某个信号量 */
	if(sigismember(&set, SIGCHLD))
	{
		printf("信号集中包含SIGCHLD信号量\n");
	}else
	{
		printf("信号集中不包含SIGCHLD信号量\n");
	}	
}