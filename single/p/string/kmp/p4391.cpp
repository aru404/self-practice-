// # [BOI2009] Radio Transmission 无线传输

// ## 题目描述

// 给你一个字符串 $s_1$，它是由某个字符串 $s_2$ 不断自我连接形成的（保证至少重复 $2$ 次）。但是字符串 $s_2$ 是不确定的，现在只想知道它的最短长度是多少。

// ## 输入格式

// 第一行一个整数 $L$，表示给出字符串的长度。 

// 第二行给出字符串 $s_1$ 的一个子串，全由小写字母组成。

// ## 输出格式

// 仅一行，表示 $s_2$ 的最短长度。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 8
// cabcabca
// ```

// ### 样例输出 #1

// ```
// 3
// ```

// ## 提示

// #### 样例输入输出 1 解释
// 对于样例，我们可以利用 $\texttt{abc}$ 不断自我连接得到 $\texttt{abcabcabcabc}$，读入的 $\texttt{cabcabca}$，是它的子串。

// #### 规模与约定
// 对于全部的测试点，保证 $1 < L \le 10^6$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E6 + 5;
int kmp[maxN];

inline void KMP(std::string& s){
    kmp[0] = -1;
    for(size_t i = 1; i < s.size(); ++i){
        int j = kmp[i - 1];
        while(~j && s[j + 1] != s[i]) j = kmp[j];
        kmp[i] = j + (s[j + 1] == s[i]);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::string s;
    std::cin >> n >> s;
    KMP(s);
    std::cout << n - 1 - kmp[n - 1];
    return 0;
}