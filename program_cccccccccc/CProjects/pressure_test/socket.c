#include<stdio.h>
#include<fcntl.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

// #define DEBUG 
/**
 * struct sockaddr_in{
 * 		sa_family_t         sin_family;
 * 		in_port_t           sin_port;
 * 		struct in_addr      sin_addr;
 * };
 *
 * in.h
 * typedef uint32_t in_addr_t;
 * struct in_addr{
 * 		in_addr_t s_addr;
 * };
 *
 * stdint.h
 * typedef unsigned int		uint32_t;
 */

int Socket(const char *host, int clientPort)
{
	int sock;
	unsigned int       inaddr;
	struct netent      *hostent;
	struct sockaddr_in ad;

	/**
	 * 得到struct sockaddr_in中的第一个成员
	 */
	memset(&ad, 0, sizeof(ad));
	ad.sin_family = AF_INET;

	/**
	 * 得到struct sockaddr_in中的第二个成员
	 */
	// 将字符串式IP转换成点分十进制IP
	inaddr = inet_addr(host);
	if(inaddr != INADDR_NONE)
		memcpy(&ad.sin_addr, &inaddr, sizeof(inaddr));
	else
	{
		// 已过时函数
		// hp = gethostbyname(host);
		// if(hp == NULL)
		// 	return -1;
		// memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);
		hostent = getnetbyname(host);
		if(hostent == NULL)
			return -1;
		ad.sin_addr.s_addr = hostent->n_net;
	}

	/**
	 * 得到struct sockaddr_in中的第三个成员
	 */
	ad.sin_port = htons(clientPort);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
		return sock;

	if(connect(sock, (struct sockaddr *)&ad, sizeof(ad)) < 0)
		return -1;

	return sock;
}

#ifdef DEBUG
int main(int argc, char const *argv[])
{
	int rtn;

	rtn = Socket("www.baidu.com", 80);

	return 0;
}
#endif
