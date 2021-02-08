@[TOC]
## 机器人的运动范围
> 地上有一个 m 行和 n 列的方格，横纵坐标范围分别是 0∼m−1 和 0∼n−1。
一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格。
但是不能进入行坐标和列坐标的数位之和大于 k 的格子。
请问该机器人能够达到多少个格子？

```cpp
输入：k=7, m=4, n=5
输出：20

输入：k=18, m=40, n=40
输出：1484
解释：当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。
      但是，它不能进入方格（35,38），因为3+5+3+8 = 19。

class Solution {
public:
    int get_single_sum(int x)
    {
        int s = 0;
        while(x) 
        {
            s += x % 10, x /= 10;
        }
        return s;
    }

    int get_sum(pair<int,int> p)
    {
        return get_single_sum(p.first) + get_single_sum(p.second);
    }
    
    int movingCount(int k, int rows, int cols)
    {
        int re = 0;
        if(!rows || !cols) return 0;
        vector<vector<bool>> st(rows, vector<bool>(cols, false)); //这里是自动赋值成false cosl 需要加上()
        queue<pair<int, int>> q;   // 队列记录点
        q.push({0,0});
        
        int dx[4] = {-1,0,1,0}, dy[4] = {0,1,0,-1};
        //这里是典型的宽度遍历BFS, 直接从{0，0} 开始遍历， 需要注意下面的几个条件
        // 1. 之前没有遍历过的， 可用bool 数组进行判断
        // 2. 没有走出边界
        // 3. 横纵坐标的数加上小于目标值
        while(q.size())  // 当队列里面还有点的时候一直进行下面操作
        {
            pair<int, int> t = q.front();
            q.pop();   // 拿一个出来就淘汰一个
            
            // 这里面数字的和大于k 或者该点已经遍历 ，就返回，因为这题是要从合法的各子走到合法的格子中
            if(get_sum(t) > k || st[t.first][t.second])  continue;
            re ++ ;
            
            st[t.first][t.second] = true;
            
            for(int i=0; i<4; i++)
            {
                int x = t.first + dx[i], y = t.second + dy[i];
                if( x >= 0 && x < rows && y >= 0 && y<cols)  // 注意rows cols 不需要加上= 
                    q.push({x, y});
            }
        }
        return re ;
    }
};
```
> **时间复杂度**： O(mn)；  BFS 典型的宽度搜索，每个节点最多会入队一次，所以最大复杂度不会超过方格中的个数。
> **总结**： 这是一个典型的宽度优先搜索问题，我们从 (0, 0) 点开始，每次朝上下左右四个方向扩展新的节点即可。
扩展时需要注意新的节点需要满足如下条件：
	1. 之前没有遍历过，这个可以用个bool数组来判断；
	2. 没有走出边界；
	3. 横纵坐标的各位数字之和小于 k；
最后答案就是所有遍历过的合法的节点个数。

## 剪绳子
> 给你一根长度为 n 绳子，请把绳子剪成 m 段（m、n 都是整数，2≤n≤58 并且 m≥2）。
每段的绳子的长度记为k[0]、k[1]、……、k[m]。k[0]k[1] … k[m] 可能的最大乘积是多少？
例如当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到最大的乘积18。

```cpp
输入：8
输出：18


class Solution {
public:
    int maxProductAfterCutting(int n) {
        if(n<=3) return 1*(n-1);   // 因为必须分成大于等于2段
        
        int re = 1;
        if(n%3 == 1) re *= 4, n -=4;
        if(n%3 == 2) re *= 2, n -=2;
        while(n)
            re *=3, n -= 3;
            
        return re ;
    }
};
```
> **时间复杂度：** O(n).   当 n 比较大时，n 会被拆分成 ⌈n/3⌉个数，我们需要计算这么多次减法和乘法，所以时间复杂度是 O(n).
> **总结**：这是一道数学题, 首先把一个正整数 N 拆分成若干正整数只有有限种拆法，所以存在最大乘积。
假设 N=n~1~+n~2~+…+n~k~ ，并且 n~1~×n~2~×…×n~k~ 是最大乘积。
	1. `显然1不会出现在其中`；
	2. `如果对于某个 i 有 n~i~ ≥ 5，那么把 ni 拆分成 3+(ni−3)，我们有 3(n~i~−3)=3n~i~−9>n~i~；`
	3. `如果 n~i~=4，拆成 2+2乘积不变，所以不妨假设没有4；`
	4. `如果有三个以上的2，那么 3×3>2×2×2，所以替换成3乘积更大`；
综上，选用尽量多的3，直到剩下2或者4时，用2。

## 二进制中1的个数
> 输入一个32位整数，输出该数二进制表示中1的个数。
> 负数在计算机中用其绝对值的补码来表示。

