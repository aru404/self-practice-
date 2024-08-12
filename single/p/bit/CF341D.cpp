// # Iahub and Xors

// ## 题面翻译

// - 给定一个初始值全为 $0$ 的 $n^2$ 矩阵，有 $m$ 次操作，有以下类型：
//     - `1 x1 y1 x2 y2`：查询 $(x_1,y_1)$ 到 $(x_2,y_2)$ 的区间异或和。
//     - `2 x1 y1 x2 y2 w`：将 $(x_1,y_1)$ 到 $(x_2,y_2)$ 的区间异或上 $w$。
// - 对于 $100\%$ 的数据，$1 \le n \le 1000$，$1 \le m \le 10^5$，$0 \le w \le 2^{62}$，$1 \le x_1\le x_2 \le n$，$1 \le y_1 \le y_2 \le n$。

// ## 题目描述

// Iahub does not like background stories, so he'll tell you exactly what this problem asks you for.

// You are given a matrix $ a $ with $ n $ rows and $ n $ columns. Initially, all values of the matrix are zeros. Both rows and columns are 1-based, that is rows are numbered 1, 2, ..., $ n $ and columns are numbered 1, 2, ..., $ n $ . Let's denote an element on the $ i $ -th row and $ j $ -th column as $ a_{i,j} $ .

// We will call a submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ such elements $ a_{i,j} $ for which two inequalities hold: $ x_{0}<=i<=x_{1} $ , $ y_{0}<=j<=y_{1} $ .

// Write a program to perform two following operations:

// 1. Query( $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ ): print the xor sum of the elements of the submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ .
// 2. Update( $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ , $ v $ ): each element from submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ gets xor-ed by value $ v $ .

// ## 输入格式

// The first line contains two integers: $ n $ ( $ 1<=n<=1000 $ ) and $ m $ ( $ 1<=m<=10^{5} $ ). The number $ m $ represents the number of operations you need to perform. Each of the next $ m $ lines contains five or six integers, depending on operation type.

// If the $ i $ -th operation from the input is a query, the first number from $ i $ -th line will be 1. It will be followed by four integers $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ . If the $ i $ -th operation is an update, the first number from the $ i $ -th line will be 2. It will be followed by five integers $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ , $ v $ .

// It is guaranteed that for each update operation, the following inequality holds: $ 0<=v<2^{62} $ . It is guaranteed that for each operation, the following inequalities hold: $ 1<=x_{0}<=x_{1}<=n $ , $ 1<=y_{0}<=y_{1}<=n $ .

// ## 输出格式

// For each query operation, output on a new line the result.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 5
// 2 1 1 2 2 1
// 2 1 3 2 3 2
// 2 3 1 3 3 3
// 1 2 2 3 3
// 1 2 2 3 2
// ```

// ### 样例输出 #1

// ```
// 3
// 2
// ```

// ## 提示

// After the first $ 3 $ operations, the matrix will look like this:

// ```
// 1 1 2
// 1 1 2
// 3 3 3
// ```
// The fourth operation asks us to compute 1 xor 2 xor 3 xor 3 = 3.

// The fifth operation asks us to compute 1 xor 3 = 2.
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

namespace BITs{
    #define lowbit(x) (x & -x)

    class BIT{
    private:
        int n;
        ll ***tree;

        inline void updata(int, int, ll);

        inline ll query(int, int);
    public:
        BIT(int);

        ~BIT();

        inline void updata(int, int, int, int, ll);

        inline ll query(int, int, int, int);
    };
    
    BIT::BIT(int m){
        n = m;
        tree = new ll**[4];
        for(int i = 0; i < 4; i++){
            tree[i] = new ll*[n + 1];
            for(int j = 0; j <= n; j++) tree[i][j] = new ll[n + 1]{};
        }
    }
    
    BIT::~BIT(){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j <= n; j++) delete[] tree[i][j];
            delete[] tree[i];
        }
        delete[] tree;
    }
    
    inline void BIT::updata(int x, int y, ll v){
        ll v3 = x * y % 2 * v, v2 = y % 2 * v, v1 = x % 2 * v;
        while(x <= n){
            int z = y;
            while(z <= n) tree[3][x][z] ^= v3, tree[2][x][z] ^= v2, tree[1][x][z] ^= v1, tree[0][x][z] ^= v, z += lowbit(z);
            x += lowbit(x);
        }
    }

    inline void BIT::updata(int x1, int y1, int x2, int y2, ll v){
        updata(x1, y1, v), updata(x1, y2 + 1, v), updata(x2 + 1, y1, v), updata(x2 + 1, y2 + 1, v);
    }

    inline ll BIT::query(int x, int y){
        int f0 = (x + 1) * (y + 1) % 2, f1 = (y + 1) % 2, f2 = (x + 1) % 2;
        ll res = 0;
        while(x){
            int z = y;
            while(z) res ^= tree[3][x][z] ^ (f2 * tree[2][x][z]) ^ (f1 * tree[1][x][z]) ^ (f0 * tree[0][x][z]), z -= lowbit(z);
            x -= lowbit(x);
        }
        return res;
    }

    inline ll BIT::query(int x1, int y1, int x2, int y2){
        return query(x1 - 1, y1 - 1) ^ query(x1 - 1, y2) ^ query(x2, y1 - 1) ^ query(x2, y2);
    } 
} // namespace BITs


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, x1, y1, x2, y2, op;
    ll v;

    std::cin >> n >> m;
    BITs::BIT tree(n);

    for(int i = 0; i < m; i++){
        std::cin >> op >> x1 >> y1 >> x2 >> y2;
        if(op == 1) std::cout << tree.query(x1, y1, x2, y2) << '\n';
        else std::cin >> v, tree.updata(x1, y1, x2, y2, v);
    }

    return 0;
}