// # [eJOI2019] 异或橙子

// ## 题目描述

// Janez 喜欢橙子！他制造了一个橙子扫描仪，但是这个扫描仪对于扫描的每个橙子的图像只能输出一个  $32$ 位整数。

// 他一共扫描了 $n$ 个橙子，但有时他也会重新扫描一个橙子，导致这个橙子的 $32$ 位整数发生更新。

// Janez 想要分析这些橙子，他觉得异或操作非常有趣，他每次选取一个区间从 $l$  至 $u$，他想要得到这个区间内所有子区间的异或和的异或和。

// 例如 $l=2,u=4$ 的情况，记橙子序列 $A$ 中第 $i$ 个橙子的整数是 ，那么他要求的就是：

// $$a_2 \oplus a_3 \oplus a_4 \oplus (a_2\oplus a_3)\oplus(a_3\oplus a_4)\oplus(a_2\oplus a_3 \oplus a_4)$$

// -------------------------------------

// 注：式子中的 $\oplus$ 代表按位异或运算。异或的运算规则如下。

// 对于两个数的第 $i$ 位，记为 $x,y$，那么：

// |$x$|$y$|$x\oplus y$|
// | :-----------: | :-----------: | :-----------: |
// |$0$|$1$|$1$|
// |$1$|$0$|$1$|
// |$0$|$0$|$0$|
// |$1$|$1$|$0$|

// 例：$13\oplus 23=26$

// |$13=$|$0\cdots 001101$|
// | --------: | :------: |
// |$23=$|$0\cdots 010111$|
// |$13\oplus 23=$|$0\cdots 011010$|

// ## 输入格式

// 第一行输入两个正整数 $n,q$，表示橙子数量和操作次数。

// 接下来一行 $n$ 个非负整数，表示每个橙子扫描得到的数值 ，从 $1$ 开始编号。

// 接下来 $q$ 行，每行三个数：

// - 如果第一个数是 $1$，接下来输入一个正整数 $i$ 与非负整数 $j$，表示将第 $i$ 个橙子的扫描值 $a_i$ 修改为 $j$。

// - 如果第一个数是 $2$，接下来输入两个正整数 $u,l$ 表示询问这个区间的答案。

// ## 输出格式

// 对于每组询问，输出一行一个非负整数，表示所求的总异或和。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 3
// 1 2 3
// 2 1 3
// 1 1 3
// 2 1 3
// ```

// ### 样例输出 #1

// ```
// 2
// 0
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 5 6
// 1 2 3 4 5
// 2 1 3
// 1 1 3
// 2 1 5
// 2 4 4
// 1 1 1
// 2 4 4
// ```

// ### 样例输出 #2

// ```
// 2
// 5
// 4
// 4
// ```

// ## 提示

// #### 输入输出样例 1 解释

// - 最初，$A=[1,2,3]$，询问结果为 $1\oplus 2\oplus 3\oplus(1\oplus 2)\oplus (2\oplus 3)\oplus(1\oplus 2\oplus 3)=2$

// - 修改后，第一个位置被修改为 $3$ ，询问的结果是 $3\oplus 2\oplus 3\oplus(3\oplus 2)\oplus (2\oplus 3)\oplus(3\oplus 2\oplus 3)=0$。

// ----------------------------

// #### 数据规模与约定：

// **本题采用多测试点捆绑测试，共有 5 个子任务**。

// - Subtask 1(12 points)：$1\le n,q\le 10^2$，无特殊限制
// - Subtask 2(18 points)：$1\le n,q\le 5\times 10^2$，且没有修改操作。
// - Subtask 3(25 points)：$1\le n,q\le 5\times 10^3$，无特殊限制
// - Subtask 4(20 points)：$1\le n,q\le 2\times 10^5$，且没有修改操作。
// - Subtask 5(25 points)：$1\le n,q\le 2\times 10^5$，无特殊限制

// 对于所有数据，$0\le a_i\le 10^9,1\le n,q\le 2\times 10^5$

// --------------------------

// #### 说明

// 原题来自：[eJOI2019](http://ejoi2019.si/) Problem A. [XORanges](https://www.ejoi2019.si/static/media/uploads/tasks/xoranges-isc(1).pdf)

// 题面&数据来自：[LibreOJ](https://loj.ac/problem/3195)
#include <iostream>
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

const int maxN = 2E5 + 5;
int tree1[maxN], tree2[maxN], w[maxN], n;

inline void updata(int x, int v, int* t){
    while(x <= n) t[x] ^= v, x += lowbit(x);
}

inline int query(int x, int* t){
    int res = 0;
    while(x) res ^= t[x], x -= lowbit(x);
    return res;
}

inline int query(int l, int r){
    int len = r - l + 1, res = 0;
    if(len % 2 == 0) return 0;
    int* t = r % 2? tree1:tree2;
    res = query(r, t) ^ query(l - 1, t);
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q, l, r, op;
    std::cin >> n >> q;
    for(int i = 1; i <= n; i++){
        std::cin >> w[i];
        if(i % 2) updata(i, w[i], tree1);
        else updata(i, w[i], tree2);
    }
    for(int i = 0; i < q; i++){
        std::cin >> op >> l >> r;
        if(op == 1){
            if(l % 2) updata(l, w[l] ^ r, tree1);
            else updata(l, w[l] ^ r, tree2);
            w[l] = r;
        }
        else std::cout << query(l, r) << '\n';
    }
    return 0;
}