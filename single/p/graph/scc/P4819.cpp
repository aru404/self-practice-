// # [中山市选] 杀人游戏

// ## 题目描述

// 一位冷血的杀手潜入Na-wiat，并假装成平民。警察希望能在$N$个人里面，查出谁是杀手。警察能够对每一个人进行查证，假如查证的对象是平民，他会告诉警察，他认识的人，谁是杀手，谁是平民。假如查证的对象是杀手，杀手将会把警察干掉。现在警察掌握了每一个人认识谁。每一个人都有可能是杀手，可看作他们是杀手的概率是相同的。

// 问：根据最优的情况，保证警察自身安全并知道谁是杀手的概率最大是多少？

// ## 输入格式

// 第一行有两个整数 $N,M$。 
// 接下来有 $M$ 行，每行两个整数 $x,y$，表示 $x$ 认识 $y$（$y$ 不一定认识 $x$ ,例如President同志） 。  

// 注：原文zz敏感内容已替换

// ## 输出格式

// 仅包含一行一个实数，保留小数点后面 $6$ 位，表示最大概率。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 4 
// 1 2 
// 1 3 
// 1 4 
// 1 5
// ```

// ### 样例输出 #1

// ```
// 0.800000
// ```

// ## 提示

// 警察只需要查证$1$。假如$1$是杀手，警察就会被杀。假如$1$不是杀手，他会告诉警察$2,3,4,5$谁是杀手。而$1$是杀手的概率是$0.2$，所以能知道谁是杀手但没被杀的概率是$0.8$。

// 对于$100\%$的数据有$1≤N≤100000,0≤M≤300000$。
#include <bits/stdc++.h>

const int maxN = 1E5 + 5, maxM = 3E5 + 5;

int in_degree[maxN];
int dfn[maxN], low[maxN], stk[maxN], inv[maxN], sz[maxN], top = 0, cnt = 0, scc = 0;
bool in_stk[maxN];

std::vector<int> es[maxN], new_es[maxN];

inline void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    stk[++top] = u;
    in_stk[u] = 1;
    for(auto v:es[u])
    {
        if(!dfn[v])
        {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        }
        else if(in_stk[v]) low[u] = std::min(low[u], low[v]);
    }
    if(dfn[u] == low[u])
    {
        ++scc;
        do{
            inv[stk[top]] = scc;
            in_stk[stk[top]] = 0;
            ++sz[scc];
        }while(stk[top--] != u);
    }
}

inline void shrink(int n)
{
    for(int i = 1; i <= n; ++i) if(!dfn[i]) tarjan(i);
    for(int i = 1; i <= n; ++i)
    {
        for(auto v:es[i])
        {
            if(inv[i] != inv[v]) new_es[inv[i]].push_back(inv[v]);
        }
    }

    for(int i = 1; i <= n; ++i)
    {
        std::sort(new_es[i].begin(), new_es[i].end());
        new_es[i].erase(std::unique(new_es[i].begin(), new_es[i].end()), new_es[i].end());
        for(auto v:new_es[i])
        {
            ++in_degree[v];
        }
    }
    int mn_p = 0;
    bool spec = 0;
    for(int i = 1; i <= scc; i++)
    {
        if(!in_degree[i])
        {
            ++mn_p;
            if(!spec && sz[i] == 1)
            {
                spec = 1;
                for(auto v:new_es[i])
                {
                    if(in_degree[v] == 1)
                    {
                        spec = 0;
                        break;
                    }
                }
            }
        }
    }
    std::cout << std::fixed << std::setprecision(6) << 1.0 - (spec? mn_p - 1:mn_p) / (n + 0.0);
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
        es[u].push_back(v);
    }
    shrink(n);
    return 0;
}