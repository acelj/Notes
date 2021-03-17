#include <iostream>
#include <functional>

using namespace std;

void myfunc(int a)
{
	cout << "myfunc() ... " << a << endl;
}


class T
{
public:
	void operator()(int a)
	{
		cout << "operator() ...  " << a << endl;
	}

	static int Tfunc(int a)
	{
		cout << "Tfunc ... " << a << endl;
		return a;
	}
};


void myfunc3(int a, int b, int c)
{
	cout <<" a,b,c = " << a << b << c << endl;
}

void myfunc4(int &x, int &y)
{
	x++;
	y++;
}

class CT {
public:
	void myfunc(int a, int b)
	{
		cout << "a= " << a << " b = " << b << endl;
		m_a = a;
	}
	int m_a = 0;
};
int main()
{
	// 

	void(*fp)(int) = myfunc;   // 定义了一个函数指针 fp 并给了初值
	void(*fp2)(int) = &myfunc;    // 加不加& 都一样
	fp(5);    // 调用函数， 这（函数指针）就是一个可调用对象
	fp2(12);

	// 仿函数的定义： 类似与函数的东西
	T t;   // 不能直接 T t(4);  ( 这个是调用构造函数)
	t(3);


	// std::function(可调用对象包装器)， 用来包装各种可调用对象    #include <functional>
	// 不能装类成员指针
	function<void(int)> f1 = myfunc;   // 绑定普通函数   返回类型void， 参数int
	f1(2);

	function<int(int)> f2 = T::Tfunc;
	f2(22);

	// std::bind 绑定器， （待绑定的函数对象，函数指针，成员函数指针，参数绑定值1，参数绑定值2，... n)
	// 总结： 
	// 1. 将可调用对象和参数绑定在一起，构成一个仿函数，所以可以直接调用
	// 2. 如果函数有多个参数，可以绑定一部分参数，其他参数在调用的时候指定
	cout << "==========" << endl;
	auto bf1 = bind(myfunc3, 10, 20, 30);  // 返回的是仿函数对象
	bf1();   // 执行myfunc3 函数

	auto bf2 = bind(myfunc3,placeholders::_1, placeholders::_2,30);  // 这里的占位符是下面调用函数的序号
	bf2(11,22); 
	
	auto bf3 = bind(myfunc3, placeholders::_1, placeholders::_1, 30);
	bf3(33,44);  // 这的第二个参数没有作用 

	cout << "===== " << endl;
	bind(myfunc3, placeholders::_1, placeholders::_1, 30)(55,66);   // 可以直接调用

	cout << "===== " << endl;
	auto bf4 = bind(myfunc3, placeholders::_2, placeholders::_1, 30);
	bf4(88, 99);   // 998830

	cout << "+++++++" << endl;
	int a = 2;
	int b = 3;
	auto bf5 = bind(myfunc4, a, placeholders::_1);
	bf5(b);
	// bind 对于预先绑定的函数参数是通过值传递的，所以这里的a 是值传递的
	// bind 对于不事先绑定的参数，通过std::placeholders 传递参数时候是通过引用传递的，b实际上是引用传递
	cout << "a, b = " << a << b << endl;  // 2 4

	// 一个类对象
	cout << "????????" << endl;
	CT ct;
	auto bf6 = bind(&CT::myfunc, ct, placeholders::_1, placeholders::_2);   // 调用成员函数必须加上类对象ct
	// 这里的函数进入以后是改动了的， 但是实际上ct对象中成员变量m_a 还是0 （没有变化）
	bf6(11, 22);    // 11, 22  等于以ct 的名义 调用了成员函数， 这时m_a 的值应该是11
	// 解释 ： 
	// 1. 上面的bind函数 调用的CT的拷贝构造函数生成了一个CT类型的临时对象，作为bind的返回值（返回的是仿函数类型对象）
	// 后续的成员函数调用的修改的这个临时对象的m_a 值，并不影响真实的ct对象的m_a （成员变量的）值
	//

	//=====================================================================================
	//如果对象前面加上&， 就不会生成临时的对象，后续成员函数myfunc 修改的就是ct对象的成员变量
	// 这时bind 的返回值就是ct对象的本身（仿函数类型对象）
	auto bf7 = bind(&CT::myfunc, &ct, placeholders::_1, placeholders::_2);
	bf7(11, 22);
	

	//=======================================================================================
	// function 和bind 配合使用
	CT ct2;
	function<void(int, int)> bf8 = bind(&CT::myfunc, ct2, placeholders::_1, placeholders::_2);
	bf8(88, 99);

	// 把成员变量地址当函数一样绑定，绑定结果放在function<int&(void)> 里保存，说白了就是一个可调用对象的方法


	// 总结：
	/*
	1. bind 思想： 所谓的延迟调用，将可调用对象统一格式，保存起来，需要的时候调用
	2. 我们有用std::function 绑定一个可调用对象，类型成员不能绑，std::bind 成员函数，成员变量等等都能绑。
	*/
	

	return 0;
}