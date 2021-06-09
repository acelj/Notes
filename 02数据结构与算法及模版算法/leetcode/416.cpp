class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for(auto x : nums)
            sum += x;
        vector<int> f(sum + 1);
        f[0] = 1;  // 表示可以切分
        if(sum % 2) return false; 
        sum /= 2;    
        for(int i=0; i < nums.size(); i++)
        {
            for(int j = sum; j >=nums[i]; j--)
                f[j] = f[j] | f[j - nums[i]];   // 0-1 背包问题
        }
        return f[sum];
    }
};