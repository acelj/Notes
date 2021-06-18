class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> s(n + 1);
        for(int i = 1; i <= n; i++) s[i] = s[i - 1] + nums[i - 1];

        unordered_map<int, int> hash;
        hash[0] = 1;
        int re = 0;
        for(int i = 1; i <= n; i++)
        {
            re += hash[s[i] - k];  // 前缀和的转换， 时间复杂度为O(n)
            hash[s[i]] ++;
        }
        return re;
    }
};