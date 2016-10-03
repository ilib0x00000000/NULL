#include<time.h>
#include<unistd.h>
#include<signal.h>
#include<getopt.h>
#include<strings.h>
#include<sys/param.h>
#include<rpc/types.h>

#include"socket_beta1.0.h"

#define METHOD_GET     0
#define METHOD_HEAD    1
#define METHOD_OPTIONS 2
#define METHOD_TRACE   3

#define PROGRAM_VERSION "1.5"


/* values */
volatile int timerexpired = 0;
int speed = 0;
int failed = 0;
int bytes = 0;

/* globals */
int http10 = 1;
/**
 * 0 - http/0.9
 * 1 - http/1.0
 * 2 - http/1.1
 */

int method       = METHOD_GET;
int clients      = 1000;
int force        = 0;
int force_reload = 0;
int proxyport    = 80;
char *proxyhost  = NULL;
int benchtime    = 100;

int mypipe[2];
char host[MAXHOSTNAMELEN];

#define REQUEST_SIZE 2048
char request[REQUEST_SIZE];

static const struct option long_options[] = {
	{"force",  no_argument,       &force,        1},
	{"reload", no_argument,       &force_reload, 1},
	{"time",   required_argument, NULL,          't'},
	{"help",   no_argument,       NULL,          '?'},
	{"http09", no_argument,       NULL,          '9'},
	{"http10", no_argument,       NULL,          '1'},
	{"http11", no_argument,       NULL,          '2'},
	{"get",    no_argument,       &method,       METHOD_GET},
	{"head",   no_argument,       &method,       METHOD_HEAD},
	{"options",no_argument,       &method,       METHOD_OPTIONS},
	{"trace",  no_argument,       &method,       METHOD_TRACE},
	{"version",no_argument,       NULL,          'V'},
	{"proxy",  required_argument, NULL,          'p'},
	{"clients",required_argument, NULL,          'c'},
	{NULL,     0,                 NULL,          0},
};

static void usage(void);
static void build_request(const char *url);
static int bench(void);
static void benchcore(const char *host, const int port, const char *request);
static void alarm_handler(int signo);

int main(int argc, char const *argv[])
{
	int opt = 0;
	int options_index = 0;
	char *tmp = NULL;

	if(argc == 1)
	{
		usage();
		return 2;
	}

	while((opt = getopt_long(argc, argv, "912Vfrt:p:c:?h", long_options, &options_index)) != EOF)
	{
		switch(opt)
		{
			case  0 : break;
			case 'f': force = 1; break;
			case 'r': force_reload = 1; break;
			case '9': http10 = 0; break;
			case '1': http10 = 1; break;
			case '2': http10 = 2; break;
			case 'V': printf(PROGRAM_VERSION"\n"); exit(EXIT_SUCCESS);
			case 't': benchtime = atoi(optarg); break;
			case 'p':
				/* proxy server parsing server:port */
				tmp = strrchr(optarg, ':');
				proxyhost = optarg;

				if(tmp == NULL)
					break;
				if(tmp == optarg)
				{
					fprintf(stderr, "Error in option --proxy %s: Missing hostname.\n", optarg);
					return 2;
				}
				if(tmp == optarg+strlen(optarg)-1)
				{
					fprintf(stderr, "Error in option --proxy %s Port number is missing.\n", optarg);
					return 2;
				}
				*tmp = '\0';
				proxyport = atoi(tmp+1); break;
			case ':':
			case 'h':
			case '?': usage(); break;
			case 'c': clients = atoi(optarg); break;
		}

		if(optind == argc)
		{
			fprintf(stderr, "webbench: Missing URL.\n");
			usage();
			return 2;
		}

		if(clients == 0)
			clients = 1;
		if(benchtime == 0)
			benchtime = 60;

		fprintf(stderr, "webbench - Simple Web Benchmark "PROGRAM_VERSION"\n"
				"Github: https://github.com/EZLippi/WebBench/blob/master/webbench.c#L82"
			);

		build_request(argv[optind]);

		printf("\nBenchmarking: ");
		switch(method)
		{
			case METHOD_GET:
			default:
				printf("GET");
				break;
			case METHOD_OPTIONS:
				printf("OPTIONS");
				break;
			case METHOD_HEAD:
				printf("HEAD");
				break;
			case METHOD_TRACE:
				printf("TRACE");
				break;
		}
		printf(" %s", argv[optind]);
		switch(http10)
		{
			case 0: printf(" (using HTTP/0.9)"); break;
			case 2: printf(" (using HTTP/1.1)"); break;
		}
		printf("\n");

		if(clients == 1)
			printf("1 client");
		else
			printf("%d clients", clients);

		printf(", running %d sec\n", benchtime);

		if(force)
			printf(", early socket close");
		if(proxyhost != NULL)
			printf(", via proxy server %s: %d", proxyhost, proxyport);
		if(force_reload)
			printf(", forcing reload");
		printf(".\n");

		return bench();
	}

	return 0;
}

