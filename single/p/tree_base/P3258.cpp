// # [JLOI2014] 松鼠的新家

// ## 题目描述

// 松鼠的新家是一棵树，前几天刚刚装修了新家，新家有$n$ 个房间，并且有 $n-1$ 根树枝连接，每个房间都可以相互到达，且俩个房间之间的路线都是唯一的。天哪，他居然真的住在“树”上。

// 松鼠想邀请小熊维尼前来参观，并且还指定一份参观指南，他希望维尼能够按照他的指南顺序，先去 $a_1$，再去 $a_2$，……，最后到 $a_n$，去参观新家。可是这样会导致重复走很多房间，懒惰的维尼不停地推辞。可是松鼠告诉他，每走到一个房间，他就可以从房间拿一块糖果吃。

// 维尼是个馋家伙，立马就答应了。现在松鼠希望知道为了保证维尼有糖果吃，他需要在每一个房间各放至少多少个糖果。

// 因为松鼠参观指南上的最后一个房间 $a_n$ 是餐厅，餐厅里他准备了丰盛的大餐，所以当维尼在参观的最后到达餐厅时就不需要再拿糖果吃了。

// ## 输入格式

// 第一行一个正整数 $n$，表示房间个数第二行 $n$ 个正整数，依次描述 $a_1, a_2,\cdots,a_n$。

// 接下来 $n-1$ 行，每行两个正整数 $x,y$，表示标号 $x$ 和 $y$ 的两个房间之间有树枝相连。

// ## 输出格式

// 一共 $n$ 行，第 $i$ 行输出标号为 $i$ 的房间至少需要放多少个糖果，才能让维尼有糖果吃。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5
// 1 4 5 3 2
// 1 2
// 2 4
// 2 3
// 4 5
// ```

// ### 样例输出 #1

// ```
// 1
// 2
// 1
// 2
// 1
// ```

// ## 提示

// 对于全部的数据，$2 \le n \le 3 \times 10^5$，$1 \le a_i \le n$。
#include <bits/stdc++.h>

const int maxN = 3E5 + 5;
int head[maxN], noe = 0;
int dfn[maxN], f[maxN], son[maxN], top[maxN], depth[maxN], sz[maxN], cnt = 0;
int diff[maxN], arr[maxN];

struct edge
{
    int to, next;
}edges[maxN << 1];

inline void add(int u, int v)
{
    edges[++noe].to = v;
    edges[noe].next = head[u];
    head[u] = noe;
}

inline void dfs1(int u, int fa)
{
    depth[u] = depth[fa] + 1;
    f[u] = fa;
    for(int e = head[u]; e; e = edges[e].next)
    {
        int &v = edges[e].to;
        if(v == fa) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) son[u] = v;
    }
    ++sz[u];
}

inline void dfs2(int u, int topf)
{
    dfn[u] = ++cnt;
    top[u] = topf;
    if(!son[u]) return ;
    dfs2(son[u], topf);
    for(int e = head[u]; e; e = edges[e].next)
    {
        int &v = edges[e].to;
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

inline void modify(int u, int v)
{
    int lca = LCA(u, v);
    ++diff[u], ++diff[v];
    --diff[lca], --diff[f[lca]];
}

inline void dfs3(int u)
{
    for(int e = head[u]; e; e = edges[e].next)
    {
        int &v = edges[e].to;
        if(v == f[u]) continue;
        dfs3(v);
        diff[u] += diff[v];
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, u, v;
    std::cin >> n;
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    for(int i = 1; i < n; ++i)
    {
        std::cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for(int i = 1; i < n; ++i)
    {
        modify(arr[i], arr[i + 1]);
    }
    dfs3(1);
    for(int i = 1; i <= n; ++i)
    {
        std::cout << diff[i] - (i != arr[1]) << '\n';
    }
    return 0;
}