// # 三元上升子序列

// ## 题目描述

// Erwin 最近对一种叫 `thair` 的东西巨感兴趣。。。

// 在含有 $n$ 个整数的序列 $a_1,a_2,\ldots,a_n$ 中，三个数被称作`thair`当且仅当 $i<j<k$ 且 $a_i<a_j<a_k$。

// 求一个序列中 `thair` 的个数。

// ## 输入格式

// 开始一行一个正整数 $n$,

// 以后一行 $n$ 个整数 $a_1,a_2,\ldots,a_n$。

// ## 输出格式

// 一行一个整数表示 `thair` 的个数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4
// 2 1 3 4
// ```

// ### 样例输出 #1

// ```
// 2
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 5
// 1 2 2 3 4
// ```

// ### 样例输出 #2

// ```
// 7
// ```

// ## 提示

// #### 样例2 解释

// $7$ 个 `thair` 分别是：

// - 1 2 3
// - 1 2 4
// - 1 2 3
// - 1 2 4
// - 1 3 4
// - 2 3 4
// - 2 3 4

// #### 数据规模与约定

// - 对于 $30\%$ 的数据 保证 $n\le100$；
// - 对于 $60\%$ 的数据 保证 $n\le2000$；
// - 对于 $100\%$ 的数据 保证 $1 \leq n\le3\times10^4$，$1\le a_i\leq 10^5$。
#include <bits/stdc++.h>
#define ll long long
#define lowbit(x) (x & -x)

const int maxN = 3E4 + 5;
int pre[maxN], suf[maxN], w[maxN], rk[maxN], tmp[maxN], k;

inline void init(int n){
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](int a, int b){return w[a] < w[b];});
    int now = 0;
    for(int i = 1; i <= n; i++){
        if(now < w[tmp[i]]) now = w[tmp[i]], k++;
        rk[tmp[i]] = k;
    }
}

inline void updata(int x, int v, int* e){
    while(x <= k) e[x] += v, x += lowbit(x);
}

inline int query(int x, int* e){
    int res = 0;
    while(x) res += e[x], x -= lowbit(x);
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    ll res = 0;
    int n, cnt;
    std::cin >> n; cnt = n;
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    init(n);
    for(int i = 1; i <= n; i++) updata(rk[i], -1, suf);
    for(int i = 1; i <= n; i++){
        updata(rk[i], 1, pre);
        updata(rk[i], 1, suf);
        cnt--;
        res += 1ll * query(rk[i] - 1, pre) * (cnt + query(rk[i], suf));
    }
    std::cout << res;
    return 0;
}