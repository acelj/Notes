class Solution {
public:
    int myAtoi(string s) {
        int re = 0;
        int k = 0;
        while(k < s.size() && s[k] == ' ') k ++;
        if( k == s.size()) return 0;

        int flag = 1;
        if(s[k] == '-') flag = -1, k ++;
        if(s[k] == '+') 
        {
            if (flag == -1) return 0;
            else
                k ++;
        }
        while(k < s.size() && s[k] >='0' && s[k] <= '9')
        {
            int x = s[k] - '0';
            if(flag > 0 && re > (INT_MAX - x)/ 10) return INT_MAX;
            if(flag < 0 && -re < (INT_MIN + x)/ 10) return INT_MIN;
            if(-re * 10 - x == INT_MIN) return INT_MIN;   // 这句是特殊判断的， INT_MN 和INT_MAX的绝对值不一样
            re = re * 10 + x;
            k++;
        }
        re *= flag;
        return re;
    }
};