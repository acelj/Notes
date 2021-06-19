class Solution {
public:
    int countSubstrings(string s) {
        int re = 0;
        for(int i = 0; i<s.size(); i++)
        {
            // 奇数情况
            for(int j = i, k = i; j>=0 && k <s.size(); j--, k++)
            {
                if(s[j] != s[k]) break;
                re++;
            }
            // 偶数情况
            for(int j = i, k = i +　1; j>=0 && k <s.size(); j--, k++)
            {
                if(s[j] != s[k]) break;
                re++;
            }
        }
        return re;
    }
};