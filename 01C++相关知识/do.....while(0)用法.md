在c中，我们遇到的有三种循环语句：for, while和do....while，最近在看一些别人写的代码时候，遇到了do...while(0),当时十分不理解，为什么要这样子做。

下面说一下为什么要用到do.....while(0)
1. 消除代码的冗余
2. 避免使用goto语句

解释1：
我们在写程序的时候，在一个函数中如果遇到需要判断情况的，有时动不动需要判断几个参数，或者我们的代码像下面这样子。

```cpp
bool Execute()
{
   // 分配资源
   int *p = new int;
   bool bOk(true);

   // 执行并进行错误处理
   bOk = func1();
   if(!bOk) 
   {
      delete p;   
      p = NULL;
      return false;
   }

   bOk = func2();
   if(!bOk) 
   {
      delete p;   
      p = NULL;
      return false;
   }

   bOk = func3();
   if(!bOk) 
   {
      delete p;   
      p = NULL;
      return false;
   }
   
   // ..........

   // 执行成功，释放资源并返回
    delete p;   
    p = NULL;
    return true;
}
```
这个例子最大的问题就是**代码十分的冗余**，而且**不利于后续的扩展**，每一次工程师加一个情况就需要加几个判断情况，这时候有人可能想到goto语句；程序就变成下面；

```cpp
bool Execute()
{
   // 分配资源
   int *p = new int;
   bool bOk(true);

   // 执行并进行错误处理
   bOk = func1();
   if(!bOk) goto label;

   bOk = func2();
   if(!bOk) goto label;

   bOk = func3();
   if(!bOk) goto label;

   // ..........

   // 执行成功，释放资源并返回
    delete p;   
    p = NULL;
    return true;

label:
    delete p;   
    p = NULL;
    return false;
}
```

上面的代码是消除了冗余，但是引入了goto语句，当在最开始学习的时候，不管是书上还是老师都是不推荐使用goto语句的，唯一的原因就是：**它太强了，一般人驾驭不了**。就是太灵活了，**时间一长，自己都可能云里雾里**，更不谈给其他工程师修改这个代码。于是乎，就出现下面这个版本的代码。

```cpp
bool Execute()
{
   // 分配资源
   int *p = new int;

   bool bOk(true);
   do
   {
      // 执行并进行错误处理
      bOk = func1();
      if(!bOk) break;

      bOk = func2();
      if(!bOk) break;

      bOk = func3();
      if(!bOk) break;

      // ..........

   }while(0);

    // 释放资源
    delete p;   
    p = NULL;
    return bOk;
}
```
看到这里，我清楚了do...while(0)的用法；

查阅资料，我发现很多宏定义是使用了这样的代码的，比如说：

```cpp
#define AFXASSUME(cond)       do { bool __afx_condVal=!!(cond); ASSERT(__afx_condVal); __analysis_assume(__afx_condVal); } while(0)
```
而且我看到某个老师写代码也是这样，我当时就想既然就循环一次，为什么加上一层衣服，这部多次一举嘛
现在看，如果不写这个，程序很可能会报错，由于写程序的习惯，语句后面加上分号，但是在宏中编译器就认为这个语句结束了，就会出错。

