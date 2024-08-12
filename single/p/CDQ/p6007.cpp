// # [USACO20JAN] Springboards G

// ## 题目描述

// Bessie 在一个仅允许沿平行于坐标轴方向移动的二维方阵中。她从点 $(0,0)$ 出发，想要到达 $(N,N)$（$1 \leq N \leq 10^9$）。为了帮助她达到目的，在方阵中有 $P$（$1 \leq P \leq 10^5$）个跳板。每个跳板都有其固定的位置 $(x_1,y_1)$，如果 Bessie 使用它，会落到点 $(x_2,y_2)$。

// Bessie 是一个过程导向的奶牛，所以她仅允许她自己向上或向右行走，从不向左或向下。类似地，每个跳板也设置为不向左或向下。Bessie 需要行走的距离至少是多少？

// ## 输入格式

// 输入的第一行包含两个空格分隔的整数 $N$ 和 $P$。

// 以下 $P$ 行每行包含四个整数 $x_1,y_1,x_2,y_2$，其中 $x_1 \leq x_2$ 且 $y_1 \leq y_2$。

// 所有跳板的位置和目标位置均不相同。

// ## 输出格式

// 输出一个整数，为 Bessie 到达点 $(N,N)$ 需要行走的最小距离。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 2
// 0 1 0 2
// 1 2 2 3
// ```

// ### 样例输出 #1

// ```
// 3
// ```

// ## 提示

// ### 样例解释

// Bessie 的最佳路线为：

// - Bessie 从 (0,0) 走到 (0,1)（1 单位距离）。
// - Bessie 跳到 (0,2)。
// - Bessie 从 (0,2) 走到 (1,2)（1 单位距离）。
// - Bessie 跳到 (2,3)。
// - Bessie 从 (2,3) 走到 (3,3)（1 单位距离）。

// Bessie 总共走过的路程为 3 单位距离。

// ### 子任务

// - 测试点 $2 \sim 5$ 满足 $P \leq 1000$。
// - 测试点 $6 \sim 15$ 没有额外限制。
#include <iostream>
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define get(x) (x <= p + 1? ps[x].x1:ps[x - p - 2].x2)

const int maxN = 1E5 + 10;
struct sq{
    int x1, x2, y1, y2;
    sq(int x1 = 0, int x2 = 0, int y1 = 0, int y2 = 0): x1(x1), x2(x2), y1(y1), y2(y2){}
}ps[maxN];

int rk[maxN << 1], tmp[maxN << 1];
int mx[maxN << 1], ans[maxN], k, p;

inline void updata(int x, int v){
    while(x <= k && v > mx[x]) mx[x] = v, x += lowbit(x); 
}

inline void clear(int x){
    while(x <= k) mx[x] = 0, x += lowbit(x);
}

inline int query(int x){
    int res = 0;
    while(x) res = std::max(res, mx[x]), x -= lowbit(x);
    return res;
}

inline void init(int n){
    for(int i = 1; i <= p; i++) std::cin >> ps[i].x1 >> ps[i].y1 >> ps[i].x2 >> ps[i].y2;
    ps[p + 1] = sq(n, n, n, n);
    std::iota(tmp, tmp + (p << 1) + 4, 0);
    std::sort(tmp, tmp + (p << 1) + 4, [&](const int a, const int b){return get(a) < get(b);});
    int now = -1, m = (p + 2) << 1;
    for(int i = 0; i < m; i++){
        int v = get(tmp[i]);
        if(now < v) now = v, ++k;
        rk[tmp[i]] = k;
    }
    for(int i = 1; i <= p + 1; i++) if(ps[i].x1 || ps[i].y1) ans[i] = INT32_MAX;
}

inline void cdq(int l, int r){
    if(l == r) return ;
    int m = (l + r) >> 1;
    cdq(l, m);

    std::sort(tmp + l, tmp + m + 1, [&](const int a, const int b){return ps[a].y2 ^ ps[b].y2? ps[a].y2 < ps[b].y2:a < b;});
    int idx1 = l, idx2 = m + 1;
    for(int i = l; i <= r; i++){
        if(idx1 == m + 1 || ps[tmp[idx2]].y1 < ps[tmp[idx1]].y2){
            ans[tmp[idx2]] = std::min(ans[tmp[idx2]], ps[tmp[idx2]].x1 + ps[tmp[idx2]].y1 - query(rk[tmp[idx2]]));
            idx2++;
        }
        else{
            updata(rk[tmp[idx1] + p + 2], ps[tmp[idx1]].x2 + ps[tmp[idx1]].y2 - ans[tmp[idx1]]);
            idx1++;
        }
    }
    for(int i = l; i <= m; i++) clear(rk[tmp[i] + p + 2]);
    cdq(m + 1, r);
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n >> p;
    init(n);
    std::iota(tmp, tmp + p + 2, 0);
    std::stable_sort(tmp, tmp + p + 2, [&](const int a, const int b){return ps[a].y1 < ps[b].y1;});
    cdq(0, p + 1);
    std::cout << ans[p + 1];

    return 0;
}