// # 【模板】回滚莫队&不删除莫队

// ## 题目背景

// 这是一道模板题。

// ## 题目描述

// 给定一个序列，多次询问一段区间 $[l,r]$，求区间中**相同的数的最远间隔距离**。

// 序列中两个元素的**间隔距离**指的是**两个元素下标差的绝对值**。

// ## 输入格式

// 第一行一个整数 $n$，表示序列长度。

// 第二行 $n$ 个整数，描述这个序列。

// 第三行一个整数 $m$，表示询问个数。

// 之后 $m$ 行，每行两个整数 $l,r$ 表示询问区间。

// ## 输出格式

// 共 $m$ 行，每行一个整数表示答案。如果区间内不存在两个数相同，则输出 $0$。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 8
// 1 6 2 2 3 3 1 6
// 5
// 1 4
// 2 5
// 2 8
// 5 6
// 1 7
// ```

// ### 样例输出 #1

// ```
// 1
// 1
// 6
// 1
// 6
// ```

// ## 提示

// 记 $a_i$ 表示序列元素。

// 对于 $40\%$ 的数据，满足 $1\leq a_i \leq 400$，$1\leq n,m\leq 60000$。

// 对于 $100\%$ 的数据，满足 $1\leq n,m\leq 2\cdot 10^5$，$1\leq a_i\leq 2\cdot 10^9$。
#include <bits/stdc++.h>

const int maxN = 2E5 + 5;
int arr[maxN], tmp[maxN], rk[maxN];
int inv1[maxN], inv2[maxN], res[maxN], sz;
int pre[maxN], suf[maxN], idx[maxN], ans;

struct Query
{
    int l, r;
    bool operator<(const Query& other) const
    {
        return inv1[l] ^ inv1[other.l]? inv1[l] < inv1[other.l]:r < other.r;
    }
}queries[maxN];

inline void initial(int n, int m)
{
    std::iota(idx, idx + n + 1, 0);
    std::sort(idx + 1, idx + n + 1, [&](const int& a, const int& b){
       return arr[a] ^ arr[b]? arr[a] < arr[b]:a < b;
    });
    int now = INT32_MIN, k = 0;
    for(int i = 1; i <= n; ++i)
    {
        if(arr[idx[i]] > now) ++k, now = arr[idx[i]];
        rk[idx[i]] = k;
        inv2[idx[i]] = i;
    }
    memset(pre + 1, 0X3f3f3f3f, sizeof(int) * k);
    sz = std::max(1, static_cast<int>(n / sqrt(m)));
    int nob = (n + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(n, i * sz);
        for(int j = st; j <= ed; ++j) inv1[j] = i;
    }
    std::iota(tmp, tmp + m, 0);
    std::sort(tmp, tmp + m, [&](const int& a, const int& b){
        return queries[a] < queries[b];
    });
}

inline void pop_back(int x)
{
    --suf[rk[x]];
}

inline void pop_front(int x)
{
    ++pre[rk[x]];
}

inline void push_back(int x)
{
    if(pre[rk[x]] > suf[rk[x]]) pre[rk[x]] = suf[rk[x]] = inv2[x];
    else ++suf[rk[x]];
    ans = std::max(ans, idx[suf[rk[x]]] - idx[pre[rk[x]]]);
}

inline void push_front(int x)
{
    if(pre[rk[x]] > suf[rk[x]]) pre[rk[x]] = suf[rk[x]] = inv2[x];
    else --pre[rk[x]];
    ans = std::max(ans, idx[suf[rk[x]]] - idx[pre[rk[x]]]);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n;
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    std::cin >> m;
    for(int i = 0; i < m; ++i) std::cin >> queries[i].l >> queries[i].r;
    initial(n, m);
    int l = 1, r = 0, ed = 0;
    int tmpV = 0;
    for(int i = 0; i < m; ++i)
    {
        int &ql = queries[tmp[i]].l, &qr = queries[tmp[i]].r;
        if(inv1[ed] != inv1[ql])
        {
            for(int j = l; j <= r; ++j) pop_front(j);
            ans = tmpV = 0;
            ed = std::min(n, inv1[ql] * sz);
            l = ed + 1, r = ed;
        }
        if(inv1[ql] == inv1[qr])
        {
            for(int j = ql; j <= qr; ++j) push_back(j);
            res[tmp[i]] = ans;
            for(int j = qr; j >= ql; --j) pop_back(j);
            ans = 0;
        }
        else
        {
            while(r < qr) push_back(++r);
            tmpV = ans;
            for(int j = ed; j >= ql; --j) push_front(j);
            res[tmp[i]] = ans;
            for(int j = ql; j <= ed; ++j) pop_front(j);
            ans = tmpV;
        }
    }
    for(int i = 0; i < m; ++i) std::cout << res[i] << '\n';
    return 0;
}