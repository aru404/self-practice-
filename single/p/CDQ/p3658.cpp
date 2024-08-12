// # [USACO17FEB] Why Did the Cow Cross the Road III P

// ## 题面翻译

// 给出两个排列 $A,B$ ，相等的数之间连线，求数对 $(i,j)$ 的个数。其中 $(i,j)$ 满足：它们所在两个排列间对应的线交叉且 $|i-j|>k$ 。

// ## 题目描述

// Farmer John is continuing to ponder the issue of cows crossing the road through his farm, introduced in the preceding two problems. He realizes now that the threshold for friendliness is a bit more subtle than he previously considered -- breeds $a$ and $b$ are now friendly if $|a - b| \leq K$, and unfriendly otherwise.
// Given the orderings of fields on either side of the road through FJ's farm, please count the number of unfriendly crossing pairs of breeds, where a crossing pair of breeds is defined as in the preceding problems.

// ## 输入格式

// The first line of input contains $N$ ($1 \leq N \leq 100,000$) and $K$ ($0 \leq K < N$). The next $N$ lines describe the order, by breed ID, of fields on one side of the road; each breed ID is an integer in the range $1 \ldots N$. The last $N$ lines describe the order, by breed ID, of the fields on the other side of the road. Each breed ID appears exactly once in each ordering.

// ## 输出格式

// Please output the number of unfriendly crossing pairs of breeds.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 1
// 4
// 3
// 2
// 1
// 1
// 4
// 2
// 3
// ```

// ### 样例输出 #1

// ```
// 2
// ```

// ## 提示

// In this example, breeds 1 and 4 are unfriendly and crossing, as are breeds 1 and 3.
#include <bits/stdc++.h>
#include <iostream>
#define lowbit(x) (x & -x)
#define ll long long

const int maxN = 1E5 + 5, inf = 0X3f3f3f3f;
int a[maxN], b[maxN], loc[maxN], inv1[maxN], inv2[maxN];
int cnt1[maxN << 1], cnt2[maxN << 1], s[maxN], s1[maxN], s2[maxN], n, k;
ll res = 0;

inline void updata(int x, int v, int* cnt){
    while(x <= n) cnt[x] += v, x += lowbit(x);
}

inline int query(int x, int* cnt){
    int ans = 0;
    while(x) ans += cnt[x], x -= lowbit(x);
    return ans;
}

inline void cdq(int l, int r){
    if(l == r) return ;
    int m = (l + r) >> 1;
    cdq(l, m), cdq(m + 1, r);
    for(int i = l; i <= m; i++) s1[i - l + 1] = s[i];
    for(int i = m + 1; i <= r; i++) s2[i - m] = s[i];
    s1[m - l + 2] = s2[r - m + 1] = 0;
    int idx1 = 1, idx2 = 1;
    for(int i = l; i <= r; i++){
        if(loc[s1[idx1]] > loc[s2[idx2]]){
            updata(a[s1[idx1]], 1, cnt1);
            updata(n + 1 - a[s1[idx1]], 1, cnt2);
            s[i] = s1[idx1++];
        }
        else{
            res += query(std::max(a[s2[idx2]] - k - 1, 0), cnt1);
            res += query(std::max(n - a[s2[idx2]] - k, 0), cnt2);
            s[i] = s2[idx2++];
        }
    }
    for(int i = 1; i <= m - l + 1; i++) updata(a[s1[i]], -1, cnt1), updata(n + 1 - a[s1[i]], -1, cnt2);
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> k;
    for(int i = 1; i <= n; i++){
        std::cin >> a[i];
        inv1[a[i]] = i;
    }
    for(int i = 1; i <= n; i++){
        std::cin >> b[i];
        inv2[b[i]] = i;
    }

    for(int i = 1; i <= n; i++) loc[inv1[i]] = inv2[i];
    std::iota(s, s + n + 1, 0);
    cdq(1, n);
    std::cout << res;
    return 0;
}