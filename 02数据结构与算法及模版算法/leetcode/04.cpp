class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
            //使用递归处理
            int total = nums1.size() + nums2.size();
            if(total % 2 == 0)
            {
                int left = findKnum(nums1,0, nums2,0,total/2);
                int right = findKnum(nums1,0,nums2,0, total/2 + 1);
                return (left + right) / 2.0;
            }
            else
                return findKnum(nums1,0,nums2,0,total/2 + 1);
    }

    int findKnum(vector<int>& nums1, int i, vector<int>& nums2, int j, int k)
    {
        // nums1 比较长， 短的放在前面
        if(nums1.size() - i > nums2.size() - j) 
            return findKnum(nums2, j, nums1, i, k);
        // 左边数组是空的
        if(nums1.size() == i) return nums2[j + k - 1];

        // k == 1 直接返回两个数组的最小值
        if(k == 1) return min(nums1[i], nums2[j]);

        int si = min(i + k /2, int(nums1.size())), sj = j + k /2;
        if(nums1[si - 1] > nums2[sj - 1])
        {
            return findKnum(nums1, i, nums2, j+ k /2, k - k /2);
        }
        else
        {
            return findKnum(nums1, si, nums2,j, k - (si - i));
        }
    }
};