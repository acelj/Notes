## OSI 简介
OSI(open system interconnect) 开放式系统互联。就是国际上一个组织定义网络互联的一个标准七层框架（物理层、数据链路层、网络层、传输层、**会话层、表示层、应用层**）。

| 层次 | 单位 |
|:--:| --:|
|物理层：| 数据单位称为比特bit.|
|数据链路层：|数据单位称为帧frame.
|网络层： |数据单位称为数据包packet.
|传输层：|TCP的数据单元称为段segments. UDP的数据单元成为数据报datagrams.
|会话层及以上的层次中：| 数据单位不在另外命名，均成为报文。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210215222213282.png?x-oss-process=image,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210215222836737.gif#pic_center)
OSI 七层模型通过七个层次化的结构模型使不同的系统不同的网络之间实现可靠的通讯，因此其最主要的功能就是帮助不同类型的主机实现数据传输 。

一个设备工作在哪一层，关键看它工作时**利用哪一层的数据头部信息**。网桥工作时，是以MAC头部来决定转发端口的，因此显然它是数据链路层的设备。
具体说:
物理层：网卡，网线，集线器，中继器，调制解调器

数据链路层：网桥，交换机

网络层：路由器

网关工作在第四层传输层及其以上

集线器是物理层设备,采用广播的形式来传输信息。

**TCP/IP 四层** ： 数据链路层、网络层、传输层、应用层。
**五层协议**： 物理层、数据链路层、网络层、传输层、应用层。

## OSI七层和TCP/IP的区别

 1. TCP/IP是一个协议簇；而OSI（开放系统互联）则是一个模型，且TCP/IP的开发时间在OSI之前。
2. TCP/IP是由一些交互性的模块做成的分层次的协议，其中每个模块提供特定的功能；OSi则指定了哪个功能是属于哪一层的。
3. TCP/IP是五层结构，而OSI是七层结构。OSI的最高三层在TCP中用应用层表示。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210215223206948.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
ps: 在有些资料中ARP, RARP 分层的不一样；
在OSI模型中ARP属于数据链路层， 在TCP/IP模型中，ARP属于网络层。

1）ARP 分层的位置是TCP/IP 的网络层
2）ARP报文是由以太网进行封装传输的，没有封装进IP包。
3）之所以不把它放在数据链路层，是因为它并不具备数据链路层的功能。它的作用是为数据链路层提供接收方的帧地地址。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210402103151925.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

说一下TCP/IP 每一层的作用是做什么的
（数据链层、网络层、传输层、应用层）
1. 数据链路层：数据链路层是负责接收IP数据报并通过网络发送之，或者从网络上接收物理帧，交给IP层。传输有地址的帧以及错误检测功能。
>1.  流量控制，有基于反馈的流控制盒基于速率的流控制。
>2. 错误检测和纠正。
>在这一层，数据的单位是帧（frame）

2. 网络层：负责相邻计算机之间的通信，功能包括三方面。
>1. 处理来自传输层的**分组发送请求**，收到请求后，将分组装入IP数据报，填充报头，选择去往信宿机的路径，然后将数据报发往适当的网络接口。
>2. **处理输入数据报**：首先检查其合法性，然后进行寻径--假如该数据报已到达信宿机，则去掉报头，将剩下部分交给适当的传输协议；假如该数据报尚未到达信宿，则转发该数据报。
>3. **处理路径、流控、拥塞等问题**。(其中拥塞控制是通过ICMP传递的） 网络层包括：IP(Internet Protocol)协议、ICMP(Internet Control Message Protocol) 控制报文协议、ARP(Address Resolution Protocol)地址转换协议、RARP(Reverse ARP)反向地址转换协议。 IP是网络层的核心，通过路由选择将下一跳IP封装后交给接口层。IP数据报是无连接服务。 ICMP是网络层的补充，可以回送报文。用来检测网络是否通畅。 Ping命令就是发送ICMP的echo包，通过回送的echo relay进行网络测试。 ARP是正向地址解析协议，通过已知的IP，寻找对应主机的MAC地址。 RARP是反向地址解析协议，通过MAC地址确定IP地址。比如无盘工作站和DHCP服务。在这一层，**数据的单位 称 数据包** （packet）

3. 传输层
网络层负责点到点的传输（这里的点指的是主机或者路由器），而传输层负责端到端的传输（这里的端指的是源主机和目的主机）。
> 1.  格式化信息流
> 2. 提供可靠的传输。为实现后者，传输层协议规定接收端必须发回确认，并且假如分组丢失，必须重新发送。
> 传输层的协议主要是： 传输控制协议TCP(transmission Control Protocol)和用户数据报协议UDP(User datagram protocol), 在这一层，数据的单位称为段。

4. 应用层
>  向用户**提供一组常用的应用程序**，比如电子邮件、文件传输访问、远程登录等。远程登录TELNET使用TELNET协议提供在网络其它主机上注册的接口。TELNET会话提供了基于字符的虚拟终端。文件传输访问FTP使用FTP协议来提供网络内机器间的文件拷贝功能。 **应用层一般是面向用户的服务**。如FTP、TELNET、DNS、SMTP、POP3。 FTP(File Transmision Protocol)是文件传输协议，一般上传下载用FTP服务，数据端口是20H，控制端口是21H。 Telnet服务是用户远程登录服务，使用23H端口，使用明码传送，保密性差、简单方便。 DNS(Domain Name Service)是域名解析服务，提供域名到IP地址之间的转换。 SMTP(Simple Mail Transfer Protocol)是简单邮件传输协议，用来控制信件的发送、中转。 POP3(Post Office Protocol 3)是邮局协议第3版本，用于接收邮件。 
