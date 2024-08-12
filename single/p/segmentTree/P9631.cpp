// # [ICPC2020 Nanjing R] Just Another Game of Stones

// ## 题面翻译

// 给定 $n$ 个石堆，第 $i$ 个石堆的石子数为 $a_i$，有 $q$ 次操作：

// `1 l r x` 表示将所有满足 $l \leq i \leq r$ 的 $a_i$ 赋值为 $\max(a_i,x)$。

// `2 l r x` 表示用石堆 $[l,r]$ 和一个石子数为 $x$ 的石堆进行 Nim 游戏，求出第一次先手取完石子后游戏变为后手必败局面的可操作总方案数。

// （如果你还不了解 Nim 游戏，[点这里](https://oi-wiki.org//math/game-theory/impartial-game/)）。

// 对于 $100\%$ 的数据保证 $1 \le q,n \le 2 \times 10^5$，$0 \le a_i,x_i \le 2^{30}-1$，$op \in \{1,2\}$，$1 \le l_i,r_i \le n$。

// ## 题目描述

// Kotori and Umi are playing games of stones, which is hosted by Honoka. The rule is the same as the classic one: There are some piles of stones and the players take turns to remove any positive number of stones from one pile. The one who can't make a legal move loses the game.

// This time however, things will be a little different. As the host, Honoka will prepare the games from $n$ candidate piles of stones, where the $i$-th pile initially has $a_i$ stones. Honoka will perform $q$ operations of the following two types:

// - Given three integers $l$, $r$ and $x$, for all $l \le i \le r$ change the number of stones in the $i$-th candidate pile to $\max(b_i, x)$, where $b_i$ is the current number of stones in the $i$-th candidate pile.
// - Given three integers $l$, $r$ and $x$, start a game of stones consisting of $(r-l+2)$ piles where the $i$-th pile contains $b_{l-1+i}$ stones for all $1 \le i < (r-l+2)$, and the $(r-l+2)$-th pile contains $x$ stones. Note that this operation is only querying for answer and will not affect the state of the $n$ candidate piles of stones.

// Kotori is always the first to move. As a big fan of Kotori, you would like to know, for each game of stones, the number of ways Kotori can play in the first step to ensure her victory if both players use the best strategy. We consider two ways different if Kotori is taking stones from different piles, or from the same pile but is taking different number of stones.

// ## 输入格式

// There is only one test case in each test file.

// The first line of the input contains two integers $n$ and $q$ ($1 \le n, q \le 2 \times 10^5$) indicating the number of candidate piles and the number of operations.

// The second line contains $n$ integers $a_1, a_2, \cdots, a_n$ ($0 \le a_i \le 2^{30}-1$) where $a_i$ indicates the initial number of stones in the $i$-th pile.

// For the following $q$ lines, the $i$-th line contains four integers $op_i$, $l_i$, $r_i$ and $x_i$ ($op_i \in \{1, 2\}$, $1 \le l_i \le r_i \le n$, $0 \le x_i \le 2^{30}-1$) indicating the $i$-th operation, where $op_i$ is the type of operation and the others are the parameters of the operation. Operations are given in the order they're performed.

// ## 输出格式

// For each operation of the second type output one line containing one integer indicating the answer.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 4
// 1 2 1 4 1
// 2 1 3 1
// 1 2 4 3
// 2 2 4 4
// 2 1 4 4
// ```

// ### 样例输出 #1

// ```
// 1
// 0
// 3
// ```

// ## 提示

// For the first operation the players will play a game of stones consisting of $1$, $2$, $1$ and $1$ stone(s) in each pile respectively. The only winning play for Kotori is reduce the pile with $2$ stones to $1$ stone.

// After the second operation, number of stones in the candidate piles changes to $1$, $3$, $3$, $4$ and $1$ respectively.

// For the fourth operation the players will play a game of stones consisting of $1$, $3$, $3$, $4$ and $4$ stone(s) in each pile respectively. The winning plays for Kotori is to reduce the pile with $1$ stone to $0$ stone, or to reduce any pile with $3$ stones to $2$ stones.
// 取mx和mn是摊还nlgn ^ 2的，没有别的做法
#include <bits/stdc++.h>
#define mn(x) tree[x].mn
#define mnCnt(x) tree[x].mnCnt
#define sec(x) tree[x].sec
#define cnt(x, y) tree[x].cnt[y]
#define sum(x) tree[x].sum
#define lz(x) tree[x].lz

