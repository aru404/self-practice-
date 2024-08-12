// # [ZJOI2007] 报表统计

// ## 题目描述

// 小 Q 的妈妈是一个出纳，经常需要做一些统计报表的工作。今天是妈妈的生日，小 Q 希望可以帮妈妈分担一些工作，作为她的生日礼物之一。

// 经过仔细观察，小 Q 发现统计一张报表实际上是维护一个非负整数数列，并且进行一些查询操作。

// 在最开始的时候，有一个长度为 $n$ 的整数序列 $a$，并且有以下三种操作：
        
// - `INSERT i k`：在原数列的第 $i$ 个元素后面添加一个新元素 $k$；如果原数列的第 $i$ 个元素已经添加了若干元素，则添加在这些元素的最后（见样例说明）。
// - `MIN_GAP`：查询相邻两个元素的之间差值（绝对值）的最小值。
// - `MIN_SORT_GAP`：查询所有元素中最接近的两个元素的差值（绝对值）。

// 于是小 Q 写了一个程序，使得程序可以自动完成这些操作，但是他发现对于一些大的报表他的程序运行得很慢，你能帮助他改进程序么？

// ## 输入格式

// 第一行包含两个整数，分别表示原数列的长度 $n$ 以及操作的次数 $m$。

// 第二行为 $n$ 个整数，为初始序列，第 $i$ 个整数表示 $a_i$。

// 接下来的 $m$ 行，每行一个操作，即`INSERT i k`，`MIN_GAP`，`MIN_SORT_GAP` 中的一种（无多余空格或者空行）。

// ## 输出格式

// 对于每一个 `MIN_GAP` 和 `MIN_SORT_GAP` 命令，输出一行答案即可。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 5
// 5 3 1
// INSERT 2 9
// MIN_SORT_GAP
// INSERT 2 6
// MIN_GAP
// MIN_SORT_GAP
// ```

// ### 样例输出 #1

// ```
// 2
// 2
// 1
// ```

// ## 提示

// #### 样例输入输出 1 解释

// 一开始的序列为 $\{5,3,1\}$。

// 执行操作 `INSERT 2  9` 将得到 $\{5,3,9,1\}$，此时 `MIN_GAP` 为 $2$，`MIN_SORT_GAP` 为 $2$。

// 再执行操作 `INSERT 2  6` 将得到：$\{5,3, 9, 6, 1\}$。

// 注意这个时候原序列的第 $2$ 个元素后面已经添加了一个 $9$，此时添加的 $6$ 应加在 $9$ 的后面。这个时候 `MIN_GAP` 为 $2$，`MIN_SORT_GAP` 为 $1$。

// ---


// #### 数据规模与约定

// 对于全部的测试点，保证 $2 \le n, m \le 5\times10^5$，$1 \leq i \leq n$，$0 \leq a_i, k \leq 5 \times 10^8$。
#include <iostream>
#include <bits/stdc++.h>

namespace BST{ 
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define rd(x) tree[x].rd
    #define sz(x) tree[x].sz
    #define v(x) tree[x].v
    #define mn(x) tree[x].mn
    #define lv(x) tree[x].lv
    #define rv(x) tree[x].rv
    std::mt19937 rnd(114515);

    struct node{
        int ls, rs, rd, sz, v, lv, rv;
    };

    struct node1 : public node{
        int mn;
    };

    struct node2 : public node{
        int mn, cnt;
    };

    class Treap1{
        private:
            #define lowbit(x) (x & -x)
            node1* tree;
            int* cnt, n, tot = 0, root = 0, rx = 0, ry = 0, rz = 0;

            inline int getNode(int);

            inline void pushUp(int&);

            inline void split(int, int, int&, int&);

            inline int merger(int, int);

            inline void updata(int, int);

            inline int query(int);
        public:
            Treap1(int, int);

            ~Treap1();

            inline void ins(int, int);

            inline int queryMn();
    };

    class Treap2{
        private:
            #define cnt(x) tree[x].cnt
            node2* tree;
            int tot = 0, root = 0, rx = 0, ry = 0, rz = 0;

            inline int getNode(int);

            inline void pushUp(int&);

            inline void split(int, int, int&, int&);

            inline int merger(int, int);
        public:
            Treap2(int);

            ~Treap2();

            inline void ins(int);

            inline int queryMn();
    };

    inline int Treap1::getNode(int v){
        int x = ++tot;
        ls(x) = rs(x) = 0, rd(x) = rnd(), sz(x) = 1;
        lv(x) = rv(x) = v(x) = v;
        mn(x) = 0X3f3f3f3f;
        return x;
    };

