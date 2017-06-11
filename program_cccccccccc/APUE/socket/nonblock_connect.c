#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>


int main(int argc, char const *argv[])
{
	int rc;
	int fd = 0;
	int err = 0;
	int flags;
	int errlen = sizeof(err);
	char *ip = "47.94.158.9";
	fd_set fdr;
	fd_set fdw;
	struct timeval timeout;
	struct sockaddr_in server_addr;


	fd = socket(AF_INET, SOCK_STREAM, 0);
	assert(fd > 0);

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port   = htons(9996);
	inet_pton(AF_INET, "47.94.158.9", &server_addr.sin_addr);

	// 设置fd为非阻塞
	flags = fcntl(fd, F_GETFL, 0);
	assert(flags > 0);
	assert(fcntl(fd, F_SETFL, flags|O_NONBLOCK) >= 0);

	// 非阻塞connect会立马返回-1
	// 需要使用select来确定是否连接上
	rc = connect(fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(rc != 0)
	{
		if(errno == EINPROGRESS)
		{
			printf("Doing connection\n"); // 正在处理连接
			FD_ZERO(&fdr);  // 可读集合
			FD_ZERO(&fdw);  // 可写集合
			FD_SET(fd, &fdr);
			FD_SET(fd, &fdw);
			timeout.tv_sec = 10;
			timeout.tv_usec = 0;

			rc = select(fd+1, &fdr, &fdw, NULL, &timeout);

			// 调用select失败
			if(rc < 0)
			{
				fprintf(stderr, "connect error: %s\n", strerror(errno));
				close(fd);
				return -1;
			}

			// 连接超时
			if(rc == 0)
			{
				fprintf(stderr, "Connect timeout.\n");
				close(fd);
				return -1;
			}

			// 连接成功，描述符可写
			if(rc==1 && FD_ISSET(fd, &fdw))
			{
				printf("Connect success\n");
				// to do ...
				close(fd);
				return 0;
			}

			// 连接出现错误，描述符即可读也可写
			if(rc == 2)
			{
				// 调用getsockopt()获取失败原因
				if(getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &errlen) == -1)
				{
					fprintf(stderr, "getsockopt(SO_ERROR): %s\n", strerror(errno));
					close(fd);
					return -1;
				}

				if(err)
				{
					errno = err;
					fprintf(stderr, "connect error: %s\n", strerror(errno));
					close(fd);
					return -1;
				}
			}
		}else
		{
			fprintf(stderr, "connect failed, error: %s.\n", strerror(errno));
			return -1;
		}
	}else
	{
		printf("connect immediately\n");
		// to do
		close(fd);
	}

	return 0;
}