#include"unp.h"

/**
 * fork函数创建的子进程与父进程共享描述符，通常情况下，子进程接着读写这个已连接套接字，父进程则关闭这个已连接套接字
 * fork的两个典型用法：
 * 		1. 一个进程创建一个自身的副本（子进程），这样每个副本都可以在另一个副本执行其他任务的同时处理自己的事务
 * 		2. 一个进程创建一个副本（子进程），然后子进程exec一个其他程序，这样副本的执行的程序彻底与父进程无关
 *
 * #include<unistd.h>
 * int excel(const char *pathname, const char *arg0, ...);
 * int execv(const char *pathname, char *const argv[]);
 * int execlp(const char *filename, const char *arg0, ...);
 * int execvp(const char *filename, char *const argv[]);
 * int execle(const char *pathname, const char *arg0, ...);
 * int execve(const char *pathname, char *const argv[], char *const envp[]);
 * 										返回值：若成功，不返回，若失败，返回-1
 * exec族函数的区别：
 * 		1. 待执行的程序是由文件名指定，还是路径名指定
 * 		2. 新程序的参数是一一列出还是由一个指针数组来引用
 * 		3. 把调用进程的环境传递给新程序还是给新程序指定新的环境
 *
 * 进程在调用exec之前打开的描述符默认在跨exec后继续保持打开，但是可以通过fcntl禁止掉
 */

#define LOCALHOST "192.168.1.113"
#define LISTENNUM 1024


int main(int argc, char const *argv[])
{
	int rtn;
	int connfd;
	int sockfd;
	pid_t pid;
	socklen_t len;
	struct sockaddr_in servaddr;
	struct sockaddr_in clinaddr;

	/***************************************************创建socket******************************************************/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		fprintf(stderr, "Create Socket Error\n");
		exit(EXIT_FAILURE);
	}

	/********************************************设置地址结构的三个成员*************************************************/
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(10086);
	inet_pton(AF_INET, LOCALHOST, &servaddr.sin_addr);

	/**************************************************绑定IP地址*******************************************************/
	rtn = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(rtn == -1)
	{
		fprintf(stderr, "绑定指定地址时失败\n");
		exit(EXIT_FAILURE);
	}

	/*******************************************指定已完成连接队列数目**************************************************/
	rtn = listen(sockfd, LISTENNUM);
	if(rtn == -1)
	{
		fprintf(stderr, "Listen Failed\n");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		/***************************************已完成连接套接字描述符********************************************/
		connfd = accept(sockfd, (struct sockaddr *)&clinaddr, &len);
		pid = fork();

		if(pid < 0)
		{
			fprintf(stderr, "创建子进程失败\n");
			exit(EXIT_FAILURE);
		}else
		if(pid == 0)
		{
			/********************************************在子进程中***********************************************/
			close(sockfd);
			/*todo*/
			close(connfd);
			exit(0);
		}else
		{
			/********************************************在父进程中***********************************************/
			close(connfd);
		}
	}

	return 0;
}


/**
 * 套接字描述符会由父进程复制一份给子进程，不管是监听套接字描述符，还是已连接套接字描述符
 * 已连接套接字描述符在传递给子进程之后，父进程也存在一份副本，父进程需要手动关闭，子进程可以不显示关闭，
 * 因为子进程结束后，内核会自动释放该文件描述符。
 */