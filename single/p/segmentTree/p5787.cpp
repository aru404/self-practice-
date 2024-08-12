// # 二分图 /【模板】线段树分治

// ## 题目描述

// 神犇有一个 $n$ 个节点的图。

// 因为神犇是神犇，所以在 $k$ 时间内有 $m$ 条边会出现后消失。

// 神犇要求出每一时间段内这个图是否是二分图。

// 这么简单的问题神犇当然会做了，于是他想考考你。

// 原 BZOJ4025。

// ## 输入格式

// 第一行三个整数 $n,m,k$。

// 接下来 $m$ 行，每行四个整数 $x,y,l,r$，表示有一条连接 $x,y$ 的边在 $l$ 时刻出现 $r$ 时刻消失。

// ## 输出格式

// $k$ 行，第 $i$ 行一个字符串 `Yes` 或 `No`，表示在第 $i$ 时间段内这个图是否是二分图。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 3 3
// 1 2 0 2
// 2 3 0 3
// 1 3 1 2
// ```

// ### 样例输出 #1

// ```
// Yes
// No
// Yes
// ```

// ## 提示

// ### 样例说明

// $0$ 时刻，出现两条边 $(1,2)$ 和 $(2,3)$。

// 第 $1$ 时间段内，这个图是二分图，输出 `Yes`。

// $1$ 时刻，出现一条边 $(1,3)$。

// 第 $2$ 时间段内，这个图不是二分图，输出 `No`。

// $2$ 时刻，$(1,2)$ 和 $(1,3)$ 两条边消失。

// 第 $3$ 时间段内，只有一条边 $(2,3)$，这个图是二分图，输出 `Yes`。

// ### 数据范围

// $n,k = 10^5$，$m = 2\times 10^5$。$1 \le x,y \le n$，$0 \le l \le r \le k$。

// ### 注意

// 本题设有 hack 数据（Subtask $2$），计 $0$ 分，但若没有通过 hack 数据则不算通过本题。
#include <iostream>
#include <bits/stdc++.h>
#define ls(x) tree[x].ls
#define rs(x) tree[x].rs

const int maxN = 1E5 + 5;
int cnt = 0, f[maxN << 1], rk[maxN << 1], s[maxN << 1][2], idx = 0, root = 0, n;
std::vector<std::pair<int, int>> es[maxN << 2];
struct seg{
    int ls, rs;
}tree[maxN << 2];

inline int find(int x){
    return x ^ f[x]? find(f[x]):x;
}

inline void merger(int x, int y){
    if(rk[x] < rk[y]){
        f[x] = y;
        s[++idx][0] = x;
    }
    else{
        f[y] = x;
        s[++idx][0] = y;
    }
    if(rk[x] == rk[y]) rk[x]++, s[idx][1] = 1;
}

inline void revoke(){
    if(s[idx][1]) rk[f[s[idx][0]]]--;
    f[s[idx][0]] = s[idx][0];
    idx--;
}

inline void ins(int l, int r, std::pair<int, int> e, int s, int t, int& p){
    if(!p) p = ++cnt;
    if(l <= s && r >= t){
        es[p].push_back(e);
        return ;
    }
    int m = (t + s) >> 1;
    if(l <= m) ins(l, r, e, s, m, ls(p));
    if(r > m) ins(l, r, e, m + 1, t, rs(p));
}

inline void query(int s, int t, int p){
    int pre = idx;
    for(auto e:es[p]){
        int x = e.first, y = e.second, rx = x + n, ry = y + n;
        x = find(x), y = find(y);
        if(x == y){
            for(int i = s; i <= t; i++) std::cout << "No" << std::endl;
            while(idx > pre) revoke();
            return ;
        }
        rx = find(rx), ry = find(ry);
        merger(x, ry), merger(y, rx);
    }
    int m = (t + s) >> 1;
    if(ls(p)) query(s, m, ls(p));
    else for(int i = s; i <= m; i++) std::cout << "Yes" << std::endl;
    if(rs(p)) query(m + 1, t, rs(p));
    else for(int i = m + 1; i <= t; i++) std::cout << "Yes" << std::endl;
    while(idx > pre) revoke();
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, k, x, y, l, r;
    std::cin >> n >> m >> k;
    std::iota(f, f + (n << 1 | 1), 0);
    for(int i = 0; i < m; i++){
        std::cin >> x >> y >> l >> r;
        ins(l + 1, r, {x, y}, 1, k, root);
    }
    query(1, k, root);
    return 0;
}