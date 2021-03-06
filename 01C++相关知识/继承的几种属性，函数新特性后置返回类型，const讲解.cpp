/************************************************************************/
/*  
1. 以下三种继承方式讲解： 
public 、protecte、private: 在基类的自身成员可以对基类中任何一个其他成员进行访问，但是通过基类的对象，就只能
返回该类的公有成员（public）。

下面区分三种继承方式，（C++中支持多继承，java 中不支持多继承）
公有继承： 当类中的继承方式是公有继承时，基类的共有成员和保护成员的访问属性在派生类中不变，而基类中的私有成员
不可直接访问。（也就是说基类中的公有成员和保护成员被继承到派生类中访问属性不变，派生类中其他成员可以直接访问
它们，在类外只能通过派生类的对象访问基类继承的公有成员，而无论是派生类的成员还是派生类的对象都无法直接访问基类的私有成员）

私有继承：当类的继承方式是私有继承时，基类中的公有成员和保护成员都以私有成员身份出现在派生类中，而基类的私有成员
在派生类中不可访问。（也就是说基类的共有成员和保护成员被继承后作为派生类中的私有成员，派生类的其他成员可以直接访问
它们，但是在类外通过派生类的对象无法直接访问他们。）（无论是派生类的成员还是通过派生类的对象，都无法直接访问从基类
继承的私有成员。）
如果私有继承后，继续私有继承的话（进一步派生），原先的基类全部成员就无法在新的派生类中直接访问，也就是基类的成员在也无法
在以后的派生类中直接发挥作用，这个也叫做终止派生。

保护继承： 当类的继承方式是保护继承时，基类的公有成员和保护成员都以保护的身份出现的派生类中，而基类的私有成员不可直接访问。
（这样派生类的其他成员就可以直接访问从基类继承来的公有和保护成员，但在类外无法直接访问他们）（无论是派生类的成员还是派生
类的对象都无法直接访问基类的私有成员。）

比较私有继承和保护继承，在第一次继承后，所有成员访问属性是一样的，但是当派生类继续向下派生后，区别就体现出来了；
两次是以保护继承的，则基类中的成员可能是保护成员（基类是public和protected 是可以访问的），是可以通过在成员内部进行访问的。
两次是以私有继承的，则基类中的成员是全部都不能访问的。

*/
/************************************************************************/

#include <iostream>
using namespace std;

auto func(int a, int b) -> int;   // 函数声明
auto func(int a, int b) -> int   // 函数定义， 后置返回类型
{
	return 3;
}

inline int func2(int a)   // 内联函数，在函数前面加上inline
{
	return 2;
}

constexpr int mf()
{
	return 0;
}

int main()
{
	// 一、 普通函数和后置返回类型的函数
	/************************************************************************/
	/*
	函数返回类型放在函数名之前，叫做前置返回类型
	C++11 中 后置返回类型，就是在函数声明和定义中，把返回类型写在参数列表之后
	前面放的是auto， 表示函数返回类型放到参数列表之后。-> 后面代表返回的参数
	*/
	/************************************************************************/

	// 二、内敛函数： 在函数定义前加上inline，
	// 函数体很小，调用的频繁，就需要引入inline函数
	// 1. inline 影响编译器，在编译阶段对inline 函数处理，系统尝试将调用函数替换为函数体，通过西方式，提升性能
	// 2. inline 只是对开发者对编译器的一个建议，决定权在编译器，编译器可做可不做。
	// 3. 内敛函数定义需要放在头文件中，不然做不了替换函数体这个功能。

	// 注意点， 内敛函数需要尽可能的小

	// 注意： 各种编译器对inline 的处理方式不同，inline函数应该尽可能的小，循环和分支，递归不要出现的内敛函数中

	// constexpr 函数, 可以看成更严格一种内联函数
	// #define 宏 展开也类似inline 


	// 三、const char * 、 char const * 、 char * const  区别
	// 1. const char* p;
	char str[] = "i love china";
	const char* p;    // p 指向的东西不能通过p来修改（p所指向的目标，那个目标的内容不能通过p来改变）
	//p = str;   // 可以现在初始化
	//p++;
	//*p = 'Y';   // 语法错误

	// char const *  等价于 const char*p  ;

	char* const p2 = str;   // 定义的时候必须初始化
							//  p2一旦指向了一个东西之后，就不可以在指向其他东西了
	// p2++;   // 不可以，p2一旦指向一个东西止呕，就不可以在指向其他东西了
	*p2 = 'U';   // 但可以修改p2指向的目标中的内容。


	//const char * const p = str;   // p的指向也不能改变，p指向的内容也不能通过p来改变。
	// =====
	int i = 100;
	const int &a = i;   // 代表a的内容是不能通过a自己来修改的，可以通过i来修改
	i = 200;
	// a = 500;   // 是不合法的

	// int &b = 3;   // 不合法的， 必须要是左值
	const int &b = 3;   // 分配了内存的，在形参中加上const，可以传字面值常量
	
	// 四、函数中形参中带const, 在函数中就不会被修改
	// 在形参中加上const
	// 1. 可以防止无意修改形参值导致实参值被修改
	// 2. 实参的类型可以更加灵活。
	// 3. 在形参中加上const，可以传字面值常量  形参是const int &a的话， 可以直接传3， 如果是int & 的话，传数值是不行的。


	return 0;
}


