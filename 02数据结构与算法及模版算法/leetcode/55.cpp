class Solution {
public:
    bool canJump(vector<int>& nums) {
        // 可以明白， 所跳跃的点都是连续的
        // 可以遍历每个点跳跃的最大值
        // 如果遍历的一个点，在前面一个点跳不到它，就表示不连续

        // j 表示能跳到右边的位置是什么
        for(int i = 0, j = 0; i < nums.size(); i++)
        {
            if(j < i) return false;  // 表示j跳到后面的位置，i在遍历，如果j到不了i，就表示不能到
            j = max(j, i + nums[i]);
        }
        return true;
    }
};