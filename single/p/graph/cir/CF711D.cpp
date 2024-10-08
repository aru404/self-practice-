// # Directed Roads

// ## 题面翻译

// 有 n 个点和 n 条边，第 i 条边从 i 连到 ai 。 每条边需要指定一个方向（无向边变为有向边）。问有多少种指定方向 的方案使得图中不出现环

// ## 题目描述

// ZS the Coder and Chris the Baboon has explored Udayland for quite some time. They realize that it consists of $ n $ towns numbered from $ 1 $ to $ n $ .

// There are $ n $ directed roads in the Udayland. $ i $ -th of them goes from town $ i $ to some other town $ a_{i} $ ( $ a_{i}≠i $ ). ZS the Coder can flip the direction of any road in Udayland, i.e. if it goes from town $ A $ to town $ B $ before the flip, it will go from town $ B $ to town $ A $ after.

// ZS the Coder considers the roads in the Udayland confusing, if there is a sequence of distinct towns $ A_{1},A_{2},...,A_{k} $ ( $ k&gt;1 $ ) such that for every $ 1<=i&lt;k $ there is a road from town $ A_{i} $ to town $ A_{i+1} $ and another road from town $ A_{k} $ to town $ A_{1} $ . In other words, the roads are confusing if some of them form a directed cycle of some towns.

// Now ZS the Coder wonders how many sets of roads (there are $ 2^{n} $ variants) in initial configuration can he choose to flip such that after flipping each road in the set exactly once, the resulting network will not be confusing.

// Note that it is allowed that after the flipping there are more than one directed road from some town and possibly some towns with no roads leading out of it, or multiple roads between any pair of cities.

// ## 输入格式

// The first line of the input contains single integer $ n $ ( $ 2<=n<=2·10^{5} $ ) — the number of towns in Udayland.

// The next line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=n,a_{i}≠i) $ , $ a_{i} $ denotes a road going from town $ i $ to town $ a_{i} $ .

// ## 输出格式

// Print a single integer — the number of ways to flip some set of the roads so that the resulting whole set of all roads is not confusing. Since this number may be too large, print the answer modulo $ 10^{9}+7 $ .

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// 2 3 1
// ```

// ### 样例输出 #1

// ```
// 6
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 4
// 2 1 1 1
// ```

// ### 样例输出 #2

// ```
// 8
// ```

// ## 样例 #3

// ### 样例输入 #3

// ```
// 5
// 2 4 2 5 3
// ```

// ### 样例输出 #3

// ```
// 28
// ```

// ## 提示

// Consider the first sample case. There are $ 3 $ towns and $ 3 $ roads. The towns are numbered from $ 1 $ to $ 3 $ and the roads are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/bbf0ca4cbc925b1d673ae3b61e28811a0ccacf51.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/43ec097315a08660c95bbf7f709c76c8ce606dd6.png) initially. Number the roads $ 1 $ to $ 3 $ in this order.

// The sets of roads that ZS the Coder can flip (to make them not confusing) are $ {1},{2},{3},{1,2},{1,3},{2,3} $ . Note that the empty set is invalid because if no roads are flipped, then towns $ 1,2,3 $ is form a directed cycle, so it is confusing. Similarly, flipping all roads is confusing too. Thus, there are a total of $ 6 $ possible sets ZS the Coder can flip.

// The sample image shows all possible ways of orienting the roads from the first sample such that the network is not confusing.

// ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/329f4376794f6e7da8ed8bb533f70d300253c072.png)
#include <bits/stdc++.h>

const int maxN = 2E5 + 5;
const int mod = 1E9 + 7;
struct edge
{
    int to, next;
}edges[maxN << 1];

int head[maxN], noe = 0;
int stk[maxN], top = 0, cnt = 0;
bool inStk[maxN], vis[maxN];

inline void add(int u, int v)
{
    edges[noe].to = v;
    edges[noe].next = head[u];
    head[u] = noe++;
}

inline bool dfs(int u, int pre)
{
    if(inStk[u])
    {
        do{
            ++cnt;
        }while(stk[top--] != u);
        return true;
    }
    if(vis[u]) return false;
    inStk[u] = vis[u] = 1;
    stk[++top] = u;
    for(int e = head[u]; ~e; e = edges[e].next)
    {
        if(e == (pre ^ 1)) continue;
        int &v = edges[e].to;
        if(dfs(v, e))
        {
            inStk[u] = 0;
            return true;
        }
    }
    inStk[u] = 0;
    --top;
    return false;
}

inline int qpow(int a, int p)
{
    int res = 1;
    while(p)
    {
        if(p & 1) res = 1ll * a * res % mod;
        a = 1ll * a * a % mod;
        p >>= 1;
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, v;
    std::cin >> n;
    memset(head + 1, -1, sizeof(int) * n);
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> v;
        add(i, v);
        add(v, i);
    }
    int tot = 0, res = 1;
    for(int i = 1; i <= n; ++i)
    {
        if(!vis[i])
        {
            cnt = 0;
            top = 0;
            if(dfs(i, -1))
            {
                tot += cnt;
                res = 1ll * res * ((qpow(2, cnt) - 2 + mod) % mod) % mod;
            };
        }
    }
    res = 1ll * res * qpow(2, n - tot) % mod;
    std::cout << res;
    return 0;
}