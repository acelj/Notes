#include <iostream>

using namespace std;

class MyString {
public:
	MyString(const char* str = nullptr);
	MyString(const MyString &s);
	~MyString();
	MyString& operator=(const MyString& s);

private:
	char* m_data;
	int m_size;
};




int main()
{
	return 0;
}

MyString::MyString(const char * str)
{
	if (str == nullptr)
	{
		m_data = new char[1];
		m_data[0] = '\0';
		m_size = 0;
	} 
	else
	{
		/************************************************************************/
		/* 
		sizeof 和 strlen 区别
		1. sizeof 是一个操作符， strlen 是库函数
		2. sizeof 的参数可以数据类型，也可以是变量，   strlen 只能以结尾为 '\0' 的字符串做参数
		3. 编译器在编译的时候就计算出了sizeof 的结果，而strlen 函数必须在运行时才能计算出来，
		sizeof 计算的是数据类型占内存大小， 而strlen 计算的字符串实际的长度。
		4. 数组做sizeof的参数不退化，传递给strlen 就退化为指针。
		*/
		/************************************************************************/
		m_size = strlen(str);   // strlen() 函数是   
		m_data = new char[m_size];
		/************************************************************************/
		/* 
		1. strcpy 函数 实现字符串变量间的拷贝
		*/
		/************************************************************************/

		strcpy(m_data, str);
	}
}

MyString::MyString(const MyString &s)
{
	m_size = s.m_size;
	m_data = new char[m_size + 1];   // 对m_data 加NULL 判断
	strcpy(m_data, s.m_data);
}

MyString::~MyString()
{
	delete[] m_data;
}

// 实现字符串赋值函数
MyString& MyString::operator=(const MyString &s)
{
	if (this == &s) return *this;    //  得分点： 检查自赋值

	delete[] m_data;   // 释放原有的内存资源
	m_size = strlen(s.m_data);
	m_data = new char[m_size + 1];
	strcpy(m_data, s.m_data);
	return *this;					// 返回本对象的引用
}


