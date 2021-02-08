@[TOC]
## 反转链表
> 定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的头结点。
> 同时实现迭代版本和递归版本

```cpp
输入:1->2->3->4->5->NULL
输出:5->4->3->2->1->NULL

// 迭代版本
翻转即将所有节点的next指针指向前驱节点。
由于是单链表，我们在迭代时不能直接找到前驱节点，所以我们需要一个额外的指针保存前驱节点。同时在改变当前节点的next指针前，不要忘记保存它的后继节点。

空间复杂度分析：遍历时只有3个额外变量，所以额外的空间复杂度是 O(1)。
时间复杂度分析：只遍历一次链表，时间复杂度是  O(n) 。
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
    ListNode* reverseList(ListNode* head) {
        ListNode *prev = nullptr;
        ListNode *cur = head;
        while (cur)
        {
            ListNode *next = cur->next;
            cur->next = prev;
            prev = cur, cur = next;
        }
        return prev;
    }
};


// 递归版本

首先我们先考虑 reverseList 函数能做什么，它可以翻转一个链表，并返回新链表的头节点，也就是原链表的尾节点。
所以我们可以先递归处理 reverseList(head->next)，这样我们可以将以head->next为头节点的链表翻转，并得到原链表的尾节点tail，此时head->next是新链表的尾节点，我们令它的next指针指向head，并将head->next指向空即可将整个链表翻转，且新链表的头节点是tail。

空间复杂度分析：总共递归 n 层，系统栈的空间复杂度是 O(n)，所以总共需要额外 O(n)的空间。
时间复杂度分析：链表中每个节点只被遍历一次，所以时间复杂度是 O(n)。


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
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode *tail = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return tail;
    }
};
```
## 合并两个排序的链表
> 输入两个**递增排序**的链表，合并这两个链表并使新链表中的结点仍然是按照递增排序的。
> 

```cpp
输入：1->3->5 , 2->4->5
输出：1->2->3->4->5->5

(二路归并) O(n)
新建头部的保护结点dummy，设置cur指针指向dummy。
若当前l1指针指向的结点的值val比l2指针指向的结点的值val小，则令cur的next指针指向l1，且l1后移；否则指向l2，且l2后移。
然后cur指针按照上一部设置好的位置后移。
循环以上步骤直到l1或l2为空。
将剩余的l1或l2接到cur指针后边。

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
    ListNode* merge(ListNode* l1, ListNode* l2) {
        auto dummy = new ListNode(-1);   // 用虚拟节点保证不为空
        auto cur = dummy;
        
        while(l1 && l2)
        {
            if(l1->val < l2->val)
            {
                cur->next = l1;
                cur = cur->next;
                l1 = l1->next;
            }
            else
            {
                cur->next = l2;
                cur = cur->next;
                l2 = l2->next;
            }
        }
        if(l1) cur->next = l1;
        else cur->next = l2;
        
        return dummy->next;
    }  
};

```

## 树的子结构
> 输入两棵二叉树A，B，判断B是不是A的子结构。
我们规定空树不是任何树的子结构。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210207160936866.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

