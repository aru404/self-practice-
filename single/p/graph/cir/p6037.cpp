// # Ryoku 的探索

// ## 题目背景

// Ryoku 对自己所处的世界充满了好奇，她希望能够在她「死」之前尽可能能多地探索世界。

// 这一天，Ryoku 得到了一张这个世界的地图，她十分高兴。然而，Ryoku 并不知道自己所处的位置到底在哪里，她也不知道她会什么时候死去。她想要知道如何才能尽可能多的探索这个世界。

// ## 题目描述

// Ryoku 所处的世界可以抽象成一个有 $n$ 个点， $n$ 条边的带权无向连通图 $G$。每条边有美观度和长度。

// Ryoku 会使用这样一个策略探索世界：在每个点寻找一个**端点她未走过**的边中**美观度最高**的走，如果没有边走，就沿着她前往这个点的边返回，类似于图的**深度优先遍历**。

// 探索的一个方案的长度是这个方案所经过的所有边长度的和（返回时经过的长度不用计算）。

// 她想知道，对于每一个起点 $s=1,2,\cdots,n$，她需要走过的长度是多少？

// ## 输入格式

// 输入包含 $n + 1$  行，其中第一行包含一个整数 $n$。  
// 接下来 $n$ 行每行包含四个整数 $u,v,w,p$，描述了一条连接 $u$ 和 $v$，长度为 $w$，美观度为 $p$ 的无向边。

// ## 输出格式

// 输出包含 $n$ 行，每行一个整数，第 $i$ 行为 $s=i$ 时的答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5
// 4 1 2 1
// 1 2 3 2
// 3 1 1 4
// 3 5 2 5
// 2 3 2 3
// ```

// ### 样例输出 #1

// ```
// 7
// 7
// 8
// 7
// 8
// ```

// ## 提示

// **【样例 1 说明】**

// 以下为输入输出样例 1 中的图： （边上红色数组为 $p$，黑色为 $w$）

// ![](https://cdn.luogu.com.cn/upload/image_hosting/rmk07281.png)

// 若起点为 $1$，顺序为 $1\to3\to5\to2\to4$，长度之和为 $7$。  
// 若起点为 $2$，顺序为 $2\to3\to5\to1\to4$，长度之和为 $7$。  
// 若起点为 $3$，顺序为 $3\to5\to1\to2\to4$，长度之和为 $8$。  
// 若起点为 $4$，顺序为 $4\to1\to3\to5\to2$，长度之和为 $7$。  
// 若起点为 $5$，顺序为 $5\to3\to1\to2\to4$，长度之和为 $8$。  

// ---

// **【数据规模与约定】**

// 对于 $40\%$ 的数据，$n\le 10^3$。    
// 对于 $100\%$ 的数据，$3 \le n \le 10^6$，$1 \le u,v,p \le n$，$0\le w\le 10^9$，保证 $p$ 互不相同。
#include <bits/stdc++.h>
#define ll long long
const int maxN = 1E6 + 5;

struct edge
{
    int to, next;
}edges[maxN << 1];

int head[maxN], w[maxN], p[maxN], noe = 0;
int stk[maxN], cirE[maxN], top = 0, cnt = 0;
bool inStk[maxN], ban[maxN << 1];
ll res[maxN], totW, val;

inline void add(int u, int v)
{
    edges[noe].to = v;
    edges[noe].next = head[u];
    head[u] = noe++;
}

inline bool dfs1(int u, int pre)
{
    if(inStk[u])
    {
        do{
            cirE[++cnt] = stk[top];
        }while(edges[stk[--top]].to != u && top);
        return true;
    }
    inStk[u] = 1;
    for(int e = head[u]; ~e; e = edges[e].next)
    {
        if(e == (pre ^ 1)) continue;
        int &v = edges[e].to;
        stk[++top] = e;
        if(dfs1(v, e)) return true;
    }
    inStk[u] = 0;
    --top;
    return false;
}

inline void dfs2(int u, int pre)
{
    res[u] = val;
    for(int e = head[u]; ~e; e = edges[e].next)
    {
        if(ban[e] || e == (pre ^ 1)) continue;
        int &v = edges[e].to;
        dfs2(v, e);
    }
}

inline void solveCir(int n)
{
    for(int i = 1; i <= cnt; ++i)
    {
        ban[cirE[i]] = ban[cirE[i] ^ 1] = 1;
    }
    for(int i = 2; i <= cnt; ++i)
    {
        val = totW - (p[cirE[i] >> 1] < p[cirE[i - 1] >> 1]? w[cirE[i] >> 1]:w[cirE[i - 1] >> 1]);
        dfs2(edges[cirE[i]].to, -1);
    }
    val = totW - (p[cirE[1] >> 1] < p[cirE[cnt] >> 1]? w[cirE[1] >> 1]:w[cirE[cnt] >> 1]);
    dfs2(edges[cirE[1]].to, -1);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, u, v;
    std::cin >> n;
    memset(head + 1, -1, sizeof(int) * n);
    for(int i = 0; i < n; ++i)
    {
        std::cin >> u >> v >> w[i] >> p[i];
        add(u, v);
        add(v, u);
        totW += w[i];
    }
    dfs1(1, -1);
    solveCir(n);
    for(int i = 1; i <= n; ++i) std::cout << res[i] << '\n';
    return 0;
}