// # [Violet] 天使玩偶/SJY摆棋子

// ## 题目描述

// Ayu 在七年前曾经收到过一个天使玩偶，当时她把它当作时间囊埋在了地下。而七年后 的今天，Ayu 却忘了她把天使玩偶埋在了哪里，所以她决定仅凭一点模糊的记忆来寻找它。

// 我们把 Ayu 生活的小镇看作一个二维平面坐标系，而 Ayu 会不定时地记起可能在某个点 (xmy) 埋下了天使玩偶；或者 Ayu 会询问你，假如她在 $(x,y)$，那么她离近的天使玩偶可能埋下的地方有多远。

// 因为 Ayu 只会沿着平行坐标轴的方向来行动，所以在这个问题里我们定义两个点之间的距离为 $\operatorname{dist}(A,B)=|A_x-B_x|+|A_y-B_y|$。其中 $A_x$ 表示点 $A$ 的横坐标，其余类似。

// ## 输入格式

// 第一行包含两个整数 $n$ 和 $m$，在刚开始时，Ayu 已经知道有 $n$ 个点可能埋着天使玩偶， 接下来 Ayu 要进行 $m$ 次操作

// 接下来 $n$ 行，每行两个非负整数 $(x_i,y_i)$，表示初始 $n$ 个点的坐标。

// 再接下来 $m$ 行，每行三个非负整数 $t,x_i,y_i$。

// * 如果 $t=1$，则表示 Ayu 又回忆起了一个可能埋着玩偶的点 $(x_i,y_i)$。
// * 如果 $t=2$，则表示 Ayu 询问如果她在点 $(x_i,y_i)$，那么在已经回忆出来的点里，离她近的那个点有多远

// ## 输出格式

// 对于每个 $t=2$ 的询问，在单独的一行内输出该询问的结果。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 2 3 
// 1 1 
// 2 3 
// 2 1 2 
// 1 3 3 
// 2 4 2
// ```

// ### 样例输出 #1

// ```
// 1 
// 2
// ```

// ## 提示

// #### 数据规模与约定

// 对于 $100\%$ 的数据 保证 $1 \leq n,m\leq 3 \times 10^5$，$0 \leq x_i,y_i \leq 10^6$。
#include <iostream>
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

const int maxN = 6E5 + 5, inf = 0X3f3f3f3f;
int xs[maxN], ys[maxN], dfn[maxN], mx1[maxN], mx2[maxN], mn1[maxN], mn2[maxN], tmp[maxN], rk[maxN], s[maxN], s1[maxN], s2[maxN], k, n;
int ans[maxN >> 1];
bool type[maxN];

inline void init(int m){
    std::iota(tmp, tmp + m + 1, 0);
    std::sort(tmp + 1, tmp + m + 1, [&](const int& a, const int& b){return ys[a] < ys[b];});
    int pre = -inf; k = 0;
    for(int i = 1; i <= m; i++){
        if(pre < ys[tmp[i]]) pre = ys[tmp[i]], ++k;
        rk[tmp[i]] = k;
    }
    std::iota(s, s + m + 1, 0);
    std::sort(s + 1, s + m + 1, [&](const int& a, const int& b){return xs[a] < xs[b];});
    for(int i = 1; i <= k; i++) mx1[i] = mx2[i] = -inf, mn1[i] = mn2[i] = inf;
    dfn[0] = inf;
}

inline void updata1(int x, int v, int* mx){
    while(x <= k) mx[x] = std::max(mx[x], v), x += lowbit(x);
}

inline void updata2(int x, int v, int* mn){
    while(x <= k) mn[x] = std::min(mn[x], v), x += lowbit(x);
}

inline int query1(int x, int* mx){
    int res = -inf;
    while(x) res = std::max(res, mx[x]), x -= lowbit(x);
    return res;
}

inline int query2(int x, int* mn){
    int res = inf;
    while(x) res = std::min(res, mn[x]), x -= lowbit(x);
    return res;
}

inline void clear(int x, int v, int* tree){
    while(x <= k) tree[x] = v, x += lowbit(x);
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
        if(dfn[s1[idx1]] < dfn[s2[idx2]]){
            if(type[s1[idx1]]){
                int id = s1[idx1] - n;
                ans[id] = std::min(ans[id], -xs[s1[idx1]] + ys[s1[idx1]] + query2(rk[s1[idx1]], mn1));
                ans[id] = std::min(ans[id], -xs[s1[idx1]] - ys[s1[idx1]] + query2(k + 1 - rk[s1[idx1]], mn2)); 
            }
            else{
                updata1(rk[s1[idx1]], xs[s1[idx1]] + ys[s1[idx1]], mx1);
                updata1(k + 1 - rk[s1[idx1]], xs[s1[idx1]] - ys[s1[idx1]], mx2);
            }
            s[i] = s1[idx1++];
        }
        else{
            if(type[s2[idx2]]){
                int id = s2[idx2] - n;
                ans[id] = std::min(ans[id], xs[s2[idx2]] + ys[s2[idx2]] - query1(rk[s2[idx2]], mx1));
                ans[id] = std::min(ans[id], xs[s2[idx2]] - ys[s2[idx2]] - query1(k + 1 - rk[s2[idx2]], mx2));
            }
            else{
                updata2(rk[s2[idx2]], xs[s2[idx2]] - ys[s2[idx2]], mn1);
                updata2(k + 1 - rk[s2[idx2]], xs[s2[idx2]] + ys[s2[idx2]], mn2);
            }
            s[i] = s2[idx2++];
        }
    }
    for(int i = 1; i <= m - l + 1; i++){
        if(!type[s1[i]]){
            clear(rk[s1[i]], -inf, mx1);
            clear(k + 1 - rk[s1[i]], -inf, mx2);
        }
    }
    for(int i = 1; i <= r - m; i++){
        if(!type[s2[i]]){
            clear(rk[s2[i]], inf, mn1);
            clear(k + 1 - rk[s2[i]], inf, mn2);
        }
    }
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int m, op;
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++) std::cin >> xs[i] >> ys[i];
    for(int i = 1; i <= m; i++){
        std::cin >> op >> xs[n + i] >> ys[n + i];
        dfn[n + i] = i;
        if(op == 2) type[n + i] =  1;
    }
    init(n + m);
    for(int i = 1; i <= m; i++) ans[i] = inf;
    cdq(1, n + m);
    for(int i = 1; i <= m; i++){
        if(ans[i] != inf) std::cout << ans[i] << std::endl;
    }
    return 0;
}