// # Cool loves touli

// ## 题目背景

// Cool 一直都很崇拜 touli。

// ## 题目描述

// 有一天 Cool 和 touli 在打多校，突然开始讨论怎么样的阵容比较厉害。Cool 觉得一个阵容，将他们的等级从低到高排序后，攻击力应该是递增的。Cool 就问 touli 这个阵容最多有几个人。

// 不过 touli 觉得这个问题实在太 SB，就改变了条件，他认为等级从低到高排序后，对于任意两个排序后相邻的英雄，等级低的英雄的攻击力应该不大于等级高的英雄的力量，等级高的英雄的攻击力应当不小于等级低的英雄的智力。

// 现在 Cool 想知道若干个英雄中，最多能选出多少个英雄加入阵容。

// ## 输入格式

// 第一行 $n$ 表示有 $n$ 个英雄。

// 接下来 $n$ 行，每行 $4$ 个整数 $l,s,w,a$，分别表示该英雄的等级、力量、智力、攻击力。

// ## 输出格式

// 一个数,表示最多能选出的英雄个数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// 1 2 3 1
// 2 1 2 2
// 3 1 3 3
// ```

// ### 样例输出 #1

// ```
// 2
// ```

// ## 提示

// 选择第 $1$ 个和第 $3$ 个英雄，符合条件。对于第 $1$ 个和第 $2$ 个英雄，第 $2$ 个英雄的攻击力小于第 $1$ 个英雄的智力，所以不能同时存在。

// $n\leq 10^5$，$l,s,w,a\le10^8$，$l$ 互不相同。
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

const int maxN = 1E5 + 5;

int rk1[maxN], rk2[maxN], tmp1[maxN], tmp2[maxN], mx[maxN], tree[maxN << 1], s1[maxN], s2[maxN], k = 0;

struct People
{
    int l, s, w, a;
}heroes[maxN];

inline void initial(int n)
{
    std::sort(heroes + 1, heroes + n + 1, [&](const People& a, const People& b)
    {
        return a.l < b.l;
    });
    std::iota(tmp1, tmp1 + n + 1, 0);
    std::sort(tmp1 + 1, tmp1 + n + 1, [&](const int& a, const int& b){
        return heroes[a].w < heroes[b].w;
    });
    std::iota(tmp2, tmp2 + n + 1, 0);
    std::sort(tmp2 + 1, tmp2 + n + 1, [&](const int& a, const int& b){
        return heroes[a].a < heroes[b].a;
    });
    memset(heroes, 0X3f3f3f3f, sizeof(People));
    int t = n << 1, idx1 = 1, idx2 = 1, now = 0;
    for(int i = 1; i <= t; ++i)
    {
        if(heroes[tmp1[idx1]].w < heroes[tmp2[idx2]].a)
        {
            if(heroes[tmp1[idx1]].w > now) now = heroes[tmp1[idx1]].w, ++k;
            rk1[tmp1[idx1]] = k;
            ++idx1;
        }
        else
        {
            if(heroes[tmp2[idx2]].a > now) now = heroes[tmp2[idx2]].a, ++k;
            rk2[tmp2[idx2]] = k;
            ++idx2;
        }
    }
}

inline void updata(int x, int v)
{
    while(x <= k && tree[x] < v) tree[x] = std::max(v, tree[x]), x += lowbit(x);
}

inline int query(int x)
{
    int res = 0;
    while(x) res = std::max(res, tree[x]), x -= lowbit(x);
    return res;
}

inline void clear(int x)
{
    while(x <= k && tree[x]) tree[x] = 0, x += lowbit(x);
}

inline void cdq(int l, int r)
{
    if(l == r)
    {
        mx[l] = std::max(mx[l], 1);
        return ;
    }
    int m = (l + r) >> 1;
    cdq(l, m);
    for(int i = l; i <= m; ++i) s1[i - l + 1] = i;
    for(int i = m + 1; i <= r; ++i) s2[i - m] = i;
    std::sort(s1 + 1, s1 + m - l + 2, [&](const int& a, const int& b){
        return heroes[a].a < heroes[b].a;
    });
    std::sort(s2 + 1, s2 + r - m + 1, [&](const int& a, const int& b){
        return heroes[a].s < heroes[b].s;
    });
    s1[m - l + 2] = s2[r - m + 1] = 0;
    int idx1 = 1, idx2 = 1;
    for(int i = l; i <= r; ++i)
    {
        if(heroes[s1[idx1]].a <= heroes[s2[idx2]].s) updata(rk1[s1[idx1]], mx[s1[idx1]]), ++idx1;
        else mx[s2[idx2]] = std::max(mx[s2[idx2]], query(rk2[s2[idx2]]) + 1), ++idx2;
    }
    for(int i = l; i <= m; ++i) clear(rk1[i]);
    cdq(m + 1, r);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    for(int i = 1; i <= n; ++i) std::cin >> heroes[i].l >> heroes[i].s >> heroes[i].w >> heroes[i].a;
    initial(n);
    cdq(1, n);
    std::cout << *std::max_element(mx + 1, mx + n + 1);
    return 0;
}