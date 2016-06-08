#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

/*
 _   _          _   _         _______ _       _ _______  _______  _______  _______  _______  _______  _______  _______ 
(_) | |        (_) | |       / _____ \\\     /// _____ \/ _____ \/ _____ \/ _____ \/ _____ \/ _____ \/ _____ \/ _____ \
| | | |        | | | |       |/     \| \\   // |/     \||/     \||/     \||/     \||/     \||/     \||/     \||/     \|
| | | |        | | | |______ ||     ||  \\ //  ||     ||||     ||||     ||||     ||||     ||||     ||||     ||||     ||
| | | |        | | | |_____ \||     ||   ||    ||     ||||     ||||     ||||     ||||     ||||     ||||     ||||     ||
| | | |        | | | |     \|||     ||  //\\   ||     ||||     ||||     ||||     ||||     ||||     ||||     ||||     ||
| | | |_______ | | | |____ /||\_____/| //  \\  |\_____/||\_____/||\_____/||\_____/||\_____/||\_____/||\_____/||\_____/|
|_| |_________||_| |_|______/\_______///    \\ \_______/\_______/\_______/\_______/\_______/\_______/\_______/\_______/

*************************************************************************************
@Email   ilib0x00000000@gmail.com
@Date    : 2016-06-08 09:24:39 
@version 0.1
*************************************************************************************
*/

/**
 * exec函数族(execl/execv)
 * 
 * int execl(const char *pathname, const char *arg, ...)
 * int execlp(const char *filename, const char *arg, ...)
 * int execlp(const char *pathname, const char *arg, ..., char *const envp[])
 *
 * int execv(const char *pathname, char *const argv[])
 * int execvp(const char *filename, char *const argv[])
 * int execve(const char *pathname, char *const argv[], char *const envp[])
 */


int main(int argc, char const *argv[])
{
	pid_t pid;
	int exec_code;

	pid = vfork();
	/**
	 * vfork函数不复制父进程的数据段，只和父进程共享数据段
	 * vfork通常和exec族函数一起使用，在子进程中创建一个新的进程
	 * 调用vfork时，父进程被挂起，子进程运行完exec族函数或者exit时，解除父进程的挂起状态
	 * vfork子进程的exec函数之后的代码不会执行
	 */

	if(pid < 0)
	{
		printf("vfork error\n");
		exit(1);
	}else
	if( pid == 0)
	{
		/*子进程执行的代码*/
		printf("Child process PID: %d\n", getpid());

		setenv("PS1", "CHILD\\$", 1);

		printf("Process %d: calling exec\n", getpid());

		/*调用exec族函数*/
		exec_code = execl("/bin/sh","echo abcd", NULL);

		if(exec_code<0)
		{
			printf("Process %4d: execl error\n", getpid());
			exit(0);
		}

		/*exec族之后的代码不会执行*/
		printf("Process %d: after child execl\n", getpid());
		printf("Process %d: child exit\n", getpid());

	}else
	{
		printf("Parent process PID: %d\n", getpid());
		printf("Process %d: The parent has fork process %d\n", getpid(), pid);
	}


	return 0;
}