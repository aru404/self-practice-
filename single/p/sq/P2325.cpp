// # [SCOI2005] 王室联邦

// ## 题目描述

// “余”人国的国王想重新编制他的国家。他想把他的国家划分成若干个省，每个省都由他们王室联邦的一个成员来管理。

// 他的国家有 $N$ 个城市，编号为 $1\ldots N$。

// 一些城市之间有道路相连，任意两个不同的城市之间有且仅有一条直接或间接的道路。

// 为了防止管理太过分散，每个省至少要有 $B$ 个城市。

// 为了能有效的管理，每个省最多只有 $3\times B$ 个城市。

// 每个省必须有一个省会，这个省会可以位于省内，也可以在该省外。

// 但是该省的任意一个城市到达省会所经过的道路上的城市（除了最后一个城市，即该省省会）都必须属于该省。

// 一个城市可以作为多个省的省会。

// 聪明的你快帮帮这个国王吧！

// ## 输入格式

// 第一行包含两个数 $N,B$。

// 接下来 $N－1$ 行，每行描述一条边，包含两个数，即这条边连接的两个城市的编号。

// ## 输出格式

// 如果无法满足国王的要求，输出 $0$。

// 否则第一行输出数 $K$，表示你给出的划分方案中省的个数。

// 第二行输出 $N$ 个数，第 $I$ 个数表示编号为 $I$ 的城市属于的省的编号。要求城市编号在 $[1,K]$ 范围内。

// 第三行输出 $K$ 个数，表示这 $K$ 个省的省会的城市编号。

// 如果有多种方案，你可以输出任意一种。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 8 2 
// 1 2 
// 2 3 
// 1 8 
// 8 7 
// 8 6 
// 4 6 
// 6 5
// ```

// ### 样例输出 #1

// ```
// 3 
// 2 1 1 3 3 3 3 2 
// 2 1 8
// ```

// ## 提示

// 对于 $100\%$ 的数据，$1\le B\leq N\le 10^3$。

// 感谢 @[FlierKing](/user/9433) 提供 spj。
#include <bits/stdc++.h>

const int maxN = 1E3 + 5;
int s[maxN], ps[maxN], st[maxN], ed[maxN], fa[maxN], inv[maxN], top = 0, cnt = 0, idx = 0;
int head[maxN], noe = 0, lim, k = 0;

struct Edge
{
    int to, next;
}edges[maxN << 1];

inline void add(int u, int v)
{
    edges[noe] = {v, head[u]};
    head[u] = noe++;
}

inline void dfs(int u, int f)
{
    s[++top] = u;
    int tmp = top;
    for(int e = head[u]; ~e; e = edges[e].next)
    {
        int & v = edges[e].to;
        if(v == f) continue;
        dfs(v, u);
        if(top - tmp >= lim)
        {
            st[++cnt] = idx + 1;
            do{
                inv[s[top]] = cnt;
                ps[++idx] = s[top--];
            }while(top != tmp);
            ed[cnt] = idx;
            fa[cnt] = u;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, u, v;
    std::cin >> n >> lim;
    memset(head + 1, -1, sizeof(int) * n);
    for(int i = 0; i < n - 1; ++i)
    {
        std::cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    if(!cnt) st[++cnt] = 1, fa[cnt] = 1;
    while(top) ps[++idx] = s[top], inv[s[top--]] = cnt;
    ed[cnt] = idx;
    std::cout << cnt << '\n';
    for(int i = 1; i <= n; ++i) std::cout << inv[i] << " \n"[i == n];
    for(int i = 1; i <= cnt; ++i) std::cout << fa[i] << " \n"[i == cnt];
    return 0;
}