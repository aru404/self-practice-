// # [国家集训队] 数颜色 / 维护队列

// ## 题目描述

// 墨墨购买了一套 $N$ 支彩色画笔（其中有些颜色可能相同），摆成一排，你需要回答墨墨的提问。墨墨会向你发布如下指令：

// 1. $Q\ L\ R$ 代表询问你从第 $L$ 支画笔到第 $R$ 支画笔中共有几种不同颜色的画笔。

// 2. $R\ P\ C$ 把第 $P$ 支画笔替换为颜色 $C$。

// 为了满足墨墨的要求，你知道你需要干什么了吗？

// ## 输入格式

// 第 $1$ 行两个整数 $N$，$M$，分别代表初始画笔的数量以及墨墨会做的事情的个数。

// 第 $2$ 行 $N$ 个整数，分别代表初始画笔排中第 $i$ 支画笔的颜色。

// 第 $3$ 行到第 $2+M$ 行，每行分别代表墨墨会做的一件事情，格式见题干部分。

// ## 输出格式

// 对于每一个 Query 的询问，你需要在对应的行中给出一个数字，代表第 $L$ 支画笔到第 $R$ 支画笔中共有几种不同颜色的画笔。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6 5
// 1 2 3 4 5 5
// Q 1 4
// Q 2 6
// R 1 2
// Q 1 4
// Q 2 6
// ```

// ### 样例输出 #1

// ```
// 4
// 4
// 3
// 4
// ```

// ## 提示

// 对于30%的数据，$n,m \leq 10000$

// 对于60%的数据，$n,m \leq 50000$

// 对于所有数据，$n,m \leq 133333$

// 所有的输入数据中出现的所有整数均大于等于 $1$ 且不超过 $10^6$。

// 本题可能轻微卡常数

// 来源：bzoj2120

// 本题数据为洛谷自造数据，使用 [CYaRon](https://github.com/luogu-dev/cyaron) 耗时5分钟完成数据制作。
#include <bits/stdc++.h>

const int maxN = 1.4E5, maxV = 1E6 + 5;
int arr[maxN], cnt[maxV], inv[maxN], tot = 0;
int modify[maxN], pos[maxN], res[maxN];

struct Query
{
    int l, r, t, id;
    bool operator<(const Query& other) const
    {
        return inv[l] ^ inv[other.l]? inv[l] < inv[other.l]:(inv[r] ^ inv[other.r]? inv[r] < inv[other.r]:t < other.t);
    }
}queries[maxN];

inline void initial(int n, int m)
{
    int sz = std::pow(n, 2.0 / 3.0), nob = (n + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(n, i * sz);
        for(int j = st; j <= ed; ++j)
        {
            inv[j] = i;
        }
    }
    std::sort(queries, queries + m);
}

inline void add(int x)
{
    if(!cnt[arr[x]]) ++tot;
    ++cnt[arr[x]];
}

inline void del(int x)
{
    --cnt[arr[x]];
    if(!cnt[arr[x]]) --tot;
}

inline void updata_time(int t, int l, int r)
{
    if(l <= pos[t] && r >= pos[t])
    {
        --cnt[arr[pos[t]]];
        if(!cnt[arr[pos[t]]]) --tot;
        if(!cnt[modify[t]]) ++tot;
        ++cnt[modify[t]];
    }
    std::swap(modify[t], arr[pos[t]]);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    int cnt1 = 0, cnt2 = 0;
    char type;
    std::cin >> n >> m;
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    for(int i = 0; i < m; ++i)
    {
        std::cin >> type;
        if(type == 'Q')
        {
            std::cin >> queries[cnt1].l >> queries[cnt1].r;
            queries[cnt1].t = cnt2;
            queries[cnt1].id = cnt1;
            ++cnt1;
        }
        else
        {
            ++cnt2;
            std::cin >> pos[cnt2] >> modify[cnt2];
        }
    }
    initial(n, cnt1);
    int l = 1, r = 0, t = 0;
    for(int i = 0; i < cnt1; ++i)
    {
        int &ql = queries[i].l, &qr = queries[i].r, &qt = queries[i].t;
        while(ql < l) add(--l);
        while(ql > l) del(l++);
        while(qr > r) add(++r);
        while(qr < r) del(r--);
        while(t < qt) updata_time(++t, l, r);
        while(t > qt) updata_time(t--, l, r);
        res[queries[i].id] = tot;
    }
    for(int i = 0; i < cnt1; ++i) std::cout << res[i] << '\n';
    return 0;
}