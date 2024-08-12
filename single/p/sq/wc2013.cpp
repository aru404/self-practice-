// Candyland 有一座糖果公园，公园里不仅有美丽的风景、好玩的游乐项目，还有许多免费糖果的发放点，这引来了许多贪吃的小朋友来糖果公园玩。

// 糖果公园的结构十分奇特，它由
// $n$
// 个游览点构成，每个游览点都有一个糖果发放处，我们可以依次将游览点编号为
// $1$
// 至
// $n$
// 。有

// $n - 1$
// 条双向道路连接着这些游览点，并且整个糖果公园都是连通的，即从任何一个游览点出发都可以通过这些道路到达公园里的所有其它游览点。

// 糖果公园所发放的糖果种类非常丰富，总共
// $m$
// 种，它们的编号依次为
// $1$
// 至
// $m$
// 。每一个糖果发放处都只发放某种特定的糖果，我们用
// $c_i$
// 来表示

// $i$
// 号游览点的糖果。

// 来到公园里游玩的游客都不喜欢走回头路，他们总是从某个特定的游览点出发前往另一个特定的游览点，并游览途中的景点，这条路线一定是唯一的。他们经过每个游览点，都可以品尝到一颗对应种类的糖果。

// 大家对不同类型的糖果的喜爱程度都不尽相同。根据游客们的反馈打分，我们得到了糖果的美味指数，第
// $i$
// 种糖果的美味指数为
// $v_i$
// 。另外，如果一位游客反复地品尝同一种类的糖果，他肯定会觉得有一些腻。根据量化统计，我们得到了游客第
// $i$
// 次品尝某类糖果的新奇指数
// $w_i$
// ，如果一位游客第
// $i$
// 次品尝第
// $j$
// 种糖果，那么他的愉悦指数
// $H$
// 将会增加对应的美味指数与新奇指数的乘积，即

// $v_j w_i$
// 。这位游客游览公园的愉悦指数最终将是这些乘积的和。

// 当然，公园中每个糖果发放点所发放的糖果种类不一定是一成不变的。有时，一些糖果点所发放的糖果种类可能会更改（也只会是

// $m$
// 种中的一种），这样的目的是能够让游客们总是感受到惊喜。

// 糖果公园的工作人员小 A 接到了一个任务，那就是根据公园最近的数据统计出每位游客游玩公园的愉悦指数。但数学不好的小 A 一看到密密麻麻的数字就觉得头晕，作为小 A 最好的朋友，你决定帮他一把。
// 输入格式

// 第一行包含三个正整数

// $n, m, q$
// ，分别表示游览点个数、糖果种类数和操作次数。  

// 第二行包含
// $m$
// 个正整数

// $v_1, v_2, \dots, v_m$
// 。

// 第三行包含
// $n$
// 个正整数

// $w_1, w_2, \dots, w_n$
// 。

// 第四行到第
// $n + 2$
// 行，每行包含两个正整数

// $a_i, b_i$
// ，表示这两个游览点之间有路径可以直接到达。

// 第
// $n + 3$
// 行包含
// $n$
// 个正整数

// $c_1, c_2, \dots, c_n$
// 。

// 接下来
// $q$
// 行，每行包含三个整数

// $t, x, y$
// ，表示一次操作：

// 若
// $t$
// 为
// $0$
// ，则
// $1 \leq x \leq n$
// ，
// $1 \leq y \leq m$
// ，表示编号为
// $x$
// 的游览点发放的糖果类型改为

// $y$
// ；

// 若
// $t$
// 为
// $1$
// ，则
// $1 \leq x, y \leq n$
// ，表示对出发点为
// $x$
// ，终止点为

// $y$
// 的路线询问愉悦指数。
// 输出格式

// 按照输入的先后顺序，对于每个
// $t$
// 为
// $1$
// 的操作输出一行，用一个正整数表示答案。
// 欧拉序拆链子
#include <bits/stdc++.h>
#define ll long long
const int maxN = 1E5 + 5;

int h1[maxN], h2[maxN], lca[maxN], f[maxN], pre[maxN], suf[maxN], noe = 0, nt = 0, dfn = 0;
int inv1[maxN << 1], inv2[maxN << 1], tmp[maxN], arr[maxN << 1];
int v[maxN], w[maxN], c[maxN], cnt[maxN];
int pos[maxN], cha[maxN];
bool vis[maxN];
ll res[maxN], tot = 0;

struct Query
{
    int l, r, t;
    bool operator<(const Query& other) const
    {
        return inv1[l] ^ inv1[other.l]? inv1[l] < inv1[other.l]:(inv1[r] ^ inv1[other.r]? inv1[r] < inv1[other.r]:t < other.t);
    }
}queries[maxN];

