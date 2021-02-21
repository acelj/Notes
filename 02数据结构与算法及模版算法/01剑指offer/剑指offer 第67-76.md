@[TOC]
## 滑动窗口的最大值（单调队列经典题）

> 给定一个数组和滑动窗口的大小，请找出所有滑动窗口里的最大值。
> 
> 例如，如果输入数组[2, 3, 4, 2, 6, 2, 5, 1]及滑动窗口的大小3,那么一共存在6个滑动窗口，它们的最大值分别为[4, 4, 6, 6, 6, 5]。
![>](https://img-blog.csdnimg.cn/20210221235140833.png)
 

```cpp
class Solution {
public:

    // 单调队列经典题

    vector<int> maxInWindows(vector<int>& nums, int k) {
        vector<int> re;
        deque<int> q;   // 双向队列， 前面的入队， 后面出队
        for(int i = 0; i<nums.size(); i++)
        {
            // 这里的deque 存储的是数组下标， 这个里面的back() 进来， front 出去
            // while(q.size() &&  q.front() <= i - k ) q.pop_front();  
            //while(q.size() && nums[q.back()] <= nums[i]) q.pop_back();   // 单调队列
            //q.push_back(i);
            //if(i >= k-1) re.push_back(nums[q.front()]);

            // 从front 进， back 出来   ，当末尾元素下标 <= i-k 的话就是 大于窗口了， 需要删除
            while(q.size() &&  q.back() <= i - k) q.pop_back();
            //while(q.size() &&  q.front() - q.back() >=  k ) q.pop_back();  // 不能这样写， 因为需要维护单调队列
            // 如果进来的元素 根前面的front元素比较大小， 如果小的话， 可以直接出去了，
            // 因为后面进来的永远比你大， 
            while(q.size() && nums[q.front()] <= nums[i]) q.pop_front();   // 单
            // 从front前面插入元素
            q.push_front(i);
            // 当窗口等于3 时开始写入数据
            if(i >= k-1) re.push_back(nums[q.back()]);
        }
        return re;
    }
};
```

## 骰子的点数

> 将一个骰子投掷n次，获得的总点数为s，s的可能范围为n~6n。
> 
> 掷出某一点数，可能有多种掷法，例如投掷2次，掷出3点，共有[1,2],[2,1]两种掷法。
> 
> 请求出投掷n次，掷出n~6n点分别有多少种掷法。
![>](https://img-blog.csdnimg.cn/20210221234924773.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
 

```cpp
// 递归做法： 提交超时， 原因: 递归太费时间，需要考虑更加高效的动态规划做法。
class Solution {
public:
    // 动态规划题目：
    // dp[i][j] 表示的是: 

    // 递归
    vector<int> numberOfDice(int n) {
       vector<int> re;
       for(int i = n; i<= 6 * n; i++) 
            re.push_back(dfs(n, i));
        return re;
    }

    int dfs(int n, int sum)
    {
        if(sum < 0) return 0;
        // 如果最后一次已经等于0次了， sum==0 此时应该刚刚好，这是返回1， 
        // 如果sum还有值， 就说明不是这种方案， 应该返回0
        if(n == 0) return !sum;   
        int re = 0;
        for(int i=1; i<=6; i++)
            re += dfs(n-1, sum - i);
        return re;
    }
};
```
不超时的做法：

```cpp
class Solution {
public:
    vector<int> numberOfDice(int n) {
        vector<vector<int>> f(n + 1, vector<int>(6 * n + 1, 0));
        f[0][0] = 1;
        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= i * 6; j ++ )
                for (int k = 1; k <= 6; k ++ )
                    if (j >= k)
                        f[i][j] += f[i - 1][j - k];
        return vector<int>(f[n].begin() + n, f[n].end());
    }
};
```

## 扑克牌的顺子

> 从扑克牌中随机抽5张牌，判断是不是一个顺子，即这5张牌是不是连续的。
> 
> 2～10为数字本身，A为1，J为11，Q为12，K为13，大小王可以看做任意数字。
> 
> 为了方便，大小王均以0来表示，并且假设这副牌中大小王均有两张。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221234751769.png)

```cpp
class Solution {
public:
    // 排序， 去重， 计算
    bool isContinuous( vector<int> nums ) {
        if(nums.empty()) return false;
        sort(nums.begin(), nums.end());
        int k =0;
        while(!nums[k]) k ++;
        for(int i=k + 1; i<nums.size(); i++)
        {
            if(nums[i] - nums[i-1] == 0) return false;
        }
        // 相差大于4 就不是顺子
        //return nums[4] -  nums[k] <= 4;  
        return nums.back() -  nums[k] <= 4;  
    }
};
```

## 圆圈中最后剩下的数字（约瑟夫环问题）

> 0, 1, …, n-1这n个数字(n>0)排成一个圆圈，从数字0开始每次从这个圆圈里删除第m个数字。
> 
> 求出这个圆圈里剩下的最后一个数字。
![>](https://img-blog.csdnimg.cn/20210221234640576.png)
 

```cpp
class Solution {
public:

    // 约瑟夫环： 
    // 1. 用递归来做
    // 原数组：                     0, 1, 2, 3, 4, 5, ...  有n个
    // 删除第m个数（序号是m-）：    m, m+1, m+2,...
    // f(n, m) = (f(n-1) + m )% n    f(n,m) 表示答案，n,m 是根据题目的意思， 公式
    // 2. 迭代
    // 当大于等于2 是， 每次循环就可以 （）
    //int lastRemaining(int n, int m){
    //    if(n== 1) return 0;
    //    return (lastRemaining(n-1, m) + m) % n;
    //}

    // 将上面用迭代的思想解答
    // f(n, m) = (f(n-1) + m )% n
    // f(1,m) = 0 f(2,m) = (f(1) + m) % 2
    // f(3,m) = (f(2,m) + m) % 3
    int lastRemaining(int n, int m){
        if(n==1) return 0;
        int last = 0;
        for(int i=1; i<=n; i++)
        {
            last = (last + m) % i;  // 为什么%i, 在上面递归的解法实质上是一样的。
        }
        return last;
    }
};
```

## 股票的最大利润（贪心）

> 假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖 一次 该股票可能获得的利润是多少？
> 
> 例如一只股票在某些时间节点的价格为[9, 11, 8, 5, 7, 12, 16, 14]。
> 
> 如果我们能在价格为5的时候买入并在价格为16时卖出，则能收获最大的利润11。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221234520281.png)

```cpp
class Solution {
public:

    // 如何枚举所有天数的最大利润
    // 1. 可以用堆存放之前的最小值
    // 2. 可以直接用变量
    // int maxDiff(vector<int>& nums) {
    //     if(nums.size() == 1) return 0;
    //     priority_queue<int, vector<int>, greater<int>> heap;
    //     int re = 0;
    //     for(auto x : nums)
    //     {
    //         heap.push(x);
    //         if(heap.size() > 1)
    //         {
    //             re = max(re, x - heap.top());
    //         }
    //     }
    //     return re>0? re : 0;
    // }
    // 2. 
    int maxDiff(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        int re =0;
        for(int i=1, minv = nums[0]; i<nums.size(); i++)
        {
            re = max(re, nums[i] - minv);
            minv = min(nums[i], minv);
        }
        return re;
    }

};
```

## 求1+2+...+n

> 求1+2+…+n,要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。
![>](https://img-blog.csdnimg.cn/20210221234409990.png)

```cpp
class Solution {
public:
    int getSum(int n) {
        //  利用递归加短路实现题目要求
        int re = n;
        (n > 0) && (re += getSum(n-1));
        return re;
    }
};
```

 

## 不用加减乘除做加法

> 写一个函数，求两个整数之和，要求在函数体内不得使用＋、－、×、÷ 四则运算符号。
![>](https://img-blog.csdnimg.cn/20210221234313909.png)

```cpp
class Solution {
public:

    // 要考虑计算机中是怎么计算的
    // 与 或 非 三种计算   &  |  ~     ^ (异或是与门和或门实现的)
    // 那计算机中的+ 是如何实现的呢？

    // A + B 分为2个部分，A^B是不进位加法，(A&B) << 1是进位，二者相加就起到了相同的作用。
    // 因为A + B = A^B + ((A&B) << 1)，所以说 还是会用到加号+，对此我们的解决方案是 使用
    // 一个while()循环，不断迭代赋值，将 异或的结果和进位的结果分别变成a和b，因为b不断左移，
    // 所以总有一天会变成0，这时候while就跳出来。答案一直存储在a里面，也就是异或(不进位加法)中，
    // 最后进位b=0，a没有必要进位了，答案就是最后的a。


    // 同样二进制加法也一样：

    // 1、两个整数做异或^，得到各位相加不进位的运算结果；

    // 2、两个整数做与&，然后再左移一位，即得到进位的运算结果；

    // 3、将上面两个结果相加，即重复步骤1,2，直至进位的运算结果为0；
    // 关键就是这个循环是怎么退出的，退出的条件是什么，怎么去分析？
    int add(int num1, int num2){
        while(num2)   // 这里必须是num2
        {
            int sum = num1 ^ num2;
            int carry = (num1 & num2) << 1;  // 这里必须加上（）  carry 表示进位的数
            num1 = sum;             // num1 sum 是答案
            num2 = carry;
        }
        return num1;
    }
};
```

 

## 构建乘积数组

> 给定一个数组A[0, 1, …, n-1]，请构建一个数组B[0, 1, …, n-1]，其中B中的元素B[i]=A[0]×A[1]×…
> ×A[i-1]×A[i+1]×…×A[n-1]。
![>](https://img-blog.csdnimg.cn/20210221234217776.png)
 

```cpp
class Solution {
public:

    // 因为返回的是vector<int> 说明数值都是int的， 不需要考虑溢出的
    // 难点： 就是只能使用常数空间  只能开一个数组 
    // 

    // vector<int> multiply(const vector<int>& A) {
    //     // 循环了两次
    //     if(A.empty()) return vector<int>();
    //     int n = A.size();
    //     vector<int> re;
    //     for(int i = 0; i<n; i++)
    //     {
    //         int num = 1;
    //         for(int j = 0; j<n; j++)
    //         {
    //             if(i == j) continue;
    //             num *= A[j];
    //         }
    //         re.push_back(num);
    //     }
    //     return re;
    // }

    // 按照前后的相乘， 这个时间复杂度就对比上面就降低到O(n)了
    vector<int> multiply(const vector<int>& A) {
        if(A.empty()) return vector<int>();

        int n = A.size();
        vector<int> B(n);

        for(int i=0, p = 1; i<n; i++)
        {
            B[i] = p;    // 因为p 是后乘的，所以B中是不包括A[i]的
            p *= A[i];
        }
        //for(int i=n-1, p = 1; i>=0; i--)
        for(int i=n-1, p = 1; ~i; i--)
        {
            B[i] *= p;   // 这个顺序不能反， P是从后面逐个保存连乘的数的， 所以不能写在下面
            p *= A[i];
        }
        return B;
    }
};
```

## 把字符串转换成整数

> 请你写一个函数StrToInt，实现把字符串转换成整数这个功能。
> 
> 当然，不能使用atoi或者其他类似的库函数。
![>](https://img-blog.csdnimg.cn/20210221234120480.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
 

```cpp
class Solution {
public:
    // str = "    + 21313";

    // 这题主要是要考虑周到
    // 1. 需要考虑前面的空格
    // 2. 需要判断前面的正负号
    // 3. 然后中间有字符的需要忽略

    int strToInt(string str) {
        int k = 0;
        while(str[k] == ' ' ) k++;

        long long num = 0;
        bool is_minus = false;   // 是否是正数
        if(str[k] == '+') k++;
        else if(str[k] == '-') k++, is_minus = true;

        while(k < str.size() && str[k] >= '0' && str[k] <= '9')
        {
            num = num * 10 + str[k] - '0';
            k++;
        }

        if(is_minus) num *= -1;   // 判断政府需要放在前面
        if(num < INT_MIN) num = INT_MIN;
        if(num > INT_MAX) num = INT_MAX;

        return num;

    }
};
```

## 树中两个结点的最低公共祖先

> 给出一个二叉树，输入两个树节点，求它们的最低公共祖先。
> 
> 一个树节点的祖先节点包括它本身。
> 
> 注意：
> 
> 输入的二叉树不为空； 
> 输入的两个节点一定不为空，且是二叉树中的节点；
![>](https://img-blog.csdnimg.cn/20210221231436825.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)
 

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    // 这个题目分两种情况
    // 1. p  q 同时属于一个tree  直接返回当前根
    // 2. p属于当前tree， q不属于当前tree 返回p

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return nullptr;  // 递归到叶子节点的，直接返回空
        // 如果当前的root节点直接是其中一个节点的话， 直接就是这两个节点的最小祖先了
        if(root == p || root == q) return root;   
        auto left = lowestCommonAncestor(root->left, p, q);
        auto right = lowestCommonAncestor(root->right, p, q);
        // 如果left right 都存在说明p,q 在两边， 这时直接返回当前的根节点就是p，q的最小祖先
        if(left && right) return root;   

        // 如果只存在左边， 则left的为根，在左边找。
        if(left) return left;
        else
        return right;

    }
};
```

