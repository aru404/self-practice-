// # [HEOI2016/TJOI2016] 序列

// ## 题目描述

// 佳媛姐姐过生日的时候，她的小伙伴从某宝上买了一个有趣的玩具送给他。

// 玩具上有一个数列，数列中某些项的值可能会变化，但同一个时刻最多只有一个值发生变化。现在佳媛姐姐已经研究出了所有变化的可能性，她想请教你，能否选出一个子序列，使得在**任意一种变化和原序列**中，这个子序列都是不降的？请你告诉她这个子序列的最长长度即可。

// ## 输入格式

// 输入的第一行有两个正整数 $n,m$，分别表示序列的长度和变化的个数。

// 接下来一行有 $n$ 个整数，表示这个数列原始的状态。

// 接下来 $m$ 行，每行有 $2$ 个整数 $x,y$，表示数列的第 $x$ 项可以变化成 $y$ 这个值。

// ## 输出格式

// 输出一个整数，表示对应的答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 4 
// 1 2 3 
// 1 2 
// 2 3 
// 2 1 
// 3 4
// ```

// ### 样例输出 #1

// ```
// 3
// ```

// ## 提示

// 注意：每种变化最多只有一个值发生变化。

// 在样例输入中，所有的变化是：
// ```plain
// 1 2 3
// 2 2 3
// 1 3 3
// 1 1 3
// 1 2 4
// ```
// 选择子序列为原序列，即在任意一种变化中均为不降子序列。

// 对于 $20\%$ 数据，所有数均为正整数，且小于等于 $300$。

// 对于 $50\%$ 数据，所有数字均为正整数，且小于等于 $3000$。

// 对于 $100\%$ 数据，所有数字均为正整数，且小于等于 $10^5$。$1\le x\le n$。
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
const int maxN = 1E5 + 5;

int arr[maxN], w1[maxN], w2[maxN], tree[maxN];
int mx[maxN], s[maxN], s1[maxN], s2[maxN], k;

inline void updata(int x, int v)
{
    while(x <= k && tree[x] < v) tree[x] = v, x += lowbit(x);
}

inline int query(int x)
{
    int res = 0;
    while(x) res = std::max(res, tree[x]), x -= lowbit(x);
    return res;
}

inline void clear(int x)
{
    while(x <= k && tree[x]) tree[x] = 0, x += lowbit(x);
}

inline void cdq(int l, int r)
{
    if(l == r)
    {
        mx[l] = std::max(1, mx[l]);
        return ;
    }
    int m = (l + r) >> 1;
    cdq(l, m);
    for(int i = l; i <= m; ++i) s1[i - l + 1] = s[i];
    for(int i = m + 1; i <= r; ++i) s2[i - m] = s[i];
    std::sort(s1 + 1, s1 + m - l + 2, [&](const int& a, const int& b){
        return w2[a] < w2[b];
    });
    std::sort(s2 + 1, s2 + r - m + 1, [&](const int& a, const int& b){
        return arr[a] < arr[b];
    });
    s1[m - l + 2] = s2[r - m + 1] = 0;
    int idx1 = 1, idx2 = 1;
    for(int i = l; i <= r; ++i)
    {
        if(w2[s1[idx1]] <= arr[s2[idx2]])
        {
            updata(arr[s1[idx1]], mx[s1[idx1]]);
            ++idx1;
        }
        else
        {
            mx[s2[idx2]] = std::max(mx[s2[idx2]], query(w1[s2[idx2]]) + 1);
            ++idx2;
        }
    }
    for(int i = 1; i <= m - l + 1; ++i) clear(arr[s1[i]]);
    cdq(m + 1, r);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, w, id;
    std::cin >> n >> m;
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
        w1[i] = w2[i] = arr[i];
    }
    for(int i = 1; i <= m; ++i)
    {
        std::cin >> id >> w;
        w1[id] = std::min(w1[id], w);
        w2[id] = std::max(w2[id], w);
    }
    w1[0] = arr[0] = w2[0] = 0X3f3f3f3f;
    k = *std::max_element(w2 + 1 , w2 + n + 1);
    std::iota(s + 1, s + m + 1, 1);
    cdq(1, n);
    std::cout << *std::max_element(mx + 1, mx + m + 1);
    return 0;
}