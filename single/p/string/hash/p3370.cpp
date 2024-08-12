// # 【模板】字符串哈希

// ## 题目描述

// 如题，给定 $N$ 个字符串（第 $i$ 个字符串长度为 $M_i$，字符串内包含数字、大小写字母，大小写敏感），请求出 $N$ 个字符串中共有多少个不同的字符串。


// **友情提醒：如果真的想好好练习哈希的话，请自觉。**

// ## 输入格式

// 第一行包含一个整数 $N$，为字符串的个数。

// 接下来 $N$ 行每行包含一个字符串，为所提供的字符串。

// ## 输出格式

// 输出包含一行，包含一个整数，为不同的字符串个数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5
// abc
// aaaa
// abc
// abcc
// 12345
// ```

// ### 样例输出 #1

// ```
// 4
// ```

// ## 提示

// 对于 $30\%$ 的数据：$N\leq 10$，$M_i≈6$，$Mmax\leq 15$。

// 对于 $70\%$ 的数据：$N\leq 1000$，$M_i≈100$，$Mmax\leq 150$。

// 对于 $100\%$ 的数据：$N\leq 10000$，$M_i≈1000$，$Mmax\leq 1500$。


// 样例说明：

// 样例中第一个字符串(abc)和第三个字符串(abc)是一样的，所以所提供字符串的集合为{aaaa,abc,abcc,12345}，故共计4个不同的字符串。


// Tip：
// 感兴趣的话，你们可以先看一看以下三题：

// BZOJ3097：http://www.lydsy.com/JudgeOnline/problem.php?id=3097

// BZOJ3098：http://www.lydsy.com/JudgeOnline/problem.php?id=3098

// BZOJ3099：http://www.lydsy.com/JudgeOnline/problem.php?id=3099

// 如果你仔细研究过了（或者至少仔细看过AC人数的话），我想你一定会明白字符串哈希的正确姿势的^\_^a
#include <iostream>
#include <bits/stdc++.h>
#define uint unsigned int

const uint base1 = 19260817, base2 = 29123;
const uint mod1 = 1E9 + 7, mod2 = 1E9 + 9;

struct hash{
    uint key1, key2;
    bool operator< (const hash& b) const{
        return key1 ^ b.key1? (key1 < b.key1):(key2 < b.key2);
    }

    bool operator!= (const hash& b) const{
        return key1 ^ b.key1 && key2 ^ b.key2;
    }
};

inline uint getHash(std::string& s, const uint base, const uint mod){
    uint v = 0;
    for(size_t i = 0; i < s.size(); ++i){
        v = ((1ull * v * base) % mod + (uint)s[i]) % mod;
    }
    return v;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::string s;
    hash* hs = new hash[n + 1];
    for(int i = 1; i <= n; i++){
        std::cin >> s;
        hs[i].key1 = getHash(s, base1, mod1);
        hs[i].key2 = getHash(s, base2, mod2);
    }

    std::sort(hs + 1, hs + n + 1, std::less<hash>{});
    int res = 1;
    for(int i = 2; i <= n; i++){
        if(hs[i] != hs[i - 1]) ++res;
    }
    std::cout << res;
    return 0;
}