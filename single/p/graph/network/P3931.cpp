// # SAC E#1 - 一道难题 Tree

// ## 题目背景

// 冴月麟和魏潇承是好朋友。

// ## 题目描述

// 冴月麟为了守护幻想乡，而制造了幻想乡的倒影，将真实的幻想乡封印了。任何人都无法进入真实的幻想乡了，但是她给前来救她的魏潇承留了一个线索。

// 她设置了一棵树（有根）。树的每一条边上具有割掉该边的代价。

// 魏潇承需要计算出割开这棵树的最小代价，这就是冴月麟和魏潇承约定的小秘密。

// 帮帮魏潇承吧。


// 注：所谓割开一棵有根树，就是删除若干条边，使得任何任何叶子节点和根节点不连通。

// ## 输入格式

// 输入第一行两个整数 $n,\mathrm{root}$ 分别表示树的节点个数和树根。

// 接下来 $n-1$ 行每行三个整数 $a,b,c$，表示 $a,b$ 之间有一条代价为 $c$ 的边。

// ## 输出格式

// 输出包含一行，一个整数，表示所求最小代价。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 1
// 1 2 1 
// 1 3 1
// 1 4 1
// ```

// ### 样例输出 #1

// ```
// 3
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 4 1
// 1 2 3
// 2 3 1
// 3 4 2
// ```

// ### 样例输出 #2

// ```
// 1
// ```

// ## 提示

// ### 数据范围及约定

// - 对于 $20\%$ 的数据，$n\le 10$；
// - 对于 $50\%$ 的数据，$n \le 1000$；
// - 对于 $100\%$ 的数据，$2\le n \le 100000$，且边权是不大于 $10^6$ 的非负整数。
#include <bits/stdc++.h>

const int maxN = 1E5 + 10;

struct edge
{
    int to, next, cap, flow;
}edges[maxN << 2];

int depth[maxN], cur[maxN], gap[maxN], head[maxN], degree[maxN], w[maxN], noe = 0;
int s, t, n;

inline void add(const int& u, const int& v, const int& f = 0)
{
    edges[noe].to = v;
    edges[noe].next = head[u];
    edges[noe].cap = f;
    head[u] = noe++;
}

inline void bfs()
{
    std::queue<int> q;
    depth[t] = 1;
    q.push(t);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        ++gap[depth[u]];
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
            int reflow = dfs(v, std::min(cap - f, flow - ret));
            edges[e].flow += reflow;
            edges[e ^ 1].flow -= reflow;
            ret += reflow;
            if(ret == flow) return flow;
        }
    }

    --gap[depth[u]];
    if(!gap[depth[u]]) gap[s] = n + 2;
    ++depth[u];
    ++gap[depth[u]];
    cur[u] = head[u];
    return ret;
}

inline void init(int u, int f)
{
    for(int e = head[u]; ~e; e = edges[e].next)
    {
        int &v = edges[e].to;
        if(v == f) continue;
        edges[e].cap = w[e >> 1];
        init(v, u);
    }
}

inline int ISAP()
{
    bfs();
    memcpy(cur, head, sizeof(int) * (n + 1));
    int max_flow = 0;
    while(depth[s] && depth[s] <= n + 1) max_flow += dfs(s, INT32_MAX);
    return max_flow;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int u, v;
    std::cin >> n >> s;
    t = n + 1;
    memset(head + 1, -1, sizeof(int) * (n + 1));
    for(int i = 0; i < n - 1; ++i)
    {
        std::cin >> u >> v >> w[i];
        add(u, v), add(v, u);
        ++degree[u], ++degree[v];
    }
    init(s, 0);
    for(int i = 1; i <= n; ++i)
    {
        if(degree[i] == 1 && i != s)
        {
            add(t, i);
            add(i, t, INT32_MAX);
        }
    }
    std::cout << ISAP();
    return 0;
}