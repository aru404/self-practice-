// # 【模板】网络最大流

// ## 题目描述

// 如题，给出一个网络图，以及其源点和汇点，求出其网络最大流。

// ## 输入格式

// 第一行包含四个正整数 $n,m,s,t$，分别表示点的个数、有向边的个数、源点序号、汇点序号。

// 接下来 $m$ 行每行包含三个正整数 $u_i,v_i,w_i$，表示第 $i$ 条有向边从 $u_i$ 出发，到达 $v_i$，边权为 $w_i$（即该边最大流量为 $w_i$）。

// ## 输出格式

// 一行，包含一个正整数，即为该网络的最大流。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 5 4 3
// 4 2 30
// 4 3 20
// 2 3 20
// 2 1 30
// 1 3 30
// ```

// ### 样例输出 #1

// ```
// 50
// ```

// ## 提示

// #### 样例输入输出 1 解释

//  ![](https://cdn.luogu.com.cn/upload/pic/2262.png) 

// 题目中存在 $3$ 条路径：

// - $4\to 2\to 3$，该路线可通过 $20$ 的流量。
// - $4\to 3$，可通过 $20$ 的流量。
// - $4\to 2\to 1\to 3$，可通过 $10$ 的流量（边 $4\to 2$ 之前已经耗费了 $20$ 的流量）。

// 故流量总计 $20+20+10=50$。输出 $50$。

// ---

// #### 数据规模与约定

// - 对于 $30\%$ 的数据，保证 $n\leq10$，$m\leq25$。
// - 对于 $100\%$ 的数据，保证 $1 \leq n\leq200$，$1 \leq m\leq 5000$，$0 \leq w\lt 2^{31}$。
// O(nm^2)
// #include <bits/stdc++.h>
// #define INF 0X3f3f3f3f

// const int maxN = 205, maxM = 5E3 + 5;

// struct edge
// {
//     int to, next, cap, flow;
//     edge(int to = 0, int next = 0, int cap = 0, int flow = 0):
//         to(to), next(next), cap(cap), flow(flow){}
// }edges[maxM << 1];

// int head[maxN], pre_edges[maxN], accept_flows[maxN], noe = 0;

// inline void add(int u, int v, int cap = 0)
// {
//     edges[noe].to = v;
//     edges[noe].next = head[u];
//     edges[noe].cap = cap;
//     head[u] = noe++;
// }

// inline bool bfs(int s, int t, int n)
// {
//     memset(accept_flows + 1, 0, sizeof(int) * n);
//     std::queue<int> q;
//     q.push(s);
//     accept_flows[s] = INT32_MAX;
//     while(!q.empty())
//     {
//         int u = q.front();
//         q.pop();
//         for(int e = head[u]; ~e; e = edges[e].next)
//         {
//             int &v = edges[e].to, &cap = edges[e].cap, &flow = edges[e].flow;
//             if(!accept_flows[v] && cap > flow)
//             {
//                 // 记录前向边
//                 pre_edges[v] = e;
//                 accept_flows[v] = std::min(cap - flow, accept_flows[u]);
//                 q.push(v);
//             }
//         }
//         if(accept_flows[t]) return true;
//     }
//     return false;
// }

// inline long long maxFlow_EK(int s, int t, int n)
// {
//     long long max_flow = 0;
//     while(bfs(s, t, n))
//     {
//         for(int p = t; p != s; p = edges[pre_edges[p] ^ 1].to)
//         {
//             edges[pre_edges[p]].flow += accept_flows[t];
//             edges[pre_edges[p] ^ 1].flow -= accept_flows[t];
//         }
//         max_flow += accept_flows[t];
//     }
//     return max_flow;
// }

// int main()
// {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);

//     int n, m, s, t, u, v, w;
//     std::cin >> n >> m >> s >> t;
//     memset(head + 1, -1, sizeof(int) * n);
//     for(int i = 0; i < m; ++i)
//     {
//         std::cin >> u >> v >> w;
//         add(u, v, w);
//         add(v, u, 0);
//     }
//     std::cout << maxFlow_EK(s, t, n);
//     return 0;
// }

// Dinic
// #include <bits/stdc++.h>

// const int maxN = 205, maxM = 5E3 + 5;

// struct edge
// {
//     int to, next, cap, flow;
//     edge(int to = 0, int next = 0, int cap = 0, int flow = 0):
//         to(to), next(next), cap(cap), flow(flow){}
// }edges[maxM << 1];

