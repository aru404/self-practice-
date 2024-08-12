// # [NOI2013] 快餐店

// ## 题目描述

// 小 T 打算在城市 C 开设一家外送快餐店。送餐到某一个地点的时间与外卖店到该地点之间最短路径长度是成正比的，小 T 希望快餐店的地址选在离最远的顾客距离最近的地方。

// 快餐店的顾客分布在城市 C 的 $N$ 个建筑中，这 $N$ 个建筑通过恰好 $N$ 条双向道路连接起来，不存在任何两条道路连接了相同的两个建筑。任意两个建筑之间至少存在一条由双向道路连接而成的路径。小 T 的快餐店可以开设在任一建筑中，也可以开设在任意一条道路的某个位置上（该位置与道路两端的建筑的距离不一定是整数）。

// 现给定城市 C 的地图（道路分布及其长度），请找出最佳的快餐店选址，输出其与最远的顾客之间的距离。

// ## 输入格式

// 第一行包含一个整数 $N$，表示城市 C 中的建筑和道路数目。

// 接下来 $N$ 行，每行 $3$ 个整数，$A_i,B_i,L_i$（$1\leq i\leq N$，$L_i>0$），表示一条道路连接了建筑 $A_i$ 与 $B_i$，其长度为 $L_i$。

// ## 输出格式

// 输出仅包含一个实数，四舍五入保留**恰好一位小数**，表示最佳快餐店选址距离最远用户的距离。

// 注意：你的结果必须恰好有一位小数，小数位数不正确不得分。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 
// 1 2 1 
// 1 4 2 
// 1 3 2 
// 2 4 1
// ```

// ### 样例输出 #1

// ```
// 2.0
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 5
// 1 5 100
// 2 1 77
// 3 2 80
// 4 1 64
// 5 3 41
// ```

// ### 样例输出 #2

// ```
// 109.0
// ```

// ## 提示

// ### 样例解释 1

// ![](https://cdn.luogu.com.cn/upload/image_hosting/r0dmxcgy.png)

// ### 样例解释 2

// ![](https://cdn.luogu.com.cn/upload/image_hosting/pf8eaowl.png)

// ### 数据范围

// - 对于 $10\%$ 的数据，$N\leq 80$，$L_i=1$；
// - 对于 $30\%$ 的数据，$N\leq 600$，$L_i\leq 100$；
// - 对于 $60\%$ 的数据，$N\leq 2000$，$L_i\leq 10^9$；
// - 对于 $100\%$ 的数据，$1\leq N\leq 10^5$，$1\leq L_i \leq 10^9$。
#include <bits/stdc++.h>
typedef long long ll;

const int maxN = 2E5 + 5;

struct edge
{
    int to, next;
}edges[maxN << 1];

int head[maxN], w[maxN], noe = 0;
int cir[maxN << 1], stk1[maxN], stk2[maxN], top = 0, cnt = 0, banU, banV;
int f[maxN << 1][2], g[maxN << 1][2];
ll radius[maxN], len[maxN], cirW[maxN << 1];
bool inStk[maxN];

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
            cir[++cnt] = stk1[top];
            cirW[cnt] = stk2[top];
        }while(stk1[top--] != u);
        return true;
    }
    inStk[u] = 1, stk1[++top] = u;
    for(int e = head[u]; ~e; e = edges[e].next)
    {
        if(pre == (e ^ 1)) continue;
        int& v = edges[e].to;
        stk2[top] = w[e >> 1];
        if(dfs1(v, e)) return true;
    }
    inStk[u] = 0;
    --top;
    return false;
}

inline void dfs2(int u, int pre)
{
    ll fir = 0, sec = 0;
    for(int e = head[u]; ~e; e = edges[e].next)
    {
        if(e == (pre ^ 1)) continue;
        int& v = edges[e].to;
        if(v == banU || v == banV) continue;
        dfs2(v, e);
        ll arm = len[v] + w[e >> 1];
        if(arm >= fir)
        {
            std::swap(fir, sec);
            fir = arm;
        }
        else if(arm > sec) sec = arm;
        radius[u] = std::max(radius[u], radius[v]); 
    }
    radius[u] = std::max(radius[u], fir + sec);
    len[u] = fir;
}

