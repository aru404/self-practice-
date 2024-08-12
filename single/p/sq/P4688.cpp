// # [Ynoi2016] 掉进兔子洞

// ## 题目背景

// 5.632

// 我（或者是在读这篇文字的你）不属于这个世界

// 这是世界的界限

// 6.41

// 世界的意义必定存在于世界之外

// 世界中的一切事物如其所存在般而存在，如其所发生般而发生

// 世界之中不存在价值

// ——《逻辑哲学论》

// 我们的情人，不过是随便借个名字，用幻想吹出来的肥皂泡

// 把信拿去吧，你可以使假戏成真

// 我本来是无病呻吟，漫无目的的吐露爱情---现在这些漂泊不定的鸟儿有地方栖息了，你可以从信里看出来

// 拿去吧---由于不是出自真心，话就说得格外动听，拿去吧，就这么办吧...

// ![](https://cdn.luogu.com.cn/upload/pic/21091.png)

// 果然……好女人要有的是，烟、楼顶……还有轻飘飘的衣服呀……

// 某一天，水上由岐看见天上掉下了个布制玩偶

// 为了被天空接受而投掷出的她的布偶，不知在天空飞舞了多少次，已经遍体鳞伤

// “被天空接受”——那是为了寻找不知何时开始在这个城市流传的“回归天空之路”的行为

// ![](https://cdn.luogu.com.cn/upload/pic/21102.png)

// 为了被天空接受而被扔出去的木偶，在空中飞舞并最终坠落

// 那是为了将其本身即为世界的少女送予天空的少女的行为

// ![](https://cdn.luogu.com.cn/upload/pic/21093.png)

// 横跨银河，被称作Vega与Altair，或是织女星与牛郎星的两颗星星，再加上北十字星之顶的天鹅座构成了夏之大三角

// 它被称作譬如三位一体的神圣的图形

// 只有神圣的图形在天空闪耀之时，世界才与天空相遇

// ![](https://cdn.luogu.com.cn/upload/pic/21094.png)

// 我想试一试，第一次，也是最后一次的恶作剧

// ![](https://cdn.luogu.com.cn/upload/pic/21095.png)

// 那是...什么？

// 什么事也没有哦，只是，间宫君他自己主动跳下去了而已哦~

// 怎么回事？

// 什么事也没有哦，只是，间宫君他自己主动跳下去了而已哦~

// 但是我看到了，是那个杀死了大家吗？

// 什么事也没有哦，只是，间宫君他自己主动跳下去了而已哦~

// 不，那个东西，什么都没有做，只是...

// 什么事也没有哦，只是，间宫君他自己主动跳下去了而已哦~

// 只是...怎么回事...

// 什么事也没有哦，只是，间宫君他自己主动跳下去了而已哦~

// 我确实听到了头盖骨破碎的声音

// 但是那个，并非是外面的世界

// 而是总自己的里面传来的

// ![](https://cdn.luogu.com.cn/upload/pic/21096.png)

// 水上同学...我偶尔会思考这种事情...

// 世界的极限到底在哪里呢...

// 世界的...世界的尽头的更尽头...

// 要是能有那种地方...

// 要是假如我能够站在那个地方的话...我还是能跟平时一样看着那个尽头的风景吗？我有这种想法....

// 我理所当然的想着这种事...然后决定似乎是有些奇怪啊

// 因为那里是世界的尽头哦

// 是世界的极限哦

// 如果我能够看到那个的话...世界的极限...是否就等同于我的极限呢？

// 因为，从那里看到的世界...我所看见的...不就是我的世界吗？

// 世界的极限...就会变成我的极限吧~

// 世界就是我看到的摸到的，并且感受到的东西

// 那样的话，世界到底是什么呢

// 世界和我到底有什么不同呢...我有这种想法

// 有吗？

// 世界和我的差别

// 是一样的

// 但是，或许其他人也有相同的感觉...

// 就连你，或许也认为世界就是你自己吧

// 并且，我觉得那个大概是正确的...

// 虽然我不太清楚...大概是你也站在世界的尽头，跟我一样在看着它吧

// 所以，你也和世界一样

// 但是啊，那样果然很奇怪啊...

// 如果世界就是我的话...为什么我会看不到你看到的世界呢？

// 明明我的世界里有你存在...却看不到你看到的世界

// 我从来没有看到过你看到的世界

// 那个，简直就像是两者不会交集的平行宇宙一样...

// 即使有现象暗示着那个东西存在...却是绝对的无法触碰...

// 我...看不到你所在的世界...

// 但是...

// 那个也是真的是真的吗？

// 我真的没有看到过你的世界吗...

// 既然所有的人都平等的拥有她们自己的世界的话

// 那么为什么世界会变成一个呢？

// 为什么那么多的世界会存在于这里呢？

// 世界变成一个的理由

