// # [JSOI2009] 计数问题

// ## 题目描述

// 一个 $n \times\ m$ 的方格，初始时每个格子有一个整数权值。接下来每次有 2 种操作：

// - 改变一个格子的权值；

// - 求一个子矩阵中某种特定权值出现的个数。

// ## 输入格式

// 第一行有两个数 $n,m$。

// 接下来 $n$ 行，每行 $m$ 个数，第 $i+1$ 行第 $j$ 个数表示格子 $(i,j)$ 的初始权值。

// 接下来输入一个整数 $Q$。

// 之后 $Q$ 行，每行描述一个操作。

// 操作 1：输入一行四个整数 $1\ x\ y\ c$，表示将格子 $(x,y)$ 的权值改成 $c$。

// 操作 2：输入一行六个整数 $2\ x_1\ x_2\ y_1\ y_2\ c$。表示询问所有满足格子颜色为 $c$，且满足 $x_1\le x\le x_2,y_1\le y\le y_2$ 的格子个数。

// ## 输出格式

// 对于每个操作 2，按照在输入中出现的顺序，依次输出一行一个整数表示所求得的个数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 3
// 1 2 3
// 3 2 1
// 2 1 3
// 3
// 2 1 2 1 2 1
// 1 2 3 2
// 2 2 3 2 3 2
// ```

// ### 样例输出 #1

// ```
// 1
// 2
// ```

// ## 提示

// 【数据规模与约定】

// 对于 $30\%$ 的数据，满足：$n,m\le 30$，$Q\le 5\times 10^4$。

// 对于 $100\%$ 的数据，满足：$1\le n,m\le 300$，$1\le Q\le 2\times 10^5$。

// 对于操作 1，保证：$1\le x
// \le n$，$1\le y\le m$，$1\le c\le 100$；

// 对于操作 2，保证：$1\le x_1≤x_2\le n$，$1\le y_1\le y_2\le m$，$1\le c\le 100$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 3E2 + 5, maxC = 1E2 + 2;
namespace BIT{
    #define lowbit(x) (x & -x)

    int bit[maxC][maxN][maxN], n, m;

    inline void updata(int x, int y, int v, int c){
        while(x <= n){
            int tmp = y;
            while(tmp <= m) bit[c][x][tmp] += v, tmp += lowbit(tmp);
            x += lowbit(x);
        }
    }

    inline int query(int x1, int x2, int y1, int y2, int c){
        int res = 0;
        --y1;
        while(x2){
            int tmp = y2;
            while(tmp) res += bit[c][x2][tmp], tmp -= lowbit(tmp);
            tmp = y1;
            while(tmp) res -= bit[c][x2][tmp], tmp -= lowbit(tmp);
            x2 -= lowbit(x2);
        }
        --x1;
        while(x1){
            int tmp = y2;
            while(tmp) res -= bit[c][x1][tmp], tmp -= lowbit(tmp);
            tmp = y1;
            while(tmp) res += bit[c][x1][tmp], tmp -= lowbit(tmp);
            x1 -= lowbit(x1);
        }
        return res;
    }
}

int w[maxN][maxN];

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q, c, x1, x2, y1, y2, op;
    std::cin >> BIT::n >> BIT::m;
    for(int i = 1; i <= BIT::n; i++){
        for(int j = 1; j <= BIT::m; j++){
            std::cin >> w[i][j];
            BIT::updata(i, j, 1, w[i][j]);
        }
    }
    std::cin >> q;
    for(int i = 0; i < q; i++){
        std::cin >> op;
        if(op == 1){
            std::cin >> x1 >> y1 >> c;
            BIT::updata(x1, y1, -1, w[x1][y1]);
            BIT::updata(x1, y1, 1, w[x1][y1] = c);
        }
        else{
            std::cin >> x1 >> x2 >> y1 >> y2 >> c;
            std::cout << BIT::query(x1, x2, y1, y2, c) << '\n';
        }
    }
    return 0;
}