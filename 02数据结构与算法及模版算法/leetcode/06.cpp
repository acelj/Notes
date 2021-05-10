// 此题应该是N 字形转换
class Solution {
public:
    string convert(string s, int numRows) {
        string re;
        if(numRows == 1) return s;
        // 找规律
        for(int j =0; j < numRows; j++)
        {
            if(j == 0 || j == numRows -1 )
            {
                for(int i = j; i<s.size(); i += 2 * numRows - 2)
                    re += s[i];
            }
            else
            {
                for(int i = j, k = 2 * numRows -2 - j; i < s.size() || k < s.size() ;i += 2 * numRows -2, k += 2 * numRows -2)
                {
                    if(i < s.size()) re += s[i];   // 先加前面的
                    if(k < s.size()) re += s[k];
                }
            }
        }
        return re;
    }
};