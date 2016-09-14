#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>


/**
 * 文件描述符标志：fd
 * 文件状态标志：read/write/append
 * 
 * fcntl函数可以改变已经打开文件的属性
 * #include<fcntl.h>
 * int fcntl(int fd, int cmd, / int arg /);
 * 						返回值：若成功，则依赖cmd，若出错，返回-1
 * 复制一个已有的描述符    cmd = F_DUPFD / F_DUPFD_CLOEXEC
 * 获取/设置文件描述符标志 cmd = F_GETFD / F_SETFD
 * 获取/设置文件状态标志   cmd = F_GETFL / F_SETFL
 * 获取/设置异步I/O所有权  cmd = F_GETOWN / F_SETOWN
 * 获取/设置记录锁         cmd = F_GETLK / F_SETLK / F_SETLKW
 */

int main(int argc, char const *argv[])
{
	int val;

	if(argc != 2)
	{
		perror("usage: cmd <descriptor>");
		exit(-1);
	}

	// 查看文件状态标志
	val = fcntl(atoi(argv[1]), F_GETFL, 0);
	if(val<0)
	{
		perror("fcntl error");
		exit(-1);
	}

	switch(val & O_ACCMODE)
	{
		case O_RDONLY:
			printf("read only");	
			break;
		case O_WRONLY:
			printf("write only");
			break;
		case O_RDWR:
			printf("read write");
			break;
		default:
			printf("unknown access mode");
	}

	if(val & O_APPEND)
		printf(", append");
	if(val & O_NONBLOCK)
		printf(", nonblocking");
	if(val & O_SYNC)
		printf(", synchronous writes\n");

	#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
		if(val & O_FSYNC)
			printf(", synchronous writes\n");
	#endif

	return 0;
}
