class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        // 遍历一遍， 在数组下标中的数字如果出现过就将设置为-1，没有出现就不变
        vector<int> re;
        for(auto x : nums)
        {
            x = abs(x);
            if(nums[x - 1] > 0) nums[x - 1] *= -1;  // 这个位置上的数字就代表出现过，设置为-1
        }
        for(int i = 0; i< nums.size(); i++)
            if(nums[i] > 0) re.push_back(i + 1);  // 这里用i = 1 遍历会越界
        return re;
    }
};