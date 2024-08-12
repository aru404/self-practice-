// # [APIO2009] 抢掠计划

// ## 题目描述

// Siruseri 城中的道路都是单向的。不同的道路由路口连接。按照法律的规定，在每个路口都设立了一个 Siruseri 银行的 ATM 取款机。令人奇怪的是，Siruseri 的酒吧也都设在路口，虽然并不是每个路口都设有酒吧。  

// Banditji 计划实施 Siruseri 有史以来最惊天动地的 ATM 抢劫。他将从市中心出发，沿着单向道路行驶，抢劫所有他途径的 ATM 机，最终他将在一个酒吧庆祝他的胜利。  

// 使用高超的黑客技术，他获知了每个 ATM 机中可以掠取的现金数额。他希望你帮助他计算从市中心出发最后到达某个酒吧时最多能抢劫的现金总数。他可以经过同一路口或道路任意多次。但只要他抢劫过某个 ATM 机后，该 ATM 机里面就不会再有钱了。 例如，假设该城中有 $6$ 个路口，道路的连接情况如下图所示：  

// ![](https://cdn.luogu.com.cn/upload/pic/4396.png)  

// 市中心在路口 $1$，由一个入口符号 → 来标识，那些有酒吧的路口用双圈来表示。每个 ATM 机中可取的钱数标在了路口的上方。在这个例子中，Banditji 能抢劫的现金总数为 $47$，实施的抢劫路线是：$1-2-4-1-2-3-5$。

// ## 输入格式

// 第一行包含两个整数 $N,M$。$N$ 表示路口的个数，$M$ 表示道路条数。  

// 接下来 $M$ 行，每行两个整数，这两个整数都在 $1$ 到 $N$ 之间，第 $i+1$ 行的两个整数表示第 $i$ 条道路的起点和终点的路口编号。  

// 接下来 $N$ 行，每行一个整数，按顺序表示每个路口处的 ATM 机中的钱数 $a_i$。  

// 接下来一行包含两个整数 $S,P$，$S$ 表示市中心的编号，也就是出发的路口。$P$ 表示酒吧数目。  

// 接下来的一行中有 $P$ 个整数，表示 $P$ 个有酒吧的路口的编号。

// ## 输出格式

// 输出一个整数，表示 Banditji 从市中心开始到某个酒吧结束所能抢劫的最多的现金总数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6 7 
// 1 2 
// 2 3 
// 3 5 
// 2 4 
// 4 1 
// 2 6 
// 6 5 
// 10 
// 12 
// 8 
// 16 
// 1 
// 5 
// 1 4 
// 4 3 5 6
// ```

// ### 样例输出 #1

// ```
// 47
// ```

// ## 提示

// 对于 $50\%$ 的数据，保证 $N, M \le 3000$。  

// 对于 $100\%$ 的数据，保证 $N, M \le 5\times 10^5$，$0 \le a_i \le 4000$。保证可以从市中心沿着 Siruseri 的单向的道路到达其中的至少一个酒吧。
#include <bits/stdc++.h>

const int maxN = 5E5 + 5;

struct edge
{
    int to, next;
}edges[maxN], new_edges[maxN];

int head[maxN], new_head[maxN], noe = 0;
int dfn[maxN], low[maxN], stk[maxN], inv[maxN], w[maxN], new_w[maxN], tot[maxN], in_degree[maxN], top = 0, scc = 0, cnt = 0;
bool in_stk[maxN], has_bar[maxN], new_has_bar[maxN];

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
                ++in_degree[inv[v]];
            }
        }
        new_has_bar[inv[i]] |= has_bar[i];
        new_w[inv[i]] += w[i];
    }
}

inline void toposort(int st)
{
    st = inv[st];
    std::queue<int> q;
    for(int i = 1; i <= scc; ++i)
    {
        if(!in_degree[i] && i != st) q.push(i);
    }
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int e = new_head[u]; e; e = new_edges[e].next)
        {
            int &v = new_edges[e].to;
            --in_degree[v];
            if(!in_degree[v] && v != st) q.push(v);
        }
    }

    q.push(st);
    tot[st] = new_w[st];
    int res = 0;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        if(new_has_bar[u]) res = std::max(res, tot[u]);
        for(int e = new_head[u]; e; e = new_edges[e].next)
        {
            int &v = new_edges[e].to;
            --in_degree[v];
            tot[v] = std::max(tot[u] + new_w[v], tot[v]);
            if(!in_degree[v]) q.push(v);
        }
    }

    std::cout << res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, u, v, p, s;
    std::cin >> n >> m;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v;
        add(u, v, head, edges);
    }
    for(int i = 1; i <= n; ++i) std::cin >> w[i];
    std::cin >> s >> p;
    for(int i = 0; i < p; ++i)
    {
        std::cin >> u;
        has_bar[u] = 1;
    }
    shrink(n);
    toposort(s);
    return 0;
}