// # I Hate It

// ## 题目背景

// 很多学校流行一种比较的习惯。老师们很喜欢询问，从某某到某某当中，分数最高的是多少。这让很多学生很反感。

// ## 题目描述

// 不管你喜不喜欢，现在需要你做的是，就是按照老师的要求，写一个程序，模拟老师的询问。当然，老师有时候需要更新某位同学的成绩。

// ## 输入格式

// 第一行，有两个正整数 $n$ 和 $m$（$0<n \le 2\times 10^5,0<m<5000$），分别代表学生的数目和操作的数目。学生 ID 编号分别从 $1$ 编到 $n$。

// 第二行包含 $n$ 个整数，代表这 $n$ 个学生的初始成绩，其中第 $i$ 个数代表 ID 为 $i$ 的学生的成绩。

// 接下来有 $m$ 行。每一行有一个字符 $c$（只取 `Q` 或 `U`），和两个正整数 $a$，$b$。

// - 当 $c$ 为 `Q` 的时候，表示这是一条询问操作，它询问 ID 从 $a$ 到 $b$（包括 $a,b$） 的学生当中，成绩最高的是多少；
// - 当 $c$ 为 `U` 的时候，表示这是一条更新操作，如果当前 $a$ 学生的成绩低于 $b$，则把 ID 为 $a$ 的学生的成绩更改为 $b$，否则不改动。

// ## 输出格式

// 对于每一次询问操作输出一行一个整数，表示最高成绩。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 6
// 1 2 3 4 5
// Q 1 5
// U 3 6
// Q 3 4
// Q 4 5
// U 2 9
// Q 1 5
// ```

// ### 样例输出 #1

// ```
// 5
// 6
// 5
// 9
// ```
#include <iostream>
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

const int maxN = 2E5 + 5;
int w[maxN], mx[maxN], n;

inline void updata(int x, int v){
    if(v <= w[x]) return ;
    w[x] = v;
    while(x <= n) mx[x] = std::max(v, mx[x]), x += lowbit(x);
}

inline int query(int l, int r){
    int res = 0;
    while(r >= l){
        if(r - lowbit(r) >= l) res = std::max(res, mx[r]), r -= lowbit(r);
        else res = std::max(res, w[r]), r--;
    }
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int a, b, m;
    char op;
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++){
        std::cin >> a;
        updata(i, a);
    }
    for(int i = 0; i < m; i++){
        std::cin >> op >> a >> b;
        if(op == 'Q'){
            std::cout << query(a, b) << std::endl;
        }
        else updata(a, b);
    }
    return 0;
}