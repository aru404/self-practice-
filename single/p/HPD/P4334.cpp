// # [COI2007] Policija

// ## 题目描述

// To help capture criminals on the run, the police are introducing a new computer system. The area covered by the police contains N cities and E bidirectional roads connecting them. The cities are labelled 1 to N.

// 为了帮助抓捕逃犯，警方引进了一套新的电脑系统。警察的辖区包含 $N$ 座城市和 $E$ 条双向道路，城市的编号是 $1\sim N$。

// The police often want to catch criminals trying to get from one city to another. Inspectors, looking at a map, try to determine where to set up barricades and roadblocks. The new computer system should answer the following two types of queries:

// 警察常常要抓住那些逃往另一个城市的罪犯。侦查员看着地图，试着确定在哪里设置路障。新的计算机系统要回答以下两种问题：

// 1. Consider two cities A and B, and a road connecting cities G1 and G2. Can the criminals get
// from city A to city B if that one road is blocked and the criminals can't use it?

// 考虑城市 $A$ 和 $B$，以及连接城市 $G_1$ 和 $G_2$ 的道路。罪犯能否在那条路不通的情况下从 $A$ 逃到 $B$？

// 2. Consider three cities A, B and C. Can the criminals get from city A to city B if the entire city C is cut off and the criminals can't enter that city?

// 考虑三个城市 $A, B, C$。罪犯能否在无法通过 $C$ 的情况下从 $A$ 逃到 $B$?

// Write a program that implements the described system.

// 写一个程序实现上述系统。

// ## 输入格式

// The first line contains two integers N and E (2 ≤ N ≤ 100 000, 1 ≤ E ≤ 500 000), the number of cities and roads.

// 第一行两个整数 $N, E$（$2\leq N\leq 10 ^ 5$，$1\leq E\leq 5\times 10 ^ 5$），表示城市数量和道路数量。

// Each of the following E lines contains two distinct integers between 1 and N – the labels of two cities connected by a road. There will be at most one road between any pair of cities.

// 接下来 $E$ 行，每行两个不同的数字 $u, v$，表示编号为 $u, v$ 的城市之间有一条道路。一对城市之间最多只有一条道路。

// The following line contains the integer Q (1 ≤ Q ≤ 300 000), the number of queries the system is being tested on.

// 接下来一行，一个整数 $Q$（$1\leq Q\leq 3\times 10 ^ 5$），表示询问数量。

// Each of the following Q lines contains either four or five integers. The first of these integers is the type of the query – 1 or 2.

// 接下来 $Q$ 行，每行四或五个整数描述一组询问。第一个数表示询问的类型 —— $1$ 或 $2$。

// If the query is of type 1, then the same line contains four more integers A, B, G1 and G2 as described earlier. A and B will be different. G1 and G2 will represent an existing road.

// 如果询问类型为 $1$，那么在同一行还有四个整数 $A, B, G_1, G_2$。$A, B$ 不同，且 $G_1, G_2$ 之间存在道路。

// If the query is of type 2, then the same line contains three more integers A, B and C. A, B and C will be distinct integers.

// 如果询问类型为 $2$，那么在同一行还有三个整数 $A, B, C$。$A, B, C$ 两两不同。

// The test data will be such that it is initially possible to get from each city to every other city.

// 保证图中每两个点相互连通。

// ## 输出格式

// Output the answers to all Q queries, one per line. The answer to a query can be "yes" or "no".

// 对于每组询问，输出 `yes` 或 `no` 表示回答。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 13 15
// 1 2
// 2 3
// 3 5
// 2 4
// 4 6
// 2 6
// 1 4
// 1 7
// 7 8
// 7 9
// 7 10
// 8 11
// 8 12
// 9 12
// 12 13
// 5
// 1 5 13 1 2
// 1 6 2 1 4
// 1 13 6 7 8
// 2 13 6 7
// 2 13 6 8
// ```

// ### 样例输出 #1

// ```
// yes
// yes
// yes
// no
// yes
// ```

// ## 提示

// Croatian Olympiad in Informatics 2007 Task 2
#include <bits/stdc++.h>
#define ll long long

const int maxN = 1E5 + 5, maxM = 5E5 + 5;
struct edge{
    int to, next;
}edges[maxM << 1], nEdges[maxN << 2];

