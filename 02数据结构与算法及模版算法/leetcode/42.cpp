三次线性扫描，故只需要 O(n)O(n) 的时间。
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int re = 0;
        if( n == 0) return 0;

        // 直接通过三次扫描
        vector<int> left(n, 0), right(n, 0);
        left[0] = height[0], right[n-1] = height[n - 1];
        for(int i = 1; i <= n - 1; i ++)
        {
            left[i] = max(left[i - 1], height[i]);
        }
        for(int i = n - 2; i >=0; i --)
        {
            right[i] = max(right[i + 1], height[i]);
        }

        for(int i = 0; i <= n-1; i++)
        {
            re += min(left[i], right[i]) - height[i];
        }
        return re;

    }
};