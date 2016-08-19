#include<setjmp.h>

#include"apue.h"

/**
 * 在栈上跳过若干调用帧，返回到当前函数调用路径上的某一个函数，使用setjmp/longjmp函数
 * 
 * int setjmp(jmp_buf env)
 * 若直接调用，返回0，若从longjmp返回，返回非0
 * 
 * void longjmp(jmp_buf env, int val)
 */
static void f1(int ,int ,int ,int );
static void f2(void);

static jmp_buf jmpbuffer;
static int globval;				// 全局变量

int main(int argc, char const *argv[])
{
	int autoval; 				// 自动变量
	register int regival; 		// 寄存器变量
	volatile int volaval; 		// 易失变量
	static int statval; 		// 静态变量

	globval = 1;
	autoval = 2;
	regival = 3;
	volaval = 4;
	statval = 5;

	if(setjmp(jmpbuffer) != 0)
	{
		printf("after longjmp:\n");
		printf("globval=%d, autoval=%d, regival=%d, volaval=%d, statval=%d\n", 
			globval, autoval, regival, volaval, statval);
		exit(0);		//如果这里不退出，会陷入递归
	}

	globval = 95;
	autoval = 96;
	regival = 97;
	volaval = 98;
	statval = 99;

	f1(autoval, regival, volaval, statval);

	exit(0);
}

static void f1(int i, int j, int k, int l)
{
	printf("in f1():\n");
	printf("globval=%d, autoval=%d, regival=%d, volaval=%d, statval=%d\n",
		globval, i, j, k, l);
	f2();
}

static void f2(void)
{
	longjmp(jmpbuffer,1);
}

/**
 * 编译运行代码有两种方式：
 * 1.不优化编译，再运行
 * output：
 * in f1():
 * globval=95, autoval=96, regival=97, volaval=98, statval=99
 * after longjmp:
 * globval=95, autoval=96, regival=97, volaval=98, statval=99

 * 2.编译时优化，再运行
 * output:
 * in f1():
 * globval=95, autoval=96, regival=97, volaval=98, statval=99
 * after longjmp:
 * globval=95, autoval=2, regival=3, volaval=98, statval=99
 *
 * 存在差异的原因：
 * 	系统手册上说明：存放在RAM中的变量将具有longjmp时的值，而在CPU和浮点寄存器中的变量则回恢复为setjmp时的值
 * 	在没有优化的情况下：所有的变量是存放在RAM中的，包括register声明的变量
 * 	优化之后：自动变量和寄存器变量放到了寄存器中，所以与未优化的情况的输出的值不一样
 */