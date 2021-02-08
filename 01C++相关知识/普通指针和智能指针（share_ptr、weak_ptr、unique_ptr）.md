@[TOC]
## new、delete初识（new、delete）
1. new 、delete 申请的内存是在堆里面，和c语言中的malloc、free一样。是**直接内存管理**方式。

```cpp
class A
{
	// 称为间接内存管理
	int i, j;   // 临时对象
	static int j = 10; // 局部静态对象
}

int* ptr = new int;   // 初值未定义
string *ptr1 = new string;  //空字符串，是直接调用了string默认构造函数
int *ptr2 = new int(10);  // 给一个int 的动态对象初值
string* ptr3 = new string(5, 'a'); //  生成一个字符串，字符串内容是5个‘a’
vector<int> * ptr4 = new vector<int>{1,2,3,4,5};  // 一个容器对象，里面有5个元素

值初始化
int* ptr = new int();   // 值初始化方式，ptr被初始化为0  
string* ptr = new string(); // 是空字符串，和不加（）一样

```
2. 在C++中auto 可以和new配合使用

```cpp
string* ptr = new string(5， 'v');
auto ptr1 = new auto(ptr); // ptr1 = string** 这里是指针的指针， 指向的是ptr的地址
string** ptr2 = new string*(ptr);   // 上面的等同于这个
delete ptr;   // 这里只需要删除一个对象就可以了

```
3. const 对象也可以动态分配，但是分配后是常量不能更改（拓展就行，尽量不使用）
~~*ptr = 200;    // 这里是错误赋值方式~~ 
```cpp
const int* ptr = new const int(100);
*ptr = 200;    // 这里是错误赋值方式
```

4. new和delete 说明
	1. 必须成对出现，否则内存泄露，delete的作用是回收用new分配的内存（释放内存），不是new出来的内存是不能用delete删除滴~
	2. delete一块内存，只能delete一次，不能delete多次。**delete后**，**这块内存就不能用了**，空指针可以多次删除但是没有实际意义。

```cpp
int int= 12；
int* ptr = &i;
delete ptr; // 错误，因为ptr不是new的新内存，不能delete

=======
int* p = new int();
int* p2 = p;
delete p2;   // 正确
delete p;    // 出现异常，因为p和p2指向的是同一快内存 
```


5. new 和delete 的总结：
	1. new出来的一定要delete，否则内存泄露，时间一长，导致系统资源紧张，运行崩溃。
	2. delete后的内存不能使用，否则异常。
	3. 同一块内存释放两次的问题，会报异常。
```cpp
int* p = new int(100);
*p = 200;
delete p;
*p = 300;   // 这是错误的
p = nullptr;  // 这是好习惯
```
6. 由于上面的内存管理用的时候需要非常小心，C++11就出现了智能指针。

