// # 寒假作业

// ## 题目背景

// zzs 和 zzy 正在被寒假作业折磨，然而他们有答案可以抄啊。

// ## 题目描述

// 他们共有 $n$ 项寒假作业。zzy 给每项寒假作业都定义了一个疲劳值 $a_$，表示抄这个作业所要花的精力。

// zzs 现在想要知道，有多少组连续的寒假作业的疲劳值的平均值不小于 $k$？

// 简单地说，给定一个长度为 $n$ 的正整数序列 $\{a_i\}$，求出有多少个**连续**子序列的平均值不小于 $k$。

// ## 输入格式

// 第一行是两个整数，分别表示序列长度 $n$ 和给定的参数 $k$。

// 第二行有 $n$ 个整数，第 $i$ 个整数表示序列的第 $i$ 个数字 $a_i$。

// ## 输出格式

// 输出一行一个整数表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 2
// 1
// 2
// 3
// ```

// ### 样例输出 #1

// ```
// 4
// ```

// ## 提示

// #### 样例 1 解释

// 共有 $6$ 个连续的子序列，分别是 $(1)$、$(2)$、$(3)$、$(1,2)$、$(2,3)$、$(1,2,3)$，平均值分别为 $1$、$2$、$3$、$1.5$、$2.5$、$2$，其中平均值不小于 $2$ 的共有 $4$ 个。

// #### 数据规模与约定

// - 对于 $20\%$ 的数据，保证 $n \leq 100$。
// - 对于 $50\%$ 的数据，保证 $n \leq 5000$。
// - 对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^5$，$1 \leq a_i,k \leq 10^4$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E5 + 5, inf = 0X3f3f3f3f;
int w[maxN], sums[maxN], s1[maxN], s2[maxN], s[maxN], n;
long long res = 0;

inline void cdq(int l, int r){
    if(l == r) return ;
    int m = (l + r) >> 1;
    cdq(l, m), cdq(m + 1, r);
    for(int i = l; i <= m; i++) s1[i - l + 1] = s[i];
    for(int i = m + 1; i <= r; i++) s2[i - m] = s[i];
    s1[m - l + 2] = s2[r - m + 1] = n + 1;
    int idx1 = 1, idx2 = 1;
    for(int i = l; i <= r; i++){
        if(sums[s2[idx2]] < sums[s1[idx1]]){
            res += idx1 - 1;
            s[i] = s2[idx2++];
        }
        else{
            s[i] = s1[idx1++];
        }
    }
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int k;
    std::cin >> n >> k;
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    for(int i = 1; i <= n; i++) sums[i] = sums[i - 1] + w[i] - k;
    std::iota(s, s + n + 1, 0);
    sums[n + 1] = inf;
    cdq(0, n);
    std::cout << res << std::endl;
    return 0;
}