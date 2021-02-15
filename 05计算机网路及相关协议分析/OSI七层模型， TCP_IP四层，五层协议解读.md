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

