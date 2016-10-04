#include"unp.h"

/**
 * 内存字节序：
 * 小端：高高低低，字节的低位存放在RAM的低位
 * 大端：高低低高，字节的低位存放在RAM的高位
 *
 * CPU:    Intel® Core™ i3-2350M CPU @ 2.30GHz × 4 
 * Kernel: Linux 4.4.0-37-generic #56~14.04.1-Ubuntu SMP GNU/Linux
 * OS:     Ubuntu 14.04 x86_64
 *
 * RAM： 小端存储
 */

int main(int argc, char const *argv[])
{
	union{
		short s;
		char  c[sizeof(short)];
	}un;

	un.s = 0x0102;

	if(sizeof(short) == 2)
	{
		if(un.c[0] == 1 && un.c[1] == 2)
			printf("大端\n");
		else if(un.c[0] == 2 && un.c[1] == 1)
			printf("小端\n");
		else
			printf("未知\n");
	}else
	{
		printf("sizeof(short) = %d\n", sizeof(short));
	}

	return 0;
}
