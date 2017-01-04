# MySQL基本操作
***

创建两张表，一张学生信息表，一张成绩表。学生信息表的主键对应成绩表的外键
创建表时有6个约束：
    * NOT NULL 
    * UNIQUE
    * PRIMARY KEY
    * FOREIGN KEY
    * CHECK
    * DEFAULT


SQL UNIQUE约束：
UNIQUE约束唯一标识数据库表中的每条记录
UNIQUE和PRIMARY KEY约束均为列或集合提供了唯一性的保证
PRIMARY KEY拥有自动定义的UNIQUE约束
每张表可以有多个UNIQUE约束，但是每个表只能有一个PRIMARY KEY约束
删除UNIQUE约束: ALTER TABLE table_name DROP INDEX field;
添加UNIQUE约束: ALTER TABLE table_name ADD UNIQUE (field);


PRIMARY KEY约束：
PRIMARY KEY约束唯一标识数据库表中的每条记录
主键必须包含唯一的值
主键列不能包含NULL值
每个表都应该有一个主键，并且每个表只能有一个主键
在表存在的情况下，创建主键：ALTER TABLE table_name ADD PRIMARY KEY (field);
删除表的主键：ALTER TABLE table_name DROP PRIMARY KEY;


FOREIGN KEY约束：
一个表中的FOREIGN KEY指向另一个表中的PRIMARY KEY
添加FOREIGN KEY，在CREATE TABLE table_name语句的最后：
    ...FOREIGN KEY(field) REFERENCES table_name(fieldx)
当表存在时，创建外键：
    ALTER TABLE table_name ADD FOREIGN KEY(field) REFERENCES table_name(fieldx)
删除外键
    ALTER TABLE table_name DROP FOREIGN KEY field


CHECK约束：
CHECK约束用于限制列中值的范围
如果对单个列定义CHECK约束，那么该列只允许特定的值
如果对一个表定义CHECK约束，那么此约束会在特定的列中对值进行限制
添加CHECK约束，在CREATE TABLE table_name语句的最后：
    ...CHECK (field<n AND field>x)
当表存在时，添加CHECK约束：
    ALTER TABLE table_name ADD CHECK(field<x AND field>n)
删除CHECK约束：
    ALTER TABLE table_name DROP CHECK field



学生信息表字段： sid（学号），name（学生姓名），sex（性别），birth（出生日期），major（专业）
成绩表字段：sid（学号），math（数学），english（英语），chinese（语文）

CREATE TABLE stu_info(
    sid    INTEGER     PRIMARY KEY   AUTO_INCREMENT,
    name   VARCHAR(64) NOT NULL,
    sex    INTEGER     DEFAULT 1,
    birth  DATE        NOT NULL,
    major  INTEGER     NOT NULL,
    # UNIQUE(name)
    # CONSTRAINT stu_id UNIQUE(sid, name) 命名UNIQUE约束，以及为多个列定义UNIQUE约束
    # FOREIGN KEY(major) REFERENCES coll_majors(major_id)

);


### 索引
CREATE INDEX语句用于在表中创建索引
在不读取整个表的情况下，索引使数据库应用可以更快的查找数据

语法：
创建一个简单的索引，允许使用重复的值
CREATE INDEX index_name ON table_name(field);

创建一个唯一的索引，唯一的索引意味着两个行不能拥有相同的索引值
CREATE UNIQUE INDEX index_name ON table_name(field);

删除索引：
ALTER TABLE table_name DROP INDEX index_name;

### 删除数据库
DROP DATABASE database_name;

### 删除表
DROP TABLE table_name;

### 增删列
ALTER TABLE table_name ADD column_name datatype;
ALTER TABLE table_name DROP COLUMN column_name;




