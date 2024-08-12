// # [国家集训队] 最长双回文串

// ## 题目描述

// 顺序和逆序读起来完全一样的串叫做回文串。比如 `acbca` 是回文串，而 `abc` 不是：`abc` 的顺序为 `abc`，逆序为 `cba`，不相同。

// 输入长度为 $n$ 的串 $S$，求 $S$ 的最长双回文子串 $T$，即可将 $T$ 分为两部分 $X, Y$（$|X|,|Y|≥1$）且 $X$ 和 $Y$ 都是回文串。

// ## 输入格式

// 一行由小写英文字母组成的字符串 $S$。

// ## 输出格式

// 一行一个整数，表示最长双回文子串的长度。

// ## 样例 #1

// ### 样例输入 #1

// ```
// baacaabbacabb
// ```

// ### 样例输出 #1

// ```
// 12
// ```

// ## 提示

// **样例说明**

// 从第二个字符开始的字符串 `aacaabbacabb` 可分为 `aacaa` 与 `bbacabb` 两部分，且两者都是回文串。

// **数据范围**

// 对于 $100\%$ 的数据，$2\leq |S|\leq 10^5$。

// 2018.12.10，2018.12.15：感谢 @Ycrpro 提供 hack 数据两组。
#include <bits/stdc++.h>

const int maxN = 1E5 + 5;
char tmp[maxN], s[maxN << 1];
int r[maxN << 1], ll[maxN << 1], rr[maxN << 1];

inline int manacher(int n)
{
    n = (n + 1) << 1;

    int mx_c = 0, mx_r = 0;
    for(int i = 1; i <= n; ++i)
    {
        if(mx_r > i) r[i] = std::min(mx_r - i, r[(mx_c << 1) - i]);
        while(s[i + r[i] + 1] == s[i - r[i] - 1]) ++r[i];
        if(mx_r < i + r[i]) mx_r = i + r[i], mx_c = i;
        rr[i + r[i]] = std::max(rr[i + r[i]], r[i]);
        ll[i - r[i]] = std::max(ll[i - r[i]], r[i]);
    }
    int res = 0;
    for(int i = 3; i <= n; i += 2) ll[i] = std::max(ll[i], ll[i - 2] - 2);
    for(int i = n - 3; i >= 1; i -= 2) rr[i] = std::max(rr[i], rr[i + 2] - 2);
    for(int i = 1; i <= n; i += 2) if(rr[i] && ll[i]) res = std::max(res, rr[i] + ll[i]);
    return res;
}

int main()
{
    scanf("%s", tmp + 1);
    int n = strlen(tmp + 1);

    s[0] = '~', s[1] = '#';
    for(int i = 1; i <= n; ++i)
    {
        s[i << 1] = tmp[i];
        s[i << 1 | 1] = '#';
    }    
    s[(n + 1) << 1] = '!';

    std::cout << manacher(n);
    return 0;
}