#include <stdio.h>
#pragma pack(8)
using namespace std;

// ===============================================================================================================
/*
1. 概念 ： 内存对齐 又叫做字节对齐
2. 为什么需要内存对齐， 内存地址对齐，是一种在计算机内存中排列数据、访问数据的方式。
3. windows 中32位指的是什么？ 当今计算机内存中读写数据都是按照word（字）大小块进行操作的，（在32位系统中，数据总线宽度为32，
每次能读取4字节，地址总线宽度为32，因此最大的 寻址空间为2^32 = 4GB，但是最低2位A[0], A[1] 是不用寻址的， A[2-31] 才能存储器
相连，因此智能访问4的倍数地址空间，但是总的寻址空间还是 2^30 *字长 = 4GB）
	1word = 2Byte = 16bit  (现在通常),不同计算机的位数是不同的，通常16位一个字，32位是一个双字，64位是两个双字
	计算机的字长决定CPU一次处理实际位数的多少，字长越大，性能越优。衡量计算机性能的一个因素。
4，内存对齐和非内存对齐举个例子： 
	假设计算机的字大小为4个字节，因此变量在内存中的首地址都是满足4地址对齐，CPU只能对4的倍数的地址进行读取，而每次能读取4个
字节大小的数据。假设有一个整型的数据a的首地址不是4的倍数，不妨设为0X00FFFFF3，则该整型数据存储在地址范围为
0X00FFFFF3~0X00FFFFF6的存储空间中，而CPU每次只能对4的倍数内存地址进行读取，因此想读取a的数据，CPU要分别在0X00FFFFF0和0X00FFFFF4
进行两次内存读取，而且需要对两次的数据进行处理后才能得到a的数据。
（关键 ： 一个程序的瓶颈往往不是CPU的速度，而是取决于内存的带宽，因为CPU的处理速度远大于从内存中读取数据的速度，因此减少对内存
空间的访问是提高程序性能的关键。）
5. 位域 ： char a:4; char b:8;
char a:4 ;char b:8;
char类型的size是8位，一个字节大小。或依据编译器内定。
char a:4;//意思是指char类型变量a只使用低四位表示，即其取值范围是0x00~0x0F
char b:8;//意思雷同，b的取值可以是ox00~0xFF
拓展： 以前内存小，或者现在在协议中有些字段不需要占用一个完整的字节，只需要占几个或一个二进制位，这时就需要将数据分开（就是位域了）。
truct bs
{
int a:8;
int b:2;
int c:6;
}data;
说明data为bs变量，共占两个字节。其中位域a占8位，位域b占2位，位域c占6位。
	说明
	1. 一个位域必须存储在同一个字节中，不能跨两个字节。如一个字节所剩空间不够存放另一位域时，应从下一单元起存放该位域。也可以有意使某位域从下一单元开始。例如：
	struct bs
	{
	unsigned a:4
	unsigned :0   //空域
	unsigned b : 4   //从下一单元开始存放
	unsigned c : 4
	}
	在这个位域定义中，a占第一字节的4位，后4位填0表示不使用，b从第二字节开始，占用4位，c占用4位。
	2. 由于位域不允许跨两个字节，因此位域的长度不能大于一个字节的长度，也就是说不能超过8位二进位。
	3. 位域可以无位域名，这时它只用来作填充或调整位置。无名的位域是不能使用的。例如：
		struct k
		{
		int a:1
		int :2   //该2位不能使用
		int b : 3
		int c : 2
		};
		从以上分析可以看出，位域在本质上就是一种结构类型， 不过其成员是按二进位分配的。


*/


// 在默认的情况下是通过struct 中的最大的字节对齐。最大是int 就是pack(4), 最大的是double就是pack(8) windows x86 环境下

struct S1 {
	int a : 8;   // 这里是位域
	char b : 4;
	int c : 4;
	double d;
};  // 20(pack(4)情况下)   24  (pack(8)情况下)

struct S11 {		// 这里就是一个字节中分成了4个部分
	char a : 1;
	char b : 2;
	char c : 3;
	char d : 2;	
};   // 1 (pack(4)情况下)  1  (pack(8)情况下)

struct S12 {
	char a : 1;
	char b : 2;
	char c : 3;
	char d : 2;
	int e : 1;
};   // 8 (pack(4)情况下)  8  (pack(8)情况下)

struct S2 {
	int a : 8;
	char b : 4;
	double c;
	int d : 4;
};  //20 (pack(4)情况下)  24   (pack(8)情况下)

struct S3 {
	int a;
	char b;
	double c;
	int d;
};  //20 (pack(4)情况下)  24  (pack(8)情况下)

struct S4 {
	int a;
	char b;
	int c;
	double d;
};  //20  (pack(4)情况下)  24  (pack(8)情况下)

struct Stu
{
	int num;
	char b;
	short c;
	char d[6];
};   // 这里是16 ，是加了后面对齐的空内存的，这里百度百科错误，百度百科写的是14 (pack(4)情况下)   16  (pack(8)情况下)

#pragma pack(8)
struct Stu2
{
	int num;
	char b;
	short c;
	char d[6];
};  // 这里也是16， 百科内存对齐中写的是错误的  (pack(4)情况下)   16  (pack(8)情况下)

int main()
{
	printf("S1 = %d\n", sizeof(S1));
	printf("S11 = %d\n", sizeof(S11));
	printf("S12 = %d\n", sizeof(S12));

	printf("================\n");
	printf("S2 = %d\n", sizeof(S2));
	printf("S3 = %d\n", sizeof(S3));
	printf("S4 = %d\n", sizeof(S4));
	printf("Stu = %d\n", sizeof(Stu));
	printf("Stu2 = %d\n", sizeof(Stu2));
	//printf("%d\n", sizeof(S1));
	//cout << sizeof(S1) << endl;
	//cout << sizeof(S2) << endl;
	//cout << sizeof(S3) << endl;
	//cout << sizeof(S4) << endl;

	return 0;
}