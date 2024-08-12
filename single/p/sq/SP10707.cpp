// # COT2 - Count on a tree II

// ## 题面翻译

// - 给定 $n$ 个结点的树，每个结点有一种颜色。
// - $m$ 次询问，每次询问给出 $u,v$，回答 $u,v$ 之间的路径上的结点的不同颜色数。
// - $1\le n\le 4\times 10^4$，$1\le m\le 10^5$，颜色是不超过 $2 \times 10^9$ 的非负整数。

// ## 题目描述

// You are given a tree with **N** nodes. The tree nodes are numbered from **1** to **N**. Each node has an integer weight.

// We will ask you to perform the following operation:

// - **u v** : ask for how many different integers that represent the weight of nodes there are on the path from **u** to **v**.

// ## 输入格式

// In the first line there are two integers **N** and **M**. (**N** <= 40000, **M** <= 100000)

// In the second line there are **N** integers. The i-th integer denotes the weight of the i-th node.

// In the next **N-1** lines, each line contains two integers **u** **v**, which describes an edge (**u**, **v**).

// In the next **M** lines, each line contains two integers **u** **v**, which means an operation asking for how many different integers that represent the weight of nodes there are on the path from **u** to **v**.

// ## 输出格式

// For each operation, print its result.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 8 2
// 105 2 9 3 8 5 7 7
// 1 2
// 1 3
// 1 4
// 3 5
// 3 6
// 3 7
// 4 8
// 2 5
// 7 8
// ```

// ### 样例输出 #1

// ```
// 4
// 4
// ```
#include <bits/stdc++.h>

const int maxN = 4E4 + 5, maxM = 1E5 + 5;

int col[maxN], dfn[maxN], cnt[maxN], lca[maxM], inv1[maxN << 1], inv2[maxN << 1], tmp[maxM];
int h1[maxN], h2[maxN], suf[maxN], pre[maxN], f[maxN], tot = 0, noe = 0, noc = 0;
int arr[maxN << 1], res[maxM];
bool vis[maxN];

struct Edge{
    int to, next;
}e1[maxN << 1], e2[maxM << 1];

struct Query
{
    int l, r;
    bool operator<(const Query& other)const
    {
        return inv1[l] ^ inv1[other.l]? inv1[l] < inv1[other.l]:(inv1[l] & 1)? r < other.r:r > other.r;
    }
}queries[maxM];

inline void add(int u, int v, int* h, Edge* e)
{
    e[noe] = {v, h[u]};
    h[u] = noe++;
}

inline int find(int x)
{
    return x ^ f[x]? (f[x] = find(f[x])):x;
}

inline void dfs(int u, int fa)
{
    f[u] = u;
    pre[u] = ++tot;
    inv2[tot] = u;
    vis[u] = 1;
    for(int e = h1[u]; ~e; e = e1[e].next)
    {
        int& v = e1[e].to;
        if(v == fa) continue;
        dfs(v, u);
        f[v] = u;
    }
    for(int e = h2[u]; ~e; e = e2[e].next)
    {
        int& v = e2[e].to;
        if(vis[v]) lca[e >> 1] = find(v);
    }
    suf[u] = ++tot;
    inv2[tot] = u;
}

inline void inintial(int n, int m)
{
    int len = n << 1;
    int sz = std::max(1, static_cast<int>(len / sqrt(m))), nob = (len + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(len, i * sz);
        for(int j = st; j <= ed; ++j)
        {
            inv1[j] = i;
        }
    }
    dfs(1, 0);
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int& a, const int& b){
        return col[a] < col[b];
    });
    int k = 0, now = -1;
    for(int i = 1; i <= n; ++i)
    {
        if(col[tmp[i]] > now) ++k, now = col[tmp[i]];
        arr[pre[tmp[i]]] = arr[suf[tmp[i]]] = k;
    }
    for(int i = 0; i < m; ++i)
    {
        int u = e2[i << 1].to, v = e2[i << 1 | 1].to;
        if(pre[u] > pre[v]) std::swap(u, v);
        if(lca[i] == u || lca[i] == v)
        {
            queries[i].l = pre[u];
            lca[i] = 0;
        }
        else
        {
            queries[i].l = suf[u];
        }
        queries[i].r = pre[v];
    }
    std::iota(tmp, tmp + m, 0);
    std::sort(tmp, tmp + m, [&](const int& a, const int& b){
        return queries[a] < queries[b];
    });
    memset(vis + 1, 0, sizeof(bool) * n);
}

inline void add(int x)
{
    if(!cnt[arr[x]]) ++noc;
    ++cnt[arr[x]];
}

inline void del(int x)
{
    --cnt[arr[x]];
    if(!cnt[arr[x]]) --noc;
}

inline void modify(int x)
{
    if(!vis[inv2[x]]) add(x);
    else del(x);
    vis[inv2[x]] ^= 1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, u, v;
    std::cin >> n >> m;
    memset(h1 + 1, -1, sizeof(int) * n);
    memset(h2 + 1, -1, sizeof(int) * n);
    for(int i = 1; i <= n; ++i) std::cin >> col[i];
    for(int i = 0; i < n - 1; ++i)
    {
        std::cin >> u >> v;
        add(u, v, h1, e1);
        add(v, u, h1, e1);
    }
    noe = 0;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v;
        add(u, v, h2, e2);
        add(v, u, h2, e2);
    }
    inintial(n, m);
    int l = 1, r = 0;
    for(int i = 0; i < m; ++i)
    {
        int& ql = queries[tmp[i]].l, qr = queries[tmp[i]].r;
        while(ql < l) modify(--l);
        while(ql > l) modify(l++);
        while(qr > r) modify(++r);
        while(qr < r) modify(r--);
        res[tmp[i]] = noc + (lca[tmp[i]] && !cnt[arr[pre[lca[tmp[i]]]]]);
    }
    for(int i = 0; i < m; ++i) std::cout << res[i] << '\n';
    return 0;
}