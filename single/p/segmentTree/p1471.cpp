// # 方差

// ## 题目背景

// 滚粗了的 HansBug 在收拾旧数学书，然而他发现了什么奇妙的东西。

// ## 题目描述

// 蒟蒻 HansBug 在一本数学书里面发现了一个神奇的数列，包含 $N$ 个实数。他想算算这个数列的平均数和方差。

// ## 输入格式

// 第一行包含两个正整数 $N,M$，分别表示数列中实数的个数和操作的个数。

// 第二行包含 $N$ 个实数，其中第 $i$ 个实数表示数列的第 $i$ 项。

// 接下来 $M$ 行，每行为一条操作，格式为以下三种之一：

// 操作 $1$：`1 x y k` ，表示将第 $x$ 到第 $y$ 项每项加上 $k$，$k$ 为一实数。  
// 操作 $2$：`2 x y` ，表示求出第 $x$ 到第 $y$ 项这一子数列的平均数。  
// 操作 $3$：`3 x y` ，表示求出第 $x$ 到第 $y$ 项这一子数列的方差。

// ## 输出格式

// 输出包含若干行，每行为一个实数，即依次为每一次操作 $2$ 或操作 $3$ 所得的结果（所有结果四舍五入保留 $4$ 位小数）。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 5
// 1 5 4 2 3
// 2 1 4
// 3 1 5
// 1 1 1 1
// 1 2 2 -1
// 3 1 5
// ```

// ### 样例输出 #1

// ```
// 3.0000
// 2.0000
// 0.8000
// ```

// ## 提示

// 关于方差：对于一个有 $n$ 项的数列 $A$，其方差 $s^2$ 定义如下：
// $$s^2=\frac{1}{n}\sum\limits_{i=1}^n\left(A_i-\overline A\right)^2$$
// 其中 $\overline A$ 表示数列 $A$ 的平均数，$A_i$ 表示数列 $A$ 的第 $i$ 项。

// 样例说明：
// | 操作步骤 | 输入内容 | 操作要求 | 数列 | 输出结果 | 说明 |
// | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
// | $0$ | - | - | `1 5 4 2 3` | - | - |
// | $1$ | `2 1 4` | 求 $\left[1,4\right]$ 内所有数字的平均数 | `1 5 4 2 3` | `3.0000` | 平均数 $=\left(1+5+4+2\right)\div 4=3.0000$ |
// | $2$ | `3 1 5` | 求 $\left[1,5\right]$ 内所有数字的方差 | `1 5 4 2 3` | `2.0000` | 平均数 $=\left(1+5+4+2+3\right)\div 5=3$，方差 $=\left(\left(1-3\right)^2+\left(5-3\right)^2+\left(4-3\right)^2+\left(2-3\right)^2+\left(3-3\right)^2\right)\div 5=2.0000$ |
// | $3$ | `1 1 1 1` | 将 $\left[1,1\right]$ 内所有数字加 $1$ | `2 5 4 2 3` | - | - |
// | $4$ | `1 2 2 -1` | 将 $\left[2,2\right]$ 内所有数字加 $-1$ | `2 4 4 2 3` | - | - |
// | $5$ | `3 1 5` | 求 $\left[1,5\right]$ 内所有数字的方差 | `2 4 4 2 3` | `0.8000` | 平均数 $=\left(2+4+4+2+3\right)\div 5=3$，方差 $=\left(\left(2-3\right)^2+\left(4-3\right)^2+\left(4-3\right)^2+\left(2-3\right)^2+\left(3-3\right)^2\right)\div 5=0.8000$ |

// 数据规模：
// | 数据点 | $N$ | $M$ | 备注 |
// | :----------: | :----------: | :----------: | :----------: |
// | $1\sim3$ | $N\le 8$ | $M\le 15$ | - |
// | $4\sim7$ | $N\le 10^5$ | $M\le 10^5$ | 不包含操作 $3$|
// | $8\sim10$ | $N\le 10^5$ | $M\le 10^5$ | - |
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E5 + 5;
const double delta = 1E-5;
double sum[maxN << 2], sq[maxN << 2], lz[maxN << 2], w[maxN];

inline void pushUp(int p){
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
    sq[p] = sq[p << 1] + sq[p << 1 | 1];
}

inline void pushDown(int s, int t, int m, int p){
    if(lz[p]){
        sq[p << 1] += 2 * lz[p] * sum[p << 1] + (m - s + 1) * lz[p] * lz[p];
        sq[p << 1 | 1] += 2 * lz[p] * sum[p << 1 | 1] + (t - m) * lz[p] * lz[p];
        sum[p << 1] += (m - s + 1) * lz[p];
        sum[p << 1 | 1] += (t - m) * lz[p];
        lz[p << 1] += lz[p], lz[p << 1 | 1] += lz[p];
        lz[p] = 0;
    }
}

inline void buildTree(int s, int t, int p){
    if(s == t){
        sum[p] = w[s];
        sq[p] = w[s] * w[s];
        return ;
    }
    int m = (t + s) >> 1;
    buildTree(s, m, p << 1);
    buildTree(m + 1, t, p << 1 | 1);
    pushUp(p);
}

inline void updata(int l, int r, double k, int s, int t, int p){
    if(l <= s && r >= t){
        sq[p] += 2 * k * sum[p] + (t - s + 1) * k * k;
        sum[p] += (t - s + 1) * k;
        lz[p] += k;
        return ;
    }
    int m = (t + s) >> 1;
    pushDown(s, t, m, p);
    if(l <= m) updata(l, r, k, s, m, p << 1);
    if(r > m) updata(l, r, k, m + 1, t, p << 1 | 1);
    pushUp(p);
}

inline double querySq(int l, int r, int s, int t, int p){
    if(l <= s && r >= t) return sq[p];
    int m = (t + s) >> 1; double res = 0;
    pushDown(s, t, m, p);
    if(l <= m) res += querySq(l, r, s, m, p << 1);
    if(r > m) res += querySq(l, r, m + 1, t, p << 1 | 1);
    return res;
} 

inline double querySum(int l, int r, int s, int t, int p){
    if(l <= s && r >= t) return sum[p];
    int m = (t + s) >> 1; double res = 0;
    pushDown(s, t, m, p);
    if(l <= m) res += querySum(l, r, s, m, p << 1);
    if(r > m) res += querySum(l, r, m + 1, t,  p << 1 | 1);
    return res;
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, m, op, l, r;
    double k;
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    buildTree(1, n, 1);
    for(int i = 0; i < m; i++){
        std::cin >> op >> l >> r;
        if(op == 1){
            std::cin >> k;
            updata(l, r, k, 1, n, 1);
        }
        else if(op == 2){
            std::cout << std::fixed << std::setprecision(4) << querySum(l, r, 1, n, 1) / (r - l + 1) << std::endl;
        }
        else{
            double x1 = querySq(l, r, 1, n, 1) / (r - l + 1), x2 = querySum(l, r, 1, n, 1) / (r - l + 1);
            std::cout << std::fixed << std::setprecision(4) << x1 - x2 * x2 << std::endl;
        }
    }
    return 0;
}