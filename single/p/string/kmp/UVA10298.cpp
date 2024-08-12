// # Power Strings

// ## 题面翻译

// ### 题意简述：

// 求一个字符串由多少个重复的子串连接而成。

// 例如 `ababab` 由三个 `ab` 连接而成，`abcd` 由 `abcd` 由一个 `abcd` 连接而成。

// ### 输入格式

// **本题多组数据**。

// 每一组数据仅有一行，这一行仅有一个字符串 $s$。

// 输入的结束标志为一个 `.`。

// ### 输出格式

// 对于每一组数据，输出这组字符串由多少个重复的子串连接而成。

// ### 说明/提示

// $1\le |s|\le 10^6$。

// ## 题目描述

// [problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1239

// [PDF](https://uva.onlinejudge.org/external/102/p10298.pdf)

// ![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10298/5a33977ad432cf783324c99a648deeedd9df4d47.png)

// ## 输入格式

// ![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10298/48a79d2d21165840dc626d1c31c7512125b674f1.png)

// ## 输出格式

// ![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10298/c81d8cc64fae1d01af82bea56512daebaba439df.png)

// ## 样例 #1

// ### 样例输入 #1

// ```
// abcd
// aaaa
// ababab
// .
// ```

// ### 样例输出 #1

// ```
// 1
// 4
// 3
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

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    do{
        std::cin >> s;
        if(s != "."){
            KMP(s);
            std::cout << s.size() / (s.size() - kmp[s.size() - 1] - 1) << '\n';
        }
    }while(s != ".");
    return 0;
}