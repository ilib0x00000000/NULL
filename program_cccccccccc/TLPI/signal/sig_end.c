#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

#include "sighelp.h"

/**
 * 终止信号处理程序的方法：
 * 1. 调用_exit()，处理函数可以先做一些清理工作。exit()函数不安全，因为其在调用_exit()之前，会刷新stdio缓冲区
 * 2. 使用kill()发送信号来杀死进程
 * 3. 从信号处理函数中执行非本地跳转
 * 4. 使用abort()函数终止进程，并产生核心存储
 *
 * 在进入信号处理函数时，内核会自动将引发调用的信号以及由act.sa_mask所指定的任意信号添加到进程的信号掩码中，并在
 * 处理器函数返回时再将他们从掩码中清除
 *
 * #include<setjmp.h>
 * int sigsetjmp(sigjmp_buf env, int saves);
 *                      返回值：初次调用返回0，当siglongjmp()调用返回非0
 * void siglongjmp(sigjmp_buf env, int saves);
 * 如果指定saves为非0，那么会将调用sigsetjmp()时进程的当前信号掩码保存于env中，之后通过指定相同
 * env参数的siglongjmp()调用进行恢复。如果saves不为0，则不会保存和恢复进程的信号掩码
 */

static volatile sig_atomic_t canJump = 0;


#ifdef USE_SIGSETJMP
        static sigjmp_buf senv;
#else
        static jmp_buf env;
#endif



static void signal_handler(int sig)
{
        printf("在信号处理函数中，进程的信号掩码：\n");
        print_sigmask(stdout, NULL);

        if(canJump)
        {
                /**
                 * 要设置canJump才能跳转
                 */
#ifdef USE_SIGSETJMP
                siglongjmp(senv,  1); // 跳转到进程中，并恢复进程的信号掩码
#else
                longjmp(env, 1);
#endif
        }

        printf("还不允许跳转\n");
        return ;
}



int main(int argc, char const *argv[])
{
        struct sigaction sa;

        print_sigmask(stdout, "进程当前的信号掩码");

        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sa.sa_handler = signal_handler;

        if(sigaction(SIGINT, &sa, NULL) == -1)
        {
                printf("调用信号处理函数失败\n");
                exit(EXIT_FAILURE);
        }

#ifdef USE_SIGSETJMP
        if(sigsetjmp(senv, 1)==0)
#else
        if(setjmp(env) == 0)
#endif
        canJump = 1;
        else
                print_sigmask(stdout,"从信号处理函数跳转回来之后的信号掩码");

        for(;;)
        {
                pause();
        }

        return 0;
} 

/**
 * 1. 直接编译
 * 输出
 * 进程当前的信号掩码
 *              <empty signal set>
 * ^C在信号处理函数中，进程的信号掩码：
 *              2 (Interrupt)
 * 从信号处理函数跳转回来之后的信号掩码
 *              2 (Interrupt)
 * ^C^C^C^C^C^C^C^C^C^C^C^C^\退出 (核心已转储)
 *
 * 输出原因：跳转回来之后的进程的信号掩码包含该信号处理函数针对的信号
 * 所以再传递相同的信号，被阻塞了
 *
 *
 * 2. gcc -D USE_SIGSETJMP ...
 * 输出
 * 进程当前的信号掩码
 *                      <empty signal set>
 * ^C在信号处理函数中，进程的信号掩码：
 *                      2 (Interrupt)
 * 从信号处理函数跳转回来之后的信号掩码
 *                      <empty signal set>
 * ^C在信号处理函数中，进程的信号掩码：
 *                      2 (Interrupt)
 * 从信号处理函数跳转回来之后的信号掩码
 *                      <empty signal set>
 * ^\退出 (核心已转储)
 */