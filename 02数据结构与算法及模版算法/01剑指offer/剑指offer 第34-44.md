@[TOC]
## 二叉搜索树的后续遍历序列(易)

> 输入一个整数数组，**判断该数组是不是某二叉搜索树的后序遍历**的结果。
> 
> 如果是则返回true，否则返回false。
> 
> 假设输入的数组的任意两个数字都互不相同。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221201612961.png)

```cpp
class Solution {
public:
    vector<int> seq;
    bool verifySequenceOfBST(vector<int> sequence) {
        // 4, 8, 6, 12, 16, 14, 10
        // 根据题目要求： 是二叉搜索树， 根节点是比左子树大， 比右子树小的。
        // 因为： 后续遍历是： 左右根子树遍历顺序
        // 第一遍： 找出10 是根节点， 然后将前面的数组，比10小的分成左子树， 比10大的就是右子树的内容
        // 4, 8 ,6 是左子树， 12 ，16 ，14 是右子树
        // 然后 6 是左子树的根节点，  14 是右子树的根节点，以此类推
        // 4 是左节点， 8 是右节点， 等等。
        seq = sequence;
        int l = 0, r = seq.size() - 1;
        return dfs(l , r);
    }

    bool dfs(int l, int r)
    {
        if(l >= r ) return true;
        int k = l;    // 这里的k 应该是l 表示左边的
        while( l < r && seq[k] < seq[r]) k++;   // 运行完了 k 应该是 右子树的第一个位置

        for(int i= k; i<r; i++)
        {
            if(seq[i] <= seq[r])  return false;
        }
        return dfs(l, k-1) && dfs(k, r-1);     // 递归求， 只有左边和右边的同时满足这种情况， 此时的数组才算是符合题意的数组
    }
};
```

## 二叉树中和为某一值的序列

