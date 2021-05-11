class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0) return false;
        int re = 0;
        int tmp = x;
        while(x)
        {
            if(re > 0 && re > (INT_MAX - x %10) / 10) return false;
            re = re * 10 + x % 10;
            x /= 10;
        }
        //cout << re ;
        return re == tmp ? true : false;
    }
};