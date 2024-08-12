// # [NOIP2009 提高组] 最优贸易

// ## 题目描述

// $C$ 国有 $n$ 个大城市和 $m$ 条道路，每条道路连接这 $n$ 个城市中的某两个城市。任意两个城市之间最多只有一条道路直接相连。这 $m$ 条道路中有一部分为单向通行的道路，一部分为双向通行的道路，双向通行的道路在统计条数时也计为 $1$ 条。

// $C$ 国幅员辽阔，各地的资源分布情况各不相同，这就导致了同一种商品在不同城市的价格不一定相同。但是，同一种商品在同一个城市的买入价和卖出价始终是相同的。

// 商人阿龙来到 $C$ 国旅游。当他得知同一种商品在不同城市的价格可能会不同这一信息之后，便决定在旅游的同时，利用商品在不同城市中的差价赚回一点旅费。设 $C$ 国 $n$ 个城市的标号从 $1\sim n$，阿龙决定从 $1$ 号城市出发，并最终在 $n$ 号城市结束自己的旅行。在旅游的过程中，任何城市可以重复经过多次，但不要求经过所有 $n$ 个城市。阿龙通过这样的贸易方式赚取旅费：他会选择一个经过的城市买入他最喜欢的商品――水晶球，并在之后经过的另一个城市卖出这个水晶球，用赚取的差价当做旅费。由于阿龙主要是来 $C$ 国旅游，他决定这个贸易只进行最多一次，当然，在赚不到差价的情况下他就无需进行贸易。

// 假设 $C$ 国有 $5$ 个大城市，城市的编号和道路连接情况如下图，单向箭头表示这条道路为单向通行，双向箭头表示这条道路为双向通行。

// ![](https://cdn.luogu.com.cn/upload/image_hosting/flre534z.png)

// 假设 $1\sim n$ 号城市的水晶球价格分别为 $4,3,5,6,1$。

// 阿龙可以选择如下一条线路：$1\to2\to3\to5$，并在 $2$ 号城市以 $3$ 的价格买入水晶球，在 $3$ 号城市以 $5$ 的价格卖出水晶球，赚取的旅费数为 $2$。

// 阿龙也可以选择如下一条线路：$1\to4\to5\to4\to5$，并在第 $1$ 次到达 $5$ 号城市时以 $1$ 的价格买入水晶球，在第 $2$ 次到达 $4$ 号城市时以 $6$ 的价格卖出水晶球，赚取的旅费数为 $5$。

// 现在给出 $n$ 个城市的水晶球价格，$m$ 条道路的信息（每条道路所连接的两个城市的编号以及该条道路的通行情况）。请你告诉阿龙，他最多能赚取多少旅费。

// ## 输入格式

// 第一行包含 $2$ 个正整数 $n$ 和 $m$，中间用一个空格隔开，分别表示城市的数目和道路的数目。

// 第二行 $n$ 个正整数，每两个整数之间用一个空格隔开，按标号顺序分别表示这 $n$ 个城市的商品价格。

// 接下来 $m$ 行，每行有 $3$ 个正整数 $x,y,z$，每两个整数之间用一个空格隔开。如果 $z=1$，表示这条道路是城市 $x$ 到城市 $y$ 之间的单向道路；如果 $z=2$，表示这条道路为城市 $x$ 和城市 $y$ 之间的双向道路。

// ## 输出格式

// 一个整数，表示最多能赚取的旅费。如果没有进行贸易，则输出 $0$。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 5 
// 4 3 5 6 1 
// 1 2 1 
// 1 4 1 
// 2 3 2 
// 3 5 1 
// 4 5 2
// ```

// ### 样例输出 #1

// ```
// 5
// ```

// ## 提示

// 【数据范围】

// 输入数据保证 $1$ 号城市可以到达 $n$ 号城市。

// 对于 $10\%$ 的数据，$1\leq n\leq 6$。

// 对于 $30\%$ 的数据，$1\leq n\leq 100$。

// 对于 $50\%$ 的数据，不存在一条旅游路线，可以从一个城市出发，再回到这个城市。

// 对于 $100\%$ 的数据，$1\leq n\leq 100000$，$1\leq m\leq 500000$，$1\leq  x,y\leq  n$，$1\leq  z\leq  2$，$1\leq $ 各城市的编号 $\leq  n$。

// 水晶球价格 $\leq 100$。

// NOIP 2009 提高组 第三题
#include <bits/stdc++.h>
#define inf 0X3f3f3f3f

const int maxN = 1E5 + 5, maxM = 5E5 + 5;

struct edge
{
    int to, next;
}edges[maxM << 1], new_edges[maxN];

int head[maxN], new_head[maxN], noe = 0;
int dfn[maxN], low[maxN], stk[maxN], inv[maxN], scc = 0, top = 0, cnt = 0;
bool in_stk[maxN];
int w[maxN], mn_w[maxN], mx_w[maxN], profit[maxN], in_degree[maxN];

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
        do
        {
            inv[stk[top]] = scc;
            in_stk[stk[top]] = 0;
        }while(stk[top--] != u);
    }
}

inline void topsort()
{
    std::queue<int> q;
    for(int i = 1; i <= scc; ++i)
    {
        if(!in_degree[i] && i != inv[1]) q.push(i);
    }

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int e = new_head[u]; e; e = new_edges[e].next)
        {
            int &v = new_edges[e].to;
            --in_degree[v];
            if(!in_degree[v] && v != inv[1])
            {
                q.emplace(v);
            }
        }
    }

    q.emplace(inv[1]);
    profit[inv[1]] = mx_w[inv[1]] - mn_w[inv[1]]; 
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int e = new_head[u]; e; e = new_edges[e].next)
        {
            int &v = new_edges[e].to;
            --in_degree[v];
            mn_w[v] = std::min(mn_w[v], mn_w[u]);
            profit[v] = std::max({profit[v], profit[u], mx_w[v] - mn_w[v]});
            if(!in_degree[v]) q.push(v);
        }
    }
}

inline void shrink(int n)
{
    for(int i = 1; i <= n; ++i) if(!dfn[i]) tarjan(i);

    noe = 0;
    memset(mn_w + 1, inf, sizeof(int) * scc);
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
        }
        mx_w[inv[i]] = std::max(mx_w[inv[i]], w[i]);
        mn_w[inv[i]] = std::min(mn_w[inv[i]], w[i]);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, u, v, z;
    std::cin >> n >> m;
    for(int i = 1; i <= n; ++i) std::cin >> w[i];
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v >> z;
        add(u, v, head, edges);
        if(z == 2) add(v, u, head, edges);
    }
    shrink(n);
    topsort();
    std::cout << profit[inv[n]];
    return 0;
}