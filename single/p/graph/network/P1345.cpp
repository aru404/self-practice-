// # [USACO5.4] 奶牛的电信Telecowmunication

// ## 题目描述

// 农夫约翰的奶牛们喜欢通过电邮保持联系，于是她们建立了一个奶牛电脑网络，以便互相交流。这些机器用如下的方式发送电邮：如果存在一个由 $c$ 台电脑组成的序列$a_1,a_2,\cdots ,a_c$，且 $a_1$ 与 $a_2$ 相连，$a_2$ 与 $a_3$ 相连，等等。那么电脑 $a_1$ 和 $a_c$ 就可以互发电邮。

// 很不幸，有时候奶牛会不小心踩到电脑上，农夫约翰的车也可能碾过电脑，这台倒霉的电脑就会坏掉。这意味着这台电脑不能再发送电邮了，于是与这台电脑相关的连接也就不可用了。

// 有两头奶牛就想：如果我们两个不能互发电邮，至少需要坏掉多少台电脑呢？请注意，$c_1,c_2$ 不能被破坏。请编写一个程序为她们计算这个最小值。

// 以如下网络为例：

// ```plain
//    1*
//   /
//  3 - 2*
// ```

// 这张图画的是有 $2$ 条连接的 $3$ 台电脑。我们想要在电脑 $1$ 和 $2$ 之间传送信息。电脑 $1$ 与 $3$，$2$ 与 $3$ 直接连通。如果电脑 $3$ 坏了，电脑 $1$ 与 $2$ 便不能互发信息了。

// ## 输入格式

// 第一行：四个由空格分隔的整数：$N,M,c_1,c_2$。$N$ 是电脑总数，电脑由 $1$ 到 $N$ 编号。$M$ 是电脑之间连接的总数。后面的两个整数 $c_1$ 和 $c_2$ 是上述两头奶牛使用的电脑编号。连接没有重复且均为双向的（即如果 $c_1$ 与 $c_2$ 相连，那么 $c_2$ 与 $c_1$ 也相连）。两台电脑之间至多有一条连接。电脑 $c_1$ 和 $c_2$ 不会直接相连。

// 第 $2$ 到 $M+1$ 行：接下来的 $M$ 行中，每行包含两台直接相连的电脑的编号。

// ## 输出格式

// 一行，一个整数，表示使电脑 $c_1$ 和 $c_2$ 不能互相通信需要坏掉的电脑数目的最小值。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 2 1 2
// 1 3
// 2 3
// ```

// ### 样例输出 #1

// ```
// 1
// ```

// ## 提示

// 对于 $100\%$ 的数据：$1\le N \le 100$，$1\le M \le 600$。
#include <bits/stdc++.h>
#define INF 0X3f3f3f3f

const int maxN = 105, maxM = 3E3 + 10;

struct edge
{
    int to, next, cap, flow;
    edge(int to = 0, int next = 0, int cap = 0, int flow = 0):to(to), next(next), cap(cap), flow(flow){}
}edges[maxM];

int head[maxN << 1], noe = 0;
int depth[maxN << 1], gap[maxN << 1], cur[maxN << 1], s, t, n;

inline void add(int u, int v, int w)
{
    edges[noe].to = v;
    edges[noe].next = head[u];
    edges[noe].cap = w;
    head[u] = noe++;
}

inline void bfs()
{
    std::queue<int> q;
    q.push(t);
    depth[t] = 1;
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
            int reflow = dfs(v, std::min(flow - ret, cap - f));
            edges[e].flow += reflow;
            edges[e ^ 1].flow -= reflow;
            ret += reflow;
            if(ret == flow) return flow;
        }
    }
    --gap[depth[u]];
    if(!gap[depth[u]]) depth[s] = n << 1 | 1;
    ++gap[++depth[u]];
    cur[u] = head[u];
    return ret;
}

inline int ISPA()
{
    bfs();
    memcpy(cur + 1, head + 1, sizeof(int) * (n << 1));
    int mxFlow = 0;
    while(depth[s] && depth[s] <= (n << 1)) mxFlow += dfs(s, INF);
    return mxFlow;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, c1, c2, u, v;
    std::cin >> n >> m >> c1 >> c2;
    s = c1 + n, t = c2;
    memset(head + 1, -1, sizeof(int) * (n << 1));
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v;
        add(u + n, v, INF);
        add(v, u + n, 0);
        add(v + n, u, INF);
        add(u, v + n, 0);
    }
    for(int i = 1; i <= n; ++i)
    {
        if(i == c1 || i == c2)
        {
            add(i, i + n, INF);
            add(i + n, i, 0);
        }
        else
        {
            add(i, i + n, 1);
            add(i + n, i, 0);
        }
    }
    std::cout << ISPA();
    return 0;
}