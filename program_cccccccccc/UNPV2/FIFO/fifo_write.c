#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<limits.h>
#include<sys/stat.h>
#include<sys/types.h>



int main(int argc, char const *argv[])
{
	int res = 0;
	int fifo_fd = -1;
	int data_fd = -1;
	int bytes_sent = 0;
	int bytes_read = 0;
	char buffer[PIPE_BUF + 1];
	const int open_mode = O_WRONLY;
	const char *fifo_name = "/tmp/fifo.test";

	if(access(fifo_name, F_OK) == -1)
	{
		// 命名管道文件不存在
		// 创建命名管道
		if((res = mkfifo(fifo_name, 0777)) != 0 )
		{
			fprintf(stderr, "Could not create fifo %s\n", fifo_name);
			exit(EXIT_FAILURE);
		}
	}

	printf("Process %d opening FIFO O_WRONLY\n", getpid());

	// 以只写阻塞方式打开FIFO文件
	fifo_fd = open(fifo_name, open_mode);

	// 以只读方式打开指定文件
	data_fd = open(argv[1], O_RDONLY);

	printf("进程ID: %d, 命名管道文件描述符: %d\n", getpid(), fifo_fd);

	if(fifo_fd != -1)
	{
		// 读取文件数据
		bytes_read = read(data_fd, buffer, PIPE_BUF);
		buffer[bytes_read] = '\0';

		while(bytes_read)
		{
			// 向FIFO写数据
			if((res = write(fifo_fd, buffer, bytes_read)) == -1)
			{
				fprintf(stderr, "write error on fifo\n");
				exit(EXIT_FAILURE);
			}

			bytes_sent += bytes_read;
			bytes_read = read(data_fd, buffer, PIPE_BUF);
			buffer[bytes_read] = '\0';
		}

		close(fifo_fd);
		close(data_fd);
	}else
	{
		fprintf(stderr, "Open FIFO error\n");
		exit(EXIT_FAILURE);
	}

	printf("进程 %d finished\n", getpid());

	return 0;
}
