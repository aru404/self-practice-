// # [NOIP2005 普及组] 校门外的树

// ## 题目描述

// 某校大门外长度为 $l$ 的马路上有一排树，每两棵相邻的树之间的间隔都是 $1$ 米。我们可以把马路看成一个数轴，马路的一端在数轴 $0$ 的位置，另一端在 $l$ 的位置；数轴上的每个整数点，即 $0,1,2,\dots,l$，都种有一棵树。


// 由于马路上有一些区域要用来建地铁。这些区域用它们在数轴上的起始点和终止点表示。已知任一区域的起始点和终止点的坐标都是整数，区域之间可能有重合的部分。现在要把这些区域中的树（包括区域端点处的两棵树）移走。你的任务是计算将这些树都移走后，马路上还有多少棵树。

// ## 输入格式

// 第一行有两个整数，分别表示马路的长度 $l$ 和区域的数目 $m$。

// 接下来 $m$ 行，每行两个整数 $u, v$，表示一个区域的起始点和终止点的坐标。

// ## 输出格式

// 输出一行一个整数，表示将这些树都移走后，马路上剩余的树木数量。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 500 3
// 150 300
// 100 200
// 470 471
// ```

// ### 样例输出 #1

// ```
// 298
// ```

// ## 提示

// **【数据范围】**

// - 对于 $20\%$ 的数据，保证区域之间没有重合的部分。
// - 对于 $100\%$ 的数据，保证 $1 \leq l \leq 10^4$，$1 \leq m \leq 100$，$0 \leq u \leq v \leq l$。

// **【题目来源】**

// NOIP 2005 普及组第二题
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E4 + 5, maxB = 1E2 + 5;
int st[maxB], ed[maxB], inv[maxN], tag[maxB], w[maxN], sz1[maxB], sz2[maxB], nob, re = 0;

inline void init(int n){
    nob = sqrt(n);
    for(int i = 1; i <= nob; i++){
        st[i] = n / nob * (i - 1) + 1;
        ed[i] = n / nob * i;
    }
    ed[nob] = n;
    for(int i = 1; i <= nob; i++){
        for(int j = st[i]; j <= ed[i]; j++) inv[j] = i;
        tag[i] = 2, sz2[i] = ed[i] - st[i] + 1;
    }
}

inline void updata(int v, int l, int r){
    if(inv[l] == inv[r]){
        if((v > 0 && tag[inv[l]] > 0) || (!v && !tag[inv[l]])) return ;
        if(~tag[inv[l]]){
            for(int i = st[inv[l]]; i <= ed[inv[l]]; i++){
                if(sz2[inv[l]] && w[i] == 2) continue;
                w[i] = tag[inv[l]];
            }
            tag[inv[l]] = -1;
        }
        for(int i = l; i <= r; i++){
            if(w[i] && !v){
                if(w[i] == 1) sz1[inv[l]]--, re++;
                else sz2[inv[l]]--;
                w[i] = v;
            }
            else if(w[i] == 0 && v) sz1[inv[l]]++, w[i] = v;
        }
    }
    else{
        for(int i = inv[l] + 1; i < inv[r]; i++){
            if((tag[i] > 0 && v) || (!tag[i] && !v)) continue;
            if(!v) re += sz1[i], sz1[i] = sz2[i] = 0;
            else sz1[i] = ed[i] - st[i] + 1 - sz2[i];
            tag[i] = v;
        }
        updata(v, l, ed[inv[l]]);
        updata(v, st[inv[r]], r);
    }
}

inline int cnt(int n){
    int res = 0;
    for(int i = 1; i <= nob; i++){
        res += sz1[i];
    }
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, l, r, op;
    std::cin >> n >> m;
    ++n;
    init(n);
    for(int i = 0; i < m; i++){
        std::cin >> op >> l >> r;
        l++, r++;
        updata(op, l, r);
    }
    std::cout << cnt(n) << '\n' << re;
    return 0;
}