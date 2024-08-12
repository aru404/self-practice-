// # [JRKSJ R3] system

// ## 题目背景

// 尽管是 35 出题，但是题目背景里面没有琴琴。

// ## 题目描述

// 定义对序列 $a$ 的一次操作为令 $b_i\gets a_{a_i}$，再令 $a_i\gets b_i$，其中 $i\in[1,n]$。

// 给你一个长为 $n$ 的序列 $a$，询问对 $a$ 进行 $k$ 次操作后的序列。

// ## 输入格式

// 第一行两个整数 $n,k$。
// 第二行 $n$ 个整数表示序列 $a$。

// ## 输出格式

// 一行共 $n$ 个整数，表示 $k$ 次操作后的序列 $a$。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 2
// 2 5 4 3 1
// ```

// ### 样例输出 #1

// ```
// 2 5 3 4 1
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 20 233
// 1 1 5 6 8 15 10 11 18 14 4 16 16 11 3 5 1 15 4 5
// ```

// ### 样例输出 #2

// ```
// 1 1 4 5 6 8 4 15 5 6 3 11 11 15 11 4 1 8 3 4
// ```

// ## 提示

// ### 样例解释

// 对于第 $1$ 个样例，$a$ 的变化如下：

// $$5,1,3,4,2$$
// $$2,5,3,4,1$$

// ### 数据规模与约定

// 本题采用捆绑测试。

// | $\text{Subtask}$ | $n\le$ | 特殊性质 | 分值 |
// | :----------: | :----------: | :----------: | :----------: |
// | $1$ | $10^4$ | $\text A$ | $5$ |
// | $2$ | $10^2$ | 无 | $15$ |
// | $3$ | $10^4$ | $\text B$ | $10$ |
// | $4$ | $5\times 10^5$ | $\text B$ | $20$ |
// | $5$ | $5\times 10^5$ | $\text C$ | $20$ |
// | $6$ | $5\times 10^5$ | 无 | $30$ |

// 性质 $\text A$：$0\le k\le 10^3$。
// 性质 $\text B$：$a_i=i\bmod n+1$。
// 性质 $\text C$：$a$ 是一个 $[1,n]$ 的排列。

// 对于 $100\%$ 的数据，$1\le n\le 5\times 10^5$，$0\le k\le 10^9$，$1\le a_i\le n$。
#include <bits/stdc++.h>

const int maxN = 5E5 + 5;

struct edge
{
    int to, next;
}edges[maxN], invEdges[maxN];

int head[maxN], invHead[maxN], noe = 0;
int stk1[maxN], stk2[maxN], stk3[maxN], cir[maxN], top1 = 0, top2 = 0, top3 = 0, cnt = 0, k, f;
int arr[maxN], res[maxN], lg[maxN], leftover[maxN];
bool inStk[maxN], vis[maxN];

inline void add(int u, int v)
{
    edges[++noe].to = v;
    edges[noe].next = head[u];
    head[u] = noe;
    invEdges[noe].to = u;
    invEdges[noe].next = invHead[v];
    invHead[v] = noe;
}

inline bool dfs1(int u)
{
    if(inStk[u])
    {
        do{
            cir[++cnt] = stk1[top1];
        }while(stk1[top1--] != u);
        return true;
    }
    if(vis[u]) return false;
    inStk[u] = vis[u] = 1;
    stk1[++top1] = u;
    for(int e = head[u]; e; e = edges[e].next)
    {
        int& v = edges[e].to;
        if(dfs1(v)) return true;
    }
    inStk[u] = 0;
    --top1;
    return false;
}

inline void dfs2(int u)
{
    stk2[++top2] = u;
    vis[u] = 1;
    if(lg[top2] <= k)
    {
        stk3[++top3] = u;
        leftover[u] = top2 - 1;
    }
    else
    {
        res[u] = stk2[top2 - (1 << k) + 1];
    }
    for(int e = invHead[u]; e; e = invEdges[e].next)
    {
        int& v = invEdges[e].to;
        if(v == f) continue;
        dfs2(v);
    }
    --top2;
}

inline int qpow(int p, int q)
{
    int a = 2, res = 1;
    while(p)
    {
        if(p & 1) res = 1ll * res * a % q;
        a = 1ll * a * a % q;
        p >>= 1;
    }
    return res;
}

inline void solveCir()
{
    cir[cnt + 1] = cir[1];
    int m = (qpow(k, cnt) + cnt - 1) % cnt;
    for(int i = 1; i <= cnt; ++i)
    {
        f = cir[i + 1];
        dfs2(cir[i]);
        int p = (i - m + cnt - 1) % cnt + 1;
        while(top3)
        {
            res[stk3[top3]] = arr[cir[(p + leftover[stk3[top3]] - 1) % cnt + 1]];
            --top3;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n >> k;
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
        add(i, arr[i]);
    }
    for(int i = 2; i <= n; ++i)
    {
        lg[i] = lg[(i + 1) >> 1] + 1;
    }
    for(int i = 1; i <= n; ++i)
    {
        if(!vis[i])
        {
            top1 = cnt = 0;
            dfs1(i);
            solveCir();
        }
    }
    for(int i = 1; i <= n; ++i) std::cout << res[i] << ' ';
    return 0;
}