// # 歴史の研究

// ## 题面翻译

// #### 题目描述
// IOI 国历史研究的第一人——JOI 教授，最近获得了一份被认为是古代 IOI 国的住民写下的日记。JOI 教授为了通过这份日记来研究古代 IOI 国的生活，开始着手调查日记中记载的事件。

// 日记中记录了连续 $N$ 天发生的事件，大约每天发生一件。

// 事件有种类之分。第 $i$ 天发生的事件的种类用一个整数 $X_i$
// 表示，$X_i$ 越大，事件的规模就越大。

// JOI 教授决定用如下的方法分析这些日记：

//  - 选择日记中连续的几天 $[L,R]$ 作为分析的时间段；

//  - 定义事件 $A$ 的重要度 $W_A$ 为 $A\times T_A$，其中 $T_A$ 为该事件在区间 $[L,R]$ 中出现的次数。

// 现在，您需要帮助教授求出所有事件中重要度最大的事件是哪个，**并输出其重要度**。

// 注意：教授有多组询问。
// #### 输入格式
// 第一行两个空格分隔的整数 $N$ 和 $Q$，表示日记一共记录了 $N$ 天，询问有 $Q$ 次。

// 接下来一行 $N$ 个空格分隔的整数表示每天的事件种类。

// 接下来 $Q$ 行，每行给出 $L,R$ 表示一组询问。

// #### 输出格式
// 输出共有 $Q$ 行，每行一个整数，表示对应的询问的答案。

// #### 数据范围
// 对于 $100\%$ 的数据，$1\le Q,N\le 10^5$，$1\le X\le 10^9$，$1\le L\le R\le 10^5$。

// ## 题目描述

// [problemUrl]: https://atcoder.jp/contests/joisc2014/tasks/joisc2014_c

// ## 输入格式

// ## 输出格式

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 5
// 9 8 7 8 9
// 1 2
// 3 4
// 4 4
// 1 4
// 2 4
// ```

// ### 样例输出 #1

// ```
// 9
// 8
// 8
// 16
// 16
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 8 4
// 9 9 19 9 9 15 9 19
// 1 4
// 4 6
// 3 5
// 5 8
// ```

// ### 样例输出 #2

// ```
// 27
// 18
// 19
// 19
// ```

// ## 样例 #3

// ### 样例输入 #3

// ```
// 12 15
// 15 9 3 15 9 3 3 8 16 9 3 17
// 2 7
// 2 5
// 2 2
// 1 12
// 4 12
// 3 6
// 11 12
// 1 7
// 2 6
// 3 5
// 3 10
// 7 10
// 1 4
// 4 8
// 4 8
// ```

// ### 样例输出 #3

// ```
// 18
// 18
// 9
// 30
// 18
// 15
// 17
// 30
// 18
// 15
// 18
// 16
// 30
// 15
// 15
// ```
#include <bits/stdc++.h>
#define ll long long

const int maxN = 1E5 + 5;
int arr[maxN], cnt[maxN], tmp[maxN], rk[maxN];
int inv[maxN], w[maxN], sz = 0;
ll res[maxN], ans = 0;

struct Query
{
    int l, r;
    bool operator<(const Query& other) const
    {
        return inv[l] ^ inv[other.l]? inv[l] < inv[other.l]:r < other.r;
    }
}queries[maxN];

inline void initial(int n, int m)
{
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int& a, const int& b){
        return arr[a] < arr[b];
    });
    int k = 0;
    w[0] = 0;
    for(int i = 1; i <= n; ++i)
    {
        if(w[k] < arr[tmp[i]]) w[++k] = arr[tmp[i]];
        rk[tmp[i]] = k;
    }
    sz = std::max(1, static_cast<int>(n / sqrt(m)));
    int nob = (n + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(n, i * sz);
        for(int j = st; j <= ed; ++j) inv[j] = i;
    }
    std::iota(tmp, tmp + m, 0);
    std::sort(tmp, tmp + m, [&](const int& a, const int& b){
        return queries[a] < queries[b];
    });
}

inline void add(int x)
{
    ++cnt[rk[x]];
    ans = std::max(ans, 1ll * cnt[rk[x]] * w[rk[x]]);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    for(int i = 0; i < q; ++i)
    {
        std::cin >> queries[i].l >> queries[i].r;
    }
    initial(n, q);
    ll tmpV = 0;
    int l = 0, r = 0, ed = 0;
    for(int i = 0; i < q; ++i)
    {
        int &ql = queries[tmp[i]].l, &qr = queries[tmp[i]].r;
        if(inv[ed] != inv[ql])
        {
            ed = std::min(n, inv[ql] * sz);
            for(int j = l; j <= r; ++j) --cnt[rk[j]];
            l = ed + 1, r = ed;
            ans = tmpV = 0;
        }
        if(inv[ql] == inv[qr])
        {
            for(int j = ql; j <= qr; ++j) add(j);
            for(int j = ql; j <= qr; ++j) --cnt[rk[j]];
            res[tmp[i]] = ans;
            ans = 0;
        }
        else
        {
            while(r < qr) add(++r);
            tmpV = ans;
            for(int j = ed; j >= ql; --j) add(j);
            for(int j = ed; j >= ql; --j) --cnt[rk[j]];
            res[tmp[i]] = ans;
            ans = tmpV;
        }
    }
    for(int i = 0; i < q; ++i) std::cout << res[i] << '\n';
    return 0;
}