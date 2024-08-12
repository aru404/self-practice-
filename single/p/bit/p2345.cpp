// # [USACO04OPEN] MooFest G

// ## 题目背景

// [P5094 [USACO04OPEN] MooFest G 加强版](https://www.luogu.com.cn/problem/P5094)

// ## 题目描述

// 约翰的 $n$ 头奶牛每年都会参加“哞哞大会”。

// 哞哞大会是奶牛界的盛事。集会上的活动很多，比如堆干草，跨栅栏，摸牛仔的屁股等等。

// 它们参加活动时会聚在一起，第 $i$ 头奶牛的坐标为 $x_i$，没有两头奶牛的坐标是相同的。

// 奶牛们的叫声很大，第 $i$ 头和第 $j$ 头奶牛交流，会发出
// $\max\{v_i,v_j\}\times |x_i − x_j |$ 
// 的音量，其中 $v_i$ 和 $v_j$ 分别是第 $i$ 头和第 $j$ 头奶牛的听力。

// 假设每对奶牛之间同时都在说话，请计算所有奶牛产生的音量之和是多少。

// ## 输入格式

// 第一行：单个整数 $n$，$1\le n\le2\times 10^4$

// 第二行到第 $n + 1$ 行：第 $i + 1$ 行有两个整数 $v_i$ 和 $x_i$（$1\le v_i,x_i\le2\times 10^4$）。

// ## 输出格式

// 单个整数：表示所有奶牛产生的音量之和

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4
// 3 1
// 2 5
// 2 6
// 4 3
// ```

// ### 样例输出 #1

// ```
// 57
// ```
#include <iostream>
#include <bits/stdc++.h>
#define ll long long
#define lowbit(x) (x & -x)

const int maxN = 2E4 + 5;
int v[maxN], x[maxN], rk[maxN], cnt[maxN], k;
ll s1[maxN], s2[maxN], s3[maxN], tot1 = 0, tot2 = 0, res = 0;

inline void updata(int v, int x1){
    int v1 = v, v2 = v * x1;
    tot1 += v1, tot2 += v2;
    while(v <= k) s1[v] += x1, s2[v] += v1, s3[v] += v2, cnt[v] += 1, v += lowbit(v);
}

inline ll query(int v, int x1){
    ll ans = tot1 * x1 - tot2, v1 = v, v2 = v * x1;
    while(v) ans -= v1 * s1[v], ans -= x1 * s2[v], ans += s3[v], ans += 1ll * cnt[v] * v2, v -= lowbit(v);
    return ans;
}

// inline void cdq(int l, int r){
//     if(l == r) return ;
//     int m = (l + r) >> 1;
//     cdq(l, m);
//     for(int i = m + 1; i <= r; i++){
//         res += query();
//     }
//     cdq(m + 1, r);
// }

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    for(int i = 1; i <= n; i++) std::cin >> v[i] >> x[i];
    k = *std::max_element(v + 1, v + n + 1);
    std::iota(rk, rk + n + 1, 0);
    std::sort(rk + 1, rk + n + 1, [&](const int& a, const int& b){return x[a] < x[b];});
    for(int i = 1; i <= n; i++){
        res += query(v[rk[i]], x[rk[i]]);
        updata(v[rk[i]], x[rk[i]]);
    }
    std::cout << res;
    return 0;
}