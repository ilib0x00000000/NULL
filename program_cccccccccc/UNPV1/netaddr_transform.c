#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>

void test_protocol_depend(void);
void test_protocol_dependless(void);


int main(int argc, char const *argv[])
{
	test_protocol_depend();
	test_protocol_dependless();

	return 0;
}

/**
 * #include<arpa/inet.h>
 * 将字符串ip转换成地址结构
 * int        inet_aton(const char *strptr, struct in_addr *addrptr);
 * 					返回值：若字符串有效，返回1，否则，返回0
 *
 * in_addr_t  inet_addr(const char *strptr);		弃用函数
 *
 * 将地址结构转换成ip字符串
 * char *     inet_ntoa(struct in_addr inaddr);
 */
void test_protocol_depend(void)
{
	char *ip = "132.157.4.86";
	struct sockaddr_in ipv4;                        // Linux下IPv4协议族地址结构

	memset(&ipv4, 0, sizeof(struct sockaddr_in));    // 使用地址结构之前先将其清零

	ipv4.sin_family = AF_INET;
	ipv4.sin_port   = htons(12345);

	if(inet_aton(ip, &(ipv4.sin_addr)))
		printf("sockaddr_in的第三个成员设置成功\n");
	else
		printf("ip字符串转换成地址结构失败\n");


	printf("ip: %s\n", inet_ntoa(ipv4.sin_addr));	
}


/**
 * 与协议无关的地址转换函数
 * #include<arpa/inet.h>
 * int         inet_pton(int family, const char *strptr, void *addrptr);
 * const char *inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
 *
 * 在将地址格式转换成字符串时，为了避免缓冲区溢出，可以指定一个系统常量
 * #include<netinet/in.h>
 * #define INET_ADDRSTRLEN   16
 * #define INET6_ADDRSTRLEN  46
 */

void test_protocol_dependless(void)
{
	int rtn;
	char *ip = "111.222.0.46";
	char buff[INET_ADDRSTRLEN];
	struct sockaddr_in ipv4;

	memset(&ipv4, 0, sizeof(struct sockaddr_in));

	ipv4.sin_family = AF_INET;
	ipv4.sin_port   = htons(12345);

	if((rtn = inet_pton(AF_INET, ip, &(ipv4.sin_addr))) == 1)
	{
		printf("sockaddr_in的第三个成员设置成功\n");
	}else
	{
		printf("sockaddr_in的第三个成员设置失败\n");
	}

	printf("网络地址结构转字符串： %s\n", inet_ntop(AF_INET, (struct sockaddr_in*)&(ipv4.sin_addr), buff, INET_ADDRSTRLEN));
}