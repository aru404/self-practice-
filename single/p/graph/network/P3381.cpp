// # 【模板】最小费用最大流

// ## 题目描述

// 给出一个包含 $n$ 个点和 $m$ 条边的有向图（下面称其为网络） $G=(V,E)$，该网络上所有点分别编号为 $1 \sim n$，所有边分别编号为 $1\sim m$，其中该网络的源点为 $s$，汇点为 $t$，网络上的每条边 $(u,v)$ 都有一个流量限制 $w(u,v)$ 和单位流量的费用 $c(u,v)$。

// 你需要给每条边 $(u,v)$ 确定一个流量 $f(u,v)$，要求：

// 1.  $0 \leq f(u,v) \leq w(u,v)$（每条边的流量不超过其流量限制）；
// 2. $\forall p \in \{V \setminus \{s,t\}\}$，$\sum_{(i,p) \in E}f(i,p)=\sum_{(p,i)\in E}f(p,i)$（除了源点和汇点外，其他各点流入的流量和流出的流量相等）；
// 3. $\sum_{(s,i)\in E}f(s,i)=\sum_{(i,t)\in E}f(i,t)$（源点流出的流量等于汇点流入的流量）。

// 定义网络 $G$ 的流量 $F(G)=\sum_{(s,i)\in E}f(s,i)$，网络 $G$ 的费用 $C(G)=\sum_{(i,j)\in E} f(i,j) \times c(i,j)$。

// 你需要求出该网络的**最小费用最大流**，即在 $F(G)$ 最大的前提下，使 $C(G)$ 最小。

// ## 输入格式

// 输入第一行包含四个整数 $n,m,s,t$，分别代表该网络的点数 $n$，网络的边数 $m$，源点编号 $s$，汇点编号 $t$。

// 接下来 $m$ 行，每行四个整数 $u_i,v_i,w_i,c_i$，分别代表第 $i$ 条边的起点，终点，流量限制，单位流量费用。

// ## 输出格式

// 输出两个整数，分别为该网络的最大流 $F(G)$，以及在 $F(G)$ 最大的前提下，该网络的最小费用 $C(G)$。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 5 4 3
// 4 2 30 2
// 4 3 20 3
// 2 3 20 1
// 2 1 30 9
// 1 3 40 5
// ```

// ### 样例输出 #1

// ```
// 50 280
// ```

// ## 提示

// 对于 $100\%$ 的数据，$1 \leq n \leq 5\times 10^3$，$1 \leq m \leq 5 \times 10^4$，$1 \leq s,t \leq n$，$u_i \neq v_i$，$0 \leq w_i,c_i \leq 10^3$，且该网络的最大流和最小费用 $\leq 2^{31}-1$。

// 输入数据随机生成。
#include <bits/stdc++.h>

const int maxN = 5E3 + 5, maxM = 5E4 + 5;
struct edge
{
    int to, next, cost, cap, flow;
    edge(int to = 0, int next = 0, int cost = 0, int cap = 0, int flow = 0):to(to), next(next), cost(cost), cap(cap), flow(flow){}
}edges[maxM << 1];

int head[maxN], noe = 0;
int dis[maxN], cur[maxN], s, t, n;
bool vis[maxN];

inline void add(int u, int v, int w, int c)
{
    edges[noe].to = v;
    edges[noe].next = head[u];
    edges[noe].cost = w;
    edges[noe].cap = c;
    head[u] = noe++;
}

inline bool bfs()
{
    std::fill_n(dis + 1, n, INT32_MAX);
    memset(vis + 1, 0, sizeof(bool) * n);
    std::queue<int> q;
    q.emplace(s);
    dis[s] = 0;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for(int e = head[u]; ~e; e = edges[e].next)
        {
            int &v = edges[e].to;
            if(edges[e].cap <= edges[e].flow) continue;

            if(dis[v] > dis[u] + edges[e].cost)
            {
                dis[v] = dis[u] + edges[e].cost;
                if(!vis[v]) q.push(v), vis[v] = 1;
            }
        }
    }
    return dis[t] != INT32_MAX;
}

inline int dfs(int u, int flow)
{
    if(u == t || !flow) return flow;
    int ret = 0;
    // 防止Cost = 0时死循环某个环为0时
    vis[u] = 1;
    for(int &e = cur[u]; ~e; e = edges[e].next)
    {
        int &v = edges[e].to, &cap = edges[e].cap, &f = edges[e].flow, &c = edges[e].cost;
        if(!vis[u] && dis[u] + c == dis[v])
        {
            int reFlow = dfs(v, std::min(flow - ret, cap - f));
            ret += reFlow;
            edges[e].flow += reFlow;
            edges[e ^ 1].flow -= reFlow;
            if(flow == ret) break;
        }
    }
    vis[u] = 0;
    return ret;
}

inline void mcmf()
{
    int mnCost = 0, mxFlow = 0;
    while(bfs())
    {
        memcpy(cur + 1, head + 1, sizeof(int) * n);
        int flow = dfs(s, INT32_MAX);
        mnCost += dis[t] * flow;
        mxFlow += flow;
    }
    std::cout << mxFlow << ' ' << mnCost;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, u, v, c, w;
    std::cin >> n >> m >> s >> t;
    memset(head + 1, -1, sizeof(int) * n);
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v >> c >> w;
        add(u, v, w, c);
        add(v, u, -w, 0);
    }
    mcmf();
    return 0;
}

// 原始对偶算法
