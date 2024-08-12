// # [POI2005] SZA-Template

// ## 题目描述

// 你打算在纸上印一串字母。

// 为了完成这项工作，你决定刻一个印章。印章每使用一次，就会将印章上的**所有**字母印到纸上。

// 同一个位置的相同字符可以印多次。例如：用 `aba` 这个印章可以完成印制 `ababa` 的工作（中间的 `a` 被印了两次）。但是，因为印上去的东西不能被抹掉，在同一位置上印不同字符是不允许的。例如：用 `aba` 这个印章不可以完成印制 `abcba` 的工作。

// 因为刻印章是一个不太容易的工作，你希望印章的字符串长度尽可能小。

// ## 输入格式

// 输入一个长度不超过 $5 \times 10^5$ 的非空字符串（只包含小写字母），代表要在纸上印的字符。

// ## 输出格式

// 输出一个整数，代表印章上字符串长度的最小值。

// ## 样例 #1

// ### 样例输入 #1

// ```
// ababbababbabababbabababbababbaba
// ```

// ### 样例输出 #1

// ```
// 8
// ```

// ## 提示

// 印章为 `ababbaba`。

// 印制过程如下：

// ```plain
// ababbababbabababbabababbababbaba
// ababbaba
//      ababbaba
//             ababbaba
//                    ababbaba
//                         ababbaba
// ```
#include <bits/stdc++.h>

const int maxN = 5E5 + 5;
char s[maxN];
int kmp[maxN], len[maxN], bucket[maxN];

inline void KMP(int n)
{
    for(int i = 2; i <= n; ++i)
    {
        int k = kmp[i - 1];
        while(k && s[k + 1] != s[i]) k = kmp[k];
        kmp[i] = k + (s[k + 1] == s[i]);
    }
}

int main()
{
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    KMP(n);

    len[1] = bucket[1] = 1;

    for(int i = 2; i <= n; ++i)
    {
        len[i] = i;
        if(bucket[len[kmp[i]]] >= i - kmp[i]) len[i] = len[kmp[i]];
        bucket[len[i]] = i;
    }
    printf("%d", len[n]);
    return 0;
}