#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>

/**
 * 参考：
 * http://www.cnblogs.com/java20130726/archive/2013/05/06/3218496.html
 * http://www.tuicool.com/articles/yyaAvqa
 * 
 * IPC:管道，FIFO（命名管道），消息队列，信号量，共享存储段
 * 每个内核中的IPC结构都用一个非负整数的标识符加以引用
 * 标识符是IPC对象的内部名，为使多个合作进程能够在同一个IPC对象上汇聚，需要提供一个外部命名方案。
 * 为此，每个IPC都与一个键（key）相关，将这个键作为该对象的外部名。
 *
 * 无论何时创建IPC结构（通过调用msgget、semget或shmget创建），都应指定一个键。
 * 这个键的数据类型为key_t，在<sys/types.h>中被定义。
 *
 * struct msqid_ds{
 * 		struct ipc_perm msg_perm;
 * 		msgqnum_t       msg_qnum;
 * 		msglen_t        msg_qbytes;
 * 		pid_t           msg_lspid;
 * 		pid_t           msg_lrpid;
 * 		time_t          msg_stime;
 * 		time_t          msg_rtime;
 * 		time_t          msg_ctime;
 * };
 *
 * struct ipc_perm{
 * 		uid_t uid;
 * 		gid_t gid;
 * 		uid_t cuid;
 * 		gid_t cgid;
 * 		mode_t mode;
 * };
 *
 * 使用接口说明：
 * 1.调用ftok接口产生一个key，
 * 2.调用msgget（使用key作为参数）产生一个队列
 * 3.进程可以调用msgsnd发送消息到这个队列，相应的别的进程可以用msgrcv读取这个队列中的消息
 * 			a): 阻塞方式下可能被信号打断，此时直接返回，尤其是大流量应用中更容易出现
 * 			b): 消息队列满，产生这个错误，则需要考虑提高系统消息队列规格，或者查看消息接收处是否有问题
 * 4.msgctl可以用来删除队列
 *
 * 消息队列产生之后，除非明确的删除，产生的队列会一直保留在系统中，Linux下的消息队列的个数是有限的。
 */

#define MAX_TEXT 512

struct msg_st
{
	long msg_type;
	char msg_text[MAX_TEXT];
};

int main(int argc, char const *argv[])
{
	int msgid;
	int running = 1;
	char buffer[BUFSIZ];		// BUFSIZ在stdlib中定义，为8192，即4k
	key_t key;
	struct msg_st share_data;

	key = ftok("/tmp/qimpanel-cell", 66666);
	
	/*创建队列*/
	msgid = msgget(key, IPC_CREAT);
	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		printf("Enter some text: ");
		fgets(buffer, BUFSIZ, stdin);

		share_data.msg_type = 1;
		strcpy(share_data.msg_text, buffer);

		if(msgsnd(msgid, (void *)&share_data, MAX_TEXT, 0) == -1)
		{
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}

		if(strncmp(buffer, "end", 3) == 0)
		{
			running = 0;
		}
	}

	exit(EXIT_SUCCESS);
}

/**
 * #include<sys/msg.h>
 * 1.产生一个key
 * key_t ftok(const char *path, int id);
 * 2.创建或打开一个队列
 * int msgget(key_t key, int flag);
 * 3.msgctl函数对队列执行多种操作
 * int msgctl(int msqid, int cmd, struct msqid_ds *buf);
 * 4.将数据放到消息队列中
 * int msgsnd(int msqid, const void *ptr, size_t nbytes, int flag);
 * 5.msgrcv从队列中读取消息
 * ssize_t msgrcv(int msqid, void *ptr, size_t nbytes, long type, int flag);
 */