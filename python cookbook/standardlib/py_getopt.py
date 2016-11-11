#!/usr/bin/env  python
# -*- coding:utf-8 -*-

'''
解析命令行参数
'''

def test_getopt():
    '''getopt函数
    opts, args = getopt.getopt(args, shortopts, longopts=[])
    参数:
        o 第1个参数是要解析的参数序列,通常来自sys.argv[1:]
        o 第2个参数是单字符选项的选项定义串,如果某个选项需要一个参数,相应字母后面会有一个冒号
        o 第3个参数是长格式选项名序列,长格式选项可以包含多个字符,序列中的选项名不包括'--'前缀,如果某个长选项需要一个参数,其名应当有一个后缀'='
    返回值:
        o 分析出的(option, value)列表对
        o 不属于格式信息的剩余命令行参数

    正常情况下,一旦遇上第一个非选项参数,选项处理就会停止,gnu_getopt()函数就是为了解决这个问题的,它允许在命令行上以任意顺序混合选项和非选项参数
    options, remainder = getopt.gnu_getopt(args, shortopts, longopts=[])
    '''
    import getopt

    opts, args = getopt.getopt(
                            ['-a', '-bvalue', '-c', '123'], # 命令行参数
                            'ab:c:', # 表示-a没有参数,-b和-c需要参数
                        )

    for opt in opts:
        print opt

    opts, args = getopt.getopt(
                            ['-c', '-ieth0', '--help', '--host=localhost', '--port=3306'], # 命令行参数
                            'ci:',    # 单字符选项,表示-c不带参数,-i带参数
                            ['help', 'host=', 'port='] # 长选项,--help不带参数,--host和--port带参数
                        )

    for opt in opts:
        print opt

    for arg in args:
        print arg



def demo_getopt():
    '''关于getopt函数更完整的例子
    '''
    import sys
    import getopt

    version = '1.0'
    verbose = False
    output_filename = 'default.out'

    print 'ARGV   :', sys.argv[1:]

    try:
        options, remainder = getopt.getopt(
            sys.argv[1:],
            'o:v',
            ['output=', 'verbose', 'version=']
        )
    except getopt.GetoptError as err:
        print 'ERROR: ', err
        sys.exit(1)

    print 'OPTIONS: ', options

    for opt,arg in options:
        if opt in ('-o', '--output'):
            output_filename = arg
        elif opt in ('-v', '--verbose'):
            verbose = True
        elif opt=='version':
            version = arg

    print 'VERSION: ', version
    print 'VERBOSE: ', verbose
    print 'OUTPUT: ', output_filename
    print 'REMAINING: ', remainder


if __name__ == '__main__':
    demo_getopt()
