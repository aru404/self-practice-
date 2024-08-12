// # 大爷的字符串题

// ## 题目背景

// 在那遥远的西南有一所学校，

// /\*被和谐部分\*/

// 然后去参加该省省选虐场，

// 然后某蒟蒻不会做，所以也出了一个字符串题：

// ## 题目描述

// 给你一个字符串 $a$，每次询问一段区间的贡献。

// 贡献定义：

// 每次从这个区间中拿出一个字符 $x$ ，然后把 $x$ 从这个区间中删除，直到区间为空。你要维护一个集合 $S$。

// - 如果 $S$ 为空，你 rp 减 $1$。 
// - 如果 $S$ 中有一个元素不小于 $x$，则你 rp 减 $1$，清空 $S$。
// - 之后将 $x$ 插入 $S$。

// 由于你是大爷，平时做过的题考试都会考到，所以每次询问你搞完这段区间的字符之后最多还有多少 rp？rp 初始为 $0$。

// 询问之间不互相影响~

// ## 输入格式

// 第一行两个整数 $n$，$m$，表示字符串长度与询问次数。

// 之后一行 $n$ 个数，第 $i$ 个整数表示给出的字符串的第 $i$ 个字符 $x_i$。

// 接下来 $m$ 行，每行两个整数 $l, r$，表示一次询问的区间。

// ## 输出格式

// 对于每次询问，输出一行一个整数表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 3
// 3 3 3
// 3 3
// 3 3
// 3 3
// ```

// ### 样例输出 #1

// ```
// -1
// -1
// -1
// ```

// ## 提示

// #### 数据规模与约定

// - 对于 $10\%$ 的数据，是样例。
// - 对于另外 $10\%$ 的数据，保证 $n,m \le 100$；
// - 对于另外 $10\%$ 的数据，保证 $n,m \le 10^3$；
// - 对于另外 $10\%$ 的数据，保证 $n,m \le 10^4$；
// - 对于另外 $10\%$ 的数据，保证 $n,m \le 10^5$；
// - 对于 $100\%$ 的数据，$1 \leq n,m \le 2 \times10^5$，$1 \leq a_i \leq 10^9$，$1 \leq l, r \leq n$。

// 保证数据像某省省选 day1T2 一样 sb，大家尽情用暴力水过题吧！

// 没事，你只要在一个好学校，就算这题只能拿到 10 分，也可以进队了。
#include <bits/stdc++.h>

const int maxN = 2E5 + 5;
int inv[maxN], sz;
int arr[maxN], rk[maxN], tmp[maxN];
int cnt[maxN], res[maxN], mx;

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
    sz = std::max(1, static_cast<int>(n / sqrt(m)));
    int nob = (n + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(n, i * sz);
        for(int j = st; j <= ed; ++j) inv[j] = i;
    }
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int& a, const int& b){
        return arr[a] < arr[b];
    });
    int k = 0, now = 0;
    for(int i = 1; i <= n; ++i)
    {
        if(now < arr[tmp[i]]) now = arr[tmp[i]], ++k;
        rk[tmp[i]] = k;
    }
    std::iota(tmp, tmp + m, 0);
    std::sort(tmp, tmp + m, [&](const int& a, const int& b){
        return queries[a] < queries[b];
    });
}

inline void add(int x)
{
    ++cnt[rk[x]];
    mx = std::max(mx, cnt[rk[x]]);
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
    int l = 1, r = 0, ed = 0, tmpV = 0;
    for(int i = 0; i < m; ++i)
    {
        int &ql = queries[tmp[i]].l, &qr = queries[tmp[i]].r;
        if(inv[ed] != inv[ql])
        {
            for(int j = l; j <= r; ++j) --cnt[rk[j]];
            mx = tmpV = 0;
            ed = std::min(n, inv[ql] * sz);
            l = ed + 1, r = ed;
        }
        if(inv[ql] == inv[qr])
        {
            for(int j = ql; j <= qr; ++j) add(j);
            res[tmp[i]] = -mx;
            for(int j = ql; j <= qr; ++j) --cnt[rk[j]];
            mx = 0;
        }
        else
        {
            while(r < qr) add(++r);
            tmpV = mx;
            for(int j = ed; j >= ql; --j) add(j);
            res[tmp[i]] = -mx;
            for(int j = ql; j <= ed; ++j) --cnt[rk[j]];
            mx = tmpV;
        }
    }
    for(int i = 0; i < m; ++i) std::cout << res[i] << '\n';
    return 0;
}