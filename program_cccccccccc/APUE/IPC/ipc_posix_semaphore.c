#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<semaphore.h>

/**
 * 参考：
 * http://www.tuicool.com/articles/jqmee2
 * http://www.cnblogs.com/Anker/archive/2013/01/13/2858765.html
 * 
 * 信号量：是一种用于提供不同进程间或一个给定进程的不同线程间同步手段的原语。信号量的使用主要是用来保护共享资源，使得资源在一个时刻
 * 只有一个进程（线程）所拥有。信号量的值为正时，说明它空闲，所测试的线程可以锁定而使用它。若为0，说明它被占用，测试的线程要进入睡眠
 * 队列中，等待被唤醒。
 * 互斥量/条件变量：主要用于线程间的同步
 * 信号量：提供一种进程间同步的方式
 *
 * POSIX信号量：有名信号量和无名信号量（基于内存的信号量）
 * 有名信号量通过IPC名字进行进程间的同步，而无名信号量如果不是放在进程间的共享内存区中，是不能用来进行进程间同步的，
 * 只能用来进行线程同步。
 *
 * 信号量的3中操作：
 * 1.创建一个信号量：创建/打开一个信号量
 * 		二值信号量：信号量的值只有0和1
 * 		计数信号量：信号量的值在0到一个大于1的限制值（32767）
 * 2.等待一个信号量wait：该操作会检查信号量的值，如果其值小于或等于0，那就阻塞，直到该值变成大于0，然后进程将信号量
 * 的值减1，进程获得共享资源的访问权限，这整个操作必须是一个原子操作，该操作必须是一个原子（P）操作。
 * 3.挂出一个信号量post：该操作将信号量的值加1，如果有进程阻塞着等待该信号量，那么其中一个进程将被唤醒，该操作也必
 * 须是一个原子（V）操作。
 */


/****************************************************ipc_posix_semaphore_create.c*****************************************************/
// 创建信号量权限模式
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define FILE_NAME "ipc_semaphore"
#define SEM_FLAGS (O_RDWR | O_CREAT)

int main(int argc, char const *argv[])
{
	int c;
	sem_t *sem;
	unsigned int value = 1;       // 所创建的信号量的初始值

	sem = sem_open(FILE_NAME, SEM_FLAGS, FILE_MODE, value);
	if(sem == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(EXIT_FAILURE);
	}

	sem_close(sem);

	exit(EXIT_SUCCESS);
}


/****************************************************ipc_posix_semaphore_delete.c*****************************************************/
#define SEM_NAME "ipc_semaphore"

/**
 * 删除信号量
 * int sem_unlink(const char *name);
 * 返回值：若成功，返回0，若失败，返回-1
 */


int main(int argc, char const *argv[])
{
	if(sem_unlink(SEM_NAME) == -1)
	{
		perror("can't delete semaphore");
		exit(EXIT_FAILURE);
	}

	return 0;
}


/****************************************************ipc_posix_semaphore_getvalue.c*****************************************************/
#define SEM_NAME "ipc_semaphore"

int main(int argc, char const *argv[])
{
	int value;
	sem_t *sem;

	// 打开一个已经存在的信号量
	sem = sem_open(SEM_NAME, 0);

	if(sem_getvalue(sem, &value) == -1)
	{
		perror("获取当前信号量的值出错");
		exit(EXIT_FAILURE);
	}

	if(value>0)
		printf("当前的信号量的值为： %d\n", value);
	else if(value == 0)
		printf("当前的信号量是被上锁的\n");
	else
		printf("当前存在%d个线程等待信号量\n", -value);

	return 0;
}



/****************************************************ipc_posix_semaphore_wait.c*****************************************************/
#define SEM_NAME "ipc_semaphore"

int main(int argc, char const *argv[])
{
	int value;
	sem_t *sem;

	sem = sem_open(SEM_NAME, 0);

	if(sem == SEM_FAILED)
	{
		perror("打开一个信号量失败");
		exit(EXIT_FAILURE);
	}


	// wait将信号量的值减1
	sem_wait(sem);

	return 0;
}


/****************************************************ipc_posix_semaphore_post.c*****************************************************/
#define SEM_NAME "ipc_semaphore"


int main(int argc, char const *argv[])
{
	int value;
	sem_t *sem;

	// 打开以存在的信号量
	if((sem = sem_open(SEM_NAME, 0)) == SEM_FAILED)
	{
		perror("open semaphore error");
		exit(EXIT_FAILURE);
	}

	// 将信号量的值加1
	sem_post(sem);

	return 0;
}


/**
 * 编译包含信号量函数源码时要加上： -l pthread
 */