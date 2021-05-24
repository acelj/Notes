class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        pair<int, int> re(INT_MAX, INT_MAX);
        for(int i = 0; i< nums.size(); i++)
        {
            for(int j = i + 1, k = nums.size() - 1; j < k; j++)
            {
                while(k - 1 > j && nums[i] + nums[j] + nums[k - 1] >= target) k --;
                int s = nums[i] + nums[j] + nums[k];
                re = min(re, make_pair(abs(s - target), s));  // re中存取的是 差值 ，三数之和
                if( k - 1 > j)
                {
                    s = nums[i] + nums[j] + nums[k - 1];   // 找到前面一个
                    re = min(re, make_pair(abs(target - s), s));
                } 
            }
        }
         return re.second;
    }
};