// # 修复公路

// ## 题目背景

// A 地区在地震过后，连接所有村庄的公路都造成了损坏而无法通车。政府派人修复这些公路。

// ## 题目描述

// 给出 A 地区的村庄数 $N$，和公路数 $M$，公路是双向的。并告诉你每条公路的连着哪两个村庄，并告诉你什么时候能修完这条公路。问最早什么时候任意两个村庄能够通车，即最早什么时候任意两条村庄都存在至少一条修复完成的道路（可以由多条公路连成一条道路）。

// ## 输入格式

// 第 $1$ 行两个正整数 $N,M$。

// 下面 $M$ 行，每行 $3$ 个正整数 $x,y,t$，告诉你这条公路连着 $x,y$ 两个村庄，在时间t时能修复完成这条公路。

// ## 输出格式

// 如果全部公路修复完毕仍然存在两个村庄无法通车，则输出 $-1$，否则输出最早什么时候任意两个村庄能够通车。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 4
// 1 2 6
// 1 3 4
// 1 4 5
// 4 2 3
// ```

// ### 样例输出 #1

// ```
// 5
// ```

// ## 提示

// $1\leq x, y\leq N \le 10 ^ 3$，$1\leq M, t \le 10 ^ 5$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E3 + 5, maxM = 1E5 + 5;
int fa[maxN], rk[maxN], sz[maxN];
struct road{
    int u, v, t;
    road(int u = 0, int v = 0, int t = 0): u(u), v(v), t(t){}
    bool operator<(const road& other) const{
        return this->t < other.t;
    }
}roads[maxM];

inline int find(int u){
    return fa[u] ^ u? (fa[u] = find(fa[u])):u;
}

inline void merger(int u, int v){
    u = find(u), v = find(v);
    if(u == v) return ;
    if(rk[v] > rk[u]) fa[u] = v, sz[v] += sz[u];
    else fa[v] = u, sz[u] += sz[v];
    if(rk[u] == rk[v]) rk[u]++;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, u, v, t;
    std::cin >> n >> m;
    std::iota(fa, fa + n + 1, 0);
    std::fill_n(sz + 1, n, 1);
    for(int i = 0; i < m; i++){
        std::cin >> u >> v >> t;
        roads[i] = road(u, v, t);
    }
    std::sort(roads, roads + m);
    for(int i = 0; i < m; i++){
        int& u = roads[i].u, &v = roads[i].v, &t = roads[i].t;
        merger(u, v);
        if(sz[find(u)] == n){
            std::cout << t;
            return 0;
        }
    }
    std::cout << -1;
    return 0;
}