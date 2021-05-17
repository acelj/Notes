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
		func();   // ͨ��lambda������Ϊ�̵߳Ĳ����Ļ��������detach �����ƴ���
	});
#elif 1
	int x = 5;
	//std::thread th(method, std::ref(x));   // ����ֻ����std::ref, ������&

	X xx;
	std::thread th(&X::do_something, &xx);   // �������õ�&, ���������std::ref ���� &

	th.join();
	cout << x << endl;

	// std::refֻ�ǳ���ģ�����ô��ݣ������������������ https://blog.csdn.net/xuebing1995/article/details/103729013
	// ����bind��ʱ���������refʱ�����ú�����û�����õ�

#endif
	cout << "main thread end" << endl;

	return 0;
}