```cpp
返回 true ,因为B是A的子结构。

代码分为两个部分：

遍历树A中的所有非空节点R；
判断树A中以R为根节点的子树是不是包含和树B一样的结构，且我们从根节点开始匹配；
对于第一部分，我们直接递归遍历树A即可，遇到非空节点后，就进行第二部分的判断。

对于第二部分，我们同时从根节点开始遍历两棵子树：
如果树B中的节点为空，则表示当前分支是匹配的，返回true；
如果树A中的节点为空，但树B中的节点不为空，则说明不匹配，返回false；
如果两个节点都不为空，但数值不同，则说明不匹配，返回false；
否则说明当前这个点是匹配的，然后递归判断左子树和右子树是否分别匹配即可；

时间复杂度
最坏情况下，我们对于树A中的每个节点都要递归判断一遍，每次判断在最坏情况下需要遍历完树B中的所有节点。
所以时间复杂度是 O(nm)，其中 n 是树A中的节点数， m 是树B中的节点数。

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
    bool hasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        // 本题使用二叉树和递归做法
        if(!pRoot1 || !pRoot2) return false;    // 如果是空就返回false
        if(isSame(pRoot1, pRoot2)) return true;  // 找到以A的为根节点， 和B的比较
        // 直接从二叉树A中的每个节点开始找有没有相同的子结构
        return hasSubtree(pRoot1->left, pRoot2) || hasSubtree(pRoot1->right, pRoot2);
    }
    
    bool isSame(TreeNode* root1, TreeNode* root2)
    {
        // A的节点和B的节点做比较
        if(!root2) return true;   // 当子树的下一个节点为空的话 就说明前面的都对应上了
        if(!root1 || root1->val != root2->val) return false;   // A节点不空， B节点也不空（上面判断），但节点值不同， 返回false
        // 然后一次遍历剩下的节点信息， 要求每一个节点都需要匹配上
        return isSame(root1->left, root2->left) && isSame(root1->right, root2->right);
    }
};
```

## 二叉树的镜像
> 输入一个二叉树，将它变换为它的镜像。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210207161151451.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NDg2MDI3,size_16,color_FFFFFF,t_70)

```cpp

我们可以发现镜像后的树就是将原树的所有节点的左右儿子互换！
所以我们递归遍历原树的所有节点，将每个节点的左右儿子互换即可。

时间复杂度：原树仅被遍历一次，所以时间复杂度是 O(n)。
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
    void mirror(TreeNode* root) {
        if(!root) return ;
        //if(!root->left) root->left = root->right;
        //if(!root->right) root->right = root->left;
        swap(root->left, root->right);
        mirror(root->left); mirror(root->right);
    }
};
```
## 对称的二叉树
> 请实现一个函数，用来判断一棵二叉树是不是对称的。
如果一棵二叉树和它的镜像一样，那么它是对称的。

```cpp
如下图所示二叉树[1,2,2,3,4,4,3,null,null,null,null,null,null,null,null]为对称二叉树：
    1
   / \
  2   2
 / \ / \
3  4 4  3

如下图所示二叉树[1,2,2,null,4,4,3,null,null,null,null,null,null]不是对称二叉树：
    1
   / \
  2   2
   \ / \
   4 4  3


// 递归
两个子树互为镜像当且仅当：

两个子树的根节点值相等；
第一棵子树的左子树和第二棵子树的右子树互为镜像，且第一棵子树的右子树和第二棵子树的左子树互为镜像；
时间复杂度
从上到下每个节点仅被遍历一遍，所以时间复杂度是 O(n)
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
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        return dfs(root->left, root->right);
    }
    
    bool dfs(TreeNode* p1, TreeNode* p2)
    {
        if(!p1 || !p2) return !p1 && !p2;  //  当由一个为空的话， 只有两个为空的时候才返回true
        if(p1->val != p2->val) return false;
        return dfs(p1->left, p2->right) && dfs(p1->right, p2->left);
    }
};

// 迭代
(迭代) O(n)
用栈模拟递归，对根节点的左子树，我们用中序遍历；对根节点的右子树，我们用反中序遍历。
则两个子树互为镜像，当且仅当同时遍历两课子树时，对应节点的值相等。

时间复杂度
树中每个节点仅被遍历一遍，所以时间复杂度是 O(n)。
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
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        stack<TreeNode*> left, right;
        TreeNode *lc = root->left;
        TreeNode *rc = root->right;
        while(lc || rc || left.size())
        {
            while (lc && rc)
            {
                left.push(lc), right.push(rc);
                lc = lc->left, rc = rc->right;
            }
            if (lc || rc) return false;
            lc = left.top(), rc = right.top();
            left.pop(), right.pop();
            if (lc->val != rc->val) return false;
            lc = lc->right, rc = rc->left;
        }
        return true;
    }

};

```
## 顺时针打印矩阵(蛇形矩阵)
> 输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

