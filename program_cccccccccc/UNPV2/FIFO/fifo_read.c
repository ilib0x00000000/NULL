#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<limits.h>
#include<sys/stat.h>
#include<sys/types.h>

#define FIFO_NAME "/tmp/fifo.test"


int main(int argc, char const *argv[])
{
	int res = 0;
	int fifo_fd = -1;
	int data_fd = -1;
	int bytes_read = 0;
	int bytes_sent = 0;
	char buffer[PIPE_BUF+1];
	const int open_mode = O_RDONLY;

	memset(buffer, 0, sizeof(buffer));

	printf("Process %d opening FIFO O_RDONLY\n", getpid());

	// 以只读阻塞方式打开命名管道文件
	fifo_fd = open(FIFO_NAME, open_mode);

	if(fifo_fd != -1)
	{
		bytes_read = read(fifo_fd, buffer, PIPE_BUF);
		buffer[bytes_read] = 0;

		while(bytes_read > 0)
		{
			printf("%s\n", buffer);

			bytes_read = read(fifo_fd, buffer, PIPE_BUF);
			buffer[bytes_read] = 0;
		}
	}else
	{
		fprintf(stderr, "Open FIFO error\n");
		exit(EXIT_FAILURE);
	}

	printf("Process %d finished\n", getpid());

	return 0;
}
