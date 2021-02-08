@[TOC]
## 找出数组中重复的数字
> 给定一个长度为 n 的整数数组 nums，数组中所有的数字都在 0∼n−1 的范围内。
数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。
请找出数组中任意一个重复的数字。
注意：如果某些数字不在 0∼n−1 的范围内，或数组中不包含重复数字，则返回 -1；
```cpp
给定 nums = [2, 3, 5, 4, 3, 2, 6, 7]。
返回 2 或 3。
```

```cpp
class Solution {
public:
    int duplicateInArray(vector<int>& nums) {
        int n = nums.size();
        for(auto i : nums)
        {
            if(i < 0 || i >= n)
            return -1;
        }
        for(int i=0; i<n; i++)
        {
        	// 将nums[i] 放到指定的位置上，交换后重复操作，直到满足条件
            while(nums[nums[i]] != nums[i]) swap(nums[nums[i]], nums[i]);
            // 说明这个nums[i]出现多次 直接返回
            if(nums[i] != i) return nums[i];
        }
        return -1;
    }
};
```

> 总结：上面的注释， 时间复杂度O（n）

##  不修改数组找出重复的数字  ？
>给定一个长度为 n+1 的数组nums，数组中所有的数均在 1∼n 的范围内，其中 n≥1。
请找出数组中任意一个重复的数，但不能修改输入的数组。

```cpp
给定 nums = [2, 3, 5, 4, 3, 2, 6, 7]。
返回 2 或 3。
如果只能使用 O(1) 的额外空间

class Solution {
public:
    int duplicateInArray(vector<int>& nums) {
        int n = nums.size();
        int l =1, r = n-1;  // 长度有n个，但是范围根据题目条件中少1
        while(l < r)
        {
            int mid = l + r >> 1;
            int s = 0;
            for(auto x : nums) s += (l <= x && mid >= x);
            if(s >= mid - l +1) r= mid;
            else l = mid + 1;
        }
        return l;
    }
};
```
>抽屉原理：n+1 个苹果放在 n 个抽屉里，那么至少有一个抽屉中会放两个苹果。
>时间复杂度： O(nlogn)
>总结： ？

## 二维数组中的查找
>在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

```cpp
输入数组：

[
  [1,2,8,9]，
  [2,4,9,12]，
  [4,7,10,13]，
  [6,8,11,15]
]
如果输入查找数值为7，则返回true，
如果输入查找数值为5，则返回false。

class Solution {
public:
    bool searchArray(vector<vector<int>> array, int t) {
        if(array.empty() || array[0].empty() ) return false;
        int i = 0, j = array[0].size() -1;
        while(i < array.size() && j>=0)
        {
            if(array[i][j] == t) return true;
            if(array[i][j] > t ) j--;
            else i++;
        }
        return false;
    }
};
```
如下图所示，x左边的数都小于等于x，x下边的数都大于等于x。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210201210233770.png)
>**时间复杂度： O(n + m)** ,每一步会排除一行或者一列，矩阵一共有 nn 行，mm 列，所以最多会进行 n+mn+m 步。所以时间复杂度是 O(n+m)O(n+m)。
> **总结：** 因此我们可以从整个矩阵的右上角开始枚举，假设当前枚举的数是 xx：
如果 xx 等于target，则说明我们找到了目标值，返回true；
如果 xx 小于target，则 xx 左边的数一定都小于target，我们可以直接排除当前一整行的数；
如果 xx 大于target，则 xx 下边的数一定都大于target，我们可以直接排序当前一整列的数；
排除一整行就是让枚举的点的横坐标加一，排除一整列就是让纵坐标减一。
当我们排除完整个矩阵后仍没有找到目标值时，就说明目标值不存在，返回false。

## 替换空格
> 请实现一个函数，把字符串中的每个空格替换成"%20"。
你可以假定输入字符串的长度最大是1000。
注意输出字符串的长度可能大于1000。

```cpp
输入："We are happy."

输出："We%20are%20happy."

class Solution {
public:
    string replaceSpaces(string &str) {
        string re;
        for(auto x : str)
            if(x == ' ') re += "%20";
            else re += x;
            
        return re;
    }
};
```

## 从尾到头打印链表
> 输入一个链表的头结点，按照 从尾到头 的顺序返回节点的值。
返回的结果用数组存储。

```cpp
输入：[2, 3, 5]
返回：[5, 3, 2]

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
    vector<int> printListReversingly(ListNode* head) {
        vector<int> re;
        while(head)
        {
            re.push_back(head->val);
            head = head->next;
        }
        return vector<int>(re.rbegin(), re.rend());
    }
};

```
## 重建二叉树   ？
> 输入一棵二叉树**前序遍历**和**中序遍历**的结果，请重建该二叉树。
注意:
二叉树中每个节点的值都互不相同；
输入的前序遍历和中序遍历一定合法；

