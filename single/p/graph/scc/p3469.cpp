// # [POI2008] BLO-Blockade

// ## 题面翻译

// B 城有 $n$ 个城镇，$m$ 条双向道路。

// 每条道路连结两个不同的城镇，没有重复的道路，所有城镇连通。

// 把城镇看作节点，把道路看作边，容易发现，整个城市构成了一个无向图。

// 请你对于每个节点 $i$ 求出，把与节点 $i$ 关联的所有边去掉以后（不去掉节点 $i$ 本身），无向图有多少个有序点 $(x,y)$，满足 $x$ 和 $y$ 不连通。

// **【输入格式】**

// 第一行包含两个整数 $n$ 和 $m$。

// 接下来 $m$ 行，每行包含两个整数 $a$ 和 $b$，表示城镇 $a$ 和 $b$ 之间存在一条道路。

// **【输出格式】**

// 输出共 $n$ 行，每行输出一个整数。

// 第 $i$ 行输出的整数表示把与节点 $i$ 关联的所有边去掉以后（不去掉节点 $i$ 本身），无向图有多少个有序点 $(x,y)$，满足 $x$ 和 $y$ 不连通。

// **【数据范围】**

// $n\le 100000$，$m\le500000$

// ## 题目描述

// There are exactly $n$ towns in Byteotia.

// Some towns are connected by bidirectional roads.

// There are no crossroads outside towns, though there may be bridges,    tunnels and flyovers. Each pair of towns may be connected by at most    one direct road. One can get from any town to any other-directly    or indirectly.

// Each town has exactly one citizen.

// For that reason the citizens suffer from loneliness.

// It turns out that each citizen would like to pay a visit to    every other citizen (in his host's hometown), and do it    exactly once. So exactly $n\cdot (n-1)$ visits should take place.

// That's right, should.

// Unfortunately, a general strike of programmers, who    demand an emergency purchase of software, is under way.

// As an act of protest, the programmers plan to block one town of    Byteotia, preventing entering it, leaving it, and even passing through.

// As we speak, they are debating which town to choose so that    the consequences are most severe.

// Task    Write a programme that:

// reads the Byteotian road system's description from the            standard input,           for each town determines, how many visits could take place            if this town were not blocked by programmers,           writes out the outcome to the standard output.

// 给定一张无向图，求每个点被封锁之后有多少个有序点对(x,y)(x!=y,1<=x,y<=n)满足x无法到达y

// ## 输入格式

// In the first line of the standard input there are two positive    integers: $n$ and $m$ ($1\le n\le 100\ 000$, $1\le m\le 500\ 000$) denoting the number of towns and roads, respectively.

// The towns are numbered from 1 to $n$.

// The following $m$ lines contain descriptions of the roads.

// Each line contains two integers $a$ and $b$ ($1\le a<b\le n$) and    denotes a direct road between towns numbered $a$ and $b$.

// ## 输出格式

// Your programme should write out exactly $n$ integers to the standard    output, one number per line. The $i^{th}$ line should contain the number    of visits that could not take place if the programmers blocked the town    no. $i$.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 5
// 1 2
// 2 3
// 1 3
// 3 4
// 4 5
// ```

// ### 样例输出 #1

// ```
// 8
// 8
// 16
// 14
// 8
// ```
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E5 + 5, maxM = 5E5 + 5;
int head[maxN], nHead[maxN << 1], dfn[maxN], low[maxN], s[maxN], noe = 0, cnt = 0, top = 0, scc = 0, ex = 0, tot = 0, n;
int sz[maxN << 1], res[maxN];

struct edge{
    int to, next;
}edges[maxM << 1], nEdges[maxN << 2];

inline void add(int u, int v, int* h, edge* e){
    e[++noe].to = v;
    e[noe].next = h[u];
    h[u] = noe;
}

inline void tarjan(int now){
    dfn[now] = low[now] = ++cnt;
    s[++top] = now;
    for(int e = head[now]; e; e = edges[e].next){
        int& to = edges[e].to;
        if(!dfn[to]){
            tarjan(to);
            low[now] = std::min(low[now], low[to]);
            if(dfn[now] == low[to]){
                ++scc;
                do{
                    add(scc, s[top], nHead, nEdges);
                    add(s[top], scc, nHead, nEdges);
                }while(s[top--] != to);
                add(scc, now, nHead, nEdges);
                add(now, scc, nHead, nEdges);
            }
        }
        else low[now] = std::min(low[now], dfn[to]);
    }
}

inline void dfs(int now, int f){
    sz[now] += now <= n;
    for(int e = nHead[now]; e; e = nEdges[e].next){
        int& to = nEdges[e].to;
        if(to == f) continue;
        dfs(to, now);
        if(now <= n) res[now] += 2 * sz[now] * sz[to];
        sz[now] += sz[to];
    }
    if(now <= n) res[now] += 2 * sz[now] * (tot - sz[now]);
}

inline void shrink(){
    for(int i = 1; i <= n; i++){
        if(!dfn[i]){
            int pre = cnt;
            tarjan(i);
            tot = cnt - pre;
            ex += (n - tot) * tot;
            dfs(i, 0);
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, u, v;
    std::cin >> n >> m;
    for(int i = 0; i < m; i++){
        std::cin >> u >> v;
        add(u, v, head, edges), add(v, u, head, edges);
    }
    noe = 0, scc = n;
    shrink();
    for(int i = 1; i <= n; i++) std::cout << res[i] + ex << std::endl;
    return 0;
}