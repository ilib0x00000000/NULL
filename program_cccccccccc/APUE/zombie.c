#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>

/**
 * 僵尸进程：父进程在fork创建子进程之后，如果子进程在父进程exit之前运行结束，此时内核会释放子进程的资源（I/O，RAM等），
 * 但是内核也会保存子进程的进程描述符（进程号，终止状态，运行时间），
 * 如果父进程不调用wait*函数，子进程的进程描述符会一直保存着，这样的进程就是僵尸进程。
 *
 * 僵尸进程危害：父进程不掉用wait*函数，内核保存的进程描述符就不会释放，如果父进程fork的子进程很多，
 * 内核保存的进程描述符就很多，而系统能使用的进程号是有限的，这样就会导致不能有新的进程产生。
 *
 * 解决方案：父线程是产生僵尸进程的源，所以解决父进程就可以了。kill或者信号杀死掉父进程，子进程变成孤儿进程，由init进程处理。
 * 
 * 参考博客：http://www.cnblogs.com/Anker/p/3271773.html
 */
void test1(void);
void test2(void);


int main(int argc, char const *argv[])
{
	test1();
	test2();

	return 0;
}


void test1(void)
{
	/**
	 * 创建一个子进程，然后变成僵尸进程
	 * 父进程必须在子进程结束之后退出。
	 */
	pid_t pid;

	pid = fork();

	if(pid < 0)
	{
		perror("fork error");
		exit(1);
	}else
	if(pid == 0)
	{
		/*子进程*/
		printf("这是子进程\n");
		exit(0);					// 子进程与父进程共享代码段（正文段），如果子进程不调用exit，则子进程会继续执行非父进程中的代码
	}

	/*父进程：只等待子进程结束，不调用任何wait*函数*/
	printf("这是父进程，等待子进程退出\n");
	sleep(2);

	system("ps -o pid,ppid,state,tty,command");
	printf("退出父进程\n");
}

void test2(void)
{
	/**
	 * 创建多个僵尸进程
	 */
	pid_t pid;

	while(1)
	{
		pid = fork();

		if(pid < 0)
		{
			perror("fork error");
			exit(1);
		}else
		if(pid == 0)
		{
			printf("这是子进程，即将成为僵尸进程\n");
			exit(0);
		}else
		{
			// 父进程休眠10s继续创建子进程
			sleep(10);
			continue;
		}
	}
}

/**
 test1 output
	 这是父进程，等待子进程退出
	 这是子进程
	  PID  PPID S TT       COMMAND
	 3486  3478 S pts/1    /bin/bash
	 3736  3486 S pts/1    ./zombie
	 +-----------------------------------------+
	 | 3737  3736 Z pts/1    [zombie] <defunct>|
	 +-----------------------------------------+
	 3738  3736 S pts/1    sh -c ps -o pid,ppid,state,tty,command
	 3739  3738 R pts/1    ps -o pid,ppid,state,tty,command
	 退出父进程

 test2 output
	ilib0x00000000@touch:~/temp/APUE$ ./zombie &
	[1] 3912
	ilib0x00000000@touch:~/temp/APUE$ 这是子进程，即将成为僵尸进程
	>>> ps -o pid,ppid,state,tty,command
	  PID  PPID S TT       COMMAND
	 3486  3478 S pts/1    /bin/bash
	 3912  3486 S pts/1    ./zombie
	 +------------------------------------------+
	 | 3913  3912 Z pts/1    [zombie] <defunct> |
	 +------------------------------------------+
	 3914  3486 R pts/1    ps -o pid,ppid,state,tty,command
	ilib0x00000000@touch:~/temp/APUE$ 这是子进程，即将成为僵尸进程
	>>> ps -o pid,ppid,state,tty,command
	  PID  PPID S TT       COMMAND
	 3486  3478 S pts/1    /bin/bash
	 3912  3486 S pts/1    ./zombie
	 +------------------------------------------+
	 | 3913  3912 Z pts/1    [zombie] <defunct> |
	 | 3915  3912 Z pts/1    [zombie] <defunct> |
	 +------------------------------------------+
	 3916  3486 R pts/1    ps -o pid,ppid,state,tty,command

	ilib0x00000000@touch:~/temp/APUE$ kill -9 3912
 */