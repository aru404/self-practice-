// # 序列终结者

// ## 题目背景

// 网上有许多题，就是给定一个序列，要你支持几种操作：A、B、C、D。一看另一道题，又是一个序列要支持几种操作：D、C、B、A。尤其是我们这里的某人，出模拟试题，居然还出了一道这样的，真是没技术含量……

// 这样我也出一道题，我出这一道的目的是为了让大家以后做这种题目有一个“库”可以依靠，没有什么其他的意思。

// 这道题目就叫序列终结者吧。

// ## 题目描述

// 给定一个长度为N的序列，每个序列的元素是一个整数（废话）。要支持以下三种操作：

// 1. 将$[L,R]$这个区间内的所有数加上$V$。
// 2. 将$[L,R]$这个区间翻转，比如`1 2 3 4`变成`4 3 2 1`。
// 3. 求$[L,R]$这个区间中的最大值。

// 最开始所有元素都是$0$。

// ## 输入格式

// 第一行两个整数`N，M`。`M`为操作个数。

// 以下$M$行，每行最多四个整数，依次为`K，L，R，V`。`K`表示是第几种操作，如果不是第1种操作则`K`后面只有两个数。

// ## 输出格式

// 对于每个第3种操作，给出正确的回答。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 4
// 1 1 3 2
// 1 2 4 -1
// 2 1 3
// 3 2 4
// ```

// ### 样例输出 #1

// ```
// 2
// ```

// ## 提示

// $N \le 50000,M \le 100000$。
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

namespace BST{
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define v(x) tree[x].v
    #define sz(x) tree[x].sz
    #define add(x) tree[x].add
    #define mx(x) tree[x].mx
    #define tag(x) tree[x].tag
    #define rd(x) tree[x].rd

    struct node{
        int ls, rs, sz, rd;
        ll  v, mx, add;
        bool tag;
    };

    std::mt19937 rnd(114514);

    class Treap{
    private:
        int tot = 0, root = 0, rx, ry, rz;
        node* tree;

        inline int getNode(int);

        inline void pushUp(int&);

        inline void pushDown(int&);

        inline void split(int, int, int&, int&);

        inline int merger(int, int);
    public:
        Treap(int);

        ~Treap();

        inline void ins(int);

        inline void reverse(int, int);

        inline void updataAdd(int, int, int);

        inline ll getRangeMx(int, int);
    };
    
    Treap::Treap(int n){
        tree = new node[n + 1];
        ls(0) = rs(0) = rd(0) = add(0) = sz(0) = 0;
        v(0) = mx(0) = INT64_MIN, tag(0) = 0;
    }
    
    Treap::~Treap(){
        delete[] tree;
    }

    inline int Treap::getNode(int v){
        int x = ++tot;
        ls(x) = rs(x) = add(x) = 0, tag(x) = 0;
        v(x) = mx(x) = v, sz(x) = 1, rd(x) = rnd();
        return x;
    }

    inline void Treap::pushUp(int& x){
        mx(x) = std::max({mx(ls(x)), mx(rs(x)), v(x)});
        sz(x) = sz(ls(x)) + sz(rs(x)) + 1;
    } 

    inline void Treap::pushDown(int& x){
        if(tag(x)){
            if(ls(x)) tag(ls(x)) ^= 1, std::swap(ls(ls(x)), rs(ls(x)));
            if(rs(x)) tag(rs(x)) ^= 1, std::swap(ls(rs(x)), rs(rs(x)));
            tag(x) = 0;
        }
        if(add(x)){
            if(ls(x)) add(ls(x)) += add(x), mx(ls(x)) += add(x), v(ls(x)) += add(x);
            if(rs(x)) add(rs(x)) += add(x), mx(rs(x)) += add(x), v(rs(x)) += add(x);
            add(x) = 0;
        }
    }

    inline void Treap::split(int k, int r, int& x, int& y){
        if(!r){
            x = y = 0;
            return ;
        }
        pushDown(r);
        if(k > sz(ls(r))) x = r, split(k - sz(ls(r)) - 1, rs(r), rs(x), y);
        else y = r, split(k, ls(r), x, ls(y));
        pushUp(r);
    }

    inline int Treap::merger(int x, int y){
        if(!x || !y) return x | y;
        if(rd(x) < rd(y)){
            pushDown(x);
            rs(x) = merger(rs(x), y), pushUp(x);
            return x;
        }
        else{
            pushDown(y);
            ls(y) = merger(x, ls(y)), pushUp(y);
            return y;    
        }
    }

    inline void Treap::ins(int v){
        root = merger(root, getNode(v));
    }

    inline void Treap::reverse(int l, int r){
        split(r, root, rx, ry);
        split(l - 1, rx, rx, rz);
        tag(rz) ^= 1, std::swap(ls(rz), rs(rz));
        root = merger(merger(rx, rz), ry);
    }

    inline void Treap::updataAdd(int l, int r, int v){
        split(r, root, rx, ry);
        split(l - 1, rx, rx, rz);
        add(rz) += v, mx(rz) += v, v(rz) += v;
        root = merger(merger(rx, rz), ry);
    }

    inline ll Treap::getRangeMx(int l, int r){
        split(r, root, rx, ry);
        split(l - 1, rx, rx, rz);
        ll res = mx(rz);
        root = merger(merger(rx, rz), ry);
        return res;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, op, l, r, v;
    std::cin >> n >> m;
    BST::Treap treap(n);
    for(int i = 0; i < n; i++) treap.ins(0);
    for(int i = 0; i < m; i++){
        std::cin >> op >> l >> r;
        if(op == 1){
            std::cin >> v;
            treap.updataAdd(l, r, v);
        }
        else if(op == 2) treap.reverse(l, r);
        else std::cout << treap.getRangeMx(l, r) << '\n';
    }
    return 0;
}