// # Dynamic Rankings

// ## 题目描述

// 给定一个含有 $n$ 个数的序列 $a_1,a_2 \dots a_n$，需要支持两种操作：  

// - `Q l r k` 表示查询下标在区间 $[l,r]$ 中的第 $k$ 小的数  
// - `C x y` 表示将 $a_x$ 改为 $y$

// ## 输入格式

// 第一行两个正整数 $n,m$，表示序列长度与操作个数。  
// 第二行 $n$ 个整数，表示 $a_1,a_2 \dots a_n$。  
// 接下来 $m$ 行，每行表示一个操作，都为上述两种中的一个。

// ## 输出格式

// 对于每一次询问，输出一行一个整数表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 3
// 3 2 1 4 7
// Q 1 4 3
// C 2 6
// Q 2 5 3
// ```

// ### 样例输出 #1

// ```
// 3
// 6
// ```

// ## 提示

// 【数据范围】  

// 对于 $10\%$ 的数据，$1\le n,m \le 100$；  
// 对于 $20\%$ 的数据，$1\le n,m \le 1000$；  
// 对于 $50\%$ 的数据，$1\le n,m \le 10^4$；     
// 对于 $100\%$ 的数据，$1\le n,m \le 10^5$，$1 \le l \le r \le n$，$1 \le k \le r-l+1$，$1\le x \le n$，$0 \le a_i,y \le 10^9$。

// 请注意常数优化，但写法正常的整体二分和树套树都可以以大约 $1000\text{ms}$ 每个点的时间通过。

// 来源：bzoj1901

// 本题数据为洛谷自造数据，使用[CYaRon](https://github.com/luogu-dev/cyaron)耗时5分钟完成数据制作。
// #include <bits/stdc++.h>
// #define lowbit(x) (x & -x)
// #define ls(x) tree[x].ls
// #define rs(x) tree[x].rs
// #define cnt(x) tree[x].cnt

// const int maxN = 1E5 + 5;

// struct seg
// {
//     int ls, rs, cnt;
// }tree[maxN * 630];

// struct q{
//     int l, r, k;
// }qs[maxN];

// int root[maxN], val[maxN << 1], pre[maxN], tmp[maxN << 1], rk[maxN << 1], cnt = 0, k = 0, tot = 0, n;
// int tmp1[20], tmp2[20];
// int stk[maxN], top = 0;

// inline void pushUp(int p)
// {
//     cnt(p) = cnt(ls(p)) + cnt(rs(p));
// }

// inline void get(int& x)
// {
//     if(top) x = stk[top--];
//     else x = ++cnt;
//     ls(x) = rs(x) = cnt(x) = 0;
// }

// inline void clear(int& x)
// {
//     stk[++top] = x;
//     x = 0;
// }

// inline void updataTree(int id, int v, int s, int t, int& x)
// {
//     if(!x) get(x);
//     if(s == t)
//     {
//         cnt(x) += v;
//         if(!cnt(x)) clear(x);
//         return ;
//     }
//     int m = (t + s) >> 1;
//     if(id <= m) updataTree(id, v, s, m, ls(x));
//     else updataTree(id, v, m + 1, t, rs(x));
//     pushUp(x);
// }

// inline void updata(int id, int v)
// {
//     int x = id;
//     if(pre[id] == v) return ;
//     while(x <= n)
//     {
//         if(pre[id]) updataTree(pre[id], -1, 1, k, root[x]);
//         updataTree(v, 1, 1, k, root[x]);
//         x += lowbit(x);
//     }
//     pre[id] = v;
// }

// inline int query(int l, int r, int kth)
// {
//     --l;
//     int idx1 = 0, idx2 = 0;
//     while(r) tmp1[++idx1] = root[r], r -= lowbit(r);
//     while(l) tmp2[++idx2] = root[l], l -= lowbit(l);
//     l = 1, r = k;
//     while(l < r)
//     {
//         int v = 0, m = (l + r) >> 1;
//         for(int i = 1; i <= idx1; ++i) v += cnt(ls(tmp1[i]));
//         for(int i = 1; i <= idx2; ++i) v -= cnt(ls(tmp2[i]));
//         if(kth > v)
//         {
//             for(int i = 1; i <= idx1; ++i) tmp1[i] = rs(tmp1[i]);
//             for(int i = 1; i <= idx2; ++i) tmp2[i] = rs(tmp2[i]);
//             kth -= v;
//             l = m + 1;
//         }
//         else
//         {
//             for(int i = 1; i <= idx1; ++i) tmp1[i] = ls(tmp1[i]);
//             for(int i = 1; i <= idx2; ++i) tmp2[i] = ls(tmp2[i]);
//             r = m;
//         }
//     }
//     return val[l];
// }

// inline void init(int m)
// {
//     std::sort(tmp + 1, tmp + m + 1, [&](const int& a, const int& b){
//         return qs[a].k ^ qs[b].k? qs[a].k < qs[b].k:a < b;
//     });
//     int now = INT32_MIN;
//     for(int i = 1; i <= m; ++i)
//     {
//         if(qs[tmp[i]].k > now)
//         {
//             val[++k] = now = qs[tmp[i]].k;
//         }
//         rk[tmp[i]] = k;
//     }
//     for(int i = 1; i <= n; ++i) updata(i, rk[i]);
// }

