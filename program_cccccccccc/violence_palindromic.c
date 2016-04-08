#include<stdio.h>
#include<string.h>
#include<stdlib.h>


/*
	给定一个字符串，查找字符串中的最大回文子序列
	例： ansjklbnbljb得到最长的回文子序列：lbnbl

	共有4种解法：
		1.暴力解
		2.动态规划
		3.中心扩展法
		4.manacher算法


	解法：暴力解
	思路：得到字符串的所有子序列，判断子序列是否是回文字符串
	复杂度：事件复杂度：得到所有的子序列复杂度为O(n^2),判断序列是否是回文字符串复杂度为O(n),总复杂度为O(n^3)
		    空间复杂度：2n
*/

/*
/*
	@author : ilib0x00000000
	@email  : ilib0x00000000@gmail.com
	@version: 1.0
	@date	: 2016/04/08
	@project: 查找一个字符串中的最长回文子序列
*/

char *violence_get_cls(char *origin_str, char *res);
int is_symmetry(char *sub);


int main(int argc, char const *argv[])
{
	char *origin_str = "abcdexyedcba";					// 测试数据
	char result[100] = {0};

	violence_get_cls(origin_str,result);
	
	if(strlen(result)>1)
	{
		printf("%s\n", result);
	}else
	{
		printf("................\n");
	}	

	return EXIT_SUCCESS;
}

char *violence_get_cls(char *origin_str, char *res)
{
	int i;
	int j;
	int index;
	int length = 1;									// 假设字符串中含有回文子序列，则子序列的长度要大于1
	char sub[100]; 									// 准备一个足够大的字符串数组存储子串

	for(i = 0 ; origin_str[i] ; i++)
	{
		for(j = i+1 ; origin_str[j] ; j++)
		{

			strncpy(sub, origin_str+i, j-i+1);
			sub[j-i+1] = 0;							// 这里一定要把第j-i+1个元素设置成NUL(0结束标记)，因为前面给子串赋值时，
													// 子串的长度可能超过后面的子串的长度

			if(is_symmetry(sub) && strlen(sub)>length)
			{
				length = strlen(sub);
				strcpy(res,sub);
			}
		}
	}

	return res;
}


int is_symmetry(char *sub)
{
	int head = 0;
	int tail = strlen(sub)-1;

	while(head<tail)
	{
		if(sub[head] != sub[tail])
			return 0;
		else
		{
			head++;
			tail--;
		}
	}

	return 1;
}