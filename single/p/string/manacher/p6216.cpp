// # 回文匹配

// ## 题目描述

// 对于一对字符串 $(s_1,s_2)$，若 $s_1$ 的长度为奇数的子串 $(l,r)$ 满足 $(l,r)$ 是回文的，那么 $s_1$ 的“分数”会增加 $s_2$ 在 $(l,r)$ 中出现的次数。

// 现在给出一对 $(s_1,s_2)$，请计算出 $s_1$ 的“分数”。

// 答案对 $2 ^ {32}$ 取模。

// ## 输入格式

// 第一行两个整数，$n,m$，表示 $s_1$ 的长度和 $s_2$ 的长度。

// 第二行两个字符串，$s_1,s_2$。

// ## 输出格式

// 一行一个整数，表示 $s_1$ 的分数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 10 2
// ccbccbbcbb bc
// ```

// ### 样例输出 #1

// ```
// 4
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 20 2
// cbcaacabcbacbbabacca ba
// ```

// ### 样例输出 #2

// ```
// 4
// ```

// ## 提示

// **【样例解释】**

//    对于样例一：

//    子串 $(1,5)$ 中 $s_2$ 出现了一次，子串 $(2,4)$ 中 $s_2$ 出现了一次。

//    子串 $(7,9)$ 中 $s_2$ 出现了一次，子串 $(6,10)$ 中 $s_2$ 出现了一次。

// --------------------------------------

// **【数据范围】**

// **本题采用捆绑测试。**

// - 对于 $100\%$ 的数据：$1 \le n,m \le 3 \times 10 ^ 6$，字符串中的字符都是小写字母。

// - **详细的数据范围：**

//   | Subtask 编号 |     $n,m \le$     | 分值 |
//   | :----------: | :---------------: | :--: |
//   |     $1$      |       $100$       | $15$ |
//   |     $2$      |     $10 ^ 3$      | $15$ |
//   |     $3$      | $5 \times 10 ^ 3$ | $20$ |
//   |     $4$      | $4 \times 10 ^ 5$ | $30$ |
//   |     $5$      | $3 \times 10 ^ 6$ | $20$ |
#include <bits/stdc++.h>

const int maxN = 3E6 + 5;
int kmp[maxN], r[maxN << 1];
unsigned int sums_2[maxN];
char s1[maxN], s2[maxN], s[maxN << 1];

inline void KMP(char* str, int n)
{
    kmp[1] = 0;
    for(int i = 2; i <= n; ++i)
    {
        int k = kmp[i - 1];
        while(k && str[k + 1] != str[i]) k = kmp[k];
        kmp[i] = k + (str[k + 1] == str[i]);
    }
}

inline void mancher(char* str, int n)
{
    int m = (n + 1) << 1;
    s[0] = '~', s[1] = '#';
    for(int i = 1; i <= n; ++i)
    {
        s[i << 1] = str[i];
        s[i << 1 | 1] = '#';
    }
    s[m] = '!';

    int mx_r = 0, mx_c = 0;
    for(int i = 1; i < m; ++i)
    {
        if(mx_r > i) r[i] = std::min(mx_r - i, r[(mx_c << 1) - i]);
        while(s[i + r[i] + 1] == s[i - r[i] - 1]) ++r[i];
        if(mx_r < i + r[i]) mx_r = i + r[i], mx_c = i;
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s %s", s1 + 1, s2 + 1);
    mancher(s1, n);
    KMP(s2, m);

    sums_2[0] = 0;
    unsigned int sum = 0;
    int idx = 0;
    for(int i = 1; i <= n; ++i)
    {
        while(idx && s1[i] != s2[idx + 1]) idx = kmp[idx];
        if(s1[i] == s2[idx + 1]) ++idx;
        if(idx == m)
        {
            idx = kmp[idx];
            ++sum;
        }
        sums_2[i] = sums_2[i - 1] + sum;
    }

    unsigned int res = 0;
    int k = m >> 1;
    for(int i = 2; i <= n; ++i)
    {
        if(r[i << 1] < m) continue;
        int p = r[i << 1] >> 1;
        res += (sums_2[i + p] - sums_2[i + k - 1]) - (sums_2[i - k + m - 2] - sums_2[i - p + m - 3]);
    }

    if(m == 1 && s1[1] == s2[1]) ++res;
    std::cout << res;
    return 0;
}