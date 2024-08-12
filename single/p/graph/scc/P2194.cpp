// # HXY烧情侣

// ## 题目描述

// 众所周知，HXY 已经加入了 FFF 团。现在她要开始喜（sang）闻（xin）乐（bing）见（kuang）地烧情侣了。

// 这里有 $n$ 座电影院，$n$ 对情侣分别在每座电影院里，然后电影院里都有汽油，但是要使用它需要一定的费用。$m$ 条单向通道连接相邻的两对情侣所在电影院。

// HXY 有个绝技，如果她能从一个点开始烧，最后回到这个点，那么烧这条回路上的情侣的费用只需要该点的汽油费即可。并且每对情侣只需烧一遍，电影院可以重复去。然后她想花尽可能少的费用烧掉所有的情侣。

// 问：最少需要多少费用，并且当费用最少时的方案数是多少？由于方案数可能过大，所以请输出方案数对 $10^9+7$ 取模的结果。

// （注：这里 HXY 每次可以从任何一个点开始走回路。就是说一个回路走完了，下一个开始位置可以任选。所以说不存在烧不了所有情侣的情况，即使图不连通，HXY 自行选择顶点进行烧情侣行动。且走过的道路可以重复走。）

// ## 输入格式

// 第一行一个正整数 $n$。   
// 第二行 $n$ 个正整数，表示每个点的汽油费 $w_i$。  
// 第三行一个正整数 $m$。  
// 接下来 $m$ 行，每行两个正整数 $x_i,y_i$，表示一条 $x_i \to y_i$ 的单向道路。

// ## 输出格式

// 输出一行两个整数，分别表示最小花费，和花费最小时的方案数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// 1 2 3
// 3
// 1 2
// 2 3
// 3 2
// ```

// ### 样例输出 #1

// ```
// 3 1
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 3
// 10 20 10
// 4
// 1 2
// 1 3
// 3 1
// 2 1
// ```

// ### 样例输出 #2

// ```
// 10 2
// ```

// ## 提示

// 对于 $30\%$ 的数据，$1\le n,m \le 20$；  
// 对于另外 $10\%$ 的数据，保证不存在回路；  
// 对于 $100\%$ 的数据，$1\le n \le 10^5$，$1\le m \le 3\times 10^5$，$0\le w_i \le 10^9$。
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

const int maxN = 1E5 + 5, maxM = 3E5 + 5;
const int mod = 1E9 + 7;
struct edge
{
    int to, next;
}edges[maxM];

int head[maxN], new_head[maxN], w[maxN], noe = 0;
int dfn[maxN], low[maxN], stk[maxN], inv[maxN], new_w[maxN], sz[maxN], cnt = 0, top = 0, scc = 0;
bool in_stk[maxN];

inline void add(int u, int v, int* hs, edge* es)
{
    es[++noe].to = v, es[noe].next = hs[u], hs[u] = noe;
}

inline void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    stk[++top] = u;
    in_stk[u] = 1;
    for(int e = head[u]; e; e = edges[e].next)
    {
        int &v = edges[e].to;
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
        new_w[scc] = INF;
        do{
            inv[stk[top]] = scc;
            in_stk[stk[top]] = 0;
            if(new_w[scc] > w[stk[top]])
            {
                sz[scc] = 1;
                new_w[scc] = w[stk[top]];
            }
            else if(new_w[scc] == w[stk[top]]) ++sz[scc];
        }while(stk[top--] != u);
    }
}

inline void shrink(int n)
{
    for(int i = 1; i <= n; ++i)
    {
        if(!dfn[i]) tarjan(i);
    }

    long long mn_cost = 0;
    int scheme_cnt = 1;
    for(int i = 1; i <= scc; ++i)
    {
        mn_cost += new_w[i];
        scheme_cnt = 1ll * scheme_cnt * sz[i] % mod;
    }
    std::cout << mn_cost << ' ' << scheme_cnt;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, u, v;
    std::cin >> n;
    for(int i = 1; i <= n; ++i) std::cin >> w[i];
    std::cin >> m;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v;
        add(u, v, head, edges);
    }
    shrink(n);
    return 0;
}