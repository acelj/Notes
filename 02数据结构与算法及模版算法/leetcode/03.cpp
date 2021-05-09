class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> hash;
        int re = 0;
        /// j 在后面，i在前面，从i和j之间找最长子串，当发现之间的字符数量>1 ，i需要向后移动
        for(int i = 0, j = 0; j < s.size(); j++)
        {
            hash[s[j]] ++;
            while(hash[s[j]] > 1) hash[s[i++]] --;
            re = max(re, j- i + 1);
        }
        return re;
    }
};