// int main()
// {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);

//     int m;
//     std::cin >> n >> m;
//     for(int i = 1; i <= n; ++i)
//     {
//         std::cin >> qs[i].k;
//         tmp[++tot] = i;
//     }
//     char type;
//     m += n;
//     for(int i = n + 1; i <= m; ++i)
//     {
//         std::cin >> type;
//         if(type == 'Q')
//         {
//             std::cin >> qs[i].l >> qs[i].r >> qs[i].k;
//         }
//         else
//         {
//             std::cin >> qs[i].l >> qs[i].k;
//             tmp[++tot] = i;
//         }
//     }
//     init(tot);
//     for(int i = n + 1; i <= m; ++i)
//     {
//         if(rk[i]) updata(qs[i].l, rk[i]);
//         else std::cout << query(qs[i].l, qs[i].r, qs[i].k) << " \n"[i < m];
//     }
//     return 0;
// }

// #include <bits/stdc++.h>
// #define lowbit(x) (x & -x)

// const int maxN = 1E5 + 5;

// struct q
// {
//     int l, r, k, id;
//     bool type;
// }qs[maxN << 2];

// int rk[maxN << 2], tmp[maxN << 2], tmp1[maxN << 2], tmp2[maxN << 2];
// int tree[maxN << 1], pre[maxN], val[maxN << 1], res[maxN], k, n;

// inline int query(int l, int r)
// {
//     --l;
//     int res = 0;
//     while(r > l) res += tree[r], r -= lowbit(r);
//     while(l > r) res -= tree[l], l -= lowbit(l);
//     return res;
// }

// inline void updata(int x, int v)
// {
//     while(x <= n) tree[x] += v, x += lowbit(x);  
// }

// inline void bisection(int l, int r, int s, int t)
// {
//     if(s > t) return ;
//     if(l == r)
//     {
//         for(int i = s; i <= t; ++i)
//         {
//             if(qs[tmp[i]].type)
//             {
//                 res[qs[tmp[i]].id] = l;
//             }
//         }
//         return ;
//     }
//     int m = (l + r) >> 1;
//     int idx1 = 0, idx2 = 0;
//     for(int i = s; i <= t; ++i)
//     {
//         if(qs[tmp[i]].type)
//         {
//             int v = query(qs[tmp[i]].l, qs[tmp[i]].r);
//             if(qs[tmp[i]].k <= v)
//             {
//                 tmp1[++idx1] = tmp[i];
//             }
//             else
//             {
//                 qs[tmp[i]].k -= v;
//                 tmp2[++idx2] = tmp[i];
//             }
//         }
//         else
//         {
//             if(rk[tmp[i]] <= m)
//             {
//                 updata(qs[tmp[i]].id, qs[tmp[i]].l);
//                 tmp1[++idx1] = tmp[i];
//             }
//             else
//             {
//                 tmp2[++idx2] = tmp[i];
//             }
//         }
//     }
//     for(int i = 1; i <= idx1; ++i)
//     {
//         if(!qs[tmp1[i]].type) updata(qs[tmp1[i]].id, -qs[tmp1[i]].l);
//         tmp[s + i - 1] = tmp1[i];
//     }
//     for(int i = 1; i <= idx2; ++i) tmp[s + idx1 + i - 1] = tmp2[i];
//     bisection(l, m, s, s + idx1 - 1);
//     bisection(m + 1, r, s + idx1, t);
// }

// inline void init(int m)
// {
//     std::sort(tmp + 1, tmp + m + 1, [&](const int& a, const int& b){
//         return qs[a].k ^ qs[b].k? qs[a].k < qs[b].k:a < b;
//     });
//     int now = INT32_MIN;
//     for(int i = 1; i <= m; ++i)
//     {
//         if(now < qs[tmp[i]].k) val[++k] = now = qs[tmp[i]].k;
//         rk[tmp[i]] = k;
//     }
// }

// int main()
// {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);

//     int m, cnt = 0, tot = 0;
//     std::cin >> n >> m;
//     for(int i = 1; i <= n; ++i)
//     {
//         std::cin >> qs[++tot].k;
//         qs[tot].id = i;
//         qs[tot].l = 1;
//         pre[i] = qs[tot].k;
//         tmp[++cnt] = tot;
//     }
//     char type;
//     for(int i = 1; i <= m; ++i)
//     {
//         std::cin >> type;
//         if(type == 'Q')
//         {
//             ++tot;
//             std::cin >> qs[tot].l >> qs[tot].r >> qs[tot].k;
//             qs[tot].id = i;
//             qs[tot].type = 1;
//         }
//         else
//         {
//             ++tot;
//             std::cin >> qs[tot].id;
//             qs[tot].k = pre[qs[tot].id];
//             qs[tot].l = -1;
//             tmp[++cnt] = tot;
//             ++tot;
//             std::cin >> qs[tot].k;
//             qs[tot].id = qs[tot - 1].id;
//             qs[tot].l = 1;
//             tmp[++cnt] = tot;
//             pre[qs[tot].id] = qs[tot].k;
//         }
//     }
//     init(cnt);
//     std::iota(tmp, tmp + tot + 1, 0);
//     bisection(1, k, 1, tot);
//     for(int i = 1; i <= m; ++i)
//     {
//         if(res[i]) std::cout << val[res[i]] << '\n';
//     }
//     return 0;
// }
#include <bits/stdc++.h>
#define ls(x) treap[x].lson
#define rs(x) treap[x].rson
#define rd(x) treap[x].rand
#define cnt(x) treap[x].count
#define id(x) treap[x].idx

