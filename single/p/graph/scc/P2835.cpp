// # 刻录光盘

// ## 题目描述

// 在JSOI2005夏令营快要结束的时候，很多营员提出来要把整个夏令营期间的资料刻录成一张光盘给大家，以便大家回去后继续学习。组委会觉得这个主意不错！可是组委会一时没有足够的空光盘，没法保证每个人都能拿到刻录上资料的光盘，又来不及去买了，怎么办呢？！

// 组委会把这个难题交给了LHC，LHC分析了一下所有营员的地域关系，发现有些营员是一个城市的，其实他们只需要一张就可以了，因为一个人拿到光盘后，其他人可以带着U盘之类的东西去拷贝啊！

// 可是，LHC调查后发现，由于种种原因，有些营员并不是那么的合作，他们愿意某一些人到他那儿拷贝资料，当然也可能不愿意让另外一些人到他那儿拷贝资料，这与我们JSOI宣扬的团队合作精神格格不入！！！

// 现在假设总共有N个营员（2<=N<=200），每个营员的编号为1~N。LHC给每个人发了一张调查表，让每个营员填上自己愿意让哪些人到他那儿拷贝资料。当然，如果A愿意把资料拷贝给B，而B又愿意把资料拷贝给C，则一旦A获得了资料，则B，C都会获得资料。

// 现在，请你编写一个程序，根据回收上来的调查表，帮助LHC计算出组委会至少要刻录多少张光盘，才能保证所有营员回去后都能得到夏令营资料？

// ## 输入格式

// 先是一个数N，接下来的N行，分别表示各个营员愿意把自己获得的资料拷贝给其他哪些营员。即输入数据的第i+1行表示第i个营员愿意把资料拷贝给那些营员的编号，以一个0结束。如果一个营员不愿意拷贝资料给任何人，则相应的行只有1个0，一行中的若干数之间用一个空格隔开。

// ## 输出格式

// 一个正整数，表示最少要刻录的光盘数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5
// 2 3 4 0
// 4 5 0
// 0
// 0
// 1 0
// ```

// ### 样例输出 #1

// ```
// 1
// ```
#include <bits/stdc++.h>

const int maxN = 205, maxM = 4E4 + 5;

struct edge
{
    int to, next;
}edges[maxM];

int head[maxN], noe = 0;
int dfn[maxN], low[maxN], inv[maxN], in_degree[maxN], cnt = 0, scc = 0;
int stk[maxN], top = 0;
bool in_stk[maxN];

inline void add(int u, int v, int* hs, edge* es)
{
    es[++noe].to = v, es[noe].next = hs[u], hs[u] = noe;
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

inline int countRes(int n)
{
    for(int i = 1; i <= n; ++i)
    {
        if(!dfn[i]) tarjan(i);
    }
    for(int i = 1; i <= n; ++i)
    {
        for(int e = head[i]; e; e = edges[e].next)
        {
            int &v = edges[e].to;
            if(inv[i] != inv[v]) ++in_degree[inv[v]];
        }
    }
    int res = 0;
    for(int i = 1; i <= scc; ++i) res += in_degree[i] == 0;
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, v;
    std::cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        do{
            std::cin >> v;
            if(v) add(i, v, head, edges);
        }while(v);
    }
    std::cout << countRes(n);
    return 0;
}