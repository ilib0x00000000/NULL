#include"apue.h"

/**
 * 子进程是父进程的副本，子进程获得父进程的数据空间、堆和栈的完全副本，父进程和子进程共享正文段
 * 由于在fork之后经常跟随着exec，所以现在的很所实现并不执行一个父进程数据段、栈和堆的完全副本。作为替代，使用了写时复制
 * 技术，这些区域由父进程和子进程共享，而且内核将他们的权限设置为只读的。如果父进程和子进程中任一个试图修改这块区域，则
 * 内核只为修改区域的那块内存制作一个副本，通常是虚拟存储系统中的一“页”。
 */


int globval = 6;
char buf[] = "a write to stdout\n";


int main(int argc, char const *argv[])
{
	int var;
	pid_t pid;

	var = 88;	// 父进程中var=88

	if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
	{
		err_sys("write error");
	}

	printf("before fork\n");

	pid = fork();

	if(pid<0)
	{
		err_sys("fork error");
	}else
	if(pid==0)
	{
		/*在子进程中*/
		globval ++;
		var ++;
		printf("在子进程中：pid= %ld, glod=%d, var=%d\n", (long)getpid(), globval, var);
	}else
	{
		/*在父进程中*/
		sleep(2);
		printf("在父进程中：pid= %ld, glod=%d, var=%d\n", (long)getpid(), globval, var);
	}
	

	return 0;
}
