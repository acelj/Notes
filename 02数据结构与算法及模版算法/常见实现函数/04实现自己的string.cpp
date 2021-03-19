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
		sizeof �� strlen ����
		1. sizeof ��һ���������� strlen �ǿ⺯��
		2. sizeof �Ĳ��������������ͣ�Ҳ�����Ǳ�����   strlen ֻ���Խ�βΪ '\0' ���ַ���������
		3. �������ڱ����ʱ��ͼ������sizeof �Ľ������strlen ��������������ʱ���ܼ��������
		sizeof ���������������ռ�ڴ��С�� ��strlen ������ַ���ʵ�ʵĳ��ȡ�
		4. ������sizeof�Ĳ������˻������ݸ�strlen ���˻�Ϊָ�롣
		*/
		/************************************************************************/
		m_size = strlen(str);   // strlen() ������   
		m_data = new char[m_size];
		/************************************************************************/
		/* 
		1. strcpy ���� ʵ���ַ���������Ŀ���
		*/
		/************************************************************************/

		strcpy(m_data, str);
	}
}

MyString::MyString(const MyString &s)
{
	m_size = s.m_size;
	m_data = new char[m_size + 1];   // ��m_data ��NULL �ж�
	strcpy(m_data, s.m_data);
}

MyString::~MyString()
{
	delete[] m_data;
}

// ʵ���ַ�����ֵ����
MyString& MyString::operator=(const MyString &s)
{
	if (this == &s) return *this;    //  �÷ֵ㣺 ����Ը�ֵ

	delete[] m_data;   // �ͷ�ԭ�е��ڴ���Դ
	m_size = strlen(s.m_data);
	m_data = new char[m_size + 1];
	strcpy(m_data, s.m_data);
	return *this;					// ���ر����������
}