int stk[maxN], dfn[maxN << 1], low[maxN], noe = 0;
int head[maxN], nHead[maxN << 1], tot = 0, cnt = 0, scc;
int sz[maxN << 1], top[maxN << 1], depth[maxN << 1], son[maxN << 1], f[maxN << 1];
std::unordered_set<ll> cut;

inline void add(int u, int v, edge* es, int* hs)
{
    es[noe].to = v, es[noe].next = hs[u], hs[u] = noe++;
}

inline void tarjan1(int u, int pre)
{
    dfn[u] = low[u] = ++cnt;
    for(int e = head[u]; ~e; e = edges[e].next)
    {
        if(e == (pre ^ 1)) continue;
        int &v = edges[e].to;
        if(!dfn[v])
        {
            tarjan1(v, e);
            low[u] = std::min(low[u], low[v]);
            if(dfn[u] < low[v]) cut.emplace((1ll * u) << 17 | v);
        }
        else low[u] = std::min(low[u], dfn[v]);
    }
}

inline void tarjan2(int u)
{
    dfn[u] = low[u] = ++cnt;
    stk[++tot] = u;
    for(int e = head[u]; ~e; e = edges[e].next)
    {
        int &v = edges[e].to;
        if(!dfn[v])
        {
            tarjan2(v);
            low[u] = std::min(low[u], low[v]);
            if(dfn[u] == low[v])
            {
                ++scc;
                do{
                    add(stk[tot], scc, nEdges, nHead);
                    add(scc, stk[tot], nEdges, nHead);
                }while(stk[tot--] != v);
                add(u, scc, nEdges, nHead);
                add(scc, u, nEdges, nHead);
            }
        }
        else low[u] = std::min(low[u], dfn[v]);
    }
}

inline void dfs1(int u, int fa)
{
    depth[u] = depth[fa] + 1;
    f[u] = fa, sz[u] = 1;
    for(int e = nHead[u]; ~e; e = nEdges[e].next)
    {
        int &v = nEdges[e].to;
        if(v == fa) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if(sz[son[u]] < sz[v]) son[u] = v;
    }
}

inline void dfs2(int u, int topf)
{
    dfn[u] = ++cnt;
    top[u] = topf;
    if(!son[u]) return;
    dfs2(son[u], topf);
    for(int e = nHead[u]; ~e; e = nEdges[e].next)
    {
        int &v = nEdges[e].to;
        if(dfn[v]) continue;
        dfs2(v, v);
    }
}

inline int LCA(int u, int v)
{
    while(top[u] != top[v])
    {
        if(depth[top[u]] < depth[top[v]]) std::swap(u, v);
        u = f[top[u]];
    }
    return dfn[u] < dfn[v]? u:v;
}

bool isSon(int fa, int p)
{
    return dfn[fa] <= dfn[p] && dfn[fa] + sz[fa] - 1 >= dfn[p];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, u, v, q, g1, g2, t, c;
    std::cin >> n >> m;
    memset(head + 1, -1, sizeof(int) * n);
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v;
        add(u, v, edges, head);
        add(v, u, edges, head);
    }
    tarjan1(1, -1);
    
    noe = cnt = 0;
    scc = n;
    memset(dfn + 1, 0, sizeof(int) * n);
    memset(low + 1, 0, sizeof(int) * n);
    memset(nHead + 1, -1, sizeof(int) * (n << 1));
    tarjan2(1);
    
    cnt = 0;
    memset(dfn + 1, 0, sizeof(int) * n);
    dfs1(1, 0), dfs2(1, 1);

    std::cin >> q;
    for(int i = 0; i < q; ++i)
    {
        std::cin >> t >> u >> v;
        if(t == 1)
        {
            std::cin >> g1 >> g2;
            if(!cut.count((1ll * g1) << 17 | g2) && !cut.count((1ll * g2) << 17 | g1))
            {
                std::cout << "yes\n";
                continue;
            }

            int fa = dfn[g1] > dfn[g2]? f[g1]:f[g2];
            if(isSon(fa, u) ^ isSon(fa, v)) std::cout << "no\n";
            else std::cout << "yes\n";
        }
        else
        {
            std::cin >> c;
            bool f1 = isSon(c, u), f2 = isSon(c, v);
            if(f1 ^ f2) std::cout << "no\n";
            else if(f1 && f2 && LCA(u, v) == c) std::cout << "no\n";
            else std::cout << "yes\n";
        }
    }
    return 0;
}