// # [清华集训2012] 序列操作

// ## 题目背景

// **滥用评测功能将被封号。**

// ## 题目描述

// 有一个长度为 $n$ 的序列，有三个操作：

// 1. `I a b c` 表示将 $[a,b]$ 这一段区间的元素集体增加 $c$；
// 2. `R a b`表示将 $[a,b]$ 区间内所有元素变成相反数；
// 3. `Q a b c` 表示询问 $[a,b]$ 这一段区间中选择 $c$ 个数相乘的所有方案的和 $\mod 19940417$ 的值。

// ## 输入格式

// 第一行两个数 $n, q$ 表示序列长度和操作个数。

// 第二行 $n$ 个整数，表示序列。

// 接下来 $q$ 行每行输入一个操作 `I a b c` 或者 `R a b` 或者 `Q a b c`，意义如题目描述。

// ## 输出格式

// 对于每个询问，输出选出 $c$ 个数相乘的所有方案的和 $\mod 19940417$ 的值。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 5
// 1 2 3 4 5
// I 2 3 1
// Q 2 4 2
// R 1 5
// I 1 3 -1
// Q 1 5 1
// ```

// ### 样例输出 #1

// ```
// 40
// 19940397
// ```

// ## 提示

// **样例说明：**

// 做完第一个操作序列变为 `1 3 4 4 5`。

// 第一次询问结果为 $3 \times 4+3 \times 4+4 \times 4=40$。

// 做完 `R` 操作变成 `-1 -3 -4 -4 -5`。

// 做完 `I` 操作变为 `-2 -4 -5 -4 -5`。

// 第二次询问结果为 $-2-4-5-4-5=-20$。

// **数据范围：**

// 对于 $100\%$ 的数据，$n \leq 50000, q \leq 50000$。初始序列的元素的绝对值 $\leq 10^9$，保证 $[a,b]$ 是一个合法区间，`I` 操作中 $|c| \leq 10^9$，`Q` 操作中 $1 \leq c \leq \min(b-a+1,20)$。
#include <iostream>
#include <bits/stdc++.h>
#define sum(p, x) tree[p].sum[x]
#define lz(p) tree[p].lz
#define tag(p) tree[p].tag

const int maxN = 5E4 + 5, mod = 19940417;
int c[maxN][21], w[maxN];
struct node{
    int sum[21] = {0}, lz = 0;
    bool tag = false;
}tree[maxN << 2];

