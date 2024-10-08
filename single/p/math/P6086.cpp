// # 【模板】Prufer 序列

// ## 题目描述

// 请实现 Prüfer 序列和无根树的相互转化。

// 为方便你实现代码，尽管是无根树，我们在读入时仍将 $n$ 设为其根。

// 对于一棵无根树，设 $f_{1\dots n-1}$ 为其**父亲序列**（$f_i$ 表示 $i$ 在 $n$ 为根时的父亲），设 $p_{1 \dots n-2}$ 为其 **Prüfer 序列**。

// 另外，对于一个长度为 $m$ 的序列 $a_{1 \dots m}$，我们设其**权值**为 $\operatorname{xor}_{i = 1}^m i \times a_i$。

// ## 输入格式

// 第一行两个整数 $n,m$，表示树的点数和转化类型。

// 若 $m = 1$，第二行一行 $n-1$ 个整数，表示父亲序列。  
// 若 $m = 2$，第二行一行 $n-2$ 个整数，表示 Prufer 序列。

// ## 输出格式

// 若 $m = 1$，一行一个整数，表示给出的父亲序列对应的 Prüfer 序列的权值。  
// 若 $m = 2$，一行一个整数，表示给出的 Prüfer 序列对应的父亲序列的权值。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6 1
// 3 6 4 6 1
// ```

// ### 样例输出 #1

// ```
// 29
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 6 2
// 4 6 5 2
// ```

// ### 样例输出 #2

// ```
// 4
// ```

// ## 提示

// **【样例 1 解释】**

// $p = \{6\ 1\ 3\ 4\}$。

// **【样例 2 解释】**

// $f = \{4\ 6\ 6\ 5\ 2\}$。

// ---

// **【数据范围】**

// | 测试点编号 | $2 \le n \le $  | $m = $ |
// | :--------: | :-------------: | :----: |
// |    $1$     |     $10^3$      |  $1$   |
// |    $2$     |     $10^5$      |  $1$   |
// |    $3$     |     $10^5$      |  $1$   |
// |    $4$     | $5 \times 10^6$ |  $1$   |
// |    $5$     | $5 \times 10^6$ |  $1$   |
// |    $6$     |     $10^3$      |  $2$   |
// |    $7$     |     $10^5$      |  $2$   |
// |    $8$     |     $10^5$      |  $2$   |
// |    $9$     | $5 \times 10^6$ |  $2$   |
// |    $10$    | $5 \times 10^6$ |  $2$   |
#include <bits/stdc++.h>
typedef long long ll;
const int maxN = 5E6 + 5;

int f[maxN], prufer[maxN];
int d[maxN];

inline void serialization(int n)
{
    for(int i = 1; i <= n - 1; ++i)
    {
        std::cin >> f[i];
        ++d[f[i]];
        ++d[i];
    }
    int top = 0;
    for(int i = 1; i <= n && top <= n - 2; ++i)
    {
        int now = i;
        while(d[now] == 1)
        {
            prufer[++top] = f[now];
            --d[f[now]], --d[now];
            if(i > f[now]) now = f[now];
            else break;
        }
    }
}

inline void antiserialization(int n)
{
    for(int i = 1; i <= n - 2; ++i)
    {
        std::cin >> prufer[i];
        ++d[prufer[i]];
    }
    prufer[n - 1] = n;
    int top = 0;
    for(int i = 1; i <= n && top <= n - 2; ++i)
    {
        int now = i;
        while(!d[now])
        {
            f[now] = prufer[++top];
            --d[f[now]];
            if(f[now] < i) now = f[now];
            else break;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, type;
    ll res = 0;
    std::cin >> n >> type;
    if(type == 1)
    {
        serialization(n);
        for(int i = 1; i <= n - 2; ++i) res ^= 1ll * i * prufer[i];
    }
    else
    {
        antiserialization(n);
        for(int i = 1; i <= n - 1; ++i) res ^= 1ll * i * f[i];
    }
    std::cout << res;
    return 0;
}