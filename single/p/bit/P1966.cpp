// # [NOIP2013 提高组] 火柴排队

// ## 题目背景

// NOIP2013 提高组 D1T2

// ## 题目描述

// 涵涵有两盒火柴，每盒装有 $n$ 根火柴，每根火柴都有一个高度。 现在将每盒中的火柴各自排成一列， 同一列火柴的高度互不相同， 两列火柴之间的距离定义为：$ \sum (a_i-b_i)^2$。

// 其中 $a_i$ 表示第一列火柴中第 $i$ 个火柴的高度，$b_i$ 表示第二列火柴中第  $i$ 个火柴的高度。

// 每列火柴中相邻两根火柴的位置都可以交换，请你通过交换使得两列火柴之间的距离最小。请问得到这个最小的距离，最少需要交换多少次？如果这个数字太大，请输出这个最小交换次数对 $10^8-3$ 取模的结果。

// ## 输入格式

// 共三行，第一行包含一个整数 $n$，表示每盒中火柴的数目。

// 第二行有 $n$ 个整数，每两个整数之间用一个空格隔开，表示第一列火柴的高度。

// 第三行有 $n$ 个整数，每两个整数之间用一个空格隔开，表示第二列火柴的高度。

// ## 输出格式

// 一个整数，表示最少交换次数对 $10^8-3$ 取模的结果。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4
// 2 3 1 4
// 3 2 1 4
// ```

// ### 样例输出 #1

// ```
// 1
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 4
// 1 3 4 2
// 1 7 2 4
// ```

// ### 样例输出 #2

// ```
// 2
// ```

// ## 提示

// **输入输出样例说明一**

// 最小距离是 $ 0$，最少需要交换 $1$ 次，比如：交换第 $1 $ 列的前 $ 2$ 根火柴或者交换第 $2$ 列的前 $2 $ 根火柴。

// **输入输出样例说明二**

// 最小距离是 $10$，最少需要交换 $2$ 次，比如：交换第 $1$ 列的中间 $2$ 根火柴的位置，再交换第 $2$ 列中后 $2$ 根火柴的位置。

// **数据范围**

// 对于 $10\%$ 的数据， $1 \leq n \leq 10$；

// 对于 $30\%$ 的数据，$1 \leq n \leq 100$；

// 对于 $60\%$ 的数据，$1 \leq n \leq 10^3$；

// 对于 $100\%$ 的数据，$1 \leq n \leq 10^5$，$0 \leq$ 火柴高度 $< 2^{31}$.
#include <iostream>
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

const int maxN = 1E5 + 5, mod = 1E8 - 3;

int tree[maxN], rk[maxN], tmp1[maxN], tmp2[maxN], a[maxN], b[maxN], n;

inline void updata(int x){
    while(x <= n) ++tree[x], x += lowbit(x);
}

inline int query(int x){
    int res = 0;
    while(x) res += tree[x], x -= lowbit(x);
    return res;
}

inline void init(){
    std::cin >> n;
    for(int i = 1; i <= n; i++) std::cin >> a[i];
    for(int i = 1; i <= n; i++) std::cin >> b[i];
    std::iota(tmp1, tmp1 + n + 1, 0);
    std::sort(tmp1 + 1, tmp1 + n + 1, [&](const int& x, const int& y){return a[x] ^ a[y]? a[x] < a[y]:x < y;});
    std::iota(tmp2, tmp2 + n + 1, 0);
    std::sort(tmp2 + 1, tmp2 + n + 1, [&](const int& x, const int& y){return b[x] ^ b[y]? b[x] < b[y]:x < y;});
    for(int i = 1; i <= n; i++) rk[tmp2[i]] = i;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int cnt = 0;
    init();
    for(int i = n; i; i--){
        cnt = (cnt + query(tmp1[rk[i]])) % mod;
        updata(tmp1[rk[i]]);
    }
    std::cout << cnt;
    return 0;
}