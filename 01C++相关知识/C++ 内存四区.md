﻿## 内存四区
首先在C++中，我这里是认同是四个区域的，网上另一派是5个区域的。
四区： 代码区、全局区、堆区、栈区。
网上五区：代码区、全局区、常量区、堆区、栈区。（就是将全局区分开成了两个，少记一个不行嘛）
### 代码区

存放 CPU执行的机器指令。通常代码区是可共享的（即另外的执行程序可以调用它），使其可共享的目的是对于频繁被执行的程序，只需要在内存中有一份代码即可。代码区通常是只读的，使其只读的原因是防止程序意外地修改了它的指令。另外，代码区还规划了局部变量的相关信息。
> 总结：你所写的**所有代码**都会放入到**代码区中**，代码区的特点是**共享和只读**。

### 全局区
全局区中**主要存放的数据**有：全局变量、静态变量、常量（如字符串常量）
全局区的叫法有很多：全局区、静态区、数据区、全局静态区、静态全局区
这部分可以细分为data区和bss区
1. data区
data区里主要存放的是**已经初始化**的全局变量、静态变量和常量
2. bss区
bss区主要存放的是**未初始化**的全局变量、静态变量，这些未初始化的数据在程序执行前会自动**被系统初始化为0或者NULL**
3. 常量区
常量区是全局区中划分的一个小区域，里面**存放的是常量**，如const修饰的全局变量、字符串常量等

> 总结：全局区存放的是**全局变量、静态变量和常量**


在程序**运行后**由产生了两个区域，**栈区**和**堆区**
## 栈区
栈是一种先进后出的内存结构，**由编译器自动分配释放**，存放函数的**参数值、返回值、局部变量**等。在程序运行过程中实时加载和释放，因此，局部变量的生存周期为申请到释放该段栈空间。

## 堆区
堆是一个大容器，它的**容量**要远远**大于栈**，但没有栈那样先进后出的顺序。**用于动态内存分配**。**堆**在内存中位于**BSS区和栈区之间**。一般由**程序员分配和释放**，若程序员不释放，程序结束时由操作系统回收（泄露）。

