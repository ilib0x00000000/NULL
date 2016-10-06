#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

/**
 * 参考：
 * http://www.tuicool.com/articles/V3Avey
 * 
 * 一个获取本地地址信息的函数
 * 一个获取外地地址信息的函数
 * 
 * #include<sys/socket.h>
 * int getsockname(int sockfd, struct sockaddr *localaddr, socklen_t *addrlen);
 * int getpeername(int sockfd, struct sockaddr *peeraddr,  socklen_t *addrlen);
 * 											返回值：若成功，返回0， 若失败，返回-1
 *
 * 子进程与父进程共享一片内存映像，如果子进程没有调用exec，则父进程保存的客户端地址，子进程也可以使用。
 * 当子进程调用了exec之后，子进程拥有自己的一片内存，则父进程保存的客户端地址无法再使用，这是需要通过已连接描述符
 * 调用getpeername获得客户端地址
 */

#define PORT    12345
#define MAXLINE 4096
#define LISTENQ 1024
#define LOCALHOST "192.168.1.113"


int main(int argc, char const *argv[])
{
	int sockfd;
	int connfd;
	int servlen;      // 服务端地址长度
	int clielen;      // 客户端地址长度
	char buff[INET_ADDRSTRLEN];     // 存放ip地址字符串的缓冲区
	struct sockaddr_in servaddr;    // 指定的服务端地址
	struct sockaddr_in clieaddr;    // 客户端地址
	struct sockaddr_in localaddr, peeraddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&localaddr, 0, sizeof(localaddr));
	memset(&peeraddr, 0, sizeof(peeraddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(PORT);
	inet_pton(AF_INET, LOCALHOST, &servaddr.sin_addr);

	bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(sockfd, LISTENQ);

	/* 获得监听套接字上的本地地址信息 */
	servlen = sizeof(localaddr);
	getsockname(sockfd, (struct sockaddr *)&localaddr, &servlen);

	printf("通过getsockname获得的监听套接字上的本地信息:"
		"localhost ip: %s\nport: %d\n", inet_ntop(AF_INET, &localaddr, buff, sizeof(buff)), ntohs(localaddr.sin_port));

	while(1)
	{
		connfd = accept(sockfd, (struct sockaddr *)NULL, NULL);   // 不保存客户端的地址信息

		/* 获得已连接套接字上的本地地址信息 */
		servlen = sizeof(localaddr);
		getsockname(connfd, (struct sockaddr *)&localaddr, &servlen);

		printf("通过getsockname获得已连接套接字上的本地信息:"
			"localhost ip: %s\nport: %d\n", inet_ntop(AF_INET, &localaddr, buff, sizeof(buff)), ntohs(localaddr.sin_port));

		/* 获得客户端的地址信息 */
		clielen = sizeof(peeraddr);
		getpeername(connfd, (struct sockaddr *)&peeraddr, &clielen);
		printf("通过getpeername获得已连接套接字上的客户端地址信息："
			"client ip: %s\nport: %d\n", inet_ntop(AF_INET, &peeraddr, buff, sizeof(buff)), ntohs(peeraddr.sin_port));
	}

	return 0;
}
