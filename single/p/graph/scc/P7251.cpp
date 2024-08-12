// # [JSOI2014] 强连通图

// ## 题目描述

// JYY 最近痴迷于图的强连通性，所以对于任何有向图，JYY 都希望增加一些边使得这个图变成强连通图。JYY现在得到了一个 $n$ 个点 $m$ 条边的有向图，所有点从 $1$ 到 $n$ 编号。

// JYY 想知道：

// - 在给定的图中，最多能选出多少个点，使得这些点在原图中两两可达？

// - 在给定的图中，最少增加多少条边，可以使得这个图变成强连通图？

// 其中，一个有向图 $G(V,E)$是强连通的，当且仅当任意顶点 $a,b\in V,a\neq b$之间都存在 $a\to b$ 和 $b\to a$ 的路径。

// ## 输入格式

// 第一行包含两个整数 $n$ 和 $m$。

// 接下来 $m$ 行，每行两个整数 $x$ 和 $y$，表示图中有一条从 $x$ 到 $y$ 的有向边。

// ## 输出格式

// 两行，第一行表示第一个问题的答案，第二行表示第二个问题的答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 3
// 1 4
// 2 3
// 2 4
// ```

// ### 样例输出 #1

// ```
// 1
// 2
// ```

// ## 提示

// ### 样例解释 1

// 对于第一个问题，无法选出互相连通两个点，答案为 $1$。

// 对于第二个问题，一种加边数最小的方案为 $(3,1)$ 和 $(4,2)$，答案为 $2$。

// ### 数据范围

// 对于 $100\%$ 的数据，$1\leq n\leq 10^5,1\leq m\leq 3\times 10^5$。
#include <bits/stdc++.h>

const int maxN = 1E5 + 5, maxM = 3E5 + 5;

struct edge
{
    int to, next;
}edges[maxM];

int head[maxN], noe = 0;
int dfn[maxN], low[maxN], stk[maxN], inv[maxN], in_degree[maxN], out_degree[maxN], top = 0, cnt = 0, scc = 0, mx_sz = 0;
bool in_stk[maxN];

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
        int sz = 0;
        do{
            inv[stk[top]] = scc;
            in_stk[stk[top]] = 0;
            ++sz;
        }while(stk[top--] != u);
        mx_sz = std::max(mx_sz, sz);
    }
}

inline void solve(int n)
{
    for(int i = 1; i <= n; ++i)
    {
        if(!dfn[i]) tarjan(i);
    }

    for(int i = 1; i <= n; ++i)
    {
        for(int e = head[i]; e; e = edges[e].next)
        {
            int &v = edges[e].to;
            if(inv[i] != inv[v])
            {
                ++in_degree[inv[v]];
                ++out_degree[inv[i]];
            }
        }
    }

    int cnt_in = 0, cnt_out = 0;
    for(int i = 1; i <= scc; ++i)
    {
        if(!in_degree[i]) ++cnt_in;
        if(!out_degree[i]) ++cnt_out;
    }

    if(scc == 1) cnt_in = cnt_out = 0;
    std::cout << mx_sz << '\n' << std::max(cnt_in, cnt_out);
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
    solve(n);
    return 0;
}