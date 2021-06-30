class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        if(!n || !m) return n + m;
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));

        dp[0][0] = 0;
        for(int i =1; i <=n; i++) dp[i][0] = i;
        for(int j =1; j <=m; j++) dp[0][j] = j;
        for(int i =1; i <=n; i++)
            for(int j =1; j<=m; j++)
            {
                /// -# 放在上面直接赋值，不需要min，放在下面需要用min
                dp[i][j] = (dp[i][j], dp[i-1][j-1] + (word1[i - 1] != word2[j - 1]));    // 后面比较的是 word1[i - 1]  而不是word1[i]，是因为下标是1开始的
                dp[i][j] = min(dp[i][j], dp[i-1][j] + 1);
                dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
            }
        return dp[n][m];
    }
};