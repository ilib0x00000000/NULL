#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/mman.h>

/**
 * 存储映射I/O能将一个磁盘文件映射到内存空间的一个缓冲区上，
 * 当从缓冲区中读取数据时，就相当于读文件中的相应字节
 * 将数据存入缓冲区中时，相应字节就自动写入文件
 *
 * #include<sys/mman.h>
 * void *mmap(void *addr, size_t len, int prot, int flag, int fd, off_t off);
 * 					addr: 缓冲区的地址
 * 					len:  要映射文件的长度
 * 					prot: 缓冲区的打开方式(读/写/可执行)
 * 					flag: 影响缓冲区的多种属性
 * 					fd:   打开的文件描述符
 * 					off:  偏移量
 * 修改缓冲区的权限：
 * int mprotect(void *addr, size_t len, int prot);
 * 
 * 如果映射的页已修改，将该页冲洗到被映射的文件中
 * int msync(void *addr, size_t len, int flags);
 *
 * 解除映射
 * int munmap(void *addr, size_t len);
 */

#define COPYINCR (1024*1024*1024)

int main(int argc, char const *argv[])
{
	int fdin, fdout;
	void *src, *dst;
	off_t fsz = 0;
	size_t copysz;
	struct stat sbuf;

	if((fdin = open(argv[1], O_RDONLY)) < 0)	
	{
		perror("can't open file for reading");
		exit(12);
	}

	if((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IXUSR | S_IRGRP | S_IROTH)) < 0)
	{
		perror("can't creat file for writing");
		exit(13);
	}

	/*获取输入文件的信息*/
	if(fstat(fdin, &sbuf) < 0)
	{
		perror("fstat error");
		exit(14);
	}

	/*指定输出文件的大小*/
	if(ftruncate(fdout, sbuf.st_size) < 0)
	{
		perror("ftruncate error");
		exit(15);
	}

	/*只要偏移量小于文件的大小*/
	while(fsz < sbuf.st_size)
	{
		if((sbuf.st_size - fsz) > COPYINCR)
			copysz = COPYINCR;
		else
			copysz = sbuf.st_size - fsz;

		/*将输入文件映射到内存上*/
		if( (src = mmap(0, copysz, PROT_READ, MAP_SHARED, fdin, fsz)) == MAP_FAILED)
		{
			perror("mmap error for input");
			exit(16);
		}

		/*将输出文件映射到内存上*/
		if( (dst = mmap(0, copysz, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, fsz)) == MAP_FAILED)
		{
			perror("mmap error for output");
			exit(17);
		}

		/**
		 * 将输入文件映射到内存的缓冲区上时，读取缓冲区就相当于读取文件
		 * 将输出文件映射到内存的缓冲区上时，写入缓冲区就相当于写入文件
		 */
		memcpy(dst, src, copysz);

		/*解除映射*/
		munmap(src, copysz);
		munmap(dst, copysz);

		fsz += copysz;
	}

	return 0;
}
