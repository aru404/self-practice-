// # 鬼子进村

// ## 题目背景

// 小卡正在新家的客厅中看电视。电视里正在播放放了千八百次依旧重播的《亮剑》，剧中李云龙带领的独立团在一个县城遇到了一个鬼子小队，于是独立团与鬼子展开游击战。

// ## 题目描述

// 县城里有 $n$ 个用地道相连的房子，第 $i$ 个只与第 $i-1$ 和第 $i+1$ 个相连。这时有 $m$ 个消息依次传来：

// 1. 若消息为 ```D x```：鬼子将 $x$ 号房子摧毁了，地道被堵上。

// 1. 若消息为 ```R``` ：村民们将鬼子上一个摧毁的房子修复了。

// 2. 若消息为 ```Q x```：有一名士兵被围堵在 $x$ 号房子中。

// 李云龙收到信息很紧张，他想知道每一个被围堵的士兵能够到达的房子有几个。

// ## 输入格式

// 第一行两个整数 $n,m$。

// 接下来 $m$ 行，有如题目所说的三种信息共 $m$ 条。

// ## 输出格式

// 对于每一个被围堵的士兵，输出该士兵能够到达的房子数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 7 9
// D 3
// D 6
// D 5
// Q 4
// Q 5
// R
// Q 4
// R
// Q 4
// ```

// ### 样例输出 #1

// ```
// 1
// 0
// 2
// 4
// ```

// ## 提示

// $1\leq n,m\leq 5\times 10^4$。

// 若士兵被围堵在摧毁了的房子中，那只能等死了。。。。。。
// #include <bits/stdc++.h>

// const int maxN = 5E4 + 5;

// struct node
// {
//     int ls, rs, v, rd, mx, mn;
//     node(int ls = 0, int rs = 0, int v = 0, int rd = 0, int mx = 0, int mn = 0):
//         ls(ls), rs(rs), v(v), rd(rd), mx(mx), mn(mn){}
// };

// #define ls(x) tree[x].ls
// #define rs(x) tree[x].rs
// #define v(x) tree[x].v
// #define rd(x) tree[x].rd
// #define mx(x) tree[x].mx
// #define mn(x) tree[x].mn

// std::mt19937 rnd;
// int r, rx, ry, rz;
// int s1[maxN], s2[maxN], top1 = 0, top2 = 0, cnt = 0;
// node tree[maxN];

// inline int& getNode(int& x, int v)
// {
//     if(top1) x = s1[top1--];
//     else x = ++cnt;
//     v(x) = mx(x) = mn(x) = v;
//     ls(x) = rs(x) = 0;
//     rd(x) = rnd();
//     return x;
// }

// inline void pushUp(int& x)
// {
//     mn(x) = mx(x) = v(x);
//     if(ls(x)) mn(x) = mn(ls(x));
//     if(rs(x)) mx(x) = mx(rs(x));
// }

// inline void split(int v, int r, int& x, int& y)
// {
//     if(!r)
//     {
//         x = y = 0;
//         return ;
//     }
//     if(v(r) <= v)
//     {
//         x = r;
//         split(v, rs(r), rs(x), y);
//     }
//     else
//     {
//         y = r;
//         split(v, ls(r), x, ls(y));
//     }
//     pushUp(r);
// }

// inline int merger(int x, int y)
// {
//     if(!x || !y) return x | y;
//     if(rd(x) < rd(y))
//     {
//         rs(x) = merger(rs(x), y);
//         pushUp(x);
//         return x;
//     }
//     else
//     {
//         ls(y) = merger(x, ls(y));
//         pushUp(y);
//         return y;
//     }
// }

// inline void ins(int v)
// {
//     split(v, r, rx, ry);
//     r = merger(merger(rx, getNode(rz, v)), ry);
// }

// inline void del(int v)
// {
//     split(v, r, rx, ry);
//     split(v - 1, rx, rx, rz);
//     s1[++top1] = rz;
//     r = merger(rx, ry);
// }

// inline int query(int v)
// {
//     split(v, r, rx, ry);
//     int lb = mx(rx), rb = mn(ry);
//     r = merger(rx, ry);
//     return lb == v? 0: rb - lb - 1;
// }

// int main()
// {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     rnd = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());

//     int n, m, w;
//     std::cin >> n >> m;
//     char q;
//     ins(0), ins(n + 1);
//     for(int i = 0; i < m; ++i)
//     {
//         std::cin >> q;
//         if(q == 'D')
//         {
//             std::cin >> w;
//             s2[++top2] = w;
//             ins(w);
//         }
//         else if(q == 'R') del(s2[top2--]);
//         else if(q == 'Q')
//         {
//             std::cin >> w;
//             std::cout << query(w) << '\n';
//         }
//     }
//     return 0;
// }

#include <bits/stdc++.h>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, w;
    char q;
    std::cin >> n >> m;
    std::set<int> tree;
    std::stack<int> s;
    tree.emplace(n + 1);
    tree.emplace(0);
    for(int i = 0; i < m; ++i)
    {
        std::cin >> q;
        if(q == 'R')
        {
            tree.erase(tree.find(s.top()));
            s.pop();
        }
        else
        {
            std::cin >> w;
            if(q == 'Q')
            {
                auto it = tree.upper_bound(w);
                int r = *it, l = *(--it);
                std::cout << (l == w? 0:r - l - 1) << '\n';
            }
            else
            {
                tree.emplace(w);
                s.push(w);
            }
        }
    }
    return 0;
}