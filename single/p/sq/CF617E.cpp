// # XOR and Favorite Number

// ## 题面翻译

// - 给定一个长度为 $n$ 的序列 $a$，然后再给一个数字 $k$，再给出 $m$ 组询问，每组询问给出一个区间，求这个区间里面有多少个子区间的异或值为 $k$。
// - $1 \le n,m \le 10 ^ 5$，$0 \le k,a_i \le 10^6$，$1 \le l_i \le r_i \le n$。


// Translated by @char32_t，Reformed by @[明依](https://www.luogu.com.cn/user/155826)。

// ## 题目描述

// Bob has a favorite number $ k $ and $ a_{i} $ of length $ n $ . Now he asks you to answer $ m $ queries. Each query is given by a pair $ l_{i} $ and $ r_{i} $ and asks you to count the number of pairs of integers $ i $ and $ j $ , such that $ l<=i<=j<=r $ and the xor of the numbers $ a_{i},a_{i+1},...,a_{j} $ is equal to $ k $ .

// ## 输入格式

// The first line of the input contains integers $ n $ , $ m $ and $ k $ ( $ 1<=n,m<=100000 $ , $ 0<=k<=1000000 $ ) — the length of the array, the number of queries and Bob's favorite number respectively.

// The second line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=1000000 $ ) — Bob's array.

// Then $ m $ lines follow. The $ i $ -th line contains integers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) — the parameters of the $ i $ -th query.

// ## 输出格式

// Print $ m $ lines, answer the queries in the order they appear in the input.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6 2 3
// 1 2 1 1 0 3
// 1 6
// 3 5
// ```

// ### 样例输出 #1

// ```
// 7
// 0
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 5 3 1
// 1 1 1 1 1
// 1 5
// 2 4
// 1 3
// ```

// ### 样例输出 #2

// ```
// 9
// 4
// 4
// ```

// ## 提示

// In the first sample the suitable pairs of $ i $ and $ j $ for the first query are: ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 4 $ ), ( $ 1 $ , $ 5 $ ), ( $ 2 $ , $ 3 $ ), ( $ 3 $ , $ 6 $ ), ( $ 5 $ , $ 6 $ ), ( $ 6 $ , $ 6 $ ). Not a single of these pairs is suitable for the second query.

// In the second sample xor equals $ 1 $ for all subarrays of an odd length.
#include <bits/stdc++.h>
#define ll long long

const int maxN = 1E5 + 5, maxV = 1 << 21;

int cnt[maxV], arr[maxN], inv[maxN];
ll res[maxN], tot = 0;

struct Query
{
    int l, r, id;
    bool operator<(const Query& other) const
    {
        return inv[l] ^ inv[other.l]? inv[l] < inv[other.l]:(inv[l] & 1)? r < other.r:r > other.r;
    }
}queries[maxN];

inline void initial(int n, int m)
{
    int sz = sqrt(n), nob = (n + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(n, i * sz);
        for(int j = st; j <= ed; ++j)
        {
            inv[j] = i;
        }
    }
    std::sort(queries, queries + m);
    for(int i = 2; i <= n; ++i)
    {
        arr[i] ^= arr[i - 1];
    }
}

inline void add(int x, int k)
{
    tot += cnt[arr[x] ^ k];
    ++cnt[arr[x]];
}

inline void del(int x, int k)
{
    --cnt[arr[x]];
    tot -= cnt[arr[x] ^ k];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    for(int i = 0; i < m; ++i) std::cin >> queries[i].l >> queries[i].r, queries[i].id = i;
    initial(n, m);
    int l = 1, r = 0;
    cnt[0] = 1;
    for(int i = 0; i < m; ++i)
    {
        int &ql = queries[i].l, &qr = queries[i].r, &id = queries[i].id;
        while(ql < l) add(--l - 1, k);
        while(ql > l) del(l++ - 1, k);
        while(qr > r) add(++r, k);
        while(qr < r) del(r--, k);
        res[id] = tot;
    }
    for(int i = 0; i < m; ++i) std::cout << res[i] << '\n';
    return 0;
}