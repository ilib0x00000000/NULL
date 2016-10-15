#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/select.h>

/**
 * 使用select函数的TCP/UDP回射服务器
 * TCP服务器：使用并发模型
 * UDP服务器：使用迭代模型
 */

#define MAXLINE 4096

void str_echo(int connfd);
void signal_handler(int signo);

int main(int argc, char const *argv[])
{
	int listenfd, connfd, udpfd, nready, maxfd;
	char mesg[MAXLINE];
	pid_t childpid;
	fd_set rset;
	ssize_t n;
	socklen_t len;
	const int on = 1;
	struct sockaddr_in clieaddr;
	struct sockaddr_in servaddr;


	/************************************设置TCP监听套接字***********************************************/
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(33333);
	inet_pton(AF_INET, "192.168.1.113", &servaddr.sin_addr);

	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	/****************************************************************************************************/



	/************************************设置UDP监听套接字***********************************************/
	udpfd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(33333);
	inet_pton(AF_INET, "192.168.1.113", &servaddr.sin_addr);

	bind(udpfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	/****************************************************************************************************/


	signal(SIGCHLD, signal_handler);		// 信号处理函数中必须调用waitpid和可重入函数

	FD_ZERO(&rset);
	maxfd = (listenfd > udpfd ? listenfd : udpfd) + 1;

	while(1)
	{
		FD_SET(listenfd, &rset);
		FD_SET(udpfd, &rset);

		if((nready = select(maxfd, &rset, NULL, NULL, NULL)) < 0)
		{
			if(errno == EINTR)
				continue;
			else
			{
				fprintf(stderr, "%s\n", "Select Error");
				exit(EXIT_FAILURE);
			}
		}

		/* 如果listenfd可读 */
		if(FD_ISSET(listenfd, &rset))
		{
			len = sizeof(clieaddr);
			connfd = accept(listenfd, (struct sockaddr *)&clieaddr, &len);

			if((childpid = fork()) == 0)
			{
				/* 在子进程中 */
				close(listenfd);
				str_echo(connfd);
				exit(0);
			}

			/* 父进程不能忘记关闭已连接套接字描述符 */
			close(connfd);
		}

		/* 如果udpfd可读 */
		if(FD_ISSET(udpfd, &rset))
		{
			len = sizeof(clieaddr);
			n = recvfrom(udpfd, mesg, MAXLINE, 0, (struct sockaddr *)&clieaddr, &len);
			sendto(udpfd, mesg, n, 0, (struct sockaddr *)&clieaddr, len);
		}
	}

	return 0;
}


void str_echo(int connfd)
{
	// read
	// write
}

void signal_handler(int signo)
{
	/* 信号处理函数，必须调用waitpid函数，且指定不阻塞调用 */
}