class Solution {
public:
    int numTrees(int n) {
        // 有公式
        // 元素个数同的二叉搜索数 ， 求的数目是一样的 如1-10， 2-11.
         vector<int> f(n + 1);
         f[0] = 1;
         for(int i = 1; i <= n; i++)
            for(int j = 1; j <= i; j++)
                f[i] += f[j - 1] * f[i - j - 1 + 1];   // 左边 * 右边
        return f[n];
    }
};