// int head[maxN], noe = 0;
// int depth[maxN], cur[maxN];

// inline void add(const int& u, const int& v, const int& cap)
// {
//     edges[noe].to = v;
//     edges[noe].next = head[u];
//     edges[noe].cap = cap;
//     head[u] = noe++;
// }

// inline int bfs(const int& s, const int &t, const int& n)
// {
//     memset(depth + 1, 0, sizeof(int) * n);
//     std::queue<int> q;
//     depth[s] = 1;
//     q.push(s);
//     while(!q.empty())
//     {
//         int u = q.front();
//         q.pop();
//         for(int e = head[u]; ~e; e = edges[e].next)
//         {
//             int &v = edges[e].to;
//             if(depth[v] || edges[e].cap == edges[e].flow) continue;
//             depth[v] = depth[u] + 1;
//             q.push(v);
//         }
//     }
//     return depth[t];
// }

// inline int dfs(int u, int flow, int t)
// {
//     if(u == t || !flow) return flow;

//     int ret = 0;
//     for(int &e = cur[u]; ~e; e = edges[e].next)
//     {
//         int &v = edges[e].to, &cap = edges[e].cap, &f = edges[e].flow;
//         if(depth[v] == depth[u] + 1)
//         {
//             int reflow = dfs(v, std::min(flow - ret, cap - f), t);
//             ret += reflow;
//             edges[e].flow += reflow;
//             edges[e ^ 1].flow -= reflow;
//             if(ret == flow) break;
//         }
//     }
//     return ret;
// }

// inline long long Dinic(const int& s, const int& t, const int& n)
// {
//     long long flow = 0;
//     while(bfs(s, t, n))
//     {
//         memcpy(cur + 1, head + 1, sizeof(int) * n);
//         flow += dfs(s, INT32_MAX, t);
//     }
//     return flow;
// }

// int main()
// {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);

//     int n, m, u, v, w, s, t;
//     std::cin >> n >> m >> s >> t;
//     memset(head + 1, -1, sizeof(int) * n);
//     for(int i = 0; i < m; ++i)
//     {
//         std::cin >> u >> v >> w;
//         add(u, v, w);
//         add(v, u, 0);
//     }
//     std::cout << Dinic(s, t, n);
//     return 0;
// }

#include <bits/stdc++.h>

const int maxN = 205, maxM = 5E3 + 5;

struct edge
{
    int to, next, cap, flow;
    edge(int to = 0, int next = 0, int cap = 0, int flow = 0):
        to(to), next(next), cap(cap), flow(flow){}
}edges[maxM << 1];

int head[maxN], noe = 0, s, t, n;
int cur[maxN], depth[maxN], cnt[maxN];

inline void add(int u, int v, int cap)
{
    edges[noe].to = v;
    edges[noe].next = head[u];
    edges[noe].cap = cap;
    head[u] = noe++;
}

inline void bfs()
{
    depth[t] = 1;
    std::queue<int> q;
    q.push(t);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        ++cnt[depth[u]];
        for(int e = head[u]; ~e; e = edges[e].next)
        {
            int &v = edges[e].to;
            if(depth[v]) continue;
            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }
}

inline int dfs(int u, int flow)
{
    if(u == t) return flow;
    int ret = 0;
    for(int &e = cur[u]; ~e; e = edges[e].next)
    {
        int &v = edges[e].to, &cap = edges[e].cap, &f = edges[e].flow;
        if(depth[u] == depth[v] + 1)
        {
            int reflow = dfs(v, std::min(flow - ret, cap - f));
            edges[e].flow += reflow;
            edges[e ^ 1].flow -= reflow;
            ret += reflow;
            if(ret == flow) return flow;
        }
    }

    --cnt[depth[u]];
    if(!cnt[depth[u]]) depth[s] = n + 1;
    ++depth[u];
    ++cnt[depth[u]];
    cur[u] = head[u];
    return ret;
}

inline long long ISAP()
{
    bfs();
    long long mx_flow = 0;
    memcpy(cur + 1, head + 1, sizeof(int) * n);
    while(depth[s] && depth[s] <= n) mx_flow += dfs(s, INT32_MAX);
    return mx_flow;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, u, v, w;
    std::cin >> n >> m >> s >> t;
    memset(head + 1, -1, sizeof(int) * n);
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, 0);
    }
    std::cout << ISAP();
    return 0;
}