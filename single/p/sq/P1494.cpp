// # [国家集训队] 小 Z 的袜子

// ## 题目描述

// upd on 2020.6.10 ：更新了时限。

// 作为一个生活散漫的人，小 Z 每天早上都要耗费很久从一堆五颜六色的袜子中找出一双来穿。终于有一天，小 Z 再也无法忍受这恼人的找袜子过程，于是他决定听天由命……

// 具体来说，小 Z 把这 $N$ 只袜子从 $1$ 到 $N$ 编号，然后从编号 $L$ 到 $R$ 的袜子中随机选出两只来穿。尽管小 Z 并不在意两只袜子是不是完整的一双，他却很在意袜子的颜色，毕竟穿两只不同色的袜子会很尴尬。

// 你的任务便是告诉小 Z，他有多大的概率抽到两只颜色相同的袜子。当然，小 Z 希望这个概率尽量高，所以他可能会询问多个 $(L,R)$ 以方便自己选择。

// **然而数据中有 $L=R$ 的情况，请特判这种情况，输出`0/1`。**

// ## 输入格式

// 输入文件第一行包含两个正整数 $N$ 和 $M$。$N$ 为袜子的数量，$M$ 为小 Z 所提的询问的数量。接下来一行包含 $N$ 个正整数 $C_i$，其中 $C_i$ 表示第 $i$ 只袜子的颜色，相同的颜色用相同的数字表示。再接下来 $M$ 行，每行两个正整数 $L, R$ 表示一个询问。

// ## 输出格式

// 包含 $M$ 行，对于每个询问在一行中输出分数 $A/B$ 表示从该询问的区间 $[L,R]$ 中随机抽出两只袜子颜色相同的概率。若该概率为 $0$ 则输出 `0/1`，否则输出的 $A/B$ 必须为最简分数。（详见样例）

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6 4
// 1 2 3 3 3 2
// 2 6
// 1 3
// 3 5
// 1 6
// ```

// ### 样例输出 #1

// ```
// 2/5
// 0/1
// 1/1
// 4/15
// ```

// ## 提示

// $30\%$ 的数据中，$N,M\leq 5000$；

// $60\%$ 的数据中，$N,M \leq 25000$；

// $100\%$ 的数据中，$N,M \leq 50000$，$1 \leq L \leq R \leq N$，$C_i \leq N$。
#include <bits/stdc++.h>
#define ll long long
const int maxN = 5E4 + 5;

int cnt[maxN], arr[maxN], inv[maxN];
ll numerator[maxN], gcd[maxN], denominator[maxN], tot = 0;

template <typename T>
inline void read(T& x)
{
    x = 0; char c = ::getchar(); bool f = 0;
    while(c < '0' || c > '9') f = c == '-', c = getchar();
    while(c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    if(f) x = -x;
}

struct Query
{
    int l, r, id;
    Query(int l = 0, int r = 0, int id = 0): l(l), r(r), id(id){}
    bool operator<(const Query& other) const
    {
        return inv[l] ^ inv[other.l]? inv[l] < inv[other.l]:(inv[l] & 1)? r < other.r:r > other.r;
    }
}queries[maxN];

inline void initial(int n, int m)
{
    int sz = n / sqrt(m), nob = (n + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(n, i * sz);
        for(int j = st; j <= ed; ++j) inv[j] = i;
    }
    std::sort(queries, queries + m);
}

// 懒得写ex了
inline ll exgcd(ll a, ll b)
{
    return b? exgcd(b, a % b):a;
}

inline void del(int x)
{
    --cnt[arr[x]];
    tot -= cnt[arr[x]];
}

inline void add(int x)
{
    tot += cnt[arr[x]];
    ++cnt[arr[x]];
}

int main()
{
    int n, m;
    read(n), read(m);
    for(int i = 1; i <= n; ++i) read(arr[i]);
    for(int i = 0; i < m; ++i) read(queries[i].l), read(queries[i].r), queries[i].id = i;
    initial(n, m);
    int l = 1, r = 0;
    for(int i = 0; i < m; ++i)
    {
        int &ql = queries[i].l, &qr = queries[i].r, &id = queries[i].id;
        if(ql == qr)
        {
            numerator[id] = 0;
            denominator[id] = 1;
            gcd[id] = 1;   
            continue;
        }
        while(ql < l) add(--l);
        while(ql > l) del(l++);
        while(qr > r) add(++r);
        while(qr < r) del(r--);

        numerator[id] = tot;
        denominator[id] = 1ll * (r - l + 1) * (r - l) / 2;
        gcd[id] = exgcd(denominator[id], numerator[id]);
    }
    for(int i = 0; i < m; ++i)
    {
        ::printf("%lld/%lld\n", numerator[i] / gcd[i], denominator[i] / gcd[i]);
    }
    return 0;
}