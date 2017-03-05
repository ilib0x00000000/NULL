#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

/**
 * 信号集：多个信号可使用一个称之为信号集的数据结构来表示，其数据类型为sigset_t
 *
 * 初始化信号集
 * #include<signal.h>
 * int sigemptyset(sigset_t *set);
 * int sigfillset(sigset_t *set);
 *              若成功，返回0，若失败，返回-1
 *
 * 向信号集中添加或删除信号
 * #include <signal.h>
 * int sigaddset(sigset_t *set, int sig);
 * int sigdelset(sigset_t *set, int sig);
 *              若成功，返回0，若失败，返回-1
 *
 * 测试信号集中是否有某个信号
 * #include<signal.h>
 * int sigismember(const sigset_t *set, int sig);
 *
 * 其他操作
 * #define _GNU_SOURCE
 * #include <signal.h>
 * int sigandset(sigset_t *dest, sigset_t *left, sigset_t *right);
 * int sigorset(sigset_t *dest, sigset_t *left, sigset_t *right);
 *              若成功，返回0，若失败，返回-1
 * int sigisempty(const sigset_t *set);
 * 1. 将left和right的交集赋值给dest
 * 2. 将left和right的并集赋值给dest
 * 3. 测试set是否为空
 * 
 */
void print_sigset(FILE *of, const char *prefix, const sigset_t *sigset);
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

int print_sigmask(FILE *of, const char *msg);
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

int print_pendingsig(FILE *of, const char *msg);
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


int main(int argc, char const *argv[])
{
        int i;
        pid_t pid;
        int nums;

        pid = atoi(argv[1]);                   // 信号要发往的进程pid
        nums = argc>2 ? atoi(argv[2]) : 10000; // 发送信号的次数

        printf("发送信号给进程%ld共%d次\n", pid, nums); 


        // 发送指定次数的相同信号
        for(i=0; i<nums; i++)
        {
                if(kill(pid, 10) == -1)
                {
                        printf("信号发送失败\n");
                        exit(EXIT_FAILURE);
                }
        }

        return 0;
}