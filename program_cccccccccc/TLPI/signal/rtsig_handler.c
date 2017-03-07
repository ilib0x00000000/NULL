#define _GNU_SOURCE
#define _POSIX_C_SOURCE 199309
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

/**
 * 信号处理函数：
 * 如果发送的实时信号携带了数据，要在信号处理程序中获取该数据，则要指定SA_SIGINFO参数
 * struct sigaction{
 *              void     (*sa_sigaction)(int, siginfo_t *, void *);
 *              int        sa_flags;
 *              sigset_t   sa_mask;
 *              void     (*sa_restorer)(void);
 * };
 *
 * void handler(int sig, siginfo_t *siginfo, void *ucontext);
 * typedef struct{
 *              int      si_signo;
 *              int      si_code;
 *              int      si_trapno;
 *              union sigval si_value;
 *              pid_t    si_pid;
 *              uid_t    si_uid;
 *              int      si_errno;
 *              void    *si_addr;
 *              int      si_overrun;
 *              int      si_timerid;
 *              long     si_band;
 *              int      si_fd;
 *              int      si_status;
 *              clock_t  si_utime;
 *              clock_t  si_stime;
 * }siginfo_t;
 */

static volatile int handlerSleepTime;
static volatile int sigCnt = 0;
static volatile int allDone = 0;

static void signal_handler(int sig, siginfo_t *si, void *ucontext)
{
        if(sig==SIGINT || sig==SIGTERM)
        {
                allDone = 1;
                return ;
        }

        sigCnt++;

        printf("..........................................\n");
        printf("收到一个信号\n");
        printf("si_signo = %d\n", si->si_signo);
        printf("si_code  = %d(%s)\n", si->si_code, (si->si_code==SI_USER) ? "SI_USER" : (si->si_code==SI_QUEUE) ? "SI_QUEUE" : "other");
        printf("si_value = %d\n", si->si_value.sival_int);
        printf("si_pid = %ld\n", (long)si->si_pid);
        printf("si_uid = %ld\n", (long)si->si_uid);

        sleep(handlerSleepTime);
}

int main(int argc, char const *argv[])
{
        int sig;
        struct sigaction sa;
        sigset_t prevMask;
        sigset_t blockMask;

        handlerSleepTime = (argc>1) ? atoi(argv[1]) : 1;

        // 配置信号处理函数
        sa.sa_sigaction = signal_handler;
        sa.sa_flags = SA_SIGINFO;
        sigfillset(&sa.sa_mask);

        for(sig=1; sig<NSIG; sig++)
        {
                if(sig!=SIGTSTP && sig!=SIGQUIT)
                        sigaction(sig, &sa, NULL);
        }

        if(argc>1)
        {
                sigfillset(&blockMask);
                sigdelset(&blockMask, SIGINT);
                sigdelset(&blockMask, SIGTERM);

                if(sigprocmask(SIG_SETMASK, &blockMask, &prevMask) == -1)
                {
                        printf("设置进程的信号掩码失败\n");
                        exit(EXIT_FAILURE);
                }

                printf("当前进程%ld将要睡眠%d\n", (long)getpid(), handlerSleepTime);


                if(sigprocmask(SIG_SETMASK, &prevMask, NULL) == -1)
                {
                        printf("恢复进程的信号掩码失败\n");
                        exit(EXIT_FAILURE);
                }
        }

        while(!allDone)
        {
                pause();
        }

        return 0;
}
