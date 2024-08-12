// # Roads in the Kingdom

// ## 题面翻译

// **题目描述**

// 王国有 $n$ 座城市与 $n$ 条有长度的街道，保证所有城市直接或间接联通，我们定义王国的直径为所有点对最短距离中的最大值，现因财政危机需拆除一条道路并同时要求所有城市仍然联通，求所有拆除方案中王国直径的最小值。

// **输入格式**

// 第一行一个整数 $n$，接下来 $n$ 行每行三个整数 $u,v,w$ 表示城市 $u,v$ 之间有一条长度为 $w$ 的道路。

// **输出格式**

// 一行一个答案，表示所有方案中直径最小值。

// ## 题目描述

// In the Kingdom K., there are $ n $ towns numbered with integers from $ 1 $ to $ n $ . The towns are connected by $ n $ bi-directional roads numbered with integers from $ 1 $ to $ n $ . The $ i $ -th road connects the towns $ u_{i} $ and $ v_{i} $ and its length is $ l_{i} $ . There is no more than one road between two towns. Also, there are no roads that connect the towns with itself.

// Let's call the inconvenience of the roads the maximum of the shortest distances between all pairs of towns.

// Because of lack of money, it was decided to close down one of the roads so that after its removal it is still possible to reach any town from any other. You have to find the minimum possible inconvenience of the roads after closing down one of the roads.

// ## 输入格式

// The first line contains the integer $ n $ ( $ 3<=n<=2·10^{5} $ ) — the number of towns and roads.

// The next $ n $ lines contain the roads description. The $ i $ -th from these lines contains three integers $ u_{i} $ , $ v_{i} $ , $ l_{i} $ ( $ 1<=u_{i},v_{i}<=n $ , $ 1<=l_{i}<=10^{9} $ ) — the numbers of towns connected by the $ i $ -th road and the length of the $ i $ -th road. No road connects a town to itself, no two roads connect the same towns.

// It's guaranteed that it's always possible to close down one of the roads so that all the towns are still reachable from each other.

// ## 输出格式

// Print a single integer — the minimum possible inconvenience of the roads after the refusal from one of the roads.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// 1 2 4
// 2 3 5
// 1 3 1
// ```

// ### 样例输出 #1

// ```
// 5
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 5
// 2 3 7
// 3 1 9
// 4 1 8
// 3 5 4
// 4 5 5
// ```

// ### 样例输出 #2

// ```
// 18
// ```
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
    std::cout << std::max(mx, mn);
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