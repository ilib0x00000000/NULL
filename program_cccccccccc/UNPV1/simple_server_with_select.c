#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/select.h>


#define MAXLINE   4096
#define LOCALHOST "192.168.1.10"
#define PORT      33333
#define LISTENNUM 1024

int main(int argc, char const *argv[])
{
	int i, max_index, maxfd;
	int fd;
	int sockfd;
	int connfd;
	int nready;
	int client[FD_SETSIZE];
	char buf[MAXLINE];
	ssize_t n;
	fd_set loopset1;
	fd_set loopset2;
	socklen_t clilen;
	struct sockaddr_in clieaddr;
	struct sockaddr_in servaddr;

	/***********************************创建一个socket*************************************/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&clieaddr, 0, sizeof(clieaddr));

	/********************************设置server的地址结构*********************************/
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(PORT);
	inet_pton(AF_INET, LOCALHOST, &servaddr.sin_addr);

	bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(sockfd, LISTENNUM);

	/******************************为select函数初始化数据*********************************/
	FD_ZERO(&loopset1);
	FD_ZERO(&loopset2);

	maxfd = sockfd;
	max_index = -1;

	for(i = 0; i < FD_SETSIZE; i++)
	{
		client[i] = -1;
	}

	FD_SET(sockfd, &loopset1);

	/***********************************select调用****************************************/
	while(1)
	{
		loopset2 = loopset1;
		nready = select(maxfd+1, &loopset2, NULL, NULL, NULL);

		if(FD_ISSET(sockfd, &loopset2))
		{
			clilen = sizeof(clieaddr);
			connfd = accept(sockfd, (struct sockaddr *)&clieaddr, &clilen);

			for(i = 0; i < FD_SETSIZE; i++)
			{
				if(client[i] < 0)
				{
					client[i] = connfd;
					break;
				}
			}

			if(i == FD_SETSIZE)
			{
				perror("Too Much Client\n");
				exit(EXIT_FAILURE);
			}

			FD_SET(connfd, &loopset1);

			if(connfd > maxfd)
				maxfd = connfd;

			if(i > max_index)
				max_index = i;

			if(--nready <= 0)
				continue;
		}

		for(i = 0; i <= max_index; i++)
		{
			if( (fd = client[i]) < 0)
				continue;

			if(FD_ISSET(fd, &loopset2))
			{
				if((n = read(fd, buf, MAXLINE)) == 0)
				{
					close(fd);
					FD_CLR(fd, &loopset1);
					client[i] = -1;
				}else
				{
					write(fd, buf, n);
				}

				if(--nready <= 0)
					break;
			}
		}
	}

	return 0;
}

/**
 * select调用需要处于一个循环中：
 * 循环中主要做两件事：
 * 1. 如果监听套接字可读，新建已连接套接字描述符，并将其在另一个描述符集中设置，且数组中也设置对应的值
 * 2. 描述符集复制，如果描述符集中不光监听套接字描述符可读，已连接描述符套接字也可读，则都读取。
 */