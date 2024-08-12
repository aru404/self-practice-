// # [SCOI2010] 序列操作

// ## 题目描述

// lxhgww 最近收到了一个 $01$ 序列，序列里面包含了 $n$ 个数，下标从 $0$ 开始。这些数要么是 $0$，要么是 $1$，现在对于这个序列有五种变换操作和询问操作：

// - `0 l r` 把 $[l, r]$ 区间内的所有数全变成 $0$；
// - `1 l r` 把 $[l, r]$ 区间内的所有数全变成 $1$；
// - `2 l r` 把 $[l,r]$ 区间内的所有数全部取反，也就是说把所有的 $0$ 变成 $1$，把所有的 $1$ 变成 $0$；
// - `3 l r` 询问 $[l, r]$ 区间内总共有多少个 $1$；
// - `4 l r` 询问 $[l, r]$ 区间内最多有多少个连续的 $1$。

// 对于每一种询问操作，lxhgww 都需要给出回答，聪明的程序员们，你们能帮助他吗？

// ## 输入格式

// 第一行两个正整数 $n,m$，表示序列长度与操作个数。  
// 第二行包括 $n$ 个数，表示序列的初始状态。  
// 接下来 $m$ 行，每行三个整数，表示一次操作。

// ## 输出格式

// 对于每一个询问操作，输出一行一个数，表示其对应的答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 10 10
// 0 0 0 1 1 0 1 0 1 1
// 1 0 2
// 3 0 5
// 2 2 2
// 4 0 4
// 0 3 6
// 2 3 7
// 4 2 8
// 1 0 5
// 0 5 6
// 3 3 9
// ```

// ### 样例输出 #1

// ```
// 5
// 2
// 6
// 5
// ```

// ## 提示

// 【数据范围】  
// 对于 $30\%$ 的数据，$1\le n,m \le 1000$；  
// 对于$100\%$ 的数据，$1\le n,m \le 10^5$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E5 + 5;
int mxL1[maxN << 2], mxR1[maxN << 2], mx1[maxN << 2], mxL2[maxN << 2], mxR2[maxN << 2], mx2[maxN << 2], cnt[maxN << 2], lz[maxN << 2];
bool rev[maxN << 2], w[maxN];

inline void pushUp(int s, int t, int m, int p){
    cnt[p] = cnt[p << 1] + cnt[p << 1 | 1];
    mxL1[p] = mxL1[p << 1] + (mxL1[p << 1] == m - s + 1? mxL1[p << 1 | 1]:0);
    mxR1[p] = mxR1[p << 1 | 1] + (mxL1[p << 1 | 1] == t - m? mxR1[p << 1]:0);
    mx1[p] = std::max({mx1[p << 1], mx1[p << 1 | 1], mxL1[p << 1 | 1] + mxR1[p << 1]});
    mxL2[p] = mxL2[p << 1] + (mxL2[p << 1] == m - s + 1? mxL2[p << 1 | 1]:0);
    mxR2[p] = mxR2[p << 1 | 1] + (mxL2[p << 1 | 1] == t - m? mxR2[p << 1]:0);
    mx2[p] = std::max({mx2[p << 1], mx2[p << 1 | 1], mxL2[p << 1 | 1] + mxR2[p << 1]}); 
}

inline void pushDown(int s, int t, int m, int p){
    if(lz[p]){
        rev[p << 1] = rev[p << 1 | 1] = 0;
        lz[p << 1] = lz[p << 1 | 1] = lz[p];
        if(lz[p] == 1){
            cnt[p << 1] = mx1[p << 1] = mxL1[p << 1] = mxR1[p << 1] = m - s + 1;
            cnt[p << 1 | 1] = mx1[p << 1 | 1] = mxL1[p << 1 | 1] = mxR1[p << 1 | 1] = t - m;
            mx2[p << 1] = mx2[p << 1 | 1] = 0;
            mxL2[p << 1] = mxL2[p << 1 | 1] = mxR2[p << 1] = mxR2[p << 1 | 1] = 0;
        }
        else{
            cnt[p << 1] = cnt[p << 1 | 1] = mx1[p << 1] = mx1[p << 1 | 1] = 0;
            mxL1[p << 1] = mxL1[p << 1 | 1] = mxR1[p << 1] = mxR1[p << 1 | 1] = 0;
            mx2[p << 1] = mxL2[p << 1] = mxR2[p << 1] = m - s + 1;
            mx2[p << 1 | 1] = mxL2[p << 1 | 1] = mxR2[p << 1 | 1] = t - m;
        }
        lz[p] = 0;
    }
    if(rev[p]){
        cnt[p << 1] = m - s + 1 - cnt[p << 1];
        cnt[p << 1 | 1] = t - m - cnt[p << 1 | 1];
        std::swap(mxL1[p << 1], mxL2[p << 1]), std::swap(mxR1[p << 1], mxR2[p << 1]);
        std::swap(mxL1[p << 1 | 1], mxL2[p << 1 | 1]), std::swap(mxR1[p << 1 | 1], mxR2[p << 1 | 1]);
        std::swap(mx1[p << 1], mx2[p << 1]), std::swap(mx1[p << 1 | 1], mx2[p << 1 | 1]);
        if(lz[p << 1]) lz[p << 1] = -lz[p << 1];
        else rev[p << 1] ^= 1;
        if(lz[p << 1 | 1]) lz[p << 1 | 1] = -lz[p << 1 | 1];
        else rev[p << 1 | 1] ^= 1;
        rev[p] = 0;
    }
}