// ...我偶尔会思考这种事情

// 所以...我才能够喜欢上你

// ## 题目描述

// 您正在打 galgame，然后突然发现您今天太颓了，于是想写个数据结构题练练手：

// 一个长为 $n$ 的序列 $a$。

// 有 $m$ 个询问，每次询问三个区间，把三个区间中同时出现的数一个一个删掉，问最后三个区间剩下的数的个数和，询问独立。

// 注意这里删掉指的是一个一个删，不是把等于这个值的数直接删完，比如三个区间是  $[1,2,2,3,3,3,3]$，$[1,2,2,3,3,3,3]$ 与 $[1,1,2,3,3]$，就一起扔掉了 $1$ 个 $1$，$1$ 个 $2$，$2$ 个 $3$。

// ## 输入格式

// 第一行两个整数表示 $n,m$。

// 第二行 $n$ 个整数表示 $a_i$。

// 之后 $m$ 行，每行 $6$ 个整数 $l_1,r_1,l_2,r_2,l_3,r_3$ 表示这三个区间。

// ## 输出格式

// 对于每个询问，输出一个整数表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 2
// 1 2 2 3 3
// 1 2 2 3 3 4
// 1 5 1 5 1 5
// ```

// ### 样例输出 #1

// ```
// 3
// 0
// ```

// ## 提示

// Idea：nzhtl1477，Solution：nzhtl1477，Code：nzhtl1477，Data：nzhtl1477

// $1\leq n , m \leq 10^5$，$1 \leq a_i\leq 10^9$，$1\leq l_1,r_1,l_2,r_2,l_3,r_3\leq n$，$l_1\leq r_1$，$l_2\leq r_2$，$l_3\leq r_3$。
#include <bits/stdc++.h>

const int maxN = 1E5 + 5, maxB = 4E4;
int arr[maxN], inv[maxN], cnt[maxN], rk[maxN], tmp[maxN];
int res[maxN];
std::bitset<maxN> vis[maxB + 5], col;

struct Query
{
    int l, r;
    bool operator<(const Query& other)
    {
        return inv[l] ^ inv[other.l]? inv[l] < inv[other.l]:(inv[l] & 1)? r < other.r:r > other.r;
    }
}queries[3][maxN];

inline void initial(int n, int m)
{
    int sz = std::max(1 , static_cast<int>(n / sqrt(m))), nob = (n + sz - 1) / sz;
    for(int i = 1; i <= nob; ++i)
    {
        int st = (i - 1) * sz + 1, ed = std::min(n, i * sz);
        for(int j = st; j <= ed; ++j) inv[j] = i;
    }
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int& a, const int& b){
        return arr[a] < arr[b];
    });
    int now = 0, k = 0, tot = 1;
    for(int i = 1; i <= n; ++i)
    {
        if(now < arr[tmp[i]]) now = arr[tmp[i]], k += tot, tot = 0;
        ++tot, rk[tmp[i]] = k;
    }
}

inline void add(int x)
{
    col[rk[x] + cnt[rk[x]]] = 1;
    ++cnt[rk[x]];
}

inline void del(int x)
{
    --cnt[rk[x]];
    col[rk[x] + cnt[rk[x]]] = 0;
}

inline void solve(int st, int ed)
{
    std::function<void(int)> mo = [&](int k)->void{
        std::iota(tmp + st, tmp + ed + 1, st);
        std::sort(tmp + st, tmp + ed + 1, [&](const int& a, const int& b){
            return queries[k][a] < queries[k][b];
        });
        int l = 1, r = 0;
        for(int i = st; i <= ed; ++i)
        {
            int &ql = queries[k][tmp[i]].l, &qr = queries[k][tmp[i]].r;
            while(ql < l) add(--l);
            while(qr > r) add(++r);
            while(ql > l) del(l++);
            while(qr < r) del(r--);
            vis[tmp[i] - st] &= col;
        }
        for(int i = l; i <= r; ++i) del(i);
    };
    for(int i = st; i <= ed; ++i) vis[i - st].set();
    for(int i = 0; i < 3; ++i) mo(i);
    for(int i = st; i <= ed; ++i)
    {
        for(int j = 0; j < 3; ++j) res[i] += queries[j][i].r - queries[j][i].l + 1;
        res[i] -= 3 * vis[i - st].count();
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    for(int i = 1; i <= m; ++i)
    {
        for(int j = 0; j < 3; ++j) std::cin >> queries[j][i].l >> queries[j][i].r;
    }
    initial(n, m);
    int k = (maxB - 1 + m) / maxB;
    for(int i = 1; i <= k; ++i)
    {
        int st = (i - 1) * maxB + 1, ed = std::min(i * maxB, m);
        solve(st, ed);
    }
    for(int i = 1; i <= m; ++i) std::cout << res[i] << '\n';
    return 0;
}