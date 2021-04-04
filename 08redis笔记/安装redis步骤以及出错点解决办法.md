
直接下载redis

```cpp
wget http://download.redis.io/releases/redis-6.0.3.tar.gz

解压
tar -zxvf redis-6.0.3.tar.gz

cd redis-6.0.3
make  (可能出现错误1)


// 如果编译错误，解决后需要删除之前的编译文件
make distclean

安装
make install  // 默认安装在/usr/local/bin中


启动测试


```



出错点1： 出现redis.server.o 编译错误
> 1. 可能系统中没有安装gcc   
> 解决： sudo apt-get install gcc
> 2. gcc 版本过低 (需要升级版本， 5.0以上)
> 解决: 

```cpp
// 下载
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update 
sudo apt-get install gcc-7

// 修改配置默认选项
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 100
sudo update-alternatives --config gcc

//查看版本
gcc -v
```

出错点2： make install 时出现pkg-config: not found

> 直接 sudo apt-get install pkg-config  



参考：
https://blog.csdn.net/ZXF_1991/article/details/105370405
