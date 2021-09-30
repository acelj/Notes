       ﻿   ﻿ ﻿1. 打开git  bash客户端
    ﻿   ﻿ ﻿2. 使用git bash 生成ssh key

```cpp
$ cd ~  #保证当前路径在”~”下

$ ssh-keygen -t rsa -C "xxxxxx@yy.com"  #建议填写自己真实有效的邮箱地址
Generating public/private rsa key pair.

Enter file in which to save the key (/c/Users/xxxx_000/.ssh/id_rsa):   #不填直接回车

Enter passphrase (empty for no passphrase):   #输入密码（可以为空）

Enter same passphrase again:   #再次确认密码（可以为空）

Your identification has been saved in /c/Users/xxxx_000/.ssh/id_rsa.   #生成的id_rsa文件为密钥

Your public key has been saved in /c/Users/xxxx_000/.ssh/id_rsa.pub.  #生成的id_rsa.pub公钥

The key fingerprint is:

e3:51:33:xx:xx:xx:xx:xxx:61:28:83:e2:81 xxxxxx@yy.com
```
*本机已完成ssh key设置，其存放路径为：c:/Users/xxxx_000/.ssh/下。
注释：可生成ssh key自定义名称的密钥，默认id_rsa。
$ ssh-keygen -t rsa -C "邮箱地址" -f ~/.ssh/githug_blog_keys #生成ssh key的名称为githug_blog_keys，慎用容易出现其它异常。

> 添加ssh key到GItHub
> 1.登录GitHub账号；点击右上角账号头像的“▼”→Settings→SSH kyes→Add SSH key。
> 2.复制id_rsa.pub的公钥内容。
> 3.进入c:/Users/xxxx_000/.ssh/目录下，打开id_rsa.pub文件，全选复制公钥内容。
> 4.Title自定义，将公钥粘贴到GitHub中Add an SSH key的key输入框，最后“Add Key”。

3. 配置账户

```cpp
$ git config --global user.name “your_username”  #设置用户名

$ git config --global user.email “your_registered_github_Email”  #设置邮箱地址(建议用注册giuhub的邮箱)
```
4. 测试ssh keys是否设置成功

```cpp
$ ssh -T git@github.com
The authenticity of host 'github.com (192.30.252.129)' can't be established.
RSA key fingerprint is 16:27:xx:xx:xx:xx:xx:4d:eb:df:a6:48.
Are you sure you want to continue connecting (yes/no)? yes #确认你是否继续联系，输入yes

Warning: Permanently added 'github.com,192.30.252.129' (RSA) to the list of known hosts.
Enter passphrase for key '/c/Users/xxxx_000/.ssh/id_rsa':  #生成ssh kye是密码为空则无此项，若设置有密码则有此项且，输入生成ssh key时设置的密码即可。

Hi xxx! You've successfully authenticated, but GitHub does not provide shell access. #出现词句话，说明设置成功。
```

## 下面就是将本地文件通过ssh push 到github
1. 创建目录、初始化、创建文件hello.md

```cpp
$ mkdir test
$ cd test

$ git init

$ echo "这是一次测试test ssh key" > hello.md
```
2. 提交本地

```cpp
$ git add .   #提交当前目录下所以文件
$ git commit -m "add hello.md"   #提交记录说明 
```
（上面出现warning， 需要重新执行）
3. 提交到github

```cpp
$ git remote add origin ‘粘贴复制test ssh key的ssh路径’（git remote add origin git@github.com:acelj/QT_FFMPEG.git）
$ git push -u origin master  // master 指的是分支
Enter passphrase for key '/c/Users/hgpin_000/.ssh/id_rsa':  #ssh key设置密码故此需要输入密码
```
## 提交本地的文件夹

```cpp
git init   // 更新文件内容了执行一下，不执行好像也可以
git add .  // 所在的目录，
git status  // 查看状态
git commit -m " 注释，提交的信息注释一下"
git remote add origin  xxx@xxx/test/git   // 根上面一眼项目的地址
git push origin master  // 不行的话，执行下面，先pull一下，在push
git pull origin master 
// ok

// 添加文件 或者修改
git add xxx
git commit -m "注释信息"   // 添加或者修改
git push origin master   // origin 是远端， master 指的是当前分支
```