```cpp
给定：
前序遍历是：[3, 9, 20, 15, 7]
中序遍历是：[9, 3, 15, 20, 7]

返回：[3, 9, 20, null, null, 15, 7, null, null, null, null]
返回的二叉树如下所示：
    3
   / \
  9  20
    /  \
   15   7

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
    unordered_map<int, int> pos;

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        // 构建一个inorder的哈希表 方便查找inorder的位置
        for (int i=0; i<n; i++) pos[inorder[i]] = i;  
        return dfs(preorder, inorder, 0, n-1, 0, n-1);
    }
    TreeNode* dfs(vector<int>& pre, vector<int>& in, int pl, int pr, int il, int ir)
    {
        if(pl > pr) return nullptr;
        int k = pos[pre[pl]] - il;
        TreeNode* root = new TreeNode(pre[pl]);  // root 节点
        // 这里的递归 ,后面的几个参数不是很清楚
        root->left = dfs(pre, in, pl + 1, pl + k, il, il+k-1);
        root->right = dfs(pre, in, pl+k+1,pr, il+k+1, ir);
        return root;
    }
};

```
> 时间复杂度： O（n）  递归
> 总结： 递归建立整棵二叉树：先递归创建左右子树，然后创建根节点，并让指针指向两棵子树。 下面是具体步骤：
> 1. 先利用前序遍历找根节点：前序遍历的第一个数，就是根节点的值；
> 2. 在中序遍历中找到根节点的位置 k，则 k 左边是左子树的中序遍历，右边是右子树的中序遍历；
> 3. 假设左子树的中序遍历的长度是 l，则在前序遍历中，根节点后面的 ll个数，是左子树的前序遍历，剩下的数是右子树的前序遍历；
> 4. 有了左右子树的前序遍历和中序遍历，我们可以先递归创建出左右子树，然后再创建根节点；

## 二叉树的下一个节点  ？
> 给定一棵二叉树的其中一个节点，请找出中序遍历序列的下一个节点。
注意：
如果给定的节点是中序遍历序列的最后一个，则返回空节点;
二叉树一定不为空，且给定的节点一定不是空节点；

```cpp
假定二叉树是：[2, 1, 3, null, null, null, null]， 给出的是值等于2的节点。

则应返回值等于3的节点。

解释：该二叉树的结构如下，2的后继节点是3。
  2
 / \
1   3

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode *father;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL), father(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* p) {
        // 如果p存在右子树， 则下一个节点就是右子树的最左边的节点
        if(p->right)
        {
            p = p->right;
            while(p->left) p = p->left;
            return p;
        }
        // 这里是p不存在右子树， p的父节点存在，且p是父节点的右子树， 就直接将p的父节点赋给p
        while(p->father && p == p->father->right) p = p->father;
        return p->father;
    }
};
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210201222239557.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)


>时间复杂度： O(h) : h是树的高度，因为总共遍历的节点数不大于树的高度。
>总结： 分情况讨论
> 1. 如果当前节点有右儿子，则右子树中最左侧的节点就是当前节点的后继。比如F的后继是H；
> 2. 如果当前节点没有右儿子，则需要沿着father域一直向上找，找到第一个是其father左儿子的节点，该节点的father就是当前节点的后继。比如当前节点是D，则第一个满足是其father左儿子的节点是F，则C的father就是D的后继，即F是D的后继。

## 用两个栈实现队列    原理
> 请用栈实现一个队列，支持如下四种操作：
push(x) – 将元素x插到队尾；
pop() – 将队首的元素弹出，并返回该元素；
peek() – 返回队首元素；
empty() – 返回队列是否为空；
你只能使用栈的标准操作：push to top，peek/pop from top, size 和 is empty；
如果你选择的编程语言没有栈的标准库，你可以使用list或者deque等模拟栈的操作；
输入数据保证合法，例如，在队列为空时，不会进行pop或者peek等操作；

```cpp
MyQueue queue = new MyQueue();

queue.push(1);
queue.push(2);
queue.peek();  // returns 1
queue.pop();   // returns 1
queue.empty(); // returns false


