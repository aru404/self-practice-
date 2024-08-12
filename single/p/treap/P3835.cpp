// # 【模板】可持久化平衡树

// ## 题目背景

// 本题为题目 **普通平衡树** 的可持久化加强版。

// **数据已经经过强化**

// **感谢@Kelin 提供的一组hack数据**

// ## 题目描述

// 您需要写一种数据结构（可参考题目标题），来维护一个可重整数集合，其中需要提供以下操作（ **对于各个以往的历史版本** ）：


// 1、 插入 $x$

// 2、 删除 $x$（若有多个相同的数，应只删除一个，**如果没有请忽略该操作**）


// 3、 查询 $x$ 的排名（排名定义为比当前数小的数的个数 $+1$）


// 4、查询排名为 $x$ 的数


// 5、 求 $x$ 的前驱（前驱定义为小于 $x$，且最大的数，**如不存在输出** $-2^{31}+1$ ）


// 6、求 $x$ 的后继（后继定义为大于 $x$，且最小的数，**如不存在输出** $2^{31}-1$ ）


// **和原本平衡树不同的一点是，每一次的任何操作都是基于某一个历史版本，同时生成一个新的版本。（操作3, 4, 5, 6即保持原版本无变化）**

// 每个版本的编号即为操作的序号（版本0即为初始状态，空树）

// ## 输入格式

// 第一行包含一个正整数 $n$ ，表示操作的总数。

// 接下来 $n$ 行，每行包含三个整数，第 $i$ 行记为 $v_i, \text{opt}_i, x_i$。

// $v_i$ 表示基于的过去版本号，$\text{opt}_i$ 表示操作的序号， $x_i$ 表示参与操作的数值

// ## 输出格式

// 每行包含一个整数，依次为各个 $3,4,5,6$ 操作所对应的答案

// ## 样例 #1

// ### 样例输入 #1

// ```
// 10
// 0 1 9
// 1 1 3
// 1 1 10
// 2 4 2
// 3 3 9
// 3 1 2
// 6 4 1
// 6 2 9
// 8 6 3
// 4 5 8
// ```

// ### 样例输出 #1

// ```
// 9
// 1
// 2
// 10
// 3
// ```

// ## 提示

// 【数据范围】   
// 对于 $28\%$ 的数据，$ 1 \leq n \leq 10 $；   
// 对于 $44\%$ 的数据，$ 1 \leq n \leq 2\times {10}^2 $；   
// 对于 $60\%$ 的数据， $ 1 \leq n \leq 3\times {10}^3 $；   
// 对于 $84\%$ 的数据， $ 1 \leq n \leq {10}^5 $；   
// 对于 $92\%$ 的数据， $ 1 \leq n \leq 2\times {10}^5 $；   
// 对于 $100\%$ 的数据， $ 1 \leq n \leq 5 \times  10^5 $ , $|x_i| \leq {10}^9$，$0 \le v_i < i$，$1\le \text{opt} \le 6$。

// **经实测，正常常数的可持久化平衡树均可通过，请各位放心**



// 样例说明：

// 共 $10$ 次操作，$11$ 个版本，各版本的状况依次是：

// 0.  $[]$

// 1.  $[9]$

// 2.  $[3, 9]$

// 3.  $[9, 10]$

// 4.  $[3, 9]$

// 5.  $[9, 10]$

// 6.  $[2, 9, 10]$

// 7.  $[2, 9, 10]$

// 8.  $[2, 10]$

// 9.  $[2, 10]$

// 10.  $[3, 9]$
#include <iostream>
#include <bits/stdc++.h>

namespace BST{
    struct node{
        int ls, rs, cnt, sz, v, rd;
    };
    
    std::mt19937 rnd(114514);

    class Treap{
    private:
        #define ls(x) tree[x].ls
        #define rs(x) tree[x].rs
        #define sz(x) tree[x].sz
        #define cnt(x) tree[x].cnt
        #define v(x) tree[x].v
        #define rd(x) tree[x].rd
        #define dfn(x) tree[x].dfn

        int tot = 0, rx = 0, ry = 0, rz = 0, rw = 0, cnt = 0;
        int* root;
        node* tree;

        inline int getNode(int);

        inline int getNode(node&);

        inline void pushUp(int&);