```cpp
输入：9
输出：2
解释：9的二进制表示是1001，一共有2个1。

输入：-2
输出：31
解释：-2在计算机里会被表示成11111111111111111111111111111110，
      一共有31个1。

class Solution {
public:
    int lowbit(int x)
    {
        return x & (-x);
    }
    int NumberOf1(int n) {
        // int re =0;
        // while(n)
        // {
        //     n -= lowbit(n);
        //     re++;
        // }
        // return re;
        
        // 正数的都一样
        // 负数-2 在计算机中是  11111111111111111111111111111110， 但是无符号的话，表示也是这样，如果把无符号转化成正数，就表示很大一个数了
        unsigned int val = n;   // 如果是负数，则无符号二进制表示的一样， 但是含义不同， 例如
        int re = 0;
        while(val) re += val & 1, val >>= 1;
        return re;
    }
};

```

> **时间复杂度**： O(logn) : 每次会将 n 除以2，最多会除 logn次，所以时间复杂度是 O(logn)。
> **总结**： 迭代进行如下两步，直到 n 变成0为止。
> 		1. 如果 n 在二进制表示下末尾是1，则在答案中加1；
> 		2. 将 n右移一位，也就是将 n在二进制表示下的最后一位删掉；
>这里有个**难点**是如何处理负数。在C++中如果我们右移一个负整数，系统会自动在最高位补1，这样会导致 n 永远不为0，就死循环了。
**解决办法是把 n 强制转化成无符号整型**，这样 n 的二进制表示不会发生改变，但在右移时系统会自动在最高位补0。

## 数值的整数次方
> 实现函数double Power(double base, int exponent)，求base的 exponent次方。
不得使用库函数，同时不需要考虑大数问题。
不会出现底数和指数同为0的情况
当底数为0时，指数一定为正

