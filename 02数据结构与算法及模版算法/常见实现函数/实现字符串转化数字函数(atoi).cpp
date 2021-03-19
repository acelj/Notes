#include <iostream>

using namespace std;

/************************************************************************/
/* 
1. 判断合法
2. 计算长度
3. 检查正负
4. 遍历长度
	1. 过滤非数字字符
	2. 从非零开始
	3. 计算数字
5. 返回正负数字

*/
/************************************************************************/

int myatoi(const char* str)
{
	int flag = 0;  // 标记正负
	int len = 0;

	int num = 0;
	if (str == nullptr) return -1;    // 1. 判断合法

	char* p = const_cast<char*>(str);
	while (*p++ != '\0') len++;

	p = const_cast<char*>(str);
	if (p[0] == '-') flag = 1;

	char tmp;
	for (int i = 0; i < len; i++)
	{
		tmp = *p++;
		if (tmp > '9' || tmp < '0')   // 过滤
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