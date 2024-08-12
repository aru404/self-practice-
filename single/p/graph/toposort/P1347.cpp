// # 排序

// ## 题目描述

// 一个不同的值的升序排序数列指的是一个从左到右元素依次增大的序列，例如，一个有序的数列 $A,B,C,D$ 表示 $A<B,B<C,C<D$。在这道题中，我们将给你一系列形如 $A<B$ 的关系，并要求你判断是否能够根据这些关系确定这个数列的顺序。

// ## 输入格式

// 第一行有两个正整数 $n,m$，$n$ 表示需要排序的元素数量，$2\leq n\leq 26$，第 $1$ 到 $n$ 个元素将用大写的 $A,B,C,D,\dots$ 表示。$m$ 表示将给出的形如 $A<B$ 的关系的数量。

// 接下来有 $m$ 行，每行有 $3$ 个字符，分别为一个大写字母，一个 `<` 符号，一个大写字母，表示两个元素之间的关系。

// ## 输出格式

// 若根据前 $x$ 个关系即可确定这 $n$ 个元素的顺序 `yyy..y`（如 `ABC`），输出

// `Sorted sequence determined after xxx relations: yyy...y.`

// 若根据前 $x$ 个关系即发现存在矛盾（如 $A<B,B<C,C<A$），输出

// `Inconsistency found after x relations.`

// 若根据这 $m$ 个关系无法确定这 $n$ 个元素的顺序，输出

// `Sorted sequence cannot be determined.`

// （提示：确定 $n$ 个元素的顺序后即可结束程序，可以不用考虑确定顺序之后出现矛盾的情况）

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 6
// A<B
// A<C
// B<C
// C<D
// B<D
// A<B
// ```

// ### 样例输出 #1

// ```
// Sorted sequence determined after 4 relations: ABCD.
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 3 2
// A<B
// B<A
// ```

// ### 样例输出 #2

// ```
// Inconsistency found after 2 relations.
// ```

// ## 样例 #3

// ### 样例输入 #3

// ```
// 26 1
// A<Z
// ```

// ### 样例输出 #3

// ```
// Sorted sequence cannot be determined.
// ```

// ## 提示

// $2 \leq n \leq 26,1 \leq m \leq 600$。
#include <bits/stdc++.h>

const int maxN = 605;
struct edge
{
    int to, next;
}edges[maxN];

int head[26], noe = 0;
int in[26], out[26], stk[30], cntIn = 0, cntOut = 0, top = 0;
int rk[26];
char inv[26];

inline void add(int u, int v)
{
    if(!in[v]) ++cntIn;
    if(!out[u]) ++cntOut;
    ++in[v], ++out[u];
    edges[++noe] = edge{v, head[u]};
    head[u] = noe;
}

inline int topsort(int n)
{
    for(int i = 0; i < n; ++i) if(!in[i]) stk[++top] = i, rk[i] = 0;
    int cnt[26] = {};
    bool f = 0;
    if(top > 1) f = 1;
    int mx = 0, vis = 0;
    while(top)
    {
        int u = stk[top--];
        mx = std::max(mx, rk[u]);
        ++vis;
        for(int e = head[u]; e; e = edges[e].next)
        {
            int &v = edges[e].to;
            ++cnt[v];
            rk[v] = rk[u] + 1;
            if(in[v] == cnt[v]) stk[++top] = v;
        }
    }
    if(vis < n) return 2;
    if(f || mx < n - 1) return 0;
    for(int i = 0; i < n; ++i) inv[rk[i]] = i + 'A';
    return 1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    char u, v, p;
    std::cin >> n >> m;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> p >> v;
        add(u - 'A', v - 'A');
        switch (topsort(n))
        {
        case 1:
        {
            std::cout << "Sorted sequence determined after " << i + 1 << " relations: ";
            for(int j = 0; j < n; ++j) std::cout << inv[j];
            std::cout << '.';
            return 0;
        }
        case 2:
        {
            std::cout << "Inconsistency found after " << i + 1 << " relations.";
            return 0;
        }
        }
    }
    std::cout << "Sorted sequence cannot be determined.";
    return 0;
}