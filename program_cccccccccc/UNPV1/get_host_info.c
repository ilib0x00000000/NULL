#include<stdio.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

/**
int getaddrinfo(const char *node, const char *service, 
	const struct addrinfo *hints, struct addrinfo **res);

参数：
	node: 指向一个主机名或者地址串
	service: 指向一个服务名或者十进制端口号串

struct addrinfo{
	int       ai_flags;
	int       ai_family;
	int       ai_socktype;
	int       ai_protocol;
	socklen_t ai_addrlen;
	struct sockaddr *ai_addr;
	char     *ai_canonname;
	struct addrinfo *ai_next;
};

如果本函数返回成功，那么由res指向的变量被填入一个指针，可能是一个链表
1.如果与node参数关联的地址有多个，那么适用于所请求地址族的每个地址都返回一个对应的结构
2.如果service参数指定的服务支持多个套接字类型，那么每个套接字类型可能返回一个对应的结构，具体取决于hint结构的ai_socktype成员

node和service不能全为NULL
*/
void print_addrinfo(struct addrinfo *link);

int main(int argc, char const *argv[])
{
	char buff[INET_ADDRSTRLEN];
	struct addrinfo hints;
	struct addrinfo *res, *cur;
	struct sockaddr_in *addr;

	if(argc != 2)
	{
		fprintf(stderr, "%s\n", "usage: ./a.out <host>");
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family   = AF_INET;
	hints.ai_flags    = AI_PASSIVE;
	hints.ai_protocol = 0;
	hints.ai_socktype = SOCK_STREAM;

	ret = getaddrinfo(argc[1], NULL, &hints, &res);

	if(ret == 0)
	{
		/* 调用getaddrinfo函数成功 */
		for(cur = res; cur != NULL; cur = cur->ai_next)
		{
			inet_ntop(AF_INET, &cur->ai_addr, buff, sizeof(buff));
			printf("%s\n", buff);
			print_addrinfo(cur);
			printf("\n\n");
		}
	}else
	{
		fprintf(stderr, "%s\n", "调用getaddrinfo函数失败，请检查主机名是否正确或网络连接是否正常");
		exit(EXIT_FAILURE);
	}

	return 0;
}

void print_addrinfo(struct addrinfo *link)
{
	printf("ai_flags:    %d\n", link->ai_flags);
	printf("ai_family:   %d\n", link->ai_family);
	printf("ai_socktype: %d\n", link->ai_socktype);
	printf("ai_protocol: %d\n", link->ai_protocol);
	printf("ai_canonname:%s\n", link->ai_canonname);
	printf("socklen_t:   %d\n", link->ai_addrlen);
}
