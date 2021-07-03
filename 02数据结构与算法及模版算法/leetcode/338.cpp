## 粗糙做法
class Solution {
public:
    int lowbit(int x) { return x & (-x); }    // 统计1的位置
    int cntbit(int x)       // 统计1的个数
    {
        int re = 0;
        if(x == 0) return 0;
        while(x)
        {
            x -= lowbit(x);
            re ++;
        }
        return re;
    }

    vector<int> countBits(int n) {
        vector<int> f(n + 1, 0);
        for(int i =0; i<=n; i++)
            f[i] = cntbit(i);
            return f;
    }
};

=======
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> f(n + 1, 0);
        for (int i = 1; i <= n; i ++ )
            f[i] = f[i >> 1] + (i & 1);
        return f;
    }
};
