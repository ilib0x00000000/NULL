#include<sys/acct.h>

#include"apue.h"

#if defined(BSD)
#define acct acctv2
#define ac_flag ac_trailer.ac_flag
#define FMT "%-*.*s e=%.0f, chars=%.0f, %c %c %c %c\n"
#elif defined(HAS_AC_STAT)
#define FMT "%-*.*s e=%6ld, chars=%7ld, stat=%3u: %c %c %c %c\n"
#else
#define FMT "%-*.*s e=%6ld, chars=%7ld, %c %c %c %c\n"
#endif

#if defined(LINUX)
#define acct acct_v3
#endif

#if !defined(HAS_ACORE)
#define ACORE 0
#endif

#if !defined(HAS_AXSIG)
#define AXSIG 0
#endif

#if !defined(BSD)
static unsigned long compt2ulong(comp_t comptime)
{
	int  exp;
	unsigned long value;

	value = comptime & 0x1fff;
	exp = (comptime >> 13) & 7;
	while(exp-- > 0)
	{
		value *= 8;
	}

	return value;
}
#endif

int main(int argc, char const *argv[])
{
	FILE *fp;
	struct acct acdata;

	if(argc != 2)
	{
		perror("command error");
		exit(1);
	}

	if((fp = fopen(argv[1], "r")) == NULL)
	{
		perror("open file failed");
		exit(1);
	}

	while(fread(&acdata, sizeof(acdata), 1, fp) == 1)
	{
		printf(FMT, (int)sizeof(acdata.ac_comm), (int)sizeof(acdata.ac_comm), acdata.ac_comm,
#if defined(BSD)
		acdata.ac_etime, acdata.ac_io,
#else
		compt2ulong(acdata.ac_etime), compt2ulong(acdata.ac_io),
#endif

#if defined(HAS_AC_STAT)
#endif

		acdata.ac_flag & ACORE ? 'D' : ' ',
		acdata.ac_flag & AXSIG ? 'X' : ' ',
		acdata.ac_flag & AFORK ? 'F' : ' ',
		acdata.ac_flag & ASU   ? 'S' : ' ');
	}

	if(ferror(fp))
	{
		perror("read error");
		exit(1);
	}

	return 0;
}