```cpp
输入：
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]

输出：[1,2,3,4,8,12,11,10,9,5,6,7]

模拟) O(n^2)
我们顺时针定义四个方向：上右下左。
从左上角开始遍历，先往右走，走到不能走为止，然后更改到下个方向，再走到不能走为止，依次类推，遍历 n2 个格子后停止。

时间复杂度
矩阵中每个格子遍历一次，所以总时间复杂度是 O(n^2)。

class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        // 思路
        // 1. 判断空的情况， 开辟每个点的标记情况 false
        // 2. 确定四个方向， 遍历长* 款的所有点
        // 3. 每走一个点就将点加入返回的vector数组中，并标记已经走过
        // 4. a<0 || a>=n || b <0 || b>=m ||st[a][b]  判断边界条件， st[a][b] 需要放在后面，意思是先判断点在不在边界内，如果不在后面的就不需要执行了
        
        
        vector<int> re;
        if(matrix.empty()) return re;
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<bool>> st(n, vector<bool>(m,false));  //标记该点走没走
        
        int dx[4] = {-1,0,1,0}, dy[4] = {0,1,0,-1};   // 表示四个方向
        int d = 1; // 第一步表示向右走
        int x = 0, y = 0;  // 从0，0 开始
        for(int i=0;i< n*m; i++)
        {
            re.push_back(matrix[x][y]);
            st[x][y] = true;
            int a = x + dx[d], b = y + dy[d];   // 添加一个变量表示下一个位置， 因为需要判断下个位置能否走， 不能走需要回溯
            if(a<0 || a>=n || b <0 || b>=m ||st[a][b] )
            {
                d = (d + 1) % 4; // 下一个位置已经走过，这时需要换一个放向
                a = x + dx[d], b = y + dy[d];
            }
            x = a, y = b;
        }
        return re;
    }
};

```
## 包含min函数的栈
> 设计一个支持push，pop，top等操作并且可以在O(1)时间内检索出最小元素的堆栈。
push(x)–将元素x插入栈中
pop()–移除栈顶元素
top()–得到栈顶元素
getMin()–得到栈中最小元素

```cpp
MinStack minStack = new MinStack();
minStack.push(-1);
minStack.push(3);
minStack.push(-4);
minStack.getMin();   --> Returns -4.
minStack.pop();
minStack.top();      --> Returns 3.
minStack.getMin();   --> Returns -1.


单调栈) O(1)
我们除了维护基本的栈结构之外，还需要维护一个单调栈，来实现返回最小值的操作。
下面介绍如何维护单调栈：

当我们向栈中压入一个数时，如果该数 ≤≤ 单调栈的栈顶元素，则将该数同时压入单调栈中；否则，不压入，这是由于栈具有先进后出性质，所以在该数被弹出之前，栈中一直存在一个数比该数小，所以该数一定不会被当做最小数输出。
当我们从栈中弹出一个数时，如果该数等于单调栈的栈顶元素，则同时将单调栈的栈顶元素弹出。
单调栈由于其具有单调性，所以它的栈顶元素，就是当前栈中的最小数。

时间复杂度
四种操作都只有常数次入栈出栈操作，所以时间复杂度都是 O(1).
class MinStack {
public:
    stack<int> st, min_st;
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        st.push(x);
        // 这里为什么是大于等于   因为pop操作的话，== 原因，  如果这里写上> 那么连续插上两个一样的数， min_st中只有一个，pop操作后， 会有问题。
        if(min_st.empty() || min_st.top() >= x) min_st.push(x);    
    }
    
    void pop() {
        if(min_st.top() == st.top()) min_st.pop();
        st.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return min_st.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */

```
## 栈的压入、弹出序列 
> 输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。
假设压入栈的所有数字均不相等。
例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
注意：若两个序列长度不等则视为并不是一个栈的压入、弹出序列。若两个序列都为空，则视为是一个栈的压入、弹出序列。

