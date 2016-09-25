#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>

/**
 * 协同进程：一个程序既能通过管道得到输入，也可以通过另一个管道输出，就是协同进程。（两个单向管道）
 * 子进程：
 * 		管道1，只读不写
 *   	管道2，只写不读
 * 父进程：
 * 		管道1，只写不读
 * 		管道2，只读不写
 * 这样的子进程叫做协同进程
 */

#define MAXLINE 4096
static void sig_pipe(int);

int main(int argc, char const *argv[])
{
	int n;
	int fd1[2];
	int fd2[2];
	char line[MAXLINE];
	pid_t pid;

	if(signal(SIGPIPE, sig_pipe) == SIG_ERR)
	{
		perror("signal error");
		exit(127);
	}

	/*创建两个管道*/
	if(pipe(fd1)<0 || pipe(fd2)<0)
	{
		perror("create pipe error");
		exit(127);
	}

	pid = fork();

	if(pid < 0)
	{
		printf("create process error\n");
		exit(127);
	}else
	if(pid > 0)
	{
		/*parent*/
		close(fd1[0]);
		close(fd2[1]);

		while(fgets(line, MAXLINE, stdin) != NULL)
		{
			/*向管道1写入数据*/
			n = strlen(line);
			if(write(fd1[1], line, n) != n)
			{
				printf("write error to pipe\n");
				exit(127);
			}

			/*从管道2读取数据*/
			if((n = read(fd2[0], line, MAXLINE)) < 0)
			{
				printf("read error to pipe\n");
				exit(127);
			}
			if(n == 0)
			{
				printf("child closed pipe\n");
				break;
			}

			/*向终端输出结果数据*/
			line[n] = 0;
			if(fputs(line, stdout) == EOF)
			{
				printf("fputs error\n");
				exit(127);
			}
		}

		if(ferror(stdin))
		{
			printf("fgets error on stdin\n");
			exit(127);
		}
		exit(0);
	}else
	{
		/*child*/
		close(fd1[1]);
		close(fd2[0]);

		/*将子进程的标准输入设置为管道1的文件描述符*/
		if(fd1[0] != STDIN_FILENO)
		{
			if(dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
			{
				printf("can't copy pipe to stdin\n");
				exit(-1);
			}
			close(fd1[0]);
		}

		/*将子进程的标准输出设置为管道2的文件描述符*/
		if(fd2[1] != STDOUT_FILENO)
		{
			if(dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
			{
				printf("can't copy pipe to stdout\n");
				exit(-1);
			}
			close(fd2[1]);
		}

		if(execl("./add", "add", (char *)0) < 0)
		{
			printf("execl error\n");
			exit(-1);
		}
		exit(0);
	}

	return 0;
}

static void sig_pipe(int signo)
{
	printf("SIGPIPE caught\n");
	exit(1);
}

/***************************************************************add的源码********************************************************/
/*
int main(int argc, char const *argv[])
{
	int n, int1, int2;
	char line[MAXLINE];

	while((n=read(STDIN_FILENO, line, MAXLINE)) > 0)
	{
		line[n] = 0;

		if(sscanf(line, "%d%d", &int1, &int2) == 2)
		{
			sprintf(line, "%d\n", int1+int2);
			n = strlen(line);
			if(write(STDOUT_FILENO, line, n) != n)
			{
				perror("write error");
				exit(127);
			}
		}else
		{
			if(write(STDOUT_FILENO, "invalid args\n", 13) != 13)
			{
				perror("write error");
				exit(127);
			}
		}
	}

	return 0;
}

 */