static void alarm_handler(int signo)
{
	timerexpired = 1;
}

static void benchcore(const char *host, const int port, const char *request)
{
	int i;
	int sock;
	int rlen;
	char buf[1500];
	struct sigaction sa;

	/* 设置信号处理函数 */
	sa.sa_handler = alarm_handler;   // 定时器函数
	sa.sa_flags = 0;

	if(sigaction(SIGALRM, &sa, NULL))
		exit(3);

	alarm(benchtime);                // 在指定时间后产生定时器信号

	rlen = strlen(request);

	nexttry:while(1)
	{
		if(timerexpired)             // 定时器函数中设置的值
		{
			if(failed > 0)
			{
				failed--;
			}

			return ;
		}
		
		if( (sock = create_socket(host, port)) < 0)
		{
			/* 连接失败，failed值加1 */
			failed++;
			continue;
		}
		if(rlen != write(sock, request, rlen))
		{
			/* 发送失败 */
			failed++;
			close(sock);
			continue;
		}
		/**
		 * SHUT_RD      0
		 * SHUT_WR      1
		 * SHUT_RDWR    2
		 */
		if(http10 == 0)
			if(shutdown(sock, 1))    // 关闭socket的写端
			{
				failed++;
				close(sock);
				continue;
			}

		/* force=0表示要读取http请求数据 */
		if(force == 0)
		{
			while(1)
			{
				if(timerexpired)
					break;

				i = read(sock, buf, 1500);

				if(i < 0)            // 读取response失败
				{
					failed++;
					close(sock);
					goto nexttry;
				}else
				if(i == 0)           // 读取response完毕
					break;
				else
					bytes+=i;
			}
		}
		if(close(sock))
		{
			failed++;
			continue;
		}

		speed++;
	}
}

static int bench(void)
{
	int i, j, k;
	int sock;
	pid_t pid;
	FILE *f;

	/**
	 * 如果指定代理，则连接代理的IP，否则连接主机(host)
	 * 这里应该是先测试Socket会不会处问题
	 */
	if((sock = create_socket(proxyhost==NULL?host:proxyhost,  proxyport)) < 0)
	{
		fprintf(stderr, "\nConnect to server failed. Aborting benchmark\n");
		return 1;
	}
	close(sock);

	/* 创建一个管道，用于父进程和子进程之间的通信 */
	if(pipe(mypipe))
	{
		fprintf(stderr, "create pipe error\n");
		return 3;
	}

	/* 创建子进程 */
	for(i = 0; i < clients; i++)
	{
		pid = fork();

		if(pid <= 0)
		{
			sleep(1);
			break;
		}
	}

	if(pid < 0)
	{
		fprintf(stderr, "problems forking worker no.%d\n", i);
		perror("fork failed");
		return 3;
	}

	if(pid == 0)
	{
		/* 在子进程中 */
		if(proxyhost == NULL)
			benchcore(host, proxyport, request);
		else
			benchcore(proxyhost, proxyport, request);

		// 将文件描述符转成文件指针
		if((f = fdopen(mypipe[1], "w")) == NULL)
		{
			fprintf(stderr, "open pipe for writing failed.\n");
			return 3;
		}

		/* 向管道写入数据 */
		fprintf(f, "%d %d %d\n", speed, failed, bytes);
		fclose(f);

		return 0;
	}else
	{
		/* 在父进程中 */
		f = fdopen(mypipe[0], "r");
		if(f == NULL)
		{
			fprintf(stderr, "open pipe for reading failed.");
			return 3;
		}

		/* 将管道流改成不带缓冲 */
		setvbuf(f, NULL, _IONBF, 0);

		speed = failed = bytes = 0;

		while(1)
		{
			pid = fscanf(f, "%d %d %d", &i, &j, &k);
			if(pid < 2)
			{
				fprintf(stderr, "有子进程挂掉了\n");
			}

			speed += i;
			failed += j;
			bytes += k;

			if(--clients == 0)
				break;
		}

		fclose(f);

		printf("\nSpeed = %d pages/min, %d bytes/sec.\nRequest: %d succeed, %d failed.\n", 
			(int)((speed+failed)/(benchtime/60.0f)),
			(int)(bytes/(float)benchtime),
			speed, failed);

		return i;
	}
}

