 先说明一下， 在Windows中， 并不要求select函数的第一个参数总应该是fdmax + 1（在Windows下， 给定-1就行）， 那linux中为什么又是呢？

这就涉及到linux select第一个参数的函数： 待测试的描述集的总个数。 但要注意， 待测试的描述集总是从0， 1， 2， ...开始的。 所以， 假如你要检测的描述符为8， 9， 10， 那么系统实际也要监测0， 1， 2， 3， 4， 5， 6,  7，  此时真正待测试的描述符的个数为11个， 也就是max（8， 9， 10） + 1

 

有两点要注意：

1.  如果你要检测描述符8, 9, 10, 但是你把select的第一个参数定为8， 实际上只检测0到7， 所以select不会感知到8, 9, 10描述符的变化。

2.  如果你要检测描述符8, 9, 10, 且你把select的第一个参数定为11， 实际上会检测0-10， 但是， 如果你不把描述如0 set到描述符中， 那么select也不会感知到0描述符的变化。

 

 所以， select感知到描述符变化的必要条件是， 第一个参数要合理， 比如定义为fdmax+1,  且把需要检测的描述符set到描述集中。

其实， 依我的愚见， linux select中第一个参数的设计， 有点画蛇添足的感觉，Windows在这点上做得更好， 只需要关心添加进去的描述集即可。

 

有兴趣的同学， 可以基于我的以下代码来测试下：
```cpp
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/types.h>
 
int main()
{
    struct timeval tv;              // 超时时间
	tv.tv_sec = 10;
    tv.tv_usec = 500;               // 注意单位是微秒
 
    fd_set rdfds;
    FD_ZERO(&rdfds);                // 描述集初始化
    FD_SET(STDIN_FILENO, &rdfds);   // STDIN_FILENO是标准输入， 塞入描述集
	
    int iRet = select(STDIN_FILENO + 1, &rdfds, NULL, NULL, &tv);  // 注意注意
    if(iRet < 0)
	{
		printf("selcet error, iRet %d\n", iRet);
		return -1;
	}
 
   	if(0 == iRet)
	{
		printf("timeout \n");
	}
 
	printf("iRet = %d \n", iRet); 
	
	return 0;
}
```
  可以改动上述代码， 进行调测。


> 另外， poll和epoll并不需要上述的+1， 完全不是一个东东。
