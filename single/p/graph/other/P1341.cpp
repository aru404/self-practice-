// # 无序字母对

// ## 题目描述

// 给定 $n$ 个各不相同的无序字母对（区分大小写，无序即字母对中的两个字母可以位置颠倒）。请构造一个有 $(n+1)$ 个字母的字符串使得每个字母对都在这个字符串中出现。

// ## 输入格式

// 第一行输入一个正整数 $n$。

// 第二行到第 $(n+1)$ 行每行两个字母，表示这两个字母需要相邻。

// ## 输出格式

// 输出满足要求的字符串。

// 如果没有满足要求的字符串，请输出 `No Solution`。

// 如果有多种方案，请输出字典序最小的方案（即满足前面的字母的 ASCII 编码尽可能小）。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4
// aZ
// tZ
// Xt
// aX
// ```

// ### 样例输出 #1

// ```
// XaZtX
// ```

// ## 提示

// 不同的无序字母对个数有限，$n$ 的规模可以通过计算得到。
#include <bits/stdc++.h>

const int maxN = 60, maxM = 3E3 + 5;
int degree[maxN], f[maxN], rk[maxN], stk[maxM], top = 0, st = 0, ed = 0;
int head[maxN];
bool edges[maxN][maxN];

inline int find(int x)
{
    return x ^ f[x]? (f[x] = find(f[x])):x;
}

inline void merger(int x, int y)
{
    x = find(x), y = find(y);
    if(x == y) return ;
    if(rk[x] < rk[y]) f[x] = y;
    else f[y] = x;
    if(rk[x] == rk[y]) ++rk[x];
}

inline bool check()
{
    int cnt = 0;
    for(int i = 1; i <= 52; ++i)
    {
        if(!degree[i]) continue;
        if(find(i) == i) ++cnt;
        if(cnt > 1) return false;
    }

    for(int i = 1; i <= 52; ++i)
    {
        if(degree[i] % 2)
        {
            if(!st) st = i;
            else if(!ed) ed = i;
            else return false;
        }
    }

    if(st > ed) std::swap(st, ed);
    if(!st)
    {
        for(int i = 1; i <= 52; ++i)
        {
            if(degree[i])
            {
                st = i;
                break;
            }
        }
    }
    return true;
}

inline void dfs(int u)
{
    while(head[u] <= 52)
    {
        int v = head[u];
        head[u]++;
        if(!edges[u][v]) continue;
        edges[v][u] = edges[u][v] = 0;
        dfs(v);
        stk[++top] = v;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    char u, v;
    std::iota(f, f + 53, 0);
    for(int i = 0; i < n; ++i)
    {
        std::cin >> u >> v;
        int u_id = ::isupper(u)? u - 'A' + 1: u - 'a' + 27;
        int v_id = ::isupper(v)? v - 'A' + 1: v - 'a' + 27;
        merger(u_id, v_id);
        edges[u_id][v_id] = edges[v_id][u_id] = 1;
        ++degree[u_id];
        ++degree[v_id];
    }

    if(check())
    {
        dfs(st);
        stk[++top] = st;
        for(int i = top; i; --i)
        {
            std::cout << static_cast<char>(stk[i] <= 26? stk[i] + 'A' - 1:stk[i] + 'a' - 27);
        }
    }
    else std::cout << "No Solution";
    return 0;
}