class MyQueue {
public:
    /** Initialize your data structure here. */
    stack<int> a,b;
    
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        a.push(x);
    }
    
    void copy(stack<int>& _a, stack<int>& _b)
    {
        while(_a.size())
        {
            _b.push(_a.top());
            _a.pop();
        }
    }
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        copy(a, b);
        int re = b.top();
        b.pop();
        copy(b, a);
        return re;
    }
    
    /** Get the front element. */
    int peek() {
        copy(a, b);
        int re = b.top();
        //b.pop();
        copy(b, a);
        return re;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return a.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue obj = MyQueue();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.peek();
 * bool param_4 = obj.empty();
 */
```

> 时间复杂度： 
> 1. push()：O(1)；
> 2. pop(): 每次需要将主栈元素全部弹出，再压入，所以需要 O(n)的时间；
> 3. peek()：类似于pop()，需要 O(n)的时间；
> 4. empty()： O(1) ；

> 总结： **我们用两个栈来做，一个主栈，用来存储数据；一个辅助栈，用来当缓存。**
> push(x)，我们直接将x插入主栈中即可。
pop()，此时我们需要弹出最先进入栈的元素，也就是栈底元素。我们可以先将所有元素从主栈中弹出，压入辅助栈中。则辅助栈的栈顶元素就是我们要弹出的元素，将其弹出即可。然后再将辅助栈中的元素全部弹出，压入主栈中。
peek()，可以用和pop()操作类似的方式，得到最先压入栈的元素。
empty()，直接判断主栈是否为空即可。


## 斐波那契数列(几种范围大的还有考虑清楚)

> 输入一个整数 n ，求斐波那契数列的第 n 项。 假定从0开始，第0项为0。(n<=39)

```cpp
输入整数 n=5 
返回 5

class Solution {
public:
    
    int Fibonacci(int n) {
        // 0 1 1 2 3 5
        //if(n== 0) return 0;
        //if(n==1 || n==2) return 1;
        //return Fibonacci(n-1) + Fibonacci(n-2);
        int a= 0, b =1;
        while(n--)
        {
            int c = a + b;
            a = b; b = c;
        }
        return a;
    }
};
```
> 时间复杂度： O（n） ，因为需要计算n次
> 总结： 数据范围小，这题直接用两个变量滚动式计算即可。
> 如果数据范围大的话，需要考虑其他做法。可以参考**记忆化搜索，递推做法，矩阵运算**等


## 旋转数组的最小数字 ？
> 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个升序的数组的一个旋转，输出旋转数组的最小元素。
例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
数组可能包含重复项。
注意：数组内所含元素非负，若数组大小为0，请返回-1。

```cpp
输入：nums=[2,2,2,0,1]
输出：0

class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size() - 1;
        if(n<0) return -1;
        if(n>0 && nums[n] == nums[0]) n--;
        
        if(nums[0] < nums[n]) return nums[0];
        int l = 0, r = n;
        while(l<r){
            int mid = l+r >> 1;
            if(nums[mid] < nums[0]) r = mid;
            else l = mid+1;
        }
        return nums[r];
    }
};
```

> 时间复杂度： O(n), 利用的二分，二分的时间复杂度是 O(logn)，删除最后水平一段的时间复杂度最坏是 O(n)，所以总时间复杂度是 O(n)
> 总结： ？  https://www.acwing.com/solution/content/727/
## 矩阵中的路径 ？
> 请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。
路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下移动一个格子。
如果一条路径经过了矩阵中的某一个格子，则之后不能再次进入这个格子。
注意
> 1. 输入的路径不为空；
> 2. 所有出现的字符均为大写英文字母；

```cpp
matrix=
[
  ["A","B","C","E"],
  ["S","F","C","S"],
  ["A","D","E","E"]
]
str="BCCE" , return "true" 
str="ASAE" , return "false"

class Solution {
public:
    bool hasPath(vector<vector<char>>& matrix, string str) {
        for (int i = 0; i < matrix.size(); i ++ )
            for (int j = 0; j < matrix[i].size(); j ++ )
                if (dfs(matrix, str, 0, i, j))
                    return true;
        return false;
    }

    bool dfs(vector<vector<char>> &matrix, string &str, int u, int x, int y) {
        if (matrix[x][y] != str[u]) return false;
        if (u == str.size() - 1) return true;
        int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
        char t = matrix[x][y];
        matrix[x][y] = '*';
        for (int i = 0; i < 4; i ++ ) {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < matrix.size() && b >= 0 && b < matrix[a].size()) {
                if (dfs(matrix, str, u + 1, a, b)) return true;
            }
        }
        matrix[x][y] = t;
        return false;
    }
};
```
> 时间复杂度： O（n^2^ 3^k^）
> 时间复杂度分析：单词起点一共有 n^2^个，单词的每个字母一共有上下左右四个方向可以选择，但由于不能走回头路，所以除了单词首字母外，仅有三种选择。所以总时间复杂度是 O(n^2^ 3^k^)。
> 总结： 深度优先搜索中，最重要的就是考虑好搜索顺序。
> 我们先枚举单词的起点，然后依次枚举单词的每个字母。
过程中需要将已经使用过的字母改成一个特殊字母，以避免重复使用字符。