```cpp
输入：10 ，2
输出：100

输入：10 ，-2  
输出：0.01

class Solution {
public:
    double Power(double b, int e) {
        // 就是考察参数为负数的情况， 考察细心的问题,
        // 直接用下面的这个会出现精确度不够
        //double re = 1;
        //for(int i=0; i<abs(e); i++) re *= b;
        //if(e < 0) re = 1 /re;
        //return re;
        typedef long long LL;
        double re = 1;
        for(LL k = abs(LL(e)); k ; k>>=1)
        {
            if( k & 1) re *= b;
            b *= b;   //  因为根据二进制划分，下个数是上一个数的平方
        }
        if(e < 0) re = 1/ re ;
        return re;
    }
};

```
> **时间复杂度**： O(n), 假设指数是n， 一共会循环n次， 所以时间复杂度是logn.
> **总结**：本题如果需要考虑大数问题，需要用快速幂来算。快速幂可以看[这个](https://www.acwing.com/problem/content/877/)
> 注意当指数是负数时，我们需要先取指数的绝对值，最后将乘积的倒数作为答案。
> 当n为负无穷的时候，取相反数会超过`int` 范围，所以需要用到 `long long`.

## 在O(1)时间删除链表结点
> 给定单向链表的一个节点指针，定义一个函数在O(1)时间删除该结点。
假设链表一定存在，并且该节点一定不是尾节点。

```cpp
输入：链表 1->4->6->8
      删掉节点：第2个节点即6（头节点为第0个节点）
输出：新链表 1->4->8

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        // 因为是要在O(1)的时间复杂度内完成操作
        auto t = node->next;  // 将node指向的下一节点给t
        
        node->val = t->val;   // 然后将下一节点删除即可
        node->next = t->next;
        //*(node) = *(node->next);   // 上面的两行代码等于这一行
        
        delete t;
    } 
};

```
> 时间复杂度： O（1），
> 总结： 由于是单链表，我们不能找到前驱节点，不能按照常规的删除方法删除。 我们就可以将下一个节点复制到当前的节点，然后将下一个节点删除即可。

## 删除链表中重复的节点
> 在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留。

```cpp
输入：1->2->3->3->4->4->5
输出：1->2->5

输入：1->1->1->2->3
输出：2->3

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplication(ListNode* head) {
        auto v_node = new ListNode(-1);
        v_node->next = head;  //  new 一个虚拟node，防止head被删除
        
        auto p = v_node;  
        while(p->next)
        {
            auto q = p->next;   // p是在前的， q是在后面的额
            /// 如果q存在， 而且前一个节点的下一个val == q指向的val 这时候说明有重复元素， q 指向下一个元素， 一直while条件
            while(q && p->next->val == q->val)  q = q->next;
            
            // 如果p 和 q的节点没不重复，中间隔了一个元素， 所以需要p->next->next，如果=q, 则p向后移一个位置
            // else 中间不是隔一个元素， 则中间有元素是重复的， 需要删除中间重复的元素，直接进行 p->next = q即可
            if(p->next->next == q) p = p->next;   // 只有一个， 直接移动位置
            else p->next = q;    //  删除重复的一段
            
        }
        return v_node->next;
    }
};

```

> 时间复杂度： O(n) 线性扫描整个链表，所以是O（n）
> 总结：为了方便处理边界的情况，我们需要定一个虚拟的节点dummy,这个节点指向链表的头节点，然后从链表的头节点扫描整个链表，每次扫描的元素相同的一段，如果这段中的元素个数多余1个，则将整段元素直接删除。


## 正则表达式匹配
> 请实现一个函数用来匹配包括'.'和'*'的正则表达式。
模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。
在本题中，匹配是指字符串的所有字符匹配整个模式。
例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配。

```cpp
输入：
s="aa"
p="a*"
输出:true

class Solution {
public:
    int n, m;
    vector<vector<int>> f;
    string s, p;
    bool isMatch(string _s, string _p) {
        // f[i][j]表示从s的i个位置开始，和p的j个位置开始，是否匹配
        /*
        状态转移
        1. p[j] 是正常字符， f[i][j] = s[i] == p[j]  && f[i + 1][j + 1];  // = 优先级低
        2. p[j] 是'.', f[i][j] = f[i + 1][j + 1]    直接向后移一位进行比较
        3. p[j + 1] 是'*', f[i][j] = f[i][j + 2] || f[i + 1][j]
        
        f[n][m] = true   // 表示空串
        
        */
        s = _s, p = _p;
        n = s.size(), m = p.size();
        f = vector<vector<int>>(n + 1, vector<int>(m+1, -1));
        
        return dp(0,0, s, p);   // 直接从0,0 开始做比较
    }
    
    bool dp(int x, int y, string& s, string& p)
    {
        if(f[x][y] != -1) return f[x][y];
        if(y == m)
            return f[x][y] = x == n;
        bool first_match =  x < n && (s[x] == p[y] || p[y] == '.'); // 第1个字符是匹配的
        bool ans;
        if(y + 1 < m && p[y + 1] == '*')   // 后面两种情况
        { 
            ans = dp(x, y + 2, s, p) || first_match && dp(x + 1, y, s, p);
        }
        else    // 前面两种情况
        {
            ans = first_match && dp(x + 1, y + 1, s, p);
        }
        return f[x][y] = ans;
    }
    
    // ""  和 "."  比较
};

```
> 时间复杂度： 动态规划O(nm)   n表示s 的长度，m表示p的长度，总共nm个状态，状态转移复杂度是O（1），所以复杂度是O（nm）。
> 总结： 思路在上面写着。


## 表示数值的字符串
> 请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。
但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。
1. 小数可以没有整数部分，例如.123等于0.123；
2. 小数点后面可以没有数字，例如233.等于233.0；
3. 小数点前面和后面可以有数字，例如233.666;
4. 当e或E前面没有数字时，整个字符串不能表示数字，例如.e1、e1；
5. 当e或E后面没有整数时，整个字符串不能表示数字，例如12e、12e+5.4;

```cpp
输入: "0"
输出: true

class Solution {
public:
    bool isNumber(string s) {
        s += '\0';   //指针移动过程中，最后会有一位的溢出，加上一位空字符防止字符串下标越界
        bool isNum = false; //该变量表示从0开始，到i位置的字符串是否构成合法数字，初始化为false

        int i = 0;  //检测指针初始化为0

        while(s[i] == ' ') ++i; //滤除最前面的空格，指针后移

        if(s[i] == '+' || s[i] == '-') ++i; //一个‘-’或‘+’为合法输入，指针后移

        while(s[i] >= '0' && s[i] <= '9'){  //此处如果出现数字，为合法输入，指针后移，同时isNum置为true
            isNum = true;  //显然,在此处，前面的所有字符是可以构成合法数字的
            ++i;
        }

        if(s[i] == '.') ++i;    //按照前面的顺序，在此处出现小数点也是合法的，指针后移（此处能否构成合法字符取决于isNum）

        while(s[i] >= '0' && s[i] <= '9'){  //小数点后出现数字也是合法的，指针后移
            isNum = true;   //无论前面是什么，此处应当是合法数字
            ++i;
        }

        //上面的部分已经把所有只包含小数点和正负号以及数字的情况包括进去了，如果只判断不含E或e的合法数字，到此处就可以停止了

        if(isNum && (s[i] == 'e' || s[i] == 'E')){ //当前面的数字组成一个合法数字时（isNum = true），此处出现e或E也是合法的
            ++i;
            isNum = false; //但到此处，E后面还没有数字，根据isNum的定义，此处的isNum应等于false;

            if(s[i] == '-' || s[i] == '+') ++i; //E或e后面可以出现一个‘-’或‘+’，指针后移

            while(s[i] >= '0' & s[i] <= '9') {
                ++i;
                isNum = true; //E后面接上数字后也就成了合法数字
            }
        }

        //如果字符串为合法数字，指针应当移到最后，即是s[i] == '\0' 同时根据isNum判断数字是否合法
        //整个过程中只有当i位置处的输入合法时，指针才会移动
        return (s[i] == '\0' && isNum);
    }
};

```
> 时间复杂度： O（n）， 整个字符串只遍历一次。
> 总结： 
> 1. 先去除行首和行尾空格；
>2. 行首如果有一个正负号，直接忽略；
>3. 如果字符串为空或只有一个'.'，则不是一个合法数；
>4. 循环整个字符串，去掉以下几种情况：
(1) '.'或'e'多于1个;
(2) '.'在'e'后面出现；
(3) 'e'后面或前面为空，或者'e'前面紧跟着'.'；
(4) 'e'后面紧跟着正负号，但正负号后面为空；
>5. 剩下的情况都合法；

## 调整数组顺序使奇数位于偶数前面
> 输入一个整数数组，实现一个函数来调整该数组中数字的顺序。
使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分。

```cpp
输入：[1,2,3,4,5]
输出: [1,3,5,2,4]

class Solution {
public:
    void reOrderArray(vector<int> &array) {
         int l = 0, r = array.size() -1;
         while(l < r)
         {
             while(l < r && array[l] % 2 == 1) l ++;
             while(l < r && array[r] % 2 == 0) r --;
             if(l < r) swap(array[l], array[r]);
         }
    }
};

```
> 时间复杂度： O（n） 双指针： 前后遍历整个字符串。
> 总结：两个指针，一前一后进行遍历，保证前面指针的数都是奇数，后面指针的后面是偶数。
> 迭代的操作是，第一个指针向后走，遇到偶数停止；第二个指针向前走，遇到奇数停止，然后进行交换，进行下一轮迭代，直到指针相遇。


## 链表中倒数第k个节点
> 输入一个链表，输出该链表中倒数第k个结点。
> k >= 0 如果k大于链表长度，返回NULL。

```cpp
输入：链表：1->2->3->4->5 ，k=2
输出：4

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* findKthToTail(ListNode* head, int k) {
        //int n = 0;
        //for(auto p = head; p; p = p->next) n++;
        //if(k > n) return nullptr;
        //auto p = head;
        //for(int i=0; i<n-k; i++)
        //{
        //    p = p->next;
        //}
        //return p;
        
        // 下面是第二种方案， 将链表中的数据放入在栈中， 然后将k-1个pop() 出来，返回top() 的结果
        stack<ListNode*> st;
        for(auto p = head; p; p = p->next) st.push(p);
        
        for(int i=0;i<k-1 && !st.empty(); i++)
            st.pop();
        
        if(st.empty()) return nullptr;
        return st.top();
    }
};

```

> 时间复杂度： O（n) 都只遍历一次。
> 第一种方法： 第一次遍历得到整个链表长度，第二次直接找到倒数第k个节点（就是n- k - 1个节点）进行输出。
> 第二中方法： 利用栈。


