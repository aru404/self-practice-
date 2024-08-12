// # [NOI2021] 轻重边

// ## 题目描述

// 小 W 有一棵 $n$ 个结点的树，树上的每一条边可能是轻边或者重边。接下来你需要对树进行 $m$ 次操作，在所有操作开始前，树上所有边都是轻边。操作有以下两种：
// 1. 给定两个点 $a$ 和 $b$，首先对于 $a$ 到 $b$ 路径上的所有点 $x$（包含 $a$ 和 $b$），你要将与 $x$ 相连的所有边变为轻边。然后再将 $a$ 到 $b$ 路径上包含的所有边变为重边。
// 2. 给定两个点 $a$ 和 $b$，你需要计算当前 $a$ 到 $b$ 的路径上一共包含多少条重边。

// ## 输入格式

// 本题有多组数据，输入数据第一行一个正整数 $T$，表示数据组数。对于每组数据：

// 第一行包含两个整数 $n$ 和 $m$，其中 $n$ 表示结点数量，$m$ 表示操作数量。

// 接下来 $n - 1$ 行，每行包含两个整数 $u\ v$，表示树上的一条边。

// 接下来 $m$ 行，每行包含三个整数 ${\mathit{op}}_i\ a_i\ b_i$，描述一个操作，其中 ${\mathit{op}}_i = 1$ 表示第 $1$ 类操作，${\mathit{op}}_i = 2$ 表示第 $2$ 类操作。

// 数据保证 $a_i \neq b_i$。

// ## 输出格式

// 对于每一次第 $2$ 类操作，输出一行一个整数表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 1
// 7 7
// 1 2
// 1 3
// 3 4
// 3 5
// 3 6
// 6 7
// 1 1 7
// 2 1 4
// 2 2 7
// 1 1 5
// 2 2 7
// 1 2 1
// 2 1 7
// ```

// ### 样例输出 #1

// ```
// 1
// 3
// 2
// 1
// ```

// ## 提示

// **【样例解释 #1】**

// 第 $1$ 次操作后，重边有：$(1, 3)$，$(3, 6)$，$(6, 7)$。

// 第 $2$ 次操作，包含的重边有：$(1, 3)$。

// 第 $3$ 次操作，包含的重边有：$(1, 3)$，$(3, 6)$，$(6, 7)$。

// 第 $4$ 次操作，首先 $(1, 3)$，$(3, 6)$ 变为轻边，之后 $(1, 3)$，$(3, 5)$ 变为重边。

// 第 $5$ 次操作，包含的重边有：$(1, 3)$，$(6, 7)$。

// 第 $6$ 次操作，首先 $(1, 3)$ 变为轻边，之后 $(1, 2)$ 变为重边。

// 第 $7$ 次操作，包含的重边有：$(6, 7)$。

// **【样例 #2】**

// 见附件 `edge/edge2.in` 与 `edge/edge2.ans`。

// 该样例约束与测试点 $3 \sim 6$ 一致。

// **【样例 #3】**

// 见附件 `edge/edge3.in` 与 `edge/edge3.ans`。

// 该样例约束与测试点 $9 \sim 10$ 一致。

// **【样例 #4】**

// 见附件 `edge/edge4.in` 与 `edge/edge4.ans`。

// 该样例约束与测试点 $11 \sim 14$ 一致。

// **【样例 #5】**

// 见附件 `edge/edge5.in` 与 `edge/edge5.ans`。

// 该样例约束与测试点 $17 \sim 20$ 一致。

// **【数据范围】**

// 对于所有测试数据：$T \le 3$，$1 \le n, m \le {10}^5$。

// | 测试点编号 | $n, m \le $ | 特殊性质 |
// |:-:|:-:|:-:|
// | $1 \sim 2$ | $10$ | 无 |
// | $3 \sim 6$ | $5000$ | 无 |
// | $7 \sim 8$ | ${10}^5$ | A，B |
// | $9 \sim 10$ | ${10}^5$ | A |
// | $11 \sim 14$ | ${10}^5$ | B |
// | $15 \sim 16$ | $2\times {10}^4$ | 无 |
// | $17 \sim 20$ | ${10}^5$ | 无 |

// 特殊性质 A：树的形态是一条链。

// 特殊性质 B：第 $2$ 类操作给出的 $a_i$ 和 $b_i$ 之间有边直接相连。
#include <iostream>
#include <bits/stdc++.h>
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
#define get(x) (ch[f[x]][1] == x)
#define isRoot(x) (ch[f[x]][get(x)] != x)

const int maxN = 1E5 + 5;
int ch[maxN][2], f[maxN], s[maxN], sz[maxN];
bool tag[maxN];

inline void pushUp(int x){
    sz[x] = 1 + sz[ls(x)] + sz[rs(x)];
}

inline void pushDown(int x){
    if(tag[x]){
        std::swap(ls(ls(x)), rs(ls(x)));
        std::swap(ls(rs(x)), rs(rs(x)));
        tag[ls(x)] ^= 1, tag[rs(x)] ^= 1;
        tag[x] = 0;
    }
} 

inline void rotate(int x){
    int y = f[x], z = f[y], k = get(y);
    if(!isRoot(y)) ch[z][get(y)] = x;
    if(ch[x][!k]) f[ch[x][!k]] = y;
    ch[y][k] = ch[x][!k], ch[x][!k] = y;
    f[y] = x, f[x] = z;
    pushUp(y), pushUp(x);
}

inline void updata(int x){
    int idx = 0;
    s[++idx] = x;
    while(!isRoot(x)) x = f[x], s[++idx] = x;
    while(idx) pushDown(s[idx--]);
}

inline void splay(int x){
    updata(x);
    for(int fa = f[x]; !isRoot(x); rotate(x), fa = f[x]){
        if(!isRoot(fa)) rotate(get(x) ^ get(fa)? x:fa);
    }
}

inline int access(int x){
    int p;
    for(p = 0; x; p = x, x = f[x]){
        splay(x);
        rs(x) = p;
        pushUp(x);
    }
    return p;
}

inline void makeRoot(int x){
    access(x);
    splay(x);
    tag[x] ^= 1;
    std::swap(ls(x), rs(x));
}

inline int findRoot(int x){
    access(x);
    splay(x);
    while(ls(x)) pushDown(x), x = ls(x);
    splay(x);
    return x;
}

//拉出一颗新的splay
inline void split(int x, int y){
    makeRoot(x);
    access(y);
    splay(y);
}

// 连虚边
inline void link(int x, int y){
    makeRoot(x);
    f[x] = y;
}

inline int cnt(int x, int y){
    while(){
        
    }
}

int main(){

}