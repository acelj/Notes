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

	void(*fp)(int) = myfunc;   // ������һ������ָ�� fp �����˳�ֵ
	void(*fp2)(int) = &myfunc;    // �Ӳ���& ��һ��
	fp(5);    // ���ú����� �⣨����ָ�룩����һ���ɵ��ö���
	fp2(12);

	// �º����Ķ��壺 �����뺯���Ķ���
	T t;   // ����ֱ�� T t(4);  ( ����ǵ��ù��캯��)
	t(3);


	// std::function(�ɵ��ö����װ��)�� ������װ���ֿɵ��ö���    #include <functional>
	// ����װ���Աָ��
	function<void(int)> f1 = myfunc;   // ����ͨ����   ��������void�� ����int
	f1(2);

	function<int(int)> f2 = T::Tfunc;
	f2(22);

	return 0;
}