#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
解析简单的数学表达式：
思路：简单的数学表达式是指只包括运算符，数字和括号的表达式。一个表达式可以看成3部分组成，
	左操作数，运算符和右操作数，而运算符的优先级为括号 > */ > +-，因此在解析时，考虑优先级
	高的运算符，其次括号内的表达式与一个普通的表达式一样，所以可以使用递归求解
	注：开发环境
			os : ubuntu14.04
			py version : 3.4
"""


"""
	@author : ilib0x00000000
	@email  : ilib0x00000000@gmail.com
	@version: 1.0
	@date	: 2016/04/12
	@project: 解析简单的数学表达式
"""

import re
import collections

# 命名捕获组
NUM = r"(?P<NUM>\d+)"
PLUS = r"(?P<PLUS>\+)"
MINUS = r"(?P<MINUS>-)"
TIMES = r"(?P<TIMES>\*)"
DIVIDE = r"(?P<DIVIDE>/)"
LPAREN = r"(?P<LPAREN>\()"
RPAREN = r"(?P<RPAREN>\))"
WS = r"(?P<WS>\s+)"


# 编译正则表达式
master_pat = re.compile('|'.join([NUM, PLUS, MINUS, TIMES, DIVIDE, LPAREN, RPAREN, WS]))

Token = collections.namedtuple('Token', ['type', 'value'])

def generate_tokens(text):
	scanner = master_pat.scanner(text)

	for m in iter(scanner.match, None):
		"""当使用正则表达式去扫描字符串时，如果有匹配的对象，
		则调用返回结果的lastgroup()方法可以得到匹配子组的命名，
		调用group()方法可以得到匹配子组的值
		"""
		tok = Token(m.lastgroup, m.group())
		if tok.type != 'WS':
			yield tok


class SimpleParser:
	"""简单的数学表达式解析器
	参数：
		expre： 简单的数学表达式，只包含数字，括号和运算符
	"""

	def parse(self,text):
		self._tokens = generate_tokens(text)
		self.tok = None
		self.nexttok = None
		self._advance()

		return self.expr()

	def _advance(self):
		self.tok, self.nexttok = self.nexttok, next(self._tokens,None)

	def _accept(self, toktype):
		if self.nexttok and self.nexttok.type == toktype:
			self._advance()
			return True
		else:
			return False

	def _except(self, toktype):
		if not self._accept(toktype):
			raise SyntaxError('Expected ' + toktype)

	def expr(self):
		exprval = self.term()
		
		while self._accept('PLUS') or self._accept('MINUS'):
			op = self.tok.type

			right = self.term()

			if op == 'PLUS':
				exprval += right
			else:
				exprval -= right

		return exprval



	def term(self):
		termval = self.factor()
		
		while self._accept('TIMES') or self._accept('DIVIDE'):
			op = self.tok.type
			right = self.factor()

			if op == 'TIMES':
				termval *= right
			else:
				termval /= right

		return termval

	def factor(self):
		if self._accept('NUM'):
			return int(self.tok.value)

		elif self._accept('LPAREN'):
			exprval = self.expr()
			self._except('RPAREN')
			return exprval
		else:
			raise SyntaxError('Error')


if __name__ == '__main__':
	s = SimpleParser()

	# output 5
	print(s.parse('3+2'))

	# output 12
	expre = r'2 + ( 4 - 2 ) * 5'
	print(s.parse(expre))