static void build_request(const char *url)
{
	int i;
	char tmp[10];

	printf("%s\n", url);

	// 不推荐使用函数
	// bzero(host, MAXHOSTNAMELEN);
	// bzero(request, REQUEST_SIZE);
	memset(host, '\0', MAXHOSTNAMELEN);
	memset(request, '\0', REQUEST_SIZE);

	if(force_reload && proxyhost!=NULL && http10<1)
		http10 = 1;
	if(method == METHOD_HEAD && http10<1)
		http10 = 1;
	if(method == METHOD_OPTIONS && http10<2)
		http10 = 2;
	if(method == METHOD_TRACE && http10<2)
		http10 = 2;

	switch(method)
	{
		default:
		case METHOD_GET: strcpy(request, "GET"); break;
		case METHOD_HEAD: strcpy(request, "HEAD"); break;
		case METHOD_OPTIONS: strcpy(request, "OPTIONS"); break;
		case METHOD_TRACE: strcpy(request, "TRACE"); break;
	}

	strcat(request, " ");

	if(NULL == strstr(url, "://"))
	{
		fprintf(stderr, "%s\n", url);
		fprintf(stderr, "\n%s: is not a valid URL.\n", url);
		exit(2);
	}
	if(strlen(url) > 1500)
	{
		fprintf(stderr, "URL is too long.\n");
		exit(2);
	}

	i = strstr(url, "://")-url+3;
	if(strchr(url+i, '/') == NULL)
	{
		fprintf(stderr, "\nInvalid URL syntax - hostname don't with '/'.");
		exit(2);
	}

	if(proxyhost == NULL)
	{
		/* 如果没有指定代理 */
		if(index(url+i, ':')!=NULL && index(url+i,':')<index(url+i,'/'))
		{
			strncpy(host, url+i, strchr(url+i, '/')-url-i);
			memset(tmp, '\0', 10);
			strncpy(tmp, index(url+i, ':')+1, strchr(url+i, '/')-index(url+i, ':')-1);
			#ifdef DEBUG
			printf("%s\n", tmp);
			#endif
			proxyport = atoi(tmp);
			if(proxyport == 0)
				proxyport = 80;
		}else
		{
			strncpy(host, url+i, strcspn(url+i, "/"));
		}
		strcat(request+strlen(request), url+i+strcspn(url+i, "/"));
	}else
	{
		strcat(request, url);
	}

	if(http10 == 1)
		strcat(request, " HTTP/1.0");
	else if(http10 == 2)
		strcat(request, " HTTP/1.1");
	strcat(request, "\r\n");

	if (http10 > 0)
	{
		strcat(request, "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.92 Safari/537.36\r\n");
	}

	if(proxyhost == NULL && http10>0)
	{
		strcat(request, "Host: ");
		strcat(request, host);
		strcat(request, "\r\n");
	}

	if(force_reload && proxyhost!=NULL)
		strcat(request, "Pragma: no-cache\r\n");
	if(http10 > 1)
		strcat(request, "Connection: close\r\n");
	if(http10 > 0)
		strcat(request, "\r\n");
}

static void usage(void)
{
	fprintf(stderr, "webbench [option] ... URL\n"
		" -f|--force                    Don't wait for reply from server.\n"
		" -r|--reload                   Send reload request - Pragma: no-cache.\n"
		" -t|--time <sec>               Run benchmark for <sec> seconds. Default 30.\n"
		" -p|--proxy <server:port>      Use proxy server for request.\n"
		" -c|--clients <n>              Run <n> HTTP clients at once. Default one.\n"
		" -9|--http09                   Use HTTP/0.9 style requests.\n"
		" -1|--http10                   Use HTTP/1.0 protocol.\n"
		" -2|--http11                   Use HTTP/1.1 protocol.\n"
		" --get                         Use GET request method .\n"
		" --head                        Use HEAD request method .\n"
		" --options                     Use OPTIONS request method .\n"
		" --trace                       Use TRACE request method .\n"
		" -?|-h|--help                  This information.\n"
		" -V|--version                  Display program version.\n"
	);
}