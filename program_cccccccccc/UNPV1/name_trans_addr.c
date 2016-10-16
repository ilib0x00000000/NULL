#include<stdio.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>


/**
 * 名字与地址转换：
 * gethostbyname/gethostbyaddr: 在主机名IPv4地址之间转换
 * getservbyname/getservbyport: 在服务名和端口号之间进行转换
 *
 * struct hostent{
 * 		char   *h_name;
 * 		char  **h_aliases;
 * 		int     h_addrtype;
 * 		int     h_length;
 * 		char  **h_addr_list;
 * };
 * struct hostent *gethostbyname(const char *hostname);
 * 										返回值：若成功，返回非NULL，若出错为NULL且设置h_errno
 *
 * struct hostent *gethostbyaddr(const char *addr, socklen_t len, int family);
 * 										返回值：若成功，返回非NULL，若出错为NULL且设置h_errno
 *
 * struct servent{
 * 		char   *s_name;
 * 		char  **s_aliases;
 * 		int     s_port;
 * 		char   *s_proto;
 * };
 * struct servent *getservbyname(const char *servname, const char *protoname);
 * 										返回值：若成功，返回非NULL，若出错为NULL
 *
 * struct servent *getservbyport(int port, const char *protoname);
 * 										返回值：若成功，返回非NULL，若出错为NULL
 *
 * 注意：设计到端口号时，有时需要使用的是网络字节序
 */
void test_gethostbyname(char *name);
void test_gethostbyaddr(char *ip);
void test_getservbyname(char *servname);
void test_getservbyport(int port);

int main(int argc, char const *argv[])
{
	// test_gethostbyname("baidu.com");
	// test_gethostbyaddr("111.13.101.208");
	// test_getservbyname("domain");			// domain 由 cat /etc/services 得到
	test_getservbyport(53);
	
	return 0;
}

void test_getservbyport(int port)
{
	char **list;
	struct servent *server;

	server = getservbyport(htons(port), NULL);     // 需要将主机字节序转换成网络字节序

	if(server == NULL)
	{
		fprintf(stderr, "该端口上没有服务\n");
		exit(EXIT_FAILURE);
	}

	printf("服务名: %s\n", server->s_name);
	printf("端口号: %d\n", ntohs(server->s_port));    // 端口号是网络字节序，需要转换成主机字节序
	printf("协议： %s\n", server->s_proto);

	for(list = server->s_aliases; *list!=NULL; list++)
	{
		printf("aliases: %s\n", *list);
	}	
}


void test_getservbyname(char *servname)
{
	char **list;
	struct servent *server;

	server = getservbyname(servname, NULL);

	printf("服务名: %s\n", server->s_name);
	printf("端口号: %d\n", ntohs(server->s_port));    // 端口号是网络字节序，需要转换成主机字节序
	printf("协议： %s\n", server->s_proto);

	for(list = server->s_aliases; *list!=NULL; list++)
	{
		printf("aliases: %s\n", *list);
	}
}


void test_gethostbyaddr(char *ip)
{
	char **list;
	char str[INET_ADDRSTRLEN]; // 用于存放IP地址的缓冲区
	struct hostent *host;

	// gethostbyname是协议依赖的，需要指定IPv4的地址长度和family
	host = gethostbyaddr(ip, 4, AF_INET);

	if(host == NULL)
	{
		fprintf(stderr, "gethostbyaddr 调用失败\nerror: %s\n", hstrerror(h_errno));
		exit(EXIT_FAILURE);
	}

	printf("cname: %s\n", host->h_name);
	printf("family: AF_INET\n");
	printf("length: %d\n", host->h_length);

	for(list=host->h_aliases; *list!=NULL; list++)
	{
		printf("aliases: %s\n", *list);
	}

	for(list=host->h_addr_list; *list!=NULL; list++)
	{
		inet_ntop(AF_INET, *list, str, sizeof(str));
		printf("IP: %s\n", str);
	}
}

void test_gethostbyname(char *name)
{
	char **list;
	char str[INET_ADDRSTRLEN];
	struct hostent *host;

	host = gethostbyname(name);

	if(host == NULL)
	{
		fprintf(stderr, "gethostbyname 调用失败\nerror:%s\n", hstrerror(h_errno));
		exit(EXIT_FAILURE);
	}

	printf("cname: %s\n", host->h_name);
	printf("family: AF_INET\n");
	printf("length: %d\n", host->h_length);

	for(list=host->h_aliases; *list != NULL; list++)
	{
		/* 如果该主机还有别名，输出该别名 */
		printf("aliases: %s\n", *list);
	}

	for(list=host->h_addr_list; *list!=NULL; list++)
	{
		/* 如果该主机还对应其他的地址，输出该地址 */
		inet_ntop(AF_INET, *list, str, sizeof(str));
		printf("IP: %s\n", str);
	}
}