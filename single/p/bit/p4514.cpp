// # 上帝造题的七分钟

// ## 题目背景

// 裸体就意味着身体。

// ## 题目描述

// “第一分钟，X 说，要有矩阵，于是便有了一个里面写满了 $0$ 的 $n\times m$ 矩阵。

// 第二分钟，L 说，要能修改，于是便有了将左上角为 $(a,b)$，右下角为 $(c,d)$ 的一个矩形区域内的全部数字加上一个值的操作。

// 第三分钟，k 说，要能查询，于是便有了求给定矩形区域内的全部数字和的操作。

// 第四分钟，彩虹喵说，要基于二叉树的数据结构，于是便有了数据范围。

// 第五分钟，和雪说，要有耐心，于是便有了时间限制。

// 第六分钟，吃钢琴男说，要省点事，于是便有了保证运算过程中及最终结果均不超过 $32$ 位有符号整数类型的表示范围的限制。

// 第七分钟，这道题终于造完了，然而，造题的神牛们再也不想写这道题的程序了。”。

// ——《上帝造裸题的七分钟》。

// 所以这个神圣的任务就交给你了。

// ## 输入格式

// 输入数据的第一行为 `X n m`，代表矩阵大小为 $n\times m$。  
// 从输入数据的第二行开始到文件尾的每一行会出现以下两种操作：  
// -    `L a b c d delta` —— 代表将 $(a,b),(c,d)$ 为顶点的矩形区域内的所有数字加上 $delta$。  
// -    `k a b c d`     —— 代表求 $(a,b),(c,d)$ 为顶点的矩形区域内所有数字的和。  

// 请注意，$k$ 为小写。

// ## 输出格式

// 针对每个 $k$ 操作，在单独的一行输出答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// X 4 4
// L 1 1 3 3 2
// L 2 2 4 4 1
// k 2 2 3 3
// ```

// ### 样例输出 #1

// ```
// 12
// ```

// ## 提示

// 对于 $10\%$ 的数据，$1 \le n \le 16$，$1 \le m \le 16$， 操作不超过 $200$ 个。

// 对于 $60\%$ 的数据，$1 \le n \le 512$，$1 \le m \le 512$。

// 对于 $100\%$ 的数据，$1 \le n \le 2048$，$1 \le m \le 2048$，$-500 \le delta \le 500$，操作不超过 $2\times 10^5$ 个，保证运算过程中及最终结果均不超过 $32$ 位带符号整数类型的表示范围。
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

namespace BITs{
    #define lowbit(x) (x & -x)

    class BIT{
    private:
        int ***tree;
        int n, m;

        inline void updata(int, int, int);

        inline int query(int, int);
    public:
        BIT(int, int);

        ~BIT();

        inline void updata(int, int, int, int, int);

        inline int query(int, int, int, int);
    };
    
    BIT::BIT(int r, int c){
        m = r, n = c;
        tree = new int**[4];
        for(int i = 0; i < 4; i++){
            tree[i] = new int*[m + 1];
            for(int j = 0; j <= m; j++) tree[i][j] = new int[n + 1]{};
        }
    }
    
    BIT::~BIT(){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j <= m; j++) delete[] tree[i][j];
            delete[] tree[i];
        }
        delete[] tree;
    }

    inline void BIT::updata(int x, int y, int v){
        if(!x || !y || x > m || y > n) return ;
        int v4 = x * y * v, v3 = x * v, v2 = y * v;
        while(x <= m){
            int z = y;
            while(z <= n) tree[0][x][z] += v, tree[1][x][z] += v2, tree[2][x][z] += v3, tree[3][x][z] += v4, z += lowbit(z);
            x += lowbit(x);
        }
    }

    inline void BIT::updata(int x1, int y1, int x2, int y2, int v){
        updata(x1, y1, v), updata(x2 + 1, y1, -v), updata(x1, y2 + 1, -v), updata(x2 + 1, y2 + 1, v);
    }

    inline int BIT::query(int x, int y){
        int res = 0, f1 = (x + 1) * (y + 1);
        int f3 = y + 1, f2 = x + 1;
        while(x){
            int z = y;
            while(z) res += tree[3][x][z] - f3 * tree[2][x][z] - f2 * tree[1][x][z] + f1 * tree[0][x][z], z -= lowbit(z);
            x -= lowbit(x);
        }
        return res;
    }

    inline int BIT::query(int x1, int y1, int x2, int y2){
        return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
    }
} // namespace BITs


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, x1, x2, y1, y2, v;
    char op;
    std::cin >> op >> m >> n;
    BITs::BIT tree(m, n);

    while(std::cin >> op){
        std::cin >> x1 >> y1 >> x2 >> y2;
        if(op == 'L') std::cin >> v, tree.updata(x1, y1, x2, y2, v);
        else std::cout << tree.query(x1, y1, x2, y2) << '\n';
    }

    return 0;
}