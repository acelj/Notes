class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        // 先用前缀来保存第i个数字前面的乘积， 然后用一个数字去更新后面的乘积，更新前面的数组就行了
        int n = nums.size();
        vector<int> f(n, 1);   // 0- n-1
        for(int i =1; i < n; i++)   // 这里不能=n
        {
            f[i] = f[i - 1] * nums[i - 1];
        }

        int end = 1;
        for(int i = n -1; i >=0; i --)
        {
            f[i] = f[i] * end;
            end *= nums[i];
        }
        return f;
    }
};