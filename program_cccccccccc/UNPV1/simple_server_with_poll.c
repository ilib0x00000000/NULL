#include<poll.h>
#include<time.h>
#include<stdio.h>
#include<errno.h>
#include<limits.h>
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


/**
 * #include<poll.h>
 * int poll(struct pollfd *array, int num, int timeout);
 *
 * poll版单进程并发服务器：
 * 		定义一个描述符监听数组，数组中第一个是监听套接字描述符，后面的都是已连接套接字描述符
 *
 * 在poll每次返回时，主要完成两件事：
 * 		1. 如果监听套接字描述符可读，则读取监听套接字描述符，将得到的已连接套接字描述符，加入数组中
 * 		2. 如果数组中有已连接套接字描述符可读，则读取该描述符，最后将该数组元素的描述符位设置为-1
 */

#define MAX_FILE_SIZE 1024
#define LOCALHOST     "192.168.1.113"
#define LISTENNUM     1024
#define PORT          23333
#define MAXLINE       4096
#define INFTIM        -1

int main(int argc, char const *argv[])
{
	int maxfd = 0;
	int nready;
	int i, max_index;
	int sockfd, connfd;
	ssize_t n;
	char buff[MAXLINE];
	socklen_t length;
	struct sockaddr_in servaddr, clieaddr;
	struct pollfd clients[MAX_FILE_SIZE];

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&clieaddr, 0, sizeof(clieaddr));

	/* 设置服务器监听套接字 */
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(PORT);
	inet_pton(AF_INET, LOCALHOST, &servaddr.sin_addr);

	/* 开启网络监听 */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(sockfd, LISTENNUM);

	clients[0].fd = sockfd;     // pollfd数组的第一个描述符是监听套接字描述符
	clients[0].events = POLLRDNORM;

	for(i = 1; i < MAX_FILE_SIZE; i++)
	{
		clients[i].fd = -1;
		clients[i].events = POLLRDNORM;
	}

	while(1)
	{
		nready = poll(clients, maxfd+1, INFTIM);

		if(clients[0].revents == POLLRDNORM)
		{
			/* 如果监听套接字描述符可读 */
			length = sizeof(clieaddr);
			connfd = accept(sockfd, (struct sockaddr *)&clieaddr, &length);

			for(i = 1; i < MAX_FILE_SIZE; i++)
			{
				if(clients[i].fd < 0)
				{
					clients[i].fd = connfd;
					break;
				}
			}

			if(i > max_index)
				max_index = i;

			if(--nready <= 0)
				continue;
		}

		for(i = 1; i < max_index; i++)
		{
			/* 如果已连接套接字描述符可读 */
			if(clients[i].fd < 0)
				continue;

			if(clients[i].revents & (POLLRDNORM | POLLERR))
			{
				while((n = read(clients[i].fd, buff, MAXLINE)) > 0)
				{
					write(clients[i].fd, buff, MAXLINE);
				}

				if(n == 0)
				{
					close(clients[i].fd);
					clients[i].fd = -1;
				}else
				{
					if(errno == ECONNRESET)
					{
						close(clients[i].fd);
						clients[i].fd = -1;
					}else
					{
						fprintf(stderr, "Read Error\n");
					}
				}
			}

			if(--nready <= 0)
				break;
		}
	}

	return 0;
}