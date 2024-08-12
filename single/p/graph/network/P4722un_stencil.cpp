// # 【模板】最大流 加强版 / 预流推进

// ## 题目描述

// 给定 $n$ 个点，$m$ 条有向边，给定每条边的容量，求从点 $s$ 到点 $t$ 的最大流。

// ## 输入格式

// 第一行包含四个正整数 $n$、$m$、$s$、$t$，用空格分隔，分别表示点的个数、有向边的个数、源点序号、汇点序号。

// 接下来 $m$ 行每行包含三个正整数 $u_i$、$v_i$、$c_i$，用空格分隔，表示第 $i$ 条有向边从 $u_i$ 出发，到达 $v_i$，容量为 $c_i$。

// ## 输出格式

// 一个整数，表示 $s$ 到 $t$ 的最大流。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 7 14 1 7
// 1 2 5
// 1 3 6
// 1 4 5
// 2 3 2
// 2 5 3
// 3 2 2
// 3 4 3
// 3 5 3
// 3 6 7
// 4 6 5
// 5 6 1
// 6 5 1
// 5 7 8
// 6 7 7
// ```

// ### 样例输出 #1

// ```
// 14
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 10 16 1 2
// 1 3 2
// 1 4 2
// 5 2 2
// 6 2 2
// 3 5 1
// 3 6 1
// 4 5 1
// 4 6 1
// 1 7 2147483647
// 9 2 2147483647
// 7 8 2147483647
// 10 9 2147483647
// 8 5 2
// 8 6 2
// 3 10 2
// 4 10 2
// ```

// ### 样例输出 #2

// ```
// 8
// ```

// ## 提示

// $1\leqslant n \leqslant 1200, 1\leqslant m \leqslant 120000, 1\leqslant c \leqslant 2^{31}-1$。

// 保证答案不超过 $2^{31}-1$。

// 常用网络流算法的复杂度为 $O(n^2 m)$，请尽量优化算法。

// 数据提供者：@negiizhao

// （如果有人用 dinic 算法过掉了此题，请私信上传者）
#include <bits/stdc++.h>

const int maxN = 1205, maxM = 1.2E5 + 5;

struct edge
{
    int to, next, cap;
    edge(int to = 0, int next = 0, int cap = 0): to(to), next(next), cap(cap){}
}edges[maxM << 1];

int head[maxN], noe = 0;
int height[maxN], gap[maxN << 1], s, t, n;

inline void add(int u, int v, int w)
{
    edges[noe].to = v;
    edges[noe].cap = w;
    edges[noe].next = head[u];
    head[u] = noe++;
}

struct cmp
{
    bool operator()(const ) const
    {

    }
};

inline bool bfs()
{
    height[t] = 1;
    std::queue<int> q;
    q.emplace(q);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        ++gap[height[u]];
        for(int e = head[u]; ~e; e = edges[e].next)
        {
            int &v = edges[e].to;
            if(height[v] || !edges[e ^ 1].cap) continue;
            height[v] = height[u] + 1;
            q.push(v);
        }
    }
    return height[s] == 0;
}

int main()
{

}