@[TOC]
## 数字序列中某一位的数字

> 数字以0123456789101112131415…的格式序列化到一个字符序列中。
> 
> 在这个序列中，第5位（从0开始计数）是5，第13位是1，第19位是4，等等。
> 
> 请写一个函数求任意位对应的数字。
![>](https://img-blog.csdnimg.cn/20210221215722371.png)
 

```cpp
class Solution {
public:
    // 思路：如果直接遍历的话，是n次，在时间上会超时，
    // 这是需要一个更加高效的算法，
    // 例如找出1000位数： 先判断是属于几位数， 1位数10个， 2位数90个，3位数900个
    // 这里利用1000 - 9 - 90 - 900 < 0 说明1000位数是属于3位数的，
    // 1. 先判断这个数字在第几位数 
    // 2. 找出是该位数的哪位数 1000-10*1- 90*2 = 870   870/3 = 290  所以对应100 + 290 - 1 = 389
    // 3. 余数是0 ，就是 389的最后一位 9

    // 确定是几位数  n -10 -90*2-900*3
    // 确定几位数的哪一个数： 100+ 256 - 1；
    // 属于那个书的第几位： 看余数
    // 时间复杂度： O(logn)

    // 向上取整： 因为C++ 中只有向下取整 n/i ; 向上取整可以表示为 （n + i -1）/i;

    int digitAtIndex(int n) {
        // i 表示几位数，从1位数开始
        // s 表示该位数的个数  i*s 表示该位数占了多个位
        // base 表示该位数的起始值 
        long long i = 1, s = 9, base = 1;
        while(n > i* s)
        {
            n -= i*s;
            i ++;
            s*= 10;
            base *= 10;
        }

        int num  = base + (n+i-1)/i -1;  // 求是哪个数字，
        int r = n%i? n%i : i;   // 求余数， 不是0 的话， 直接是余数， 是0代表整除： 就是i表示这个数字的最后一位

        // 12561 的第二位就是将后面的三位数删掉就行
        for(int j = 0; j< i-r; j++) num /= 10;  // 删除后面的位数

        return num % 10;
    }
};
```

## 把数组排成最小的数

> 输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。
> 
> 例如输入数组[3, 32, 321]，则打印出这3个数字能排成的最小数字321323。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221215528674.png)

```cpp
class Solution {
public:
    static bool cmp(int a, int b)   // 这里必须是静态函数才能行
    {
        string sa = to_string(a), sb = to_string(b);
        return sa+ sb < sb + sa;
    }

    string printMinNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), cmp);
        string re;
        for(auto x : nums)
        {
            re += to_string(x);   // 这里也要转化成string
        }

        return re;
    }
};
```

## 把数字翻译成字符串(类似爬楼梯的dp问题)

> 给定一个数字，我们按照如下规则把它翻译为字符串：
> 
> 0翻译成”a”，1翻译成”b”，……，11翻译成”l”，……，25翻译成”z”。
> 
> 一个数字可能有多个翻译。例如12258有5种不同的翻译，它们分别是”bccfi”、”bwfi”、”bczi”、”mcfi”和”mzi”。
> 
> 请编程实现一个函数用来计算一个数字有多少种不同的翻译方法。
![>](https://img-blog.csdnimg.cn/20210221215410717.png)
 

```cpp
class Solution {
public:
    // 类比： 爬楼梯(dp)
    // dp[n] = dp[n-1] + dp[n-2] 代表走到最后一个字符 有多少翻译方法？
    // 1. 最后一个字符是1个字母作为翻译的话dp[n] = dp[n-1]
    // 2. 最后一个字符和前一个字符组合翻译成的话 dp[n-2]种，而这种是有条件的当前一个字符是0的话，
    // 不能被组合翻译, 只有 x >=10 && x <= 25 才符合条件
    // 所以总共的个数为 dp[n]; n 代表多少个字符

    int getTranslationCount(string s) {
        // if(s.empty()) return 0;
        int n = s.size();
        vector<int> dp(n);
        dp[0] = 1;
        for(int i =1; i<=n; i++)
        {
            dp[i] = dp[i-1];
            int k = (i>=2) * (s[i-2]-'0') * 10 + s[i-1]-'0';  // 需要保证有2位
            if( k >= 10 && k <= 25) dp[i] += dp[i-2];
        }
        return dp[n];
    }
};
```

## 礼物的最大价值（矩阵中的简单dp问题）

> 在一个m×n的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于0）。
> 
> 你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格直到到达棋盘的右下角。
> 
> 给定一个棋盘及其上面的礼物，请计算你最多能拿到多少价值的礼物？
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221215256105.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

```cpp
class Solution {
public:
    //　不能往回走　经典的 dp 问题
    // 因为每个格子只有两种状态进来（最后第二步走向最后第一步 只有向右或者向下）
    // dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + vlaue[i][j]  最后价值max = dp[n][m]

    int getMaxValue(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> f(n + 1 , vector<int>(m + 1));   // 因为从1开始算， 这里加 1 
        for(int i = 1; i<=n; i++ )   //从1开始算， 不用处理边界情况
            for(int j= 1; j<=m; j++)
                // grid[i-1][j-1] , 这里偏移了一位 实际上等于grid[i][j]的
                f[i][j] = max(f[i-1][j], f[i][j-1]) + grid[i-1][j-1]; 

        return f[n][m];
    }
};
```


## 最长不含重复的子字符串(子字符串，不能用set)

> 请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。
> 
> 假设字符串中只包含从’a’到’z’的字符。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221214936556.png)

