#include<stdio.h>

/*
	命令行参数:
		argc: 参数的个数
		argv: 参数数组，参数以字符串的形式传递
		参数至少为1个，程序名，即argv[0]就是程序名

*/

int main(int argc, char const *argv[])
{
	int i;

	if(argc == 1)
	{
		printf("只有一个参数，程序名：%s\n", argv[0]);
	}
	else if(argc == 2)
	{
		printf("参数是%s\n", argv[1]);
	}
	else
	{
		for (i = 1; i < argc; ++i)
		{
			printf("参数%d:%s\n",i, argv[i]);
		}
	}


	return 0;
}