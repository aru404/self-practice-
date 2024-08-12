// # Anthem of Berland

// ## 题面翻译

// 给定 $s$ 串和 $t$ 串，其中 $s$ 串包含小写字母和问号，$t$ 串只包含小写字母。

// 假设共有 $k$ 个问号。

// 你需要给把每个问号变成一个小写字母，共有 $26^k$ 种可能。

// 对于每种可能，设 $t$ 匹配 $s$ 的次数为 $f_i$，请输出 $\max(f_i)$ 。

// $1\leq |s|,|t|\leq 10^5,|s|\cdot |t|\leq 10^7$

// 由 @Ghastlcon 提供翻译

// ## 题目描述

// Berland has a long and glorious history. To increase awareness about it among younger citizens, King of Berland decided to compose an anthem.

// Though there are lots and lots of victories in history of Berland, there is the one that stand out the most. King wants to mention it in the anthem as many times as possible.

// He has already composed major part of the anthem and now just needs to fill in some letters. King asked you to help him with this work.

// The anthem is the string $ s $ of no more than $ 10^{5} $ small Latin letters and question marks. The most glorious victory is the string $ t $ of no more than $ 10^{5} $ small Latin letters. You should replace all the question marks with small Latin letters in such a way that the number of occurrences of string $ t $ in string $ s $ is maximal.

// Note that the occurrences of string $ t $ in $ s $ can overlap. Check the third example for clarification.

// ## 输入格式

// The first line contains string of small Latin letters and question marks $ s $ ( $ 1<=|s|<=10^{5} $ ).

// The second line contains string of small Latin letters $ t $ ( $ 1<=|t|<=10^{5} $ ).

// Product of lengths of strings $ |s|·|t| $ won't exceed $ 10^{7} $ .

// ## 输出格式

// Output the maximum number of occurrences of string $ t $ you can achieve by replacing all the question marks in string $ s $ with small Latin letters.

// ## 样例 #1

// ### 样例输入 #1

// ```
// winlose???winl???w??
// win
// ```

// ### 样例输出 #1

// ```
// 5
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// glo?yto?e??an?
// or
// ```

// ### 样例输出 #2

// ```
// 3
// ```

// ## 样例 #3

// ### 样例输入 #3

// ```
// ??c?????
// abcab
// ```

// ### 样例输出 #3

// ```
// 2
// ```

// ## 提示

// In the first example the resulting string $ s $ is "winlosewinwinlwinwin"

// In the second example the resulting string $ s $ is "glorytoreorand". The last letter of the string can be arbitrary.

// In the third example occurrences of string $ t $ are overlapping. String $ s $ with maximal number of occurrences of $ t $ is "abcabcab".
#include <bits/stdc++.h>

const int maxN = 1E5 + 5;
char s[maxN], t[maxN];
int kmp[maxN], f[maxN], g[maxN];

inline void KMP(int m)
{
    kmp[1] = 0;
    for(int i = 2; i <= m; ++i)
    {
        int k = kmp[i - 1];
        while(k && t[k + 1] != t[i]) k = kmp[k];
        kmp[i] = k + (t[k + 1] == t[i]);
    }
}

inline bool check(int idx, int m)
{
    int k = idx - m;
    for(int i = 1; i <= m; ++i)
    {
        if(s[i + k] == t[i] || s[i + k] == '?') continue;
        return false;    
    }
    return true;
}

int main()
{
    scanf("%s", s + 1);
    scanf("%s", t + 1);

    int n = strlen(s + 1), m = strlen(t + 1);
    KMP(m);
    for(int i = m; i <= n; ++i)
    {
        f[i] = f[i - 1];
        if(!check(i, m)) continue;
        g[i] = f[i - m] + 1;
        int k = kmp[m];
        while(k) g[i] = std::max(g[i], g[i - m + k] + 1), k = kmp[k];
        f[i] = std::max(f[i], g[i]);
    }
    printf("%d", f[n]);
    return 0;
}