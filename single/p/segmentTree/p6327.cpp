// # 区间加区间 sin 和

// ## 题目描述

// 给出一个长度为 $n$ 的整数序列 $a_1,a_2,\ldots,a_n$，进行 $m$ 次操作，操作分为两类。

// 操作 $1$：给出 $l,r,v$，将 $a_l,a_{l+1},\ldots,a_r$ 分别加上 $v$。

// 操作 $2$：给出 $l,r$，询问 $\sum\limits_{i=l}^{r}\sin(a_i)$。

// ## 输入格式

// 第一行一个整数 $n$。

// 接下来一行 $n$ 个整数表示 $a_1,a_2,\ldots,a_n$。

// 接下来一行一个整数 $m$。

// 接下来 $m$ 行，每行表示一个操作，操作 $1$ 表示为 `1 l r v`，操作 $2$ 表示为 `2 l r`。

// ## 输出格式

// 对每个操作 $2$，输出一行，表示答案，四舍五入保留一位小数。

// 保证答案的绝对值大于 $0.1$，且答案的准确值的小数点后第二位不是 $4$ 或 $5$。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5
// 1 3 1 5 5
// 5
// 1 5 5 5
// 2 3 3
// 2 1 5
// 2 2 2
// 2 4 4
// ```

// ### 样例输出 #1

// ```
// 0.8
// 0.3
// 0.1
// -1.0
// ```

// ## 提示

// Idea：nzhtl1477，Solution：nzhtl1477，Code：ccz181078，Data：nzhtl1477

// 保证 $1\leq n,m,a_i,v\leq 2\times 10^5$，$1\leq l\leq r\leq n$。保证所有输入的数都是正整数。
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

const int maxN = 2E5 + 5;
double cs[maxN << 2], sn[maxN << 2];
int add[maxN << 2], wi[maxN];
ll w[maxN << 2];

inline void pushUp(int p){
    cs[p] = cs[p << 1] + cs[p << 1 | 1];
    sn[p] = sn[p << 1] + sn[p << 1 | 1];
}

inline void pushDown(int p){
    if(w[p]){
        w[p << 1] += w[p], w[p << 1 | 1] += w[p];
        double tmp1 = cs[p << 1], tmp2 = sn[p << 1], s = std::sin(w[p]), c = std::cos(w[p]);
        cs[p << 1] = tmp1 * c - tmp2 * s;
        sn[p << 1] = tmp1 * s + tmp2 * c;
        tmp1 = cs[p << 1 | 1], tmp2 = sn[p << 1 | 1];
        cs[p << 1 | 1] = tmp1 * c - tmp2 * s;
        sn[p << 1 | 1] = tmp1 * s + tmp2 * c;
        w[p] = 0;
    }
}

inline void buildTree(int s, int t, int p){
    if(s == t){
        cs[p] = std::cos(wi[s]);
        sn[p] = std::sin(wi[s]);
        return ;
    }
    int m = (t + s) >> 1;
    buildTree(s, m, p << 1);
    buildTree(m + 1, t, p << 1 | 1);
    pushUp(p);
}

inline void updata(int l, int r, int v, int s, int t, int p){
    if(l <= s && r >= t){
        w[p] += v;
        double tmp1 = cs[p], tmp2 = sn[p], c = std::cos(v), sv = std::sin(v);
        cs[p] = tmp1 * c - tmp2 * sv;
        sn[p] = tmp1 * sv + tmp2 * c;
        return ;
    }
    int m = (t + s) >> 1;
    pushDown(p);
    if(l <= m) updata(l, r, v, s, m, p << 1);
    if(r > m) updata(l, r, v, m + 1, t, p << 1 | 1);
    pushUp(p);
}

inline double query(int l, int r, int s, int t, int p){
    if(l <= s && r >= t) return sn[p];
    int m = (t + s) >> 1;
    pushDown(p);
    double res = 0;
    if(l <= m) res += query(l, r, s, m, p << 1);
    if(r > m) res += query(l, r, m + 1, t, p << 1 | 1);
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, op, l, r, v;
    std::cin >> n;
    for(int i = 1; i <= n; i++) std::cin >> wi[i];
    std::cin >> m;
    buildTree(1, n, 1);
    for(int i = 0; i < m; i++){
        std::cin >> op >> l >> r;
        if(op == 1){
            std::cin >> v;
            updata(l, r, v, 1, n, 1);
        }
        else std::cout << std::fixed << std::setprecision(1) << query(l, r, 1, n, 1) << '\n';
    }
}