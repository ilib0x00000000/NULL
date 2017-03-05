#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

/**
 * 获取进程的信号掩码
 * #include <signal.h>
 * int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
 * sigprocmask()既可以修改进程的信号掩码，也可以获取现有的掩码
 * 1. SIG_BLOCK: 将set指向信号集内的指定信号添加到进程信号掩码内，就是将当前信号掩码设置成其与set的并集
 * 2. SIG_UNBLOCK: 将set指向的信号集中信号从进程的信号掩码中去除
 * 3. SIG_SETMASK: 将set指向的信号集赋值给信号掩码
 *
 * 如果是查询信号掩码，则将set赋值为NULL，此时，将忽略how参数
 *
 *
 * 获取进程中处于等待的信号
 * #include <signal.h>
 * int sigpending(sigset_t *set);
 *                      返回值：若成功，返回0，若失败，返回-1
 */

static int sigcnt[NSIG];
static volatile sig_atomic_t gotsigint = 0;

int print_pendingsig(FILE *of, const char *msg);
void print_sigset(FILE *of, const char *prefix, const sigset_t *sigset);
int print_sigmask(FILE *of, const char *msg);


static void signal_handler(int sig);
static void signal_handler(int sig)
{
        if(sig == SIGINT)
                gotsigint = 1;
        else
                sigcnt[sig]++;
}



int main(int argc, char const *argv[])
{
        int n, numsecs;
        sigset_t pending_mask;
        sigset_t blocking_mask;
        sigset_t empty_mask;

        printf("当前进程的PID： %ld\n", getpid());

        for(n=1; n<NSIG; n++)
        {
                (void)signal(n, signal_handler);
        }

        if(argc > 1)
        {
                numsecs = atoi(argv[1]);

                sigfillset(&blocking_mask);   // 填满信号集
                if(sigprocmask(SIG_SETMASK, &blocking_mask, NULL) == -1)
                {
                        printf("设置信号掩码失败\n");
                        exit(EXIT_FAILURE);
                }

                printf("CPU休眠\n");
                sleep(numsecs);

                // 获取等待信号
                if(sigpending(&pending_mask) == -1)
                {
                        printf("获取等待信号失败\n");
                        exit(EXIT_FAILURE);
                }

                // 输出等待信号
                if(print_pendingsig(stdout, NULL) == -1)
                {
                        printf("输出等待信号失败\n");
                        exit(EXIT_FAILURE);
                }

                // 解阻塞所有信号
                sigemptyset(&empty_mask);
                if(sigprocmask(SIG_SETMASK, &empty_mask, NULL) == -1)
                {
                        printf("将进程的信号掩码设置为空失败\n");
                        exit(EXIT_FAILURE);
                }
        }

        while(!gotsigint)
                continue;

        for(n = 1; n < NSIG; n++)
        {
                if(sigcnt[n] != 0)
                        printf("信号%d:传递了%d次\n", n, sigcnt[n]);
        }

        return 0;
}


void print_sigset(FILE *of, const char *prefix, const sigset_t *sigset)
{
        int sig;
        int cnt;

        cnt = 0;
        for(sig=1; sig<NSIG; sig++)
        {
                if(sigismember(sigset, sig))
                {
                        cnt++;
                        fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
                }
        }

        if(cnt == 0)
                fprintf(of, "%s<empty signal set>\n", prefix);
}

int print_sigmask(FILE *of, const char *msg)
{
        sigset_t currMask;

        if(msg != NULL)
                fprintf(of, "%s\n", msg);

        if(sigprocmask(SIG_BLOCK, NULL, &currMask)==-1) // 获取当前进程的信号掩码，并存放在currMask中
        {
                return -1;
        }

        print_sigset(of, "\t\t", &currMask);
        return 0;
}

int print_pendingsig(FILE *of, const char *msg)
{
        sigset_t pendingSigs;

        if(msg != NULL)
        {
                fprintf(of, "%s\n", msg);
        }

        if(sigpending(&pendingSigs)==-1)  // 获取进程当前等待的信号
        {
                return -1;
        }
}

/**
 * 输出说明：
 * 最终的信号输出都是1次，因为是标准信号，所以进程对其不排队，也就是在等待的时候，同一个信号无论接受到多少次，最终进程只会给目标
 * 进程传递1次该信号
 *
 * 如果没有设置阻塞所有信号，则进程收到的信号可能是小于发送的次数的，原因如下：
 * 进程在一开始收到该信号，立即运行信号处理函数，此时内核会自动阻塞该信号。如果在信号处理时，同时接收到一个信号多次，则只传递该信号1次
 *
 * kill命令：
 * $ kill -s SIGINT pid
 * 例： kill -s SIGINT 12382
 */