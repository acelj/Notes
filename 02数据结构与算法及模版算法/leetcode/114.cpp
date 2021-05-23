/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void flatten(TreeNode* root) {

        while(root)
        {
            auto p = root->left;
            if(p) 
            {   // 下面的代码在里面
                while(p->right) p = p->right;   // 如果存在左节点, 移动到右节点的最后一个节点
                // 然后将这条链插入右子树
                p->right = root->right;   
                root->right = root->left;
                // 一定要将左子树清空 
                root->left = NULL;     
            }
            root = root->right;
        }
    }
};