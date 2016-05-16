#include<stdio.h>

/*
@Date    : 2016-05-16
@Author  : ilib0x00000000
@email   : ilib0x00000000@gmail.com
@github  : https://github.com/ilib0x00000000
@Version : 0.1
*/

#define ROW  100
#define COL  100

int main(int argc, char const *argv[])
{
	/*
		Warnning: 这里的矩阵以静态的数据给出，实际需要动态构造数组
	*/
	int mata[2][2] = {{2,3}, {1,-5}};					// 矩阵A
	int matb[2][3] = {{4,3,6}, {1,-2,3}};					// 矩阵B
	int resmat[ROW][COL] = {0};						// 矩阵A乘以矩阵B的结果集

	int bp = 3;
	int n = 2;
	int am = 2;

	int i;
	int j;
	int k;

	/* 两个矩阵相乘核心代码 */
	for (k = 0; k < am; k++)
	{
		for (j = 0; j < bp; j++)
		{
			for (i = 0; i < n; i++)
			{
				resmat[k][j] += mata[k][i] * matb[i][j];
			}
		}
	}

	for (i = 0; i < am; ++i)
	{
		for (j = 0; j < bp; j++)
		{
			printf("%d   ", resmat[i][j]);
		}
		printf("\n");
	}

	return 0;
}
