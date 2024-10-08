// # 无聊的数列

// ## 题目背景

// 无聊的 YYB 总喜欢搞出一些正常人无法搞出的东西。有一天，无聊的 YYB 想出了一道无聊的题：无聊的数列。。。（K峰：这题不是傻X题吗）

// ## 题目描述

// 维护一个数列 $a_i$，支持两种操作：

//  - `1 l r K D`：给出一个长度等于 $r-l+1$ 的等差数列，首项为 $K$，公差为 $D$，并将它对应加到 $[l,r]$ 范围中的每一个数上。即：令 $a_l=a_l+K,a_{l+1}=a_{l+1}+K+D\ldots a_r=a_r+K+(r-l) \times D$。

//  - `2 p`：询问序列的第 $p$ 个数的值 $a_p$。

// ## 输入格式

// 第一行两个整数数 $n,m$ 表示数列长度和操作个数。

// 第二行 $n$ 个整数，第 $i$ 个数表示 $a_i$。

// 接下来的 $m$ 行，每行先输入一个整数 $opt$。

// 若 $opt=1$ 则再输入四个整数 $l\ r\ K\ D$；

// 若 $opt=2$ 则再输入一个整数 $p$。

// ## 输出格式

// 对于每个询问，一行一个整数表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 2
// 1 2 3 4 5
// 1 2 4 1 2
// 2 3
// ```

// ### 样例输出 #1

// ```
// 6
// ```

// ## 提示

// #### 数据规模与约定

// 对于 $100\%$ 数据，$0\le n,m \le 10^5,-200\le a_i,K,D\le 200, 1 \leq l \leq r \leq n, 1 \leq p \leq n$。
#include <iostream>
#include <bits/stdc++.h>
#define ll long long
#define lowbit(x) (x & -x)

const int maxN = 1E5 + 5;
int w[maxN];
ll d1[maxN], d2[maxN], n;

inline void updata(int x, int v){
    ll v2 = 1ll * x * v;
    while(x <= n)d1[x] += v, d2[x] += v2, x += lowbit(x);
}

inline ll query(int x){
    int y = x + 1;
    ll s1 = 0, s2 = 0;
    while(x) s1 += d1[x], s2 += d2[x], x -= lowbit(x);
    return y * s1 - s2; 
}

inline void modify(int l, int r, int k, int d){
    updata(l, k);
    updata(l + 1, d - k);
    updata(r + 1, -k - (r - l + 1) * d);
    updata(r + 2, k + (r - l) * d);
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int m, op, l, r, k, d;
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    for(int i = 0; i < m; i++){
        std::cin >> op;
        if(op == 1){
            std::cin >> l >> r >> k >> d;
            modify(l, r, k, d);
        }
        else{
            std::cin >> d;
            std::cout << query(d) + w[d] << std::endl;
        }
    }
    return 0;
}