```cpp
class Solution {
public:
    // 子串： 一定是连续的
    // 子序列： 按照序列的顺序就行了， 可以不连续 

    // 1. 暴力做法， 用 j 先遍历一遍， 然后i 从j 往前遍历，存到hash表中，这样的时间复杂度为O(n^2)
    // 2. 遍历一遍的优化做法： 用j遍历一遍，存进hash表中，如果有元素大于1 ，说明这里面存在重复元素了
    // 这里i从前面走，当s[i]出现的次数等于1时，说明这个元素不是重复元素，需要继续向后遍历 ，
    // (这些不是重复元素但是在前面的元素都要删除)
    // 直到s[i]出现的次数不是1, 说明下一个元素就是重复元素， 这是需要删除下一个元素，
    // 然后计算这是的元素个数 j - i + 1.

    int longestSubstringWithoutDuplication(string s) {
        unordered_map<char, int> cnt;
        int re = 0;
        // 书写要点： 尽量不在判断里面加上 i++ , while(cnt[s[i]] == 1) 不要写成 while(cnt[s[i++]] == 1)
        for(int i =0, j = 0; j < s.size(); j ++)    // 用j遍历一遍，
        {
            if( ++ cnt[s[j]] > 1)   // 将每个元素都存进hash表中， > 1 说明有重复元素了
            {
                while(cnt[s[i]] == 1)   // 需要删除前面的不是重复元素 找到重复元素的前一位退出，
                    cnt[s[i ++]] --;  // 删除前面不重复的元素，同时i向后移位
                cnt[s[i++]] --;   // 这里的cnt[s[i]] == 2 说明这个元素重复了， 需要删除 ，然后i向后移一位
            }
            re = max(re, j - i + 1);    //计算每次不重复的长度
        }
        return re;
    }
};
```


## 丑数
> 我们把只包含质因子2、3和5的数称作丑数（Ugly Number）。
> 
> 例如6、8都是丑数，但14不是，因为它包含质因子7。
> 
> 求第n个丑数的值。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221203040457.png)

```cpp
class Solution {
public:

    // 1, 2,3,4,5,6,8,9,10,  （包含除了2,3,5之内的质因子）
    // 7, 11 ，13， 14（不是）包含7 质因子， 11 ， 13 也是质因子。
    /*

    1 2 3 4 5 6 7 8 9 10
    i j k = 0;
    第一次循环： v中有1，2，t = 2; i = 1，j = k = 0;
    第二次循环： v中有1,2,3  t = 3; i = 1, j =1 k = 0;
    第三次循环： v中有1,2,3,4 t = 4; i = 2,j =1, k = 0;
                 v中有1,2,3,4,5 t = 5 i = 2，j =1, k =1;
                 v中有1,2,3,4,5,6 t = 6, i =3, j =2,k=1;   // 这里有重复的
                 v中有1,2,3,4,5,6，8， t = 8, i = 4， j = 2,k=1;  //这里就剔除了7 
    */


    int getUglyNumber(int n) {
        vector<int> v;
        v.push_back(1);
        int i= 0, j =0, k = 0;
        while(-- n)   // 因为找第n个丑数，第一个已经找到了， 现在只需要找n-1个，  while(n--) 代表循环n次
        {
            int t = min(v[i] * 2, min(v[j] * 3, v[k] * 5));
            v.push_back(t);
            if(v[i] * 2 == t) i ++;
            if(v[j] * 3 == t) j ++;
            if(v[k] * 5 == t) k ++;
        }
        return v.back();
    }
};
```

## 字符串中第一个只出现一次的字符

