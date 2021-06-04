class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        /// 用双指针做法， 前提，必须有序
        // 这里本来是O(n^3) 优化成了O(n^2), 优化了1维
        vector<vector<int>> re;
        
        sort(nums.begin(), nums.end()); 
        for(int i = 0; i < nums.size(); i++)
        {
            if(i > 0 &&  nums[i] == nums[i - 1] ) continue;  /// 保证不出现重复的，下一个i和上一个一样，那就是重复的，需跳过
            for(int j = i + 1, k= nums.size() - 1; j < k; j ++)
            {
                // 因为固定nums[i] 后， j 向后移动的话，k只会向前移动，所以j 和k总共是O(n)级别的，加上前面就是O（n^2）
                if( j > i + 1 && nums[j] == nums[j - 1]) continue;
                while(j < k -1 && nums[i] + nums[j] + nums[k - 1] >= 0) k --;   // 试探下一个数
                if(nums[i] + nums[j] + nums[k] == 0)
                {
                    re.push_back({nums[i], nums[j] ,nums[k]});
                }
            }
        }
        return re;
    }
};