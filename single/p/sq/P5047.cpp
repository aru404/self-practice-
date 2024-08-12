// # [Ynoi2019 模拟赛] Yuno loves sqrt technology II

// ## 题目描述

// ![](https://cdn.luogu.com.cn/upload/pic/44005.png)

// 给你一个长为 $n$ 的序列 $a$，$m$ 次询问，每次查询一个区间的逆序对数。

// ## 输入格式

// 第一行两个整数 $n,m$。

// 第二行 $n$ 个整数表示这个序列。

// 之后 $m$ 行，每行两个整数表示查询的区间。

// ## 输出格式

// 输出 $m$ 行，每行一个整数表示这次询问的答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 1
// 1 4 2 3
// 2 4
// ```

// ### 样例输出 #1

// ```
// 2
// ```

// ## 提示

// $1\leq n,m \leq 10^5$，$0 \leq a_i \leq 10^9$。

// 我们已经有了低于 $n^{1.5}$ 的算法。

// Source
// By nzhtl1477
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
const int maxN = 1E5 + 5;

int arr[maxN], tmp[maxN], rk[maxN], inv1[maxN], eq[maxN], k;
int cnt[maxN], lz[400], inv2[maxN], noc, szb;
ll res[maxN], pre[maxN];

struct Query
{
    int l, r;
    bool operator<(const Query& other) const
    {
        return inv1[l] ^ inv1[other.l]? inv1[l] < inv1[other.l]:(inv1[l] & 1)? r < other.r:r > other.r;
    }
}queries[maxN];

struct Line
{
    int v, l, r, id, type;
    bool operator<(const Line& other) const
    {
        return v > other.v;
    }
}lines[maxN << 1];

inline void updata(int x, int v)
{
    int ed = std::min(k, inv2[x] * szb);
    for(int i = x; i <= ed; ++i) cnt[i] += v;
    for(int i = inv2[x] + 1; i <= noc; ++i) lz[i] += v;
}

inline int query(int x)
{
    return lz[inv2[x]] + cnt[x];
}

inline void initial(int n, int m)
{
    int sz = std::max(1, static_cast<int>(n / sqrt(m))), nob = (n + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(n, i * sz);
        for(int j = st; j <= ed; ++j) inv1[j] = i;
    }
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int& a, const int& b){
        return arr[a] < arr[b];
    });
    int now = -1;
    for(int i = 1; i <= n; ++i)
    {
        if(now < arr[tmp[i]]) now = arr[tmp[i]], ++k;
        rk[tmp[i]] = k;
    }
    szb = sqrt(n), noc = (k + szb - 1) / szb;
    for(int i = 1; i <= noc; ++i)
    {
        int st = (i - 1) * szb + 1, ed = std::min(i * szb, k);
        for(int j = st; j <= ed; ++j) inv2[j] = i;
    }
    std::iota(tmp, tmp + m + 1, 0);
    std::sort(tmp + 1, tmp + m + 1, [&](const int& a, const int& b){
        return queries[a] < queries[b];
    });

    for(int i = 1; i <= n; ++i)
    {
        eq[i] = query(rk[i]) - query(rk[i] - 1);
        updata(rk[i], 1);
        pre[i] = query(rk[i] - 1);
    }
    memset(lz, 0, sizeof(lz));
    memset(cnt, 0, sizeof(cnt));
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    for(int i = 1; i <= m; ++i) std::cin >> queries[i].l >> queries[i].r;
    initial(n, m);
    int l = 1, r = 0, top = 0;
    for(int i = 1; i <= m; ++i)
    {
        int &ql = queries[tmp[i]].l, &qr = queries[tmp[i]].r;
        if(r < qr && l > 1) lines[++top] = {l - 1, r + 1, qr, tmp[i], 3};
        while(r < qr) ++r, res[tmp[i]] += r - l - pre[r] - eq[r];
        if(r > qr && l > 1) lines[++top] = {l - 1, qr + 1, r, tmp[i], 4};
        while(r > qr) res[tmp[i]] -= r - l - pre[r] - eq[r], --r;
        if(l < ql && r > 0) lines[++top] = {r, l, ql - 1, tmp[i], 1};
        while(l < ql) res[tmp[i]] += pre[l++];
        if(l > ql && r > 0) lines[++top] = {r, ql, l - 1, tmp[i], 2};
        while(l > ql) res[tmp[i]] -= pre[--l];
    }
    std::sort(lines + 1, lines + top + 1);
    for(int i = 1; i <= n; ++i)
    {
        updata(rk[i], 1);
        while(top && lines[top].v == i)
        {
            for(int j = lines[top].l; j <= lines[top].r; ++j)
            {
                if(lines[top].type == 1) res[lines[top].id] -= query(rk[j] - 1);
                else if(lines[top].type == 2) res[lines[top].id] += query(rk[j] - 1);
                else if(lines[top].type == 3) res[lines[top].id] += query(rk[j]);
                else res[lines[top].id] -= query(rk[j]);
            }
            --top;
        }
    }
    for(int i = 1; i <= m; ++i) res[tmp[i]] += res[tmp[i - 1]];
    for(int i = 1; i <= m; ++i) std::cout << res[i] << '\n';
    return 0;
}