inline std::tuple<ll, ll, int> get(int idx, bool type)
{
    ll v1, v2, v3, v4, fir, sec;
    int idx1;
    if(type)
    {
        v1 = cirW[f[idx][0]] + len[cir[f[idx][0]]];
        v2 = cirW[f[idx + cnt - 1][0]] + len[cir[f[idx + cnt - 1][0]]];
        v3 = cirW[f[idx][1]] + len[cir[f[idx][1]]];
        v4 = cirW[f[idx + cnt - 1][1]] + len[cir[f[idx + cnt - 1][1]]];
        if(v1 > v2) fir = v1, sec = v2, idx1 = f[idx][0];
        else fir = v2, sec = v1, idx1 = f[idx + cnt - 1][0];
    }
    else
    {
        v1 = len[cir[g[idx][0]]] - cirW[g[idx][0]];
        v2 = len[cir[g[idx + cnt - 1][0]]] - cirW[g[idx + cnt - 1][0]];
        v3 = len[cir[g[idx][1]]] - cirW[g[idx][1]];
        v4 = len[cir[g[idx + cnt - 1][1]]] - cirW[g[idx + cnt - 1][1]];
        if(v1 > v2) fir = v1, sec = v2, idx1 = g[idx][0];
        else fir = v2, sec = v1, idx1 = g[idx + cnt - 1][0];
    }
    sec = std::max({sec, v3, v4});
    return std::make_tuple(fir, sec, idx1);
}

inline void solveCir()
{
    dfs1(1, -1);
    cir[0] = cir[cnt];
    for(int i = 1; i <= cnt; ++i)
    {
        cir[i + cnt] = cir[i];
        cirW[i + cnt] = cirW[i];
    }
    for(int i = 1; i <= cnt; ++i)
    {
        banU = cir[i - 1], banV = cir[i + 1];
        dfs2(cir[i], -1);
    }
    cirW[1] = 0;
    int m = cnt << 1;
    for(int i = 2; i <= m; ++i) cirW[i] += cirW[i - 1];

    cir[0] = 0, len[0] = INT64_MIN;
    int fir = 0, sec = 0;
    ll fv = INT64_MIN, sv = INT64_MIN;
    for(int i = cnt; i; --i)
    {
        ll v = cirW[i] + len[cir[i]];
        if(fv <= v)
        {
            std::swap(fir, sec);
            std::swap(fv, sv);
            fv = v, fir = i;
        }
        else if(sv < v) sec = i, sv = v;
        f[i][0] = fir, f[i][1] = sec;
    }
    fir = sec = 0, fv = sv = INT64_MIN;
    for(int i = cnt + 1; i <= m; ++i)
    {
        ll v = cirW[i] + len[cir[i]];
        if(fv <= v)
        {
            std::swap(fir, sec);
            std::swap(fv, sv);
            fv = v, fir = i;
        }
        else if(sv < v) sec = i, sv = v;
        f[i][0] = fir, f[i][1] = sec;
    }
    fir = sec = 0, fv = sv = INT64_MIN;
    for(int i = cnt; i; --i)
    {
        ll v = len[cir[i]] - cirW[i];
        if(fv <= v)
        {
            std::swap(fir, sec);
            std::swap(fv, sv);
            fir = i, fv = v;
        }
        else if(sv < v) sec = i, sv = v;
        g[i][0] = fir, g[i][1] = sec;
    }
    fir = sec = 0, fv = sv = INT64_MIN;
    for(int i = cnt + 1; i <= m; ++i)
    {
        ll v = len[cir[i]] - cirW[i];
        if(fv <= v)
        {
            std::swap(fir, sec);
            std::swap(fv, sv);
            fir = i, fv = v;
        }
        else if(sv < v) sec = i, sv = v;
        g[i][0] = fir, g[i][1] = sec;
    }

    ll mx = radius[cir[1]];
    ll mn = f[1][0] ^ g[1][0]? cirW[f[1][0]] - cirW[g[1][0]] + len[cir[f[1][0]]] + len[cir[g[1][0]]]:
    std::max(cirW[f[1][0]] - cirW[g[1][1]] + len[cir[f[1][0]]] + len[cir[g[1][1]]], cirW[f[1][1]] - cirW[g[1][0]] + len[cir[f[1][1]]] + len[cir[g[1][0]]]);

    for(int i = 2; i <= cnt; ++i)
    {
        mx = std::max(mx, radius[cir[i]]);
        auto it1 = get(i, 0), it2 = get(i, 1);
        ll v1, v2, v3, v4;
        int idx1, idx2;
        std::tie(v1, v2, idx1) = it1;
        std::tie(v3, v4, idx2) = it2;
        if(idx1 ^ idx2) mn = std::min(mn, v1 + v3);
        else mn = std::min(mn, std::max(v1 + v4, v2 + v3));
    }
    std::cout << std::fixed << std::setprecision(1) << std::max(mx, mn) / 2.0;
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
        std::cin >> u >> v >> w[i];
        add(u, v);
        add(v, u);
    }
    solveCir();
    return 0;
}