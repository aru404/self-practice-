// # [NOIP2018 提高组] 旅行

// ## 题目背景

// NOIP2018 提高组 D2T1

// ## 题目描述

// 小 Y 是一个爱好旅行的 OIer。她来到 X 国，打算将各个城市都玩一遍。 
  
// 小 Y 了解到，X 国的 $n$ 个城市之间有 $m$ 条双向道路。每条双向道路连接两个城市。 不存在两条连接同一对城市的道路，也不存在一条连接一个城市和它本身的道路。并且， 从任意一个城市出发，通过这些道路都可以到达任意一个其他城市。小 Y 只能通过这些 道路从一个城市前往另一个城市。   

// 小 Y 的旅行方案是这样的：任意选定一个城市作为起点，然后从起点开始，每次可 以选择一条与当前城市相连的道路，走向一个没有去过的城市，或者沿着第一次访问该 城市时经过的道路后退到上一个城市。当小 Y 回到起点时，她可以选择结束这次旅行或 继续旅行。需要注意的是，小 Y 要求在旅行方案中，每个城市都被访问到。   

// 为了让自己的旅行更有意义，小 Y 决定在每到达一个新的城市（包括起点）时，将 它的编号记录下来。她知道这样会形成一个长度为 $n$ 的序列。她希望这个序列的字典序 最小，你能帮帮她吗？  对于两个长度均为 $n$ 的序列 $A$ 和 $B$，当且仅当存在一个正整数 $x$，满足以下条件时， 我们说序列 $A$ 的字典序小于 $B$。 
  
// - 对于任意正整数 $1 ≤ i < x$，序列 $A$ 的第 $i$ 个元素 $A_i$ 和序列 $B$ 的第 $i$ 个元素 $B_i$ 相同。   
// - 序列 $A$ 的第 $x$ 个元素的值小于序列 $B$ 的第 $x$ 个元素的值。

// ## 输入格式

// 输入文件共 $m + 1$ 行。第一行包含两个整数 $n,m(m ≤ n)$，中间用一个空格分隔。
 
// 接下来 m 行，每行包含两个整数 $u,v (1 ≤ u,v ≤ n)$ ，表示编号为 $u$ 和 $v$ 的城市之 间有一条道路，两个整数之间用一个空格分隔。

// ## 输出格式

// 输出文件包含一行，$n$ 个整数，表示字典序最小的序列。相邻两个整数之间用一个 空格分隔。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6 5 
// 1 3 
// 2 3 
// 2 5 
// 3 4 
// 4 6
// ```

// ### 样例输出 #1

// ```
// 1 3 2 5 4 6
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 6 6 
// 1 3 
// 2 3 
// 2 5 
// 3 4 
// 4 5 
// 4 6
// ```

// ### 样例输出 #2

// ```
// 1 3 2 4 5 6
// ```

// ## 提示

// 【数据规模与约定】   

// 对于 $100\%$ 的数据和所有样例， $1 \le n \le 5000 $ 且 $m = n − 1$ 或 $m = n$ 。

// 对于不同的测试点， 我们约定数据的规模如下：

// ![](https://cdn.luogu.com.cn/upload/pic/43271.png)
#include <bits/stdc++.h>

const int maxN = 5E5 + 5;

std::vector<int> es[maxN];
int stk[maxN], cir[maxN], res[maxN], cnt = 0, top = 0;
bool inStk[maxN];
int banU = 0, banV = 0, in;

inline void add(int u, int v)
{
    es[u].push_back(v);
    es[v].push_back(u);
}

inline bool findCir(int u, int f)
{
    if(inStk[u])
    {
        do{
            cir[++cnt] = stk[top];
        }
        while(stk[top--] != u);
        in = stk[top];
        return true;
    }
    inStk[u] = 1;
    stk[++top] = u;
    for(int& v:es[u])
    {
        if(v == f) continue;
        if(findCir(v, u)) return true;
    }
    inStk[u] = 0;
    --top;
    return false;
}

inline void dfs(int u, int f)
{
    res[++top] = u;
    for(int& v:es[u])
    {
        if((u == banU && v == banV) || (u == banV && v == banU)) continue;
        if(v == f) continue;
        dfs(v, u);
    }
}

inline void getBan()
{
    int l = 1, r = cnt - 1;
    cir[0] = cir[cnt];
    int v = 0, u, pre = in;
    if(cir[l] < cir[r])
    {
        do{
            v = es[cir[l]].back();
            if(v == cir[l - 1]) v = es[cir[l]][es[cir[l]].size() - 2];
            for(auto it = es[cir[l - 1]].begin(); it != es[cir[l - 1]].end(); ++it)
            {
                if(*it <= cir[l] || *it == pre) continue;
                u = *it;
                break;
            }
            pre = cir[l - 1];
            ++l;
        }while((v != cir[l] || cir[l] < u) && l < cnt);
        banU = cir[l], banV = cir[l - 1];
    }
    else
    {
        do{
            v = es[cir[r]].back();
            if(v == cir[r + 1]) v = es[cir[r]][es[cir[r]].size() - 2];
            for(auto it = es[cir[r + 1]].begin(); it != es[cir[r + 1]].end(); ++it)
            {
                if(*it <= cir[r] || *it == pre) continue;
                u = *it;
                break;
            }
            pre = cir[r + 1];
            --r;
        }while((v != cir[r] || cir[r] < u) && r);
        banU = cir[r], banV = cir[r + 1];
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
        add(u, v);
    }
    for(int i = 1; i <= n; ++i)
    {
        std::sort(es[i].begin(), es[i].end());
    }
    if(n == m)
    {
        findCir(1, 0);
        getBan();
    }
    top = 0;
    dfs(1, 0);
    for(int i = 1; i <= n; ++i) std::cout << res[i] << ' ';
    return 0;
}