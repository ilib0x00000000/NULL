#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>

/**
 * 孤儿进程：由一个用户进程fork出来的子进程，父进程在子进程exit之前终止，则子进程变成孤儿进程，
 * 孤儿进程的父进程变成init进程。
 * 较新的Linux内核实现
 */

int main(int argc, char const *argv[])
{
	pid_t pid;

	pid = fork();

	if(pid < 0)
	{
		perror("fork error");
		exit(1);
	}
	if(pid == 0)
	{
		/*在子进程中*/
		printf("在父进程终止之前：\n");
		printf("父进程ID： %d \n", getppid());

		// 在父进程结束之后
		sleep(5);
		printf("在父进程结束之后：\n");
		printf("父进程ID： %d \n", getppid());
	}else
	{
		// 保证在父进程终止之前，子进程先运行一次
		sleep(2);
	}

	return 0;
}
/*
注意：在图形界面下运行得到如下：
	在父进程终止之前：
	父进程ID： 4075 
	在父进程结束之后：
	父进程ID： 2027 (ubuntu启动图形界面进程的ID)

在命令行模式下运行正常。
 */