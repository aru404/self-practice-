// # 交友问题

// ## 题目背景

// ![](https://cdn.luogu.com.cn/upload/image_hosting/pu73hyh9.png)

// ## 题目描述

// 洛谷上有 $n$ 位用户，这些用户组成了一个双向的网络。

// 洛谷的图片分享机制如下：如果第 $i$ 个用户向他的好友 $j$ 分享了一张照片，那么，$j$ 的所有好友 $k$ 就能看到这张照片。**$j$ 也可以看到这张照片。**

// 现在，用户 $u_i$ 想分享一张照片，但是TA不想让用户 $v_i$ 看到这张照片。在不发送给自己的情况下，TA想知道，他最多可以发送给多少位好友？

// ## 输入格式

// 第一行三个正整数 $n,m,q$，分别代表用户数，边数，询问数。

// 接下来 $m$ 行，每行两个数 $x_i,y_i$，表示用户 $x_i$ 与 $y_i$ 之间有一条双向边。

// 接下来 $q$ 行，每行两个数 $u_i,v_i$，表示第 $i$ 次询问。

// ## 输出格式

// 对于每一次询问，输出一行，包含一个数，答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6 7 8
// 5 1
// 1 4
// 1 6
// 5 6
// 5 4
// 1 2
// 5 3
// 5 3
// 1 1
// 3 6
// 1 5
// 5 6
// 1 4
// 5 2
// 2 6
// ```

// ### 样例输出 #1

// ```
// 3
// 0
// 0
// 1
// 2
// 2
// 3
// 0
// ```

// ## 提示

// 对于 $20\%$ 的数据，满足 $1 \le n,q \le 2\times10^3$，$1\le m \le 8\times 10^3$；

// 对于 $60\%$ 的数据，满足 $1 \le n,q \le 2\times10^4$，$1\le m \le 5\times 10^4$；

// 对于 $100\%$ 的数据，满足 $1 \le n,q \le 2\times10^5$，$1\le m \le 7\times 10^5$。

// **保证没有重边和自环**
#include <bits/stdc++.h>

const int maxN = 2E5 + 5, maxM = 7E5 + 5;

int degree[maxN], res[maxN], rk[maxN];
std::vector<int> es[maxN];
std::vector<std::pair<int, int>> qs[maxN];
int vis[maxN];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, q, m, u, v;
    std::cin >> n >> m >> q;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v;
        es[u].push_back(v);
        es[v].push_back(u);
        ++degree[u];
        ++degree[v];
    }
    for(int i = 0; i < q; ++i)
    {
        std::cin >> u >> v;
        res[i] = degree[u];
        if(degree[u] < degree[v]) std::swap(u, v);
        qs[u].push_back(std::make_pair(v, i));
    }
    for(int i = 1; i <= n; ++i)
    {
        if(qs[i].empty()) continue;
        std::sort(qs[i].begin(), qs[i].end());
        for(auto it:es[i]) vis[it] = i;
        vis[i] = i;
        v = 0;
        int cnt = 0;
        for(int j = 0; j < qs[i].size(); ++j)
        {
            if(v != qs[i][j].first)
            {
                cnt = 0, v = qs[i][j].first;
                for(auto it:es[v]) cnt += vis[it] == i;
            }
            res[qs[i][j].second] -= cnt;
        }
    }
    for(int i = 0; i < q; ++i) std::cout << res[i] << '\n';
    return 0;
}