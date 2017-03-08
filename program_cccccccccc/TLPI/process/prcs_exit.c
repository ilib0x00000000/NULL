#define _BSD_SOURCE
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


/**
 * exit()和_exit()
 * #include<unistd.h>
 * void _exit(int status);
 *
 *
 * #include<stdlib.h>
 * void exit(int status);
 *
 * _exit()和exit()的区别：
 * exit()调用封装了_exit()调用
 * exit()调用如下：
 * 1. 调用退出处理程序（通过atexit()和on_exit()注册的函数），其执行的顺序与注册的顺序相反
 * 2. 刷新stdio流缓冲区
 * 3. 使用由status提供的值执行_exit()系统调用
 *
 *
 * 
 * 注册退出处理函数API
 * #include<stdlib.h>
 * int atexit(void (*func)(void));
 *                      返回值：若成功，返回0，若失败，返回非0
 *
 * #define _BSD_SOURCE
 * #include <stdlib.h>
 * int on_exit(void (*func)(int, void *), void *arg);
 *                      返回值：若成功，返回0，若失败，返回非0
 *
 * 1. 退出处理函数由程序员提供，可在进程生命周期的任意时点注册，并在进程调用exit()正常终止时自动执行
 * 2. 退出处理函数的执行顺序与注册时的顺序相反
 * 3. 退出处理函数里面不能再调用exit()函数
 */

void atexit_func1(void);
void atexit_func2(void);
void onexit_func1(int status, void *msg);
void onexit_func2(int status, void *msg);

int main(int argc, char const *argv[])
{
    if(atexit(atexit_func1) != 0)
    {
        printf("注册退出处理程序失败\n");
        exit(EXIT_FAILURE);
    }

    if(on_exit(onexit_func2, NULL) != 0)
    {
        printf("注册退出处理程序失败\n");
        exit(EXIT_FAILURE);
    }

    if(on_exit(onexit_func1, NULL) != 0)
    {
        printf("注册退出处理程序失败\n");
        exit(EXIT_FAILURE);
    }

    if(atexit(atexit_func2) != 0)
    {
        printf("注册退出处理程序失败\n");
        exit(EXIT_FAILURE);
    }

    exit(5);
    // return 0;
}



void atexit_func1(void)
{
    printf("运行退出处理函数1\n");
}
void atexit_func2(void)
{
    printf("运行退出处理函数2\n");
}
void onexit_func1(int status, void *msg)
{
    printf("运行退出处理函数3\n");
    printf("进程的退出状态参数是：%d\n", status);
    if(msg)
    {
        printf("进程传递进来的参数是：%s\n", (char *)msg);
    }
}
void onexit_func2(int status, void *msg)
{
    printf("运行退出处理函数4\n");
    printf("进程的退出状态参数是：%d\n", status);
    if(msg)
    {
        printf("进程传递进来的参数是：%s\n", (char *)msg);
    }
}