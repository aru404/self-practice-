// # [POI2012] RAN-Rendezvous

// ## 题目描述

// Byteasar is a ranger who works in the Arrow Cave - a famous rendezvous destination among lovers.

// The cave consists of $n$ chambers connected with one-way corridors.

// In each chamber exactly one outgoing corridor is marked with an arrow.

// Every corridor leads directly to some (not necessarily different) chamber.

// The enamoured couples that agree to meet in the Arrow Cave are notorious for forgetting to agree upon    specific chamber, and consequently often cannot find their dates.

// In the past this led to many mix-ups and misunderstandings\dots    But ever since each chamber is equipped with an emergency telephone line to the ranger on duty,    helping the enamoured find their dates has become the rangers' main occupation.

// The rangers came up with the following method.

// Knowing where the enamoured are, they tell each of them how many times they should follow the corridor marked with an arrow in order to meet their date.

// The lovers obviously want to meet as soon as possible - after all, they came to the cave to spend time together, not to wander around alone!

// Most rangers are happy to oblige: they do their best to give each couple a valid pair of numbers such that their maximum is minimal.

// But some rangers, among their numbers Byteasar, grew tired of this extracurricular activity and ensuing puzzles.  Byteasar has asked you to write a program    that will ease the process.  The program, given a description of the cave and the current location of $k$ couples,    should determine $k$ pairs of numbers $x_i$ and $y_i$ such that if the $i$-th couple follows respectively: he $x_i$ and she $y_i$ corridors marked with arrows,then they will meet in a single chamber of the cave $max(x_i,y_i)$ is minimal,subject to above $min(x_i,y_i)$ is minimal,if above conditions do not determine a unique solution, then the woman should cover smaller distance ($x_i\ge y_i$).

// It may happen that such numbers $x_i$ and $y_i$ do not exist - then let $x_i=y_i=-1$.  Note that it is fine for several couples    to meet in a single chamber.  Once the lovers have found their dates, they will be happy to lose themselves in the cave again...

// 给定一棵内向森林，多次给定两个点a和b，求点对(x,y)满足：


// 1.从a出发走x步和从b出发走y步会到达同一个点


// 2.在1的基础上如果有多解，那么要求max(x,y)最小


// 3.在1和2的基础上如果有多解，那么要求min(x,y)最小


// 4.如果在1、2、3的基础上仍有多解，那么要求x>=y

// ## 输入格式

// In the first line of the standard input there are two positive integers $n$ and $k$($1\le n,k\le 500\ 000$), separated by a single space, that denote   the number of chambers in the Arrow Cave and the number of couples who want to find their dates, respectively.

// The chambers are numbered from 1 to $n$, while the enamoured couples are numbered from 1 to $k$.

// The second line of input contains $n$ positive integers separated by single spaces:

// the $i$-th such integer determines the number of chamber to which the corridor marked with an arrow going out of chamber $i$ leads.

// The following $k$ lines specify the queries by the separated couples. Each such query consists of two positive integers separated by a single space - these denote the numbers of chambers where the lovers are - first him, then her.

// In the tests worth 40% of the total points it additionally holds that $n,k\le 2\ 000$.

// ## 输出格式

// Your program should print exactly $k$ lines to the standard output,   one line per each couple specified in the input:

// the $i$-th line of the output should give the instructions for the $i$-th couple on the input.

// I.e., the $i$-th line of output should contain the integers $x_i,y_i$, separated by a single space.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 12 5
// 4 3 5 5 1 1 12 12 9 9 7 1
// 7 2
// 8 11
// 1 2
// 9 10
// 10 5
// ```

// ### 样例输出 #1

// ```
// 2 3
// 1 2
// 2 2
// 0 1
// -1 -1
// ```

// ## 提示

// 给定一棵内向基环森林，多次给定两个点a和b，求点对(x,y)满足：

// 1.从a出发走x步和从b出发走y步会到达同一个点

// 2.在1的基础上如果有多解，那么要求max(x,y)最小

// 3.在1和2的基础上如果有多解，那么要求min(x,y)最小

// 4.如果在1、2、3的基础上仍有多解，那么要求x>=y
#include <bits/stdc++.h>

const int maxN = 5E5 + 5;

struct edge
{
    int to, next;
}edges[maxN];