    inline void Treap1::pushUp(int& x){
        sz(x) = sz(ls(x)) + sz(rs(x)) + 1;
        lv(x) = rv(x) = v(x);
        mn(x) = std::min(mn(ls(x)), mn(rs(x)));
        if(ls(x)) lv(x) = lv(ls(x)), mn(x) = std::min(mn(x), std::abs(v(x) - rv(ls(x))));
        if(rs(x)) rv(x) = rv(rs(x)), mn(x) = std::min(mn(x), std::abs(v(x) - lv(rs(x))));
    }
    
    inline void Treap1::split(int k, int r, int& x, int& y){
        if(!r){
            x = y = 0;
            return ;
        }
        if(k > sz(ls(r))) x = r, split(k - sz(ls(r)) - 1, rs(r), rs(x), y);
        else y = r, split(k, ls(r), x, ls(y));
        pushUp(r);
    }

    inline int Treap1::merger(int x, int y){
        if(!x || !y) return x | y;
        if(rd(x) < rd(y)){
            rs(x) = merger(rs(x), y), pushUp(x);
            return x;
        }
        else{
            ls(y) = merger(x, ls(y)), pushUp(y);
            return y;
        }
    }

    inline void Treap1::updata(int x, int v){
        while(x <= n) cnt[x] += v, x += lowbit(x);
    }

    inline int Treap1::query(int x){
        int res = 0;
        while(x) res += cnt[x], x -= lowbit(x);
        return res;
    }

    Treap1::Treap1(int m, int maxM){
        n = m;
        tree = new node1[maxM + 1];
        cnt = new int[m + 1];
        memset(cnt, 0, sizeof(int) * (m + 1));
        ls(0) = rs(0) = rd(0) = sz(0) = 0;
        mn(0) = 0X3f3f3f3f;
    }

    Treap1::~Treap1(){
        delete[] tree;
        delete[] cnt;
    }

    inline void Treap1::ins(int k, int v){
        int idx = query(k);
        updata(k, 1);
        split(idx, root, rx, ry);
        root = merger(merger(rx, getNode(v)), ry);
    }

    inline int Treap1::queryMn(){
        return mn(root);
    }
    
    inline int Treap2::getNode(int v){
        int x = ++tot;
        ls(x) = rs(x) = 0, rd(x) = rnd(), sz(x) = cnt(x) = 1;
        lv(x) = rv(x) = v(x) = v;
        mn(x) = 0X3f3f3f3f;
        return x;
    };
    
    inline void Treap2::pushUp(int& x){
        sz(x) = sz(ls(x)) + sz(rs(x)) + cnt(x);
        lv(x) = rv(x) = v(x);
        mn(x) = std::min(mn(ls(x)), mn(rs(x)));
        if(cnt(x) > 1) mn(x) = 0;
        if(ls(x)) lv(x) = lv(ls(x)), mn(x) = std::min(mn(x), v(x) - rv(ls(x)));
        if(rs(x)) rv(x) = rv(rs(x)), mn(x) = std::min(mn(x), lv(rs(x)) - v(x));
    }

    inline void Treap2::split(int k, int r, int& x, int& y){
        if(!r){
            x = y = 0;
            return ;
        }
        if(k >= v(r)) x = r, split(k, rs(r), rs(x), y);
        else y = r, split(k, ls(r), x, ls(r));
        pushUp(r);
    }

    inline int Treap2::merger(int x, int y){
        if(!x || !y) return x | y;
        if(rd(x) < rd(y)){
            rs(x) = merger(rs(x), y), pushUp(x);
            return x;
        }
        else{
            ls(y) = merger(x, ls(y)), pushUp(y);
            return y;
        }
    }

    Treap2::Treap2(int n){
        tree = new node2[n + 1];
        ls(0) = rs(0) = sz(0) = rd(0) = cnt(0) = 0;
        mn(0) = 0X3f3f3f3f;
    }

    Treap2::~Treap2(){
        delete[] tree;
    }

    inline void Treap2::ins(int v){
        split(v, root, rx, ry);
        split(v - 1, rx, rx, rz);
        if(!rz) rz = getNode(v);
        else ++cnt(rz), ++sz(rz), mn(rz) = 0;
        root = merger(merger(rx, rz), ry);
    }

    inline int Treap2::queryMn(){
        return mn(root);
    }
}

const int maxN = 1E6 + 5;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, v, k;
    std::string op;
    std::cin >> n >> m;
    BST::Treap1 tree1(n, maxN);
    BST::Treap2 tree2(maxN);
    for(int i = 1; i <= n; i++){
        std::cin >> v;
        tree1.ins(i, v);
        tree2.ins(v);
    }
    for(int i = 0; i < m; i++){
        std::cin >> op;
        if(op[4] == 'R'){
            std::cin >> k >> v;
            tree1.ins(k, v), tree2.ins(v);
        }
        else if(op[4] == 'G') std::cout << tree1.queryMn() << '\n';
        else std::cout << tree2.queryMn() << '\n';
    }
    return 0;
}