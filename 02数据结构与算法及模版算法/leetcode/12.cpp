/// 可以直接把个 十 百 千 的数字对应的数字写出来，
/// 第二种就是按照下面的，把需要用到的数字列出来，其他的可以用这些数字来表示
class Solution {
public:
    string intToRoman(int num) {
        int vals[] = {1000,
                    900,500,400,100,
                    90,50,40,10,
                    9,5,4,1
        };
        string reps[] = {"M", 
                    "CM", "D", "CD", "C", 
                    "XC", "L", "XL", "X", 
                    "IX", "V", "IV", "I"
        };

        string re;
        for(int i = 0; i < 13; i++)
        {
            while(num >= vals[i])
            {
                num -= vals[i];
                re += reps[i];
            }
        }
        return re;
    }
};