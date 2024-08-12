// # 【模板】动态树（LCT）

// ## 题目描述

// 给定 $n$ 个点以及每个点的权值，要你处理接下来的 $m$ 个操作。  
// 操作有四种，操作从 $0$ 到 $3$ 编号。点从 $1$ 到 $n$ 编号。


// - `0 x y` 代表询问从 $x$ 到 $y$ 的路径上的点的权值的 $\text{xor}$ 和。保证 $x$ 到 $y$ 是联通的。
// - `1 x y` 代表连接 $x$ 到 $y$，若 $x$ 到 $y$ 已经联通则无需连接。
// - `2 x y` 代表删除边 $(x,y)$，不保证边 $(x,y)$ 存在。
// - `3 x y` 代表将点 $x$ 上的权值变成 $y$。

// ## 输入格式

// 第一行两个整数，分别为 $n$ 和 $m$，代表点数和操作数。

// 接下来 $n$ 行，每行一个整数，第 $(i + 1)$ 行的整数 $a_i$ 表示节点 $i$ 的权值。

// 接下来 $m$ 行，每行三个整数，分别代表操作类型和操作所需的量。

// ## 输出格式

// 对于每一个 $0$ 号操作，你须输出一行一个整数，表示 $x$ 到 $y$ 的路径上点权的 $\text{xor}$ 和。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 3 
// 1
// 2
// 3
// 1 1 2
// 0 1 2 
// 0 1 1
// ```

// ### 样例输出 #1

// ```
// 3
// 1
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 5 14
// 114
// 514
// 19
// 19
// 810
// 1 1 2
// 0 1 2
// 2 1 2
// 1 1 2
// 1 2 3
// 2 1 3
// 1 1 3
// 1 4 5
// 1 2 5
// 0 3 5
// 0 3 4
// 3 5 233333
// 0 1 5
// 0 2 5
// ```

// ### 样例输出 #2

// ```
// 624
// 315
// 296
// 232709
// 232823
// ```

// ## 提示

// #### 数据规模与约定

// 对于全部的测试点，保证：
// - $1 \leq n \leq 10^5$，$1 \leq m \leq 3 \times 10^5$，$1 \leq a_i \leq 10^9$。
// - 对于操作 $0, 1, 2$，保证 $1 \leq x, y \leq n$。
// - 对于操作 $3$，保证 $1 \leq x \leq n$，$1 \leq y \leq 10^9$。# 【模板】动态树（LCT）

// ## 题目描述

// 给定 $n$ 个点以及每个点的权值，要你处理接下来的 $m$ 个操作。  
// 操作有四种，操作从 $0$ 到 $3$ 编号。点从 $1$ 到 $n$ 编号。


// - `0 x y` 代表询问从 $x$ 到 $y$ 的路径上的点的权值的 $\text{xor}$ 和。保证 $x$ 到 $y$ 是联通的。
// - `1 x y` 代表连接 $x$ 到 $y$，若 $x$ 到 $y$ 已经联通则无需连接。
// - `2 x y` 代表删除边 $(x,y)$，不保证边 $(x,y)$ 存在。
// - `3 x y` 代表将点 $x$ 上的权值变成 $y$。

// ## 输入格式

// 第一行两个整数，分别为 $n$ 和 $m$，代表点数和操作数。

// 接下来 $n$ 行，每行一个整数，第 $(i + 1)$ 行的整数 $a_i$ 表示节点 $i$ 的权值。

// 接下来 $m$ 行，每行三个整数，分别代表操作类型和操作所需的量。

// ## 输出格式

// 对于每一个 $0$ 号操作，你须输出一行一个整数，表示 $x$ 到 $y$ 的路径上点权的 $\text{xor}$ 和。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 3 
// 1
// 2
// 3
// 1 1 2
// 0 1 2 
// 0 1 1
// ```

// ### 样例输出 #1

// ```
// 3
// 1
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 5 14
// 114
// 514
// 19
// 19
// 810
// 1 1 2
// 0 1 2
// 2 1 2
// 1 1 2
// 1 2 3
// 2 1 3
// 1 1 3
// 1 4 5
// 1 2 5
// 0 3 5
// 0 3 4
// 3 5 233333
// 0 1 5
// 0 2 5
// ```

// ### 样例输出 #2

// ```
// 624
// 315
// 296
// 232709
// 232823
// ```

// ## 提示

// #### 数据规模与约定

// 对于全部的测试点，保证：
// - $1 \leq n \leq 10^5$，$1 \leq m \leq 3 \times 10^5$，$1 \leq a_i \leq 10^9$。
// - 对于操作 $0, 1, 2$，保证 $1 \leq x, y \leq n$。
// - 对于操作 $3$，保证 $1 \leq x \leq n$，$1 \leq y \leq 10^9$。
#include <iostream>
#include <bits/stdc++.h>
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
#define get(x) (ch[fa[x]][1] == x)
#define isRoot(x) (ch[fa[x]][get(x)] != x)

const int maxN = 1E5 + 5;
int ch[maxN][2], fa[maxN], w[maxN], xOr[maxN], s[maxN];
bool tag[maxN];

inline void pushDown(int x){
    if(tag[x]){
        std::swap(ls(ls(x)), rs(ls(x)));
        std::swap(ls(rs(x)), rs(rs(x)));
        tag[ls(x)] ^= 1, tag[rs(x)] ^= 1;
        tag[x] = 0;
    }
}

inline void pushUp(int x){
    xOr[x] = w[x] ^ xOr[ls(x)] ^ xOr[rs(x)];
}

inline void rotate(int x){
    int y = fa[x], z = fa[y], k = get(x);
    if(!isRoot(y)) ch[z][get(y)] = x;
    if(ch[x][!k]) fa[ch[x][!k]] = y;
    ch[y][k] = ch[x][!k], ch[x][!k] = y;
    fa[y] = x, fa[x] = z;
    pushUp(y), pushUp(x);
}

inline void updata(int x){
    int idx = 0;
    s[++idx] = x;
    while(!isRoot(x)) x = fa[x], s[++idx] = x;
    while(idx) pushDown(s[idx--]);
}

inline void splay(int x){
    updata(x);
    for(int f = fa[x]; !isRoot(x); rotate(x), f = fa[x]){
        if(!isRoot(f)) rotate((get(x) ^ get(f))? x:f);
    }
}

inline int access(int x){
    int p;
    for(p = 0; x; p = x, x = fa[p]){
        splay(x);
        rs(x) = p;
        pushUp(x);
    }
    return p;
}

inline void makeRoot(int x){
    access(x);
    splay(x);
    std::swap(ls(x), rs(x));
    tag[x] ^= 1;
}

inline void split(int x, int y){
    makeRoot(x);
    access(y);
    splay(y);
}

inline int findRoot(int x){
    access(x);
    splay(x);
    while(ls(x)) pushDown(x), x = ls(x);
    splay(x);
    return x;
}

inline void link(int x, int y){
    makeRoot(x);
    if(findRoot(y) != x) fa[x] = y;
}

inline void cut(int x, int y){
    makeRoot(x);
    if(findRoot(y) != x || fa[y] != x || ls(y)) return ;
    fa[y] = rs(x) = 0;
    pushUp(x);
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, x, y, op;
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    for(int i = 0; i < m; i++){
        std::cin >> op >> x >> y;
        if(!op){
            split(x, y);
            std::cout << xOr[y] << '\n';
        }
        else if(op == 1){
            link(x, y);
        }
        else if(op == 2){
            cut(x, y);
        }
        else if(op == 3){
            splay(x), w[x] = y;
        }
    }
    return 0;
}