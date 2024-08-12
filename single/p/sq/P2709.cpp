// # 小B的询问

// ## 题目描述

// 小B 有一个长为 $n$ 的整数序列 $a$，值域为 $[1,k]$。  
// 他一共有 $m$ 个询问，每个询问给定一个区间 $[l,r]$，求：  
// $$\sum\limits_{i=1}^k c_i^2$$

// 其中 $c_i$ 表示数字 $i$ 在 $[l,r]$ 中的出现次数。  
// 小B请你帮助他回答询问。

// ## 输入格式

// 第一行三个整数 $n,m,k$。

// 第二行 $n$ 个整数，表示 小B 的序列。

// 接下来的 $m$ 行，每行两个整数 $l,r$。

// ## 输出格式

// 输出 $m$ 行，每行一个整数，对应一个询问的答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6 4 3
// 1 3 2 1 1 3
// 1 4
// 2 6
// 3 5
// 5 6
// ```

// ### 样例输出 #1

// ```
// 6
// 9
// 5
// 2
// ```

// ## 提示

// 【数据范围】   
// 对于 $100\%$ 的数据，$1\le n,m,k \le 5\times 10^4$。
#include <bits/stdc++.h>

const int maxN = 5E4 + 5;

struct Query
{
    int l, r;
    Query(int l = 0, int r = 0): l(l), r(r){}
}queries[maxN];

int arr[maxN], tmp[maxN], rk[maxN], cnt[maxN], inv[maxN];
int res[maxN], qrk[maxN], tot = 0;

class cmp
{
public:
    bool operator()(const int& a, const int& b) const
    {
        return operator()(queries[a], queries[b]);
    }

    bool operator()(const Query& a, const Query& b) const
    {
        return inv[a.l] ^ inv[b.l]? inv[a.l] < inv[b.l]:(inv[a.l] & 1)? a.r < b.r : a.r > b.r;
    }
};

inline void initial(int n, int m)
{
    int sz = n / std::sqrt(m), nob = (n + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(i * sz, n);
        for(int j = st; j <= ed; ++j) inv[j] = i;
    }
    std::iota(qrk, qrk + m, 0);
    std::sort(qrk, qrk + m, cmp());
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int& a, const int& b){return arr[a] < arr[b];});
    int k = 0, now = INT32_MIN;
    for(int i = 1; i <= n; ++i)
    {
        if(now < arr[tmp[i]]) ++k, now = arr[tmp[i]];
        rk[tmp[i]] = k;
    }
}

inline void add(int x)
{
    tot += cnt[rk[x]] << 1 | 1;
    ++cnt[rk[x]];
}

inline void del(int x)
{
    tot -= (cnt[rk[x]] << 1) - 1;
    --cnt[rk[x]];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    for(int i = 0; i < m; ++i) std::cin >> queries[i].l >> queries[i].r;
    initial(n, m);
    int l = 1, r = 0;
    for(int i = 0; i < m; ++i)
    {
        int &ql = queries[qrk[i]].l, &qr = queries[qrk[i]].r;
        while(ql < l) add(--l);
        while(ql > l) del(l++);
        while(qr > r) add(++r);
        while(qr < r) del(r--);
        res[qrk[i]] = tot;
    }
    for(int i = 0; i < m; ++i) std::cout << res[i] << '\n';
    return 0;
}