const int maxN = 1E5 + 5;

struct node
{
    int count, idx, rand, lson, rson;
    node(int cnt = 0, int id = 0, int rd = 0, int ls = 0, int rs = 0):
        count(cnt), idx(id), rand(rd), lson(ls), rson(rs){}
}treap[maxN * 20];

struct q
{
    int l, r, k;
}qs[maxN << 1];

int root[maxN << 3], cnt = 0, rx, ry, rz; 
int stk[maxN << 3], tmp[maxN << 1], rk[maxN << 1], val[maxN << 1], pre[maxN], top = 0, k;
std::mt19937 rnd;

inline void get(int& x, int id)
{
    if(top) x = stk[top--];
    else x = ++cnt;
    ls(x) = rs(x) = 0;
    cnt(x) = 1, rd(x) = rnd(), id(x) = id;
}

inline void clear(int& x)
{
    stk[++top] = x;
    x = 0;
}

inline void pushUp(int x)
{
    cnt(x) = cnt(ls(x)) + cnt(rs(x)) + 1;
}

inline void split(int id, int r, int& x, int& y)
{
    if(!r)
    {
        x = y = 0;
        return ;
    }
    if(id(r) <= id)
    {
        x = r;
        split(id, rs(r), rs(x), y);
    }
    else
    {
        y = r;
        split(id, ls(r), x, ls(y));
    }
    pushUp(r);
}

inline int merger(int x, int y)
{
    if(!x || !y) return x | y;
    if(rd(x) < rd(y))
    {
        rs(x) = merger(rs(x), y);
        pushUp(x);
        return x;
    }
    else
    {
        ls(y) = merger(x, ls(y));
        pushUp(y);
        return y;
    }
}

inline void ins(int& r, int id)
{
    split(id, r, rx, ry);
    get(rz, id);
    r = merger(merger(rx, rz), ry);
}

inline void del(int& r, int id)
{
    split(id, r, rx, ry);
    split(id - 1, rx, rx, rz);
    clear(rz);
    r = merger(rx, ry);
}

inline int queryTreap(int l, int r, int& rt)
{
    int res = 0;
    split(r, rt, rx, ry);
    res += cnt(rx);
    split(l - 1, rx, rx, rz);
    res -= cnt(rx);
    rt = merger(merger(rx, rz), ry);
    return res;
}

inline void updata(int v, int id, int s, int t, int p, bool type)
{
    if(p ^ 1)
    {
        if(type) del(root[p], id);
        else ins(root[p], id);
    }
    if(s == t) return ;
    int m = (t + s) >> 1;
    if(v <= m) updata(v, id, s, m, p << 1, type);
    else updata(v, id, m + 1, t, p << 1 | 1, type);
}

inline int query(int l, int r, int k, int s, int t, int p)
{
    if(s == t) return val[s];
    int m = (t + s) >> 1;
    int v = queryTreap(l, r, root[p << 1]);
    if(k <= v) return query(l, r, k, s, m, p << 1);
    else return query(l, r, k - v, m + 1, t, p << 1 | 1);
}

inline void init(int n)
{
    std::sort(tmp + 1, tmp + n + 1, [&](const int& a, const int& b){
        return qs[a].k ^ qs[b].k? qs[a].k < qs[b].k:a < b;
    });
    int now = INT32_MIN;
    for(int i = 1; i <= n; ++i)
    {
        if(now < qs[tmp[i]].k) now = val[++k] = qs[tmp[i]].k;
        rk[tmp[i]] = k;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    rnd = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());
    int n, m, tot = 0;
    char type;
    std::cin >> n >> m;
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> qs[i].k;
        qs[i].l = i;
        tmp[++tot] = i;
    }
    m += n;
    for(int i = n + 1; i <= m; ++i)
    {
        std::cin >> type;
        if(type == 'Q')
        {
            std::cin >> qs[i].l >> qs[i].r >> qs[i].k;
        }
        else
        {
            std::cin >> qs[i].l >> qs[i].k;
            tmp[++tot] = i;
        }
    }
    init(tot);
    for(int i = 1; i <= m; ++i)
    {
        if(rk[i])
        {
            if(pre[qs[i].l] ^ rk[i] && pre[qs[i].l]) updata(pre[qs[i].l], qs[i].l, 1, k, 1, 1);
            updata(rk[i], qs[i].l, 1, k, 1, 0);
            pre[qs[i].l] = rk[i];
        }
        else std::cout << query(qs[i].l, qs[i].r, qs[i].k, 1, k, 1) << '\n';
    }
    return 0;
}