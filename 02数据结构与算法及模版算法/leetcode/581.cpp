class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int l = 0, r= nums.size() - 1;
        while ( l + 1 < nums.size() && nums[l + 1] >= nums[l]) l++;  // 中左边升序zmax
        if(l == r) return 0;
        while(r - 1 >=0 && nums[r - 1] <= nums[r]) r--;
        for(int i = l + 1; i < nums.size(); i++)
            while(l >=0 && nums[l] > nums[i])
                l --;    // 左边的max 需要小于右边所有值
        for(int i = r - 1; i >= 0; i --)
            while(r < nums.size() && nums[r] < nums[i])
                r ++ ;
        return r - l - 1;  // - 1

    }
};