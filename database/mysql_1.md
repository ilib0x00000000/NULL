# MySQL管理
***

### mysql的配置文件
/etc/my.cnf

### 显示所有数据库
SHOW DATABASES;


### 选择数据库
USE database_name;


### 显示指定数据库的所有表
SHOW TABLES;


### 显示表的的属性，字段信息
SHOW COLUMNS FROM table_name;


### 显示数据库表的详细索引信息，包括PRIMARY KEY（主键）
SHOW INDEX FROM table_name;
+-----------+------------+----------+--------------+-------------+-----------+-------------+----------+--------+------+------------+---------+---------------+
| Table     | Non_unique | Key_name | Seq_in_index | Column_name | Collation | Cardinality | Sub_part | Packed | Null | Index_type | Comment | Index_comment |
+-----------+------------+----------+--------------+-------------+-----------+-------------+----------+--------+------+------------+---------+---------------+
| auth_user |          0 | PRIMARY  |            1 | id          | A         |           0 |     NULL | NULL   |      | BTREE      |         |               |
| auth_user |          0 | username |            1 | username    | A         |           0 |     NULL | NULL   |      | BTREE      |         |               |
+-----------+------------+----------+--------------+-------------+-----------+-------------+----------+--------+------+------------+---------+---------------+


### 输出MySQL数据库管理系统的性能及统计信息
SHOW TABLE STATUS FROM database_name;              # 显示数据库中所有表的信息
SHOW TABLE STATUS FROM database_name LIKE 'user%'; # 数据库中以‘user’开头的表的信息
SHOW TABLE STATUS FROM database_name LIKE 'user%'\G;   # 查询结果按列打印

