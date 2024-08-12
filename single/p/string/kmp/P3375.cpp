// # 【模板】KMP

// ## 题目描述

// 给出两个字符串 $s_1$ 和 $s_2$，若 $s_1$ 的区间 $[l, r]$ 子串与 $s_2$ 完全相同，则称 $s_2$ 在 $s_1$ 中出现了，其出现位置为 $l$。  
// 现在请你求出 $s_2$ 在 $s_1$ 中所有出现的位置。

// 定义一个字符串 $s$ 的 border 为 $s$ 的一个**非 $s$ 本身**的子串 $t$，满足 $t$ 既是 $s$ 的前缀，又是 $s$ 的后缀。  
// 对于 $s_2$，你还需要求出对于其每个前缀 $s'$ 的最长 border $t'$ 的长度。

// ## 输入格式

// 第一行为一个字符串，即为 $s_1$。  
// 第二行为一个字符串，即为 $s_2$。

// ## 输出格式

// 首先输出若干行，每行一个整数，**按从小到大的顺序**输出 $s_2$ 在 $s_1$ 中出现的位置。  
// 最后一行输出 $|s_2|$ 个整数，第 $i$ 个整数表示 $s_2$ 的长度为 $i$ 的前缀的最长 border 长度。

// ## 样例 #1

// ### 样例输入 #1

// ```
// ABABABC
// ABA
// ```

// ### 样例输出 #1

// ```
// 1
// 3
// 0 0 1
// ```

// ## 提示

// ### 样例 1 解释

//  ![](https://cdn.luogu.com.cn/upload/pic/2257.png)。
 
// 对于 $s_2$ 长度为 $3$ 的前缀 `ABA`，字符串 `A` 既是其后缀也是其前缀，且是最长的，因此最长 border 长度为 $1$。


// ### 数据规模与约定

// **本题采用多测试点捆绑测试，共有 3 个子任务**。

// - Subtask 1（30 points）：$|s_1| \leq 15$，$|s_2| \leq 5$。
// - Subtask 2（40 points）：$|s_1| \leq 10^4$，$|s_2| \leq 10^2$。
// - Subtask 3（30 points）：无特殊约定。

// 对于全部的测试点，保证 $1 \leq |s_1|,|s_2| \leq 10^6$，$s_1, s_2$ 中均只含大写英文字母。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E6 + 5;

int kmp[maxN];

inline void KMP(std::string& s){
    kmp[0] = -1;
    for(unsigned int i = 1; i < s.size(); i++){
        int j = kmp[i - 1];
        while(~j && s[i] != s[j + 1]) j = kmp[j];
        kmp[i] = j + (s[i] == s[j + 1]);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s1, s2;
    std::cin >> s1 >> s2;
    KMP(s2);

    int idx = -1;
    for(unsigned int i = 0; i < s1.size(); i++){
        while(~idx && s1[i] != s2[idx + 1]) idx = kmp[idx];
        if(s1[i] == s2[idx + 1]) ++idx;
        if(idx == (int)s2.size() - 1){
            std::cout << i - s2.size() + 2 << '\n';
            idx = kmp[idx];
        }
    }

    for(unsigned int i = 0; i < s2.size(); i++) std::cout << kmp[i] + 1 << ' ';
    return 0;
}