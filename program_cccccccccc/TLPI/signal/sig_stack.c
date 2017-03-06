#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

/**
 * 在调用信号处理函数时，内核通常会在进程栈中为其创建一帧。不过，如果进程对栈的
 * 扩展突破了对栈的大小(RLIMIT_STACK)的限制时，就不再调用信号处理程序，
 * 而是选择默认行为
 *
 * #include<signal.h>
 * int sigaltstack(const stack_t *sigstack, stack_t *old_sigstack);
 *                      返回值：若成功，返回0，若失败，返回-1
 *
 * typedef struct{
 *              void  *ss_sp;
 *              int    ss_flags;
 *              size_t ss_size;
 * }stack_t;
 * 参数sigstack所指向的所指向的数据结构描述了新备选信号栈的位置及属性
 * 参数old_sigstack指向的结构则用于返回上一备选信号栈的相关信息（如果存在）
 *
 * ss_flags取值如下：
 *              SS_ONSTACK: 如果在获取已创建备选信号栈的当前信息时，该标志已然置位，就表明进程正在备选信号栈上执行。
 *                                      当进程已经在备选信号栈上运行时，试图调用sigaltstack()来创建一个新的备选信号栈就会产生一个错误(EPERM)
 *              SS_DISABLE: 在old_sigstack中返回，表示当前不存在已创建的备选信号栈。如果在sigstack中指定，则会
 *                                      禁用当前已创建的备选信号栈
 */

static void signal_handler(int sig)
{
        int x;

        printf("Caught signal %d (%s)\n", sig, strsignal(sig));
        printf("Top of handler stack near %10p\n", (void *)&x);

        fflush(NULL);

        _exit(EXIT_FAILURE);   // 硬件异常信号，不能正常返回
}


static void overflowStack(int callNum)
{
        /**
         * 递归调用，为了让栈溢出
         */
        char a[100000];

        printf("Call %4d - top of stack near %10p\n", callNum ,&a[0]);
        overflowStack(callNum+1);
}


int main(int argc, char const *argv[])
{
        int j;
        stack_t sigstack;
        struct sigaction sa;

        printf("TOP of standard stack is near %10p\n", (void *)&j);

        sigstack.ss_sp = malloc(SIGSTKSZ); // 申请备选栈的大小

        if(sigstack.ss_sp == NULL)
        {
                printf("无法申请内存\n");
                exit(EXIT_FAILURE);
        }

        sigstack.ss_size = SIGSTKSZ;
        sigstack.ss_flags = 0;

        if(sigaltstack(&sigstack, NULL) == -1)
        {
                printf("无法创建备选栈\n");
                exit(EXIT_FAILURE);
        }

        printf("备选栈地址在 %10p - %p\n", sigstack.ss_sp, (char *)sbrk(0)-1);

        // 设置信号处理函数
        sa.sa_handler = signal_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_ONSTACK;  // 指示信号处理函数使用备选栈

        if(sigaction(SIGSEGV, &sa, NULL) == -1)
        {
                printf("信号处理函数调用失败\n");
                exit(EXIT_FAILURE);
        }

        overflowStack(1); // 递归调用，会导致栈溢出，产生SIGSEGV信号

        return 0;
}