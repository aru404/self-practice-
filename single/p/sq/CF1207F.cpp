// # Remainder Problem

// ## 题面翻译

// ## 题目描述
// 给你一个长度为 $500000$ 的序列，初值为 $0$ ，你要完成 $q$ 次操作，操作有如下两种：
// 1. `1 x y` : 将下标为 $x$ 的位置的值加上 $y$
// 2. `2 x y` : 询问所有下标模 $x$ 的结果为 $y$ 的位置的值之和

// ## 输入格式
// 第一行一个整数 $q$ ，表示操作数。($q\leqslant500000$)  
// 接下来 $q$ 行，每行三个整数 $t,x,y$ 表示一次操作。($t\in\{1,2\}$)  
// 若 $t=1$ 则为第一种操作，保证：  
// $1\leqslant x\leqslant500000,-1000\leqslant y\leqslant1000$  
// 若 $t=2$ 则为第二种操作，保证：  
// $1\leqslant x\leqslant500000,0\leqslant y<x$  
// 数据保证至少有一个操作 $2$ 。

// ## 输出格式
// 每行对于每个操作 $2$ 输出一个整数表示答案。

// ## 题目描述

// You are given an array $ a $ consisting of $ 500000 $ integers (numbered from $ 1 $ to $ 500000 $ ). Initially all elements of $ a $ are zero.

// You have to process two types of queries to this array:

// - $ 1 $ $ x $ $ y $ — increase $ a_x $ by $ y $ ;
// - $ 2 $ $ x $ $ y $ — compute $ \sum\limits_{i \in R(x, y)} a_i $ , where $ R(x, y) $ is the set of all integers from $ 1 $ to $ 500000 $ which have remainder $ y $ modulo $ x $ .

// Can you process all the queries?

// ## 输入格式

// The first line contains one integer $ q $ ( $ 1 \le q \le 500000 $ ) — the number of queries.

// Then $ q $ lines follow, each describing a query. The $ i $ -th line contains three integers $ t_i $ , $ x_i $ and $ y_i $ ( $ 1 \le t_i \le 2 $ ). If $ t_i = 1 $ , then it is a query of the first type, $ 1 \le x_i \le 500000 $ , and $ -1000 \le y_i \le 1000 $ . If $ t_i = 2 $ , then it it a query of the second type, $ 1 \le x_i \le 500000 $ , and $ 0 \le y_i < x_i $ .

// It is guaranteed that there will be at least one query of type $ 2 $ .

// ## 输出格式

// For each query of type $ 2 $ print one integer — the answer to it.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5
// 1 3 4
// 2 3 0
// 2 4 3
// 1 4 -4
// 2 1 0
// ```

// ### 样例输出 #1

// ```
// 4
// 4
// 0
// ```
#include <bits/stdc++.h>

typedef long long ll;
const int maxN = 5E5 + 5, maxM = 710, n = 5E5;

int arr[maxN];
ll sq[maxM][maxM];

inline void update(int idx, int v)
{
    arr[idx] += v;
    for(int i = 1; i < maxM; ++i)
        sq[i][idx % i] += v;
}

inline ll query(int x, int y)
{
    if(x < maxM) return sq[x][y];
    ll res = 0;
    while(y <= n)
    {
        res += arr[y];
        y += x;
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q, x, y, t;
    std::cin >> q;
    for(int i = 0; i < q; ++i)
    {
        std::cin >> t >> x >> y;
        if(t == 1) update(x, y);
        else std::cout << query(x, y) << '\n';
    }
    return 0;
}