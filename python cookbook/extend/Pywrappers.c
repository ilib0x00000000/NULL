#include"Python.h"

#include"extend.h"

/*
在Python中使用C的扩展：
	1. 导入头文件 Python.h
	2. 包装C源文件的函数
	3. 创建一个包含函数的数组
	4. 初始化模块
	5. 编译，在另一个模块中
*/


/*
	包装源函数时，要定义一个静态的，类似PyObject * Module_functionname()的函数
	函数的返回值类型：PyObject *
	函数名由模块名和源函数名组成
*/
static PyObject* Cextends_factor(PyObject *self, PyObject *args);

static PyObject* Cextends_factor(PyObject *self, PyObject *args)
{
	/*
		在包装函数中：包装函数接受Python调用，传入的参数，然后将Python的参数转换成C的参数，再将C的运算结果转换成Python的对象
		Python数据转换成C数据：PyArg_ParseTuple/PyArg_ParseTupleAndKeywords()
		将C数据转换成Python对象：Py_BuildValue()

		注意：如果Python数据转换成C数据成功会返回1，表示成功，否则返回0，表示失败。
	*/
	int res;
	int num;
	PyObject * retval;

	res = PyArg_ParseTuple(args, "i", &num);

	if(!res)
		return NULL;

	res = factor(num);

	retval = (PyObject *)Py_BuildValue("i", res);

	return retval;
}


static PyObject* Cextends_reverse(PyObject *self, PyObject *args);

static PyObject* Cextends_reverse(PyObject *self, PyObject *args)
{
	char *origin_str;

	if(!(PyArg_ParseTuple(args, "s", &origin_str)))
	{
		return NULL;
	}

	return (PyObject *)Py_BuildValue("s", reverse(origin_str));
}




/*
	创建静态数组，包含源函数与包装函数的对应关系，方便导入模块时调用
	数组名组成： ModuleMethods
*/
static PyMethodDef CextendsMethods[] = {
	{"factor", Cextends_factor, METH_VARARGS},
	{"reverse", Cextends_reverse, METH_VARARGS},
	{NULL, NULL}
};




/*
	使用initModule()函数初始化模块
	在该函数中需要调用Py_InitModule()函数，并调用模块名和ModuleMethods数组名

*/
void initCextends();

void initCextends()
{
	Py_InitModule("Cextends", CextendsMethods);
}




/*
附：Python与C之间的数据转换的通用代码

格式代码					Python类型					C型
------------------------------------------------------------------------
s 						str 						char *
z 						str/None					char * /NUll
i 						int 						int
l 						long 						long
c 						str 						char
d 						float 						double

D 						complex 					Py_Complex *
O 						(any) 						PyObject *
S 						str 						PyStringObject
*/