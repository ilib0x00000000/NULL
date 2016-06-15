#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>

#define ARRAY_SIZE 4000
#define MALLOC_SIZE 10000
#define SHM_SIZE 10000
#define SHM_MODE (SHM_R | SHM_W)

/*
 _   _          _   _         _______ _       _ _______  _______  _______  _______  _______  _______  _______  _______ 
(_) | |        (_) | |       / _____ \\\     /// _____ \/ _____ \/ _____ \/ _____ \/ _____ \/ _____ \/ _____ \/ _____ \
| | | |        | | | |       |/     \| \\   // |/     \||/     \||/     \||/     \||/     \||/     \||/     \||/     \|
| | | |        | | | |______ ||     ||  \\ //  ||     ||||     ||||     ||||     ||||     ||||     ||||     ||||     ||
| | | |        | | | |_____ \||     ||   ||    ||     ||||     ||||     ||||     ||||     ||||     ||||     ||||     ||
| | | |        | | | |     \|||     ||  //\\   ||     ||||     ||||     ||||     ||||     ||||     ||||     ||||     ||
| | | |_______ | | | |____ /||\_____/| //  \\  |\_____/||\_____/||\_____/||\_____/||\_____/||\_____/||\_____/||\_____/|
|_| |_________||_| |_|______/\_______///    \\ \_______/\_______/\_______/\_______/\_______/\_______/\_______/\_______/
*************************************************************************************
 @Email   ilib0x00000000@gmail.com
 @date    2016-06-15 21:58:36
 @version 0.1
*************************************************************************************
*/

/**
 * ******************************************************************************************************* *
 *                                              注意执行时需要root权限                                      *
 * ******************************************************************************************************* *
 */

int main(int argc, char const *argv[])
{
	int shmid;
	char array[ARRAY_SIZE];
	char *ptr;
	char *shmptr;
	struct shmid_ds shmds;

	/**
	 * 创建共享内存
	 * int shmget(key_t key, int size, int flag)
	 * key=IPC_PRIVATE:创建一个指定大小的共享内存区域，flag无效
	 * key!=IPC_PRIVATE:
	 * 			flag=IPC_CREAT:执行操作由key决定
	 * 			flag=IPC_CREAT | IPC_EXCL:只执行创建共享内存
	 */
	shmid = shmget(IPC_PRIVATE, SHM_SIZE, 0);

	if(shmid == -1){
		printf("shmget error\n");
		exit(1);
	}


	/**
	 * 创建共享内存之后，如果一个进程需要使用这个共享内存，需要将此共享内存附加到该进程的地址空间
	 * void *shmat(int shmid, void *addr, int flag)
	 * addr=0:系统自动查找进程地址空间，此时flag无效
	 * addr!=0:一般不会出现
	 */
	shmptr = shmat(shmid, 0, 0);
	if(shmptr==(void *)-1){
		printf("shmat error\n");
		exit(1);
	}

	/**
	 * 共享内存的控制
	 * int shmctl(int shmid, int cmd, struct shmid_ds *buf)
	 * cmd:
	 * 		SHM_LOCK:对共享区域加锁（限root用户）
	 * 		IPC_RMID:删除共享内存，并非真正删除
	 * 		IPC_SET: 按buf指向的shmid_ds结构，设置共享内存区域对应的shmid_ds结构
	 * 		IPC_STAT:用于获得共享内存的shmid_ds结构，保存到buf
	 * 		SHM_UNLOCK:将上锁的共享内存区域释放(限root用户)
	 */
	if(shmctl(shmid, IPC_STAT, &shmds)<0){
		printf("shmctl error\n");
		exit(1);
	}

	printf("uid:%d\n", shmds.shm_perm.uid);
	printf("gid:%d\n", shmds.shm_perm.gid);
	printf("cuid:%d\n", shmds.shm_perm.cuid);
	printf("cgid:%d\n", shmds.shm_perm.cgid);

	printf("size: %d\n", shmds.shm_segsz);

	printf("atime: %ld\n", shmds.shm_atime);
	printf("dtime: %ld\n", shmds.shm_dtime);
	printf("ctime: %ld\n", shmds.shm_ctime);


	return 0;
}