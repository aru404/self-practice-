// # 瑞瑞的木棍

// ## 题目描述

// 瑞瑞有一堆的玩具木棍，每根木棍的两端分别被染上了某种颜色，现在他突然有了一个想法，想要把这些木棍连在一起拼成一条线，并且使得木棍与木棍相接触的两端颜色都是相同的，给出每根木棍两端的颜色，请问是否存在满足要求的排列方式。

// 例如，如果只有 2 根木棍，第一根两端的颜色分别为 red, blue，第二根两端的颜色分别为 red, yellow，那么 blue---red | red----yellow 便是一种满足要求的排列方式。

// ## 输入格式

// 输入有若干行，每行包括两个单词，表示一根木棍两端的颜色，单词由小写字母组成，且单词长度不会超过 $10$ 个字母，最多有 $250000$ 根木棍。

// ## 输出格式

// 如果木棒能够按要求排列，输出 `Possible`，否则输出 `Impossible`

// ## 样例 #1

// ### 样例输入 #1

// ```
// blue red
// red violet
// cyan blue
// blue magenta
// magenta cyan
// ```

// ### 样例输出 #1

// ```
// Possible
// ```
#include <bits/stdc++.h>

const int maxN = 2.5E5 + 5;

struct node
{
    bool isEnd;
    int id;
    node *son[26];
    node(bool isEnd = 0, int id = 0):isEnd(isEnd), id(id)
    {
        std::fill_n(son, 26, nullptr);
    }
};

std::unordered_map<std::string, int> ps;
int degree[maxN << 1], f[maxN << 1], rk[maxN << 1], from[maxN], to[maxN], cnt = 0;
node* root;

inline int ins(std::string& s)
{
    node* r = root;
    for(auto c:s)
    {
        if(r->son[c - 'a'] == nullptr) r->son[c - 'a'] = new node();
        r = r->son[c - 'a'];
    }
    r->isEnd = 1;
    if(!r->id) r->id = ++cnt;
    return r->id;
}

inline int find(int x)
{
    return x ^ f[x]? (f[x] = find(f[x])):x;
}

inline void merger(int x, int y)
{
    x = find(x), y = find(y);
    if(x == y) return ;
    if(rk[y] > rk[x]) f[x] = y;
    else f[y] = x;
    if(rk[x] == rk[y]) ++rk[x];
}

inline bool check(int n, int m)
{
    std::iota(f, f + n + 1, 0);
    for(int i = 1; i <= m; ++i)
    {
        merger(from[i], to[i]);
    }

    int cnt_union = 0;
    for(int i = 1; i <= m; ++i)
    {
        if(find(i) == i) ++cnt_union;
        if(cnt_union > 1) return false;
    }

    int cnt_odd = 0;
    for(int i = 1; i <= n; ++i)
    {
        cnt_odd += degree[i] % 2;
    }
    return cnt_odd == 2 || cnt_odd == 0;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string u, v;
    root = new node();
    int m = 0;
    while(std::cin >> u >> v)
    {
        ++m;
        from[m] = ins(u), to[m] = ins(v);
        ++degree[from[m]], ++degree[to[m]];
    }
    if(check(cnt, m)) std::cout << "Possible";
    else std::cout << "Impossible";
    return 0;
}