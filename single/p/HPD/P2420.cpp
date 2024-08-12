// # 让我们异或吧

// ## 题目描述

// 异或是一种神奇的运算,大部分人把它总结成不进位加法.

// 在生活中 xor 运算也很常见。比如，对于一个问题的回答，是为 $1$，否为 $0$，那么：

// （$A$ 是否是男生）xor（$B$ 是否是男生）＝ $A$ 和 $B$ 是否能够成为情侣

// 好了，现在我们来制造和处理一些复杂的情况。比如我们将给出一颗树，它很高兴自己有 $N$ 个结点。树的每条边上有一个权值。我们要进行 $M$ 次询问，对于每次询问，我们想知道某两点之间的路径上所有边权的异或值。

// ## 输入格式

// 输入文件第一行包含一个整数 $N$ ，表示这颗开心的树拥有的结点数，以下有 $N-1$ 行，描述这些边，每行有3个数，$u,v,w$，表示 $u$ 和 $v$ 之间有一条权值为 $w$ 的边。接下来一行有一个整数 $M$，表示询问数。之后的 $M$ 行，每行两个数 $u,v$，表示询问这两个点之间的路径上的权值异或值。

// ## 输出格式

// 输出 $M$ 行，每行一个整数，表示异或值

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5
// 1 4 9644
// 2 5 15004
// 3 1 14635
// 5 3 9684
// 3
// 2 4
// 5 4
// 1 1
// ```

// ### 样例输出 #1

// ```
// 975
// 14675
// 0
// ```

// ## 提示

// 对于 $40\%$ 的数据，有 $1 \le N,M \le 3000$；  
// 对于 $100\%$ 的数据，有 $1 \le N ,M\le 100000$。

// 保证边权在 `int` 范围内。
#include <bits/stdc++.h>

const int maxN = 1E5 + 5;

struct edge
{
    int to, next;
}edges[maxN << 1];

int head[maxN], w[maxN], nw[maxN], noe = 0, cnt = 0;

inline void add(int u, int v)
{
    edges[noe].to = v;
    edges[noe].next = head[u];
    head[u] = noe++;
}

inline void dfs(int u, int fa)
{
    for(int e = head[u]; ~e; e = edges[e].next)
    {
        int &v = edges[e].to;
        if(v == fa) continue;
        nw[v] = nw[u] ^ w[e >> 1];
        dfs(v, u);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, u, v, m;
    std::cin >> n;
    memset(head + 1, -1, sizeof(int) * n);
    for(int i = 0; i < n - 1; ++i)
    {
        std::cin >> u >> v >> w[i];
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    std::cin >> m;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v;
        std::cout << (nw[u] ^ nw[v]) << '\n';
    }
    return 0;
}