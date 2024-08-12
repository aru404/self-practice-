// # [CEOI2017] Building Bridges

// ## 题目描述

// 有 $n$ 根柱子依次排列，每根柱子都有一个高度。第 $i$ 根柱子的高度为 $h_i$。

// 现在想要建造若干座桥，如果一座桥架在第 $i$ 根柱子和第 $j$ 根柱子之间，那么需要 $(h_i-h_j)^2$​​ 的代价。

// 在造桥前，所有用不到的柱子都会被拆除，因为他们会干扰造桥进程。第 $i$ 根柱子被拆除的代价为 $w_i$，注意 $w_i$ 不一定非负，因为可能政府希望拆除某些柱子。

// 现在政府想要知道，通过桥梁把第 $1$ 根柱子和第 $n$ 根柱子连接的最小代价。注意桥梁不能在端点以外的任何地方相交。

// ## 输入格式

// 第一行一个正整数 $n$。

// 第二行 $n$ 个空格隔开的整数，依次表示 $h_1,h_2,\cdots,h_n$​​。

// 第三行 $n$ 个空格隔开的整数，依次表示 $w_1,w_2,\cdots,w_n$​​。

// ## 输出格式

// 输出一行一个整数表示最小代价，注意最小代价不一定是正数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6
// 3 8 7 1 6 6
// 0 -1 9 1 2 0
// ```

// ### 样例输出 #1

// ```
// 17
// ```

// ## 提示

// 对于 $100\%$ 的数据，有 $2\le n\le 10^5;0\le h_i,\vert w_i\vert\le 10^6$。
#include <iostream>
#include <bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f

const int maxN = 1E5 + 5;
struct node{
    int k;
    ll b; ll lv, rv;
    node(int k = 0, ll b = 0, ll lv = 0, ll rv = 0):k(k), b(b), lv(lv), rv(rv){}
}tree[maxN << 2];

int h[maxN], w[maxN], rk[maxN], vals[maxN], tmp[maxN], q;
ll sums[maxN], ans[maxN];

inline void init(int n){
    for(int i = 1; i <= n; i++) std::cin >> h[i];
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int a, const int b){return h[a] < h[b];});

    int now = -1;
    for(int i = 1; i <= n; i++){
        if(now < h[tmp[i]]) vals[++q] = now = h[tmp[i]];
        rk[tmp[i]] = q;
    }
}

inline void buildTree(int s, int t, int p){
    tree[p].b = tree[p].lv = tree[p].rv = -INF;
    if(s == t) return ;
    int m = (t + s) >> 1;
    buildTree(s, m, p << 1);
    buildTree(m + 1, t, p << 1 | 1);
}

inline void updata(int s, int t, int p, int k, ll b, ll lv, ll rv){
    if(s == t){
        if(tree[p].lv <= lv) tree[p] = node(k, b, lv, lv);
        return ;
    }
    int m = (t + s) >> 1;
    if(rv <= tree[p].rv && lv <= tree[p].lv) return ;
    if(rv > tree[p].rv && lv > tree[p].lv){
        tree[p] = node(k, b, lv, rv);
        return ;
    }
    updata(s, m, p << 1, k, b, lv, 1ll * k * vals[m] + b);
    updata(m + 1, t, p << 1 | 1, k, b, 1ll * k * vals[m + 1] + b, rv);
}

inline ll query(int s, int t, int id, int p){
    if(s == t) return tree[p].lv;
    ll res = 1ll * tree[p].k * vals[id] + tree[p].b;
    int m = (t + s) >> 1;
    if(id <= m) res = std::max(res, query(s, m, id, p << 1));
    else res = std::max(res, query(m + 1, t, id, p << 1 | 1));
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    init(n);
    for(int i = 1; i <= n; i++) sums[i] = sums[i - 1] + w[i];
    buildTree(1, q, 1);

    ll sq = 1ll * h[1] * h[1], b = -sq + sums[1] - ans[1];
    int k = 2 * h[1];
    updata(1, q, 1, k, b, 1ll * k * vals[1] + b, 1ll * k * vals[q] + b);
    for(int i = 2; i <= n; i++){
        sq = 1ll * h[i] * h[i];
        ans[i] = sq + sums[i - 1] - query(1, q, rk[i], 1);

        k = 2 * h[i];
        b = -sq + sums[i] - ans[i];
        updata(1, q, 1, k, b, 1ll * k * vals[1] + b, 1ll * k * vals[q] + b);
    }

    std::cout << ans[n];
    return 0;
}