Git
安装git
 Linux安装git：sudo apt-get install git
windows安装git：官网下载后，找到git bash终端
配置git
git config --global user.name "xxxxx"
git config --global user.email "xxxxx@xxx.com"
创建本地repo
mkdir dev
cd dev
git init
工作流
工作区—git stash/add—暂存/缓存区—git commit—本地repo—git push/pull—远程repo

查看提交状态：git status
查看提交记录：git log
远程仓库操作
克隆远程repo到本地：git clone xxxxxxx.git
获取远程repo的信息：git remote -v
更新远程repo的变更：git remote update origin
合并远程repo到本地：git merge origin/branch_name
拉取远程repo某个分支所有的变更到本地：git fetch origin yuancheng
拉取并合并远程分支变更到本地分支：git pull origin yuancheng:bendi
git pull = git fetch + git merge
推送本地分支到远程：git push origin yuancheng:bendi

提交修改到暂存区
暂存所有修改：git stash
恢复所有修改：git stash pop
提交修改到缓存区
缓存所有修改：git add .
缓存指定修改：git add xxx.cpp
撤销提交缓存：git rm --cached xxx.cpp
回滚缓存提交：git reset commit-id，会将晚于commit-id的提交stash
清楚本地变更：git reset --hard
提交缓存到本地repo
git commit -m "message"
分支管理
新建分支：git branch name，不会切换分支
切换分支：git checkout name
新建并切换分支：git checkout -b name
合并分支：git merge --no-ff name
删除本地分支：git checkout -d name
删除远程分支：git push origin --delete name
master分支：主分支
release分支：预发布分支，从develop分支创建
develop分支：日常开发分支
feature分支：为开发特定功能从develop分支切出的分支，完成后合并回develop
git rebase

打标签
查看标签：git tag
新建标签：git tag name
新建带备注的标签：git tag -a name -m "my tag"
给某个commit打标签：git tag name commit-id
推送tag：git push origin name
切换tag：git checkout name
删除tag：git tag -d name
