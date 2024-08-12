// # [HEOI2012] 采花

// ## 题目描述

// 萧薰儿是古国的公主，平时的一大爱好是采花。

// 今天天气晴朗，阳光明媚，公主清晨便去了皇宫中新建的花园采花。

// 花园足够大，容纳了 $n$ 朵花，共有 $c$ 种颜色，用整数 $1 \sim c$ 表示。且花是排成一排的，以便于公主采花。公主每次采花后会统计采到的花的颜色数，颜色数越多她会越高兴。同时，她有一癖好，她不允许最后自己采到的花中，某一颜色的花只有一朵。为此，公主每采一朵花，要么此前已采到此颜色的花，要么有相当正确的直觉告诉她，她必能再次采到此颜色的花。

// 由于时间关系，公主只能走过花园连续的一段进行采花，便让女仆福涵洁安排行程。福涵洁综合各种因素拟定了 $m$ 个行程，然后一一向你询问公主能采到的花共有几种不同的颜色。

// ## 输入格式

// 输入的第一行是三个用空格隔开的整数，分别代表花的个数 $n$，花的颜色数 $c$，以及行程数 $m$。

// 输入的第二行是 $n$ 个用空格隔开的整数，第 $i$ 个整数代表第 $i$ 朵花的颜色 $x_i$。

// 第 $3$ 行到第 $(m + 2)$ 行，每行两个整数 $l, r$，第 $(i + 2)$ 行的数字代表第 $i$ 次行程为第 $l$ 到第 $r$ 朵花。

// ## 输出格式

// 共输出 $m$ 行，每行一个整数。第 $i$ 行的整数代表第 $i$ 次行程公主能采到的花共有几种不同的颜色。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 3 5
// 1 2 2 3 1
// 1 5
// 1 2
// 2 2
// 2 3
// 3 5
// ```

// ### 样例输出 #1

// ```
// 2
// 0
// 0
// 1
// 0
// ```

// ## 提示

// #### 输入输出样例 $1$ 解释

// 共有五朵花，颜色分别为 $1,~2,~2,~3,~1$。

// 对于第一次行程，公主采花的区间为 $[1, 5]$，可以采位置 $1,~2,~3,~5$ 处的花，共有 $1$ 和 $2$ 两种不同的颜色。

// 对于第二次行程，公主采花的区间为 $[1, 2]$，但是颜色为 $1$ 和 $2$ 的花都只出现了一次，因此公主无花可采。

// 对于第三次行程，公主采花的区间为 $[2, 2]$，但是颜色为 $2$ 的花只出现了一次，公主无花可采。

// 对于第四次行程，公主采花的区间为 $[2, 3]$，可以采 $2,~3$ 位置的花，只有 $2$ 这一种颜色。

// 对于第五次行程，公主采花的区间为 $[3,5]$，但是颜色为 $1, 2, 3$ 的花都只出现了一次，因此公主无花可采。

// #### 数据范围与约定

// **本题采用多测试点捆绑测试，共有两个子任务**。

// 对于子任务 $1$，分值为 $100$ 分，保证 $1 \leq n, c, m \leq 3 \times 10^5$。

// 对于子任务 $2$，分值为 $100$ 分，保证 $1 \leq n, c, m \leq 2 \times 10^6$。

// 对于全部的测试点，保证 $1 \leq x_i \leq c$，$1 \leq l \leq r \leq n$。
#include <iostream>
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

const int maxN = 2E6 + 5;
int cnt[maxN], pre1[maxN], pre2[maxN], col[maxN], res[maxN], rk[maxN], n;

struct node{
    int l, r;
    bool operator<(const node& b) const{
        return r ^ b.r? r < b.r:l < b.l;
    }
}nodes[maxN];

inline void updata(int x, int v){
    while(x <= n) cnt[x] += v, x += lowbit(x);
}

inline int query(int l, int r){
    int res = 0;
    while(r) res += cnt[r], r -= lowbit(r);
    --l;
    while(l) res -= cnt[l], l -= lowbit(l);
    return res; 
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int c, m;
    std::cin >> n >> c >> m;
    for(int i = 1; i <= n; i++) std::cin >> col[i];
    for(int i = 0; i < m; i++){
        std::cin >> nodes[i].l >> nodes[i].r;
    }
    std::iota(rk, rk + m, 0);
    std::sort(rk, rk + m, [&](const int& a, const int& b){return nodes[a] < nodes[b];});
    int l = -1, r = 0;
    for(int i = 0; i < m; i++){
        while(r < nodes[rk[i]].r){
            ++r;
            if(pre2[col[r]]) updata(pre2[col[r]], -1);
            if(pre1[col[r]]) updata(pre1[col[r]], 1);
            pre2[col[r]] = pre1[col[r]], pre1[col[r]] = r;
        }
        l = nodes[rk[i]].l;
        res[rk[i]] = query(l, r);
    }
    for(int i = 0; i < m; i++){
        std::cout << res[i] << '\n';
    }
    return 0;
}