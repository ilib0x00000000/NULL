# 字段类型

class AutoField(**options)
一个根据实际ID自动增长的IntegerField，通常不需要直接使用，如果不指定，一个主键字段将自动添加到创建的模型中

class BigIntegerField(**options)
一个64位整数，类似于一个IntegerField

class BinaryField(**options)
这是一个用来存储原始二进制码的field，只支持bytes赋值

class BooleanField(**options)
true/false字段

class CharField(max_length=None, **options)
一个用来存储从小到很大各种长度的字符串的地方

class CommaSeparatedIntegerField(max_length=None, **options)
一个逗号分隔的整数字段

class DateField([auto_now=False, auto_now_add=False, **options])
使用Python的datetime.date实例表示的日期
auto_now: 每次保存对象时，自动设置该字段为当前时间，用于最后一次修改的时间戳
auto_now_add: 当对象第一次被创建时自动设置为当前时间，用于创建时间的时间戳


class DateTimeField([auto_now=False, auto_now_add=False, **options])
这是通过python datatime.datetime实例表示的日期和时间

class DecimalField(max_digits=None, decimal_places=None, **options)
表示十进制的浮点数
max_digits: 位数总数，包括小数点后的位数，该值必须大于decimal_places
decimal_places: 小数点后的数字数量

class DurationField(**options)
用作存储一段时间的字段类型

class EmailField(max_length=254, **options)
一个CharField用来检查输入的email地址是否合法

class FileField(upload_to=None, max_length=100, **options)
一个上传文件的字段

class FilePathField(path=None, match=None, recursive=False, max_length=100, **options)
一个CharField，内容仅限文件系统内特定目录下的文件名

class FloatField(**options)
用Python的一个float实例来表示一个浮点数

class ImageField(upload_to=None, height_field=None, width_field=None, max_length=100, **options)
继承了FileField的所有属性和方法，还对上传的对象进行校验，确保它是个有效的image

class IntegerField(**options)
整数


class GenericIPAddressField(**options)
一个IPv4或IPv6地址

class NullBooleanField(**options)
类似BooleanField，但是允许NULL作为一个选项


class PositiveIntegerField(**options)
类似整型，但是值必须是正数或0

class PositiveSmallIntegerField(**options)
类似PositiveIntegerField，但是值是在0-32767之间


class SlugField(max_length=50, **options)
Slug是一个新闻术语，叫做短标题


class SmallIntegerField(**options)

class TextField(**options)
大文本字段


class TimeField(auto_now=False, auto_now_add=False, **options)
时间字段，和Python的datetime.time一样

class URLField(max_length=200, **options)
一个CharField类型的URL

class UUIDField(**options)
一个用来存储UUID的字段，使用Python的UUID类


# 关系字段
class ForeignKey(Model, **options)
多对一关系，需要一个位置参数，与该模型关联的类
fk.limit_choices_to
fk.related_name
fk.related_query_name
fk.to_field
fk.db_constraint
fk.on_delete
fk.swappable
fk.allow_unsaved_instance_assignment

class ManyToManyField(Model, **options)
多对多关系
mtm.related_name
mtm.related_query_name
mtm.limit_choices_to
mtm.symmetrical
mtm.through
mtm.through_fields
mtm.db_table
mtm.db_constraint
mtm.swappable
mtm.allow_unsaved_instance_assignment

class OneToOneField(Model[, parent_link=False, **options])
一对一关联关系





# 元数据
# Meta
abstract: 如果这个选项为True，则表示这个模型是抽象基类
app_label: 如果一个模型位于标准的位置之外，该模型必须定义它属于哪个应用
db_table: 该模型所用的数据表的名称
db_tablespace: 当前模型所使用的数据库表空间的名字，默认值是项目设置中的DEFAULT_TABLESPACE
default_related_name: 这个名字会默认被用于一个关联对象到当前对象的关系
get_latest_by: 模型中某个可排序的字段的名称
managed: 默认为True，意思是Django在migrate命令中创建合适的数据表，并且会在flush管理命令中移除它们，换句话说，Django会管理这些数据表的生命周期
order_with_respect_to: 按照给定的字段把这个对象标记为“可排序的”，这一属性通常用到关联对象上面，使它在父对象中有序
ordering: 对象默认的顺序，获取一个对象的列表时使用
permissions: 设置创建对象时权限表中额外的权限
default_permissions: 对数据库表的默认操作权限，增删改等等
proxy: 如果为True，表示这是一个Model的子类，将作为该父类的一个代理模型
select_on_save: 该选项决定了是否采用Django 1.6之前的django.db.models.Model.save()算法
unique_together: 用来设置的不重复的字段组合
index_together: 用来设置带有索引的字段组合
verbose_name: 对象的一个易于理解的名称，为单数
verbose_name_plural: 该对象复数形式的名称