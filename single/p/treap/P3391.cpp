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

namespace BST{
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define sz(x) tree[x].sz
    #define rd(x) tree[x].rd
    #define v(x) tree[x].v
    #define lz(x) tree[x].lz

    struct node{
        int v, rd, ls, rs, sz;
        bool lz;
    };

    std::mt19937 rnd(114514);

    class Treap{
    private:
        node* tree;
        int tot = 0;

        inline void getNode(int&, int);

        inline void pushUp(int&);

        inline void pushDown(int&);

        inline void split(int, int, int&, int&);

        inline int merger(int, int);
    public:
        int root = 0;

        Treap(int);

        ~Treap();

        inline void ins(int);

        inline void reverse(int, int);

        inline void print(int);
    };
    
    Treap::Treap(int n){
        tree = new node[n + 1];
        ls(0) = rs(0) = sz(0) = rd(0) = v(0) = 0;
        lz(0) = 0;
    }
    
    Treap::~Treap(){
        delete[] tree;
    }

    inline void Treap::getNode(int& x, int v){
        x = ++tot;
        ls(x) = rs(x) = 0, sz(x) = 1, v(x) = v;
        rd(x) = rnd(), lz(x) = 0;
    }

    inline void Treap::pushUp(int& x){
        sz(x) = sz(ls(x)) + sz(rs(x)) + 1;
    }

    inline void Treap::pushDown(int& x){
        if(lz(x)){
            if(ls(x)) lz(ls(x)) ^= 1, std::swap(ls(ls(x)), rs(ls(x)));
            if(rs(x)) lz(rs(x)) ^= 1, std::swap(ls(rs(x)), rs(rs(x)));
            lz(x) = 0;
        }
    }

    inline void Treap::split(int key, int r, int& x, int& y){
        if(!r){
            x = y = 0;
            return ;
        }
        pushDown(r);
        if(key > sz(ls(r))) x = r, split(key - sz(ls(r)) - 1, rs(r), rs(x), y);
        else y = r, split(key, ls(r), x, ls(y));
        pushUp(r);
        return ;
    }

    inline int Treap::merger(int x, int y){
        if(!x || !y) return x | y;
        pushDown(x), pushDown(y);
        if(rd(x) < rd(y)){
            rs(x) = merger(rs(x), y), pushUp(x);
            return x;
        }
        else{
            ls(y) = merger(x, ls(y)), pushUp(y);
            return y;
        }
    }

    inline void Treap::ins(int v){
        int newNode; getNode(newNode, v);
        root = merger(root, newNode);
    }

    inline void Treap::reverse(int l, int r){
        int rx = 0, ry = 0, rz = 0;
        split(r, root, rx, ry);
        split(l - 1, rx, rx, rz);
        lz(rz) ^= 1, std::swap(ls(rz), rs(rz));
        root = merger(merger(rx, rz), ry);
    }

    inline void Treap::print(int r){
        if(!r) return;
        pushDown(r);
        print(ls(r));
        std::cout << v(r) << ' ';
        print(rs(r));
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, l, r;
    std::cin >> n >> m;
    BST::Treap treap(n);
    for(int i = 1; i <= n; i++) treap.ins(i);
    for(int i = 0; i < m; i++){
        std::cin >> l >> r;
        treap.reverse(l, r);
    }
    treap.print(treap.root);
    return 0;
}