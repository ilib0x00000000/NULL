#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>

/**
 * IPC:
 * 		1.经典的IPC：管道、FIFO、消息队列、信号量和共享存储
 * 		2.套接字机制的网络IPC
 * 		3.IPC的某些高级特征
 */

#define MAXLINE 1024

int main(int argc, char const *argv[])
{
	int n;
	int fd[2];
	pid_t pid;
	char line[MAXLINE];

	/*创建管道*/
	if(pipe(fd) < 0)
	{
		perror("create pipe error");
		exit(-1);
	}

	pid = fork();
	if(pid < 0)
	{
		perror("create process error");
		exit(-1);
	}else
	if(pid == 0)
	{
		printf("child start ...\n");
		close(fd[1]);				// 关闭写端
		n = read(fd[0], line, MAXLINE);	// 从读端读取数据
		write(STDOUT_FILENO, line, n);
	}else
	{
		printf("parent prepare for writing\n");
		close(fd[0]);				// 关闭读端
		write(fd[1], "Hello world\n", 12);// 向写端写入数据
		printf("parent writed\n");
	}

	return 0;
}

/**
 * 管道：管道只能在具有公共祖先的两个进程之间使用。
 * 通常，一个管道由一个进程创建，在进程调用fork之后，这个管道就能在父进程和子进程之间使用了
 * #include<unistd.h>
 * int pipe(int fd[2]);
 * 				返回值：若成功，返回0，若失败，返回-1
 *
 * 当管道的一端被关闭后：
 * 1.当read一个写端已被关闭的管道时，在所有的数据都被读取后，read返回0，表示文件结束
 * 2.当write一个读端已被关闭的管道时，则产生信号SIGPIPE。如果忽略或捕捉该信号，则write返回-1，errno设置为EPIPE
 */