int head[maxN], noe = 0;
int dfn[maxN], son[maxN], topf[maxN], fs[maxN], depth[maxN], sz[maxN], cnt1 = 0, banU = 0;
int cir[maxN], stk[maxN], root[maxN], cirId[maxN], cirLen[maxN], invId[maxN], top = 0, cnt2 = 0, r;
int fa[maxN], rk[maxN];
bool inStk[maxN], vis[maxN];

inline int find(int x)
{
    return fa[x] ^ x? (fa[x] = find(fa[x])):x;
}

inline void merger(int x, int y)
{
    x = find(x), y = find(y);
    if(x == y) return;
    if(rk[x] < rk[y]) fa[x] = y;
    else fa[y] = x;
    if(rk[x] == rk[y]) ++rk[x];
} 

inline void add(int u, int v)
{
    edges[++noe].to = v;
    edges[noe].next = head[u];
    head[u] = noe;
    merger(u, v);
}

inline void dfs1(int u, int f)
{
    fs[u] = f;
    depth[u] = depth[f] + 1;
    vis[u] = 1;
    for(int e = head[u]; e; e = edges[e].next)
    {
        int& v = edges[e].to;
        if(v == banU) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) son[u] = v;
    }
    ++sz[u];
}

inline void dfs2(int u, int t)
{
    topf[u] = t;
    dfn[u] = ++cnt1;
    root[u] = r;
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int e = head[u]; e; e = edges[e].next)
    {
        int& v = edges[e].to;
        if(dfn[v] || v == banU) continue;
        dfs2(v, v);
    }
}

inline bool findCir(int u)
{
    if(inStk[u])
    {
        ++cnt2;
        cirLen[cnt2] = cirLen[cnt2 - 1];
        do{
            cir[++cirLen[cnt2]] = stk[top];
            cirId[stk[top]] = cnt2;
        }while(stk[top--] != u);
        return true;
    }
    if(vis[u]) return false;
    stk[++top] = u, vis[u] = inStk[u] = 1;
    for(int e = head[u]; e; e = edges[e].next)
    {
        int& v = edges[e].to;
        if(findCir(v)) return true;
    }
    inStk[u] = 0;
    --top;
    return false;
}

inline void init(int n)
{
    for(int i = 1; i <= n; ++i)
    {
        if(!vis[i])
        {
            top = 0;
            if(findCir(i))
            {
                banU = cir[cirLen[cnt2]];
                r = cir[cirLen[cnt2 - 1] + 1];
                invId[cir[cirLen[cnt2 - 1] + 1]] = 1;
                dfs1(r, 0), dfs2(r, r);
                for(int i = cirLen[cnt2 - 1] + 2; i <= cirLen[cnt2]; ++i)
                {
                    banU = cir[i - 1];
                    r = cir[i];
                    invId[cir[i]] = i - cirLen[cnt2 - 1];
                    dfs1(r, 0), dfs2(r, r);
                }
            }
        }
    }
}

inline int LCA(int u, int v)
{
    while(topf[u] != topf[v])
    {
        if(depth[topf[u]] < depth[topf[v]]) std::swap(u, v);
        u = fs[topf[u]];
    }
    return dfn[u] < dfn[v]? u:v;
}

inline void query(int u, int v)
{
    int x = -1, y = -1;
    if(find(u) == find(v))
    {
        int lca = LCA(u, v);
        if(lca)
        {
            x = depth[u] - depth[lca];
            y = depth[v] - depth[lca];
        }
        else
        {
            x = depth[u] - 1;
            y = depth[v] - 1;
            u = root[u], v = root[v];
            int len = cirLen[cirId[u]] - cirLen[cirId[u] - 1];
            int p1 = invId[u] < invId[v]? invId[v] - invId[u]:len - invId[u] + invId[v];
            int p2 = len - p1;
            if(x + p1 < y + p2) x += p1;
            else if(x + p1 > y + p2) y += p2;
            else
            {
                if(x < y) y += p2;
                else x += p1;
            }
        }
    }
    std::cout << x << ' ' << y << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k, u, v;
    std::cin >> n >> k;
    std::iota(fa, fa + n + 1, 0);
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> u;
        add(u, i);
    }
    init(n);
    for(int i = 0; i < k; ++i)
    {
        std::cin >> u >> v;
        query(u, v);
    }
    return 0;
}