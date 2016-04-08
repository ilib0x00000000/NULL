#include<stdio.h>
#include<string.h>

/*
	BF算法的思想是：目标串S，模式串T，从S的第一个元素开始，如果S和T的第一个元素相同，
	则比较S和T的第二个元素，否则比较S第二个与T的第一个元素

	BF算法是一种蛮力算法
*/

#define bf_search(des_str,patt_str)  _bf_search(des_str,patt_str,0)	// 利用宏模拟一个默认参数函数


int _bf_search(char *des_str, char *patt_str,int position);

int _bf_search(char *des_str, char *patt_str,int position)
{
	int i;
	int j;
	int index = -1;
	int des_len = strlen(des_str);
	int patt_len = strlen(patt_str);

	for(i = position ; des_str[i] ; i++)
	{
		for(j = 0 ; patt_str[j] ; j++)
		{
			if(des_str[i+j] != patt_str[j])
			{
				break;
			}
		}

		if(j==patt_len)
		{
			index = i;
			break;
		}
	}

	return index;
}


int main(void)
{
	char *origin = "abcdefghijk";
	char *test0 = "lkjjhgg";
	char *test1 = "fgh";

	int index;

	printf(".............\n");
	index = bf_search(origin, test0);
	printf("no macth: %d\n", index);

	index = _bf_search(origin, test1,4);
	printf("macthing : %d\n", index);

	// printf("bf-test");
	return 0;
}