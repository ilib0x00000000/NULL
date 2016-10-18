#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>

/**
 * 管道：由于没有名字，只能由有亲缘关系的进程使用
 * 当需要一个双向数据流时，必须创建两个管道，每个方向一个
 */

#define MAXLINE 4096

void server(int readfd, int writefd);
void client(int readfd, int writefd);


int main(int argc, char const *argv[])
{
	int pipe1[2];
	int pipe2[2];
	pid_t pid;

	pipe(pipe1);
	pipe(pipe2);

	if((pid = fork()) == 0)
	{
		/**
		 * 在子进程中
		 */
		close(pipe1[1]);           // 关闭管道1的写端
		close(pipe2[0]);           // 关闭管道2的读端

		server(pipe1[0], pipe2[1]);
		exit(0);
	}

	close(pipe1[0]);               // 关闭管道1的读端
	close(pipe2[1]);               // 关闭管道2的写端

	client(pipe2[0], pipe1[1]);

	waitpid(pid, NULL, 0);

	return 0;
}

void client(int readfd, int writefd)
{
	size_t len;
	ssize_t n;
	char buff[MAXLINE];

	/* 从标准输入读取数据 */
	fgets(buff, MAXLINE, stdin);

	len = strlen(buff);
	if(buff[len-1] == '\n')
		len--;

	/* 向管道中写入数据 */
	write(writefd, buff, len);

	/* 从管道中读取数据，并写向标准输出 */
	while((n = read(readfd, buff, MAXLINE)) > 0)
		write(STDOUT_FILENO, buff, n);
}

void server(int readfd, int writefd)
{
	int fd;
	ssize_t n;
	char buff[MAXLINE];

	if( (n = read(readfd, buff, MAXLINE)) == 0)
	{
		fprintf(stderr, "end-of-file while reading pathname\n");
		exit(EXIT_FAILURE);
	}

	buff[n] = '\0';

	if( (fd = open(buff, O_RDONLY)) < 0)
	{
		/* 打开文件出错，返回给客户端 */
		snprintf(buff+n, sizeof(buff)-n, ": can't open %s\n", strerror(errno));
		n = strlen(buff);
		write(writefd, buff, n);
	}else
	{
		while((n = read(fd, buff, MAXLINE)) > 0)
			write(writefd, buff, n);

		close(fd);
	}
}
