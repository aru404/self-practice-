// # 【模板】全源最短路（Johnson）

// ## 题目描述

// 给定一个包含 $n$ 个结点和 $m$ 条带权边的有向图，求所有点对间的最短路径长度，一条路径的长度定义为这条路径上所有边的权值和。

// 注意：

// 1. 边权**可能**为负，且图中**可能**存在重边和自环；

// 2. 部分数据卡 $n$ 轮 SPFA 算法。

// ## 输入格式

// 第 $1$ 行：$2$ 个整数 $n,m$，表示给定有向图的结点数量和有向边数量。

// 接下来 $m$ 行：每行 $3$ 个整数 $u,v,w$，表示有一条权值为 $w$ 的有向边从编号为 $u$ 的结点连向编号为 $v$ 的结点。

// ## 输出格式

// 若图中存在负环，输出仅一行 $-1$。

// 若图中不存在负环：

// 输出 $n$ 行：令 $dis_{i,j}$ 为从 $i$ 到 $j$ 的最短路，在第 $i$ 行输出 $\sum\limits_{j=1}^n j\times dis_{i,j}$，注意这个结果可能超过 int 存储范围。

// 如果不存在从 $i$ 到 $j$ 的路径，则 $dis_{i,j}=10^9$；如果 $i=j$，则 $dis_{i,j}=0$。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 7
// 1 2 4
// 1 4 10
// 2 3 7
// 4 5 3
// 4 2 -2
// 3 4 -3
// 5 3 4
// ```

// ### 样例输出 #1

// ```
// 128
// 1000000072
// 999999978
// 1000000026
// 1000000014
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 5 5
// 1 2 4
// 3 4 9
// 3 4 -3
// 4 5 3
// 5 3 -2
// ```

// ### 样例输出 #2

// ```
// -1
// ```

// ## 提示

// 【样例解释】

// 左图为样例 $1$ 给出的有向图，最短路构成的答案矩阵为：

// ```
// 0 4 11 8 11 
// 1000000000 0 7 4 7 
// 1000000000 -5 0 -3 0 
// 1000000000 -2 5 0 3 
// 1000000000 -1 4 1 0 
// ```

// 右图为样例 $2$ 给出的有向图，红色标注的边构成了负环，注意给出的图不一定连通。

// ![](https://cdn.luogu.com.cn/upload/image_hosting/7lb35u4u.png)

// 【数据范围】

// 对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^3,\ \ 1\leq m\leq 6\times 10^3,\ \ 1\leq u,v\leq n,\ \ -3\times 10^5\leq w\leq 3\times 10^5$。

// 对于 $20\%$ 的数据，$1\leq n\leq 100$，不存在负环（可用于验证 Floyd 正确性）

// 对于另外 $20\%$ 的数据，$w\ge 0$（可用于验证 Dijkstra 正确性）

// upd. 添加一组 Hack 数据：针对 SPFA 的 SLF 优化
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 3E3 + 5, inf = 1E9;
int head[maxN], dis[maxN][maxN], cnt[maxN], noe = 0;
bool vis[maxN];
struct v{
    int p, d;
    v(int p, int d): p(p), d(d){}
    bool operator< (const v& other) const{
        return this->d ^ other.d? this->d > other.d:this->p > other.p;
    }
};
std::priority_queue<v> pq;

struct edge{
    int to, next, w;
}edges[maxN << 1];

inline void add(int u, int v, int w){
    edges[++noe].to = v;
    edges[noe].next = head[u];
    edges[noe].w = w;
    head[u] = noe;
}

inline bool spfa(int n){
    std::queue<int> q;
    for(int i = 1; i <= n; i++) q.emplace(i), vis[i] = 1; 
    while(!q.empty()){
        int top = q.front();
        q.pop();
        vis[top] = 0;
        for(int e = head[top]; e; e = edges[e].next){
            int& to = edges[e].to, &w = edges[e].w;
            if(dis[0][to] > dis[0][top] + w){
                dis[0][to] = dis[0][top] + w;
                if(!vis[to]){
                    vis[to] = 1, cnt[to]++;
                    if(cnt[to] >= n) return 0;
                    q.emplace(to);
                }
            }
        }
    }
    return 1;
}

inline void dijkstra(int st, int n){
    std::fill_n(dis[st] + 1, n, inf);
    memset(vis + 1, 0, sizeof(bool) * n);
    dis[st][st] = 0;
    pq.emplace(v(st, 0));
    while(!pq.empty()){
        auto top = pq.top();
        pq.pop();
        if(vis[top.p]) continue;
        vis[top.p] = 1;
        for(int e = head[top.p]; e; e = edges[e].next){
            int& to = edges[e].to, w = edges[e].w + dis[0][top.p] - dis[0][to];
            if(dis[st][to] > dis[st][top.p] + w){
                dis[st][to] = dis[st][top.p] + w;
                pq.emplace(v(to, dis[st][to]));
            }
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, u, v, w;
    std::cin >> n >> m;
    for(int i = 0; i < m; i++){
        std::cin >> u >> v >> w;
        add(u, v, w);
    }
    if(!spfa(n)){
        std::cout << -1 << std::endl;
        return 0;
    }
    for(int i = 1; i <= n; i++){
        dijkstra(i, n);
        long long res = 0;
        for(int j = 1; j <= n; j++){
            if(dis[i][j] == inf) res += 1ll * j * inf;
            else res += 1ll * j * (dis[i][j] + dis[0][j] - dis[0][i]);
        }
        std::cout << res << std::endl;
    }
    return 0;
}