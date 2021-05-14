class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string re;

        if(strs.empty()) return re;
        for(int i = 0; i < strs[0].size(); i++)
        {
            char c =  strs[0][i];
            for(auto& str : strs)
            {
                if(str.size() <= i || str[i] != c )
                    return re;
            }
            re += c;
        }
        return re;
    }
};