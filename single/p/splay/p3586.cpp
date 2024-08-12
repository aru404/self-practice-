// # [POI2015] LOG

// ## 题目描述

// 维护一个长度为 $n$ 的序列，一开始都是 $0$，支持以下两种操作：

// 1. `U k a` 将序列中第 $k$ 个数修改为 $a$。
// 2. `Z c s` 在这个序列上，每次选出 $c$ 个正数，并将它们都减去 $1$，询问能否进行 $s$ 次操作。

// 每次询问独立，即每次询问不会对序列进行修改。

// ## 输入格式

// 第一行包含两个正整数 $n,m$，分别表示序列长度和操作次数。

// 接下来 $m$ 行为 $m$ 个操作。

// ## 输出格式

// 包含若干行，对于每个 `Z` 询问，若可行，输出 `TAK`，否则输出 `NIE`。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 8
// U 1 5
// U 2 7
// Z 2 6
// U 3 1
// Z 2 6
// U 2 2
// Z 2 6
// Z 2 1
// ```

// ### 样例输出 #1

// ```
// NIE
// TAK
// NIE
// TAK
// ```

// ## 提示

// **【数据范围】**

// 对于 $100\%$ 的数据，$1\leq n,m\leq 10^6$，$1\leq k,c\leq n$，$0\leq a\leq 10^9$，$1\leq s\leq 10^9$。

// ----

// 原题名称：Logistyka。
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

const int maxN = 1E6 + 5;

namespace Splay{
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define f(x) tree[x].f
    #define v(x) tree[x].val
    #define cnt(x) tree[x].cnt
    #define sum(x) tree[x].sum
    #define sz(x) tree[x].sz
    #define get(x) (rs(f(x)) == x)
    #define son(x, y) (y? rs(x):ls(x))
    
    struct node{
        int ls, rs, cnt, val, sz, f;
        ll sum;
    }tree[maxN];

    int root = 0, idx = 0;
    std::stack<int> stk;

    inline void pushUp(int x){
        sz(x) = cnt(x) + sz(ls(x)) + sz(rs(x));
        sum(x) = 1ll * cnt(x) * v(x) + sum(ls(x)) + sum(rs(x));
    }

    inline void getNode(int& x){
        if(!stk.empty()) x = stk.top(), stk.pop();
        else x = ++idx;
        ls(x) = rs(x) = cnt(x) = v(x) = sz(x) = f(x) = sum(x) = 0;
    }

    inline void rotate(int x){
        int y = f(x), z = f(y), k = get(x);
        if(z) son(z, get(y)) = x;
        if(son(x, !k)) f(son(x, !k)) = y;
        son(y, k) = son(x, !k), son(x, !k) = y;
        f(y) = x, f(x) = z;
        pushUp(y), pushUp(x);
    }

    inline void splay(int x, int r){
        for(int fa = f(x); f(x) != r; rotate(x), fa = f(x)){
            if(f(fa) != r) rotate(get(x) ^ get(fa)? x:fa);
        }
        if(!r) root = x;
    }

    inline void find(int v){
        int r = root;
        while(son(r, v(r) < v) && v(r) != v) r = son(r, v(r) < v);
        if(r) splay(r, 0);
    }

    inline void ins(int v){
        int r = root, fa = 0;
        while(r && v(r) != v) fa = r, r = son(r, v(r) < v);
        if(!r){
            getNode(r), f(r) = fa, v(r) = v;
            if(fa) son(fa, v(fa) < v) = r;
        }
        ++cnt(r);
        pushUp(r);
        splay(r, 0);
    }

    inline int findBound(int v, bool f){
        find(v);
        int r = root;
        if((v(r) < v && !f) || (v(r) > v && f)) return r;
        r = son(r, f);
        while(son(r, !f)) r = son(r, !f);
        return r;
    }

    inline void del(int v){
        int pre = findBound(v, 0), suf = findBound(v, 1);
        if(pre) splay(pre, 0);
        if(suf) splay(suf, pre);
        if(!pre && !suf){
            --cnt(root);
            pushUp(root);
            if(!cnt(root)) stk.emplace(root), root = 0;
            return ; 
        }
        int r = suf? ls(suf):rs(pre);
        --cnt(r);
        if(!cnt(r)){
            int fa = f(r);
            stk.emplace(r);
            if(fa) son(fa, get(r)) = 0, pushUp(fa);
        }
        else pushUp(r), splay(r, 0);
    }
}

int w[maxN];

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k, a;
    char op;
    std::cin >> n >> m;
    using namespace Splay;
    for(int i = 0; i < m; i++){
        std::cin >> op >> k >> a;
        if(op == 'U'){
            if(w[k]) del(w[k]);
            if(a) ins(a);
            w[k] = a;
        }
        else{
            int pre = findBound(a, 0);
            if(!pre){
                if(sz(root) >= k) std::cout << "TAK\n";
                else std::cout << "NIE\n";
                continue;
            }
            splay(pre, 0);
            k -= sz(rs(root));
            ll v = sum(ls(root)) + 1ll * v(root) * cnt(root);
            if(v < 1ll * a * k) std::cout << "NIE\n";
            else std::cout << "TAK\n";
        }
    }
    return 0;
}