#include <iostream>
#include <thread>

using std::cout;
using std::endl;

#if 1
void func()
{
	cout << "current thread start! " << endl;
	while (1)
	{

	}
}
//#elif 1
class backgroud_task
{
public:
	void operator()() const
	{
		func();
	}
};

#endif

void method(int &a) { a += 5; }
class X
{
public:
	void do_something()
	{
		cout << "X do_something" << endl;
	}
};

int main()
{
	cout << "main thread start" << endl;
#if 0
	backgroud_task f;
	std::thread t(f);
	t.join();
#elif 0
	std::thread my_threaf([] {
		func();   // 通过lambda函数作为线程的参数的话，会出现detach 的类似错误
	});
#elif 1
	int x = 5;
	//std::thread th(method, std::ref(x));   // 这里只能用std::ref, 不能用&

	X xx;
	std::thread th(&X::do_something, &xx);   // 这里是用的&, 这里可以用std::ref 或者 &

	th.join();
	cout << x << endl;

	// std::ref只是尝试模拟引用传递，并不能真正变成引用 https://blog.csdn.net/xuebing1995/article/details/103729013
	// 在用bind的时候，如果不用ref时，调用函数是没有引用的

#endif
	cout << "main thread end" << endl;

	return 0;
}
