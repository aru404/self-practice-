// # [NOIP2007 提高组] 树网的核

// ## 题目描述

// 设 $T=(V,E,W)$ 是一个无圈且连通的无向图（也称为无根树），每条边都有正整数的权，我们称 $T$ 为树网（`treenetwork`），其中 $V$，$E$ 分别表示结点与边的集合，$W$ 表示各边长度的集合，并设 $T$ 有 $n$ 个结点。

// 路径：树网中任何两结点 $a$，$b$ 都存在唯一的一条简单路径，用 $d(a, b)$ 表示以 $a, b$ 为端点的路径的长度，它是该路径上各边长度之和。我们称 
// $d(a, b)$ 为 $a, b$ 两结点间的距离。

// $D(v, P)=\min\{d(v, u)\}$, $u$ 为路径 $P$ 上的结点。

// 树网的直径：树网中最长的路径成为树网的直径。对于给定的树网 $T$，直径不一定是唯一的，但可以证明：各直径的中点（不一定恰好是某个结点，可能在某条边的内部）是唯一的，我们称该点为树网的中心。

// 偏心距 $\mathrm{ECC}(F)$：树网 $T$ 中距路径 $F$ 最远的结点到路径 $F$ 的距离，即

// $\mathrm{ECC}(F)=\max\{D(v, F),v \in V\}$

// 任务：对于给定的树网 $T=(V, E, W)$ 和非负整数 $s$，求一个路径 $F$，他是某直径上的一段路径（该路径两端均为树网中的结点），其长度不超过 $s$（可以等于 $s$），使偏心距 $\mathrm{ECC}(F)$ 最小。我们称这个路径为树网 $T=(V, E, W)$ 的核（`Core`）。必要时，$F$ 可以退化为某个结点。一般来说，在上述定义下，核不一定只有一个，但最小偏心距是唯一的。

// 下面的图给出了树网的一个实例。图中，$A-B$ 与 $A-C$ 是两条直径，长度均为 $20$。点 $W$ 是树网的中心，$EF$ 边的长度为 $5$。如果指定 $s=11$，则树网的核为路径`DEFG`（也可以取为路径`DEF`），偏心距为 $8$。如果指定 $s=0$（或 $s=1$、$s=2$），则树网的核为结点 $F$，偏心距为 $12$。

// ![](https://cdn.luogu.com.cn/upload/image_hosting/oms5c6rq.png)

// ## 输入格式

// 共 $n$ 行。

// 第 $1$ 行，两个正整数 $n$ 和 $s$，中间用一个空格隔开。其中 $n$ 为树网结点的个数，$s$ 为树网的核的长度的上界。设结点编号以此为 $1,2\dots,n$。

// 从第 $2$ 行到第 $n$ 行，每行给出 $3$ 个用空格隔开的正整数 $u, v, w$，依次表示每一条边的两个端点编号和长度。例如，`2 4 7` 表示连接结点 $2$ 与 $4$ 的边的长度为 $7$。

// ## 输出格式

// 一个非负整数，为指定意义下的最小偏心距。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 2
// 1 2 5
// 2 3 2
// 2 4 4
// 2 5 3
// ```

// ### 样例输出 #1

// ```
// 5
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 8 6
// 1 3 2
// 2 3 2 
// 3 4 6
// 4 5 3
// 4 6 4
// 4 7 2
// 7 8 3
// ```

// ### 样例输出 #2

// ```
// 5
// ```

// ## 提示

// - 对于 $40\%$ 的数据，保证 $n \le 15$。
// - 对于 $70\%$ 的数据，保证 $n \le 80$。
// - 对于 $100\%$ 的数据，保证 $2\le n \le 300$，$0\le s\le10^3$，$1 \leq u, v \leq n$，$0 \leq w \leq 10^3$。

// NOIP2007 提高组第四题
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 305;

struct edge{
    int to, next, w;
}edges[maxN << 1];

int head[maxN], dis[maxN], r[maxN], mx[maxN], r1, r2, tot = 0, cnt = 0;

inline void add(int u, int v, int w){
    edges[++tot].to = v, edges[tot].next = head[u], edges[tot].w = w;
    head[u] = tot;
}

inline void dfs1(int now, int f){
    for(int e = head[now]; e; e = edges[e].next){
        int& to = edges[e].to;
        if(to == f) continue;
        dis[to] = dis[now] + edges[e].w;
        dfs1(to, now);
    }
}

inline void dfs2(int now, int f){
    mx[now] = 0;
    if(now == r2) r[++cnt] = now;
    for(int e = head[now]; e; e = edges[e].next){
        int& to = edges[e].to;
        if(to == f) continue;
        dfs2(to, now);
        if(r[cnt] == to) r[++cnt] = now;
        else mx[now] = std::max(mx[now], mx[to] + edges[e].w);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, s, u, v, w;
    std::cin >> n >> s;
    for(int i = 1; i < n; i++){
        std::cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    dfs1(1, 0);
    int now = 0;
    for(int i = 1; i <= n; i++) if(dis[i] > now) r1 = i, now = dis[i];
    dis[r1] = now = 0, dfs1(r1, 0);
    for(int i = 1; i <= n; i++) if(dis[i] > now) r2 = i, now = dis[i];
    dfs2(r1, 0);
    std::deque<int> q;
    int res = 0X3f3f3f3f, idx = cnt;
    for(int i = cnt; i; i--){
        while(!q.empty() && dis[r[i]] - dis[q.front()] > s) q.pop_front();
        while(dis[r[i]] - dis[r[idx]] > s) --idx;
        while(!q.empty() && mx[q.back()] < mx[r[i]]) q.pop_back();
        q.emplace_back(r[i]);
        res = std::min(res, std::max({mx[q.front()], dis[r[idx]], dis[r2] - dis[r[i]]}));
    }
    std::cout << res;
    return 0;
}