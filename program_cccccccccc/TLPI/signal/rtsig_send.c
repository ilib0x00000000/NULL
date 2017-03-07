#define _POSIX_C_SOURCE 199309
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


/**
 * 发送实时信号
 * #define _POSIX_C_SOURCE 199303
 * #include<signal.h>
 * int sigqueue(pid_t pid, int sig, const union sigval value);
 *                      返回值：若成功，返回0，若失败，返回-1
 * union sigval{
 *              int   sival_int;
 *              void *sival_ptr; // 很少用，因为指针的作用域仅在进程内部
 * };
 * 一旦触及对排队信号数量的限制，sigqueue()调用将会失败。同时将errno设置为EAGAIN，表示需要再次发送该信号
 */


int main(int argc, char const *argv[])
{
    int j;
    int numsigs;
    int sigdata;
    union sigval sv;

    printf("当前进程的pid是%ld, uid是%ld\n", (long)getpid(), (long)getuid());
    numsigs = argc>2 ? atoi(argv[2]) : 100;

    sigdata = 12;

    for(j = 0; j < numsigs; j++)
    {
        sv.sival_int = sigdata+j;
        if(sigqueue(atoi(argv[1]), SIGRTMIN+1, sv) == -1)
        {
            if(errno == EAGAIN)
            {
                printf("实时信号等待队列已满，请重新发送\n");
            }else
            {
                printf("发送实时信号失败\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}