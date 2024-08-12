// # 首都

// ## 题目描述

// 在 X 星球上有 $n$ 个国家，每个国家占据着 X 星球的一座城市，城市从 $1$ 至 $n$ 编号。由于国家之间是敌对关系，所以不同国家的两个城市是不会有公路相连的。

// X 星球上战乱频发，如果 A 国打败了 B 国，那么 B 国将永远从这个星球消失，而 B 国的国土也将归 A 国管辖。A 国国王为了加强统治，会在 A 国和 B 国之间修建一条公路，即选择原 A 国的某个城市和 B 国某个城市，修建一条连接这两座城市的公路。

// 同样为了便于统治自己的国家，国家的首都会选在某个使得其他城市到它距离之和最小的城市，这里的距离是指需要经过公路的条数，如果有多个这样的城市，编号最小的将成为首都。

// 现在告诉你发生在 X 星球的战事，需要你处理一些关于国家首都的信息，具体地，有如下3种信息需要处理：

// - `A x y`：表示某两个国家发生战乱，战胜国选择了 $x$ 城市和 $y$ 城市，在它们之间修建公路（保证其中城市一个在战胜国另一个在战败国）。
// - `Q x`：询问当前编号为 $x$ 的城市所在国家的首都。
// - `Xor`：询问当前所有国家首都编号的异或和。

// ## 输入格式

// 输入的第一行有两个整数，分别表示城市数 $n$ 和需要处理的信息数 $m$。

// 接下来 $m$ 行，每行首先有一个字符串 $op$，表示信息类型，后有若干个整数，其格式如【题目描述】所示。

// ## 输出格式

// 对于每个 `Q` 操作和 `Xor` 操作，输出一行一个整数表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 10 10 
// Xor 
// Q 1 
// A 10 1 
// A 1 4 
// Q 4 
// Q 10 
// A 7 6 
// Xor 
// Q 7 
// Xor
// ```

// ### 样例输出 #1

// ```
// 11 
// 1 
// 1 
// 1 
// 2 
// 6 
// 2
// ```

// ## 提示

// #### 数据规模与约定

// 对于全部的测试点，保证 $1 \leq n \leq 10^5$，$1 \leq m \leq 2 \times 10^5$，$1 \leq x, y \leq n$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E5 + 5;

namespace LCT{
    #define ls(x) ch[x][0]
    #define rs(x) ch[x][1]
    #define get(x) (ch[f[x]][1] == x)
    #define isRoot(x) (ch[f[x]][get(x)] != x)

    int f[maxN], ch[maxN][2], sz[maxN], sos[maxN], mx[maxN], s[maxN];
    bool tag[maxN];

    inline void pushUp(int x){
        sz[x] = sz[ls(x)] + sz[rs(x)] + sos[x] + 1;
        mx[x] = std::max(sz[rs(x)], mx[x]);
    }

    inline void pushDown(int x){
        if(tag[x]){
            if(ls(x)) std::swap(ls(ls(x)), rs(ls(x))), tag[ls(x)] ^= 1;
            if(rs(x)) std::swap(ls(rs(x)), rs(rs(x))), tag[rs(x)] ^= 1;
            tag[x] = 0;
        }
    }

    inline void rotate(int x){
        int y = f[x], z = f[y], k = get(x);
        if(!isRoot(y)) ch[z][get(y)] = x;
        if(ch[x][!k]) f[ch[x][!k]] = y;
        ch[y][k] = ch[x][!k], ch[x][!k] = y;
        f[x] = z, f[y] = x;
        pushUp(y), pushUp(x);
    }

    inline void updata(int x){
        int idx = 0;
        s[++idx] = x;
        while(!isRoot(x)) x = f[x], s[++idx] = x;
        while(idx) pushDown();
    }

    inline void splay(int x){
        update(x);
    }
} // namespace LCT


int main(){

}