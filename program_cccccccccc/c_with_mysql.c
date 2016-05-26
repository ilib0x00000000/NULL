#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>

/**
 _   _          _   _         _______ _       _ _______  _______  _______  _______  _______  _______  _______  _______ 
(_) | |        (_) | |       / _____ \\\     /// _____ \/ _____ \/ _____ \/ _____ \/ _____ \/ _____ \/ _____ \/ _____ \
| | | |        | | | |       |/     \| \\   // |/     \||/     \||/     \||/     \||/     \||/     \||/     \||/     \|
| | | |        | | | |______ ||     ||  \\ //  ||     ||||     ||||     ||||     ||||     ||||     ||||     ||||     ||
| | | |        | | | |_____ \||     ||   ||    ||     ||||     ||||     ||||     ||||     ||||     ||||     ||||     ||
| | | |        | | | |     \|||     ||  //\\   ||     ||||     ||||     ||||     ||||     ||||     ||||     ||||     ||
| | | |_______ | | | |____ /||\_____/| //  \\  |\_____/||\_____/||\_____/||\_____/||\_____/||\_____/||\_____/||\_____/|
|_| |_________||_| |_|______/\_______///    \\ \_______/\_______/\_______/\_______/\_______/\_______/\_______/\_______/

*************************************************************************************
# @Date    : 2016-05-26 16:45:48 
# @Email   : ilib0x00000000@gmail.com
# @Version : 0.1
*************************************************************************************
 */

/**
 * 构造结构体存储学生信息
 * 向数据库中写入学生信息
 */


typedef struct Age
{
	int year;
	int month;
	int date;
}Age;

typedef struct Student
{
	char id[9];
	char name[25];
	unsigned char sex;
	Age birth;
	int score;
}Student;

int main(int argc, char const *argv[])
{
	int i;
	Student students[3];

	MYSQL mysql;								// 连接数据库的句柄
	MYSQL *sock;

	MYSQL_RES *res;								// 查询结果集
	MYSQL_FIELD *fd;							// 包含字段信息的结构
	MYSQL_ROW row;								// 存放一行查询结果的字符串数组


	char sql_string[200];						// SQL语句


	for(i = 0 ; i < sizeof(students)/sizeof(Student); i++)
	{
		/**
		 * 不考虑数据的正确性
		 */
		printf("请输入学号：");
		scanf("%s", students[i].id);
		printf("请输入姓名：");
		scanf("%s", students[i].name);
		printf("请选择性别男/女(1/0):");
		scanf("%d",&(students[i].sex));
		printf("请输入出生日期：");
		scanf("%d %d %d", &(students[i].birth.year), &(students[i].birth.month), &(students[i].birth.date));
		printf("请输入分数：");
		scanf("%d", &(students[i].score));
		printf("输入成功！\n");	
	}


	mysql_init(&mysql);								// 初始化
	
	/**
	 * 连接数据库，
	 * 连接成功，返回MYSQL *句柄
	 * 连接失败，返回NULL
	 */
	sock = mysql_real_connect(&mysql, "localhost", "root", "", "", 0, NULL, 0);
	if(!sock)
	{
		printf("can't connect database\n");
		exit(1);
	}

	/*连接数据库成功*/
	for (i = 0; i < sizeof(students)/sizeof(Student); ++i)
	{
		/*构造SQL 语句*/
		sprintf(sql_string, "insert into c_test values('%s', '%s', %d, '%s', %d);", students[i].id, students[i].name,
				students[i].sex,"1996-05-27",students[i].score);
		printf("%s\n", sql_string);
		
		/**
		 * 向数据库中插入数据
		 * int mysql_query(MYSQL *mysql,const char *query);
		 * 返回值为0，表示成功， 非0，表示错误
		 */
		
		if(mysql_query(sock, sql_string))
		{
			printf("Error 向数据库中写入数据时失败\n");
		}else
		{
			printf("success\n");
			if(mysql_query(sock,"select * from c_test"))
			{
				printf("查询失败\n");
			}else
			{
				/**
				 * 获得结果集指针
				 * MYSQL_RES *mysql_store_result(MYSQL *mysql);
				 * 成功：返回结果集指针，失败：返回NULL 
				 */
				res = mysql_store_result(sock);

				if(!res)
				{
					printf("获取结果集失败\n");
				}else
				{
					/**
					 * 遍历结果集
					 * MYSQL_ROW mysql_fetch_row(MYSQL_RES *result);
					 * 迭代结果集指针指向的结果集，如果迭代结束或者发生错误，返回NULL
					 */
					
					printf("id \t name \t sex \t birth \t socre\n");
					while(row = mysql_fetch_row(res))
					{
						printf("%s \t %s \t %d \t %s \t %d\n", row[0], row[1], row[2], row[3], row[4]);
					}

					/**
					 * 释放结果集
					 */
					 mysql_free_result(res);
				}
			}
		}
		
	}

	
	mysql_close(sock);

	return 0;
}



/**
 *Ubuntu下编译C文件
 * gcc filename.c -o filename $(mysql_config --cflags --libs) 
 */