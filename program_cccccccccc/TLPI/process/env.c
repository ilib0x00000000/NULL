#define _BSD_SOURCE

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 _   _          _   _         _______ _       _ _______  _______  _______  _______  _______  _______  _______  _______ 
(_) | |        (_) | |       / _____ \\\     /// _____ \/ _____ \/ _____ \/ _____ \/ _____ \/ _____ \/ _____ \/ _____ \
| | | |        | | | |       |/     \| \\   // |/     \||/     \||/     \||/     \||/     \||/     \||/     \||/     \|
| | | |        | | | |______ ||     ||  \\ //  ||     ||||     ||||     ||||     ||||     ||||     ||||     ||||     ||
| | | |        | | | |_____ \||     ||   ||    ||     ||||     ||||     ||||     ||||     ||||     ||||     ||||     ||
| | | |        | | | |     \|||     ||  //\\   ||     ||||     ||||     ||||     ||||     ||||     ||||     ||||     ||
| | | |_______ | | | |____ /||\_____/| //  \\  |\_____/||\_____/||\_____/||\_____/||\_____/||\_____/||\_____/||\_____/|
|_| |_________||_| |_|______/\_______///    \\ \_______/\_______/\_______/\_______/\_______/\_______/\_______/\_______/

 * @author  ilib0x00000000
 * @email   yinghaozhg@qq.com
 * @version 0.1
 *
 * C语言环境变量函数API
 */


/**
 * 从进程环境中检索出单个值
 * #include<stdlib.h>
 * char *getenv(const char *name);
 *
 * 
 * 向调用进程的环境添加一个新变量，或者修改一个已存在的变量值
 * #include<stdlib.h>
 * int putenv(char *string);
 * 若成功，返回0，若失败，返回非0值。
 * 
 * 向环境添加一个变量
 * #include<stdlib.h>
 * int setenv(const char *name, const char *value, int overwrite);
 * 若成功，返回0，若失败，返回-1
 * 
 * 移除指定环境变量
 * #include<stdlib.h>
 * int unsetenv(const char *name);
 * 若成功，返回0，若失败，返回-1
 * 
 * 清除环境
 * #define _BSD_SOURCE
 * #include<stdlib.h>
 * int clearenv(void);
 * 若成功，返回0，若失败，返回-1
 */

// 如果想得到进程的全部环境变量，可以引入全局变量environ
extern char **environ;

int main(int argc, char const *argv[])
{
	char *s;
	char **cp;
	char *env_user;

	/**
	 * 打印进程全部环境变量
	 */
	cp = environ;

	while(*cp)
	{
		printf("%s\n", *cp);
		cp ++;
	}

	printf("****************************************************************************\n");


	// 获取指定环境变量的值
	env_user = getenv("USER");
	printf("%s\n", env_user);
	printf("****************************************************************************\n");


	// 清楚所有环境变量
	clearenv();    

	// 添加环境变量
	if(putenv("PATH=/a/b/c") != 0)
	{
		printf("添加环境失败\n");
	}else
	{
		printf("%s\n", getenv("PATH"));
	}
	printf("****************************************************************************\n");


	// 添加环境
	assert(setenv("PATH", "/lib/bin", 1) == 0);
	assert((s=getenv("PATH")) != NULL);
	printf("%s\n", s);
	printf("****************************************************************************\n");


	// 删除指定环境变量
	assert(unsetenv("PATH") == 0);
	assert((s=getenv("PATH")) == NULL);

	return 0;
}
