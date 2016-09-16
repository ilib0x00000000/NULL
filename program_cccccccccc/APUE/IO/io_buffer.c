#include<stdio.h>
#include<stdlib.h>

/**
 * 二进制I/O
 * #include<stdio.h>
 * size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
 * size_t fwrite(const void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
 * 								返回值：读或写的对象数
 *
 * 定位流：
 * #include<stdio.h>
 * long ftell(FILE *fp);
 * off_t ftello(FILE *fp);
 * 								返回值：若成功，返回当前文件位置指示，若出错，返回-1
 * int fseek(FILE *fp, long offset, int whence);
 * int fseeko(FILE *fp, off_t offset, int whence);
 * 								返回值：若成功，返回0，若出错，返回-1
 * void rewind(FILE *fp);
 *
 * fgetpos将文件位置指示器的当前值存入由pos指向的对象中
 * #include<stdio.h>
 * int fgetpos(FILE *restrict fp, fpos_t *restrict pos);
 * int fsetpos(FILE *fp, const fpos_t *pos);
 * 								返回值：若成功，返回0，若出错，返回-1
 *
 * 格式化输出：
 * #include<stdio.h>
 * int printf(const char *restrict format, ...);
 * int fprintf(FILE *restrict fp, const char *restrict format, ...);
 * int dprintf(int fd, const char *restrict format, ...);
 * 								返回值：若成功，返回输出字节数，若出错，返回负值
 * int sprintf(char *restrict buf, const char *restrict format, ...);
 * 								返回值：若成功，返回存入数组的字符数，若编码出错，返回负值
 * int snprintf(char *restrict buf, size_t n, const char *restrict format, ...);
 * 								返回值：若缓冲区足够大，返回将要存入数组的字符数，若编码出错，返回负值
 *
 * printf变体，将可变参数变成了arg
 * #include<stdio.h>
 * #include<stdarg.h>
 * int vprintf(const char *restrict format, va_list arg);
 * int vfprintf(FILE *restrict fp, const char *restrict format, va_list arg);
 * int vdprintf(int fd, const char *restrict format, va_list arg);
 * 								返回值：若成功，返回输出字符数，若输出出错，返回负值
 * int vsprintf(char *restrict buf, const char *restrict format, va_list arg);
 * 								返回值：若成功，返回存入数组的字符数，若编码出错，返回负值
 * int vsnprintf(char *restrict buf, size_t n, const char *restrict format, va_list arg);
 * 								返回值：若缓冲区足够大，返回存入数组的字符数，若编码出错，返回负值
 */

int buffer_size(FILE *);
int is_unbuffered(FILE *);
int is_linebuffered(FILE *);
void pr_stdio(const char *, FILE *);

int main(int argc, char const *argv[])
{
	FILE *fp;

	fputs("enter any character\n", stdout);
	if(getchar() == EOF)
	{
		perror("getchar error");
		exit(-1);
	}
	fputs("one line to standard error\n", stderr);

	pr_stdio("stdio", stdin);
	pr_stdio("stdout", stdout);
	pr_stdio("stderr", stderr);

	if( (fp = fopen("/etc/passwd", "r")) == NULL)
	{
		perror("open /etc/passwd error");
		exit(-1);
	}

	if( getc(fp) == EOF)
	{
		perror("getc error");
		exit(-1);
	}

	pr_stdio("/etc/passwd", fp);

	return 0;
}

void pr_stdio(const char *name, FILE *fp)
{
	printf("stream = %s, ", name);
	if(is_unbuffered(fp))
		printf("unbuffered");
	else if(is_linebuffered(fp))
		printf("line buffered");
	else
		printf("fully buffered");

	printf(", buffer size = %d\n", buffer_size(fp));
}

#if defined(_IO_UNBUFFERED)
	int is_unbuffered(FILE *fp)
	{
		return (fp->_flags & _IO_UNBUFFERED);
	}
	int is_linebuffered(FILE *fp)
	{
		return (fp->_flags & _IO_LINE_BUF);
	}
	int buffer_size(FILE *fp)
	{
		return (fp->_IO_buf_end - fp->_IO_buf_base);
	}

#elif defined(__SNBF)
	int is_unbuffered(FILE *fp)
	{
		return (fp->flags & fp->__SNBF);
	}
	int is_linebuffered(FILE *fp)
	{
		return (fp->flags & fp->__SLBF);
	}
	int buffer_size(FILE *fp)
	{
		return fp->_bf._size;
	}

#elif defined(_IONBF)

	#ifdef _LP64
	#define _flag __pad[4]
	#define _ptr  __pad[1]
	#define _base __pad[2]
	#endif

	int is_unbuffered(FILE *fp)
	{
		return (fp->flag & _IONBF);
	}
	int is_linebuffered(FILE *fp)
	{
		return (fp->flag & _IOLBF);
	}
	int buffer_size(FILE *fp)
	{
		#ifdef _LP64
			return (fp->_base - fp->_ptr);
		#else
			return BUFSIZ;
		#endif
	}

#else

#error unknown stdio implementation!

#endif