#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


/**
 * 发送信号
 * #include<signal.h>
 * int kill(pid_t pid, int sig);
 *              返回值：若成功，返回0，若失败，返回-1
 * 若pid>0: 那么pid会发送信号给由pid指定的进程
 * 若pid==0: 那么会发送信号给与调用进程同组的每个进程，包括进程自身
 * 若pid<-1: 那么会向组ID等于该pid绝对值的进程组内所有下属进程发送信号
 * 若pid==-1: 信号的发送范围是调用进程有权将信号发往的每个目标进程，除去init和调用进程本身
 *
 * 若sig是0，表示发送空信号
 *
 * 向进程自身发送信号
 * #include<signal.h>
 * int raise(int sig);
 *              返回值，若成功，返回0，若失败，返回非0
 * 在单线程程序中，调用raise()相当于
 * kill(getpid(), sig)
 * 在多线程中
 * pthread_kill(pthread_self(), sig);
 *
 * 向进程组的所有成员发送一个信号
 * #include<signal.h>
 * int killpg(pid_t pgrp, int sig+);
 */


int main(int argc, char const *argv[])
{
    int s;
    int sig = SIGIO;
    pid_t pid = getpid();

    s = kill(pid+2, sig);   // 向进程pid发送信号sig

    if(sig != 0)
    {
        if(s == -1)
        {
            printf("发送信号失败\n");
            exit(EXIT_FAILURE);
        }else
        {
            printf("发送信号成功\n");
        }
    }else   // 发送了空信号
    {
        if(s == 0)
        {
            printf("pid指向的进程存在，且可以向该进程发送信号\n");
        }else
        {
            if(errno == EPERM)
                printf("pid指向的进程存在，但是没有权限向其发送信号\n");
            else if(errno == ESRCH)
                printf("进程不存在\n");
            else
                printf("未知错误\n");
        }
    }

    return 0;
}