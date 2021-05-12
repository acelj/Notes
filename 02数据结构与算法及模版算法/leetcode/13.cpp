class Solution {
public:
    int romanToInt(string s) {
        /// 直接根据字母算数字的大小，然后除了4和9， 左边的比右边的字母小，这样的字母在左边就需要减去它
        unordered_map<char, int> hash;
        hash['I'] = 1, hash['V'] = 5;
        hash['X'] = 10, hash['L'] = 50;
        hash['C'] = 100, hash['D'] = 500;
        hash['M'] = 1000;

        int re = 0;
        for(int i = 0; i< s.size(); i++)
        {
            if(i + 1 < s.size() && hash[s[i]] < hash[s[i + 1]])
                re -= hash[s[i]];
            else
                re += hash[s[i]];
        }   
        return re;
    }
};