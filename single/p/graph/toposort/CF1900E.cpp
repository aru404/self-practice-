// # Transitive Graph

// ## 题面翻译

// 有一个 $N$ 个点，$M$ 条边的 **有向图**  $G$ ，对于一个顶点 $u$ ，它的权值为 $a_u$。

// 现在对它进行以下操作：

// - 若存在三元组 $a, b, c$ ，使得 $a$ 到 $b$ 有一条边， $b$ 到 $c$ 有一条边，但是 $a$ 到 $c$ 没边，则连一条 $a$ 到 $c$ 的边。

// - 重复上述操作直到这样的三元组不存在。

// 当上述操作完成后，请计算图中最长的 **不经过相同的点** 的路径长度，并计算这些最长路径中，路径上的点权值和 **最小** 是多少。

// **请注意图中可能存在重边和自环。**

// 翻译提供： @aaaaaaqqqqqq

// ## 题目描述

// You are given a directed graph $ G $ with $ n $ vertices and $ m $ edges between them.

// Initially, graph $ H $ is the same as graph $ G $ . Then you decided to perform the following actions:

// - If there exists a triple of vertices $ a $ , $ b $ , $ c $ of $ H $ , such that there is an edge from $ a $ to $ b $ and an edge from $ b $ to $ c $ , but there is no edge from $ a $ to $ c $ , add an edge from $ a $ to $ c $ .
// - Repeat the previous step as long as there are such triples.

// Note that the number of edges in $ H $ can be up to $ n^2 $ after performing the actions.

// You also wrote some values on vertices of graph $ H $ . More precisely, vertex $ i $ has the value of $ a_i $ written on it.

// Consider a simple path consisting of $ k $ distinct vertices with indexes $ v_1, v_2, \ldots, v_k $ . The length of such a path is $ k $ . The value of that path is defined as $ \sum_{i = 1}^k a_{v_i} $ .

// A simple path is considered the longest if there is no other simple path in the graph with greater length.

// Among all the longest simple paths in $ H $ , find the one with the smallest value.

// ## 输入格式

// Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

// The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n,m \le 2 \cdot 10^5 $ ) — the number of vertices and the number of edges.

// The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the numbers written on the vertices of graph $ H $ .

// The $ i $ -th of the next $ m $ lines contains two integers $ v_i $ and $ u_i $ ( $ 1 \le v_i, u_i \le n $ ) — meaning that there is an edge going from vertex $ v_i $ to vertex $ u_i $ in graph $ G $ . Note that edges are directed. Also note that the graph may have self-loops and multiple edges.

// It is guaranteed that neither the sum of $ n $ nor the sum of $ m $ over all test cases exceeds $ 2 \cdot 10^5 $ .

// ## 输出格式

// For each test case, output two numbers — the length of the longest simple path in $ H $ and the minimal possible value of such path.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// 5 6
// 2 2 4 1 3
// 1 2
// 1 3
// 2 4
// 3 4
// 4 5
// 5 2
// 7 7
// 999999999 999999999 999999999 999999999 1000000000 999999999 1000000000
// 1 2
// 2 3
// 3 4
// 4 1
// 4 5
// 4 6
// 6 7
// 14 22
// 2 3 5 7 3 4 1 4 3 4 2 2 5 1
// 1 2
// 2 3
// 2 4
// 3 1
// 4 4
// 4 5
// 5 6
// 5 6
// 5 12
// 6 7
// 6 8
// 7 5
// 7 7
// 7 9
// 8 4
// 9 11
// 10 9
// 11 10
// 11 10
// 12 13
// 13 14
// 14 12
// ```

// ### 样例输出 #1

// ```
// 5 12
// 6 5999999995
// 11 37
// ```

// ## 提示

// In the first test case, the longest path in both graphs is $ 1 \to 3 \to 4 \to 5 \to 2 $ . As the path includes all vertices, the minimal possible value of the longest path is the sum of values on all vertices, which is $ 12 $ .

