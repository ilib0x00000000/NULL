#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>

/**
 * 套接字
 * #include<sys/socket.h>
 * int socket(int domain, int type, int protocol);
 * 						返回值：若成功，返回文件描述符，若出错，返回-1
 *
 * domain：
 * AF_INET			IPv4
 * AF_INET6			IPv6
 * AF_UNIX			UNIX域
 * AF_UPSPEC		未指定
 *
 * type:
 * SOCK_DGRAM		UDP
 * SOCK_RAW			IP协议的数据报接口
 * SOCK_SEQPACKET	
 * SOCK_STREAM		TCP
 *
 * 禁止一个套接字的I/O
 * #include<sys/socket.h>
 * int shutdown(int sockfd, int how);
 * 						返回值：若成功，返回0，若失败，返回-1
 * how=SHUT_RD		关闭读端
 * how=SHUT_WR		关闭写端
 * how=SHUT_RDWR	关闭读写端
 *
 * #include<arpa/inet.h>
 * uint32_t htonl(uint32_t hostint32);			返回值：以网络字节序表示的32位整数
 * uint16_t htons(uint16_t hostint16);			返回值：以网络字节序表示的16位整数
 * uint32_t ntohl(uint32_t netint32);			返回值：以主机字节序表示的32位整数
 * uint16_t ntohs(uint16_t netint16);			返回值：以主机字节序表示的16位整数
 *
 * const char *inet_ntop(int domain, const void *restrict addr, char *restrict str, socklen_t size);
 * 								返回值：若成功，返回地址字符串指针，若失败，返回NULL
 * int inet_pton(int domain, const char *restrict str, void *restrict addr);
 * 								返回值：若成功，返回1，若格式无效，返回0，若出错，返回-1
 * 
 * IPv4:
 * #include<netinet/in.h>
 * struct sockaddr_in{
 * 		sa_family_t		sin_family;
 * 		in_port_t		sin_port;		// uint16_t
 * 		struct in_addr	sin_addr;
 * };
 *
 * struct in_addr{
 * 		in_addr_t		s_addr;			// uint32_t
 * };
 */

void *new_thread(void *arg);


int main(int argc, char const *argv[])
{
	int err;
	int sockfd;							// 套接字描述符
	int connect_num;					// 允许同时连接的最大个数
	int connect_no = 0;					// 连接进来的请求返回的文件描述符
	char *address;						// 存放IP地址
	char addr_buf[INET_ADDRSTRLEN];		// 存放IPv4的缓冲区
	struct sockaddr_in linux_addr;		// linux下地址格式
	struct sockaddr_in client_addr;		// 客户端的地址
	struct socklen_t *len;

	// 创建socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0)
	{
		printf("socket failed\n");
		return -1;
	}

	linux_addr.sin_family = AF_INET;	// 地址的域
	linux_addr.sin_port   = 12345;		// 地址的端口
	linux_addr.sin_addr.s_addr = inet_addr("192.168.1.113");

	// 绑定地址和端口
	err = bind(sockfd, (struct sockaddr *)&linux_addr, sizeof(struct sockaddr));

	if(err != 0)
	{
		printf("bind error\n");
		return -1;
	}

	#ifdef SOMAXCONN
	connect_num = SOMAXCONN;
	#else
	connect_num = 1024;
	#endif

	// 监听
	err = listen(sockfd, connect_num);

	if(err != 0)
	{
		printf("listen error\n");
		return -1;
	}

	while(1)
	{
		// connect_no = accept(sockfd, (struct sockaddr *)&client_addr, len);
		connect_no = accept(sockfd, NULL, NULL);
		if(connect_no)
			printf("client connected.....\n");
	}

	return 0;
}

/**
 * linux C socket编程函数
 * #include<arpa/inet.h>
 * #include<sys/socket.h>
 * #include<netinet/in.h>
 * int socket(int domain, int type, int protocol);
 * int bind(int sockfd, const struct sockaddr *addr, socklen_t len);
 * int listen(int sockfd, int backlog);
 * int connect(int sockfd, const struct sockaddr* addr, socklen_t len);
 * int accept(int sockfd, struct sockaddr * restrict addr, socklen_t *restrict len);
 *
 * IP地址的二进制格式与点分十进制之间的转换
 * const char *inet_ntop(int domain, const void *restrict addr, char *restrict str, socklen_t size);
 * int inet_pton(int domain, const char *restrict str, void *restrict addr);
 *
 * Linux下的IP地址结构
 * struct sockaddr_in{
 * 		sa_family_t sin_family;
 * 		in_port_t   sin_port;
 * 		unsigned char sin_zero[8];
 * 		struct in_addr sin_addr;
 * };
 *
 * struct in_addr{
 * 		in_addr_t s_addr;
 * };
 */

void *new_thread(void *arg)
{

}

/**
 * 6个为数据传递而设计的套接字函数：
 * #include<sys/socket.h>
 * ----------------发送数据报
 * ssize_t send(int sockfd, const void *buf, size_t nbytes, int flags);
 * ssize_t sendto(int sockfd, const void *buf, size_t nbytes, int flags, const struct sockaddr *destaddr, socklen_t destlen);
 * ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);

 * ----------------接收数据报
 * ssize_t recv(int sockfd, void *buf, size_t nbytes, int flags);
 * ssize_t recvfrom(int sockfd, void *restrict buf, size_t len, int flags, struct sockaddr *restrict addr, socklen_t addrlen);
 * ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
 *
 * struct msghdr{
 * 		int       msg_flags;
 * 		int       msg_iovlen;
 * 		void      *msg_control;
 * 		void      *msg_name;
 * 		socklen_t msg_namelen;
 * 		socklen_t msg_controllen;
 * 		struct iovev *msg_iov;
 * };
 */