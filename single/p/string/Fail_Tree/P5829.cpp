// # 【模板】失配树

// ## 题目描述

// 给定一个字符串 $s$，定义它的 **$k$ 前缀** $\mathit{pre}_k$ 为字符串 $s_{1\dots k}$，**$k$ 后缀** $\mathit{suf}_k$ 为字符串 $s_{|s|-k+1\dots |s|}$，其中 $1 \le k \le |s|$。

// 定义 $\bold{Border}(s)$ 为**对于 $i \in [1, |s|)$，满足 $\mathit{pre}_i = \mathit{suf}_i$** 的字符串 $\mathit{pre}_i$ 的集合。$\bold{Border}(s)$ 中的每个元素都称之为字符串 $s$ 的 $\operatorname{border}$。

// 有 $m$ 组询问，每组询问给定 $p,q$，求 $s$ 的 **$\boldsymbol{p}$ 前缀** 和 **$\boldsymbol{q}$ 前缀** 的 **最长公共 $\operatorname{border}$**  的长度。

// ## 输入格式

// 第一行一个字符串 $s$。

// 第二行一个整数 $m$。

// 接下来 $m$ 行，每行两个整数 $p,q$。

// ## 输出格式

// 对于每组询问，一行一个整数，表示答案。若不存在公共 $\operatorname{border}$，请输出 $0$。

// ## 样例 #1

// ### 样例输入 #1

// ```
// aaaabbabbaa
// 5
// 2 4
// 7 10
// 3 4
// 1 2
// 4 11
// ```

// ### 样例输出 #1

// ```
// 1
// 1
// 2
// 0
// 2
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// zzaaccaazzccaacczz
// 3
// 2 18
// 10 18
// 3 5
// ```

// ### 样例输出 #2

// ```
// 1
// 2
// 0
// ```

// ## 提示

// 样例 $2$ 说明：

// 对于第一个询问，$2$ 前缀和 $18$ 前缀分别是 ``zz`` 和 ``zzaaccaazzccaacczz``，由于 ``zz`` 只有一个 $\operatorname{border}$，即 ``z``，故最长公共 $\operatorname{border}$ 长度为 $1$。

// ---

// 对于 $16\%$ 的数据，$s$ 中的字符全部相等。

// 对于 $100\%$ 的数据，$1\leq p,q \le |s|\leq 10^6$，$1 \leq m \leq 10^5$，$s_i \in [\texttt{a}, \texttt{z}]$。
#include <bits/stdc++.h>
const int maxN = 1E6 + 5;

struct edge
{
    int to, next;
}edges[maxN], qEdges[maxN];

int kmp[maxN], head[maxN], qHead[maxN], res[maxN], f[maxN], noe = 0;
char s[maxN];
bool vis[maxN];

inline void add(int u, int v, edge* es, int* hs)
{
    es[++noe].to = v;
    es[noe].next = hs[u];
    hs[u] = noe;
}

inline int find(int x)
{
    return f[x] ^ x? (f[x] = find(f[x])):x;
}

inline void KMP(int n)
{
    kmp[1] = 0;
    add(0, 1, edges, head);
    for(int i = 2; i <= n; ++i)
    {
        int k = kmp[i - 1];
        while(k && s[k + 1] != s[i]) k = kmp[k];
        kmp[i] = k + (s[k + 1] == s[i]);
        add(kmp[i], i, edges, head);
    }
}

inline void dfs(int now, int fa)
{
    vis[now] = 1;
    f[now] = now;
    for(int e = head[now]; e; e = edges[e].next)
    {
        int &to = edges[e].to;
        dfs(to, now);
    }

    for(int e = qHead[now]; e; e = qEdges[e].next)
    {
        int &to = qEdges[e].to;
        if(vis[to]) res[(e + 1) >> 1] = find(to);
    }
    f[now] = fa; 
}

int main()
{
    scanf("%s", s + 1);
    int n;
    scanf("%d", &n);
    int m = strlen(s + 1);
    KMP(m);
    int u, v;
    noe = 0;
    for(int i = 0; i < n; ++i)
    {
        scanf("%d %d", &u, &v);
        u = kmp[u], v = kmp[v];
        add(u, v, qEdges, qHead);
        add(v, u, qEdges, qHead);
    }
    dfs(0, -1);
    for(int i = 1; i <= n; ++i)
    {
        std::cout << res[i] << '\n';
    }
    return 0;
}