struct Edge
{
    int to, next;
}e1[maxN << 1], e2[maxN << 1];

inline void add(int from, int to, int* h, Edge* e)
{
    e[noe] = {to, h[from]};
    h[from] = noe++;
}

inline int find(int x)
{
    return x ^ f[x]? (f[x] = find(f[x])):x;
}

inline void dfs(int u, int fa)
{
    f[u] = u;
    pre[u] = ++dfn;
    inv2[dfn] = u;
    vis[u] = 1;
    for(int e = h1[u]; ~e; e = e1[e].next)
    {
        int &to = e1[e].to;
        if(to == fa) continue;
        dfs(to, u);
        f[to] = u;
    }
    for(int e = h2[u]; ~e; e = e2[e].next)
    {
        int &to = e2[e].to;
        if(vis[to]) lca[e >> 1] = find(to);
    }
    suf[u] = ++dfn;
    inv2[dfn] = u;
}

inline void initial(int n, int m)
{
    dfs(1, 0);
    int sz = std::max(1, static_cast<int>(dfn / sqrt(m))), nob = (dfn + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(dfn, i * sz);
        for(int j = st; j <= ed; ++j) inv1[j] = i;
    }
    for(int i = 1; i <= n; ++i) arr[pre[i]] = arr[suf[i]] = c[i];
    for(int i = 0; i < m; ++i)
    {
        int from = e2[i << 1].to, to = e2[i << 1 | 1].to;
        if(pre[from] > pre[to]) std::swap(from, to);
        if(lca[i] != from) queries[i].l = suf[from];
        else queries[i].l = pre[from], lca[i] = 0;
        queries[i].r = pre[to];
    }
    std::iota(tmp, tmp + m, 0);
    std::sort(tmp, tmp + m, [&](const int& a, const int& b){
        return queries[a] < queries[b];
    });
    memset(vis + 1, 0, sizeof(bool) * n);
}

inline void add(int x)
{
    ++cnt[arr[x]];
    tot += 1ll * v[arr[x]] * w[cnt[arr[x]]];
}

inline void del(int x)
{
    tot -= 1ll * v[arr[x]] * w[cnt[arr[x]]];
    --cnt[arr[x]];
}

inline void modify(int x)
{
    if(vis[inv2[x]]) del(x);
    else add(x);
    vis[inv2[x]] ^= 1;
}

inline void modify_time(int t, int l, int r)
{
    if((pre[pos[t]] >= l && pre[pos[t]] <= r) ^ (suf[pos[t]] >= l && suf[pos[t]] <= r))
    {
        ++cnt[cha[t]];
        tot += 1ll * v[cha[t]] * w[cnt[cha[t]]] - 1ll * v[c[pos[t]]] * w[cnt[c[pos[t]]]];
        --cnt[c[pos[t]]];
    }
    arr[pre[pos[t]]] = arr[suf[pos[t]]] = cha[t];
    std::swap(c[pos[t]], cha[t]);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;
    memset(h1 + 1, -1, sizeof(int) * n);
    memset(h2 + 1, -1, sizeof(int) * n);
    for(int i = 1; i <= m; ++i) std::cin >> v[i];
    for(int i = 1; i <= n; ++i) std::cin >> w[i];
    int from, to;
    for(int i = 0; i < n - 1; ++i)
    {
        std::cin >> from >> to;
        add(from, to, h1, e1);
        add(to, from, h1, e1);
    }
    for(int i = 1; i <= n; ++i) std::cin >> c[i];
    noe = 0;
    int t, x, y, p = 0;
    for(int i = 0; i < q; ++i)
    {
        std::cin >> t >> x >> y;
        if(!t)  pos[++nt] = x, cha[nt] = y;
        else
        {
            add(x, y, h2, e2);
            add(y, x, h2, e2);
            queries[p++].t = nt;
        }
    }
    initial(n, p);
    t = 0;
    int l = 1, r = 0;
    for(int i = 0; i < p; ++i)
    {
        int &ql = queries[tmp[i]].l, &qr = queries[tmp[i]].r, &qt = queries[tmp[i]].t;
        while(ql < l) modify(--l);
        while(ql > l) modify(l++);
        while(qr > r) modify(++r);
        while(qr < r) modify(r--);
        while(qt > t) modify_time(++t, l, r);
        while(qt < t) modify_time(t--, l, r);
        res[tmp[i]] = tot + (lca[tmp[i]]? 1ll * v[c[lca[tmp[i]]]] * (w[cnt[c[lca[tmp[i]]]] + 1]):0);
    }
    for(int i = 0; i < p; ++i) std::cout << res[i] << '\n';
    return 0;
}