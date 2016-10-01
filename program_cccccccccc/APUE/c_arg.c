#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>

/**
 * 参考：
 * http://blog.csdn.net/cashey1991/article/details/7942809
 * 
 * C的命令行参数
 * extern char *optarg: 如果参数形式是-chr value/-chr string，则表示value/string，否则是null
 * 
 * extern int optind: 表示下一个将被处理到的可选参数(-chr)在argv中的下标值
 * extern int opterr: 如果opterr=0，则getopt*函数遇到的错误将不会输出到标准输出流
 * extern int optopt: 
 * 
 * int getopt(int argc, char *const argv[], const char *optstring);
 * int getopt_long(int argc, char *const argv[], const char *optstring, const struct option *longopts, int *longindex);
 * int getopt_long_only(int argc, char *const argv[], const char *optstring, const struct option *longopts, int *longindex);
 */
static struct option long_option[] = {
	{"reqarg",   required_argument,  NULL, 'r'},
	{"noarg",    no_argument,        NULL, 'n'},
	{"optarg",   optional_argument,  NULL, 'o'},
	{0,          0,                  0,    0}
};

void test_getopt(int argc, char *argv[], const char *optstring);
void test_getopt_long(int argc, char *argv[], const char *optstring, const struct option *longopts);

int main(int argc, char const *argv[])
{
	char *optstring = "e:v";


	// test_getopt(argc, argv, optstring);
	test_getopt_long(argc, argv, optstring, long_option);

	return 0;
}

void test_getopt_long(int argc, char *argv[], const char *optstring, const struct option *longopts)
{
	/**
	 * 长参数 --arg value
	 * option结构体定义：
	 * struct option{
	 * 		const char *name;        // 参数的名字
	 * 		int   has_arg;           // 指明是否带参数值 no_argument | required_argument | optional_argument
	 * 		int   *flag              // 为空时：函数将value的数值从getopt_long的返回值返回出去，非空时，value的值会被赋到flag指向的值中
	 * 		int   value;             // 用于指定函数找到该选项时的返回值，或者flag非空时指定flag指向的值
	 * };
	 */
	int opt;
	int option_index;

	while((opt = getopt_long(argc, argv, optstring, longopts, &option_index)) != -1)
	{
		printf("opt = %c\n", opt);
		printf("optarg = %s\n", optarg);
		printf("optind = %d\n", optind);
		printf("argv[optind-1] = %s\n", argv[optind-1]);
		printf("option_index = %d\n\n", option_index);
	}
}

void test_getopt(int argc, char *argv[], const char *optstring)
{
	/**
	 * optstring:如果全是纯字母(chr)，则表示检测命令行参数是否包含-chr，如果字母后面还带":"，表示检测命令行
	 * 参数中是否存在-chr 100/-chr user之类的参数
	 *
	 * getopt会依次检测参数中是否包含optstring中的字母，需要多次调用getopt函数，直到其返回-1
	 */
	int opt;
	
	while((opt = getopt(argc, argv, optstring)) != -1)
	{
		fprintf(stdout, "opt = %c\n", opt);
		fprintf(stdout, "optarg = %s\n", optarg);
		fprintf(stdout, "optind = %d\n", optind);
		fprintf(stdout, "argv[optind-1] = %s\n\n", argv[optind-1]);
	}
}