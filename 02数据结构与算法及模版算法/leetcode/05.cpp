class Solution {
public:
    string longestPalindrome(string s) {
        // 暴力做法
        // 回文子串 分为奇数和偶数 
        string re ;
        for(int i = 0; i < s.size(); i++)
        {
            int l = i - 1, r = i + 1;
            while(l >= 0 && r < s.size() && s[l] == s[r] )  l --, r ++;
            if(re.size() < r - l - 1) re = s.substr(l + 1, r - l - 1);  /// l + 1,  r - 1

            l = i, r= i + 1;
            while(l >= 0 && r < s.size() && s[l] == s[r] )  l --, r ++;
            if(re.size() < r - l - 1) re = s.substr(l + 1, r - l - 1);
        }
        return re;
    }
};