## 添加的内容

```cpp
常用的命令（一套下来的）
git clone, pull, add + commit + push, revert

实际中遇到的案例： 
当本地的工作目录和远端的仓库文件不一致是，需要提交时候：
1. git pull origin master（feature）相应的分支
2. 这时候会提醒pull下来的文件和当前本地仓库中的文件不一致
3. 修改不一致的内容（直接在文件中删除不要的内容）（head表示当前仓库的指针，下面是当前仓库的内容；=====下面是远端仓库的内容，和哈希值）
4. 修改完后需要git commit xxx   （这里需要测试下）
5. 然后git push origin master   到远端


另外在git中还经常遇到的几个命令：
a. head命令 （HEAD^, HEAD^^,  表示距离当前提交的前面1个，前面2个），， 也可以这样写 HEAD~(n),后面的这种写法是可以写多级的，前面只能1-4级。
b.  git bisect 命令  
git bisect start A B   表示在的A版本和B版本之间锁定出现差错的版本，原理是二分查找。
c. rebase 命令：  合并几次提交的内容，这个经常用到。
d. git submoudle(需要第三方库) ： 在大项目管理中很有用的。
```

## 在项目中功能开发git大致操作流程

```cpp
git checkout feature    // 切换分支

git pull origin feature   // pull 最新的代码
...   // 开发过程
git rebase -i HEAD~(n)    // 合并之前的几次提交

// 经过上面两步后，往往本地仓库和远端仓库内容不一致，其他开发人员也在修改
git rebase develop     // 将develop最新代码pull 下来， 这个时候会有冲突，就需要解决冲突
git push origin feature    // 解决冲突后push 远端
git checkout develop     // 切换分支
git merge feature      // 合并代码

```


根据上面的内容，遇到复杂的事情可以
8. 参考git 中的分支管理办法，一步一步分给相关人员并发的进行开发。
9. 可以参考设计模式那样，将事情抽象出来，把主干流程去掉，构造数据模型。




## 错误提示
1. 提示： `fatal: remote origin already exists.`

```cpp
// 先删除远程git仓库
git remote rm origin
// 再添加远程git仓库
$ git remote add origin git@github.com:xxxx
```

2. commit 后 push 遇到 `failed to push some refs to`解决方法

```cpp
a. 原因，远程库根本地的代码文件不同步导致的。，这时只要将远程的库同步到本地即可：
git pull --rebase origin master
命令的意思是将远程的库合并到本地（可能有冲突，解决下）， --rebase 的作用是取消本地库中刚刚提交的commit ，并把他们接到更新后的本地仓库中

b 可以使用下面命令，将commit 代码撤回，然后git pull 远程仓库在进行。
git reset --soft HEAD^

git pull origin master  // 同步一下
```



## 删除远程仓库的文件或者文件夹

```cpp
git pull origin master(从分支中拉下来)
如果本地有和远程一样的可以不用执行上面一步

dir 可以看看有哪些文件夹

（cached不会把本地的flashview文件夹删除）
git rm -r --cached xxx(文件或者文件夹)（文件夹加上前面的-r）（这里删除的是xxx文件或者文件夹）
git commit -m '删除了xxx文件'
git push -u origin master (这里是master 分支提交)

```



## Git出现|MERGING解决

```cpp
git reset --hard head
```



## 合并分支出现refusing to merge unrelated histories 

> 在操作命令后面加上 --allow-unrelated-histories 



例如：

```bash
git merge dev --allow-unrelated-histories 
或者
git pull origin master --allow-unrelated-histories

// 合并的过程
1、 可以下pull下来的
2、 遇到编辑选项，可以在出来的内容加上 commit 注释，vim的命令， 写上一点东西
3、 在提交  git push origin master（你想提交的分支）
```



