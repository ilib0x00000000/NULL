#include<stdio.h>

#define LENGTH 6

int bin_search(int *arr, int finder, int head, int tail);	// 声明函数

int main(int argc, char const *argv[])
{
	int i;
	int j;
	int arr[LENGTH] = {7, 21, 36, 80, 120, 900};// 测试数组，数组必须是已排序的
	int index ;									// 查找结果，如果找到，返回该元素的下标，否则返回-1
	int finder;									// 待查找的值
	int head = 0;								// 指向数组的头部 
	int tail = sizeof(arr) / sizeof(int) -1;	// 指向数组的尾部
	
	scanf("%d", &finder);
	index = bin_search(arr, finder, head, tail);


	if(index==-1)
	{
		printf("\ncan't find!\n");
	}else
	{
		printf("\nindex:%d\n", index);
		printf("values:%d\n", arr[index]);
	}

	return 0;
}


int bin_search(int *arr, int finder, int head, int tail)
{
	/*递归式二分查找*/
	int index;
	int temp = (head+tail)/2+1;

	printf("head:%d\n", head);
	printf("temp:%d\n", temp);
	printf("tail:%d\n", tail);


	if(head>=tail)
	{
		return -1;
	}

	if(arr[temp] == finder)
		return temp;
	else if(arr[temp] < finder)
		index = bin_search(arr, finder, temp+1, tail);		// 如果temp上元素与要查找的数不同，则直接对比下一个元素
	else
		index = bin_search(arr, finder, head, temp-1);	

	return index;
}