        inline void split(int, int, int&, int&, bool);

        inline int merger(int, int);

        inline int dfs(int, int);
    public:
        Treap(int, int);

        ~Treap();

        inline void ins(int, int);

        inline void del(int, int);

        inline int getRk(int, int);

        inline int getKth(int, int);

        inline int pre(int, int);

        inline int suf(int, int);
    };
    
    Treap::Treap(int n, int m){
        tree = new node[m + 1];
        root = new int[n + 1];
        ls(0) = rs(0) = sz(0) = cnt(0) = root[0] = 0;
    }
    
    Treap::~Treap(){
        delete[] tree;
        delete[] root;
    }

    inline int Treap::getNode(int v){
        int x = ++tot;
        ls(x) = rs(x) = 0, cnt(x) = sz(x) = 1;
        rd(x) = rnd(), v(x) = v;
        return x;
    }

    inline int Treap::getNode(node& y){
        int x = ++tot;
        tree[x] = y;
        return x;
    }

    inline void Treap::pushUp(int& x){
        sz(x) = sz(ls(x)) + sz(rs(x)) + cnt(x);
    }

    inline void Treap::split(int k, int r, int& x, int& y, bool f){
        if(!r){
            x = y = 0;
            return ;
        }
        if(f) r = getNode(tree[r]);
        if(v(r) <= k) x = r, split(k, rs(r), rs(x), y, f);
        else y = r, split(k, ls(r), x, ls(y), f);
        pushUp(r);
        return ;
    }

    inline int Treap::merger(int x, int y){
        if(!x || !y) return x | y;
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

    inline void Treap::ins(int r, int v){
        ++cnt;
        split(v, root[r], rx, ry, 1);
        split(v - 1, rx, rx, rz, 1);
        if(!rz) rw = getNode(v);
        else rw = getNode(tree[rz]), ++cnt(rw), ++sz(rw);
        root[cnt] = merger(merger(rx, rw), ry);
    }

    inline void Treap::del(int r, int v){
        ++cnt;
        split(v, root[r], rx, ry, 1);
        split(v - 1, rx, rx, rz, 1);
        if(cnt(rz) <= 1) rw = 0;
        else rw = getNode(tree[rz]), --cnt(rw), --sz(rw);
        root[cnt] = merger(merger(rx, rw), ry);
    }

    inline int Treap::getRk(int r, int v){
        split(v, root[r], rx, ry, 0);
        split(v - 1, rx, rx, rz, 0);
        int res = 1 + sz(rx);
        root[r] = root[++cnt] = merger(merger(rx, rz), ry);
        return res;
    }

    inline int Treap::getKth(int r, int k){
        root[++cnt] = root[r];
        return dfs(root[r], k);
    }

    inline int Treap::dfs(int r, int k){
        if(ls(r) && k <= sz(ls(r))) return dfs(ls(r), k);
        else if(k > sz(ls(r)) + cnt(r)) return dfs(rs(r), k - sz(ls(r)) - cnt(r));
        return v(r);
    }

    inline int Treap::pre(int r, int k){
        split(k - 1, root[r], rx, ry, 0);
        int tmp = rx;
        while(rs(tmp)) tmp = rs(tmp);
        int res = tmp? v(tmp):-INT32_MAX;
        root[r] = root[++cnt] = merger(rx, ry);
        return res;
    }

    inline int Treap::suf(int r, int k){
        split(k, root[r], rx, ry, 0);
        int tmp = ry;
        while(ls(tmp)) tmp = ls(tmp);
        int res = tmp? v(tmp):INT32_MAX;
        root[r] = root[++cnt] = merger(rx, ry);
        return res;
    }
}

const int maxN = 2E7 + 5;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, op, r, k;
    std::cin >> n;
    BST::Treap treap(n, maxN);
    for(int i = 0; i < n; i++){
        std::cin >> r >> op >> k;
        if(op == 1) treap.ins(r, k);
        else if(op == 2) treap.del(r, k);
        else if(op == 3) std::cout << treap.getRk(r, k) << '\n';
        else if(op == 4) std::cout << treap.getKth(r, k) << '\n';
        else if(op == 5) std::cout << treap.pre(r, k) << '\n';
        else if(op == 6) std::cout << treap.suf(r, k) << '\n';
    }
    return 0;
}