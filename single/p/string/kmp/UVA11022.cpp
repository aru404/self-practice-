// 字符压缩，问给一个字符串，如果有连续重复的子串，可以压缩为一个子串，问最短的压缩是多长
#include <bits/stdc++.h>

const int maxN = 100 + 5;
int kmp[maxN][maxN], dp[maxN][maxN];
char s[maxN];

inline void KMP(int n)
{
    for(int i = 1; i <= n; ++i)
    {
        kmp[i][i] = 0;
        for(int j = i + 1; j <= n; ++j)
        {
            int k = kmp[i][j - 1];
            while(k && s[k + i] != s[j]) k = kmp[i][k];
            kmp[i][j] = k + (s[k + i] == s[j]);
        }
    }
}

int main()
{
    while(scanf("%s", s + 1))
    {
        if(s[1] == '*') break;
        int n = strlen(s + 1);
        KMP(n);

        for(int i = n; i; i--)
        {
            for(int j = i; j <= n; j++)
            {
                dp[i][j] = j - i + 1;
                for(int k = i; k <= j; ++k)
                {
                    int len = j - k + 1 - kmp[k][j];
                    if((j - k + 1) % len == 0)
                    {
                        dp[i][j] = std::min(dp[i][j], dp[i][k - 1] + dp[k][k + len - 1]);
                    }
                    else
                    {
                        dp[i][j] = std::min(dp[i][j], dp[i][k - 1] + dp[k][j]);
                    }
                }
            }
        }
        std::cout << dp[1][n] << '\n';
    }
    return 0;
}