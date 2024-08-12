// # [JSOI2008] 星球大战

// ## 题目描述

// 很久以前，在一个遥远的星系，一个黑暗的帝国靠着它的超级武器统治着整个星系。

// 某一天，凭着一个偶然的机遇，一支反抗军摧毁了帝国的超级武器，并攻下了星系中几乎所有的星球。这些星球通过特殊的以太隧道互相直接或间接地连接。

// 但好景不长，很快帝国又重新造出了他的超级武器。凭借这超级武器的力量，帝国开始有计划地摧毁反抗军占领的星球。由于星球的不断被摧毁，两个星球之间的通讯通道也开始不可靠起来。

// 现在，反抗军首领交给你一个任务：给出原来两个星球之间的以太隧道连通情况以及帝国打击的星球顺序，以尽量快的速度求出每一次打击之后反抗军占据的星球的连通块的个数。（如果两个星球可以通过现存的以太通道直接或间接地连通，则这两个星球在同一个连通块中）。

// ## 输入格式

// 输入文件第一行包含两个整数，$n,m$，分别表示星球的数目和以太隧道的数目。星球用 $0 \sim n-1$ 的整数编号。

// 接下来的 $m$ 行，每行包括两个整数 $x,y$，表示星球 $x$ 和星球 $y$ 之间有 “以太” 隧道，可以直接通讯。

// 接下来的一行为一个整数 $k$ ，表示将遭受攻击的星球的数目。

// 接下来的 $k$ 行，每行有一个整数，按照顺序列出了帝国军的攻击目标。这 $k$ 个数互不相同，且都在 $0$ 到 $n-1$ 的范围内。

// ## 输出格式

// 第一行是开始时星球的连通块个数。接下来的 $k$ 行，每行一个整数，表示经过该次打击后现存星球的连通块个数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 8 13
// 0 1
// 1 6
// 6 5
// 5 0
// 0 6
// 1 2
// 2 3
// 3 4
// 4 5
// 7 1
// 7 2
// 7 6
// 3 6
// 5
// 1
// 6
// 3
// 5
// 7
// ```

// ### 样例输出 #1

// ```
// 1
// 1
// 1
// 2
// 3
// 3
// ```

// ## 提示

// 【数据范围】  
// 对于 $100\%$ 的数据，$1\le m \le 2\times 10^5$，$1\le n \le 2m$，$x \neq y$。

// [JSOI2008]
#include <bits/stdc++.h>

const int maxN = 2E5 + 5;

struct edge
{
    int to, next;
}edges[maxN << 1];

int f[maxN << 1], rk[maxN << 1], head[maxN << 1], tot, noe = 0;
int stk[maxN << 1], top = 0;
bool ban[maxN << 1];

inline void add(int u, int v)
{
    edges[++noe].to = v, edges[noe].next = head[u], head[u] = noe;
}

inline int find(int x)
{
    return f[x] ^ x? (f[x] = find(f[x])):x;
}

inline void merger(int x, int y)
{
    x = find(x), y = find(y);
    if(x == y) return ;
    if(rk[x] < rk[y]) f[x] = y;
    else f[y] = x;
    if(rk[x] == rk[y]) ++rk[y];
    --tot;
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
        add(u, v), add(v, u);
    }
    int k;
    std::cin >> k;
    std::iota(f, f + n, 0);
    for(int i = 0; i < k; ++i)
    {
        std::cin >> u;
        stk[++top] = u;
        ban[u] = 1;
    }
    tot = n - k;
    for(int i = 0; i < n; ++i)
    {
        if(!ban[i])
        {
            for(int e = head[i]; e; e = edges[e].next)
            {
                int &v = edges[e].to;
                if(ban[v]) continue;
                merger(i, v);
            }
        }
    }
    for(int i = k; i; --i)
    {
        ban[stk[i]] = 0;
        stk[i + 1] = tot;
        ++tot;
        for(int e = head[stk[i]]; e; e = edges[e].next)
        {
            int &v = edges[e].to;
            if(ban[v]) continue;
            merger(stk[i], v);
        }
    }
    stk[1] = tot;
    for(int i = 1; i <= k + 1; ++i) std::cout << stk[i] << '\n';
    return 0;
}