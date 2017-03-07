#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "sighelp.h"

/**
 * sigsuspend函数API
 * #include<signal.h>
 * int sigsuspend(const sigset_t *mask);
 *              返回值：若sigsuspend()因信号的传递而中断，则将返回-1，并将errno设置为EINTR
 *                    若mask指向的地址无效，则sigsuspend()调用失败，并将errno设置为EFAULT
 * sigsuspend完成的功能如下（原子操作）：
 * 1. 使用mask替换掉原来的进程信号掩码
 * 2. 等待一个信号到达，并执行该信号处理程序
 * 3. 从该信号处理函数返回
 * 4. 恢复进程信号掩码
 *
 * sigsuspend()函数的作用：
 * 1. 临时阻塞一个信号，以防止其信号处理器将某些关键代码片段的执行中断
 * 2. 解除对信号的阻塞，然后暂停执行，直到有信号到达
 */

static volatile sig_atomic_t gotSigquit = 0;

void signal_handler(int sig)
{
        printf("捕捉到信号 %d (%s)\n", sig, strsignal(sig));
        print_sigmask(stdout, "信号处理函数中的信号掩码");

        if(sig == SIGQUIT)
                gotSigquit = 1;
}


int main(int argc, char const *argv[])
{
        int loopNum;
        time_t startTime;
        sigset_t origMask;
        sigset_t blockMask;
        struct sigaction sa;

        print_sigmask(stdout, "初始时，进程的信号掩码");


        // 将信号SIGINT和SIGQUIT添加到进程的信号掩码中，即阻塞SIGINT和SIGQUIT信号
        sigemptyset(&blockMask);
        sigaddset(&blockMask, SIGINT);
        sigaddset(&blockMask, SIGQUIT);
        if(sigprocmask(SIG_BLOCK, &blockMask, &origMask) == -1)
        {
                printf("设置进程信号掩码失败\n");
                exit(EXIT_FAILURE);
        }


        // 为指定信号建立处理程序
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sa.sa_handler = signal_handler;
        if(sigaction(SIGINT, &sa, NULL) == -1)
        {
                printf("建立SIGINT信号处理程序失败\n");
                exit(EXIT_FAILURE);
        }
        if(sigaction(SIGQUIT, &sa, NULL) == -1)
        {
                printf("建立SIGQUIT信号处理程序失败\n");
                exit(EXIT_FAILURE);
        }


        for(loopNum=1; !gotSigquit; loopNum++)
        {
                printf("=== LOOP %d\n", loopNum);

                print_sigmask(stdout, "......");
                for(startTime=time(NULL); time(NULL)<startTime+8;)
                        continue;

                print_pendingsig(stdout, "进程当前阻塞的信号");

                if(sigsuspend(&origMask)==-1 && errno!=EINTR)
                {
                        // 这里进程的信号掩码被设置成初始信号掩码，被阻塞的SIGINT信号递送过来
                        // 调用SIGINT信号处理函数
                        printf("sigsuspend调用失败\n");
                        exit(EXIT_FAILURE);
                }
        }

        print_sigmask(stdout, "sigsuspend返回之后的进程信号掩码");
        if(sigprocmask(SIG_SETMASK, &origMask, NULL) == -1)
        {
                printf("恢复进程信号掩码失败\n");
                exit(EXIT_FAILURE);
        }

        return 0;
}