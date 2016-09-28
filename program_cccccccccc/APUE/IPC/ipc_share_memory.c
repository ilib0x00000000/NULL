#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<sys/types.h>

/**
 * 参考：
 * http://www.embedu.org/Column/5220.html
 * http://m.blog.csdn.net/article/details?id=52058952
 * 
 * 共享存储：共享存储允许两个或多个进程共享一个给定的存储区，因为数据不需要在客户进程和服务进程之间复制，所以这是最快的IPC。
 * 注意：多个进程要同步访问一个给定的存储区。
 *
 * 理解：共享内存就是允许两个不相关的进程访问同一物理内存，进程可以将同一段共享内存连接到他们自己的地址空间中，
 * 所有进程都可以访问共享内存的地址，每个进程所做的改动将立即影响到可以访问同一段共享内存的任何其他进程。
 * 共享内存是在两个正在运行的进程之间共享和传递数据的一种非常有效的方式，但是共享内存并为提供同步机制。也就是说，
 * 在每一个进程对共享内存读写时需要手动实施同步机制来控制对共享内存的访问。
 *
 * #include<sys/shm.c>
 * 创建或引用一个共享存储段：
 * int shmget(key_t key, size_t size, int flag);
 *
 * 对共享存储段执行多种操作：
 * int shmctl(int shmid, int cmd, struct shmid_ds *buf);
 *
 * 进程可以调用shmat函数将共享存储段连接到自己的地址空间：
 * void *shmat(int shmid, const void *addr, int flag);
 *
 * 当对共享存储段操作结束时，可以调用shmat与该段分离：
 * int shmdt(const void *addr);
 */

#define _PATH_ "apue.h"
#define _PROJECT_ 6644
#define _SHM_SIZE_ 3*1024   // 共享内存在内核中是以页为基本单位的，大小为4K

int get_shm(void);
char *at_shm(int shm_id);
int delete_shm(int shm_id);
int rm_shm(char *addr);

int main(int argc, char const *argv[])
{
	int i;
	int shm_id;
	pid_t pid;
	char *map_buf1;
	char *map_buf2;

	shm_id = get_shm();                      // 创建一个共享内存段，并返回一个id标识符
	pid = fork();

	if(pid < 0)
	{
		perror("Create New Process Error");
		exit(EXIT_FAILURE);
	}else
	if(pid == 0)
	{
		/*在子进程中*/
		map_buf1 = at_shm(shm_id);          // 将共享内存段连接到子进程中，并使map_buf1指向共享内存段
		i = 0;
		while(i < _SHM_SIZE_)
		{
			map_buf1[i] = '8';
			i++;
		}

		map_buf1[_SHM_SIZE_-1] = '\0';
		rm_shm(map_buf1);                  // 分离子进程与共享内存
	}else
	{
		/*在父进程中*/
		map_buf2 = at_shm(shm_id);         // 将共享内存连接到父进程中，并使map_buf2指向共享内存段
		sleep(5);
		printf("In Parent, read Share Memory: %s\n", map_buf2);
		rm_shm(map_buf2);                  // 分离父进程与共享内存

		waitpid(pid, NULL, 0);             // 等待子进程结束
		delete_shm(shm_id);                // 删除共享内存
	}

	return 0;
}

int rm_shm(char *addr)
{
	return shmdt(addr);                      // 分离进程与该共享内存段
}

int delete_shm(int shm_id)
{
	return shmctl(shm_id, IPC_RMID, NULL);   // 删除共享内存段
}

char *at_shm(int shm_id)
{
	return (char *)shmat(shm_id, NULL, 0);   // 启动进程并连接地址空间
}

int get_shm(void)
{
	int flag = 0666 | IPC_CREAT;
	int shm_id;
	key_t key;

	key = ftok(_PATH_, _PROJECT_);
	shm_id = shmget(key, _SHM_SIZE_, flag);

	if(shm_id == -1)
	{
		printf("Create Share Memory Error\n");
	}else
	{
		printf("Create Share Memory Successed\n");
	}

	return shm_id;
}
