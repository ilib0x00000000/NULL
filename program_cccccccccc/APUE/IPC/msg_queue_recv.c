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
 * http://www.tuicool.com/articles/yyaAvqa
 * 
 * int msgget(key_t key, int flag);
 * flag = IPC_CREAT: 如果消息队列对象不存在，则创建之，否则进行打开操作
 * flag = IPC_EXCL: 和IPC_CREAT一起使用，如果消息队列对象不存在则创建之，否则产生一个错误并返回
 * 返回值：成功时返回队列ID，失败返回-1，错误原因存于errno中
 *
 * int msgsnd(int msgid, void *msgbuf, int msgsize, int flag);
 * 第一个参数：要发送消息队列的队列ID，
 * 第二个参数：指向要发送信息所在的内存，要强转成如下的结构体指针
 * 第三个参数：要发送的信息的字符串的长度
 * 第四个参数：控制函数的行为
 * struct msq_buf{
 * 		long type,
 * 		char text[512];
 * };
 * 返回值：若成功，返回0，若失败，返回-1，错误信息存放在errno
 *
 * ssize_t msgrcv(int msgid, void *msgbuf, int msgsize, long type, int flag);
 * 第一个参数：要读取消息队列的队列ID
 * 第二个参数：指向要读取信息所在内存，也需要强转
 * 第三个参数：读取的信息的长度
 * 第四个参数：指定了函数从队列中读取的消息的类型，如果是0，自动读取最旧的消息
 * 第五个参数：控制函数的行为
 * 返回值：读取的消息的长度，若失败，返回-1
 *
 * int msgctl(int msgqid, int cmd, struct msqid_ds *buf);
 * 
 */

/**
 * 定义消息的结构体：
 * msg_type: 消息类型
 * msg_text: 消息正文
 */
struct msg_buf{
	long msg_type;
	char msg_text[512];
};

int main(int argc, char const *argv[])
{
	int msgid;
	int running = 1;
	long msg_to_recv = 0;	// 表示接受消息队列中的第一个消息
	struct msg_buf message;

	/*创建消息队列*/
	msgid = msgget((key_t)1234, IPC_CREAT);

	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/*接受消息*/
	while(running)
	{
		if(msgrcv(msgid, (void *)&message, BUFSIZ, msg_to_recv, 0) == -1)
		{
			fprintf(stderr, "msgrcv failed with error: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		printf("receive message: %s\n", message.msg_text);
		if(strncmp(message.msg_text, "end", 0) == 0)
			running = 0;
	}

	/*删除消息队列*/
	if(msgctl(msgid, IPC_RMID, 0) == -1)
	{
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
