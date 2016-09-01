#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>


/**
 * 信号集（数据结构）：告诉内核不允许发生该信号集中的信号
 *
 * int sigemptyset(sigset_t *set);
 * int sigfillset(sigset_t *set);
 * int sigaddset(sigset_t *set, int signo);
 * int sigdelset(sigset_t *set, int signo);
 * 										4个函数返回值：若成功，返回0，若出错，返回-1
 * int sigismember(const sigset_t *set, int signo);
 * 										返回值：若真，返回1，若假，返回0
 *
 * sigemptyset函数初始化由set指向的信号集，清除其中的所有信号
 * sigfillset函数初始化由set指向的信号集，使其包括所有信号
 * sigaddset函数将一个信号添加到已有的信号集中
 * sigdelset函数从信号集中删除一个信号
 *
 * #include<signal.h>
 * int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);
 * int sigpending(sigset_t *set);
 * int sigaction(int signo, const struct sigaction *restrict act, struct sigaction *restrict oact);
 * 														返回值：若成功，返回0，若失败，返回-1
 *
 * sigprocmask函数可以检测和更改进程的信号屏蔽字。（信号屏蔽字：规定了当前阻塞而不能递送给该进程的信号集）
 * sigpending函数返回一个信号集，对于调用进程而言，其中的各信号是阻塞不能递送的，因而一定是当前未决的。该信号通过set参数返回。
 * sigaction函数的功能是检查或修改与指定信号相关联的处理动作。
 */

void pr_mask(const char *str)
{
	int errno_save;
	sigset_t sigset;

	errno_save = errno;

	if(sigprocmask(0, NULL, &sigset) < 0)
	{
		perror("sigprocmask error");
	}else
	{
		printf("%s", str);
		if(sigismember(&sigset, SIGINT))
		{
			printf("SIGINT");
		}
		if(sigismember(&sigset, SIGQUIT))
		{
			printf("SIGQUIT");
		}
		if(sigismember(&sigset, SIGUSR1))
		{
			printf("SIGUSR1");
		}
		if(sigismember(&sigset, SIGALRM))
		{
			printf("SIGALRM");
		}

		printf("\n");
	}

	errno = errno_save;
}

static void sig_quit(int);

int main(int argc, char const *argv[])
{
	sigset_t newmask;
	sigset_t oldmask;
	sigset_t pendmask;

	if(signal(SIGQUIT, sig_quit) == SIG_ERR)
		perror("can't catch SIGQUIT");

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	/**
	 * sigprocmask函数的使用方法：
	 * 		1.若最后一个参数是非空指针，那么进程的当前信号屏蔽字通过最后一个参数返回
	 * 		2.若第二个参数是非空指针，则第一个参数指示如何修改当前信号屏蔽字
	 */
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)		// 这里阻塞了SIGQUIT信号
		perror("SIG_BLOCK error");

	sleep(10);

	if(sigpending(&pendmask) < 0)						// 返回阻塞的（未决的）信号集，写在参数中
		perror("sigpending error");

	if(sigismember(&pendmask, SIGQUIT))					// 检测pending信号集中是否设置了SIGQUIT信号
		printf("\nSIGQUIT pending\n");

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)	// 解除SIGQUIT的阻塞信号
		perror("SIG_SETMASK error");

	printf("SIGQUIT unblocked\n");

	sleep(5);

	return 0;
}

static void sig_quit(int signo)
{
	printf("catch SIGQUIT\n");

	if(signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		perror("can't reset SIGQUIT");
}