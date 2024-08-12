// # 搭配购买

// ## 题目描述

// 明天就是母亲节了，电脑组的小朋友们在忙碌的课业之余挖空心思想着该送什么礼物来表达自己的心意呢？听说在某个网站上有卖云朵的，小朋友们决定一同前往去看看这种神奇的商品，这个店里有 $n$ 朵云，云朵已经被老板编号为 $1,2,3,...,n$，并且每朵云都有一个价值，但是商店的老板是个很奇怪的人，他会告诉你一些云朵要搭配起来买才卖，也就是说买一朵云则与这朵云有搭配的云都要买，电脑组的你觉得这礼物实在是太新奇了，但是你的钱是有限的，所以你肯定是想用现有的钱买到尽量多价值的云。

// ## 输入格式

// 第一行输入三个整数，$n,m,w$，表示有 $n$ 朵云，$m$ 个搭配和你现有的钱的数目。

// 第二行至 $n+1$ 行，每行有两个整数， $c_i,d_i$，表示第 $i$ 朵云的价钱和价值。

// 第 $n+2$ 至 $n+1+m$ 行 ，每行有两个整数 $u_i,v_i$。表示买第 $u_i$ 朵云就必须买第 $v_i$ 朵云,同理，如果买第 $v_i$ 朵就必须买第 $u_i$ 朵。

// ## 输出格式

// 一行，表示可以获得的最大价值。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 3 10
// 3 10
// 3 10
// 3 10
// 5 100
// 10 1
// 1 3
// 3 2
// 4 2
// ```

// ### 样例输出 #1

// ```
// 1
// ```

// ## 提示

// - 对于 $30\%$ 的数据，满足 $1 \le n \le 100$；
// - 对于 $50\%$ 的数据，满足 $1 \le n, w \le 10^3$，$1 \le m \le 100$；
// - 对于 $100\%$ 的数据，满足 $1 \le n, w \le 10^4$，$0 \le m \le 5 \times 10^3$。
#include <bits/stdc++.h>

const int maxN = 1E4 + 5;

int f[maxN], w[maxN], sz[maxN], rk[maxN];
int dp[maxN];

inline int find(int x)
{
    return f[x] ^ x? (f[x] = find(f[x])):x;
}

inline void merger(int x, int y)
{
    x = find(x), y = find(y);
    if(x == y) return ;
    if(rk[x] < rk[y])
    {
        f[x] = y;
        sz[y] += sz[x];
        w[y] += w[x];
    }
    else
    {
        f[y] = x;
        sz[x] += sz[y];
        w[x] += w[y];
    }

    if(rk[x] == rk[y]) ++rk[x];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, money;
    std::cin >> n >> m >> money;
    int u, v;
    for(int i = 1; i <= n; ++i) std::cin >> sz[i] >> w[i];
    std::iota(f, f + n + 1, 0);
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v;
        merger(u, v);
    }

    int tot = 0;
    for(int i = 1; i <= n; ++i)
    {
        if(find(i) != i) continue;
        tot = std::min(tot + sz[i], money);

        for(int j = tot; j >= sz[i]; --j)
        {
            dp[j] = std::max(dp[j], dp[j - sz[i]] + w[i]);
        }
    }
    std::cout << *std::max_element(dp + 1, dp + money + 1);
    return 0;
}