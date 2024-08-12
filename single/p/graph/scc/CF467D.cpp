// # Fedor and Essay

// ## 题面翻译

// 在你帮助 Fedor 在 *Call of Soldiers 3* 这款游戏中找到朋友之后，他完全停止了学习。今天，英语老师让他准备一篇文章。Fedor 并不想准备这篇文章，所以他向 Alex 寻求帮助。Alex 帮忙为 Fedor 写了一篇文章。但 Fedor 根本不喜欢这篇文章。现在 Fedor 将使用英语同义词词典来重写文章。

// Fedor 不想改变文章的含义。因此，他将做的唯一改变是：根据字典中的替换规则，将一个论文中的单词改为它的一个同义词。Fedor 可以多次执行此操作。

// Fedor 希望得到一篇文章，其中包含尽可能少的字母 `R`（大写或者小写均可）。如果有多篇文章都有最少的 `R`，那么他希望文章的长度尽可能小（文章的长度是其中所有单词长度的总和）。帮助 Fedor 求出目标文章。

// 请注意，在这个问题中，字母的大小写情况无关紧要。例如，如果同义词词典说单词 `cat` 可以用单词 `DOG` 替换，则允许用单词 `doG` 替换单词 `Cat`。

// ## 题目描述

// After you had helped Fedor to find friends in the «Call of Soldiers 3» game, he stopped studying completely. Today, the English teacher told him to prepare an essay. Fedor didn't want to prepare the essay, so he asked Alex for help. Alex came to help and wrote the essay for Fedor. But Fedor didn't like the essay at all. Now Fedor is going to change the essay using the synonym dictionary of the English language.

// Fedor does not want to change the meaning of the essay. So the only change he would do: change a word from essay to one of its synonyms, basing on a replacement rule from the dictionary. Fedor may perform this operation any number of times.

// As a result, Fedor wants to get an essay which contains as little letters «R» (the case doesn't matter) as possible. If there are multiple essays with minimum number of «R»s he wants to get the one with minimum length (length of essay is the sum of the lengths of all the words in it). Help Fedor get the required essay.

// Please note that in this problem the case of letters doesn't matter. For example, if the synonym dictionary says that word cat can be replaced with word DOG, then it is allowed to replace the word Cat with the word doG.

// ## 输入格式

// The first line contains a single integer $ m $ $ (1<=m<=10^{5}) $ — the number of words in the initial essay. The second line contains words of the essay. The words are separated by a single space. It is guaranteed that the total length of the words won't exceed $ 10^{5} $ characters.

// The next line contains a single integer $ n $ $ (0<=n<=10^{5}) $ — the number of pairs of words in synonym dictionary. The $ i $ -th of the next $ n $ lines contains two space-separated non-empty words $ x_{i} $ and $ y_{i} $ . They mean that word $ x_{i} $ can be replaced with word $ y_{i} $ (but not vise versa). It is guaranteed that the total length of all pairs of synonyms doesn't exceed $ 5·10^{5} $ characters.

// All the words at input can only consist of uppercase and lowercase letters of the English alphabet.

// ## 输出格式

// Print two integers — the minimum number of letters «R» in an optimal essay and the minimum length of an optimal essay.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// AbRb r Zz
// 4
// xR abRb
// aA xr
// zz Z
// xr y
// ```

// ### 样例输出 #1

// ```
// 2 6
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 2
// RuruRu fedya
// 1
// ruruRU fedor
// ```

// ### 样例输出 #2

// ```
// 1 10
// ```
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

const int maxN = 1E5 + 5;

struct edge
{
    int to, next;
}edges[maxN], new_edges[maxN];

struct node
{
    int id;
    bool isEnd;
    node* next[26];
    node(int id = 0, bool isEnd = false):id(id), isEnd(isEnd)
    {
        memset(next, 0, sizeof(next));
    }
};

int head[maxN], new_head[maxN];
int dfn[maxN], low[maxN], stk[maxN], in_degree[maxN], inv[maxN], len[maxN], cnt_r[maxN], mn_r[maxN], mn_len[maxN], init_id[maxN], top = 0, cnt = 0, noe = 0, scc = 0, id = 0;
bool in_stk[maxN];
node *root;

inline int ins(std::string& s)
{
    node *r = root;
    int tot_r = 0;
    for(auto c:s)
    {
        c = tolower(c);
        tot_r += c == 'r';
        if(r->next[c - 'a'] == nullptr)
        {
            r->next[c - 'a'] = new node();
        }
        r = r->next[c - 'a'];
    }
    if(!(r->isEnd))
    {
        r->isEnd = 1;
        r->id = ++id;
        len[id] = s.size();
        cnt_r[id] = tot_r;
    }
    return r->id;
}

inline void add(int u, int v, int *hs, edge *es)
{
    es[++noe].to = v, es[noe].next = hs[u], hs[u] = noe;
}

inline void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    in_stk[u] = 1;
    stk[++top] = u;
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
        mn_len[scc] = mn_r[scc] = INF;
        do{
            inv[stk[top]] = scc;
            in_stk[stk[top]] = 0;
            if(cnt_r[stk[top]] < mn_r[scc])
            {
                mn_r[scc] = cnt_r[stk[top]];
                mn_len[scc] = len[stk[top]];
            }
            else if(cnt_r[stk[top]] == mn_r[scc])
            {
                mn_len[scc] = std::min(mn_len[scc], len[stk[top]]);
            }
        }while(stk[top--] != u);
    }
}

inline void toposort()
{
    std::queue<int> q;
    for(int i = 1; i <= scc; ++i)
    {
        if(!in_degree[i]) q.push(i);
    }
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int e = new_head[u]; e; e = new_edges[e].next)
        {
            int &v = new_edges[e].to;
            --in_degree[v];
            if(mn_r[u] < mn_r[v])
            {
                mn_r[v] = mn_r[u];
                mn_len[v] = mn_len[u];
            }
            else if(mn_r[u] == mn_r[v])
            {
                mn_len[v] = std::min(mn_len[u], mn_len[v]);
            }
            if(!in_degree[v]) q.push(v);
        }
    }
}

inline void shrink(int n, int m)
{
    for(int i = 1; i <= n; ++i)
    {
        if(!dfn[i]) tarjan(i);
    }
    noe = 0;
    for(int i = 1; i <= n; ++i)
    {
        for(int e = head[i]; e; e = edges[e].next)
        {
            int &v = edges[e].to;
            if(inv[i] != inv[v])
            {
                add(inv[i], inv[v], new_head, new_edges);
                ++in_degree[inv[v]];
            }
        }
    }
    toposort();
    long long mn_sz = 0;
    int mn_tot_r = 0;
    for(int i = 1; i <= m; ++i)
    {
        mn_sz += mn_len[inv[init_id[i]]];
        mn_tot_r += mn_r[inv[init_id[i]]];
    }
    std::cout << mn_tot_r << ' ' << mn_sz;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::string u, v;
    std::cin >> n;
    root = new node();
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> u;
        init_id[i] = ins(u);
    }

    std::cin >> m;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v;
        int u_id = ins(u), v_id = ins(v);
        add(v_id, u_id, head, edges);
    }
    shrink(id, n);
    return 0;
}