const int maxN = 2E5 + 5;

struct Node
{
    int mn, sec, mnCnt, sum, lz;
    int cnt[30];
}tree[maxN << 2];
int arr[maxN], n;

inline void push_up(int p)
{
    sum(p) = sum(p << 1) ^ sum(p << 1 | 1);
    for(int i = 0; i < 30; ++i) cnt(p, i) = cnt(p << 1, i) + cnt(p << 1 | 1, i);
    if(mn(p << 1) == mn(p << 1 | 1))
    {
        mn(p) = mn(p << 1);
        sec(p) = std::min(sec(p << 1), sec(p << 1 | 1));
        mnCnt(p) = mnCnt(p << 1) + mnCnt(p << 1 | 1);
    }
    else if(mn(p << 1) < mn(p << 1 | 1))
    {
        mn(p) = mn(p << 1);
        sec(p) = std::min(mn(p << 1 | 1), sec(p << 1));
        mnCnt(p) = mnCnt(p << 1);
    }
    else
    {
        mn(p) = mn(p << 1 | 1);
        sec(p) = std::min(mn(p << 1), sec(p << 1 | 1));
        mnCnt(p) = mnCnt(p << 1 | 1);
    }
}

inline void modify(int v, int p)
{
    if(mn(p) >= v) return ;
    sum(p) ^= mnCnt(p) & 1? mn(p) ^ v:0;
    for(int i = 0; i < 30; ++i)
    {
        cnt(p, i) += (((v >> i) & 1) - ((mn(p) >> i) & 1)) * mnCnt(p);
    }
    lz(p) = mn(p) = v;
}

inline void push_down(int p)
{
    if(~lz(p))
    {
        modify(lz(p), p << 1);
        modify(lz(p), p << 1 | 1);
        lz(p) = -1;
    }
}

inline void build_tree()
{
    std::function<void(int, int, int)> build = [&](int s, int t, int p)->void
    {
        lz(p) = -1;
        if(s == t)
        {
            mn(p) = sum(p) = arr[s];
            sec(p) = INT32_MAX;
            mnCnt(p) = 1;
            for(int i = 0; i < 30; ++i)
            {
                cnt(p, i) = (arr[s] >> i) & 1;
                if(!(arr[s] >> i)) break;
            }
            return ;
        }
        int m = (t + s) >> 1;
        build(s, m, p << 1);
        build(m + 1, t, p << 1 | 1);
        push_up(p);
    };
    build(1, n, 1);
}

inline void updata_max(int l, int r, int v)
{
    std::function<void(int, int, int)> updata = [&](int s, int t, int p)->void
    {
        if(mn(p) >= v) return ;
        if(l <= s && r >= t && v < sec(p))
        {
            modify(v, p);
            return ;
        }
        int m = (t + s) >> 1;
        push_down(p);
        if(l <= m) updata(s, m, p << 1);
        if(r > m) updata(m + 1, t, p << 1 | 1);
        push_up(p);
    };
    updata(1, n, 1);
}

inline int query_cnt(int l, int r, int s, int t, int b, int p)
{
    if(l <= s && r >= t) return cnt(p, b);
    int m = (t + s) >> 1;
    push_down(p);
    int res = 0;
    if(l <= m) res += query_cnt(l, r, s, m, b, p << 1);
    if(r > m) res += query_cnt(l, r, m + 1, t, b, p << 1 | 1);
    return res;
};

inline int query_xor(int l, int r, int s, int t, int p)
{
    if(l <= s && r >= t) return sum(p);
    int m = (t + s) >> 1;
    push_down(p);
    int res = 0;
    if(l <= m) res ^= query_xor(l, r, s, m, p << 1);
    if(r > m) res ^= query_xor(l, r, m + 1, t, p << 1 | 1);
    return res;
}

inline int query(int l, int r, int x)
{
    int y = query_xor(l, r, 1, n, 1) ^ x;
    if(!y) return 0;
    int b = 29;
    while(!(y >> b)) --b;
    return query_cnt(l, r, 1, n, b, 1) + ((x >> b) & 1);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int q;
    std::cin >> n >> q;
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }
    build_tree();
    int l, r, v, t;
    for(int i = 0; i < q; ++i)
    {
        std::cin >>t >> l >> r >> v;
        if(t == 1) updata_max(l, r, v);
        else std::cout << query(l, r, v) << '\n';
    }
    return 0;
}