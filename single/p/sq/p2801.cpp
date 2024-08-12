// # 教主的魔法

// ## 题目描述

// 教主最近学会了一种神奇的魔法，能够使人长高。于是他准备演示给 XMYZ 信息组每个英雄看。于是 $N$ 个英雄们又一次聚集在了一起，这次他们排成了一列，被编号为 $1, 2, \ldots, N$。


// 每个人的身高一开始都是不超过 $1000$ 的正整数。教主的魔法每次可以把闭区间 $[L, R]$（$1≤L≤R≤N$）内的英雄的身高全部加上一个整数 $W$。（虽然 $L=R$ 时并不符合区间的书写规范，但我们可以认为是单独增加第 $L(R)$ 个英雄的身高）


// CYZ、光哥和 ZJQ 等人不信教主的邪，于是他们有时候会问 WD 闭区间 $[L, R]$ 内有多少英雄身高大于等于 $C$，以验证教主的魔法是否真的有效。


// WD 巨懒，于是他把这个回答的任务交给了你。

// ## 输入格式

// 第 $1$ 行为两个整数 $N, Q$。$Q$ 为问题数与教主的施法数总和。

// 第 $2$ 行有 $N$ 个正整数，第 $i$ 个数代表第 $i$ 个英雄的身高。


// 第 $3$ 到第 $Q+2$ 行每行有一个操作：


// 1. 若第一个字母为 `M`，则紧接着有三个数字 $L, R, W$。表示对闭区间 $[L, R]$ 内所有英雄的身高加上 $W$。

// 2. 若第一个字母为 `A`，则紧接着有三个数字 $L, R, C$。询问闭区间 $[L, R]$ 内有多少英雄的身高大于等于 $C$。

// ## 输出格式

// 对每个 `A` 询问输出一行，仅含一个整数，表示闭区间 $[L, R]$ 内身高大于等于 $C$ 的英雄数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 3
// 1 2 3 4 5
// A 1 5 4
// M 3 5 1
// A 1 5 4
// ```

// ### 样例输出 #1

// ```
// 2
// 3
// ```

// ## 提示

// 【输入输出样例说明】

// 原先 $5$ 个英雄身高为 $1, 2, 3, 4, 5$，此时 $[1, 5]$ 间有 $2$ 个英雄的身高大于等于 $4$。教主施法后变为 $1, 2, 4, 5, 6$，此时 $[1, 5]$ 间有 $3$ 个英雄的身高大于等于 $4$。

// 【数据范围】

// 对于 $30\%$ 的数据，$N≤1000$，$Q≤1000$。

// 对于 $100\%$ 的数据，$N≤10^6$，$Q≤3000$，$1≤W≤1000$，$1≤C≤10^9$。

// ---

// $\text{upd 2022.8.18}$：新增加一组 Hack 数据。  
// $\text{upd 2023.8.16}$：新增加一组 [Hack 数据](https://www.luogu.com.cn/discuss/661585)。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E6 + 5, maxB = 230;
int w[maxN], lz[maxB], st[maxB], ed[maxB], inv[maxN], s[maxN], nob;

inline void init(int n){
    nob = sqrt(n / log2(n));
    for(int i = 1; i <= nob; i++){
        st[i] = n / nob * (i - 1) + 1;
        ed[i] = n / nob * i;
    }
    ed[nob] = n;
    std::iota(s, s + n + 1, 0);
    for(int i = 1; i <= nob; i++){
        for(int j = st[i]; j <= ed[i]; j++) inv[j] = i;
        std::sort(s + st[i], s + ed[i] + 1, [&](int a, int b){
            return w[a] < w[b];
        });
    }
}

inline void updata(int l, int r, int v){
    if(inv[l] == inv[r]){
        if(l == st[inv[l]] && r == ed[inv[l]]){
            lz[inv[l]] += v;
            return ;
        }
        for(int i = l; i <= r; i++) w[i] += v;
        std::sort(s + st[inv[l]], s + ed[inv[l]] + 1, [&](int a, int b){
            return w[a] < w[b];
        });
    }
    else{
        for(int i = inv[l] + 1; i < inv[r]; i++) lz[i] += v;
        updata(l, ed[inv[l]], v);
        updata(st[inv[r]], r, v);
    }
}

inline int query(int l, int r, int v){
    int res = 0;
    if(inv[l] == inv[r]){
        v -= lz[inv[l]];
        if(l == st[inv[l]] && r == ed[inv[l]]){
            res += s + ed[inv[l]] + 1 - std::lower_bound(s + st[inv[l]], s + ed[inv[l]] + 1, v, [&](int a, int val){
                return val > w[a];
            });
            return res;
        }
        for(int i = l; i <= r; i++){
            if(w[i] >= v) res++;
        }
    }
    else{
        for(int i = inv[l] + 1; i < inv[r]; i++){
            res += s + ed[i] + 1 - std::lower_bound(s + st[i], s + ed[i] + 1, v - lz[i], [&](int a, int val){
                return val > w[a];
            });
        }
        res += query(l, ed[inv[l]], v);
        res += query(st[inv[r]], r, v);
    }
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, l, r, v;
    char op;
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    init(n);
    for(int i = 0; i < m; i++){
        std::cin >> op >> l >> r >> v;
        if(op == 'M'){
            updata(l, r, v);
        }
        else{
            std::cout << query(l, r, v) << std::endl;
        }
    }
    return 0;
}