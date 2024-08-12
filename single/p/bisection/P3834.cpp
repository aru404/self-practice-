// # 【模板】可持久化线段树 2

// ## 题目背景

// 这是个非常经典的可持久化权值线段树入门题——静态区间第 $k$ 小。

// **数据已经过加强，请使用可持久化权值线段树。同时请注意常数优化**。

// ## 题目描述

// 如题，给定 $n$ 个整数构成的序列 $a$，将对于指定的闭区间 $[l, r]$ 查询其区间内的第 $k$ 小值。

// ## 输入格式

// 第一行包含两个整数，分别表示序列的长度 $n$ 和查询的个数 $m$。  
// 第二行包含 $n$ 个整数，第 $i$ 个整数表示序列的第 $i$ 个元素 $a_i$。   
// 接下来 $m$ 行每行包含三个整数 $ l, r, k$ , 表示查询区间 $[l, r]$ 内的第 $k$ 小值。

// ## 输出格式

// 对于每次询问，输出一行一个整数表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 5
// 25957 6405 15770 26287 26465 
// 2 2 1
// 3 4 1
// 4 5 1
// 1 2 2
// 4 4 1
// ```

// ### 样例输出 #1

// ```
// 6405
// 15770
// 26287
// 25957
// 26287
// ```

// ## 提示

// ### 样例 1 解释

// $n=5$，数列长度为 $5$，数列从第一项开始依次为$\{25957, 6405, 15770, 26287, 26465\}$。

// - 第一次查询为 $[2, 2]$ 区间内的第一小值，即为 $6405$。
// - 第二次查询为 $[3, 4]$ 区间内的第一小值，即为 $15770$。
// - 第三次查询为 $[4, 5]$ 区间内的第一小值，即为 $26287$。
// - 第四次查询为 $[1, 2]$ 区间内的第二小值，即为 $25957$。
// - 第五次查询为 $[4, 4]$ 区间内的第一小值，即为 $26287$。


// ### 数据规模与约定

// - 对于 $20\%$ 的数据，满足 $1 \leq n,m \leq 10$。
// - 对于 $50\%$ 的数据，满足 $1 \leq n,m \leq 10^3$。
// - 对于 $80\%$ 的数据，满足 $1 \leq n,m \leq 10^5$。
// - 对于 $100\%$ 的数据，满足 $1 \leq n,m \leq 2\times 10^5$，$|a_i| \leq 10^9$，$1 \leq l \leq r \leq n$，$1 \leq k \leq r - l + 1$。
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

const int maxN = 2E5 + 5;

struct q
{
    int l, r, k, id;
    bool type;
}queries[maxN << 1];

int arr[maxN], tmp[maxN << 1], val[maxN], res[maxN], s1[maxN << 1], s2[maxN << 1], n, k = 0;
int tree[maxN];

inline void updata(int x, int v)
{
    while(x <= n) tree[x] += v, x += lowbit(x);
}

inline int query(int l, int r)
{
    --l;
    int res = 0;
    while(r > l) res += tree[r], r -= lowbit(r);
    while(l > r) res -= tree[l], l -= lowbit(l);
    return res; 
}

inline void init()
{
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int& a, const int& b){
        return arr[a] ^ arr[b]? arr[a] < arr[b]:a < b;
    });
    int now = INT32_MIN;
    for(int i = 1; i <= n; ++i)
    {
        if(arr[tmp[i]] > now)
        {
            val[++k] = arr[tmp[i]];
            now = arr[tmp[i]];
        }
        queries[tmp[i]].k = k;
    }
}

inline void bisection(int l, int r, int s, int t)
{
    if(s > t) return ;
    if(l == r)
    {
        for(int i = s; i <= t; ++i)
        {
            if(queries[tmp[i]].type) res[queries[tmp[i]].id] = val[l];
        }
        return ;
    }
    int m = (l + r) >> 1;
    int idx1 = 0, idx2 = 0;
    for(int i = s; i <= t; ++i)
    {
        if(queries[tmp[i]].type)
        {
            int v = query(queries[tmp[i]].l, queries[tmp[i]].r);
            if(queries[tmp[i]].k <= v)
            {
                s1[++idx1] = tmp[i];
            }
            else
            {
                queries[tmp[i]].k -= v;
                s2[++idx2] = tmp[i];
            }
        }
        else
        {
            if(queries[tmp[i]].k <= m)
            {
                updata(queries[tmp[i]].id, 1);
                s1[++idx1] = tmp[i];
            }
            else
            {
                s2[++idx2] = tmp[i];
            }
        }
    }
    for(int i = 1; i <= idx1; ++i)
    {
        tmp[s + i - 1] = s1[i];
        if(!queries[s1[i]].type)
        {
            updata(queries[s1[i]].id, -1);
        }
    }
    for(int i = 1; i <= idx2; ++i) tmp[s + idx1 + i - 1] = s2[i];
    bisection(l, m, s, s + idx1 - 1);
    bisection(m + 1, r, s + idx1, t);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m;
    std::cin >> n >> m;
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
        queries[i].id = i;
        queries[i].type = 0;
    }
    for(int i = 1; i <= m; ++i)
    {
        std::cin >> queries[i + n].l >> queries[i + n].r >> queries[i + n].k;
        queries[i + n].type = 1;
        queries[i + n].id = i;
    }
    init();
    std::iota(tmp, tmp + n + m + 1, 0);
    bisection(1, k, 1, n + m);
    for(int i = 1; i <= m; ++i) std::cout << res[i] << " \n"[i < m];
    return 0;
}