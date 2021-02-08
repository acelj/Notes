```cpp
/************************************************************************/
/* 
1.使用attribute关键字，声明constructor和destructor函数(gcc中，注意：vc中不支持attribute)
2.通过段名称“.CRTXIU”，“.CRTXCU”把函数放在“C/C++初始化函数表”中
3.利用全局对象的构造函数会在main函数之前执行的特点

*/
/************************************************************************/

/************************************************************************/
/* 
C++ 中的_onexit() 函数：这个函数可以实现在main主函数执行完毕之后，才执行的代码。
(1)使用格式：_onexit(int fun()) ，其中函数fun()必须是带有int类型返回值的无参数函数;
(2)_onexit() 包含在头文件cstdlib中，cstdlib为c语言中的库函数；
(3)无论函数_onexit() 放到main中任意位置，它都是最后执行。
(4) _onexit()： 多个onexit() 函数就是写在mian前面的是最后执行。
*/
/************************************************************************/

#include <iostream>

using namespace std;

int func1()
{
	cout << "this is func1() " << endl;
	return 0;
}

int func2()
{
	cout << "this is func2() " << endl;
	return 0;
}

int func3()
{
	cout << "this is func3() " << endl;
	return 0;
}

typedef int func();

#pragma data_seg(".CRT$XIU")  //用#pragma data_seg建立一个新的数据段并定义共享数据
func* myfunc1 = func1;

//XIU 是最先执行的， 然后是全局对象的构造函数， 然后是XCU执行, 然后是main执行，最后全局对象的析构函数
#pragma data_seg(".CRT$XCU")  
func* myfunc2 = func2;

//#pragma data_seg() 



// 3. 全局对象的构造函数会在main 函数之前执行 
class MyClass {
public:
	MyClass()
	{
		cout << "MyClass constructor function! " << endl;
	}
	~MyClass()
	{
		cout << "~MyClass destructor function! " << endl;
	}
};

MyClass test;    // 利用全局对象的构造函数会在main函数之前执行的特点。

int main()
{
	//_onexit(func1);  // 写在main函数中的 最后执行的函数，无论什么位置， 如果有多个，则写在前面的最后执行。
	cout << "this is main function " << endl;
	//_onexit(func2);
	//_onexit(func3);
	return 0;
}




```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210208200348366.png)

---

> C++ 中的_onexit() 函数：这个函数可以实现在main主函数执行完毕之后，才执行的代码。
(1)使用格式：_onexit(int fun()) ，其中函数fun()必须是带有int类型返回值的无参数函数;
(2)_onexit() 包含在头文件cstdlib中，cstdlib为c语言中的库函数；
(3)无论函数_onexit() 放到main中任意位置，它都是最后执行。
(4) _onexit()： 如果有多个onexit() 函数，就是写在mian前面的是最后执行。


```cpp
/************************************************************************/
/* 
C++ 中的_onexit() 函数：这个函数可以实现在main主函数执行完毕之后，才执行的代码。
(1)使用格式：_onexit(int fun()) ，其中函数fun()必须是带有int类型返回值的无参数函数;
(2)_onexit() 包含在头文件cstdlib中，cstdlib为c语言中的库函数；
(3)无论函数_onexit() 放到main中任意位置，它都是最后执行。
(4) _onexit()： 多个onexit() 函数就是写在mian前面的是最后执行。
*/
/************************************************************************/

#include <iostream>

using namespace std;

int func1()
{
	cout << "this is func1() " << endl;
	return 0;
}

int func2()
{
	cout << "this is func2() " << endl;
	return 0;
}

int func3()
{
	cout << "this is func3() " << endl;
	return 0;
}
// 3. 全局对象的构造函数会在main 函数之前执行 
class MyClass {
public:
	MyClass()
	{
		cout << "MyClass constructor function! " << endl;
	}
	~MyClass()
	{
		cout << "~MyClass destructor function! " << endl;
	}
};

MyClass test;    // 利用全局对象的构造函数会在main函数之前执行的特点。

int main()
{
	_onexit(func1);  // 写在main函数中的 最后执行的函数，无论什么位置， 如果有多个，则写在前面的最后执行。
	cout << "this is main function " << endl;
	_onexit(func2);
	_onexit(func3);
	return 0;
}
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210208205621442.png)

