#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>


/**
 * 参考：
 * http://www.cnblogs.com/wuchanming/p/4020463.html
 *
 * SIGCHLD信号：
 * 		在父进程创建一个子进程，子进程执行结束时，内核会释放子进程的相关资源，如文件描述符，存储等等，
 * 		但是内核会保留关于进程的部分状态，如子进程的PID，进程结束状态，CPU时间等。这样会导致子进程的
 * 		PID一直被保留着，如果父进程不处理子进程，则子进程就会变成僵尸进程。
 *
 * 子进程exit时会产生一个SIGCHLD信号，父进程对此信号的默认动作是忽略，如果不捕捉该信号，则会导致子进程变成僵尸进程。
 *
 * 父进程捕捉到该信号，将信号处理函数设置成SIG_IGN或调用wait函数，都可以避免僵尸进程的出现
 * 如果在父进程最后再调用一个wait函数，则父进程将阻塞到所有子进程都终止，然后wait会返回-1，并将errno设置为ECHILD，
 * 此信号的默认配置是忽略。
 */
void test_zombie(void);
void test_kill_zombie(void);

int main(int argc, char const *argv[])
{
	test_kill_zombie();
	// test_zombie();
	return 0;
}

void test_kill_zombie(void)
{
	int i;
	pid_t pid;

	/* 这里对子进程退出的信号处理是忽略，与默认处理动作不同 */
	if(signal(SIGCHLD, SIG_IGN) == SIG_ERR)
	{
		printf("调用信号处理函数失败\n");
	}

	for(i = 0; i < 5; i++)
	{
		pid = fork();
		if(pid < 0)
		{
			printf("创建子进程失败\n");
		}else
		if(pid == 0)
		{
			/* 在子进程中 */
			printf("子进程正在运行中\n");
			exit(0);
		}
	}
	pause();
	printf("父进程退出\n");
}
/**
 * 测试：后台运行，ps -o pid,ppid,stat
 * 没有出现stat为Z的进程
 */

void test_zombie(void)
{
	int i;
	pid_t pid;

	for(i = 0; i < 5; i++)
	{
		pid = fork();
		if(pid < 0)
		{
			printf("创建子进程失败\n");
		}else
		if(pid == 0)
		{
			/* 在子进程中 */
			printf("子进程-%d-正在运行中\n", pid);
			exit(0);
		}
	}
	/* 父进程不能在子进程运行结束之后就结束 */
	pause();
	printf("子进程全部创建完毕\n");
}

/**
 * 测试：
 * test_zombie调用之后，后台运行，ps -aux发现有一些进程状态显示Z，表示僵尸进程
 * 或者使用命令 ps -o pid,ppid,stat
 */