inline void buildTree(int s, int t, int p){
    if(s == t){
        if(w[s]) cnt[p] = mx1[p] = mxL1[p] = mxR1[p] = 1;
        else mx2[p] = mxL2[p] = mxR2[p] = 1;
        return ;
    }
    int m = (t + s) >> 1;
    buildTree(s, m, p << 1);
    buildTree(m + 1, t, p << 1 | 1);
    pushUp(s, t, m, p);
}

inline void updataCov(int l, int r, bool v, int s, int t, int p){
    if(l <= s && r >= t){
        rev[p] = 0;
        if(v){
            cnt[p] = mx1[p] = mxL1[p] = mxR1[p] = t - s + 1;
            mx2[p] = mxL2[p] = mxR2[p] = 0;
            lz[p] = 1;
        }
        else{
            cnt[p] = mx1[p] = mxL1[p] = mxR1[p] = 0;
            mx2[p] = mxL2[p] = mxR2[p] = t - s + 1;
            lz[p] = -1;
        }
        return ;
    }
    int m = (t + s) >> 1;
    pushDown(s, t, m, p);
    if(l <= m) updataCov(l, r, v, s, m, p << 1);
    if(r > m) updataCov(l, r, v, m + 1, t, p << 1 | 1);
    pushUp(s, t, m, p); 
}

inline void updataRev(int l, int r, int s, int t, int p){
    if(l <= s && r >= t){
        if(lz[p]) lz[p] = -lz[p];
        else rev[p] ^= 1;
        std::swap(mx1[p], mx2[p]), cnt[p] = t - s + 1 - cnt[p];
        std::swap(mxL1[p], mxL2[p]), std::swap(mxR1[p], mxR2[p]);
        return ;
    }
    int m = (t + s) >> 1;
    pushDown(s, t, m, p);
    if(l <= m) updataRev(l, r, s, m, p << 1);
    if(r > m) updataRev(l, r, m + 1, t, p << 1 | 1);
    pushUp(s, t, m, p);
}

inline int queryCnt(int l, int r, int s, int t, int p){
    if(l <= s && r >= t) return cnt[p];
    int res = 0, m = (t + s) >> 1;
    pushDown(s, t, m, p);
    if(l <= m) res += queryCnt(l, r, s, m, p << 1);
    if(r > m) res += queryCnt(l, r, m + 1, t, p << 1 | 1);
    return res;
}

inline std::tuple<int, int, int> queryMx(int l, int r, int s, int t, int p){
    if(l <= s && r >= t) return {mx1[p], mxL1[p], mxR1[p]};
    int m = (t + s) >> 1, mx = 0, mxL = 0, mxR = 0;
    pushDown(s, t, m, p);
    if(l <= m){
        auto it = queryMx(l, r, s, m, p << 1);
        mx = std::get<0>(it), mxL = std::get<1>(it), mxR = std::get<2>(it);
    }
    if(r > m){
        auto it = queryMx(l, r, m + 1, t, p << 1 | 1);
        mx = std::max({mx, std::get<0>(it), mxR + std::get<1>(it)});
        mxL = mxL + (mxL == std::min(std::max(m - l + 1, 0), m - s + 1)? std::get<1>(it):0);
        mxR = std::get<2>(it) + (std::get<2>(it) == std::min(r - m, t - m)? mxR:0);
    }
    return {mx, mxL, mxR};
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, m, op, l, r;
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    buildTree(1, n, 1);
    for(int i = 0; i < m; i++){
        std::cin >> op >> l >> r;
        l++, r++;
        if(!op) updataCov(l, r, 0, 1, n, 1);
        else if(op == 1) updataCov(l, r, 1, 1, n, 1);
        else if(op == 2) updataRev(l, r, 1, n, 1);
        else if(op == 3) std::cout << queryCnt(l, r, 1, n, 1) << '\n';
        else std::cout << std::get<0>(queryMx(l, r, 1, n, 1)) << '\n';
    }
    return 0;
}