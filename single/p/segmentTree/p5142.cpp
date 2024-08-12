// # 区间方差

// ## 题目背景

// 出题人并没有能力写有趣的题面……

// ## 题目描述

// 对于一个长度为 $n$ 的序列 $a_1,a_2,a_3\cdots a_n$，我们定义它的平均数 $a$ 为:

// $$a=\frac{1}{n}\sum_{i=1}^{n}a_i$$

// 并定义它的方差 $d$ 为:

// $$d=\frac{1}{n}\sum_{i=1}^{n}(a_i-a)^2$$

// 现在给定一个长度为 $n$ 的序列 $b_1,b_2\cdots b_n$。你需要支持两种操作。每种操作的格式为 `c x y`。

// 若 $c=1$，为修改操作，代表将 $b_x$ 赋值为 $y$。

// 若 $c=2$，为查询操作，代表查询 $b_x$ 到 $b_y$ 的方差。

// 为了避免浮点数误差，请以分数取模形式输出结果（对 1000000007（$10^9+7$）取模）。

// ## 输入格式

// 第一行两个整数 $n,m$，代表序列 $b$ 的长度为 $n$，有 $m$ 个操作。

// 第二行 $n$ 个整数 $b_i$，表示序列 $b$ 的初始值。

// 下面有 $m$ 行整数，每行格式为 `c x y`，含义如上文所示。保证所有操作合法。

// ## 输出格式

// 对于每个操作 2，输出一行。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 8
// 0 0 0 0
// 1 1 1
// 1 2 2
// 1 3 3
// 1 4 4
// 2 1 1
// 2 1 2
// 2 1 3
// 2 1 4
// ```

// ### 样例输出 #1

// ```
// 0
// 250000002
// 666666672
// 250000003
// ```

// ## 提示

// #### 样例 1 解释
// 四次修改后，序列 $b$ 为：$\{1,2,3,4\}$。

// 区间 $[1,1]$ 的方差为 $0$。

// 区间 $[1,2]$ 的方差为 $\frac{1}{4}$ 。$4$ 的逆元为 $250000002$。

// 区间 $[1,3]$ 的方差为 $\frac{2}{3}$。$3$ 的逆元为 $333333336$，$2\times333333336\bmod M=666666672$。

// #### 数据规模与约定

// - 对于 $50\%$ 的数据，$n\leq 1000$，$m\leq 1000$。
// - 对于 $100\%$ 的数据，$1\leq n,m\leq 1\times 10^5$，$1\leq b_i\leq 1\times 10^9$，$1\leq x\leq n$。对于操作 1，$1\leq y\leq 1\times 10^9$。对于操作2，$x\leq y\leq n$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E5 + 5, mod = 1E9 + 7;
int inv[maxN], e[maxN << 2], sq[maxN << 2], w[maxN];

inline void init(int n){
    inv[1] = 1;
    for(int i = 2; i <= n; i++){
        inv[i] = (mod - 1ll * (mod / i) * inv[mod % i] % mod);
    }
}

inline void pushUp(int p){
    e[p] = (e[p << 1] + e[p << 1 | 1]) % mod;
    sq[p] = (sq[p << 1] + sq[p << 1 | 1]) % mod;
}

inline void buildTree(int s, int t, int p){
    if(s == t){
        e[p] = w[s], sq[p] = 1ll * w[s] * w[s] % mod;
        return ;
    }
    int m = (t + s) >> 1;
    buildTree(s, m, p << 1);
    buildTree(m + 1, t, p << 1 | 1);
    pushUp(p);
}

inline void updata(int id, int v, int s, int t, int p){
    if(s == t){
        sq[p] = 1ll * v * v % mod;
        e[p] = v;
        return ;
    }
    int m = (t + s) >> 1;
    if(id <= m) updata(id, v, s, m, p << 1);
    else updata(id, v, m + 1, t, p << 1 | 1);
    pushUp(p);
}

inline std::pair<int, int> query(int l, int r, int s, int t, int p){
    if(l <= s && r >= t) return std::make_pair(sq[p], e[p]);
    int m = (t + s) >> 1;
    if(r <= m) return query(l, r, s, m, p << 1);
    if(l > m) return query(l, r, m + 1, t, p << 1 | 1);
    auto lq = query(l, r, s, m, p << 1), rq = query(l, r, m + 1, t, p << 1 | 1);
    return std::make_pair((lq.first + rq.first) % mod, (lq.second + rq.second) % mod);
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q, l, r, op;
    std::cin >> n >> q;
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    buildTree(1, n, 1); init(n);
    for(int i = 0; i < q; i++){
        std::cin >> op >> l >> r;
        if(op == 1) updata(l, r, 1, n, 1);
        else{
            auto it = query(l, r, 1, n, 1);
            int len = r - l + 1;
            int res = (1ll * it.first * inv[len] % mod - (1ll * it.second * inv[len] % mod) * (1ll * it.second * inv[len] % mod) % mod + mod) % mod;
            std::cout << res << '\n';
        }
    }
    return 0;
}