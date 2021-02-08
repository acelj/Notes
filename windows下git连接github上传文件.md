 ﻿1. 打开git  bash客户端
﻿2. 使用git bash 生成ssh key

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
git push origin master 


```

## 错误提示
1. 提示： `fatal: remote origin already exists.`

```cpp
// 先删除远程git仓库
git remote rm origin
// 再添加远程git仓库
$ git remote add origin git@github.com:xxxx
```

2. `failed to push some refs to`解决方法

```cpp
git pull origin master  // 同步一下
```



