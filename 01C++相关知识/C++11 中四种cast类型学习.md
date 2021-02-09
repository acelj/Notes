```cpp
#include <iostream>
using namespace std;

int main()
{
	//// 一、 隐式类型转换： 系统自动进行，不需要开发人员管
	//int x = 3 + 4.213;
	//double b = 4 + 5.1231;

	//// 二、显式类型转换：（强制类型转换）
	//int k = 5 % (int) 2.3;   // c语言风格中的强制转换， 没有类型检查，像int k = 5 % (int)"asdad"; 都能过，但没意义
	////int k = 5 % (int)"asdad";   // 实际上是错误的
	//int k = 5 % int(2.3);    // 函数风格， 也是c语言风格的


	// C++ 强制类型转换分为4种： 分别用于不同场合
	/*
	1. static_cast :
	2. dynamic_cast;  运行时， 其他都是编译时转换
	3. const_cast;
	4. reinterpret_cast;
	这四个强制类型转换被称呼为“命名的强制类型转换”
	格式： 强制类型转换名<type>(express) :
	强制类型转换名： 是上面的4种cast
	type: 转换的目标类型
	express: 需要转换的值
	*/
	// 1. static_cast : 静态转换， 理解成正常转换，编译时会进行类型转换的检查
		//代码中确保类型转换的安全性，c风格的强制类型转换，都可以用这个。
	
	// 可用于：
	//// a) 相关类型转换，如整型和实型
	//double f = 3.14f;
	//int i = int(f);    // c风格的
	//int i2 = static_cast<int>(f);  // c++风格
	//// b) 子类转成父类类型（继承关系），可以用这个
	//class A {};
	//class B :public A {};
	//B b;
	//A a = static_cast<A>(b);   // 把子类转换为父类对象   OK 

	//A a;
	//B b = static_cast<A>(a);   // 这个是不行的
	// c) void* 与其他类型指针之间的转换 ，  void* 万能指针
	//int i = 10;
	//int* p = &i;
	//void* q = static_cast<void*>(p);   // int* 转换为void* 

	// 不可用于： 
	// 一般不可以用 int* 转换成double* , float* 转 double*等


	// 2. dynamic_cast; 主要应用与   运行时的类型检查。主要用来父类型和子类型之间转换的（父类指针指向子类类型对象的）
					// 然后用dynamic_cast 把父指针类型往子指针类型转
		// 如果该运算符能够转换成功，说明这个指针实际上是要转换到那个类型，这个运算符可以帮助做安全检查。
	// Human 父类，  Man 子类  ， Women 未定义类
	//Human* phuman = new Men;
	//Men* p = (Men*)phuman;   // c语言风格， 强制类型转换 , 可能不成功， 这时就需要用dynamic_cast

	//Men* pmen = dynamic_cast<Men*>(phuman);
	//if (pmen != nullptr)
	//{
	//	cout << "phumen 现在是Men 类型" << endl;
	//}
	//else
	//{
	//	cout << "转换失败" << endl;
	//}

	// dynamic_cast : 这个可以对于引用， 如果失败，则系统会抛出一个std::bad_cast异常 try {}  ... catch () {}

	//Human* phumen = new Men;
	//Human &q = *phumen;
	//try
	//{
	//	Men &menb = dynamic_cast<Men&>(q);   // 转换不成功, 程序流程直接进入catch ,如果成功，流程继续往下走
	//	cout << "phumen 是Men 类型 " << endl;
	//	menb.xxxx(); 

	//}
	//catch (std::bad_cast)
	//{
	//	cout << "phumen 实际上不是一个Men 类型" << endl;
	//}




	// 3. const_cast : 去除指针或引用的const属性， 该转换能够将const性质去掉
	//		// 编译时就会进行类型转换
	//const int ai = 100;
	////int a = const_cast<int>(ai);    // ai 不是指针不是引用， 无法使用

	//const int* p = &ai;
	//int* pi = const_cast<int*>(p);   // OK 将const 属性去掉
	//*pi = 120;    // 这种行为不友好， 不同编译器可能改不了
	//cout << *pi << endl;


	// 4. reinterpret_cast; 编译时候 就会进行类型转换检查。  被认为是危险的类型转换，编译器都不报错
		// reinterpret_cast：重新编译，（将操作数内容解释为另一种不同的类型【能把操作数的类型都转了】）
	// 处理无关类型的转换 ： 也就是两个转换类型之间没有关系，就等于可以乱转，怎么转都行，很随意。

	// a) 将一个整型（地址）转换成指针，一种类型指针转换成另一种类型指针，按照转换后的内容重新解释内存中的内容。
	// b) 也可以从一个指针类型转换成一个整型
	int i = 10;
	int* pi = &i;
	int* p2 = reinterpret_cast<int*>(&i);
	char* p3 = reinterpret_cast<char*>(pi);   // int* 转换成char*

	// 例子
	int i = 10;
	int* pi = &i;
	void* pvoid = reinterpret_cast<void*>(pi);
	// .. 业务逻辑
	int* pi2 = reinterpret_cast<int*>(pvoid);


	// 总结
	// 1. 强制类型转换，不建议使用，强制类型转换能够抑制编译器报错。
	// 2. 学习目的，认识这些类型转换符，方便大家阅读源代码。
	// 3. 资料说 reinterpret_cast 是危险的， const_cast 意味着设计缺陷。
	// 4. 不要在使用c语言中的类型转换，是在要用，用C++的。
	// 5. 一般static_cast 和reinterpret_cast 就能够很好的取代c语言中的强制转换。

	// reinterpret_cast 只要好好用， 合乎规则用，其实很好用的。


 	return 0;
}
```

