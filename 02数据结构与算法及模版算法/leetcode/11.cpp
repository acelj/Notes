class Solution {
public:
    int maxArea(vector<int>& height) {
        // 用双指针扫描
        // 如果前面的指针高度低，前面的指针向后移动， 如果后面的指针低，后面指针向前移动  
        // 
        int re = 0;
        for(int i = 0, j = height.size() - 1; i < j ; )
        {
            re = max(re, min(height[i], height[j]) * (j - i));
            if(height[i] < height[j]) i++;
            else  j--;
        }
        return re;
    }
};