```cpp
输入：[1,2,3,4,5]
      [4,5,3,2,1]
输出：true

class Solution {
public:
    bool isPopOrder(vector<int> pushV,vector<int> popV) {
        /*
        就是模拟题： 
        首先需要想到只有两个操作，而且两个操作是不影响的
        1. 将下一个元素加入栈中
        2. 将栈顶元素弹出
        
        需要判断情况：栈顶元素是否和下一个输出的元素是一样的
        1. 一样： 必然会将当前栈顶输出
        2. 不一样：必然会将输入序列的下一个元素加入栈中。
        */
        if(pushV.size() != popV.size()) return false;
        
        stack<int> s;
        int i = 0;
        for(auto x : pushV)
        {
            s.push(x);
            while(s.size() && s.top() == popV[i])
            {
                i++;
                s.pop();
            }
        }
        return s.empty();
    }
};

```
## 不分行从上往下打印二叉树
> 从上往下打印出二叉树的每个结点，同一层的结点按照从左到右的顺序打印。

```cpp
输入如下图所示二叉树[8, 12, 2, null, null, 6, null, 4, null, null, null]
    8
   / \
  12  2
     /
    6
   /
  4

输出：[8, 12, 2, 6, 4]

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
    vector<int> printFromTopToBottom(TreeNode* root) {
        vector<int> re;
        if(!root ) return re;
        queue<TreeNode*> q;
        q.push(root);
        while(q.size())
        {
            auto t = q.front();
            q.pop();
            re.push_back(t->val);
            if(t->left) q.push(t->left);
            if(t->right) q.push(t->right);
        }
        return re;
    }
};


```

## 分行从上往下打印二叉树
> 从上到下按层打印二叉树，同一层的结点按从左到右的顺序打印，每一层打印到一行。

```cpp
输入如下图所示二叉树[8, 12, 2, null, null, 6, null, 4, null, null, null]
    8
   / \
  12  2
     /
    6
   /
  4

输出：[[8], [12, 2], [6], [4]]

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
    vector<vector<int>> printFromTopToBottom(TreeNode* root) {
        // 第一种解法， 用null 表示一行的结尾
        vector<vector<int>> re;
        if(!root) return re;
        
        queue<TreeNode*> q;
        q.push(root);
        q.push(nullptr);   // 这里必须加上一个条件，作为一行的判断
        
        vector<int> level;
        while(q.size())
        {
            auto t = q.front();
            q.pop();
            if(!t)   // t是空的，表示遍历完了一整行了
            {
                if(level.empty()) break;  
                re.push_back(level);
                level.clear();
                q.push(nullptr);  //作为满二叉树，在最后一行加上一个null
                continue;
            }
            else
            {
                level.push_back(t->val);
            }
            if(t->left) q.push(t->left);
            if(t->right) q.push(t->right);
        }
        return re;
        
    }
};

```

## 之字形打印二叉树 (上面的加了一个条件)
> 请实现一个函数按照之字形顺序从上向下打印二叉树。
即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。

```cpp
输入如下图所示二叉树[8, 12, 2, null, null, 6, 4, null, null, null, null]
    8
   / \
  12  2
     / \
    6   4
输出：[[8], [2, 12], [6, 4]]

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
    vector<vector<int>> printFromTopToBottom(TreeNode* root) {
        // 第一种解法， 用null 表示一行的结尾
        int i = 0;
        vector<vector<int>> re;
        if(!root) return re;
        
        queue<TreeNode*> q;
        q.push(root);
        q.push(nullptr);   // 这里必须加上一个条件，作为一行的判断
        
        vector<int> level;
        while(q.size())
        {
            auto t = q.front();
            q.pop();
            if(!t)   // t是空的，表示遍历完了一整行了
            {
                if(level.empty()) break;
                if((i ++) % 2 == 1)   // 在这里加上条件就行了
                    reverse(level.begin(), level.end());
                re.push_back(level);
                level.clear();
                q.push(nullptr);  //作为满二叉树，在最后一行加上一个null
                continue;
            }
            else
            {
                level.push_back(t->val);
            }
            if(t->left) q.push(t->left);
            if(t->right) q.push(t->right);
        }
        return re;
        
    }
};

```

