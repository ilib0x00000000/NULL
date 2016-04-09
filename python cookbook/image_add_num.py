#!/usr/bin/env  python
# -*- coding:utf-8 -*-

"""
给一张图片的右上角添加一个数字，实现类似微信头像消息提示
注：开发环境
			os : ubuntu14.04
			py version : 2.7.9
			PIL version : 1.1.7 
"""

"""
	@author : ilib0x00000000
	@email  : ilib0x00000000@gmail.com
	@version: 1.0
	@date	: 2016/04/08
	@project: 给一张图片的右上角添加数字
"""



from random import randint
from PIL import Image, ImageDraw, ImageFont


im = Image.open("P60403-201124.jpg")


def  insert_num(img_url):
	img = Image.open(img_url)									# 得到一个图片文件对象

	draw = ImageDraw.Draw(img)

	ubuntu_font_url = "/usr/share/fonts/truetype/freefont/FreeSerifBoldItalic.ttf"
																# ubuntu下的字体文件位置
	text_font = ImageFont.truetype(ubuntu_font_url, size=40)	# 字体设置
	text_color = "#EE0000"										# 颜色取值

	(width,height) = img.size									# 得到图片的尺寸

	draw.text((width-20,0), str(randint(1,5)), font = text_font, fill = text_color)

	img.save("new_img.jpg", 'jpeg')

	return 0

if __name__ == '__main__':
	insert_num("test.jpg")