// # [AHOI2009] 维护序列

// ## 题目背景

// 老师交给小可可一个维护数列的任务，现在小可可希望你来帮他完成。

// ## 题目描述

// 有一个长为 $n$ 的数列 $\{a_n\}$，有如下三种操作形式：

// 1. 格式 `1 t g c`，表示把所有满足 $t\le i\le g$ 的 $a_i$ 改为 $a_i\times c$ ;
// 2. 格式 `2 t g c` 表示把所有满足 $t\le i\le g$ 的 $a_i$ 改为 $a_i+c$ ;
// 3. 格式 `3 t g` 询问所有满足 $t\le i\le g$ 的 $a_i$ 的和，由于答案可能很大，你只需输出这个数模 $p$ 的值。

// ## 输入格式

// 第一行两个整数 $n$ 和 $p$。

// 第二行含有 $n$ 个非负整数，表示数列 $\{a_i\}$ 。

// 第三行有一个整数 $m$，表示操作总数。

// 从第四行开始每行描述一个操作，同一行相邻两数之间用一个空格隔开，每行开头和末尾没有多余空格。

// ## 输出格式

// 对每个操作 3，按照它在输入中出现的顺序，依次输出**一行一个整数**表示询问结果。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 7 43
// 1 2 3 4 5 6 7
// 5
// 1 2 5 5
// 3 2 4
// 2 3 7 9
// 3 1 3
// 3 4 7
// ```

// ### 样例输出 #1

// ```
// 2
// 35
// 8
// ```

// ## 提示

// #### 样例输入输出 1 解释

// - 初始时数列为 $\{1,2,3,4,5,6,7\}$。
// - 经过第 $1$ 次操作后，数列为 $\{1,10,15,20,25,6,7\}$。
// - 对第 $2$ 次操作，和为 $10+15+20=45$，模 $43$ 的结果是 $2$。
// - 经过第 $3$ 次操作后，数列为 $\{1,10,24,29,34,15,16\}$。
// - 对第 $4$ 次操作，和为 $1+10+24=35$，模 $43$ 的结果是 $35$。
// - 对第 $5$ 次操作，和为 $29+34+15+16=94$，模 $43$ 的结果是$8$。


// #### 数据规模与约定

// 测试数据规模如下表所示：

// | 数据点编号 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9,10 |
// | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
// | $n=$ | $10$ | $1000$ | $1000$ | $10000$ | $60000$ | $70000$ | $80000$ | $90000$ | $100000$ |
// | $m=$ | $10$ | $1000$ | $1000$ | $10000$ | $60000$ | $70000$ | $80000$ | $90000$ | $100000$ |

// 对于全部的测试点，保证 $0 \leq p, a_i, c \leq 10^9$，$1 \leq t \leq g \leq n$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E5 + 5;
int sum[maxN << 2], lz1[maxN << 2], lz2[maxN << 2], mod;
int w[maxN];

inline void pushDown(int s, int t, int m, int p){
    if(lz1[p] != 1){
        lz2[p << 1] = 1ll * lz2[p << 1] * lz1[p] % mod;
        lz2[p << 1 | 1] = 1ll * lz2[p << 1 | 1] * lz1[p] % mod;
        lz1[p << 1] = 1ll * lz1[p << 1] * lz1[p] % mod;
        lz1[p << 1 | 1] = 1ll * lz1[p << 1 | 1] * lz1[p] % mod;
        sum[p << 1] = 1ll * sum[p << 1] * lz1[p] % mod;
        sum[p << 1 | 1] = 1ll * sum[p << 1 | 1] * lz1[p] % mod;
        lz1[p] = 1;
    }
    if(lz2[p]){
        lz2[p << 1] = (lz2[p << 1] + lz2[p]) % mod;
        lz2[p << 1 | 1] = (lz2[p << 1 | 1] + lz2[p]) % mod;
        sum[p << 1] = (sum[p << 1] + 1ll * (m - s + 1) * lz2[p]) % mod;
        sum[p << 1 | 1] = (sum[p << 1 | 1] + 1ll * (t - m) * lz2[p]) % mod;
        lz2[p] = 0;
    }
}

inline void pushUp(int p){
    sum[p] = (sum[p << 1] + sum[p << 1 | 1]) % mod;
}

inline void buildTree(int s, int t, int p){
    lz1[p] = 1;
    if(s == t){
        sum[p] = w[s];
        return ;
    }
    int m = (t + s) >> 1;
    buildTree(s, m, p << 1);
    buildTree(m + 1, t, p << 1 | 1);
    pushUp(p);
}

inline void updataAdd(int l, int r, int v, int s, int t, int p){
    if(l <= s && r >= t){
        lz2[p] = (lz2[p] + v) % mod;
        sum[p] = (sum[p] + 1ll * (t - s + 1) * v) % mod;
        return ;
    }
    int m = (t + s) >> 1;
    pushDown(s, t, m, p);
    if(l <= m) updataAdd(l, r, v, s, m, p << 1);
    if(r > m) updataAdd(l, r, v, m + 1, t, p << 1 | 1);
    pushUp(p);
}

inline void updataMult(int l, int r, int v, int s, int t, int p){
    if(l <= s && r >= t){
        lz1[p] = 1ll * lz1[p] * v % mod;
        lz2[p] = 1ll * lz2[p] * v % mod;
        sum[p] = 1ll * sum[p] * v % mod;
        return ;
    }
    int m = (t + s) >> 1;
    pushDown(s, t, m, p);
    if(l <= m) updataMult(l, r, v, s, m, p << 1);
    if(r > m) updataMult(l, r, v, m + 1, t, p << 1 | 1);
    pushUp(p);
}

inline int query(int l, int r, int s, int t, int p){
    if(l <= s && r >= t) return sum[p];
    int res = 0, m = (t + s) >> 1;
    pushDown(s, t, m, p);
    if(l <= m) res = (res + query(l, r, s, m, p << 1)) % mod;
    if(r > m) res = (res + query(l, r, m + 1, t, p << 1 | 1)) % mod;
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, op, l, r, v;
    std::cin >> n >> mod;
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    if(mod) buildTree(1, n, 1);
    std::cin >> m;
    for(int i = 0; i < m; i++){
        std::cin >> op >> l >> r;
        if(!mod){
            if(op == 3) std::cout << 0 << '\n';
            else std::cin >> v;
        }
        else{
            if(op == 1){
                std::cin >> v;
                updataMult(l, r, v, 1, n, 1);
            }
            else if(op == 2){
                std::cin >> v;
                updataAdd(l, r, v, 1, n, 1);
            }
            else std::cout << query(l, r, 1, n, 1) << '\n';
        }
    }
    return 0;
}