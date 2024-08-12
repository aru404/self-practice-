// # [POI2012] LIT-Letters

// ## 题目描述

// 给出两个长度相同的的只含大写字母的字符串 $a, b$，每次可以交换 $a$ 中相邻两个字符，求最少的交换次数，使得 $a$ 交换后的得到的字符串与 $b$ 相同。

// ## 输入格式

// 输入的第一行是一个整数，代表字符串的长度 $n$。

// 第二行是一个长度为 $n$ 的字符串，代表 $a$。

// 第三行是一个长度为 $n$ 的字符串，代表 $b$。

// ## 输出格式

// 输出一行一个整数，代表最少的交换次数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// ABC
// BCA
// ```

// ### 样例输出 #1

// ```
// 2
// ```

// ## 提示

// #### 数据规模与约定

// - 对于 $30\%$ 的数据，保证 $n \leq 10^3$。
// - 对于 $100\%$ 的数据，$1 \leq n \leq 10^6$，$a, b$ 中只含大写字母，且数据保证 $a$ 可以变成 $b$。
#include <iostream>
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

const int maxN = 1E6 + 5;
int tree[maxN], rk[maxN], n;
std::vector<int> alpha[26];
std::string s;

inline void updata(int x, int v){
    while(x <= n) tree[x] += v, x += lowbit(x);
}

inline int query(int x){
    int res = 0;
    while(x) res += tree[x], x -= lowbit(x);
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    char c;
    std::cin >> n;
    for(int i = 1; i <= n; i++){
        std::cin >> c;
        alpha[c - 'A'].push_back(i);
    }
    std::cin >> s;
    long long res = 0;
    for(int i = n; i; i--){
        int idx = s[i - 1] - 'A', now = alpha[idx].back();
        alpha[idx].pop_back();
        res += query(now);
        updata(now, 1);
    }
    std::cout << res;
    return 0;
}