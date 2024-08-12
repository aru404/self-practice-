// # 【模板】manacher

// ## 题目描述

// 给出一个只由小写英文字符 $\texttt a,\texttt b,\texttt c,\ldots\texttt y,\texttt z$ 组成的字符串 $S$ ,求 $S$ 中最长回文串的长度 。

// 字符串长度为 $n$。

// ## 输入格式

// 一行小写英文字符 $\texttt a,\texttt b,\texttt c,\cdots,\texttt y,\texttt z$ 组成的字符串 $S$。

// ## 输出格式

// 一个整数表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// aaa
// ```

// ### 样例输出 #1

// ```
// 3
// ```

// ## 提示
 
// $1\le n\le 1.1\times 10^7$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1.1E7 + 10;
int r[maxN << 1];
char s[maxN << 1], tmp[maxN];

inline void manacher(int n){
    int maxR = 0, maxC = 0;
    for(int i = 1; i < n; ++i){
        if(maxR > i) r[i] = std::min(r[(maxC << 1) - i], maxR - i);
        while(s[i - r[i] - 1] == s[i + r[i] + 1]) ++r[i];
        if(maxR < i + r[i]) maxC = i, maxR = i + r[i];
    }
}

int main(){
    s[0] = '~';
    s[1] = '#';
    scanf("%s", tmp + 1);
    int n = strlen(tmp + 1);
    for(int i = 1; i <= n; ++i){
        s[i << 1] = tmp[i];
        s[i << 1 | 1] = '#';
    }
    s[(n + 1) << 1] = '&';
    n <<= 1, n |= 1;
    manacher(n);
    std::cout << *std::max_element(r + 1, r + n + 1);
    return 0;
}