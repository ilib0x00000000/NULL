#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>

/**
 * 改进：
 * 		处理了子进程结束时产生的SIGCHLD信号，避免了僵尸进程。
 * 		增强了accept函数(低速系统调用)调用的健壮性
 *
 * 注意：在子进程结束后，会产生SIGCHLD信号，如果此时正处于SIGCHLD信号处理程序运行时，则该信号会被屏蔽，
 * 且如果此时有多个SIGCHLD信号产生，则只会有一个信号在排队，所以在SIGCHLD信号处理程序中应该调用waitpid
 * 函数，且指定不阻塞
 */

#define LOCALHOST "192.168.1.113"
#define LISTENNUM 1024
#define PORT      33333

void sig_handler(int signo);

int main(int argc, char const *argv[])
{
	int sockfd;      // 监听套接字描述符
	int connfd;      // 已连接套接字描述符
	pid_t pid;
	socklen_t len;
	struct sockaddr_in servaddr;
	struct sockaddr_in clieaddr;
	struct sigaction sigchld;

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&clieaddr, 0, sizeof(clieaddr));

	/************************************设置信号处理结构***************************************/
	sigchld.sa_handler = sig_handler;     // 信号处理程序
	sigchld.sa_flags = 0;
	sigemptyset(&sigchld.sa_mask);        // 清空进程的信号屏蔽字


	/*********************************捕获信号并指定处理程序************************************/
	sigaction(SIGCHLD, &sigchld, NULL);



	/**************************************创建socket*******************************************/
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "Create Socket Error\n");
		exit(EXIT_FAILURE);
	}

	/**********************************设置地址结构的3个成员************************************/
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(PORT);
	inet_pton(AF_INET, LOCALHOST, &servaddr.sin_addr);


	/*****************************************关联主机******************************************/
	if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		fprintf(stderr, "绑定指定地址失败\n");
		exit(EXIT_FAILURE);
	}

	/**********************************指定已完成连接队列数目***********************************/
	if(listen(sockfd, LISTENNUM) < 0)
	{
		fprintf(stderr, "Listen Error\n");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		if((connfd = accept(sockfd, (struct sockaddr *)&clieaddr, &len)) < 0)
		{
			if(errno == EINTR)
				continue;      // 这里实现了accept被信号中断之后的重启动
			else
				fprintf(stderr, "Accept Error\n");
		}

		pid = fork();

		if(pid < 0)
		{
			fprintf(stderr, "创建子进程失败\n");
		}else
		if(pid == 0)
		{
			/********************************在子进程中********************************/
			close(sockfd);     // 关闭父进程的监听套接字描述符
			/* todo */
			close(connfd);     // 关闭已连接的套接字描述符
			exit(0);
		}else
		{
			/********************************在父进程中********************************/
			close(connfd);    // 关闭已连接套接字描述符
		}
	}

	close(sockfd);
	return 0;
}


void sig_handler(int signo)
{
	// 信号处理程序不能调用不可重入函数
	int stat;
	pid_t pid;

	pid = waitpid(-1, &stat, WNOHANG);
}