// # Checkposts

// ## 题面翻译

// ## 题目描述 
// 你的城市有 $n$ 个路口。路口之间有一条单程道路。作为城市的市长，你必须确保所有路口的安全。

// 为了确保安全，你必须建造一些警察检查站。一个检查站只能建在一个路口。 如果有一个检查站在 $i$ 路口，保护 $j$ 的条件是：$i==j$ 或者警察巡逻车可以从 $i$ 走到 $j$，并且能回到 $i$。

// 建造检查站要花一些钱。 由于城市的某些地区比其他地区更昂贵，在某些路口修建检查站可能比其他路口花费更多的钱。

// 你需要找到使所有路口安全的最低花费，以及花费与最低价格相等的方案数。

// 如果其中任何一个路口包含其中一个检查点而不包含在另一个路口中，则两种方式是不同的。

// 方案数模 $10^9+7$。

// ## 输入格式

// 第一行输入一个整数 $n$ 表示路口数。

// 第二行输入 $n$ 个整数 $a_{i}$ 表示每个路口建检查站的花费。

// 第三行输入一个整数 $m$ 表示有向道路的数量。

// 接下来 $m$ 行，每行两个整数 $x,y$，表示一条从 $x$ 到 $y$ 的有向道路。

// ## 输出格式

// 一行用空格分割的两个数，分别表示最小花费和方案数

// ## 提示

// $1 \leq n \leq 10^5,0 \leq m \leq 3 \times 10^5,0 \leq a_{i} \leq 10^9$。

// $1<=u_{i},v_{i}<=n,u≠v$。

// **最小花费不需要取模，方案数需要取模。**

// ## 题目描述

// Your city has $ n $ junctions. There are $ m $ one-way roads between the junctions. As a mayor of the city, you have to ensure the security of all the junctions.

// To ensure the security, you have to build some police checkposts. Checkposts can only be built in a junction. A checkpost at junction $ i $ can protect junction $ j $ if either $ i=j $ or the police patrol car can go to $ j $ from $ i $ and then come back to $ i $ .

// Building checkposts costs some money. As some areas of the city are more expensive than others, building checkpost at some junctions might cost more money than other junctions.

// You have to determine the minimum possible money needed to ensure the security of all the junctions. Also you have to find the number of ways to ensure the security in minimum price and in addition in minimum number of checkposts. Two ways are different if any of the junctions contains a checkpost in one of them and do not contain in the other.

// ## 输入格式

// In the first line, you will be given an integer $ n $ , number of junctions $ (1<=n<=10^{5}) $ . In the next line, $ n $ space-separated integers will be given. The $ i^{th} $ integer is the cost of building checkpost at the $ i^{th} $ junction (costs will be non-negative and will not exceed $ 10^{9} $ ).

// The next line will contain an integer $ m (0<=m<=3·10^{5}) $ . And each of the next $ m $ lines contains two integers $ u_{i} $ and $ v_{i} (1<=u_{i},v_{i}<=n; u≠v) $ . A pair $ u_{i},v_{i} $ means, that there is a one-way road which goes from $ u_{i} $ to $ v_{i} $ . There will not be more than one road between two nodes in the same direction.

// ## 输出格式

// Print two integers separated by spaces. The first one is the minimum possible money needed to ensure the security of all the junctions. And the second one is the number of ways you can ensure the security modulo $ 1000000007 $ $ (10^{9}+7) $ .

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// 1 2 3
// 3
// 1 2
// 2 3
// 3 2
// ```

// ### 样例输出 #1

// ```
// 3 1
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 5
// 2 8 0 6 0
// 6
// 1 4
// 1 3
// 2 4
// 3 4
// 4 5
// 5 1
// ```

// ### 样例输出 #2

// ```
// 8 2
// ```

// ## 样例 #3

// ### 样例输入 #3

// ```
// 10
// 1 3 2 2 1 3 1 4 10 10
// 12
// 1 2
// 2 3
// 3 1
// 3 4
// 4 5
// 5 6
// 5 7
// 6 4
// 7 3
// 8 9
// 9 10
// 10 9
// ```

// ### 样例输出 #3

// ```
// 15 6
// ```

// ## 样例 #4

// ### 样例输入 #4

// ```
// 2
// 7 91
// 2
// 1 2
// 2 1
// ```

// ### 样例输出 #4

// ```
// 7 1
// ```
#include <bits/stdc++.h>

const int maxN = 1E5 + 5, maxM = 3E5 + 5;
const int mod = 1E9 + 7;

struct edge
{
    int to, next;
}edges[maxM];


int head[maxN], w[maxN], noe = 0;
int dfn[maxN], low[maxN], stk[maxN], inv[maxN], top = 0, scc = 0, cnt = 0;
bool in_stk[maxN];

inline void add(int u, int v)
{
    edges[++noe].to = v, edges[noe].next = head[u], head[u] = noe;
}

inline void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    stk[++top] = u;
    in_stk[u] = 1;
    for(int e = head[u]; e; e = edges[e].next)
    {
        int &v = edges[e].to;
        if(!dfn[v])
        {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        }
        else if(in_stk[v]) low[u] = std::min(low[u], dfn[v]);
    }

    if(dfn[u] == low[u])
    {
        ++scc;
        do
        {
            inv[stk[top]] = scc;
            in_stk[stk[top]] = 0;
        }while(stk[top--] != u);
    }
}

inline void cntRes(int n)
{
    for(int i = 1; i <= n; ++i)
    {
        if(!dfn[i]) tarjan(i);
    }

    int* mn = new int[scc + 1]{};
    int* mn_cnt = new int[scc + 1]{};
    memset(mn + 1, 0X3f3f3f3f, sizeof(int) * scc);
    for(int i = 1; i <= n; ++i)
    {
        if(mn[inv[i]] > w[i]) mn[inv[i]] = w[i], mn_cnt[inv[i]] = 1;
        else if(mn[inv[i]] == w[i]) ++mn_cnt[inv[i]];
    }

    long long mn_cost = 0;
    int mn_scheme = 1;
    for(int i = 1; i <= scc; ++i)
    {
        mn_cost += mn[i];
        mn_scheme = 1ll * mn_scheme * mn_cnt[i] % mod; 
    }
    
    std::cout << mn_cost << ' ' << mn_scheme;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, u, v;
    std::cin >> n;
    for(int i = 1; i <= n; ++i) std::cin >> w[i];
    std::cin >> m;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v;
        add(u, v);
    }
    cntRes(n);
    return 0;
}