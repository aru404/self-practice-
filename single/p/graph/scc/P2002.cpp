// # 消息扩散

// ## 题目背景

// 本场比赛第一题，给个简单的吧，这 100 分先拿着。

// ## 题目描述

// 有 $n$ 个城市，中间有单向道路连接，消息会沿着道路扩散，现在给出 $n$ 个城市及其之间的道路，问至少需要在几个城市发布消息才能让这所有 $n$ 个城市都得到消息。

// ## 输入格式

// 第一行两个整数 $n, m$，表示 $n$ 个城市，$m$ 条单向道路。

// 以下 $m$ 行，每行两个整数 $b, e$ 表示有一条从 $b$ 到 $e$ 的道路，道路可以重复或存在自环。

// ## 输出格式

// 一行一个整数，表示至少要在几个城市中发布消息。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 4
// 1 2
// 2 1
// 2 3
// 5 1
// ```

// ### 样例输出 #1

// ```
// 2
// ```

// ## 提示

// **【样例解释 #1】**

// 样例中在 $4, 5$ 号城市中发布消息。

// **【数据范围】**

// 对于 $20 \%$ 的数据，$n \le 200$；  
// 对于 $40 \%$ 的数据，$n \le 2000$；  
// 对于 $100 \%$ 的数据，$1 \le n \le {10}^5$，$1 \le m \le 5 \times {10}^5$。
#include <bits/stdc++.h>

const int maxN = 1E5 + 5, maxM = 5E5 + 5;;

struct edge
{
    int to, next;
}edges[maxM];

int head[maxN], stk[maxN], dfn[maxN], low[maxN], top = 0, noe = 0, cnt = 0;
int inv[maxN], in_degree[maxN], scc = 0;
bool in_stk[maxN];

inline void add(int u, int v, int* hs, edge* es)
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
    }

    for(int i = 1; i <= n; ++i)
    {
        if(!dfn[i]) tarjan(i);
    }

    for(int i = 1; i <= n; ++i)
    {
        for(int e = head[i]; e; e = edges[e].next)
        {
            int &to = edges[e].to;
            if(inv[i] != inv[to]) ++in_degree[inv[to]];
        }
    }

    int res = 0;
    for(int i = 1; i <= scc; ++i) res += in_degree[i] == 0;
    std::cout << res;
    return 0;
}