> 输入一棵二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。
> 
>从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221201502270.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

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
    vector<vector<int>> re;
    vector<int> path;

    vector<vector<int>> findPath(TreeNode* root, int sum) {
        // 思路： 此题只需要将二叉树所有的路径遍历一遍就行了， 如果满足该路径下的和 = sum ,记录下来.
        // 小细节： 用减法，可以减少一个求和的变量
        dfs(root, sum);
        return re;
    }

    void dfs(TreeNode* root, int sum)
    {
        if(!root) return ;  // 节点为空，直接返回
        sum -= root->val;
        path.push_back(root->val);
        if(!root->left && !root->right && !sum) re.push_back(path);   // 此时的节点左子树，右子树均没有，且sum已经减到0了， 就说明这条路径是所求的，加入re数组中
        dfs(root->left,sum), dfs(root->right, sum);
        path.pop_back();  // 当路径走完后，path里面的数据需要恢复原状
    }
};
```

## 复杂链表的复制

> 请实现一个函数可以复制一个复杂链表。
> 
> 在复杂链表中，每个结点除了有一个指针指向下一个结点外，还有一个额外的指针指向链表中的任意结点或者null。


```cpp
/**
 * Definition for singly-linked list with a random pointer.
 * struct ListNode {
 *     int val;
 *     ListNode *next, *random;
 *     ListNode(int x) : val(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    // 思路： 先遍历节点，将每个节点赋值一份，放入当前节点的后面
    // 然后修改放入节点的random指针， 一定要对应好
    // 最后将新建的赋值链表节点按照顺序输出出来

    ListNode *copyRandomList(ListNode *head) {
        for(auto p = head; p; )
        {
            auto newNode = new ListNode(p->val);
            auto next = p->next; // 保存当前p节点的next节点
            p->next = newNode;   // 将p节点的复制出来
            newNode->next = next; // 将newNode 添加其中
            p = next;  // 这里只能是将之前的p的next节点给p, 不能是p = p->next;
        }
        for(auto p = head; p; p = p->next->next)  // 因为每两个节点中间增加了一个节点，所以遍历的时候需要隔一个遍历
        {
            if(p->random)   // 是将复制的节点的random指针和之前节点的random指针弄成对应相等的
                p->next->random = p->random->next;
        }

        auto dummy = new ListNode(-1);
        auto cur = dummy;
        for(auto p = head; p; p = p->next )   // 这几个next 指针需要好好分析
        {
            cur->next =  p->next;   // 为什么是p->next ,因为我们要的是新建的赋值节点的链表， 所以是next节点
            cur = cur->next; 
            //p = p->next;   // 这里会报错，这里的分离是将我们新建立的所有节点分离，这个代码是分离的原链表
            p->next = p->next->next;  // 这个代码是分离的我们新建的赋值链表是符合要求的，上面的就是原链表，就不符合要求了
        }
        return dummy->next;
    }
};
```

## 二叉搜索树与双向链表（中等）

> 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。
> 
> 要求不能创建任何新的结点，只能调整树中结点指针的指向。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221200813278.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

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
    TreeNode* convert(TreeNode* root) {
        if(!root) return nullptr;
        auto lside = dfs(root);
        return lside.first;   // 返回最小值
    }

    // 返回值是pair， first是表示左子树的最小值， second是表示右子树的最大值
    pair<TreeNode*, TreeNode*> dfs(TreeNode* root)
    { 
        //  如果root的左子树和右子树 都没有， 则直接返回root，
        if(!root->left && !root->right) return {root, root}; 
        if(root->left && root->right)     //  如果root的左右子树都存在
        {
            auto lside = dfs(root->left), rside = dfs(root->right);
            lside.second->right = root, root->left = lside.second;
            root->right = rside.first, rside.first->left = root;
            return {lside.first, rside.second};
        }
        else if(root->left)
        {
            auto lside = dfs(root->left);
            lside.second->right = root, root->left = lside.second;
            return {lside.first, root};
        }
        else if(root->right)
        {
            auto rside = dfs(root->right);
            root->right = rside.first, rside.first->left = root;
            return {root, rside.second};
        }
    }
};
```


## 序列化二叉树（难）

> 请实现两个函数，分别用来序列化和反序列化二叉树。
> 
> 您需要确保二叉树可以序列化为字符串，并且可以将此字符串反序列化为原始树结构。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221195831481.png)

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

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        
    }
};
```
下面的代码是不考虑正负号的

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

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string re;
        dfs_s(root, re);
        return re;
    }

    void dfs_s(TreeNode* root, string& s)
    {
        if(!root) 
        {
            s += "null ";    // 这里的null加上空格
            return;
        }
        s += to_string(root->val) + ' ';
        dfs_s(root->left, s);
        dfs_s(root->right, s);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int u = 0;
        return dfs_d(data, u);
    }

    TreeNode* dfs_d(string data, int& u)
    {
        if(u == data.size()) return NULL;
        int k = u;
        while(data[k] != ' ') k ++;
        if(data[u] == 'n')
        {
            u = k + 1;
            return NULL;
        }
        int val = 0;
        for(int i = u; i< k; i++) val = val * 10 + data[i] - '0';   // 将字符串按照位数转换成数字

        u = k + 1;
        auto root = new TreeNode(val);
        root->left = dfs_d(data, u);
        root->right = dfs_d(data, u);
        return root;
    }
};
```

下面是考虑正负号的

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

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string re;
        dfs_s(root, re);
        return re;
    }

    void dfs_s(TreeNode* root, string& s)
    {
        if(!root) 
        {
            s += "null ";    // 这里的null加上空格
            return;
        }
        s += to_string(root->val) + ' ';
        dfs_s(root->left, s);
        dfs_s(root->right, s);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int u = 0;
        return dfs_d(data, u);
    }

    TreeNode* dfs_d(string data, int& u)
    {
        if(u == data.size()) return NULL;
        int k = u;
        while(data[k] != ' ') k ++;
        if(data[u] == 'n')
        {
            u = k + 1;
            return NULL;
        }
        int val = 0;
        if(data[u] == '-')
        {
            for(int i = u + 1; i<k ;i ++) val = val * 10 + data[i] - '0';
            val = -val;
        }
        else
            for(int i = u; i< k; i++) val = val * 10 + data[i] - '0';   // 将字符串按照位数转换成数字

        u = k + 1;
        auto root = new TreeNode(val);
        root->left = dfs_d(data, u);
        root->right = dfs_d(data, u);
        return root;
    }
};
```


## 数字排列 （dfs + 二进制代替数字是否存在）

> 这里是引用
> 输入一组数字（可能包含重复数字），输出其所有的排列方式。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210220234155740.png)

经典的dfs操作，需要记住模版， 这题还利用**二进制代替哪些位置是空的的特点**
```cpp
class Solution {
public:

    // 如果当中有重复的数字 ，怎么办，
    // 先排序
    // 规定 有重复的数字的话，后面的一个数字只能放在前面的数字后面    

    // 回溯法：时间复杂度为 O(n!)
    // 利用重复数字的相对位置不变
    vector<vector<int>> ans;
    vector<int> path;
    vector<vector<int>> permutation(vector<int>& nums) {
        path.resize(nums.size());
        sort(nums.begin(), nums.end());
// (三个0 的参数意思)： 从0开始； 二进制表示哪些数是空的（比如5的二进制哪一位是否存在）；上一个数的位置在哪
        dfs(nums, 0, 0, 0);    
        return ans;
    }
    void dfs(vector<int>& nums, int u ,int start, int state)
    {
        if(u == nums.size())
        {
            ans.push_back(path);
            return;
        }
        if(!u || nums[u] != nums[u -1]) start = 0;   // 设置相对位置
        for(int i= start; i<nums.size(); i++)
            if(!(state >> i & 1))   // 检查第i位是否是1，如果为0就可以操作
            {
                path[i] = nums[u];
                dfs(nums, u + 1, i + 1, state +(1 << i)) ;  // state +(1 << i)  从0 -> 1了
            }
    }
};
```

## 数组中出现次数超过一半的数字（巧妙利用出现次数大于其他数字之和）

> 数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
> 
> 假设数组非空，并且一定存在满足条件的数字。
> 
> 思考题：
> 
> 假设要求只能使用 O(n) 的时间和额外 O(1) 的空间，该怎么做呢？
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210220233822583.png)

```cpp
class Solution {
public:
    // 因为sort 时间复杂度为O(nlogn), 所以不符合题意
    int moreThanHalfNum_Solution(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() /2];
    }
};
```
主要利用了这个数字最后的数量肯定是大于其他所有数字的出现次数之和的。
```cpp
class Solution {
public:
    int moreThanHalfNum_Solution(vector<int>& nums) {
        // 时间复杂度 O(n)，空间复杂度O(1)
        // 利用了在数组中出现次数超过数组的一半， 弄清楚下面2点就行了
        // 1. 除它之外所有元素出现的次数都没有它多
        // 2. 前面的数字抵消之后，直接换下一个数字，因为被抵消的数字肯定不是答案，所以直接返回val
        int cnt = 0, val = -1;
        for(auto x : nums)
        {
            if(!cnt)  val = x, cnt = 1;
            else
            {
                if(x == val) cnt ++;
                else cnt --;
            }
        }
        return val;
    }
};
```


## 最小的k个数 （直接排序和 利用大根堆在反转）

> 输入n个整数，找出其中最小的k个数。
> 
> 注意：
> 
> 数据保证k一定小于等于输入数组的长度;
>  输出数组内元素请按从小到大顺序排序;
![>](https://img-blog.csdnimg.cn/20210220233552635.png)
  这题有几种解法： 1. 直接进行快速排序，然后在找。2. 利用大根堆，在进行反转。
  

```cpp
class Solution {
public:
    vector<int> re;
    vector<int> getLeastNumbers_Solution(vector<int> input, int k) {

        //// 解法 1 ， 直接利用快速排序， 时间复杂度为快排的时间复杂度O（nlogn）
        //sort(input.begin(), input.end());
        //
        //for(int i=0; i<k; i++)
        //{
        //    re.push_back(input[i]);
        //}
        //return re;

        // 解法 2 ： 利用大根堆， 堆里直接存储k个数， 直接push进去数， 当数据大于k个后， 直接pop掉最前面的数， 因为最前面的数不是前k个小的数子了
        // 然后输出数组中， 因为是大根堆， 需要反转一下
        priority_queue<int> heap;
        for(auto i : input)
        {
            heap.push(i);
            if(heap.size() > k ) heap.pop();
        }

        vector<int> re;
        for(int i=0; i<k; i++)
            re.push_back(heap.top()), heap.pop();
        reverse(re.begin(), re.end());

        return re;
    }
};
```

## 数据流中的中位数（两个堆维护，值得反复看）

> 如何得到一个数据流中的中位数？
> 
> 如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
> 
> 如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。
![>](https://img-blog.csdnimg.cn/20210220233255427.png)
 这题用两个堆进行维护，处理的特别巧妙，值得反复看！！！
 

```cpp
class Solution {
public:
    // 思路： 用两个堆了来维护， 一个大根堆（堆顶是最大的元素）， 一个小根堆（堆顶是最小的元素），想想小根堆在上面
    // 需要做成小根堆里面的元素 都比大根堆的元素要大， 这是求中位数就好求。 约定是基数的话，下面的堆（大根堆多1），直接返回小根堆的top()就行
    // 如果数据是偶数的话， 直接返回两个堆中的top 的平均数就可。
    // 如何维护呢？
    // 当每遍历数据中的数据时候， 直接插入下面的堆（大根堆），然后进行下面的判断  1. 逆序（应交换）  2. 多2 （转移）
    // 1. 如果下面的堆（大根堆）的top元素跟上面的堆（小根堆）是逆序关系， 这是就说明这个元素本应该是插到上面的小根堆的， 直接交换两个堆顶。
    // 2. 如果交换后差生了下面的堆的元素比上面的元素数据多了2个（应该最多只能多一个），说明下面的数据top() 应该是上面（小根堆的元素），直接给它就行。

    priority_queue<int> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap;


    void insert(int num){
        max_heap.push(num);   // 每次的元素直接插入大根堆
        if(min_heap.size() && max_heap.top() > min_heap.top())   //(需要交换)  // 这里需要判断小根堆里有没有元素
        {
            auto min = min_heap.top(), max = max_heap.top();
            min_heap.pop(), max_heap.pop();
            min_heap.push(max), max_heap.push(min);
        }
        if(max_heap.size() > min_heap.size() + 1)   // 大根堆里面的元素多， 需要转移  (一定不能弄反)
        {
            min_heap.push(max_heap.top()) , max_heap.pop();
        }
    }

    double getMedian(){
        if(max_heap.size() + min_heap.size() & 1) return max_heap.top();   // 判断两个堆中的元素数量是否是基数
        else return (max_heap.top() + min_heap.top()) / 2.0;
    }
};
```

## 连续子数组的最大和

> 输入一个 非空 整型数组，数组里的数可能为正，也可能为负。
> 
> 数组中一个或连续的多个整数组成一个子数组。
> 
> 求所有子数组的和的最大值。
> 
> 要求时间复杂度为O(n)。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210220233144322.png)
这是一道特殊的动态规划，看下面的解法

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int re = INT_MIN, s = 0; // 这题是特殊的动态规划， 只需要一个变量就可以表示 s表示前一个数结尾的最大子数组的最大值
        for(auto x : nums)
        {
            if(s < 0) s = 0;   // 这里分析的是 s = 0; 不是x = 0
            s += x;
            re = max(re, s);
        }
        return re;
    }
};
```




## 从1到n整数中1出现的次数

> 输入一个整数n，求从1到n这n个整数的十进制表示中1出现的次数。
例如输入12，从1到12这些整数中包含“1”的数字有1，10，11和12，其中“1”一共出现了5次。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210220232948880.png)
下面的解法是错误示范只能通过小部分。
```cpp
class Solution {
public:
    // 直接利用遍历数字的方法， 但是会超时
    int get(int i)
    {
        int re = 0;
        while(i)
        {
            if(i%10 == 1) re ++;
            i /= 10;
        }
        return re;
    }

    int numberOf1Between1AndN_Solution(int n) {
        int re = 0;
        for(int i= 1;i<=n; i++)
        {
            re += get(i);
        }
        return re;
    }
};
```

应该用下面的解法：

```cpp
class Solution {
public:
     /*
     abcdef 求c位的1的个数， 如果c位不是1 的话，就是0个了

     1. 左边是00- (ab-1)  : 右边可以是 000-999     ===>     ab* 1000 个
     2. 左边是ab，  c = 0    ； 0个     // 这三个情况是只存在一种的
                    c = 1    : 0 - def  个         ===>    def + 1 个
                    c > 1    : 0 -999 个           ===>     1000个
        只要考虑 1 ，2.2 2.3这三种情况
     */
    int numberOf1Between1AndN_Solution(int n) {
        if(!n) return 0;
        vector<int> num;   // 保存n的每位数
        while(n) num.push_back(n % 10), n /= 10;

        int re =0;
        for(int i=num.size() - 1; i>=0; i--)   // 从n的数字最高位开始
        {
            auto left = 0, right = 0, t = 1;  // t 表示后面有几位
            for(int j = num.size() - 1; j> i; j--) left = left * 10 + num[j];
            for(int j = i - 1; j>=0; j--) right = right * 10 + num[j], t *= 10;
            re += left * t;    // 第一种情况
            // num[i] == 0 就表示没有， 因为是只求这一位的1的个数
            if(num[i] == 1) re += right + 1;   // 下面两种是2的其中一种情况
            else if(num[i] > 1) re += t;
        }
        return re;
    }  
};
```

