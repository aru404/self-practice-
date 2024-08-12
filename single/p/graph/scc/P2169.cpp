// # 正则表达式

// ## 题目背景

// 小Z童鞋一日意外的看到小X写了一个正则表达式的高级程序，这个正则表达式程序仅仅由字符“0”,“1”，“.”和“\*”构成，但是他能够匹配出所有在OJ上都AC的程序的核心代码！小Z大为颇感好奇，于是他决定入侵小X的电脑上去获得这个正则表达式的高级程序。

// ## 题目描述

// 在 Internet 网络中的每台电脑并不是直接一对一连通的，而是某些电脑之间存在单向的网络连接，也就是说存在 $A$ 到 $B$ 的连接不一定存在 $B$ 到 $A$ 的连接，并且有些连接传输速度很快，有些则很慢，所以不同连接传输所花的时间是有大有小的。另外，如果存在 $A$ 到 $B$ 的连接的同时也存在 $B$ 到 $A$ 的连接的话，那么 $A$ 和 $B$ 实际上处于同一局域网内，可以通过本地传输，这样花费的传输时间为 $0$。

// 现在小 Z 告诉你整个网络的构成情况，他希望知道从他的电脑（编号为 $1$），到小 X 的电脑（编号为 $n$）所需要的最短传输时间。

// ## 输入格式

// 第一行两个整数 $n,m$，表示有 $n$ 台电脑，$m$ 个连接关系。

// 接下来 $m$ 行，每行三个整数 $u,v,w$，表示从电脑 $u$ 到电脑 $v$ 传输信息的时间为 $w$。

// ## 输出格式

// 输出文件仅一行为最短传输时间。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 2
// 1 2 1
// 2 3 1
// ```

// ### 样例输出 #1

// ```
// 2
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 5 5
// 1 2 1
// 2 3 6
// 3 4 1
// 4 2 1
// 3 5 2
// ```

// ### 样例输出 #2

// ```
// 3
// ```

// ## 提示

// - 对于  $40\%$ 的数据，$1\leq n\leq 10^3$, $1\leq m\leq 10^4$；
// - 对于  $70\%$ 的数据，$1\leq n\leq 5 \times 10^3$， $1\leq m\leq 10^5$；
// - 对于  $100\%$ 的数据，$1\leq n\leq 2 \times 10^5$， $1\leq m\leq 10^6$。

// 保证答案在 `int` 范围内。
#include <bits/stdc++.h>

const int maxN = 2E5 + 5, maxM = 1E6 + 5;

struct edge
{
    int to, next;
}edges[maxM], new_edges[maxN];

int head[maxN], new_head[maxN], noe = 0;
int dfn[maxN], low[maxN], stk[maxN], w[maxM], new_w[maxN], inv[maxN], top = 0, cnt = 0, scc = 0;
bool in_stk[maxN], vis[maxN];
int dis[maxN];

class cmp
{
public:
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const
    {
        return a.first > b.first;
    }
};

inline void add(int u, int v, int *hs, edge *es)
{
    es[++noe].to = v, es[noe].next = hs[u], hs[u] = noe;
}

inline void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    stk[++top] = u;
    in_stk[u] = 1;
    for(int e = head[u]; e; e = edges[e].next)
    {
        int &v = edges[e].to;
        if(!dfn[v])
        {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        }
        else if(in_stk[v]) low[u] = std::min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        ++scc;
        do{
            inv[stk[top]] = scc;
            in_stk[stk[top]] = 0;
        }while(stk[top--] != u);
    }
}

inline void dijkstra(int st, int ed)
{
    std::fill_n(dis + 1, scc, INT32_MAX);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, cmp> pq;
    dis[st] = 0;
    pq.emplace(std::make_pair(0, st));
    while(!pq.empty())
    {
        int u = pq.top().second, d = pq.top().first;
        pq.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(int e = new_head[u]; e; e = new_edges[e].next)
        {
            int &v = new_edges[e].to;
            if(dis[v] > d + new_w[e])
            {
                dis[v] = d + new_w[e];
                pq.emplace(std::make_pair(dis[v], v));
            }
        }
    }
    std::cout << dis[ed];
}

inline void shrink(int n)
{
    for(int i = 1; i <= n; ++i)
    {
        if(!dfn[i]) tarjan(i);
    }
    noe = 0;
    for(int i = 1; i <= n; ++i)
    {
        for(int e = head[i]; e; e = edges[e].next)
        {
            int &v = edges[e].to;
            if(inv[i] != inv[v])
            {
                add(inv[i], inv[v], new_head, new_edges);
                new_w[noe] = w[e];
            }
        }
    }
    dijkstra(inv[1], inv[n]);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, u, v;
    std::cin >> n >> m;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v;
        add(u, v, head, edges);
        std::cin >> w[noe];
    }
    shrink(n);
    return 0;
}