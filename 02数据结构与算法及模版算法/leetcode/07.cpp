class Solution {
public:
    int reverse(int x) {
        int re = 0;
        while(x)
        {
            if(re > 0 && re > (INT_MAX - x % 10)/ 10) return 0;
            if(re < 0 && re < (INT_MIN - x % 10) / 10) return 0;
            re = re * 10 + x % 10;   /// 这行代码会溢出
            x /= 10;
        }
        // if(re > INT_MAX) return 0;
        // if(re < INT_MIN) return 0;
        return re;
    }
};