// # 【模板】莫队二次离线（第十四分块(前体)）

// ## 题目描述

// 珂朵莉给了你一个序列 $a$，每次查询给一个区间 $[l,r]$，查询 $l \leq i< j \leq r$，且 $a_i \oplus a_j$ 的二进制表示下有 $k$ 个 $1$ 的二元组 $(i,j)$ 的个数。$\oplus$ 是指按位异或。

// ## 输入格式

// 第一行三个数表示 $n,m,k$。

// 第二行 $n$ 个数表示序列 $a$。

// 之后 $m$ 行，每行两个数 $l,r$ 表示一次查询。

// ## 输出格式

// 输出 $m$ 行，每行一个数表示查询的结果。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 5 2
// 3 4 8 0 2
// 4 5
// 3 5
// 1 4
// 2 5
// 1 5
// ```

// ### 样例输出 #1

// ```
// 0
// 1
// 2
// 3
// 4
// ```

// ## 提示

// 对于5%的数据，为样例。

// 对于30%的数据，$1 \leq n , m \leq 5000$。

// 对于50%的数据，空间限制为 512 MiB。

// 对于100%的数据，$1 \leq n, m \leq 100000$，$0 \leq a_i, k < 16384$。
// 毒瘤问题
#include <bits/stdc++.h>
#define ll long long

const int maxN = 1E5 + 5, maxV = 1 << 14;

int arr[maxN], inv[maxN], tmp[maxN], cnt[maxV + 10], pre[maxN];
int var[maxN], tot1 = 0, tot2 = 0;
ll res[maxN];

struct Query
{
    int l, r;
    bool operator<(const Query& other) const
    {
        return inv[l] ^ inv[other.l]? inv[l] < inv[other.l]:(inv[l] & 1)? r < other.r:r > other.r; 
    }
}queries[maxN];

struct Line
{
    int v, l, r, id;
    bool operator<(const Line& other) const
    {
        return v < other.v;
    }
}lines[maxN << 1];

inline void initial(int n, int m, int k)
{
    for(int i = 0; i < maxV; ++i) if(__builtin_popcount(i) == k) var[++tot1] = i;
    
    int sz = std::max(1, static_cast<int>(n / sqrt(m))), nob = (n + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(n, i * sz);
        for(int j = st; j <= ed; ++j) inv[j] = i;
    }
    std::iota(tmp, tmp + m + 1, 0);
    std::sort(tmp + 1, tmp + m + 1, [&](const int& a, const int& b){
        return queries[a] < queries[b];
    });

    for(int i = 1; i <= n; ++i)
    {
        pre[i] = cnt[arr[i]];
        for(int j = 1; j <= tot1; ++j) ++cnt[arr[i] ^ var[j]];
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;
    if(k > 14)
    {
        for(int i = 0; i < m; ++i) std::cout << 0 << '\n';
        return 0;
    }
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    for(int i = 1; i <= m; ++i) std::cin >> queries[i].l >> queries[i].r;
    initial(n, m, k);
    int l = 1, r = 0;
    for(int i = 1; i <= m; ++i)
    {
        int &ql = queries[tmp[i]].l, &qr = queries[tmp[i]].r;
        if(ql < l && r > 0) lines[++tot2] = {r, ql, l - 1, tmp[i]};
        while(ql < l) res[tmp[i]] -= pre[--l];
        if(ql > l && r > 0) lines[++tot2] = {r, l, ql - 1, -tmp[i]};
        while(ql > l) res[tmp[i]] += pre[l++];
        if(qr > r && l > 1) lines[++tot2] = {l - 1, r + 1, qr, -tmp[i]};
        while(qr > r) res[tmp[i]] += pre[++r];
        if(qr < r && l > 1) lines[++tot2] = {l - 1, qr + 1, r, tmp[i]};
        while(qr < r) res[tmp[i]] -= pre[r--];
    }
    std::sort(lines + 1, lines + tot2 + 1);
    memset(cnt, 0, sizeof(cnt));
    int idx = 1;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= tot1; ++j) ++cnt[arr[i] ^ var[j]];
        while(lines[idx].v == i && idx <= tot2)
        {
            for(int j = lines[idx].l; j <= lines[idx].r; ++j)
            {
                if(lines[idx].id > 0)
                {
                    if(!k && j <= i) res[lines[idx].id] += cnt[arr[j]] - 1;
                    else res[lines[idx].id] += cnt[arr[j]];
                }
                else
                {
                    if(!k && j <= i) res[-lines[idx].id] -= cnt[arr[j]] - 1;
                    else res[-lines[idx].id] -= cnt[arr[j]];
                }
            }
            ++idx;
        }
    }
    for(int i = 1; i <= m; ++i) res[tmp[i]] += res[tmp[i - 1]];
    for(int i = 1; i <= m; ++i) std::cout << res[i] << '\n';
    return 0;
}