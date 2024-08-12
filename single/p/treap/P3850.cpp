// # [TJOI2007] 书架

// ## 题目描述

// Knuth 先生家里有个精致的书架，书架上有 $N$ 本书，如今他想学到更多的知识，于是又买来了 $M$ 本不同的新书。现在他要把新买的书依次插入到书架中，他已经把每本书要插入的位置标记好了，并且相应的将它们放好。由于 Knuth 年龄已大，过几天他已经记不清某些位置上放的到底是什么书了，请问你能帮助他吗？

// ## 输入格式

// 输入文件的第一行为整数 $N$，接下来 $N$ 行分别是书架上依次放着的 N 本书的书名（书名由不含空格的字符串构成，长度不超过 $10$）。下一行将要输入一个整数 $M$，接下来的 $M$ 行分别为这本书的书名和要插入的位置。下一行将要输入一个整数 $Q$，接下来共有 $Q$ 次询问，每行都是一个整数表示询问的位置。（书架上位置的编号从 $0$ 开始）

// ## 输出格式

// 输出 $Q$ 行，每行对应着相应查询位置的书名。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// Math
// Algorithm
// Program
// 2
// Picture 2
// System 1
// 3
// 0
// 1
// 3
// ```

// ### 样例输出 #1

// ```
// Math
// System
// Picture
// ```

// ## 提示

// 原来有三本书 Math、Algorithm、Program，后来又买了两本书，分别插入到 $2$ 和 $1$ 的位置，每次插入时其他书都要向后挪一个位置，最后书架上书的序列为：

// ```plain
// 0  Math
// 1  System
// 2  Algorithm
// 3  Picture
// 4  Program
// ```
// $Q$ 次询问依次为 $0$, $1$, $3$ 位置的书，所以答案为：Math、System、Picture


// 对于 $30\%$ 的数据，$1 \leqslant N \leqslant 100$, $1 \leqslant M \leqslant 10^3$, $1 \leqslant Q \leqslant 10^3$

// 对于 $100\%$ 的数据，$1 \leqslant N \leqslant 200$, $1 \leqslant M \leqslant 10^5$, $1 \leqslant Q \leqslant 10^4$

// 对于 $100\%$ 的数据都符合题目中所描述的限制关系，数据保证每次插入的位置均不超过当时书架上书的数量，而且保证 $Q$ 次查询中的每个位置上一定有书。
#include <iostream>
#include <bits/stdc++.h>

namespace BST{
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define sz(x) tree[x].sz
    #define nm(x) tree[x].name
    #define rd(x) tree[x].rd

    std::mt19937 rnd(114514);
    struct node{
        int ls, rs, sz, rd;
        std::string name;
    };

    class Treap{
    private:
        node* tree;
        int tot = 0, root = 0, rx = 0, ry = 0, rz = 0;

        inline int getNode(std::string&);

        inline void pushUp(int&);

        inline void split(int, int, int&, int&);

        inline int merger(int, int);
    public:
        Treap(int);

        ~Treap();

        inline void ins(int, std::string&);

        inline std::string& query(int);
    };
    
    Treap::Treap(int n){
        tree = new node[n + 1];
        ls(0) = rs(0) = rd(0) = sz(0) = 0;
    }

    Treap::~Treap(){
        delete[] tree;
    }

    inline int Treap::getNode(std::string& nm){
        int x = ++tot;
        ls(x) = rs(x) = 0, sz(x) = 1, rd(x) = rnd();
        nm(x) = nm;
        return x;
    }

    inline void Treap::pushUp(int& x){
        sz(x) = sz(ls(x)) + sz(rs(x)) + 1;
    }

    inline void Treap::split(int k, int r, int& x, int& y){
        if(!r){
            x = y = 0;
            return ;
        }
        if(k > sz(ls(r))) x = r, split(k - sz(ls(x)) - 1, rs(r), rs(x), y);
        else y = r, split(k, ls(r), x, ls(y));
        pushUp(r);
    }

    inline int Treap::merger(int x, int y){
        if(!x || !y) return  x | y;
        if(rd(x) < rd(y)){
            rs(x) = merger(rs(x), y);
            pushUp(x);
            return x;
        }
        else{
            ls(y) = merger(x, ls(y));
            pushUp(y);
            return y;
        }
    }

    inline void Treap::ins(int k, std::string& nm){
        split(k, root, rx, ry);
        rz = getNode(nm);
        root = merger(merger(rx, rz), ry);
    }

    inline std::string& Treap::query(int k){
        int r = root;
        while(1){
            if(k < sz(ls(r))) r = ls(r);
            else if(k > sz(ls(r))) k -= sz(ls(r)) + 1, r = rs(r);
            else return nm(r);
        }
    }
}

const int maxM = 1E5;
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k, q, m;
    std::string nm;
    std::cin >> n;
    BST::Treap treap(n + maxM);
    for(int i = 0; i < n; i++) std::cin >> nm, treap.ins(i, nm);
    std::cin >> m;
    for(int i = 0; i < m; i++){
        std::cin >> nm >> k;
        treap.ins(k, nm);
    }
    std::cin >> q;
    for(int i = 0; i < q; i++){
        std::cin >> k;
        std::cout << treap.query(k) << '\n';
    }
    return 0;
}