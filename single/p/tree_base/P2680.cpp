// # [NOIP2015 提高组] 运输计划

// ## 题目背景

// NOIP2015 Day2T3

// ## 题目描述

// 公元 $2044$ 年，人类进入了宇宙纪元。

// L 国有 $n$ 个星球，还有 $n-1$ 条双向航道，每条航道建立在两个星球之间，这 $n-1$ 条航道连通了 L 国的所有星球。

// 小 P 掌管一家物流公司， 该公司有很多个运输计划，每个运输计划形如：有一艘物流飞船需要从 $u_i$ 号星球沿最快的宇航路径飞行到 $v_i$ 号星球去。显然，飞船驶过一条航道是需要时间的，对于航道 $j$，任意飞船驶过它所花费的时间为 $t_j$，并且任意两艘飞船之间不会产生任何干扰。

// 为了鼓励科技创新， L 国国王同意小 P 的物流公司参与 L 国的航道建设，即允许小 P 把某一条航道改造成虫洞，飞船驶过虫洞不消耗时间。

// 在虫洞的建设完成前小 P 的物流公司就预接了 $m$ 个运输计划。在虫洞建设完成后，这 $m$ 个运输计划会同时开始，所有飞船一起出发。当这 $m$ 个运输计划都完成时，小 P 的物流公司的阶段性工作就完成了。

// 如果小 P 可以自由选择将哪一条航道改造成虫洞， 试求出小 P 的物流公司完成阶段性工作所需要的最短时间是多少？

// ## 输入格式

// 第一行包括两个正整数 $n, m$，表示 L 国中星球的数量及小 P 公司预接的运输计划的数量，星球从 $1$ 到 $n$ 编号。

// 接下来 $n-1$ 行描述航道的建设情况，其中第 $i$ 行包含三个整数 $a_i, b_i$ 和 $t_i$，表示第 $i$ 条双向航道修建在 $a_i$ 与 $b_i$ 两个星球之间，任意飞船驶过它所花费的时间为 $t_i$。  

// 数据保证 

// 接下来 $m$ 行描述运输计划的情况，其中第 $j$ 行包含两个正整数 $u_j$ 和 $v_j$，表示第 $j$ 个运输计划是从 $u_j$ 号星球飞往 $v_j$号星球。

// ## 输出格式

// 一个整数，表示小 P 的物流公司完成阶段性工作所需要的最短时间。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6 3 
// 1 2 3 
// 1 6 4 
// 3 1 7 
// 4 3 6 
// 3 5 5 
// 3 6 
// 2 5 
// 4 5
// ```

// ### 样例输出 #1

// ```
// 11
// ```

// ## 提示

// 所有测试数据的范围和特点如下表所示

//  ![](https://cdn.luogu.com.cn/upload/pic/1831.png) 

// **请注意常数因子带来的程序效率上的影响。**

// 对于 $100\%$ 的数据，保证：$1 \leq a_i,b_i \leq n$，$0 \leq t_i \leq 1000$，$1 \leq u_i,v_i \leq n$。
#include <bits/stdc++.h>

const int maxN = 3E5 + 5;

int head[maxN], qHead[maxN], w[maxN], noe = 0;
int d[maxN], f[maxN], lca[maxN], dis[maxN], top = 0, mx, mxW;
bool vis[maxN];

struct edge
{
    int to, next;
}edges[maxN << 1], qEdges[maxN << 1];

inline void add(int u, int v, int* hs, edge* es)
{
    es[noe] = edge{v, hs[u]};
    hs[u] = noe++;
}

inline int find(int x)
{
    return f[x] ^ x? (f[x] = find(f[x])):x;
}

inline void tarjan(int u, int fa)
{
    f[u] = u;
    vis[u] = 1;
    for(int e = head[u]; ~e; e = edges[e].next) 
    {
        int &v = edges[e].to;
        if(v == fa) continue;
        tarjan(v, u);
        f[v] = u;
    }
    for(int e = qHead[u]; ~e; e = qEdges[e].next)
    {
        int& v = qEdges[e].to;
        if(vis[v]) lca[e >> 1] = find(v);
    }
}

inline void dfs1(int u, int fa)
{
    for(int e = head[u]; ~e; e = edges[e].next)
    {
        int &v = edges[e].to;
        if(v == fa) continue;
        dis[v] = dis[u] + w[e >> 1];
        dfs1(v, u);
    }
}

inline void dfs2(int u, int fa)
{
    for(int e = head[u]; ~e; e = edges[e].next)
    {
        int &v = edges[e].to;
        if(v == fa) continue;
        dfs2(v, u);
        d[u] += d[v];
        if(d[v] == top) mxW = std::max(mxW, w[e >> 1]);
    }
}

inline bool check(int n, int m, int k)
{
    top = 0;
    for(int i = 0; i < m; ++i)
    {
        int u = qEdges[i << 1].to;
        int v = qEdges[i << 1 | 1].to;
        if(dis[u] + dis[v] - 2 * dis[lca[i]] > k)
        {
            ++d[u];
            ++d[v];
            d[lca[i]] -= 2;
            ++top;
        }
    }
    mxW = 0;
    dfs2(1, 0);
    memset(d + 1, 0, sizeof(int) * n);
    return mx <= k + mxW;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, u, v;
    std::cin >> n >> m;
    memset(head + 1, -1, sizeof(int) * n);
    memset(qHead + 1, -1, sizeof(int) * n);    
    for(int i = 0; i < n - 1; ++i)
    {
        std::cin >> u >> v >> w[i];
        add(u, v, head, edges);
        add(v, u, head, edges);
    }
    noe = 0;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v;
        add(u, v, qHead, qEdges);
        add(v, u, qHead, qEdges);
        ++d[u], ++d[v];
    }
    tarjan(1, 0);
    dfs1(1, 0);
    for(int i = 0; i < m; ++i)
    {
        mx = std::max(mx, dis[qEdges[i << 1].to] + dis[qEdges[i << 1 | 1].to] - dis[lca[i]] * 2);
    }
    int l = 0, r = mx, res = 0X3f3f3f3f;
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        if(check(n, m, mid))
        {
            res = std::min(res, mid);
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    std::cout << res;
    return 0;
}