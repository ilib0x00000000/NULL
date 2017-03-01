#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define MAX_ALLOCS 1000000


int main1(int argc, char const *argv[])
{
	int i;
	int block_size = 999;
	int num_allocs = 10240;
	int free_step = 2;
	int free_min = 1;
	int free_max = 999;
	char *ptr[MAX_ALLOCS];

	printf("程序初始时，program break地址： %10p\n", sbrk(0));

	printf("申请 %d * %d 个字节\n", num_allocs, block_size); // num_allocs个block_size字节块

	for(i = 0; i < num_allocs; i++)
	{
		ptr[i] = malloc(block_size);
		if(ptr[i] == NULL)
		{
			perror("申请内存失败");
			exit(EXIT_FAILURE);
		}
	}

	printf("现在program break地址为： %10p\n", sbrk(0));
	/**
	 * free行为：
	 * 一般情况下，free()并不降低program break的位置，而是将这块内存加入空闲内存列表中，供后续的malloc()函数循环使用。原因如下：
	 * > 被释放的内存通常会位于堆的中间，而非堆的顶部，因而降低program break是不可能的
	 * > 它最大程度的减少了程序必须执行的sbrk()调用次数。
	 * > 在大多数情况下，降低program break的位置不会对那些大量内存程序有多少帮助，因为它们通常倾向于持有已分配内存或是反复释放和重新分配内存，而非释放所有内存后再持续运行
	 * 一段时间
	 *
	 * 特殊情况：当释放的内存位于堆的顶部，且累积到一定大小（128KB）之后，free()会释放堆定的空间，降低program break
	 */
	for(i = free_min; i < free_max; i += free_step)
	{
		free(ptr[i]);
	}


	printf("释放一些内存之后的program break地址： %10p\n", sbrk(0));

	return 0;
}

/**
 * 输出：
 * 程序初始时，program break地址：  0x22fb000
 * 申请 10240 * 999 个字节
 * 现在program break地址为：  0x2ce8000
 * 释放一些内存之后的program break地址：  0x2ce8000
 */


int main(int argc, char const *argv[])
{
	int i;
	int block_size = 10240;
	int num_allocs = 999;
	int free_step = 1;
	int free_min = 499;
	int free_max = 999;
	char *ptr[MAX_ALLOCS];

	printf("程序初始时，program break地址： %10p\n", sbrk(0));

	printf("申请 %d * %d 个字节\n", num_allocs, block_size); // num_allocs个block_size字节块

	for(i = 0; i < num_allocs; i++)
	{
		ptr[i] = malloc(block_size);
		if(ptr[i] == NULL)
		{
			perror("申请内存失败");
			exit(EXIT_FAILURE);
		}
	}

	printf("现在program break地址为： %10p\n", sbrk(0));
	/**
	 * 释放堆顶的一半字节
	 */
	for(i = free_min; i < free_max; i += free_step)
	{
		free(ptr[i]);
	}


	printf("释放一些内存之后的program break地址： %10p\n", sbrk(0));

	return 0;
}