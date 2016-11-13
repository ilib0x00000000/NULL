# Mac上git的使用
***

1. 安装git：
	下载安装Git installer，官网【http://git-scm.com/downloads】
	双击安装

2. 创建用户：
	git config --global user.name "。。。"
	git config --global user.email "。。。"

3. 生成ssh-key：
	ssh-keygen

	在~/.ssh/下有3个文件

# Mac向Github提交代码
***
注：Github上已有仓库，仓库中也有文件
现将本机的公钥文件中的字符串导入github的SSH密码串中

1. 创建一个与远程仓库同名的文件夹：
	`
	$ mkdir NULL/
	`

2. 进入刚刚创建的文件夹，初始化一个git仓库：
	`
	$ cd NULL/
	$ git init
	`

3. 关联远程的仓库：
	`
	$ git remote add origin git@github.com:ilib0x00000000/NULL.git
	`

4. 将远程仓库中的文件同步下来：
	`
	$ git pull origin master
	`

5. 添加文件
	`
	$ git add file
	`
6. 提交文件
	`
	$ git commit -m '....'
	`

7. 同步到远程仓库
	`
	$ git push origin master
	`