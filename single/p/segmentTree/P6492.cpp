// # [COCI2010-2011#6] STEP

// ## 题目描述

// 给定一个长度为 $n$ 的字符序列 $a$，初始时序列中全部都是字符 `L`。

// 有 $q$ 次修改，每次给定一个 $x$，若 $a_x$ 为 `L`，则将 $a_x$ 修改成 `R`，否则将 $a_x$ 修改成 `L`。

// 对于一个只含字符 `L`，`R` 的字符串 $s$，若其中不存在连续的 `L` 和 `R`，则称 $s$ 满足要求。

// 每次修改后，请输出当前序列 $a$ 中最长的满足要求的连续子串的长度。

// ## 输入格式

// 第一行有两个整数，分别表示序列的长度 $n$ 和修改操作的次数 $q$。

// 接下来 $q$ 行，每行一个整数，表示本次修改的位置 $x$。

// ## 输出格式

// 对于每次修改操作，输出一行一个整数表示修改 $a$ 中最长的满足要求的子串的长度。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6 2
// 2
// 4
// ```

// ### 样例输出 #1

// ```
// 3
// 5
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 6 5
// 4
// 1
// 1
// 2
// 6
// ```

// ### 样例输出 #2

// ```
// 3
// 3
// 3
// 5
// 6
// ```

// ## 提示

// #### 数据规模与约定

// 对于全部的测试点，保证 $1 \leq n, q \leq 2 \times 10^5$，$1 \leq x \leq n$。

// #### 说明

// **题目译自 [COCI2010-2011](https://hsin.hr/coci/archive/2010_2011/) [CONTEST #6](https://hsin.hr/coci/archive/2010_2011/contest6_tasks.pdf) *T5 STEP***，翻译来自 @[一扶苏一](https://www.luogu.com.cn/user/65363)。
#include <bits/stdc++.h>
const int maxN = 2E5 + 5;

struct seg
{
    bool l, r, inv;
    int mx_len, l_len, r_len;
    seg(bool l = 0, bool r = 0, bool inv = 0, int mx_len = 0, int l_len = 0, int r_len = 0):
        l(l), r(r), inv(inv), mx_len(mx_len), l_len(l_len), r_len(r_len){} 
}tree[maxN << 2];

#define l(x) tree[x].l
#define r(x) tree[x].r
#define inv(x) tree[x].inv
#define mx_len(x) tree[x].mx_len
#define l_len(x) tree[x].l_len
#define r_len(x) tree[x].r_len

inline void pushUp(int x, int s, int t, int m)
{
    l(x) = l(x << 1), r(x) = r(x << 1 | 1);
    mx_len(x) = std::max({mx_len(x << 1), mx_len(x << 1 | 1), r(x << 1) ^ l(x << 1 | 1)? r_len(x << 1) + l_len(x << 1 | 1):0});
    l_len(x) = l_len(x << 1);
    r_len(x) = r_len(x << 1 | 1);
    if(l_len(x << 1) == m - s + 1 && r(x << 1) ^ l(x << 1 | 1))
    {
        l_len(x) += l_len(x << 1 | 1);
    }
    if(r_len(x << 1 | 1) == t - m && r(x << 1) ^ l(x << 1 | 1))
    {
        r_len(x) += r_len(x << 1);
    }
}

inline void pushDown(int x, int s, int t, int m)
{
    if(inv(x))
    {
        l(x << 1) ^= 1, r(x << 1) ^= 1;
        l(x << 1 | 1) ^= 1, r(x << 1 | 1) ^= 1;
        inv(x << 1) ^= 1, inv(x << 1 | 1) ^= 1;
    }
}

inline void buildTree(int s, int t, int p)
{
    mx_len(p) = l_len(p) = r_len(p) = 1;
    if(s == t) return ;
    int m = (t + s) >> 1;
    buildTree(s, m, p << 1);
    buildTree(m + 1, t, p << 1 | 1);
}

inline void updataInv(int l, int r, int s, int t, int p)
{
    if(l <= s && r >= t)
    {
        l(p) ^= 1, r(p) ^= 1, inv(p) ^= 1;
        return ;
    }
    int m = (t + s) >> 1;
    pushDown(p, s, t, m);
    if(l <= m) updataInv(l, r, s, m, p << 1);
    if(r > m) updataInv(l, r, m + 1, t, p << 1 | 1);
    pushUp(p, s, t, m);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q, x;
    std::cin >> n >> q;
    buildTree(1, n, 1);
    for(int i = 0; i < q; ++i)
    {
        std::cin >> x;
        updataInv(x, x, 1, n, 1);
        std::cout << mx_len(1) << '\n';
    }
    return 0;
}