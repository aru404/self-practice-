// # [JSOI2010] 连通数

// ## 题目背景

// 本题数据过水，可前往 https://www.luogu.com.cn/problem/U143178 提交

// $\text{upd 2022.8.4}$：已作为 Hack 数据合并进来。

// ## 题目描述

// 度量一个有向图连通情况的一个指标是连通数，指图中可达顶点对个的个数。

// 如图

// ![qwq](https://cdn.luogu.com.cn/upload/pic/15481.png)

// 顶点 $1$ 可达 $1, 2, 3, 4, 5$

// 顶点 $2$ 可达 $2, 3, 4, 5$

// 顶点 $3$ 可达 $3, 4, 5$

// 顶点 $4, 5$ 都只能到达自身。

// 所以这张图的连通数为 $14$。

// 给定一张图，请你求出它的连通数

// ## 输入格式

// 输入数据第一行是图顶点的数量，一个正整数 $N$。  
// 接下来 $N$ 行，每行 $N$ 个字符。第 $i$ 行第 $j$ 列的 `1` 表示顶点 $i$ 到 $j$ 有边，`0` 则表示无边。

// ## 输出格式

// 输出一行一个整数，表示该图的连通数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// 010
// 001
// 100
// ```

// ### 样例输出 #1

// ```
// 9
// ```

// ## 提示

// 对于 $100 \%$ 的数据，$1 \le N \le 2000$。
#include <bits/stdc++.h>

const int maxN = 2E3 + 5;
std::vector<int> es[maxN], new_es[maxN];
int dfn[maxN], low[maxN], stk[maxN], inv[maxN], sz[maxN], in_degree[maxN], top = 0, cnt = 0, scc = 0;
int tot[maxN];
bool in_stk[maxN];
std::bitset<maxN> vis[maxN];

inline void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    stk[++top] = u;
    in_stk[u] = 1;
    for(auto v:es[u])
    {
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
            ++sz[scc];
        }while(stk[top--] != u);
    }
}

inline void shrink(int n)
{
    for(int i = 1; i <= n; ++i)
    {
        if(!dfn[i]) tarjan(i);
    }
    for(int i = 1; i <= scc; ++i)
    {
        vis[i][i] = 1;
    }
    for(int i = 1; i <= n; ++i)
    {
        for(auto v:es[i])
        {
            if(inv[i] != inv[v])
            {
                new_es[inv[v]].push_back(inv[i]);
                ++in_degree[inv[i]];
            }
        }
    }

    std::queue<int> q;
    for(int i = 1; i <= scc; ++i)
    {
        if(!in_degree[i]) q.emplace(i);
    }
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        tot[u] += sz[u];
        for(auto v:new_es[u])
        {
            vis[v] |= vis[u];
            --in_degree[v];
            if(!in_degree[v]) q.push(v);
        }
    }
}

int main()
{
    int n;
    char s[maxN];
    scanf("%d\n", &n);
    for(int i = 1; i <= n; ++i)
    {
        scanf("%s", s + 1);
        for(int j = 1; j <= n; ++j)
        {
            if(s[j] == '1') es[i].push_back(j);
        }
    }
    shrink(n);
    int res = 0;
    for(int i = 1; i <= scc; ++i)
    {
        for(int j = 1; j <= scc; ++j)
        {
            if(vis[i][j]) res += sz[i] * sz[j];
        }
    }
    std::cout << res;
    return 0;
}