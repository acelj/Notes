#include <iostream>

using namespace std;

/************************************************************************/
/* 
1. �жϺϷ�
2. ���㳤��
3. �������
4. ��������
	1. ���˷������ַ�
	2. �ӷ��㿪ʼ
	3. ��������
5. ������������

*/
/************************************************************************/

int myatoi(const char* str)
{
	int flag = 0;  // �������
	int len = 0;

	int num = 0;
	if (str == nullptr) return -1;    // 1. �жϺϷ�

	char* p = const_cast<char*>(str);
	while (*p++ != '\0') len++;

	p = const_cast<char*>(str);
	if (p[0] == '-') flag = 1;

	char tmp;
	for (int i = 0; i < len; i++)
	{
		tmp = *p++;
		if (tmp > '9' || tmp < '0')   // ����
		{
			continue;
		}
		else
		{
			num *= 10;
			num += (tmp - '0');
		}
	}

	return flag == 1 ? -num : num;
}

int main()
{
	
	const char* str = "-54a3b21";
	cout << myatoi(str) << endl;
	return 0;
}