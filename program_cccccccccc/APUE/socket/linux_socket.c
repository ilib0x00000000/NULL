#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>

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
 *
 * #include<netdb.h>
 * struct hostent *gethostent(void);
 * void sethostent(int stayopen);
 * void endhostent(void);
 */


