// # 小清新人渣的本愿

// ## 题目背景

// **本题时限3s，空间128MB**

// 我感觉我要挂省选

// 人渣的本愿是一个有趣的番

// 可爱的花火喜欢从小和她谈♂笑♂风♂生的欧♂尼♂酱鸣海，欧尼酱特别想当老师，然后剧本安排当了花火的班主任。

// 然而有个叫做皆川茜的奇怪的人抢走了欧尼酱！

// 花火就很失落呀，然后看到一个叫做麦的人也很失落，原来麦喜欢茜老师。。。

// 花火和麦从此天天谈笑风生，然后决定在一起，把对方当做自己喜欢的人的替代品

// 因为花火很可爱，所以有许多奇怪的人喜欢花火，比如一个叫做绘鸠早苗的妹子

// 因为麦长的也不错，所以有许多奇怪的人喜欢麦，比如一个叫做最可的妹子

// 然后就开始愉快的生♂活了~

// 以上内容如果你没有看过这个番可以无视掉


// 按照套路，现在欧尼酱会问花火一个OI问题（一般是数据结构），然后花火肯定不会OI，所以会来请教您这位IOI Au选手，然后您肯定会帮助她

// 但是
// 这个套路太无聊了，我们来换一个（但是不会改变您是IOI Au选手的事实）

// 花火有一天看了几个有趣的番，叫做“在W??身上寻找女装是否搞错了什么”，“从女装开始的?X?”，“我家大佬不可能那么可爱”，然后发现??H太厉害了，然后就穿越到了异世界，和???谈笑风生

// 花火就和???做了一个交♂易，花火帮???做一道题，然后???帮花火改写地球online的程序，让花火和欧尼酱在♂一♂起

// ???虽然非常厉害，但是不会数据结构题，他最近刚刚遇到一道有趣的数据结构题，于是他接受了交易

// 但是花火也不会数据结构题呀

// 所以又回到了这个老套路，就靠您这个IOI Au选手来帮她了！

// 以上内容如果你没有看过这个番还是可以无视掉

// 这里用一个经典的图来解释这个关系（其实没那么蛋疼的）

// ![](https://cdn.luogu.com.cn/upload/pic/4628.png)

// ## 题目描述

// 这个题是这样的：

// 给你一个序列 $a$，长度为 $n$，有 $m$ 次操作，每次询问一个区间是否可以选出两个数它们的差为 $x$，或者询问一个区间是否可以选出两个数它们的和为 $x$，或者询问一个区间是否可以选出两个数它们的乘积为 $x$ ，这三个操作分别为操作 $1,2,3$。

// 选出的这两个数可以是同一个位置的数。

// ![](https://cdn.luogu.com.cn/upload/pic/4629.png)

// ## 输入格式

// 第一行两个数 $n,m$。

// 后面一行 $n$ 个数表示 $a_i$。

// 后面 $m$ 行每行四个数 `opt l r x`。

// $opt$ 表示这个是第几种操作，$l,r$ 表示操作的区间，$x$ 表示这次操作的 $x$。

// ## 输出格式

// 对于每个询问，如果可以，输出 `hana`，否则输出 `bi`。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 10 10
// 1 1 8 9 9 1 1 1 1 9 
// 3 5 9 42
// 2 1 3 14
// 2 3 5 2
// 2 3 3 6
// 1 6 10 18
// 3 4 9 14
// 2 1 4 22
// 3 1 3 32
// 2 5 6 32
// 3 1 9 17
// ```

// ### 样例输出 #1

// ```
// bi
// bi
// bi
// bi
// bi
// bi
// bi
// bi
// bi
// bi
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 5 5
// 1 1 2 3 4
// 2 1 1 2
// 1 1 2 2
// 3 1 1 1
// 3 5 5 16
// 1 2 3 4
// ```

// ### 样例输出 #2

// ```
// hana
// bi
// hana
// hana
// bi
// ```

// ## 提示

// 定义 $c$ 为每次的 $x$ 和 $a_i$ 中的最大值，$a_i \geq 0$，每次的 $x\geq 2$。

// 对于 $10\%$ 的数据，$n,m,c \leq 100$。

// 对于另外 $10\%$ 的数据，$n,m,c \leq 3\times 10^3$。

// 对于另外 $10\%$ 的数据，只有 $1$ 操作。

// 对于另外 $10\%$ 的数据，只有 $2$ 操作。
 
// 对于另外 $10\%$ 的数据，只有 $3$ 操作。

// 对于 $100\%$ 的数据，$n,m,c \leq 10^5$。

// ![](https://cdn.luogu.com.cn/upload/pic/4630.png)
#include <bits/stdc++.h>

const int maxN = 1E5 + 5, v = 1E5;

int arr[maxN], inv[maxN], cnt[maxN];
std::bitset<maxN> f1, f2, res;

struct Query
{
    int t, l, r, x, id;
    bool operator<(const Query& other) const
    {
        return inv[l] ^ inv[other.l]? inv[l] < inv[other.l]:(inv[l] & 1)? r < other.r : r > other.r;
    }
}queries[maxN];

inline void initial(int n, int m)
{
    int sz = std::max(1, static_cast<int>(n / sqrt(m)));
    int nob = (n + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(n, i * sz);
        for(int j = st; j <= ed; ++j) inv[j] = i;
    }
    std::sort(queries, queries + m);
}

inline void add(int x)
{
    if(!cnt[arr[x]]) f1[arr[x]] = f2[v - arr[x]] = 1;
    ++cnt[arr[x]];
}

inline void del(int x)
{
    --cnt[arr[x]];
    if(!cnt[arr[x]]) f1[arr[x]] = f2[v - arr[x]] = 0;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    for(int i = 0; i < m; ++i) std::cin >> queries[i].t >> queries[i].l >> queries[i].r >> queries[i].x, queries[i].id = i; 
    initial(n, m);
    int l = 1, r = 0;
    for(int i = 0; i < m; ++i)
    {
        int &ql = queries[i].l, &qr = queries[i].r;
        while(l < ql) del(l++);
        while(l > ql) add(--l);
        while(r < qr) add(++r);
        while(r > qr) del(r--);
        if(queries[i].t == 1) res[queries[i].id] = (f1 & (f1 << queries[i].x)).any();
        else if(queries[i].t == 2) res[queries[i].id] = (f1 & (f2 >> (v - queries[i].x))).any();
        else
        {
            int mx = sqrt(queries[i].x);
            for(int j = 1; j <= mx; ++j)
            {
                if(queries[i].x % j) continue;
                if(f1[j] & f1[queries[i].x / j])
                {
                    res[queries[i].id] = 1;
                    break;
                }
            }
        }
    }
    for(int i = 0; i < m; ++i) std::cout << (res[i]? "hana\n":"bi\n");
    return 0;
}