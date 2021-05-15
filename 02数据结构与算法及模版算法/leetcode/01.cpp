class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> re;
        unordered_map<int, int> hash;
        for(int i=0; i<nums.size(); i++)
        {
            int other = target - nums[i];
            if(hash.count(other))
            {
                re = vector<int>({hash[other], i});
                break;
            }
            hash[nums[i]] = i;
        }
        return re;
    }
};