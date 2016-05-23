#include<stdio.h>
#include<stdlib.h>

int factor(int num);
/*使用递归的方式求解一个数的阶乘*/

int factor(int num)
{
	// num < 30
	if(num < 2)
		return 1;

	return num*factor(num-1);
}

char * reverse(char *origin_str);
/*反转一个字符串*/

char * reverse(char *origin_str)
{
	register char temp;			// 中间变量
	register char *p;			// pwd
	register char *q;			// bwd

	p = origin_str;
	q = origin_str + (strlen(origin_str)-1);

	while(p < q)
	{
		temp = *p;
		*p++ = *q;
		*q-- = temp;
	}

	return origin_str;
}
