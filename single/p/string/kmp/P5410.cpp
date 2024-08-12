// # 【模板】扩展 KMP/exKMP（Z 函数）

// ## 题目描述

// 给定两个字符串 $a,b$，你要求出两个数组：

// - $b$ 的 $z$ 函数数组 $z$，即 $b$ 与 $b$ 的每一个后缀的 LCP 长度。
// - $b$ 与 $a$ 的每一个后缀的 LCP 长度数组 $p$。

// 对于一个长度为 $n$ 的数组 $a$，设其权值为 $\operatorname{xor}_{i=1}^n i \times (a_i + 1)$。

// ## 输入格式

// 两行两个字符串 $a,b$。

// ## 输出格式

// 第一行一个整数，表示 $z$ 的权值。

// 第二行一个整数，表示 $p$ 的权值。

// ## 样例 #1

// ### 样例输入 #1

// ```
// aaaabaa
// aaaaa
// ```

// ### 样例输出 #1

// ```
// 6
// 21
// ```

// ## 提示

// **样例解释：**

// $z = \{5\ 4\ 3\ 2\ 1\}$，$p = \{4\ 3\ 2\ 1\ 0\ 2\ 1\}$。

// ---

// **数据范围：**

// 对于第一个测试点，$|a|,|b| \le 2 \times 10^3$。

// 对于第二个测试点，$|a|,|b| \le 2 \times 10^5$。

// 对于 $100\%$ 的数据，$1 \le |a|,|b| \le 2 \times 10^7$，所有字符均为小写字母。
#include <bits/stdc++.h>

const int maxN = 2E7 + 5;

int b_z[maxN], p[maxN];
char a[maxN], b[maxN];

inline void exKMP(int n)
{
    int mx_r = 0, mx_l = 0;
    for(int i = 1; i < n; ++i)
    {
        if(mx_r >= i) b_z[i] = std::min(b_z[i - mx_l], mx_r - i + 1);
        while(i + b_z[i] < n && b[i + b_z[i]] == b[b_z[i]]) ++b_z[i];
        if(mx_r < i + b_z[i] - 1) mx_r = i + b_z[i] - 1, mx_l = i;
    }
}

inline void match(int n, int m)
{
    int mx_r = 0, mx_l = 0;
    for(int i = 0; i < n; ++i)
    {
        if(mx_r > i) p[i] = std::min(b_z[i - mx_l], mx_r - i + 1);
        while(i + p[i] < n && p[i] < m && a[i + p[i]] == b[p[i]]) ++p[i];
        if(mx_r < i + p[i] - 1) mx_r = i + p[i] - 1, mx_l = i;
    }
    b_z[0] = m;
}

int main()
{
    scanf("%s", a);
    scanf("%s", b);

    int n = strlen(b);
    int m = strlen(a);
    exKMP(n);
    match(m, n);
    long long res = 0;
    for(int i = 0; i < n; ++i) res ^= 1ll * (i + 1) * (b_z[i] + 1);
    std::cout << res << std::endl;
    res = 0;
    for(int i = 0; i < m; ++i) res ^= 1ll * (i + 1) * (p[i] + 1);
    std::cout << res << std::endl;
    return 0;
}