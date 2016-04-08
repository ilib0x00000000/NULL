#include<stdio.h>
#include<stdlib.h>


/*
	@author : ilib0x00000000
	@email  : ilib0x00000000@gmail.com
	@version: 1.0
	@date	: 2016/04/05
	@project: 打印螺旋数组
*/


/*
	假设有一个全局变量二维数组，长度和宽度相同，都是n(n可变)
	要求打印出如下数据:

		 1  2  3 4
 		12 13 14 5
 		11 16 15 6
 		10  9  8 7
*/

/*
	思路：将数组看成一个矩阵，每一个圆圈当成一个代码段，
		  这样可以递归迭代螺旋数组，递归结束的条件为start点的坐标大于end点

	(start,start) ----------------------------> (start,end-1)
		  |\										|
		  |	\										|
		  |	 \										|
		  |	  \										|
		  |	   \									|
		  |		\									|
		  |		 \									|
		  |		 _\|增加								|
		  |											|
		  |									 _		|
		  |									|\减小	|
		  |									  \		|
		  |									   \	|
		  |										\	|
		  |										 \	|
		  |										  \	|
		  V 									   \V
	(end-1,start) -----------------------------> (end-1,end-1)
*/

#define LENGTH 10

int arr[LENGTH][LENGTH] = {0};	// 全局变量数组


void spiral(int start, int end, int value);
int  evalue(int start, int end, int value);

int main(void)
{
	int i;
	int j;

	spiral(0,LENGTH,1);

	for(i = 0 ; i < LENGTH ; i++)
	{
		for(j = 0 ; j < LENGTH ; j++)
		{
			printf("%3d ", arr[i][j]);
		}
		printf("\n\n");
	}

	return EXIT_SUCCESS;
}

void spiral(int start, int end, int value)
{
	// 给数组元素赋值
	if(start > end)
	{
		return ;
	}else
	{
		value = evalue(start,end,value);

		//spiral(start++, end--, value);这样写会进入死循环，应该是++操作符的原因（未确认）
		
		start++;
		end--;
		spiral(start, end, value);	
	}
}


int  evalue(int start, int end, int value)
{
	int i;
	int j;

	for(i = j = start; j < end ; j++)
	{
		arr[i][j] = value++;
	}

	for(j--,i++; i < end ; i++)
	{
		arr[i][j] = value++;
	}

	for(i--,j-- ; j >= start ; j--)
	{
		arr[i][j] = value++;
	}

	for(j++,i-- ; i > start ; i--)
	{
		arr[i][j] = value++;
	}

	return value;
}

/*
最终结果如下：
  1   2   3   4   5   6   7   8   9  10 
 36  37  38  39  40  41  42  43  44  11 
 35  64  65  66  67  68  69  70  45  12 
 34  63  84  85  86  87  88  71  46  13 
 33  62  83  96  97  98  89  72  47  14 
 32  61  82  95 100  99  90  73  48  15 
 31  60  81  94  93  92  91  74  49  16 
 30  59  80  79  78  77  76  75  50  17 
 29  58  57  56  55  54  53  52  51  18 
 28  27  26  25  24  23  22  21  20  19 
*/