#!/usr/bin/env  python
# -*- coding:utf-8 -*-

'''
生成验证码
生成验证码的字体使用说明：
根据操作系统的不同，拥有的字体库也各不同，font_type:由操作系统安装的字体文件决定
mac下字体文件在: /System/Library/Font下
'''

from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
from PIL import ImageFilter
import random
import math, string

_letter_cases = 'abcdefghjkmnpqrstuvwxy'   # 小写字母，除去易干扰的i,l,o,z
_upper_cases  = _letter_cases.upper()      # 大写字母
_numbers      = ''.join(map(str, range(3, 10))) # 数字，除去易干扰的1，2
init_chars    = ''.join([_letter_cases, _upper_cases, _numbers])


def get_chars(chars, length):
	# 生成给定长度的字符串，返回列表格式
	return random.sample(chars, length)

def create_lines(n_line, draw, size):
	# 绘制干扰线
	line_num = random.randint(*n_line)

	for i in range(line_num):
 		begin = (random.randint(0, size[0]), random.randint(0, size[1])) # 起始点
		end = (random.randint(0, size[0]), random.randint(0, size[1]))  #结束点
		draw.line([begin, end], fill=(0, 0, 0))

def create_points(point_chance, width, height, draw):
	# 绘制干扰点
	chance = min(100, max(0, int(point_chance)))  # 大小限制在[0, 100]

	for w in xrange(width):
		for h in xrange(height):
			tmp = random.randint(0, 100)
			if tmp > 100-chance:
				draw.point((w,h), fill=(0,0,0))

def create_strs(chars, length, font_type, font_size, width, height, fg_color, draw):
	# 绘制验证码字符
	c_chars = get_chars(chars, length)
	strs = ' %s ' % ''.join(c_chars)  # 每个字符前后以空格隔开

	font = ImageFont.truetype(font_type, font_size)
	font_width, font_height = font.getsize(strs)

	draw.text(((width-font_width)/3,(height-font_height)/3), strs, font=font, fill=fg_color)

	return ''.join(c_chars)

def create_validate_code(
		size         = (150, 50),      # 图片的大小，宽高默认为120，30
		chars        = init_chars,     # 允许的字符集
		img_type     = 'PNG',          # 图片保存的格式，默认为GIF，可选的为GIF，JPEG，TIFF，PNG
		mode         = 'RGB',          # 图片模式，默认为RGB
		bg_color     = (255, 255, 255),# 背景颜色，默认为白色
		fg_color     = (0, 0, 255),    # 前景色，验证码字符颜色，默认为蓝色
		font_size    = 24,             # 验证码字体大小
		font_type    = 'Keyboard.ttf', # 验证码字体
		length       = 4,        # 验证码字符个数
		draw_lines   = True,     # 是否化干扰线
		n_line       = (1,2),    # 干扰线的条数范围，格式元组，默认为(1,2)
		draw_points  = True,     # 是否画干扰点
		point_chance = 2,        # 干扰点出现的概率，大小范围[0,100]
	):
	width, height = size  # 宽，高
	img = Image.new(mode, size, bg_color) # 创建图形
	draw = ImageDraw.Draw(img)  # 创建画笔

	if draw_lines:
		create_lines(n_line, draw, size)
	if draw_points:
		create_points(point_chance, width, height, draw)
	strs = create_strs(chars, length, font_type, font_size, width, height, fg_color, draw)

	# 图形扭曲参数
	params = [1 - float(random.randint(1, 2)) / 100,
			0,
			0,
			0,
			1 - float(random.randint(1, 10)) / 100,
			float(random.randint(1, 2)) / 500,
			0.001,
			float(random.randint(1, 2)) / 500
		]

	img = img.transform(size, Image.PERSPECTIVE, params) # 创建扭曲
	img = img.filter(ImageFilter.EDGE_ENHANCE_MORE) # 滤镜，边界加强（阈值更大）
	
	return img, strs

if __name__ == '__main__':
	code_img, code_str = create_validate_code()

	code_img.save('test.png', 'PNG')
	print code_str