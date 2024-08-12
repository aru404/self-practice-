// # 【模板】文艺平衡树

// ## 题目描述

// 您需要写一种数据结构（可参考题目标题），来维护一个有序数列。  

// 其中需要提供以下操作：翻转一个区间，例如原有序序列是 $5\ 4\ 3\ 2\ 1$，翻转区间是 $[2,4]$ 的话，结果是 $5\ 2\ 3\ 4\ 1$。

// ## 输入格式

// 第一行两个正整数 $n,m$，表示序列长度与操作个数。序列中第 $i$ 项初始为 $i$。  
// 接下来 $m$ 行，每行两个正整数 $l,r$，表示翻转的区间。

// ## 输出格式

// 输出一行 $n$ 个正整数，表示原始序列经过 $m$ 次变换后的结果。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 3
// 1 3
// 1 3
// 1 4
// ```

// ### 样例输出 #1

// ```
// 4 3 2 1 5
// ```

// ## 提示

// 【数据范围】  
// 对于 $100\%$ 的数据，$1 \le n, m \leq 100000 $，$1 \le l \le r \le n$。
#include <iostream>
#include <bits/stdc++.h>
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
#define get(x) (ch[f[x]][1] == x)

const int maxN = 1E5 + 5, inf = 0X3f3f3f3f;
int ch[maxN][2], f[maxN], sz[maxN], w[maxN], s[maxN], root;
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
    sz[x] = 1 + sz[ls(x)] + sz[rs(x)];
}

inline void rotate(int x){
    int y = f[x], z = f[y], k = get(x);
    if(z) ch[z][get(y)] = x;
    if(ch[x][!k]) f[ch[x][!k]] = y;
    ch[y][k] = ch[x][!k], ch[x][!k] = y;
    f[y] = x, f[x] = z;
    pushUp(y), pushUp(x);    
}

inline void updata(int x, int r){
    int idx = 0;
    s[++idx] = x;
    while(f[x] != r) x = f[x], s[++idx] = x;
    while(idx) pushDown(s[idx--]);
}

inline void splay(int x, int r){
    updata(x, r);
    for(int fa = f[x]; fa != r; rotate(x), fa = f[x]){
        if(f[fa] != r) rotate(get(x) ^ get(fa)? x:fa);
    }
    if(!r) root = x;
}

inline int find(int x){
    int r = root;
    while(x != sz[ls(r)] + 1){
        pushDown(r);
        if(x <= sz[ls(r)]) r = ls(r);
        else{
            x -= sz[ls(r)] + 1;
            r = rs(r);
        }
    };
    return r;
}

inline void reverse(int l, int r){
    l = find(l), r = find(r + 2);
    splay(l, 0), splay(r, l);
    int rr = ls(r);
    tag[rr] ^= 1;
    std::swap(ls(rr), rs(rr));
}

inline void dfs(int x){
    pushDown(x);
    if(ls(x)) dfs(ls(x));
    if(w[x] != inf) std::cout << w[x] << ' ';
    if(rs(x)) dfs(rs(x));
}

inline int buildTree(int l, int r, int fa){
    if(l > r) return 0;
    int m = (l + r) >> 1;
    f[m] = fa;
    ls(m) = buildTree(l, m - 1, m);
    rs(m) = buildTree(m + 1, r, m);
    pushUp(m);
    return m;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, l, r;
    std::cin >> n >> m;
    w[1] = w[n + 2] = inf;
    for(int i = 2; i <= n + 1; i++) w[i] = i - 1;
    root = buildTree(1, n + 2, 0);
    for(int i = 0; i < m; i++){
        std::cin >> l >> r;
        reverse(l, r);
    }
    dfs(root);
    return 0;
}