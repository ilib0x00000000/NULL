#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<mqueue.h>

/**
 * 参考：
 * http://blog.csdn.net/zhangxiao93/article/details/52414647
 * http://blog.chinaunix.net/uid-24774106-id-3033607.html
 *
 * 消息队列是一个链表：
 * 表头：队列中允许的最大消息数和每个消息的最大大小
 * 消息：优先级/数据的长度/数据
 *
 * 创建或打开一个消息队列：
 * #include<mqueue.h>
 * mqd_t mq_open(const char *name, int oflag, ... / mode_t mode, struct mq_attr *attr /);
 * 												返回值：若成功，返回消息队列描述符，若失败，返回-1
 *
 * 关闭消息队列：
 * int  mq_close(mqd_t mqdes);
 * 												返回值：若成功，返回0，若失败，返回-1
 *
 * 删除消息队列：
 * int  mq_unlink(const char *name);
 * 												返回值：若成功，返回0，若失败，返回-1
 *
 * 消息队列的四个属性：
 * struct mq_attr{
 * 		long  mq_flags;
 * 		long  mq_maxmsg;
 * 		long  mq_msgsize;
 * 		long  mq_curmsgs;
 * };
 *
 * int  mq_getattr(mqd_t mqdes, struct mq_attr *attr);
 * int  mq_setattr(mqd_t mqdes, const struct mq_attr *attr, struct mq_attr *oattr);
 * 												返回值：若成功，返回0，若失败，返回-1
 */

#define MQNAME    "/newmqueue"
#define FILE_MODE 0777

int main(int argc, char const *argv[])
{
	int rtn;
	mqd_t mq;
	struct mq_attr mqattr;

	/* 创建一个消息队列 */
	mq = mq_open(MQNAME, O_RDWR|O_CREAT, FILE_MODE, NULL);

	if(mq == -1)
	{
		fprintf(stderr, "can't create mqueue %s\nerrno: %d\n", MQNAME, errno);
		exit(EXIT_FAILURE);
	}

	if((rtn = mq_getattr(mq, &mqattr)) != 0)
	{
		fprintf(stderr, "get mqueue attrs error\n");
		close(mq);
		mq_unlink(MQNAME);
		exit(EXIT_FAILURE);
	}

	printf("mq_flags: %ld\n", mqattr.mq_flags);
	printf("mq_maxmsg: %ld\n", mqattr.mq_maxmsg);
	printf("mq_msgsize: %ld\n", mqattr.mq_msgsize);
	printf("mq_curmsgs: %ld\n", mqattr.mq_curmsgs);

	/* 关闭消息队列 */
	close(mq);

	/* 删除消息队列 */
	mq_unlink(MQNAME);

	return 0;
}


/**
 * 注意：编译POSIX消息队列函数时，需要加上 -lrt
 */