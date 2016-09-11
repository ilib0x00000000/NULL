#include<time.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/select.h>
#include<netinet/in.h>

/**
 * #include<sys/select.h>
 * int select(int maxfdpl, 
 * 				fd_set *restrict readfds,
 * 				fd_set *restrict writefds,
 * 				fd_set *restrict exceptfds,
 * 				struct timeval *restrict tvptr);
 *
 * 传给select的参数告诉内核：
 * 				我们所关心的描述符
 * 				对于每个描述符我们所关心的条件（是否想从一个给定的描述符读，是否想写一个给定的描述符，是否关心一个给定描述符的异常条件）
 * 				愿意等多长时间
 *
 * 从select返回时，内核告诉我们：
 * 				已经准备好的描述符的总数量
 * 				对于读，写或异常这3个条件中的每一个，哪些描述符已准备好
 *
 * 操作描述集的函数
 * #include<sys/select.h>
 * int FD_ISSET(int fd, fd_set *fdset);
 * void FD_CLR(int fd, fd_set *fdset);
 * void FD_SET(int fd, fd_set *fdset);
 * void FD_ZERO(fd_set *fdset);
 *
 * #include<poll.h>
 * int poll(struct polled fdarray[], nfds_t nfds, int timeout);
 * 						返回值：准备就绪的描述符数目，若超时，返回0，若出错，返回-1
 *
 * struct polled{
 * 		int fd;
 * 		short events;
 * 		short revents;
 * }
 *
 * 可以通过将events设置为:
 * 			POLLIN			可以不阻塞的读高优先级数据以外的数据
 * 			POLLRDNORM		可以不阻塞的读普通数据
 * 			POLLRDBAND		可以不阻塞的读优先级数据
 * 			POLLPRI			可以不阻塞的读高优先级数据
 * 			----------------------------------------------------------------------
 * 			POLLOUT			可以不阻塞的写普通数据
 * 			POLLWRNORM		与POLLOUT相同
 * 			POLLWRBAND		可以不阻塞的写优先级数据
 * 			----------------------------------------------------------------------
 * 			POLLERR			已出错
 * 			POLLHUP			已挂断
 * 			POLLNVAL		描述符没有引用一个打开文件
 */

int main(int argc, char const *argv[])
{
	int n, res, flags, sockfd, recvbytes;
	int error = -1;
	char *sendData = "1234567890";		// 发送字符串
	char buf[1024] = "\0";				// 接收buffer
	fd_set rset;
	fd_set wset;
	socklen_t len;
	struct timeval tval;
	struct sockaddr_in serv_addr;

	// 创建socket描述符
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket create failed");
		return 1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(9999);
	serv_addr.sin_addr.s_addr = inet_addr("192.168.1.113");

	bzero(&(serv_addr.sin_zero), 8);
	flags = fcntl(sockfd, F_GETFL, 0);
	fcntl(sockfd, F_SETFL, flags|O_NONBLOCK);		// 设置为非阻塞

	if((res = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr))) < 0)
	{
		if(errno != EINPROGRESS)
		{
			return 1;
		}
	}

	while(error != 0)
	{
		tval.tv_sec = 0;
		tval.tv_usec = 3000000;
		FD_ZERO(&rset);
		FD_SET(sockfd, &rset);
		wset = rset;
		printf("enter while\n");

		res = select(sockfd+1, NULL, &wset, NULL, &tval);
		if(res == 0)
		{
			perror("connect time out\n");
		}else
		{
			if(res > 0)
			{
				len = sizeof(error);
				getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);
				
			}
		}
	}

	return 0;
}