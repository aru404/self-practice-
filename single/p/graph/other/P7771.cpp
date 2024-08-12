// # 【模板】欧拉路径

// ## 题目描述

// 求有向图字典序最小的欧拉路径。

// ## 输入格式

// 第一行两个整数 $n,m$ 表示有向图的点数和边数。

// 接下来 $m$ 行每行两个整数 $u,v$ 表示存在一条 $u\to v$ 的有向边。

// ## 输出格式

// 如果不存在欧拉路径，输出一行 `No`。

// 否则输出一行 $m+1$ 个数字，表示字典序最小的欧拉路径。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 6
// 1 3
// 2 1
// 4 2
// 3 3
// 1 2
// 3 4
// ```

// ### 样例输出 #1

// ```
// 1 2 1 3 3 4 2
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 5 5
// 1 2
// 3 5
// 4 3
// 3 4
// 2 3
// ```

// ### 样例输出 #2

// ```
// 1 2 3 4 3 5
// ```

// ## 样例 #3

// ### 样例输入 #3

// ```
// 4 3
// 1 2
// 1 3
// 1 4
// ```

// ### 样例输出 #3

// ```
// No
// ```

// ## 提示

// 对于 $50\%$ 的数据，$n,m\leq 10^3$。

// 对于 $100\%$ 的数据，$1\leq u,v\leq n\leq 10^5$，$m\leq 2\times 10^5$。

// 保证将有向边视为无向边后图连通。

// [数据生成器](https://www.luogu.com.cn/paste/9oswk47n)

// 要求从某点出发，所有路径都经过一次，回到出发点时为欧拉回路(欧拉图)，不用回出发点为欧拉路径(半欧拉图)
// 显然，对于欧拉回路，每点必出度等于入度（否则会困在某点）
// 对于欧拉路径，要求起点的出度刚好比入度大一，终点的出度比入度小一
// 对于无向图，回路要求所有点度数为偶数
// 路径要求只有起点和终点的度数为奇数
// 欧拉回路如何做：
// 先判断有无欧拉图
// 判断存在欧拉回路/路径后(确定起点和终点，条件是充要的)
// 存在后，开始跑Hierholzer算法
// 实现非常简单(当前弧优化的DFS)
// 由于欧拉回路每点都有出度等于入度，从一个点开始dfs必然能找到环
#include <bits/stdc++.h>

const int maxN = 1E5 + 5, maxM = 2E5 + 5;

std::vector<int> edges[maxN];
int in[maxN], out[maxN], stk[maxM], st = 0, ed = 0, top = 0;

inline bool check(int n)
{
    for(int i = 1; i <= n; ++i)
    {
        if(out[i] - in[i] == 1)
        {
            if(!st) st = i;
            else return false;
        }
        else if(in[i] - out[i] == 1)
        {
            if(!ed) ed = i;
            else return false;
        }
        else if(in[i] != out[i]) return 0;
    }

    if(!st)
    {
        for(int i = 1; i <= n; ++i)
        {
            if(out[i])
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
    while(!edges[u].empty())
    {
        int v = edges[u].back();
        edges[u].pop_back();
        dfs(v);
        stk[++top] = v;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, u, v;
    std::cin >> n >> m;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v;
        edges[u].push_back(v);
        ++in[v], ++out[u];
    }

    if(check(n))
    {
        for(int i = 1; i <= n; ++i)
        {
            std::sort(edges[i].begin(), edges[i].end(), std::greater<int>{});
        }
        dfs(st);
        stk[++top] = st;
        for(int i = top; i; --i) std::cout << stk[i] << ' ';
    }
    else std::cout << "No";
    return 0;
}