// In the second test case, the longest possible path is $ 1 \to 2 \to 3 \to 4 \to 6 \to 7 $ . As there are no longest paths with vertex $ 5 $ in them, this path has the minimal possible value of $ 5\,999\,999\,995 $ .

// In the third test case, it can be proven that there is no path longer than $ 11 $ and that the value of the longest path cannot be less than $ 37 $ . Also, notice that the given graph has both self-loops and multiple edges.
#include <bits/stdc++.h>
#define ll long long
const int maxN = 2E5 + 5;

int h1[maxN], h2[maxN], in[maxN];
int dfn[maxN], low[maxN], stk[maxN], inv[maxN], top = 0, noe = 0, scc = 0, cnt = 0;
int w[maxN], sz[maxN], totSz[maxN];
ll nw[maxN], totW[maxN];
std::bitset<maxN> inStk = 0;

struct Edge
{
    int to, next;
}e1[maxN], e2[maxN];

inline void add(int u, int v, int* h, Edge* e)
{
    e[++noe] = {v, h[u]};
    h[u] = noe;
}

inline void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    stk[++top] = u;
    inStk[u] = 1;
    for(int e = h1[u]; e; e = e1[e].next)
    {
        int &v = e1[e].to;
        if(!dfn[v])
        {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        }
        else if(inStk[v]) low[u] = std::min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        ++scc;
        do
        {
            inStk[stk[top]] = 0;
            inv[stk[top]] = scc;
            ++sz[scc];
            nw[scc] += w[stk[top]];
        }while(stk[top--] != u);
    }
}

inline void topsort(int n)
{
    std::queue<int> q;
    for(int i = 1; i <= scc; ++i) if(!in[i]) q.push(i), totSz[i] = sz[i], totW[i] = nw[i];
    int mx = 0;
    ll mnW = INT64_MAX;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        if(mx == totSz[u]) mnW = std::min(mnW, totW[u]);
        else if(mx < totSz[u]) mx = totSz[u], mnW = totW[u];
        for(int e = h2[u]; e; e = e2[e].next)
        {
            int v = e2[e].to;
            --in[v];
            if(totSz[u] + sz[v] == totSz[v]) totW[v] = std::min(totW[v], totW[u] + nw[v]);
            else if(totSz[u] + sz[v] > totSz[v])
            {
                totSz[v] = totSz[u] + sz[v];
                totW[v] = totW[u] + nw[v];
            }
            if(!in[v]) q.push(v);
        }
    }
    std::cout << mx << ' ' << mnW << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, m, n, u, v;
    std::cin >> t;
    for(int i = 0; i < t; ++i)
    {
        std::cin >> n >> m;

        for(int i = 1; i <= n; ++i) std::cin >> w[i];
        for(int i = 0; i < m; ++i)
        {
            std::cin >> u >> v;
            add(u, v, h1, e1);
        }
        for(int i = 1; i <= n; ++i)
        {
            if(!dfn[i]) tarjan(i);
        }
        noe = 0;
        for(int i = 1; i <= n; ++i)
        {
            for(int e = h1[i]; e; e = e1[e].next)
            {
                int &v = e1[e].to;
                if(inv[v] != inv[i]) add(inv[i], inv[v], h2, e2), ++in[inv[v]];
            }
        }
        topsort(scc);

        memset(h1 + 1, 0, sizeof(int) * n);
        memset(h2 + 1, 0, sizeof(int) * n);
        memset(dfn + 1, 0, sizeof(int) * n);
        memset(sz + 1, 0, sizeof(int) * scc);
        memset(nw + 1, 0, sizeof(ll) * scc);
        memset(totSz + 1, 0, sizeof(int) * scc);
        memset(totW + 1, 0, sizeof(ll) * scc);
        noe = cnt = scc = 0;
    }
    return 0;
}