#include <stdio.h>

/**
 * 链接：https://www.nowcoder.com/practice/9370d298b8894f48b523931d40a9a4aa?tpId=49&tqId=29233&rp=1&ru=/ta/2016test&qru=/ta/2016test/question-ranking来源：牛客网风口之下，猪都能飞。当今中国股市牛市，真可谓“错过等七年”。
   给你一个回顾历史的机会，已知一支股票连续n天的价格走势，以长度为n的整数数组表示，数组中第i个元素（prices[i]）代表该股票第i天的股价。
   假设你一开始没有股票，但有至多两次买入1股而后卖出1股的机会，并且买入前一定要先保证手上没有股票。若两次交易机会都放弃，收益为0。
   设计算法，计算你能获得的最大收益。 输入数值范围：2<=n<=100,0<=prices[i]<=100
 * 
 * 计算你能获得的最大收益
 * 
 * @param prices Prices[i]即第i天的股价
 * @return 整型
 */

int positivemax(int *arr, int low, int up)
{
	/**
	 * 计算一个数组中的最大差值（正值）
	 */
	int i;
	int j;
	int x;
	int max = 0;

	for(i=low; i<=up; i++)
	{
		for(j=i+1; j<=up; j++)
		{
			x = arr[j]-arr[i];

			if(x>max)
				max = x;
		}
	}

	return max;
}


int calu(int *prices)
{
	/**
	 * 把一个数组拆分成两个数组，分别计算每个数组的最大差值
	 */
	int i;
	int max = 0;
	int temp;
	int length;

	length = sizeof(prices)/sizeof(int);
	max = positivemax(prices, 0, length-1);

	for(i=0; i<length-1; i++)
	{
		temp = positivemax(prices, 0, i) + positivemax(prices, i+1, length-1);
		if(temp>max)
			max = temp;
	}

	return max;
}


int main(int argc, char const *argv[])
{
	return 0;
}