## 链表中环的入口结点 
> 给定一个链表，若其中包含环，则输出环的入口节点。
若其中不包含环，则输出NULL;
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210207143749524.png)

```cpp
给定如上所示的链表：
[1, 2, 3, 4, 5, 6]
2
注意，这里的2表示编号是2的节点，节点编号从0开始。所以编号是2的节点就是val等于3的节点。
则输出环的入口节点3.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    // 思路： 快慢指针，刚开始快指针走2步，慢指针走1步，相遇后，两个指针都走1步，再次相遇后，就是环的入口节点
    // 上面的情况如果有快指针一直走到null，则代表不存在环
    ListNode *entryNodeOfLoop(ListNode *head) {
        if(!head || !head->next) return 0;
        auto first = head, second = head;
        
        while(first && second)
        {
            // 下面是表示慢指针走一步， 快指针走2步
            first = first->next;
            second = second->next;
            if(second) second = second->next;
            else return 0;   // 表示链表中没有环
            
            // 第一次相遇
            if(first == second)
            {
                first = head;
                while(first != second)
                {
                    first = first->next;
                    second = second->next;
                }
                // 第二次相遇
                return second;
            }
        }
        return 0;
    }
};

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210207143905532.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
> 时间复杂度： O(n) ,线性的遍历
> 总结： 利用上面的图，x + (y + z ) * n + y = 2 (x + y)知道等式就很好办了。
