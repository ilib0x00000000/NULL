#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

/**
 * 信号：事件发生时对进程的通知机制，有时称之为软件中断
 * 信号分为：标准信号和实时信号
 * 信号处理函数：signal()/sigaction()
 *
 * API
 * #include<signal.h>
 * void (*signal(int sig, void (*handler)(int)))(int);
 *
 * 发送信号：
 * #include<signal.h>
 * int kill(pid_t pid, int  sig);
 * int raise(int sig);
 * int killpg(pid_t pgrp, int sig);
 */

void signal_handle(int signo);
void signal_handle(int signo)
{
        if(signo == SIGINT)
        {
                printf("进程接收到SIGINT信号\n");
                return ;
        }

        if(signo == SIGQUIT)
        {
                printf("进程接收到SIGQUIT信号\n");
        }
}

int main(int argc, char const *argv[])
{
        int i;

        if(signal(SIGQUIT, signal_handle) == SIG_ERR)
        {
                printf("调用信号处理函数失败\n");
                exit(EXIT_FAILURE);
        }

        if(signal(SIGINT, signal_handle) == SIG_ERR)
        {
                printf("调用信号处理函数失败\n");
                exit(EXIT_FAILURE);
        }

        for(i = 0; i<10; i++)
        {
                sleep(5);
        }

        return 0;
}