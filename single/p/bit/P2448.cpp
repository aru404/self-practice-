// # 无尽的生命

// ## 题目描述

// 逝者如斯夫，不舍昼夜！

// 叶良辰认为，他的寿命是无限长的，而且每天都会进步。

// 叶良辰的生命的第一天，他有 $1$ 点能力值。第二天，有 $2$ 点。第 $n$ 天，就有 $n$ 点。也就是 $S_i=i$。

// 但是调皮的小A使用时光机，告诉他第 $x$ 天和第 $y$ 天，就可以任意交换某两天的能力值。即 $S_x\leftrightarrow S_y$。

// 小A玩啊玩，终于玩腻了。

// 叶良辰：小A你给我等着，我有 $100$ 种办法让你生不如死。除非能在 $1$ 秒钟之内告知有多少对“异常对”。也就是说，最后的能力值序列，有多少对的两天 $x,y$，其中 $x<y$，但是能力值 $S_x>S_y$？

// 小A：我好怕怕啊。

// 于是找到了你。

// ## 输入格式

// 第一行一个整数 $k$，表示小A玩了多少次时光机

// 接下来 $k$ 行，$x_i,y_i$，表示将 $S_{x_i}$ 与 $S_{y_i}$ 进行交换。

// ## 输出格式

// 输出共一行，表示有多少“异常对”。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 2
// 4 2
// 1 4
// ```

// ### 样例输出 #1

// ```
// 4
// ```

// ## 提示

// 样例说明

// - 最开始是 $1,2,3,4,5,6\cdots$
// - 然后是 $1,4,3,2,5,6\cdots$
// - 然后是 $2,4,3,1,5,6\cdots$

// 符合的对是 $(1,4),(2,3),(2,4),(3,4)$。


// - 对于 $30\%$  的数据，$x_i,y_i\le 2\times 10^3$；
// - 对于 $70\%$  的数据，$x_i,y_i\le 10^5$；
// - 对于 $100\%$ 的数据，$x_i.y_i\le 2^{31}-1$，$k\le 10^5$。
#include <iostream>
#include <bits/stdc++.h>
#define ll long long
#define lowbit(x) (x & -x)

const int maxN = 1E5 + 5;

int tree[maxN << 2], tmp1[maxN], tmp2[maxN], rkx[maxN], rky[maxN], rk[maxN << 2], w[maxN << 2], k;
unsigned int x[maxN], y[maxN];

inline void updata(int x, int v){
    while(x <= k) tree[x] += v, x += lowbit(x);
}

inline int query(int x){
    int res = 0;
    while(x) res += tree[x], x -= lowbit(x);
    return res;
}

inline void init(int n){
    for(int i = 0; i < n; i++) std::cin >> x[i] >> y[i];
    std::iota(tmp1, tmp1 + n + 1, 0);
    std::iota(tmp2, tmp2 + n + 1, 0);
    x[n] = y[n] = 1 << 31;
    std::sort(tmp1, tmp1 + n, [&](const int& a, const int& b){return x[a] < x[b];});
    std::sort(tmp2, tmp2 + n, [&](const int& a, const int& b){return y[a] < y[b];});
    unsigned int now = 0; int idx1 = 0, idx2 = 0;
    while(idx1 < n || idx2 < n){
        unsigned int m = std::min(x[tmp1[idx1]], y[tmp2[idx2]]);
        if(now < m){
            w[++k] = m - now - 1;
            if(!w[k]) w[k] = 1;
            else w[++k] = 1;
            now = m;
        }
        if(x[tmp1[idx1]] == m) rkx[tmp1[idx1++]] = k;
        if(y[tmp2[idx2]] == m) rky[tmp2[idx2++]] = k;
    }
    std::iota(rk, rk + k + 1, 0);
    for(int i = 0; i < n; i++) std::swap(rk[rkx[i]], rk[rky[i]]);
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n; ll res = 0;
    std::cin >> n;
    init(n);
    for(int i = k; i; i--){
        res += 1ll * w[i] * query(rk[i]);
        updata(rk[i], w[i]);
    }
    std::cout << res;
    return 0;
}