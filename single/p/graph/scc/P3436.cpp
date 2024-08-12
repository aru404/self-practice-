// # [POI2006] PRO-Professor Szu

// ## 题面翻译

// $1 \leq n,m \leq 10^6$，$1 \leq u_i,v_i \leq n+1$。

// ## 题目描述

// 某大学校内有一栋主楼，还有 $n$ 栋住宅楼。这些楼之间由一些单向道路连接，但是任意两栋楼之间可能有多条道路，也可能存在起点和终点为同一栋楼的环路。存在住宅楼无法到达主楼的情况。

// 现在有一位古怪的教授，他希望每天去主楼上班的路线不同。

// 一条上班路线中，每栋楼都可以访问任意多次。我们称两条上班路线是**不同的**，当且仅当两条路线中存在一条路是不同的（两栋楼之间的多条道路被视为是不同的道路）。

// 现在教授希望知道，从哪些住宅楼前往主楼的上班路线数最多。

// ## 输入格式

// 第一行两个整数 $n,m$，分别为大学内住宅楼的数量和道路的数量。大学内所有住宅楼编号为 $1 \sim n$，主楼编号为 $n+1$。

// 接下来 $n$ 行，第 $i$ 行两个整数 $u_i,v_i$，代表大学内存在一条从 $u_i$ 号楼到 $v_i$ 号楼的道路。

// ## 输出格式

// 第一行：如果存在一栋楼到主楼的上班路线数超过了 $36\,500$，输出 `zawsze`。否则输出一个整数，代表从一栋住宅楼前往主楼的最多上班路线数。

// 第二行：输出一个整数 $p$，代表有多少栋住宅楼能使前往主楼的上班路线数最大化。**特别地，如果最大上班路线数超过了 $36\,500$，那么这一行请输出能使上班路线数超过 $36\,500$ 的住宅楼的数量。**

// 第三行：按编号从小到大的顺序输出 $p$ 个整数，代表能使前往主楼的上班路线最大化的住宅楼的编号。**特别地，如果最大上班路线数超过了 $36\,500$，那么这一行请输出所有能使上班路线数超过 $36\,500$ 的住宅楼的编号。**

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 5
// 1 2
// 1 3
// 2 3
// 3 4
// 3 4
// ```

// ### 样例输出 #1

// ```
// 4
// 1
// 1
// ```
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
const int maxN = 1E6 + 5;
const int limit = 36500;

struct edge
{
    int to, next;
}edges[maxN], new_edges[maxN];

int head[maxN], new_head[maxN], in_degree[maxN], noe = 0;
int dfn[maxN], low[maxN], stk[maxN], inv[maxN], schemes[maxN], top = 0, scc = 0, cnt = 0;
bool is_scc[maxN], in_stk[maxN];

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

inline void toposort(int st)
{
    std::queue<int> q;
    for(int i = 1; i <= scc; ++i)
    {
        if(!in_degree[i] && i != st) q.emplace(i);
    }
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        schemes[u] = 0;
        for(int e = new_head[u]; e; e = new_edges[e].next)
        {
            int &v = new_edges[e].to;
            --in_degree[v];
            if(!in_degree[v] && v != st) q.emplace(v);
        }
    }

    if(!schemes[st]) schemes[st] = 1;
    q.emplace(st);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int e = new_head[u]; e; e = new_edges[e].next)
        {
            int &v = new_edges[e].to;
            --in_degree[v];
            schemes[v] = std::min(INF, schemes[u] + schemes[v]);
            if(!in_degree[v]) q.emplace(v);
        }
    }
}

inline void shrink(int n)
{
    for(int i = 1; i <= n; ++i) if(!dfn[i]) tarjan(i);
    noe = 0;
    for(int i = 1; i <= n; ++i)
    {
        for(int e = head[i]; e; e = edges[e].next)
        {
            int &v = edges[e].to;
            if(inv[i] != inv[v])
            {
                add(inv[i], inv[v], new_head, new_edges);
                ++in_degree[inv[v]];
            }
            else schemes[inv[i]] = INF;
        }
    }
    toposort(inv[n]);

    int mx = std::min(*std::max_element(schemes + 1, schemes + scc + 1), limit);
    if(mx == limit) std::cout << "zawsze\n";
    else std::cout << mx << '\n';
    int tot = 0;
    for(int i = 1; i <= n; ++i)
    {
        if(schemes[inv[i]] >= mx) ++tot; 
    }
    std::cout << tot << '\n';
    for(int i = 1; i <= n; ++i)
    {
        if(schemes[inv[i]] >= mx) std::cout << i << ' ';
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, u, v;
    std::cin >> n >> m;
    for(int i = 1; i <= m; ++i)
    {
        std::cin >> u >> v;
        add(v, u, head, edges);
    }
    shrink(n + 1);
    return 0;
}