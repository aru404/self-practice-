// # DQUERY - D-query

// ## 题面翻译

// 给出一个长度为n 的数列，$a_{1}$​ ,$a_{2}$​ ,...,$a_{n}$ ，有q 个询问，每个询问给出数对$(i,j)$，需要你给出$a_{i}$​ ，$a_{i+1}$​ ，...，$a_{j}$​ 这一段中有多少不同的数字

// ## 题目描述

// [English](/problems/DQUERY/en/) [Vietnamese](/problems/DQUERY/vn/)Given a sequence of n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ and a number of d-queries. A d-query is a pair (i, j) (1 ≤ i ≤ j ≤ n). For each d-query (i, j), you have to return the number of distinct elements in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ .

// ## 输入格式

// - Line 1: n (1 ≤ n ≤ 30000).
// - Line 2: n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ (1 ≤ a $ _{i} $ ≤ 10 $ ^{6} $ ).
// - Line 3: q (1 ≤ q ≤ 200000), the number of d-queries.
// - In the next q lines, each line contains 2 numbers i, j representing a d-query (1 ≤ i ≤ j ≤ n).

// ## 输出格式

// - For each d-query (i, j), print the number of distinct elements in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ in a single line.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5
// 1 1 2 1 3
// 3
// 1 5
// 2 4
// 3 5
// ```

// ### 样例输出 #1

// ```
// 3
// 2
// 3
// ```
#include <bits/stdc++.h>

const int maxN = 1E5 + 5;
int arr[maxN], rk[maxN], tmp[maxN], cnt[maxN], inv[maxN], k, tot;
int qrk[maxN], res[maxN];

struct Query
{
    int l, r;
    bool operator< (const Query& other) const
    {
        return inv[other.l] ^ inv[l]?  inv[l] < inv[other.l]:(inv[l] & 1)? r < other.r:r > other.r;
    }
}queries[maxN];

inline void initial(int n, int m)
{
    int sz = n / sqrt(m), nob = (n + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(n, i * sz);
        for(int j = st; j <= ed; ++j)
        {
            inv[j] = i;
        }
    }
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int& a, const int& b){
        return arr[a] < arr[b];
    });
    std::iota(qrk, qrk + m, 0);
    std::sort(qrk, qrk + m, [&](const int& a, const int& b){
        return queries[a] < queries[b];
    });
    int now = INT32_MIN;
    k = 0;
    for(int i = 1; i <= n; ++i)
    {
        if(now < arr[tmp[i]]) ++k, now = arr[tmp[i]];
        rk[tmp[i]] = k;
    }
}

inline void add(int x)
{
    if(!cnt[rk[x]]) ++tot;
    ++cnt[rk[x]];
}

inline void del(int x)
{
    --cnt[rk[x]];
    if(!cnt[rk[x]]) --tot;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    for(int i = 0; i < m; ++i) std::cin >> queries[i].l >> queries[i].r;
    initial(n, m);
    int l = 1, r = 0;
    for(int i = 0; i < m; ++i)
    {
        int ql = queries[qrk[i]].l, qr = queries[qrk[i]].r;
        while(l > ql) add(--l);
        while(l < ql) del(l++);
        while(r < qr) add(++r);
        while(r > qr) del(r--);
        res[qrk[i]] = tot;
    }
    for(int i = 0; i < m; ++i) std::cout << (res[i] == queries[i].r - queries[i].l + 1? "Yes":"No") << '\n';
    return 0;
}