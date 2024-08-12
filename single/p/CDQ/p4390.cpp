// # [BalkanOI2007] Mokia 摩基亚

// ## 题目描述

// 摩尔瓦多的移动电话公司摩基亚（Mokia）设计出了一种新的用户定位系统。和其他的定位系统一样，它能够迅速回答任何形如 “用户 C 的位置在哪？” 的问题，精确到毫米。但其真正高科技之处在于，它能够回答形如 “给定区域内有多少名用户？” 的问题。

// 在定位系统中，世界被认为是一个 $w\times w$ 的正方形区域，由 $1\times 1$ 的方格组成。每个方格都有一个坐标 $(x, y)$，$1\leq x,y\leq w$。坐标的编号从 $1$ 开始。对于一个 $4\times 4$ 的正方形，就有 $1\leq x\leq 4$，$1\leq y\leq 4$（如图）：

// ![](https://cdn.luogu.com.cn/upload/pic/17271.png)

// 请帮助 Mokia 公司编写一个程序来计算在某个矩形区域内有多少名用户。

// ## 输入格式

// 有三种命令，意义如下：

// |命令|参数|意义|
// |:-:|:-:|:-:|
// |$0$|$w$|初始化一个全零矩阵。本命令仅开始时出现一次。|
// |$1$|$x\ y\ a$|向方格 $(x, y)$ 中添加 $a$ 个用户。$a$ 是正整数。|
// |$2$|$x_1\ y_1\ x_2\ y_2$|查询 $x_1\leq x\leq x_2$，$y_1\leq y\leq y_2$ 所规定的矩形中的用户数量。|
// |$3$|无参数|结束程序。本命令仅结束时出现一次。|

// 输入共若干行，每行有若干个整数，表示一个命令。

// ## 输出格式

// 对所有命令 $2$，输出一个一行整数，即当前询问矩形内的用户数量。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 0 4
// 1 2 3 3
// 2 1 1 3 3
// 1 2 2 2
// 2 2 2 3 4
// 3
// ```

// ### 样例输出 #1

// ```
// 3
// 5
// ```

// ## 提示

// #### 数据规模与约定


// 对于 $100\%$ 的数据，保证：
// - $1\leq w\leq 2\times 10 ^ 6$。
// - $1\leq x_1\leq x_2\leq w$，$1\leq y_1\leq y_2\leq w$，$1\leq x,y\leq w$，$0<a\leq 10000$。
// - 命令 $1$ 不超过 $160000$ 个。
// - 命令 $2$ 不超过 $10000$ 个。
#include <iostream>
#include <bits/stdc++.h>
#define ll long long
#define lowbit(x) (x & -x)

const int maxN = 2E5 + 5, maxM = 1E4 + 5;
ll res[maxM], cnt[maxN];
int x[maxN], y[maxN], tag[maxN], s[maxN], s1[maxN], s2[maxN], rk[maxN], k;

inline void updata(int x, int v){
    while(x <= k) cnt[x] += v, x += lowbit(x);
}

inline ll query(int x){
    ll res = 0;
    while(x) res += cnt[x], x -= lowbit(x);
    return res;
}

inline void init(int n){
    std::iota(s, s + n + 1, 0);
    std::sort(s + 1, s + n + 1, [&](const int& a, const int& b){return y[a] < y[b];});
    int pre = -1;
    for(int i = 1; i <= n; i++){
        if(y[s[i]] > pre) pre = y[s[i]], ++k;
        rk[s[i]] = k;
    }
    x[0] = 0X3f3f3f3f;
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
        if(x[s1[idx1]] <= x[s2[idx2]]){
            if(tag[s1[idx1]] > 0) updata(rk[s1[idx1]], tag[s1[idx1]]);
            s[i] = s1[idx1++];
        }
        else{
            if(tag[s2[idx2]] < 0){
                if(tag[s2[idx2]] < -maxM) res[-tag[s2[idx2]] - maxM] -= query(rk[s2[idx2]]);
                else res[-tag[s2[idx2]]] += query(rk[s2[idx2]]);
            }
            s[i] = s2[idx2++];
        }
    }
    for(int i = 1; i <= m - l + 1; i++) if(tag[s1[i]] > 0) updata(rk[s1[i]], -tag[s1[i]]);
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0, op, w, a, b, c, d, idx = 0;
    do{
        std::cin >> op;
        if(!op) std::cin >> w;
        else if(op == 1){
            ++n;
            std::cin >> x[n] >> y[n] >> tag[n];
        }
        else if(op == 2){
            ++idx;
            std::cin >> a >> b >> c >> d;
            n++, x[n] = a - 1, y[n] = b - 1, tag[n] = -idx;
            n++, x[n] = c, y[n] = d, tag[n] = -idx;
            n++, x[n] = a - 1, y[n] = d, tag[n] = -idx - maxM;
            n++, x[n] = c, y[n] = b - 1, tag[n] = -idx - maxM;
        }
    }while(op != 3);
    init(n);
    std::iota(s, s + n + 1, 0);
    cdq(1, n);
    for(int i = 1; i <= idx; i++) std::cout << res[i] << '\n';
    return 0;
}