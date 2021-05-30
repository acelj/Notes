class Solution {
public:
    int hammingDistance(int x, int y) {
        int re = 0;
        while(x || y)
        {
            re += (x & 1 ) ^ (y & 1);
            x >>= 1, y >>= 1;
        }
        return re;
    }
};