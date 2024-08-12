// # [SCOI2005] 繁忙的都市

// ## 题目描述

// 城市 C 是一个非常繁忙的大都市，城市中的道路十分的拥挤，于是市长决定对其中的道路进行改造。城市 C 的道路是这样分布的：城市中有 $n$ 个交叉路口，有些交叉路口之间有道路相连，两个交叉路口之间最多有一条道路相连接。这些道路是双向的，且把所有的交叉路口直接或间接的连接起来了。每条道路都有一个分值，分值越小表示这个道路越繁忙，越需要进行改造。但是市政府的资金有限，市长希望进行改造的道路越少越好，于是他提出下面的要求：

// 1. 改造的那些道路能够把所有的交叉路口直接或间接的连通起来。
// 1. 在满足要求 1 的情况下，改造的道路尽量少。
// 1. 在满足要求 1、2 的情况下，改造的那些道路中分值最大的道路分值尽量小。

// 任务：作为市规划局的你，应当作出最佳的决策，选择哪些道路应当被修建。

// ## 输入格式

// 第一行有两个整数 $n,m$ 表示城市有 $n$ 个交叉路口，$m$ 条道路。

// 接下来 $m$ 行是对每条道路的描述，$u, v, c$ 表示交叉路口 $u$ 和 $v$ 之间有道路相连，分值为 $c$。

// ## 输出格式

// 两个整数 $s, \mathit{max}$，表示你选出了几条道路，分值最大的那条道路的分值是多少。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 5
// 1 2 3
// 1 4 5
// 2 4 7
// 2 3 6
// 3 4 8
// ```

// ### 样例输出 #1

// ```
// 3 6
// ```

// ## 提示

// ### 数据范围及约定

// 对于全部数据，满足 $1\le n\le 300$，$1\le c\le 10^4$，$1 \le m \le 8000$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 305, maxM = 8005;
int fa[maxN], rk[maxN];
struct road{
    int u, v, w;
    road(int u = 0, int v = 0, int w = 0): u(u), v(v), w(w){}
    bool operator<(const road& other) const{
        return this->w < other.w;
    }
}roads[maxM];

inline int find(int u){
    return u ^ fa[u]? (fa[u] = find(fa[u])):u;
}

inline void merger(int u, int v){
    if(rk[v] > rk[u]) fa[u] = v;
    else fa[v] = u;
    if(rk[u] == rk[v]) rk[u]++;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, mx = 0, cnt = 0;
    std::cin >> n >> m;
    for(int i = 0; i < m; i++){
        std::cin >> roads[i].u >> roads[i].v >> roads[i].w;
    }
    std::sort(roads, roads + m);
    std::iota(fa, fa + n + 1, 0);
    for(int i = 0; i < m; i++){
        int u = roads[i].u, v = roads[i].v, w = roads[i].w;
        u = find(u), v = find(v);
        if(u == v) continue;
        mx = w, cnt++, merger(u, v);
        if(cnt == n - 1) break;
    }
    std::cout << cnt << ' ' << mx;
    return 0;
}