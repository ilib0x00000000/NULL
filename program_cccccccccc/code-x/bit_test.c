#include <stdio.h>


/**
 * 世界上有10种人，一种懂二进制，一种不懂。那么你知道两个int32整数m和n的二进制表达，有多少个位(bit)不同么？ 
 *
 *
 * 
 * 获得两个整形二进制表达位数不同的数量
 * 
 * @param m 整数m
 * @param n 整数n
 * @return 整型
 * 
 * @link https://www.nowcoder.com/practice/ba033b0d1c2f497da1dd04330cc003af?tpId=49&tqId=29232&rp=1&ru=/ta/2016test&qru=/ta/2016test/question-ranking
 */

int countBitDiff(int m, int n) 
{
	int temp;
    int total = 0;
    int i = 32;      // 对应temp的位数，要以i为循环条件，逐步将temp对应的位
    int x;
    
    temp = m^n;    // temp是m和异或出来的值

    
    while(i)
    {
        total += (temp&1); // &1得到最后一位上的值

        
        temp = temp >> 1;
        
        i--;
    }
    
    return total;
}

int main(int argc, char const *argv[])
{
	printf("%d\n", countBitDiff(1999, 2299));
	
	return 0;
}