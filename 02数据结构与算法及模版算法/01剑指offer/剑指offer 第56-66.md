@[TOC]
## 0到n-1中缺失的数字

> 一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0到n-1之内。
> 
> 在范围0到n-1的n个数字中有且只有一个数字不在该数组中，请找出这个数字。
![>](https://img-blog.csdnimg.cn/20210221230816524.png)
二分

```cpp
class Solution {
public:


    int getMissingNumber(vector<int>& nums) {

        if(!nums.size()) return 0;
        int l = 0, r = nums.size() - 1;   // 这里减1 不减1，都行
        while(l < r)
        {
            int mid = l + r >> 1;
            if(nums[mid] != mid) r = mid;
            else
                l = mid + 1;
        }

        // 如果整个序列是连续的，只缺少最后一个数
        if(nums[r] == r) r ++ ;

        return r;
    }
};
```

 直接遍历
 

```cpp
class Solution {
public:
    int getMissingNumber(vector<int>& nums) {
        int i = 0;
        for(; i< nums.size(); i++)
            if(nums[i] != i) break;

        return i;
    }
};
```

## 数组中数值和下标相等的元素

> 假设一个单调递增的数组里的每个元素都是整数并且是唯一的。
> 
> 请编程实现一个函数找出数组中任意一个数值等于其下标的元素。
> 
> 例如，在数组[-3, -1, 1, 3, 5]中，数字3和它的下标相等。
![>](https://img-blog.csdnimg.cn/20210221230622604.png)
 直接遍历法
 

```cpp
class Solution {
public:

    // 直接遍历法
    int getNumberSameAsIndex(vector<int>& nums) {
        int i = 0;
        for( ; i<nums.size() ; i++)
        {
            if(nums[i] == i) break;
        }
        if(i == nums.size()) return -1;
        else
            return i;
    }
};
```

二分法： 找到相关性质

```cpp
// 找数组是否单调， 或者构造成的新数组是否单调，nums[i] - i >= nums[i] - (i-1)
int getNumberSameAsIndex(vector<int>& nums) {
    if(!nums.size()) return -1;
    int l = 0, r = nums.size();
    while(l < r)
    {
        int mid = l + r >> 1;
        if(nums[mid] - mid >= 0) r = mid;
        else l = mid + 1;
    }

    if(nums[r] - r == 0)  return r;
    // 如果序列中没有符合的元素
    return -1;
}
```

## 二叉搜索树的第k个结点

> 给定一棵二叉搜索树，请找出其中的第k小的结点。
> 
> 你可以假设树和k都存在，并且1≤k≤树的总结点数。
![>](https://img-blog.csdnimg.cn/20210221230416625.png)
 

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
    // 二叉搜索数的中序遍历是有序的，可以直接找中序遍历中的结果
    // 直接中序遍历找第k个数字。
    TreeNode* re;

    TreeNode* kthNode(TreeNode* root, int k) {
        dfs(root, k);
        return re;
    }

    // 传引用是为了确保每次改变
    void dfs(TreeNode* root, int& k)
    {
        if(!root) return ;
        dfs(root->left, k);
        k --;
        if(!k) re = root;
        if(k > 0) dfs(root->right, k);

    }
};
```

## 二叉树的深度

> 输入一棵二叉树的根结点，求该树的深度。
> 
> 从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。
![>](https://img-blog.csdnimg.cn/20210221230317708.png)

```cpp
在这里插入代码片
```

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

    // 用递归的思想去做题
    int treeDepth(TreeNode* root) {
        if(!root) return 0;
        // + 1 表示加上根节点的这一层
        return max(treeDepth(root->left), treeDepth(root->right)) + 1;
    } 
};
```

## 平衡二叉树

> 输入一棵二叉树的根结点，判断该树是不是平衡二叉树。
> 
> 如果某二叉树中任意结点的左右子树的深度相差不超过1，那么它就是一棵平衡二叉树。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221222042965.png)
两种递归方法：

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

    // 需要考虑二叉树只有左子树，而且左子树中有几层节点，是平衡二叉树
    int deep(TreeNode* root)
    {
        if(!root) return 0;
        return max(deep(root->left) , deep(root->right)) + 1;
    }

    bool isBalanced(TreeNode* root) {
        if(!root)    return true;
        if(abs(deep(root->left) - deep(root->right)) <= 1)    
            return isBalanced(root->left) && isBalanced(root->right);   // 这里需要递归调用， 不是直接返回的
        return false;
    }
};
```

```cpp
// 第二种递归
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

    bool re = true;
    bool isBalanced(TreeNode* root) {
        dfs(root);
        return re;
    }

    int dfs(TreeNode* root)
    {
        if(!root) return 0;
        int l = dfs(root->left), r = dfs(root->right);
        if(abs(l - r) > 1)  re = false;
        return max(l, r) + 1;
    }
};
```


## 数组中只出现一次的两个数字（高级解法，异或）

> 一个整型数组里除了两个数字之外，其他的数字都出现了两次。
> 
> 请写程序找出这两个只出现一次的数字。
> 
> 你可以假设这两个数字一定存在。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221221718184.png)

```cpp
解法1 : 利用hash表，存储数字出现的次数
class Solution {
public:
    vector<int> findNumsAppearOnce(vector<int>& nums) {
        vector<int> re;
        vector<int> tmp;
        unordered_map<int ,int > map;
        for(int i= 0; i<nums.size(); i++)
        {
            ++ map[nums[i]];
        }
       for(auto x : map)
       {
           if( x.second == 1) re.push_back(x.first);
       }
        return re;
    }
};
```
高级解法

```cpp
class Solution {
public:
    vector<int> findNumsAppearOnce(vector<int>& nums) {
        int sum = 0;
        for (auto x : nums) sum ^= x;
        int k = 0;
        while (!(sum >> k & 1)) k ++ ;
        int first = 0;
        for (auto x : nums)
            if (x >> k & 1)
                first ^= x;
        return vector<int>({first, sum ^ first});
    }
};
```


## 数组中唯一只出现一次的数字（十分特殊，第二种解法是大佬解法）

> 在一个数组中除了一个数字只出现一次之外，其他数字都出现了三次。
> 
> 请找出那个只出现一次的数字。
> 
> 你可以假设满足条件的数字一定存在。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210221221442198.png)

```cpp
class Solution {
public:
    int findNumberAppearingOnce(vector<int>& nums) {
        unordered_map<int, int> map;
        for(int i=0; i<nums.size(); i++)
        {
            map[nums[i]] ++ ;
        }
        for(auto x : map) 
            if(x.second == 1) return x.first;
        return 0;
    }
};
```

特殊解法 ： 太特殊了，只能靠猜

```cpp
class Solution {
public:
    int findNumberAppearingOnce(vector<int>& nums) {
        int ones = 0, twos = 0;
        for (auto x : nums)
        {
            ones = (ones ^ x) & ~twos;
            twos = (twos ^ x) & ~ones;
        }
        return ones;
    }
};
```

## 和为S的两个数字（利用hash 降低复杂度）

> 输入一个数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。
> 
> 如果有多对数字的和等于s，输出任意一对即可。
> 
> 你可以认为每组输入中都至少含有一组满足条件的输出。
![>](https://img-blog.csdnimg.cn/20210221221333791.png)
 

```cpp
class Solution {
public:
    vector<int> findNumbersWithSum(vector<int>& nums, int target) {
        unordered_set<int> hash;
        for(int i = 0; i<nums.size(); i++)
        {
            if(hash.count(target - nums[i])) 
                // 下面这种方式是简写 vector<int> ({1 ,2, 3,3 ,4});  省略的()
                return vector<int> {target - nums[i], nums[i] };  
            hash.insert(nums[i]);
        }
        return vector<int>();
    }
};
```

## 和为S的连续正数序列

> 输入一个正数s，打印出所有和为s的连续正数序列（至少含有两个数）。
> 
> 例如输入15，由于1+2+3+4+5=4+5+6=7+8=15，所以结果打印出3个连续序列1～5、4～6和7～8。
![>](https://img-blog.csdnimg.cn/20210221221231329.png)

 双指针算法
 

```cpp
class Solution {
public:
    vector<vector<int> > findContinuousSequence(int sum) {
        vector<vector<int>> re;

        // 双指针算法， 两个指针向后遍历
        // 1. 用一个i记录前面的指针, j 是后面的指针， s 记录的是从i 向后遍历， 如果小于sum，逐个向后加
        // 直到加到== sum ， 且 j- i > 0 说明区间至少有两个数字
        // 2. 满足上面的情况，就讲一个区间保存在vector中，然后i向后加， 这时j也是向后的，它们是单调的，
        // 所以不必返回从0开始， 这时时间复杂度为O(n)

        for(int i=1, j =1, s = 1; i< sum/2 + 1; i++)
        {
            while(s < sum) s += ++j;
            if(s == sum && j -i >= 1)
            {
                vector<int> child;
                for(int k = i; k<=j; k++) child.push_back(k);
                re.push_back(child);
            }
            s -= i;
        }
        return re;

    }
};
```

## 翻转单词顺序（先全部翻转，后单词翻转）

> 输入一个英文句子，单词之前用一个空格隔开，且句首和句尾没有多余空格。翻转句子中单词的顺序，但单词内字符的顺序不变。
> 
> 为简单起见，标点符号和普通字母一样处理。
> 
> 例如输入字符串"I am a student."，则输出"student. a am I"。
![>](https://img-blog.csdnimg.cn/20210221221051154.png)
 

```cpp
class Solution {
public:
    // 最优解 时间O（n） 空间 O（1）

