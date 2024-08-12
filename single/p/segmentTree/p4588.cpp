// # [TJOI2018] 数学计算

// ## 题目描述

// 小豆现在有一个数 $x$，初始值为 $1$。小豆有 $Q$ 次操作，操作有两种类型：

// `1 m`：将 $x$ 变为 $x \times m$，并输出 $x \bmod M$

// `2 pos`：将 $x$ 变为 $x$ 除以第 $pos$ 次操作所乘的数（保证第 $pos$ 次操作一定为类型 1，对于每一个类型 1 的操作至多会被除一次），并输出 $x \bmod M$。

// ## 输入格式

// 一共有  $t$ 组输入。

// 对于每一组输入，第一行是两个数字 $Q,M$。

// 接下来 $Q$ 行，每一行为操作类型 $op$，操作编号或所乘的数字 $m$（保证所有的输入都是合法的）。

// ## 输出格式

// 对于每一个操作，输出一行，包含操作执行后的 $x \bmod M$ 的值。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 1
// 10 1000000000
// 1 2
// 2 1
// 1 2
// 1 10
// 2 3
// 2 4
// 1 6
// 1 7
// 1 12
// 2 7
// ```

// ### 样例输出 #1

// ```
// 2
// 1
// 2
// 20
// 10
// 1
// 6
// 42
// 504
// 84
// ```

// ## 提示

// 对于 $20\%$ 的数据，$1 \le Q \le 500$。

// 对于 $100\%$ 的数据，$1 \le Q \le 10^5$，$t \le 5, M \le 10^9$，$0 < m \leq 10^9$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E5 + 5;
int mult[maxN << 2], k = 1, mod;

inline void updata(int x, int v){
    mult[k + x] = v;
    for(int i = k + x; i > 1; i >>= 1){
        mult[i >> 1] = 1ll * mult[i] * mult[i ^ 1] % mod;
    }
} 

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, op, x, t;
    std::cin >> t;
    std::fill_n(mult, sizeof(mult) / sizeof(int), 1);
    for(int i = 0; i < t; i++){
        std::cin >> n >> mod;
        while(k < n) k <<= 1;
        for(int i = 1; i <= n; i++){
            std::cin >> op >> x;
            if(op == 1){
                updata(i, x);
            }
            else{
                updata(x, 1);
            }
            std::cout << mult[1] << std::endl;
        }
        for(int i = 1; i <= k + n; i++) mult[i] = 1;
    }
    return 0;
}