// # 上帝造题的七分钟 2 / 花神游历各国

// ## 题目背景

// XLk 觉得《上帝造题的七分钟》不太过瘾，于是有了第二部。

// ## 题目描述

// "第一分钟，X 说，要有数列，于是便给定了一个正整数数列。

// 第二分钟，L 说，要能修改，于是便有了对一段数中每个数都开平方(下取整)的操作。

// 第三分钟，k 说，要能查询，于是便有了求一段数的和的操作。

// 第四分钟，彩虹喵说，要是 noip 难度，于是便有了数据范围。

// 第五分钟，诗人说，要有韵律，于是便有了时间限制和内存限制。

// 第六分钟，和雪说，要省点事，于是便有了保证运算过程中及最终结果均不超过 $64$ 位有符号整数类型的表示范围的限制。

// 第七分钟，这道题终于造完了，然而，造题的神牛们再也不想写这道题的程序了。"

// ——《上帝造题的七分钟·第二部》

// 所以这个神圣的任务就交给你了。

// ## 输入格式

// 第一行一个整数 $n$，代表数列中数的个数。

// 第二行 $n$ 个正整数，表示初始状态下数列中的数。

// 第三行一个整数 $m$，表示有 $m$ 次操作。

// 接下来 $m$ 行每行三个整数 `k l r`。

// - $k=0$ 表示给 $[l,r]$ 中的每个数开平方（下取整）。

// - $k=1$ 表示询问 $[l,r]$ 中各个数的和。

// **数据中有可能 $l>r$，所以遇到这种情况请交换 $l$ 和 $r$。**

// ## 输出格式

// 对于询问操作，每行输出一个回答。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 10
// 1 2 3 4 5 6 7 8 9 10
// 5
// 0 1 10
// 1 1 10
// 1 1 5
// 0 5 8
// 1 4 8
// ```

// ### 样例输出 #1

// ```
// 19
// 7
// 6
// ```

// ## 提示

// 对于 $30\%$ 的数据，$1\le n,m\le 10^3$，数列中的数不超过 $32767$。

// 对于 $100\%$ 的数据，$1\le n,m\le 10^5$，$1\le l,r\le n$，数列中的数大于 $0$，且不超过 $10^{12}$。
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

const int maxN = 1E5 + 5, maxB = 320;
int st[maxB], ed[maxB], inv[maxN], nob;
ll sum[maxB], w[maxN];
bool tag[maxB];

inline void init(int n){
    nob = sqrt(n);
    for(int i = 1; i <= nob; i++){
        st[i] = n / nob * (i - 1) + 1;
        ed[i] = n / nob * i;
    }
    ed[nob] = n;
    for(int i = 1; i <= nob; i++){
        tag[i] = 1;
        for(int j = st[i]; j <= ed[i]; j++){
            inv[j] = i;
            sum[i] += w[j], tag[i] &= w[j] <= 1;
        }
    }
}

inline void updata(int l, int r){
    if(inv[l] == inv[r]){
        if(tag[inv[l]]) return ;
        for(int i = l; i <= r; i++) if(w[i] > 1) w[i] = sqrt(w[i]);
        tag[inv[l]] = 1, sum[inv[l]] = 0;
        for(int i = st[inv[l]]; i <= ed[inv[l]]; i++){
            sum[inv[l]] += w[i];
            tag[inv[i]] &= w[i] <= 1;
        }
    }
    else{
        updata(l, ed[inv[l]]), updata(st[inv[r]], r);
        for(int i = inv[l] + 1; i < inv[r]; i++){
            if(!tag[i]) updata(st[i], ed[i]);
        }
    }
}

inline ll query(int l, int r){
    ll res = 0;
    if(inv[l] == inv[r]){
        if(l == st[inv[l]] && r == ed[inv[l]]) return sum[inv[l]];
        for(int i = l; i <= r; i++) res += w[i];
    }
    else{
        res += query(l, ed[inv[l]]), res += query(st[inv[r]], r);
        for(int i = inv[l] + 1; i < inv[r]; i++) res += sum[i];
    }
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, l, r, op;
    std::cin >> n;
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    init(n);
    std::cin >> m;
    for(int i = 0; i < m; i++){
        std::cin >> op >> l >> r;
        if(l > r) std::swap(l, r);
        if(!op) updata(l, r);
        else std::cout << query(l, r) << '\n';
    }
    return 0;
}