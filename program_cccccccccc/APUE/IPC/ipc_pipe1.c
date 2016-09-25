#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

/**
 * #include<stdio.h>
 * FILE *popen(const char *cmdstring, const char *type);
 * 							返回值：若成功，返回文件指针，若出错，返回NULL
 * int pclose(FILE *fp);
 * 							返回值：若成功，返回cmdstring的终止状态，若出错，返回-1
 *
 * type = "r":则文件指针连接到cmdstring的标准输出
 * type = "w":则文件指针连接到cmdstring的标准输入
 */

#define MAXLINE 4096
#define PAGER "${PAGER:-more}"

int main(int argc, char const *argv[])
{
	FILE *fpin;
	FILE *fpout;
	char line[MAXLINE];

	if((fpin = fopen(argv[1], "r")) == NULL)
	{
		perror("open file failed");
		exit(127);
	}

	if( (fpout = popen(PAGER, "w")) == NULL)
	{
		perror("popen error");
		exit(126);
	}

	while(fgets(line, MAXLINE, fpin) != NULL)
	{
		if(fputs(line, fpout) == EOF)
		{
			perror("fputs error to pipe");
			exit(125);
		}
	}

	if(ferror(fpin))
	{
		perror("fgets error");
		exit(124);
	}

	if(pclose(fpout) == -1)
		exit(123);

	return 0;
}