> 在字符串中找出第一个只出现一次的字符。
> 
> 如输入"abaccdeff"，则输出b。
> 
> 如果字符串中不存在只出现一次的字符，返回#字符。
![在这里插入图片描述](https://img-blog.csdnimg.cn/2021022120294671.png)

```cpp
class Solution {
public:
    // 直接用hash 表， 存储每个char的出现次数
    char firstNotRepeatingChar(string s) {
        char re = '#';
        unordered_map<char, int> map;
        for(int i=0; i<s.size(); i++ ) 
        {
            map[s[i]] ++ ;
        }
        for(int i=0; i< s.size(); i++)
        {
            if(map[s[i]] == 1) 
                return s[i];
        }
        return re;
    }
};
```

## 字符流中第一个只出现一次的字符

> 请实现一个函数用来找出字符流中第一个只出现一次的字符。
> 
> 例如，当从字符流中只读出前两个字符”go”时，第一个只出现一次的字符是’g’。
> 
> 当从该字符流中读出前六个字符”google”时，第一个只出现一次的字符是’l’。
> 
> 如果当前字符流没有存在出现一次的字符，返回#字符。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221202641128.png)

```cpp
class Solution{
public:
    //Insert one char from stringstream
    void insert(char ch){
        
    }
    //return the first appearence once char in current stringstream
    char firstAppearingOnce(){
        
    }
};
```
两种方法： 


```cpp
class Solution{
public:
    string s;
    unordered_map<char, int> map;
    //Insert one char from stringstream
    void insert(char ch){
        s += ch;
        map[ch] ++ ;
    }
    //return the first appearence once char in current stringstream
    char firstAppearingOnce(){
        for(int i=0; i < s.size(); i++)
            if(map[s[i]] == 1)   
                return s[i];
        return '#';
    }
};
```

```cpp
class Solution{
public:
    // 双指针和单调队列 
    // 队列本质上是一个双指针
    queue<char> q;
    unordered_map<char, int> map;

    //Insert one char from stringstream
    void insert(char ch){
        map[ch] ++;
        if(map[ch] > 1)
        {
            while(q.size() && map[q.front()] > 1) q.pop();
        }
        else
            q.push(ch);
    }
    //return the first appearence once char in current stringstream
    char firstAppearingOnce(){
        if(q.empty()) return '#';
        else
        return q.front();
    }
};
```





## 数组中的逆序对（归并排序）

> 在数组中的两个数字如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。
> 
> 输入一个数组，求出这个数组中的逆序对的总数。
![>](https://img-blog.csdnimg.cn/20210221202440992.png)
 

```cpp
class Solution {
public:
    // 这里就是归并思路（m模版加以应用）
    int merge(vector<int>& nums, int l ,int r)
    {
        if(l >= r) return 0;  // 如果只有一个元素

        int mid = l + r >> 1;
        int re = merge(nums, l , mid) + merge(nums, mid + 1, r);
        int i = l, j = mid + 1;
        vector<int> tmp;
        while(i<= mid  && j <= r )
        {
            if(nums[i] <= nums[j] )  tmp.push_back(nums[i ++]);
            else 
            {
                tmp.push_back(nums[j++]);       // 必须是这个情况谁才是逆序对， 这样才计算结果+1
                re += mid - i + 1;              // 加上小于的区间数字的数量
            }
        }
        while(i <= mid) tmp.push_back(nums[i++]);
        while(j <= r) tmp.push_back(nums[j++]);
        i = l;       // 按照左边写入数组
        for(auto x : tmp) nums[i ++] = x;
        return re;
    }




    int inversePairs(vector<int>& nums) {
        // 暴力
        // int re = 0;
        // for(int i = 0; i<nums.size(); i++)
        //     for(int j = i+1; j<nums.size(); j++)
        //         if(nums[i] > nums[j] ) re ++;
        // return re;

        return merge(nums, 0, nums.size() -1 );

    }
};
```


## 两个链表的第一个公共结点（链表经典题目、双指针题型）

> 输入两个链表，找出它们的第一个公共结点。
> 
> 当不存在公共节点时，返回空节点。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221202301757.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

```cpp
**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:

    // 题目输入： 第二个链表中的插入到公共节点前面， 
    //[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]
    //[1, 2, 3, 4, 5, 6, 7]
    //10
    // 应该输出 10
    ListNode *findFirstCommonNode(ListNode *headA, ListNode *headB) {
        auto p = headA, q = headB;
        while(p != q)
        {
            if(p) p = p->next;
            else p = headB;
            if(q) q = q->next;
            else q = headA;
        }
        return q;   // 当相遇后， 返回q或者q都行

    }
};
```


## 数字在排序数组中出现的次数（利用二分查找性质）

> 统计一个数字在排序数组中出现的次数。
> 
> 例如输入排序数组[1, 2, 3, 3, 3, 3, 4, 5]和数字3，由于3在这个数组中出现了4次，因此输出4。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221202138664.png)

```cpp
class Solution {
public:
    // 可以用二分求出小于k的数字位置， 然后求出大于k的数字位置
    // 但是如果用二分找的话，出现在k的前面一个数字也是重复的，这样如何考虑呢

    int getNumberOfK(vector<int>& nums , int k) {
        if(!nums.size()) return 0;

        int l = 0, r = nums.size() -1, left = 0, right = 0;
        while(l < r)
        {
            int mid = l + r >> 1;
            if(nums[mid] >=  k) r= mid;    // >= 是找的左边边界。 
            else l = mid + 1;  
        }
        left = r;   
        //cout<< l <<"  "<< r << endl;

        l = left, r = nums.size() -1;   // 可以将上面的左边边界加上，优化一点时间
        while(l < r)
        {
            int mid = l + r + 1>> 1;
            if(nums[mid] <= k ) l = mid;
            else r = mid -1;
        }
        right = r ;
        //cout<< l <<"  "<< r << endl;

        if(nums[left] != k || nums[right] != k) return 0;
        return right - left + 1;
     }
};
```