## new、delete 探秘
1. sizeof 也是**关键字和运算符**，不是函数； malloc、free是函数（主要用于c语言中）。
2. new、delete**是关键字和运算符**，不是函数。（比malloc，free干的事多）[https://blog.csdn.net/hihozoo/article/details/51441521](https://blog.csdn.net/hihozoo/article/details/51441521)

```cpp
class A
{
public: 
	A(){};
	~A(){};
};

A* p = new A();   // 构造函数被调用
delete p;   // 析构函数被调用
// new、delete 具备对堆上分配内存进行初始化、释放的能力，而malloc、free是不具备的。

```
3. operator new() he operator delete函数

	```cpp
	new 是干了两件事：
	1. 分配内存（通过operator new()来分配函数）
	void* ptr = operator new(100);  //分配100字节，不过一般没人这么做
	2. 调用构造函数来初始化内存
	delete 也干了两件事
	1. 调用析构函数
	2. 释放内存（通过operator delete()释放内存）
	```
4. new 可以记录分配内存的大小供delete 使用
	
	```cpp
	int* p = new int;   // 4字节
	delete p;  // 删除的时候，编译器知道是回收的4字节，因为new中有记录，
				//记录申请的内存大小
	```
	
	
	```cpp
	class A 
	{
	public: 
		A(){}
		~A(){}
	};
	
	int* p = new int(100);  // 分配的是int 4字节， 给int = 100；
	int* p = new int[2];   // 给的是8字节，因为int 的内置类型，4 * 2 =8
	
	A a;
	int len = sizeof(a);  // 这是1字节，类对象肯定有地址，就至少占用1字节空间
	
	A* pa = new A();  // 不删除， 泄露1字节
	A* pa2 = new A[2]();  // 泄露6字节， 多的4字节是干嘛的
	int* p = new int[2];  // 泄露的是8字节，没有多出4字节
	```

5. new[] 应该用delete[] 来进行释放，在内置类型中直接delete是可以的，但是在自定义类型中(有自定义析构函数)不用delete[] 就会出现异常。
	原因： 内置类型（比如： int， float）不需要调用析构函数，所以new[] 时候系统没有分配4字节，对于上面的这些类型，`delete p；`和`delete[] p;` 是一样的；
		如果一个**自定义对象**（**有析构函数**）使用`new[]` 来分配对象，那么系统会多出4自己来记录需要析构的次数； 如果自定义的对象中没有析构函数，那么跟上面内置类型一样，`delete p；`和`delete[] p;` 是可以的。

	```cpp
	/// 用上面的代码，解决疑问
	A* pa = new A();  // 不删除， 泄露1字节
	
	int* p = new int[2];  // 泄露的是8字节，没有多出4字节
	// delete p;    // 没有用[]， 这里没有发生泄露
	delete[] p;  // 正确用法
	
	A* pa2 = new A[2]();  // 泄露6字节， 多的4字节是干嘛的
	//delete pa2;		// 这里会出现异常
	delete[] pa2;  // 正确,
	```

## 智能指针初识
1. 智能指针就是对“裸指针”（直接new 出来的返回的指针）的包装，不用担心申请的内存忘记释放。
2. 现阶段C++标准库有四种智能指针std::
		a. auto_ptr : (C++98中就有，现在完全被unique_ptr代替)
		b. shared_ptr（C++11）：共享式指针，多个指针指向同一个对象，最后一个指针被销毁时，这个对象才会被销毁。
		c. weak_ptr（C++11）：是辅助shared_ptr指针工作的
		d. unique_ptr（C++11）： 独占式指针，只有一个指针能后指向该对象。当然该对象的所有权还是可以移交出去的。

## shared_ptr指针
1. 共享所有权，不是被一个shared_ptr拥有，而是被多个shared_ptr之间相互协作；shared_ptr有额外开销。
2. **工作原理:**  引用计数，每个shared_ptr的拷贝都指向相同的内存，所以，只有最后一个指向该内存对象的shared_ptr指针不需要在指向该对象时，这个shared_ptr才会去析构所指向的对象。
3. 在下面的情况，shared_ptr会释放对象
		a. **这个shared_ptr被析构的时候；**
		b. **这个shared_ptr指向其他对象时候；**
4. 格式： shared_ptr<指向的类型> 智能指针名
5.  非常不推荐裸指针和智能指针交叉用。

```cpp
shared_ptr<int> p1;  // 指向int 的p1智能指针，为nullptr指针
shared_ptr<int> p(new int(100));   // p指向一个值为100的int型数据
shared_ptr<int> p2 = new int(10); // 不能用这种方法，智能指针是explicit，
								//不可以进行隐式类型转换。必须用直接初始化形式。

shared_ptr<int> makes(int val)
{
	// return new int(val);   // 不行， 无法把new 得到的int* 转换成shared_ptr
	return shared_ptr<int>(new int(val));  // 可以，显示的用int* 创建shared_ptr<int>
}

// 下面是正确的，但是非常不推荐使用，
int* p = new int;		// 裸指针
shared_ptr<int> p1(p);
								
```
6. make_share函数， 标准库里面的函数，安全高效的分配和使用shared_ptr。 std::make_shared()

```cpp
shared_ptr<int> p = std::make_shared<int>(100);   // 有点类似 int* p = new int(100);shared_ptr 指向一个值为100的整型内存
shared_ptr<string> p2 = std::make_shared<string>(5, 'a');  // 5个字符a生成的字符串
shared_ptr<int> p3 = std::make_shared<int>();   // p3指向的int，int里保存的是0（值初始化）
p3 = std::make_shared<int>(100); // p3指向一个新的int，int里保存的是100，p3首先释放刚才指向0的内存，然后指向100的内存
auto p4 = std::make_shared<string>(5, 'a');  // 可以使用auto
```

## shared_ptr 常用操作
1. shared_ptr 采用的是**引用次数增加和减少**来实现的智能控制的。每个shared_ptr的拷贝都指向相同的内存，所以，只有最后一个指向该内存对象的shared_ptr指针不需要在指向该对象时，这个shared_ptr才会去析构所指向的对象。

```cpp
auto p = make_shared<int>(100);  // 目前p 所指向的对象只有p一个引用者
auto p1(p); // 智能指针定义时的初始化，p1和p指向了相同的对象，此对象目前有两个引用者
```

2. 引用次数增加的几种方式
		a.  像上面这种情况直接用智能指针定义初始化；
		b. 把智能指针当作实参往函数里面传递；
		c. 作为函数的返回值（没有变量接临时的指针，引用次数会在生命周期结束的时候，引用次数-1）

```cpp
void mufun(shared_ptr<int> tmp) // 如果参数是引用，则智能指针的引用基数不会增加1
{
	return 
}

shared_ptr<int> myfun2(shared_ptr<int> &tmp)  // 返回值会增加引用次数
{
	return tmp;	
}

auto p = make_shared<int>(100);
auto p2 = myfun2(p);   // 会增加引用次数
myfun2(p);   // 没有变量接临时指针，则生命周期到了，引用次数会减少1
```

3. 引用次数减少的几种方式
		a. 给shared_ptr赋予新值，让该shared_ptr指向一个新对象
		b. 局部的shared_ptr 离开 其作用域（上面的函数调用结束后，没有变量接，就会释放）
		c. 当一个shared_ptr 引用计数从1变成0， 则它会自动释放自己所管理（指向）的对象
		d.
		

```cpp
auto p = make_shared<int>(1);
auto p2 = myfun2(p);
auto p3 = myfun2(p2);	// p,p2,p3 引用次数为3
auto p3 = make_shared<int>(3);  // p3指向新对象，次数为1，p，p2引用次数为2
auto p2 = make_shared<int>(4);  // p2指向新对象，次数为1，p引用次数为1
auto p = make_shared<int>(5);  //p指向新对象，计数为1，p指向原内存被释放
===
auto p = make_shared<int>(1);
auto p2 = make_shared<int>(1);
p = p2;  // 给p赋值会让p 指向p2所指向的对象，该对象引用计数变成2，而原来p所指向的对象
		// 引用计数会从1变成0，从而释放

```


4. shared_ptr 指针常用操作
			a. use_count() : 返回多少个智能指针指向某个对象，主要用于调试。
			b. unique() : 是否该智能指针独占某个指向对象，也就是只有一个智能指针指向对象，就返回true（`p.use_count() == 1`）。
			c. reset() : 恢复（复位、重置意思）：1.**不带参数**：若p 是**唯一指向**该对象的指针，那么释放p所指向的对象，并将p置空；若p**不是唯一指向**该对象的指针，那么不释放p所指向的对象，但指向该对象的引用计数减少1，同时将p置空。2. **带参数**（**一般是new出来的指针**）：若p 是**唯一指向**该对象的指针，则释放p所指向的对象，让p指向新对象； 若p**不是唯一指向**该对象的指针，则不释放p指向的对象，但指向该对象的引用计数减少1，同时让p指向新对象。
			d. * 解引用： 获得p指向的对象
			e.  get() : p.get() 返回p中保存的裸指针，小心使用，如果智能指针释放了所指向的对象， 那么这个返回的裸指针就无效了 （**在一些需要裸指针参数的函数用的多**）
			f. swap(): 交换两个智能指针所指向的对象。`std::swap(p1, p2)`, 或者`p1.swap(p2);`
			g. = nullptr :  引用减1，置空。
			h. 可以作为判断条件： 跟普通指针一样。
			i. **指定删除器以及数组问题**： 1. 指定删除器（自定义函数）； 2. 可以用`default_delete<A[]>()` 是标准库中的模版库 3. 在<> 中加上[] 就行了。 （注意： 两个shared_ptr指定了不同删除器，但是指向的对象类型相同，那么这两个shared_ptr属于同一类型，可以放到同一vector容器中）
		

```cpp
shared_ptr<int> p(new int(100));
int cnt = p.use_count();   //1 
shared_ptr<int> p2(p);
cnt = p.use_count();  // 2

p.unique() == 1;
===
shared_ptr<int> p(new int(100));
auto p2(p);
p.reset();
===
shared_ptr<int> p(new int(100));
auto p2(p);   // p2引用次数会变成2
p.reset(new int(1)); // 释放原内存，指向新内存
===
shared_ptr<int> p(new int(100));
cout << *p << endl; // 100
===

shared_ptr<int> p(new int(100));
int* p2 = p.get();
*p2    // 100;
// delete p2;    // 千万不能delete, 这里就会错误

===
// 删除器
// 自定义的删除器， 删除整型指针用的，当引用计数为0，就会自动调用自定义的删除器
void deleteptr(int* p)  
{
	// 写一些日志 
	delete p; 
}
shared_ptr<int> p(new int(100));
shared_ptr<int> p2(p);
p2.reset();
p.reset();   // 这里之后应该调用删除器

// 还可以用lambda 函数
shared_ptr<int> pi(new int(100), [](int* p){ 
		delete p;
});

// 有些情况，默认的删除器处理不了
shared_ptr<int> pi(new int[10], [](int* p){ 
		delete[] p;
});

// 因为系统默认的是delete p， 而不是delete[] p;, 这时我们需要的在删除器中写delete[]
shared_ptr<int> pA(new A[10], [](int* p){ 
		delete[] p;   
});

shared_ptr<int> pA(new A[10],  std::default_delete<A[]>());


shared_ptr<int[]> pA(new int[10]);   // 在<> 中加上[] 就行了
shared_ptr<A[]> pA(new A[10]); 

// 写个函数模版来封装shared_ptr数组
template<typename T>
shared_ptr<T> make_shared_array(size_t size)
{
	return shared_ptr<T>(new T[size], default_delete<T[]>());
}

shared_ptr<int> p = make_shared_array<int>(5);
shared_ptr<A> p = make_shared_array<A>(12);
```
## weak_ptr 指针
概述： weak_ptr 是辅助shared_ptr进行工作的，这里是弱引用，share_ptr是强引用。weak_ptr 也是类模版，是智能指针，这个指针指向一个由share_ptr 管理的对象，但是weak_ptr 这种指针**不控制所指向的对象生命周期**。
（就是waek_ptr绑定到share_ptr上并不会改变share_ptr的引用计数，也可以说weak_ptr的构造和析构不会增加和减少所指向对象的引用计数）
当share_ptr 需要释放所指定的对象的时候，不管是否有weak_ptr 指向该对象，控制不了所指向对象的生存期。

作用： weak_ptr可以理解成监视share_ptr（强引用）的生命周期的。是一种对share_ptr的扩充。

1. weak_ptr 的创建：创建一个weak_ptr，一般用一个share_ptr来初始化

```cpp
auto p = make_shared<int>(100);  // share_ptr
weak_ptr<int> piw(p);   // piw 弱共享p，p引用计数不改变，但弱引用计数会从0 -> 1,
					// (只有强引用计数才能控制对象的生命周期)

```

2. lock() :  功能就是检查weak_ptr 所指向的对象是否存在，如果存在，那么这个lock他就能返回一个指向该对象的share_ptr（指向对象的强引用就会+ 1），如果不存在，lock就会返回一个空的share_ptr；

```cpp
auto pi2 = piw.lock();
if(pi2 != nullptr)
{
	*pi = 12;
}
else
{
	cout << "lock 失败 ！" << endl;
}
// 可以看出，weak_ptr 能够判断所指向的对象是否存在
```
3. weak_ptr 的常用操作

> 1. use_count()  : 获取该弱指针共享对象的其他share_ptr 的数量，或者说获得当前所观测资源的强引用计数。
> 2. expired() :  是否过期的意思。弱指针的use_count() 为0， （表示该弱指针所指向的对象已经不存在了），则返回true。（就是这个函数可以判断所观测的资源是否已经被释放）
> 3. reset() : 将该弱引用指针设置为空，不影响指向该对象的强引用数量，但指向该对象的弱引用数量会减少。
> 4 .lock() : 上面已经说了， **下面有个实际的例子**。

```cpp
auto p = make_shared<int>(100);
auto p2(p);  // 是一个shared_ptr
weak_ptr<int> piw(pi);  
int isc = piw.use_count();
cout << isc << endl;  // 2
=====
p.reset();   // 释放一个强引用
p2.reset();  
if(piw.expired())
{
	cout << "对象已经过期" << endl;
}
====
piw.rese();
=====
auto p1 = make_shared<int>(10);
weak_ptr<int> pw;
pw = p1;    // 可以用shared_ptr给weak_ptr赋值
if(!pw.expired())
{
	auto p2 = pw.lock();  // 返回一个shared_ptr，并且此时强引用计数为2，p2
	if(p2 != nullptr)
	{
		// 做一些操作
		int test；
		test = 1；
		// 离开这个范围， 强引用计数会恢复为1
	}
}
else
{
	// 已经过期
	int test；
	test= 1；
}
// 走到这里强引用计数为1
```
4. 尺寸问题

> weak_ptr 的尺寸和shared_ptr尺寸一样大，是裸指针的2倍。
> **裸指针在32位机器上是4字节**， 64位机器上是8字节
> **weak_ptr和shared_ptr 在32位机器上占8字节** ， 两个裸指针大小
> 第一个裸指针   指向的是这个智能指针所指向的对象
> 第二个裸指针   指向一个很大的数据结构（控制块），这个控制块里有
> 				1. 所指对象的强引用计数
> 2.所指对象的弱引用计数
> 3. 其他数据，比如自定义的删除器的指针等等。

```cpp
weak_ptr<int> pw;
int *p;
int len1= sizeof(p); // 4, 是裸指针
int len2= sizeof(pw); // 8 两个裸指针
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210131222756491.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

## unique_ptr 指针

> 概述： 独占式，同一时刻，只能有一个unique_ptr指针指向这个对象（这块内存）
> 当这个unique_ptr被销毁的时候，它所指向的对象也被销毁。
> 格式： unique_ptr<指向对象类型> 智能指针变量名；

> 1. 初始化（unique_ptr和new 使用）
> 2. make_unique函数： C++11中没有， C++14才有的，不支持指定的删除器语法，如果不使用删除器，建议优先选择使用，更高的性能。

```cpp
unique_ptr<int> pi;
if(pi == nullptr)
{
	cout << "pi 是空指针" << endl;
}
unique_ptr<int> p2(new int(10));   // 此时p2 指向一个值为10的int对象

=====
unique_ptr<int> p1 = make_unique_ptr<int>(100);
auto p2 = make_unique_ptr<int>(200);
unique_ptr<int> p3(new int(300));   // 前边不能简写成auto

```
unique_ptr 的常规操作
> 1. 不支持拷贝和赋值操作
> 2. 移动语义
> 3. release(): 放弃对指针的控制权，（切断了智能指针和其所质量的对象之间的联系）
> 返回的裸指针，将该智能指针置空，返回的这个裸指针我们可以手工delete释放，也可以初始化另外一个智能指针，或者给另一个智能指针赋值。
> 4. reset(): **不带参数情况**，释放智能指针所指向的对象，并将智能指针置空。
> reset() : **带参数的情况**, 释放智能指针所指向的对象，并让该智能指针指向新对象。
> 5.  = nullptr  : 释放智能指针所指向的对象，并将智能指针置空。
> 6. 指向一个数组： 需要加上[]
> 7. get() : 返回智能指针中保存的裸指针。(**考虑有些函数的参数需要裸指针**)
> 8. * ：解引用： 获取该智能指针指向的对象，可以直接操作。
> 9. swap : 交换两个智能指针所指向的对象。
> 10. 智能指针名字作为判断条件
> 11. 转换成shared_ptr类型，如果unique_ptr为右值，就可以将它赋值给shared_ptr。
> 因为shared_ptr包含一个显式构造函数，可用于将右值unique_ptr转换为shared_ptr， shared_ptr将接管原来归unique_ptr所拥有的对象
```cpp
unique_ptr<string> ps1(new string("i am xxxx"));
unique_ptr<string> ps2(ps1);    // 不支持拷贝
unique_ptr<string> ps3 = ps1;  // 不支持 赋值， 独占式智能指针不支持
====
unique_ptr<string> ps1(new string("i am xxxx"));
unique_ptr<string> ps2 = std::move(ps1);  // 支持移动语义，移动后，ps1为空，ps2指向原先的ps1

====
unique_ptr<string> ps1(new string("i am xxxx"));
unique_ptr<string> ps2(ps1.release());
if(ps1 == nullptr)
{
	cout << "ps1被置空！" << endl;
}

// ps2.release();    // 直接这样会导致内存泄露 
/// 需要下面这样写
string* tmp = ps2.release();
delete tmp;   // 手工释放

=====

unique_ptr<string> ps1(new string("i am xxxx"));
ps1.reset();   // 直接置空
======
unique_ptr<string> ps1(new string("i am xxxx"));
unique_ptr<string> ps2(new string("i am jjjjjj"));
ps1.reset(ps2.release()); // 释放ps1指向的对象内存，让ps1指向ps2所指向的内存，同时ps2被置空
// 或者 ps1.reset(new string("i am fffff"));

=====
6.
unique_ptr<int[]> arr(new int[10]);  // 数组后面需要加上[]
arr[0] = 10;
arr[1] = 11;
// 这里不要忘记A[]()自己定义的类， 如果有自己的析构函数，则会报异常
===
7. 
unique_ptr<string> ps1(new string("i am xxxx"));
string* ps = ps1.get();
*ps = "i am jjjjjj"; 
// delete ps；   // 不要这么干，否则产生不可预料的后果

===
8. 
unique_ptr<string> ps1(new string("i am xxxx"));
*ps1 = "i am jjjjjj"; 

unique_ptr<int[]> arr(new int[10]);   // 对于定义的内容是数组，是没有解引用运算符的
// *arr[0] = 10; 
====
11.
auto mufunc()
{
	return unique_ptr<string> ps1(new string("i am xxxx"));  // 这是个右值，（临时对象都是右值）
}
shared_ptr<string> pss1 = myfunc(); // 是可以的， 这里会创建控制块

// 第二种方法
unique_ptr<string> ps1(new string("i am xxxx"));
shared_ptr<string> pss1 = std::move(ps);  // 左值转右值，执行后ps为空，pss1 就是shared_ptr


```

