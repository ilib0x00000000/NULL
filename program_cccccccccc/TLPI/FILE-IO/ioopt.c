#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
 * IO主要的4个系统调用
 * int open(const char *pathname, int flags,... /mode_t mode/);
 * ssize_t read(int fd, void *buffer, size_t count);
 * ssize_t write(int fd, void *buffer, size_t count);
 * int close(int fd);
 *
 * 
 * IO重要的3个函数
 * int creat(const char *pathname, mode_t mode);
 * off_t lseek(int fd, off_t offset, int whence);
 * #include<sys/ioctl.h>
 * int ioctl(int fd, int request, ... /argp/);
 *
 * 0   标准输入   STDIN_FILENO    stdin
 * 1   标准输出   STDOUT_FILENO   stdout
 * 2   标准错误   STDERR_FILENO   stderr
 *
 * 
 */

#define BUF_SIZE 1024

int main(int argc, char const *argv[])
{
	int inputFd;
	int outputFd;
	int openFlags;
	mode_t filePerms;
	ssize_t numRead;
	char buf[BUF_SIZE];

	if(argc!=3 || strcmp(argv[1], "--help")==0)
	{
		printf("Usage %s: 当前文件 目标文件\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/**
	 * #include<fcntl.h>
	 * #include<sys/stat.h>
	 * int open(const char *pathname, int flags, /mode_t mode/);
	 * pathname表示要打开的文件
	 * flags指定文件的访问模式
	 * mode在创建文件时，指定文件的权限
	 * 返回值：若成功，返回文件描述符。若失败，返回-1
	 *
	 * 创建文件时指定的权限不仅仅依赖于参数mode，而且受到进程的umask值和父目录的默认访问控制列表影响
	 */
	inputFd = open(argv[1], O_RDONLY);
	if(inputFd == -1)
	{
		perror("open file error");
		exit(EXIT_FAILURE);
	}

	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	outputFd = open(argv[2], openFlags, filePerms);
	/**
	 * open的flags常量分为以下3组：
	 * 1. 文件访问模式：只读只写或读写
	 * 2. 文件创建标志
	 * 3. 已打开文件的状态标志，使用fcntl()的F_GETFL和F_SETFL操作可以分别检索和修改此类标志
	 */

	if(outputFd == -1)
	{
		perror("open File Error");
		exit(EXIT_FAILURE);
	}

	while((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
	{
		if(write(outputFd, buf, numRead) != numRead)
		{
			perror("Write Error");
			exit(EXIT_FAILURE);
		}
	}

	if(numRead == -1)
	{
		perror("Read Error");
		exit(EXIT_FAILURE);
	}

	assert(close(inputFd) != -1);
	assert(close(outputFd) != -1);

	return 0;
}