#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>

/**
 * 参考：
 * http://kenby.iteye.com/blog/1173862
 * 
 * 不可靠信号：信号可能会丢失，一个信号发生了，但是进程可能一直不知道这一点。
 *
 * 信号处理时需要注意：
 * 		1. 调用的函数是否可以重入
 * 		2. errno值的保存
 *
 * 信号的生成来自内核，让内核生成信号的请求来自3个地方：
 * 		1. 用户：用户能够通过输入CTRL+c和Ctrl+\，或者其他特殊键来请求内核产生信号
 * 		2. 内核：当进程执行出错时，内核会给进程发送一个信号
 * 		3. 进程：一个进程可以通过系统调用kill给另一个进程发送信号，一个进程可以通过信号和另一个进程进行通信
 *
 * 同步信号(synchronous signals)：由进程的某个操作产生的信号
 * 异步信号(asynchronous signals)：由像用户触发某个键产生的信号
 *
 * 有两个信号：SIGKILL/SIGSTOP，既不能捕捉也不能忽略，只能接受系统的默认处理，即终止进程.
 *
 * 信号造成：硬件异常，软件中断，kill调用...为进程产生一个信号
 * 信号产生：当一个信号产生时，内核通常在进程表中以某种形式设置一个标志
 * 信号递送：内核调用信号的处理函数，把信号传递给该函数就是信号递送
 */


int main(int argc, char const *argv[])
{
	return 0;
}
