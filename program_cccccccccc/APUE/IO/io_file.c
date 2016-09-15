#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/ioctl.h>

/**
 * ioctl函数可以处理很多设备I/O
 * #include<sys/ioctl.h>
 * int ioctl(int fd, int request, ...);
 * 						返回值：若出错，返回-1，若成功，返回其他值
 *
 * 文件：
 * #include<sys/stat.h>
 * int stat(const char *restrict pathname, struct stat *restrict buf);
 * int fstat(int fd, struct stat *buf);
 * int lstat(const char *restrict pathname, struct stat *restrict buf);
 * int fstatat(int fd, const char *restrict pathname, struct stat *restrict buf, int flag);
 * 						返回值：若成功，返回0，若出错，返回-1
 *
 * stat函数会返回pathname所指向的文件的信息结构
 * fstat函数会返回fd打开的文件的有关信息
 * lstat会返回链接文件的信息，而不是链接所指向的文件的信息
 *
 * struct stat{
 * 		mode_t             st_mode;      // 文件类型
 * 		ino_t              st_ino;
 * 		dev_t              st_dev;
 * 		dev_t              st_rdev;
 * 		nlink_t            st_nlink;
 * 		uid_t              st_uid;
 * 		gid_t              st_gid;
 * 		off_t              st_size;
 * 		struct timespec    st_atime;
 * 		struct timespec    st_mtime;
 * 		struct timespec    st_ctime;
 * 		blksize_t          st_blksize;
 * 		blkcnt_t           st_blocks;
 * };
 *
 * struct timespec{
 * 		time_t  tv_sec;
 * 		long    tv_nsec;
 * };
 *
 * 7种文件类型
 * 1.普通文件
 * 2.目录文件
 * 3.块特殊文件
 * 4.字符特殊文件
 * 5.FIFO
 * 6.套接字
 * 7.符号链接
 */


int main(int argc, char const *argv[])
{
	int i;
	char *ptr;
	struct stat buf;

	for(i = 1; i < argc; i++)
	{
		printf("%s: ", argv[i]);
		if( stat(argv[i], &buf) < 0)
		{
			perror("stat error");
			exit(-1);
		}

		if(S_ISREG(buf.st_mode))
			ptr = "regular";
		else if(S_ISDIR(buf.st_mode))
			ptr = "directory";
		else if(S_ISCHR(buf.st_mode))
			ptr = "character special";
		else if(S_ISBLK(buf.st_mode))
			ptr = "block special";
		else if(S_ISFIFO(buf.st_mode))
			ptr = "fifo";
		else if(S_ISLNK(buf.st_mode))
			ptr = "symbolic link";
		else if(S_ISSOCK(buf.st_mode))
			ptr = "socket";
		else
			ptr = "** unknown mode **";

		printf("%s\n", ptr);
	}

	return 0;
}
