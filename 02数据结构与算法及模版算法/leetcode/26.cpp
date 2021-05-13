class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // return distance(nums.begin(), unique(nums.begin(), nums.end()));

        int k =  0;
        for(int i = 0; i< nums.size(); i++)
        {
            if( !i || nums[i] != nums[i - 1])
                nums[k ++ ] = nums[i];
        }
        return k;
    }
};