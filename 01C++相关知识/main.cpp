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

	return 0;
}