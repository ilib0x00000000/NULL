#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

/**
 * #include<unistd.h>
 * ssize_t pread(int fd, void *buf, size_t nbytes, off_t offset);
 * 						返回值：读到的字节数，若已到文件尾，返回0，若出错，返回-1
 * ssize_t pwrite(int fd, const void *buf, size_t nbytes, off_t offset);
 * 						返回值：若成功，返回已写的字节数，若出错，返回-1
 *
 * 复制一个现有的文件描述符
 * #include<unistd.h>
 * int dup(int fd);
 * int dup2(int fd, int fd2);
 * 						返回值：若成功，返回新的文件描述符，若出错，返回-1
 *
 * 复制得到的文件描述符与被复制的文件描述符，指向一个相同的文件表项，
 * 所以共享同一文件状态标志以及同一当前文件偏移量
 *
 * UNIX系统实现时在内核中设置有缓冲区高速缓存或页高速缓存，大多数的磁盘I/O都通过缓冲区进行。
 * 当向文件写入数据时，内核常将数据复制到缓冲区中，然后排入队列，晚些时候再写入硬盘，这种方式叫做延迟写。
 *
 * #include<unistd.h>
 * int fsync(int fd);
 * int fdatasync(int fd);
 * 						返回值：若成功，返回0，若失败，返回-1
 * void sync(void);
 */

int main(int argc, char const *argv[])
{
	int fd;
	int fd1;
	char buffer[10];
	char text[1000];

	fd = open("a.txt", O_RDONLY);
	if(fd<0)
	{
		perror("open error");
		exit(-1);
	}

	if(read(fd, buffer, 10) == -1)
	{
		perror("read error");
		exit(-1);
	}
	printf("%s\n", buffer);

	fd1 = dup(fd);
	printf("%d\n", fd1);
	if( read(fd1, text, 1000) == -1)
	{
		printf("read error after dup\n");
		exit(-1);
	}
	printf("%s\n", text);

	close(fd);
	close(fd1);

	return 0;
}
