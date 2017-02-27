#define _GNU_SOURCE
#define __USE_GNU

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
 @date    2017-02-27 18:41:13
 @version 0.1
*************************************************************************************
*/

#include <sched.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>

/**
 * 要求控制CPU的使用率
 * 注意点：CPU的核数， 测试CPU使用率的间隔时间
 * 所有时间精确到毫秒级别
 *
 * 参考：http://blog.chinaunix.net/uid-27062906-id-3388512.html
 *
 * 注意：这里的时间计算有误！！！！！
 */

#define RATE      0.5   // 要求CPU的使用率
#define INTERVAL  1000  // 计算CPU使用率的间隔时间，毫秒 


unsigned long get_tick_count(void);
unsigned long get_tick_count(void)
{
	struct timeval  tv;
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	
	return (ts.tv_sec*1000 + ts.tv_nsec/(1000*1000));
}



int main(int argc, char const *argv[])
{
	int i = 0;
	cpu_set_t mask;

	unsigned long busytime = 10;
	unsigned long idletime = busytime;
	unsigned long starttime = 0;

	/**
	 * double busytime = INTERVAL * RATE;
	 * double idletime = INTERVAL*(1-RATE);
	 */

	CPU_ZERO(&mask);
	CPU_SET(1, &mask);

	sched_setaffinity(getpid(), sizeof(mask), &mask); // 把本进程绑定到CPUset上

	while(1)
	{
		starttime = get_tick_count();

		// 在指定的busytime，使CPU一直运行
		while(get_tick_count()-starttime <= busytime)
			;

		// 使CPU睡眠idletime
		usleep(idletime);
	}

	return 0;
}