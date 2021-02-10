@[TOC]
## 高精度加法
1≤整数长度≤100000， 实现这两个整数的和。

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> add(vector<int>& A, vector<int>& B) ///< 计算数组A 表示的大数 加上数组B表示的大数
{
    vector<int> C;
    // t为进位
    int t = 0;
    for(int i=0; i < A.size() || i < B.size(); i++)
    {
        if(i <= A.size()) t += A[i];
        if(i <= B.size()) t += B[i];

        C.push_back(t % 10);    ///< 低位在前
        t /= 10;
    }
    if(t) C.push_back(1);   ///< 如果高位有进位， 添加上1
    return C;
}

int main()
{
    string a,b;
    cin >> a >> b;
    vector<int> A, B;

    for(int i=a.size()-1; i>=0; i--) A.push_back(a[i] - '0');   ///< 将个位放在数组前面
    for(int i=b.size()-1; i>=0; i--) B.push_back(b[i] - '0');

    auto C = add(A, B);
    /// 将答案C 数组输出出来， 注意顺序
    for(int i= C.size()-1; i>=0; i--) cout << C[i];
    return 0;
}
```

## 高精度减法
整数同上，计算结果可能是负数。

```cpp
#include <iostream>
#include <vector>
using namespace std;

/// 判断A 是否大于B
bool cmp(vector<int>&A, vector<int>& B)
{
    if(A.size() != B.size()) return A.size() >= B.size();

    for(int i=A.size()-1; i>=0; i--) 
        if(A[i] != B[i]) 
        return A[i] >= B[i];

    return true;
}

vector<int> sub(vector<int>& A, vector<int>& B)
{
    vector<int> C;
    int t = 0; /// 表示借位
    for(int i=0; i<A.size(); i++)  ///< 这里是个位相减，从0开始遍历
    {
        t = A[i] - t;   ///< t表示借位
        if(i < B.size()) t -=B[i];    ///< 表示B上i位有数的话，减去
        // 这里代表两种状态 1. t>=0 表示A[i] >= B[i] 能够直接减去，
        //                  2. t<0  表示 不够减， 需要借位， 在下面将t = 1， 然后下一位减去
        C.push_back((t + 10) % 10);  /// 表示了两种情况
        if(t < 0) t = 1;    ///< t< 0 表示借位了
        else
         t = 0;
    }

    // 去掉前面的0， 条件（位数大于1， && 前面的数字是0）
    while(C.size() > 1 && C.back() == 0) C.pop_back();  
    return C;
}


int main()
{
    string a, b;
    cin >> a >> b;
    vector<int> A, B;

    for(int i=a.size()-1; i>=0; i--) A.push_back(a[i] - '0');
    for(int i=b.size()-1; i>=0; i--) B.push_back(b[i] - '0');

    if(cmp(A,B))
    {
        auto C = sub(A, B);
        for(int i=C.size()-1; i>=0; i--)  cout << C[i] ;
    }
    else
    {
        cout << '-';
        auto C = sub(B, A);
        for(int i=C.size()-1; i>=0; i--) cout << C[i];
    }
    return 0;
}
```

## 高精度乘法
实现一个整数A * 一个整数b 。 A的长度[1,100000],  b 是[0,10000], b不是大数，用int

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> multi(vector<int>&A ,int b)
{
    vector<int> C;
    int t =0;
    for(int i=0; i<A.size() || t; i++)    // 需加上|| t  表示 乘以b后超过A了， 还可以计算
    {
        if(i< A.size()) t += A[i] * b;
        C.push_back( t % 10);
        t /= 10;
    }
    while(C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

int main()
{
    string a;
    int b;
    cin >> a >> b;
    vector<int> A;
    for(int i=a.size()-1; i>=0; i--)  A.push_back(a[i] - '0');

    auto C = multi(A,b);

    for(int i=C.size() -1; i>=0; i--) cout << C[i];
}
```

牛客网上的两个string 相乘，实现代码

```cpp
string solve(string s, string t) {
   // write code here
    int len1 = s.size();
    int len2 = t.size();
    string re(len1 + len2, '0');
    for(int i= len1 -1; i>=0; i--)
    {
        for(int j = len2 -1; j>=0; j--)
        {
            int tmp = (s[i] - '0') * (t[j] - '0') + (re[i + j + 1] - '0');
            re[i + j + 1] = tmp % 10 + '0';
            re[i + j] += tmp / 10;   // 前一位
        }
    }
    for(int i = 0; i < re.size(); i++)   // 去掉前面的0 ,因为初始化中有
        if(re[i] != '0') return re.substr(i);
    return "0";
}

```

## 高精度除法
给定两个非负整数A，b，请你计算 A / b的商和余数。A的长度[1,100000],  b 是[0,10000], b不是大数，用int。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 返回的vector是商， r是余数, r是引用
vector<int> div(vector<int>& A, int b, int& r)
{
    vector<int> C;

    for(int i=A.size()-1; i>=0 ;i--)
    {
        r = 10*r + A[i];
        C.push_back( r / b);    // 除以b的商
        r = r % b;    // 除以b的余数
    }
    reverse(C.begin(), C.end());   ///< 高位转化。
    while(C.size() > 1 && C.back() == 0)  C.pop_back();  ///< 去掉前面0， back 是vector最后的元素
    return C;
}

int main()
{
    string a;
    int b;
    cin >> a >> b;
    vector<int> A;
    for(int i=a.size()-1; i>=0; i--)  A.push_back(a[i] - '0');

    int r = 0;
    auto C = div(A, b, r);
    for(int i=C.size() - 1; i>=0; i--)  cout << C[i];
    cout << endl << r << endl;

    return 0;
}
```

