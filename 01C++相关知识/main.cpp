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

	// std::bind ������ �����󶨵ĺ������󣬺���ָ�룬��Ա����ָ�룬������ֵ1��������ֵ2��... n)
	// �ܽ᣺ 
	// 1. ���ɵ��ö���Ͳ�������һ�𣬹���һ���º��������Կ���ֱ�ӵ���
	// 2. ��������ж�����������԰�һ���ֲ��������������ڵ��õ�ʱ��ָ��
	cout << "==========" << endl;
	auto bf1 = bind(myfunc3, 10, 20, 30);  // ���ص��Ƿº�������
	bf1();   // ִ��myfunc3 ����

	auto bf2 = bind(myfunc3,placeholders::_1, placeholders::_2,30);  // �����ռλ����������ú��������
	bf2(11,22); 
	
	auto bf3 = bind(myfunc3, placeholders::_1, placeholders::_1, 30);
	bf3(33,44);  // ��ĵڶ�������û������ 

	cout << "===== " << endl;
	bind(myfunc3, placeholders::_1, placeholders::_1, 30)(55,66);   // ����ֱ�ӵ���

	cout << "===== " << endl;
	auto bf4 = bind(myfunc3, placeholders::_2, placeholders::_1, 30);
	bf4(88, 99);   // 998830

	cout << "+++++++" << endl;
	int a = 2;
	int b = 3;
	auto bf5 = bind(myfunc4, a, placeholders::_1);
	bf5(b);
	// bind ����Ԥ�Ȱ󶨵ĺ���������ͨ��ֵ���ݵģ����������a ��ֵ���ݵ�
	// bind ���ڲ����Ȱ󶨵Ĳ�����ͨ��std::placeholders ���ݲ���ʱ����ͨ�����ô��ݵģ�bʵ���������ô���
	cout << "a, b = " << a << b << endl;  // 2 4

	// һ�������
	cout << "????????" << endl;
	CT ct;
	auto bf6 = bind(&CT::myfunc, ct, placeholders::_1, placeholders::_2);   // ���ó�Ա����������������ct
	// ����ĺ��������Ժ��ǸĶ��˵ģ� ����ʵ����ct�����г�Ա����m_a ����0 ��û�б仯��
	bf6(11, 22);    // 11, 22  ������ct ������ �����˳�Ա������ ��ʱm_a ��ֵӦ����11
	// ���� �� 
	// 1. �����bind���� ���õ�CT�Ŀ������캯��������һ��CT���͵���ʱ������Ϊbind�ķ���ֵ�����ص��Ƿº������Ͷ���
	// �����ĳ�Ա�������õ��޸ĵ������ʱ�����m_a ֵ������Ӱ����ʵ��ct�����m_a ����Ա�����ģ�ֵ
	//

	//=====================================================================================
	//�������ǰ�����&�� �Ͳ���������ʱ�Ķ��󣬺�����Ա����myfunc �޸ĵľ���ct����ĳ�Ա����
	// ��ʱbind �ķ���ֵ����ct����ı����º������Ͷ���
	auto bf7 = bind(&CT::myfunc, &ct, placeholders::_1, placeholders::_2);
	bf7(11, 22);
	

	//=======================================================================================
	// function ��bind ���ʹ��
	CT ct2;
	function<void(int, int)> bf8 = bind(&CT::myfunc, ct2, placeholders::_1, placeholders::_2);
	bf8(88, 99);

	// �ѳ�Ա������ַ������һ���󶨣��󶨽������function<int&(void)> �ﱣ�棬˵���˾���һ���ɵ��ö���ķ���


	// �ܽ᣺
	/*
	1. bind ˼�룺 ��ν���ӳٵ��ã����ɵ��ö���ͳһ��ʽ��������������Ҫ��ʱ�����
	2. ��������std::function ��һ���ɵ��ö������ͳ�Ա���ܰ�std::bind ��Ա��������Ա�����ȵȶ��ܰ�
	*/
	

	return 0;
}