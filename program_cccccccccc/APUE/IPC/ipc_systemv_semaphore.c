#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>

/**
 * 参考：http://www.cnblogs.com/cpsmile/p/4435185.html
 *
 * system v 信号量
 * 信号量通常是在内核中实现的
 * 为了获得共享资源：
 * 1.测试控制该资源的信号量
 * 2.若此信号量的值为正，则进程可以使用该资源，在这种情况下，进程会将信号量值减1，表示它使用了一个资源单位
 * 3.否则，若此信号量的值为0，则进程进入休眠状态，直至信号量值大于0，进程被唤醒，重复以上 
 *
 * #include<sys/sem.h>
 * 创建或打开一个信号量集：
 * int semget(key_t key, int nsems, int flag);
 * 参数：
 * 			flag：与open函数的各种标志很相似，低端9个位是该信号量集的权限，也可以与键值IPC_CREAT按位或操作，
 * 			以创建一个新的信号量，即使给出已有的键，也并不是一个错误。也可以IPC_CREAT和IPC_EXCL标志联合使用
 * 			确保自己将创建出一个新的独一无二的信号量集，如果该信号量集存在，就会返回一个错误。
 * 返回值：
 * 			若成功：返回一个称为信号标识符的整数
 * 			若出错：返回-1
 * 
 * 多种信号量操作：
 * int semctl(int semid, int semnum, int cmd, / union semun arg /);
 * 
 * 自动执行信号量集合上的操作数组：
 * int semop(int semid, struct sembuf semoparray[], size_t nops);
 */

// 申请一个资源
void P(int semph);
void V(int semph);

int main(int argc, char const *argv[])
{
	int semph;
	key_t key;

	/*创建一个信号量集*/
	semph = semget(key, 1, 0666 | IPC_CREAT);

	if(semph == -1)
	{
		fprintf(stderr, "create semaphore error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/*获取第1个信号量的semval值*/
	printf("before setval: %d\n", semctl(semph, 0, GETVAL));
	printf("setting value...\n");

	/*设置第1个信号量的semval值*/
	semctl(semph, 0, SETVAL, 1);
	printf("after setval: %d\n", semctl(semph, 0, GETVAL));

	P(semph);
	while(getchar() != EOF)
		;
	V(semph);

	sleep(5);
	/*删除信号量集中的信号量*/
	semctl(semph, 0, IPC_RMID);

	return 0;
}

void P(int semph)
{
	struct sembuf sem_temp;         // 信号量操作数组的元素

	memset(&sem_temp, 0, sizeof(sem_temp));
	
	sem_temp.sem_num = 0;           // 操作的信号量
	sem_temp.sem_op = -1;           // 怎样操作
	sem_temp.sem_flg = SEM_UNDO;    // 设置信号量的UNDO位

	semop(semph, &sem_temp, 1);     // 自动执行信号量集合上的操作数组
}

void V(int semph)
{
	struct sembuf sem_temp;

	memset(&sem_temp, 0, sizeof(sem_temp));

	sem_temp.sem_num = 0;
	sem_temp.sem_op  = 1;
	sem_temp.sem_flg = SEM_UNDO;

	semop(semph, &sem_temp, 1);
}