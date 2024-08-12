// # [国家集训队] 稳定婚姻

// ## 题目描述

// 我们已知 $n$ 对夫妻的婚姻状况，称第 $i$ 对夫妻的男方为 $B_i$，女方为 $G_i$。若某男 $B_i$ 与某女 $G_j$ 曾经交往过（无论是大学，高中，亦或是幼儿园阶段，$i \le j$），则当某方与其配偶（即 $B_i$ 与 $G_i$ 或 $B_j$ 与 $G_j$）感情出现问题时，他们有私奔的可能性。不妨设 $B_i$ 和其配偶 $G_i$ 感情不和，于是 $B_i$ 和 $G_j$ 旧情复燃，进而 $B_j$ 因被戴绿帽而感到不爽，联系上了他的初恋情人 $G_k$ ……一串串的离婚事件像多米诺骨牌一般接踵而至。若在 $B_i$ 和 $G_i$ 离婚的前提下，这 $2n$ 个人最终依然能够结合成 $n$ 对情侣，那么我们称婚姻 $i$ 为不安全的，否则婚姻 $i$ 就是安全的。

// 给定所需信息，你的任务是判断每对婚姻是否安全。

// ## 输入格式

// 第一行为一个正整数 $n$，表示夫妻的对数；

// 以下 $n$ 行，每行包含两个字符串，表示这 $n$ 对夫妻的姓名（先女后男），由一个空格隔开；

// 第 $n+2$ 行包含一个正整数 $m$，表示曾经相互喜欢过的情侣对数；

// 以下 $m$ 行，每行包含两个字符串，表示这 $m$ 对相互喜欢过的情侣姓名（先女后男），由一个空格隔开。

// ## 输出格式

// 输出文件共包含 $n$ 行，第 $i$ 行为 `Safe`（如果婚姻 $i$ 是安全的）或 `Unsafe`（如果婚姻 $i$ 是不安全的）。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 2
// Melanie Ashley
// Scarlett Charles
// 1
// Scarlett Ashley
// ```

// ### 样例输出 #1

// ```
// Safe
// Safe
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 2
// Melanie Ashley
// Scarlett Charles
// 2
// Scarlett Ashley
// Melanie Charles
// ```

// ### 样例输出 #2

// ```
// Unsafe
// Unsafe
// ```

// ## 提示

// 对于 $20\%$ 的数据，$n \le 20$；

// 对于 $40\%$ 的数据，$n \le 100$，$m \le 400$；

// 对于 $100\%$ 的数据，所有姓名字符串中只包含英文大小写字母，大小写敏感，长度不大于 $8$，保证每对关系只在输入文件中出现一次，输入文件的最后 $m$ 行不会出现未在之前出现过的姓名，这 $2n$ 个人的姓名各不相同，$1 \le n \le 4000$，$0 \le m \le 20000$。
#include <bits/stdc++.h>

const int maxN = 4E3 + 5, maxM = 2E4 + 5;

struct node
{
    bool is_end;
    int id;
    node *next[52];
    node():is_end(0), id(0)
    {
        memset(next, 0, sizeof(next));
    }
};

struct edge
{
    int to, next;
}edges[maxM];

node *root;
int head[maxN], noe = 0;
int stk[maxN], dfn[maxN], low[maxN], inv[maxN], cnt = 0, top = 0, scc = 0;
bool in_stk[maxN], is_scc[maxN];

inline void add(int u, int v)
{
    edges[++noe].to = v, edges[noe].next = head[u], head[u] = noe;
}

inline void ins(std::string& s, int id)
{
    node *r = root;
    for(auto c:s)
    {
        int v = ::isupper(c)? c - 'A':c - 'a' + 26;
        if(r->next[v] == nullptr) r->next[v] = new node();
        r = r->next[v];
    }
    r->id = id;
    r->is_end = 1;
}

inline int getId(std::string& s)
{
    node *r = root;
    for(auto c:s)
    {
        int v = ::isupper(c)? c - 'A':c - 'a' + 26;
        if(r->next[v] == nullptr) r->next[v] = new node();
        r = r->next[v];
    }
    return r->id;
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
        int cnt_sz = 0;
        do{
            ++cnt_sz;
            inv[stk[top]] = scc;
            in_stk[stk[top]] = 0;
        }while(stk[top--] != u);
        is_scc[scc] = cnt_sz > 1;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    root = new node();
    int n, m;
    std::string g, b;
    std::cin >> n;

    for(int i = 1; i <= n; ++i)
    {
        std::cin >> g >> b;
        ins(g, i), ins(b, i);
    }

    std::cin >> m;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> g >> b;
        int u = getId(g), v = getId(b);
        add(v, u);
    }

    for(int i = 1; i <= n; ++i)
    {
        if(!dfn[i]) tarjan(i);
    }
    for(int i = 1; i <= n; ++i)
    {
        if(!is_scc[inv[i]]) std::cout << "Safe\n";
        else std::cout << "Unsafe\n";
    }
    return 0;
}