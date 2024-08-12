// # Password

// ## 题面翻译

// Asterix，Obelix 和他们的临时伙伴 Suffix、Prefix 已经最终找到了和谐寺。然而和谐寺大门紧闭，就连 Obelix 的运气也没好到能打开它。

// 不久他们发现了一个字符串 $S\ (1\leqslant\vert S\vert\leqslant1000000)$，刻在和谐寺大门下面的岩石上。Asterix 猜想那一定是打开寺庙大门的密码，于是就大声将字符串朗读了出来，然而并没有什么事发生。于是 Asterix 又猜想密码一定是字符串 $S$ 的子串 $T$。

// Prefix 认为 $T$ 是 $S$ 的前缀，Suffix 认为 $T$ 是 $S$ 的后缀，Obelix 却认为 $T$ 应该是 $S$ 中的某一部分，也就是说，$T$ 既不是 $S$ 的前缀，也不是 $S$ 的后缀。

// Asterix 选择子串 $T$ 来满足所有伙伴们的想法。同时，在所有可以被接受的子串变形中，Asterix 选择了最长的一个。当 Asterix 大声读出子串 $T$ 时，寺庙的大门开了。（也就是说，你需要找到既是 $S$ 的前缀又是 $S$ 的后缀同时又在 $S$ 中间出现过的最长子串）

// 现在给你字符串 $S$，你需要找到满足上述要求的子串 $T$。

// ### 输入格式

// 一行一个只包含小写字母的字符串 $S$。

// ### 输出格式

// 输出子串 $T$，如果 $T$ 不存在，输出 `Just a legend`。

// ## 题目描述

// Asterix, Obelix and their temporary buddies Suffix and Prefix has finally found the Harmony temple. However, its doors were firmly locked and even Obelix had no luck opening them.

// A little later they found a string $ s $ , carved on a rock below the temple's gates. Asterix supposed that that's the password that opens the temple and read the string aloud. However, nothing happened. Then Asterix supposed that a password is some substring $ t $ of the string $ s $ .

// Prefix supposed that the substring $ t $ is the beginning of the string $ s $ ; Suffix supposed that the substring $ t $ should be the end of the string $ s $ ; and Obelix supposed that $ t $ should be located somewhere inside the string $ s $ , that is, $ t $ is neither its beginning, nor its end.

// Asterix chose the substring $ t $ so as to please all his companions. Besides, from all acceptable variants Asterix chose the longest one (as Asterix loves long strings). When Asterix read the substring $ t $ aloud, the temple doors opened.

// You know the string $ s $ . Find the substring $ t $ or determine that such substring does not exist and all that's been written above is just a nice legend.

// ## 输入格式

// You are given the string $ s $ whose length can vary from $ 1 $ to $ 10^{6} $ (inclusive), consisting of small Latin letters.

// ## 输出格式

// Print the string $ t $ . If a suitable $ t $ string does not exist, then print "Just a legend" without the quotes.

// ## 样例 #1

// ### 样例输入 #1

// ```
// fixprefixsuffix
// ```

// ### 样例输出 #1

// ```
// fix
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// abcdabc
// ```

// ### 样例输出 #2

// ```
// Just a legend
// ```
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E6 + 5;
int kmp[maxN];

inline void KMP(std::string& s){
    kmp[0] = -1;
    for(size_t i = 1; i < s.size(); ++i){
        int j = kmp[i - 1];
        while(~j && s[i] != s[j + 1]) j = kmp[j];
        kmp[i] = j + (s[i] == s[j + 1]);
    }
}

inline int solve(std::string& s){
    size_t n = s.size();
    std::unordered_set<int> set;
    int k = kmp[n - 1];
    while(~k) set.emplace(k), k = kmp[k];
    for(size_t i = 1; i < n - 1; ++i){
        if(set.count(kmp[i])) k = std::max(kmp[i], k);
    }
    return k + 1;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;
    KMP(s);

    int k = solve(s);
    std::cout << (k? s.substr(0, k):"Just a legend");
    return 0;
}