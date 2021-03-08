作为网络协议的老大哥，掌握TCP是必不可少的，所以我们今天来挖掘TCP的包含内容。

## 建立连接的三次握手
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210305204454865.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
说明： 

> 客户端是通过调用connect函数 发起的**主动打开**，连接的服务器；服务端必须准备接收外来的连接，是通过调用socket，bind，listen这三个函数来完成的，被称为**被动打开**。

1. 客户端主动建立连接后，需要发送一个SYN(同步)分节，用来告诉服务器将在（待建立的）连接中发送的数据的初始序列号。通过SYN分节是不携带数据的
2. 服务器端收到客户端发送的SYN信号后，需要向客户端发送一个确认信号，同时自己也得发送一个SYN分节，此时就像上面那样是SYN(同步)， ACK(确认)
3. 最后一步是客户端需要确认服务器的SYN。
（上面图中的序号解释： 客户端的初始序列号是J， 服务器初始序列号是K， ACK 确认号是发送这个ACK的一端所期待的下一个序列号，SYN是占据一个字节序列号空间），所以每一个SYN的ACK中的确认号就是该SYN初始序列号 ＋１

上面就是TCP建立连接时的三次握手。


## 终止连接的四次挥手

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021030521120525.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

说明：
1. 某个应用进程首先调用close， 这个称为该端执行**主动关闭**（active close），于是该端发送一个FIN分节，表示的数据发送完毕。

2. 接收到FIN的对端执行**被动关闭**（passive close），这个FIN由TCP确认。它的接收也作为一个文件结束符传递给接收端应用进程（**放在已排队等候应用进程接收的任何其他数据之后**）(**此过程就是半关闭状态**)，因为FIN的接收意味这接收端应用进程在相应连接上再无额外数据可接收。
3. **一段时间后**，接收到这个文件结束符的应用进程将**调用close关闭它的套接字**。这会导致它的TCP**也会发送一个FIN**。
4. 接收这个最终FIN的原发送端TCP（即执行主动关闭的那一端）确认这个FIN.
> 四次挥手为什么不能做成3次，因为服务端可能还有一些事情没有处理完，需要等事情处理完后才能结束。


类似SYN, 一个FIN也占据1个字节的序列空间，因此每个FIN的ACK确认号就是FIN的序列号+ 1.

> ps :  无论是客户端还是服务器端都可以执行主动关闭的，不过通常情况是客户端执行主动关闭。 （**但是HTTP1.0是由服务器执行主动关闭**）

## 下面是一张经典的TCP11种状态转换图 ：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2021030521262087.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210305212557253.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

## 观察完整的情况
下面有TCP的三次握手和数据的发送以及TCP的四次挥手三个过程。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210305212751472.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
> 可以通过netstat 命令查看， 在哪一个状态

## 观察TCP头的格式：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210305204214464.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
中间的是一些状态位:
> SYN是发起一个连接，ACK是回复，RST是重新连接，FIN是结束连接等

从TCP 的格式来看主要是影该关注下面五个问题：
1. 顺序问题
2. 丢包问题
3. 连接维护
4. 流量控制
5. 拥塞控制

区别： 流量控制和拥塞控制一个是针对另一端的一个是针对网路的。

通过上面的三次握手和四次挥手主要解决的是连接维护问题。

那剩下的四个问题怎样解决的呢？
首先**需要明确**发送端和接收端的里面数据**缓存的数据结构是什么样的**？这也是TCP实现可靠的必要原因。

TCP为了记录所有发送和接收的包， TCP需要将发送端和接收端分别都用缓存来保存这些记录。
1. **发送端的缓存里是按照包的ID一个个排列，根据处理的情况分成四个部分。**

> 第一部分：**发送了并且已经确认**的。这部分就是你交代下属的，并且也做完了的，应该划掉的。
> 
> 第二部分：**发送了并且尚未确认的**。这部分是你交代下属的，但是还没做完的，需要等待做完的回复之后，才能划掉。
> 
> 第三部分：**没有发送，但是已经等待发送的**。这部分是你还没有交代给下属，但是马上就要交代的。
> 
> 第四部分：**没有发送，并且暂时还不会发送的**。这部分是你还没有交代给下属，而且暂时还不会交代给下属的。
ps： 第二部分 + 第三部分 就是TCP 中的滑动窗口的大小。

综上，发送端的数据模式就是下面的模式：
![在这里插入图片描述](https://img-blog.csdnimg.cn/202103082056578.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

 - LastByteAcked：第一部分和第二部分的分界线

- LastByteSent：第二部分和第三部分的分界线

- LastByteAcked + AdvertisedWindow（滑动窗口的大小）：第三部分和第四部分的分界线
2. **接收端里面的缓存应该是下面的样子**

> 第一部分：接受并且确认过的。也就是我领导交代给我，并且我做完的。
> 
> 第二部分：还没接收，但是马上就能接收的。也即是我自己的能够接受的最大工作量。
> 
> 第三部分：还没接收，也没法接收的。也即超过工作量的部分，实在做不完。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210308210655209.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

 - MaxRcvBuffer：最大缓存的量；

- LastByteRead之后是已经接收了，但是还没被应用层读取的；

- NextByteExpected是第一部分和第二部分的分界线。
这里的滑动窗口应该是 AdvertisedWindow=MaxRcvBuffer-((NextByteExpected-1)-LastByteRead)。

**第二部分和第三部分的分界线是**： NextByteExpected加AdvertisedWindow就是第二部分和第三部分的分界线，其实也就是LastByteRead加上MaxRcvBuffer。

在第二部分里面的，由于受到的包可能不是顺序的，会出现空挡，只有和第一部分连续的，可以马上进行回复，中间空着的部分需要等待，哪怕后面的已经来了。

按照上面的规则，下面进行TCP的顺序问题和丢包问题的讨论
## 顺序问题和丢包问题
还是刚才的图，在发送端来看，1、2、3已经发送并确认；4、5、6、7、8、9都是发送了还没确认；10、11、12是还没发出的；13、14、15是接收方没有空间，不准备发的。

在接收端来看，1、2、3、4、5是已经完成ACK，但是没读取的；6、7是等待接收的；8、9是已经接收，但是没有ACK的。


