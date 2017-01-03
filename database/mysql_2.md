# MySQL基本操作
***

### 创建数据库
CREATE DATABASE database_name;


### 创建表
CREATE TABLE table_name
(
    field0 type extra,
    field1 type extra,
    field2 type extra,
    ...
    fieldn type,
    ...
);

demo1:
CREATE TABLE stu_info(
    sid   INTEGER     PRIMARY KEY   AUTO_INCREMENT,  # 设置自增的主键
    name  VARCHAR(64) NOT NULL,
    sex   INTEGER     NOT NULL      DEFAULT 1,
    birth DATE        NOT NULL,
    major INTEGER     NOT NULL
);

demo2:
CREATE TABLE recond(
    rid     INTEGER      PRIMARY KEY,            # 设置主键
    sid     INTEGER,
    math    INTEGER      NOT NULL,
    english INTEGER      NOT NULL,
    chinese INTEGER      NOT NULL,
    CHECK(math<=100 AND math>=0),                # 约束math的值只能在[0, 100]之间
    CHECK(english<=100 AND english>=0),
    CHECK(chinese<=100 AND chinese>=0),
    FOREIGN KEY(sid)     REFERENCES   stu_info(sid)  # 设置外键
);

创建数据库表的时候，可以设置SQL约束(Constraints)
约束有如下：
    * NOT NULL     # 非空
    * UNIQUE       # 唯一性
    * PRIMARY KEY  # 主键
    * FOREIGN KEY  # 外键
    * CHECK        # 添加额外条件
    * DEFAULT      # 默认值


### 数据类型
MySQL数据类型主要分为3类：数值、日期和字符串

1. 数值类型
TINYINT     1B   (-128, 127)      (0, 255)        小整数值
SMALLINT    2B   (-32768, 32767)  (0, 2^16-1)     大整数值
MEDIUMINT   3B   (-2^23, 2^23-1)  (0, 2^24-1)     大整数值
INT/INTEGER 4B   (-2^31, 2^31-1)  (0, 2^32-1)     大整数值
BIGINT      8B   (-2^63, 2^63-1)  (0, 2^64-1)     极大整数值
FLOAT       4B                                    单精度浮点值
DOUBLE      8B                                    双精度浮点值
DECIMAL    DECIMAL(M, D)                          小数


2. 日期类型
DATE     3B    '1000-01-01'/'9999-12-31'  YYYY-MM-DD   日期值
TIME     3B    -838:59:59/838:59:59       HH:MM:SS     时间值或持续时间
YEAR     1B    1901/2155                  YYYY         年份值
DATETIME 8B    1000-01-01 00:00:00/9999-12-31 YYYY-MM-DD HH:MM:SS 混合日期时间值
TIMESTAMP4B    1970-01-01 00:00:00/2037-xx-xx YYYYMMDD HHMMSS     时间戳


3. 字符串类型
CHAR        0-255字节            定长字符串
VARCHAR     0-65535字节          变长字符串
TINYBLOB    0-255字节            不超过255个字符的二进制字符串
TINYTEXT    0-255字节            短文本字符串
BLOB        0-65535字节          二进制形式的中等长度文本数据
TEXT        0-65535字节          长文本数据
MEDIUMBLOB  0-16777215字节       二进制形式的中等长度文本数据
MEDIUMTEXT  0-16777215字节       中等长度文本数据
LONGBLOG    0-42亿字节           二进制形式的极大文本数据
LONGTEXT    0-42亿字节           极大文本数据
