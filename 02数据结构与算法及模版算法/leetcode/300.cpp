class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> f(n, 1);

        int re = 1;
        for(int i = 1; i< n; i++)
        {
            for(int j =0; j< i; j++)
                if(nums[j] < nums[i])
                    f[i] = max(f[j] + 1, f[i]);
            if(f[i] > re)
                re = f[i];
        }
        return re;
    }
};