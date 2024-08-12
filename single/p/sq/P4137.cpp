// # Rmq Problem / mex

// ## 题目描述

// 有一个长度为 $n$ 的数组 $\{a_1,a_2,\ldots,a_n\}$。

// $m$ 次询问，每次询问一个区间内最小没有出现过的自然数。

// ## 输入格式

// 第一行，两个正整数 $n,m$。  
// 第二行，$n$ 个非负整数 $a_1, a_2, \ldots , a_n$。  
// 接下来 $m$ 行，每行两个正整数 $l,r$，表示一次询问。

// ## 输出格式

// 输出 $m$ 行，每行一个数，依次表示每个询问的答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 5
// 2 1 0 2 1
// 3 3
// 2 3
// 2 4
// 1 2
// 3 5
// ```

// ### 样例输出 #1

// ```
// 1
// 2
// 3
// 0
// 3
// ```

// ## 提示

// 对于 $30\%$ 的数据：$1\leq n,m\leq 1000$。  
// 对于 $100\%$ 的数据：$1\leq n,m\leq 2\times {10}^5$，$1\leq l\leq r\leq n$，$0\leq a_i\leq 2\times 10^5$。
#include <bits/stdc++.h>

const int maxN = 2E5 + 5;

int inv[maxN], arr[maxN], cnt[maxN], sz;
int res[maxN], ans = 0, mex = 0;

struct Query
{
    int l, r, id;
    bool operator<(const Query& other) const
    {
        return inv[l] ^ inv[other.l]? inv[l] < inv[other.l]:r > other.r;
    }
}queries[maxN];

inline void initial(int n, int m)
{
    sz = std::max(1, static_cast<int>(n / sqrt(m)));
    int nob = (n + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(n, i * sz);
        for(int j = st; j <= ed; ++j) inv[j] = i;
    }
    std::sort(queries, queries + m);
    for(int i = 1; i <= n; ++i) ++cnt[arr[i]];
    int mx = 1 + *std::max_element(arr + 1, arr + n + 1);
    for(int i = 0; i <= mx; ++i)
    {
        if(!cnt[i])
        {
            mex = i;
            break;
        }
    }
    ans = mex;
}

inline void del(int x)
{
    --cnt[arr[x]];
    if(!cnt[arr[x]]) ans = std::min(ans, arr[x]);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    for(int i = 0; i < m; ++i) std::cin >> queries[i].l >> queries[i].r, queries[i].id = i;
    initial(n, m);
    int l = 1, r = n, st = 0;
    int tmpV = mex;
    for(int i = 0; i < m; ++i)
    {
        int &ql = queries[i].l, &qr = queries[i].r;
        if(inv[st] != inv[ql])
        {
            ans = mex;
            st = (inv[ql] - 1) * sz + 1;
            for(int j = r + 1; j <= n; ++j) ++cnt[arr[j]];
            for(int j = l; j < st; ++j) del(j);
            mex = ans;
            l = st, r = n;
        }
        while(qr < r) del(r--);
        tmpV = ans;
        for(int j = l; j < ql; ++j) del(j);
        for(int j = l; j < ql; ++j) ++cnt[arr[j]];
        res[queries[i].id] = ans;
        ans = tmpV;
    }
    for(int i = 0; i < m; ++i) std::cout << res[i] << '\n';
    return 0;
}