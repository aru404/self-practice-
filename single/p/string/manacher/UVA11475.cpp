// # Extend to Palindrome

// ## 题面翻译

// 输入多个字符串。

// 对于每个字符串  $S$  ，求出一个字符串  $S^*$  ，  $S^*$  需要满足：

// 1.   $S$  为  $S^*$  的前缀；
// 2.   $S^*$  是一个回文字符串；
// 3.   $|S^*|$  应尽可能小；

// 对于每个  $S$  ，输出  $S^*$  ，每行输出以换行符结尾。

// 感谢@info___tion 提供的翻译

// ## 题目描述

// [problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2470

// [PDF](https://uva.onlinejudge.org/external/114/p11475.pdf)

// ![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11475/ae37dadabf3a354b162ed1c713805d6b078797e1.png)

// ## 输入格式

// ![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11475/4d2d2ef490382ca953209c6068aedc5d2dd678ba.png)

// ## 输出格式

// ![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11475/dd218972587d925ba462f27c3ea37bb9bb3b2e1c.png)

// ## 样例 #1

// ### 样例输入 #1

// ```
// aaaa
// abba
// amanaplanacanal
// xyz
// ```

// ### 样例输出 #1

// ```
// aaaa
// abba
// amanaplanacanalpanama
// xyzyx
// ```
#include <bits/stdc++.h>

const int maxN = 1E5 + 5;
int r[maxN << 1];
char tmp[maxN << 1], s[maxN << 1];

inline void mancher(int n)
{
    int m = (n + 1) << 1;
    int mx_r = 0, mx_c = 0;
    r[0] = 0;
    for(int i = 1; i < m; ++i)
    {
        r[i] = 0;
        if(i < mx_r) r[i] = std::min(mx_r - i, r[(mx_c << 1) - i]);
        while(s[i + r[i] + 1] == s[i - r[i] - 1]) ++r[i];
        if(mx_r < i + r[i]) mx_r = i + r[i], mx_c = i;
        if(mx_r == m - 1) break; 
    }

    int t = (n << 1) - r[mx_c] + 1;
    for(int i = n - r[mx_c]; i; --i)
    {
        tmp[t - i] = tmp[i];
    }
    tmp[t] = '\0';
}

int main()
{
    while(scanf("%s", tmp + 1) != EOF)
    {
        int n = strlen(tmp + 1);
        s[0] = '~', s[1] = '#';
        for(int i = 1; i <= n; ++i)
        {
            s[i << 1] = tmp[i];
            s[i << 1 | 1] = '#';
        }
        s[(n + 1) << 1] = '!';

        mancher(n);
        printf("%s\n", tmp + 1);
    }
    return 0;
}