    // 交换两次， 
    // 1. 第一次将全部的反转
    // 2. 第二次将逐个单词进行反转

    string reverseWords(string s) {
        //for(int i=0 ,j = s.size() -1; i< j; i++, j--)   swap(s[i], s[j]);
        reverse(s.begin(), s.end());

        for(int i=0; i<s.size(); i++)
        {
            int j = i;
            while(j<s.size() && s[j] != ' ') j++;
            reverse(s.begin() + i, s.begin() + j);
            i = j;
        }

        return s;

    }
};
```

## 左旋转字符串

> 字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。
> 
> 请定义一个函数实现字符串左旋转操作的功能。
> 
> 比如输入字符串"abcdefg"和数字2，该函数将返回左旋转2位得到的结果"cdefgab"。
![>](https://img-blog.csdnimg.cn/20210221221004866.png)
 

```cpp
class Solution {
public:


    // 时间O（n） 空间O（1）
    // 1. 先将全部的进行翻转，
    // 2. 然后将前面的部分进行翻转， 在将后面的进行翻转， 这样就得到答案。

    string leftRotateString(string s, int n) {
        reverse(s.begin(), s.end());   //实际上每次进行翻转的时间复杂度为Ｏ（ｎ），　双指针进行翻转
        reverse(s.begin(), s.end() -n);
        reverse(s.end() - n, s.end());

        return s;
    }
};
```