inline void init(int n){
    for(int i = 0; i <= n; i++){
        c[i][0] = 1;
        for(int j = 1; j <= std::min(20, i); j++){
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
    }
}

inline void pushUp(int p, int s, int t, int m){
    for(int i = 1; i <= std::min(t - s + 1, 20); i++){
        sum(p, i) = 0;
        for(int j = std::max(0, i - t + m); j <= std::min(m - s + 1, i); j++){
            sum(p, i) = (sum(p, i) + 1ll * sum(p << 1, j) * sum(p << 1 | 1, i - j)) % mod;
        }
    }
}

inline void pushDown(int p, int s, int t, int m){
    if(tag(p)){
        int lol = m - s + 1, lor = t - m;
        tag(p << 1) ^= 1, tag(p << 1 | 1) ^= 1;
        lz(p << 1) = (-lz(p << 1) + mod) % mod;
        lz(p << 1 | 1) = (-lz(p << 1 | 1) + mod) % mod;
        for(int i = 1; i <= std::min(20, lol); i += 2) sum(p << 1, i) = (-sum(p << 1, i) + mod) % mod;
        for(int i = 1; i <= std::min(20, lor); i += 2) sum(p << 1 | 1, i) = (-sum(p << 1 | 1, i) + mod) % mod;
        tag(p) = 0;
    }
    if(lz(p)){
        int lol = m - s + 1, lor = t - m;
        lz(p << 1) = (lz(p << 1) + lz(p)) % mod;
        lz(p << 1 | 1) = (lz(p << 1 | 1) + lz(p)) % mod;
        int d[21]; d[0] = 1;
        for(int i = 1; i <= std::min(20, std::max(lol, lor)); i++){
            d[i] = 1ll * d[i - 1] * lz(p) % mod;
        }
        for(int i = std::min(20, lol); i; i--){
            int v = 0;
            for(int j = 0; j <= i; j++) v = (v + 1ll * c[lol - j][i - j] * d[i - j] % mod * sum(p << 1, j)) % mod;
            sum(p << 1, i) = v;
        }
        for(int i = std::min(20, lor); i; i--){
            int v = 0;
            for(int j = 0; j <= i; j++) v = (v + 1ll * c[lor - j][i - j] * d[i - j] % mod * sum(p << 1 | 1, j)) % mod;
            sum(p << 1 | 1, i) = v;
        }
        lz(p) = 0;
    }
}

inline void buildTree(int s, int t, int p){
    sum(p, 0) = 1;
    if(s == t){
        sum(p, 1) = (w[s] % mod + mod) % mod;
        return ;
    }
    int m = (t + s) >> 1;
    buildTree(s, m, p << 1);
    buildTree(m + 1, t, p << 1 | 1);
    pushUp(p, s, t, m);
}

inline void updataRev(int l, int r, int s, int t, int p){
    if(l <= s && r >= t){
        tag(p) ^= 1;
        lz(p) = (-lz(p) + mod) % mod;
        for(int i = 1; i <= std::min(20, t - s + 1); i += 2) sum(p, i) = (-sum(p, i) + mod) % mod;
        return ;
    }
    int m = (t + s) >> 1;
    pushDown(p, s, t, m);
    if(l <= m) updataRev(l, r, s, m, p << 1);
    if(r > m) updataRev(l, r, m + 1, t, p << 1 | 1);
    pushUp(p, s, t, m);
}

inline void updataAdd(int l, int r, int v, int s, int t, int p){
    if(l <= s && r >= t){
        int d[21], len = t - s + 1; d[0] = 1;
        lz(p) = (lz(p) + v) % mod;
        for(int i = 1; i <= std::min(20, len); i++) d[i] = (1ll * d[i - 1] * v) % mod;
        for(int i = std::min(20, len); i; i--){
            int val = 0;
            for(int j = 0; j <= i; j++) val = (val + 1ll * c[len - j][i - j] * d[i - j] % mod * sum(p, j)) % mod;
            sum(p, i) = val;
        }
        return ;
    }
    int m = (t + s) >> 1;
    pushDown(p, s, t, m);
    if(l <= m) updataAdd(l, r, v, s, m, p << 1);
    if(r > m) updataAdd(l, r, v, m + 1, t, p << 1 | 1);
    pushUp(p, s, t, m);
}

inline node query(int l, int r, int k, int s, int t, int p){
    if(l <= s && r >= t) return tree[p];
    int m = (t + s) >> 1;
    pushDown(p, s, t, m);
    if(r <= m) return query(l, r, k, s, m, p << 1);
    if(l > m) return query(l, r, k, m + 1, t, p << 1 | 1);
    auto ln = query(l, r, k, s, m, p << 1), rn = query(l, r, k, m + 1, t, p << 1 | 1);
    int lol = std::min(m - l + 1, m - s + 1), lor = std::min(r - m, t - m);
    node res; res.sum[0] = 1;
    for(int i = 1; i <= std::min(k, lol + lor); i++){
        res.sum[i] = 0;
        for(int j = std::max(0, i - lor); j <= std::min(lol, i); j++){
            res.sum[i] = (res.sum[i] + 1ll * ln.sum[j] * rn.sum[i - j]) % mod;
        }
    }
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q, l, r, k;
    char op;
    std::cin >> n >> q;
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    init(n), buildTree(1, n, 1);
    for(int i = 0; i < q; i++){
        std::cin >> op >> l >> r;
        if(op == 'I'){
            std::cin >> k;
            k = (k % mod + mod) % mod;
            updataAdd(l, r, k, 1, n, 1);
        }
        else if(op == 'R') updataRev(l, r, 1, n, 1);
        else{
            std::cin >> k;
            auto it = query(l, r, k, 1, n, 1);
            std::cout << it.sum[k] << '\n';
        }       
    }
    return 0;
}          