#include<stdio.h>
#include<errno.h>
#include<wchar.h>
#include<stdlib.h>
#include<unistd.h>

/**
 * 标准I/O文件流可用于单字节或多字节字符集，流的定向决定了所读、写的字符是单字节还是多字节的
 * 只有两个函数可以改变流的定向
 * 
 * 设置流的定向
 * #include<stdio.h>
 * #include<wchar.h>
 * int fwide(FILE *fp, int mode);
 * 						返回值：若流是宽定向的，返回正值；若流是字节定向的，返回负值；若流是未定向的，返回0
 * 如果mode参数为负，fwide将试图使指定的流是字节定向的
 * 如果mode参数为正，fwide将试图使指定的流是宽定向的
 * 如果mode参数值为0，fwide将不试图设置流的定向，但返回标识该流定向的值
 *
 * 缓冲：
 * 全缓冲：在这种情况下，在填满标准I/O缓冲区后才进行实际I/O操作
 * 行缓冲：在这种情况下，当在输入和输出中遇到换行符时，标准I/O库执行I/O操作
 * 不带缓冲：标准I/O库不对字符进行缓冲存储
 *
 * 更改缓冲类型(全缓冲/行缓冲/无缓冲)：
 * #include<stdio.h>
 * void setbuf(FILE *restrict fp, char *restrict buf);
 * int setvbuf(FILE *restrict fp, char *restrict buf, int mode, size_t size);
 * 						返回值：若成功，返回0，若出错，返回非0
 *
 * 冲洗一个流：
 * #include<stdio.h>
 * int fflush(FILE *fp);
 * 						返回值：若成功，返回0，若出错，返回EOF
 */

#define BUFFERSIZE 100

int main(int argc, char const *argv[])
{
	int mode;
	FILE *fp;	
	FILE *cp;
	char buffer[BUFFERSIZE];

	fp = fopen("io.c", "rb");		// 只读打开一个文件
	if(fp == NULL)
	{
		perror("open file error");
		exit(-1);
	}

	mode = fwide(fp, 1);			// 打开文件时就设置了流的定向
	if(mode > 0)
		printf("宽定向\n");
	if(mode < 0)
		printf("字节定向\n");

	cp = fopen("test.txt", "a+b");
	if(cp == NULL)
	{
		perror("create new file error");
		exit(-1);
	}
	// mode = fwide(cp, 1);

	while(fgets(buffer, BUFFERSIZE, fp) != NULL)
	{
		if(fputs(buffer, cp) == EOF)
			printf("write error\n");
	}
	// else
	// {
	// 	if(ferror(fp))
	// 		printf("read error\n");
	// 	else if(feof(fp))
	// 		printf("eof\n");
	// 	else
	// 		printf("unknown error\n");
	// }

}

/**
 * 打开流
 * FILE *fopen(const char * restrict pathname, const char *restrict type);
 * FILE *freopen(const char *restrict pathname, const char *restrict type, FILE *restrict fp);
 * FILE *fdopen(int fd, const char *type);
 * 						返回值：若成功，返回文件指针，若出错，返回NULL
 *
 * fopen函数：
 * 		打开路径名为pathname的一个指定的文件
 * freopen函数：
 * 		在一个指定的流上打开一个指定的文件，如若该流已经打开，则先关闭该流。若该流已经定向，则使用freopen清除该定向。
 * fdopen函数：
 * 		取一个已有的文件描述符，并使一个标准的I/O流与该描述符相结合
 *
 * 关闭流：
 * #include<stdio.h>
 * int fclose(FILE *fp);
 * 						返回值：若成功，返回0，若出错，返回EOF
 */


/**
 * 读写流：
 * 1.每次一个字符的I/O，一次读或写一个字符，如果流是带缓冲的，则标准I/O函数处理所有缓冲。
 * 2.每次一行的I/O。
 * 3.直接I/O，fread和fwrite函数支持这种类型的I/O。
 *
 * 一次读取一个字符：
 * #include<stdio.h>
 * int getc(FILE *fp);
 * int fgetc(FILE *fp);
 * int getchar(void);
 * 						返回值：若成功，返回下一个字符，若到达文件尾或出错，返回EOF
 *
 * 区分读取流是出错还是到达文件尾
 * #include<stdio.h>
 * int ferror(FILE *fp);
 * int feof(FILE *fp);
 * 						返回值：若条件为真，返回真，若条件为假，返回0
 * void clearerr(FILE *fp);
 *
 * 一次输出一个字符：
 * #include<stdio.h>
 * int putc(int c, FILE *fp);
 * int fputc(int c, FILE *fp);
 * int putchar(int);
 * 						返回值：若成功，返回c，若出错，返回EOF
 *
 * 一次读取一行：
 * #include<stdio.h>
 * char *fgets(char *restrict buf, int n, FILE *restrict fp);
 * char *gets(char *buf);
 * 						返回值：若成功，返回buf，若到达文件尾或出错，返回NULL
 *
 * 一次输出一行：
 * #include<stdio.h>
 * int fputs(const char *restrict str, FILE *restrict fp);
 * int puts(const char *str);
 * 						返回值：若成功，返回非负值，若出错，返回EOF
 */