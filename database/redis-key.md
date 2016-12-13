# Redis key命令
***

### DEL key
在键存在时，删除key

### DUMP key
序列化给定key，并返回被序列化的值
如果给定的key存在，返回被序列化的值，如果不存在，返回nil

### EXISTS key
检查给定key是否存在
如果键存在，返回1，如果键不存在，返回0

### EXPIRE key seconds
设置键的过期时间
如果设置成功返回1，否则返回0

### EXPIREAT key timestamp
和EXPIRE类似，用UNIX时间戳为键设置过期时间
如果设置成功返回1，否则返回0

### PEXPIRE key milliseconds
设置key的过期时间以毫秒计
如果设置成功返回1，否则返回0

### PEXPIREAT key milliseconds-timestamp
用UNIX时间戳的毫秒设置键的过期时间
如果设置成功返回1，否则返回0

### KEYS pattern
查找所有符合给定模式的key

### MOVE key db
将当前数据库的key移动到指定的数据库

### PERSIST key
移除key的过期时间，key将持久保存

### PTTL key
以毫秒为单位返回key的剩余的过期时间

### TTL key
以秒为单位，返回key的剩余生存时间

### RANDOMKEY
从当前数据库随机返回一个key
如果数据库中不存在任何键，返回nil

### RENAME key newkey
修改key的名称

### RENAMENX key newkey
仅当newkey不存在时，将key该名为newkey

### TYPE key
返回key所存储的值得类型