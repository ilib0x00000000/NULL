#include<stdio.h>
#include<stdlib.h>

/**
 * 创建临时文件
 * #include<stdio.h>
 * char *tmpnam(char *ptr);
 * 						返回值：指向唯一路径名的指针
 * FILE *tmpfile(void);
 * 						返回值：若成功，返回文件指针，若出错，返回NULL
 */

#ifndef TMP_MAX
#define TMP_MAX 238328
#endif

#ifndef L_tmpnam
#define L_tmpnam 20
#endif

#define LINELENGTH 1024

int main(int argc, char const *argv[])
{
	FILE *fp;
	char name[L_tmpnam];
	char line[LINELENGTH];

	printf("%s\n", tmpnam(NULL));		// 临时文件名通过返回值返回

	tmpnam(name);						// 临时文件名通过参数返回
	printf("%s\n", name);

	fp = tmpfile();						// tmpfile函数创建的临时文件会在程序结束或关闭该文件时自动删除
	if(fp == NULL)
	{
		perror("create tmpfile error");
		exit(-1);
	}

	fputs("one line of output\n", fp);
	rewind(fp);

	if(fgets(line, sizeof(line), fp) == NULL)
	{
		perror("fgets error");
		exit(-1);
	}

	fputs(line, stdout);


	return 0;
}

/**
 * char *tmpnam(char *ptr);
 * 1.ptr == NULL, 创建的临时文件名，会通过返回值返回
 * 2.ptr为char *类型，且长度足够大，临时文件的文件名会通过ptr返回
 *
 * GCC v4.8.4推荐使用mkstemp代替tmpnam函数
 */
