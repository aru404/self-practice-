// # [NOI2005] 维护数列

// ## 题目描述

// 请写一个程序，要求维护一个数列，支持以下 $6$ 种操作：

// | 编号 | 名称 | 格式 | 说明 |
// | :-----------: | :-----------: | :-----------: | :----------- |
// | 1 | 插入 | $\operatorname{INSERT}\ posi \ tot \ c_1 \ c_2 \cdots c_{tot}$ | 在当前数列的第 $posi$ 个数字后插入 $tot$ 个数字：$c_1, c_2 \cdots c_{tot}$；若在数列首插入，则 $posi$ 为 $0$ |
// | 2 | 删除 | $\operatorname{DELETE} \ posi \ tot$ | 从当前数列的第 $posi$ 个数字开始连续删除 $tot$ 个数字 |
// | 3 | 修改 | $\operatorname{MAKE-SAME} \ posi \ tot \ c$ | 从当前数列的第 $posi$ 个数字开始的连续 $tot$ 个数字统一修改为 $c$ |
// | 4 | 翻转 | $\operatorname{REVERSE} \ posi \ tot$ | 取出从当前数列的第 $posi$ 个数字开始的 $tot$ 个数字，翻转后放入原来的位置 |
// | 5 | 求和 | $\operatorname{GET-SUM} \ posi \ tot$ | 计算从当前数列的第 $posi$ 个数字开始的 $tot$ 个数字的和并输出 |
// | 6 | 求最大子列和 | $\operatorname{MAX-SUM}$ | 求出当前数列中和最大的一段子列，并输出最大和 |

// ## 输入格式

// 第一行包含两个整数 $N$ 和 $M$，$N$ 表示初始时数列中数的个数，$M$ 表示要进行的操作数目。

// 第二行包含 $N$ 个数字，描述初始时的数列。以下 $M$ 行，每行一条命令，格式参见问题描述中的表格。

// ## 输出格式

// 对于输入数据中的 $\operatorname{GET-SUM}$ 和 $\operatorname{MAX-SUM}$ 操作，向输出文件依次打印结果，每个答案（数字）占一行。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 9 8 
// 2 -6 3 5 1 -5 -3 6 3 
// GET-SUM 5 4
// MAX-SUM
// INSERT 8 3 -5 7 2
// DELETE 12 1
// MAKE-SAME 3 3 2
// REVERSE 3 6
// GET-SUM 5 4
// MAX-SUM
// ```

// ### 样例输出 #1

// ```
// -1
// 10
// 1
// 10
// ```

// ## 提示

// #### 数据规模与约定

// - 你可以认为在任何时刻，数列中至少有 $1$ 个数。
// - 输入数据一定是正确的，即指定位置的数在数列中一定存在。
// - 对于 $50\%$ 的数据，任何时刻数列中最多含有 $3 \times 10^4$ 个数。
// - 对于 $100\%$ 的数据，任何时刻数列中最多含有 $5 \times 10^5$ 个数，任何时刻数列中任何一个数字均在 $[-10^3, 10^3]$ 内，$1 \le M \le 2 \times 10^4$，插入的数字总数不超过 $4 \times 10^6$。

// 题面由 @syksykCCC 提供。
#include <iostream>
#include <bits/stdc++.h>

namespace BST{
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define rd(x) tree[x].rd
    #define v(x) tree[x].val
    #define sz(x) tree[x].sz
    #define sum(x) tree[x].sum
    #define mx(x) tree[x].mx
    #define mxl(x) tree[x].mxl
    #define mxr(x) tree[x].mxr
    #define cov(x) tree[x].cov
    #define tag(x) tree[x].tag
    #define inf 0X3f3f3f3f

    std::mt19937 rnd(114514);
    struct node{
        int ls, rs, rd, sz, val, mx, sum, mxl, mxr, cov;
        bool tag;
    };

    class Treap
    {
    private:
        node* tree;
        int tot = 0, root = 0, rx = 0, ry = 0, rz = 0;
        std::stack<int> s;

        inline int getNode(int);

        inline void pushUp(int&);

        inline void pushDown(int&);

        inline void split(int, int, int&, int&);

        inline int merger(int, int);

        inline void reclaim(int);
    public:
        Treap(int);

        ~Treap();

        inline void ins(int, int);

        inline void del(int, int);

        inline void reverse(int, int);

        inline void modify(int, int, int);

        inline int getSum(int, int);

        inline int getMxSum();
    };
    
    Treap::Treap(int n){
        tree = new node[n + 1];
        ls(0) = rs(0) = sz(0) = rd(0) = sum(0) = 0;
        mx(0) = INT32_MIN, mxl(0) = mxr(0) = 0;         
    }
    
    Treap::~Treap(){
        delete[] tree;
    }

    inline int Treap::getNode(int v){
        int x;
        if(!s.empty()) x = s.top(), s.pop();
        else x = ++tot;
        ls(x) = rs(x) = 0, tag(x) = 0, sz(x) = 1;
        mx(x) = sum(x) = v(x) = v;
        mxl(x) = mxr(x) = std::max(v, 0);
        cov(x) = -inf, rd(x) = rnd();
        return x;
    }

    inline void Treap::pushUp(int& x){
        sz(x) = sz(ls(x)) + sz(rs(x)) + 1;
        sum(x) = v(x) + sum(ls(x)) + sum(rs(x));
        mx(x) = std::max({mx(ls(x)), mx(rs(x)), mxr(ls(x)) + v(x) + mxl(rs(x))});
        mxr(x) = std::max(mxr(ls(x)) + v(x) + sum(rs(x)), mxr(rs(x)));
        mxl(x) = std::max(mxl(ls(x)), sum(ls(x)) + v(x) + mxl(rs(x)));
    }

    inline void Treap::pushDown(int& x){
        if(tag(x)){
            if(ls(x)) tag(ls(x)) ^= 1, std::swap(ls(ls(x)), rs(ls(x))), std::swap(mxl(ls(x)), mxr(ls(x)));
            if(rs(x)) tag(rs(x)) ^= 1, std::swap(ls(rs(x)), rs(rs(x))), std::swap(mxl(rs(x)), mxr(rs(x)));
            tag(x) = 0;
        }
        if(cov(x) != -inf){
            if(ls(x)){
                cov(ls(x)) = v(ls(x)) = cov(x), sum(ls(x)) = sz(ls(x)) * cov(x);
                mxl(ls(x)) = mxr(ls(x)) = std::max(0, sum(ls(x)));
                mx(ls(x)) = cov(x) < 0? cov(x):sum(ls(x));
            }
            if(rs(x)){
                cov(rs(x)) = v(rs(x)) = cov(x), sum(rs(x)) = sz(rs(x)) * cov(x);
                mxl(rs(x)) = mxr(rs(x)) = std::max(0, sum(rs(x)));
                mx(rs(x)) = cov(x) < 0? cov(x):sum(rs(x));
            }
            cov(x) = -inf;
        }
    }

    inline void Treap::split(int k, int r, int& x, int& y){
        if(!r){
            x = y = 0;
            return ;
        }
        pushDown(r);
        if(sz(ls(r)) < k) x = r, split(k - sz(ls(r)) - 1, rs(r), rs(x), y);
        else y = r, split(k, ls(r), x, ls(y));
        pushUp(r);
    }

    inline int Treap::merger(int x, int y){
        if(!x || !y) return x | y;
        if(rd(x) < rd(y)){
            pushDown(x);
            rs(x) = merger(rs(x), y);
            pushUp(x);
            return x;
        }
        else{
            pushDown(y);
            ls(y) = merger(x, ls(y));
            pushUp(y);
            return y;
        }
    }

    inline void Treap::reclaim(int r){
        if(!r) return ;
        reclaim(ls(r)), reclaim(rs(r)), s.push(r);
    }

    inline void Treap::ins(int k, int n){
        if(!n) return;
        int v; rz = 0;
        split(k, root, rx, ry);
        for(int i = 0; i < n; i++){
            std::cin >> v;
            rz = merger(rz, getNode(v));
        }
        root = merger(merger(rx, rz), ry);
    }

    inline void Treap::del(int k, int n){
        if(!n) return ;
        split(k - 1, root, rx, ry);
        split(n, ry, rz, ry);
        root = merger(rx, ry);
        reclaim(rz);
    }

    inline void Treap::modify(int k, int n, int v){
        if(!n) return ;
        split(k - 1, root, rx, ry);
        split(n, ry, rz, ry);
        cov(rz) = v(rz) = v, sum(rz) = sz(rz) * v;
        mx(rz) = v < 0? v:sum(rz);
        mxl(rz) = mxr(rz) = std::max(0, sum(rz));
        root = merger(merger(rx, rz), ry);
    }

    inline void Treap::reverse(int k, int n){
        if(!n) return ;
        split(k - 1, root, rx, ry);
        split(n, ry, rz, ry);
        tag(rz) ^= 1, std::swap(mxl(rz), mxr(rz)), std::swap(ls(rz), rs(rz));
        root = merger(merger(rx, rz), ry);
    }
    
    inline int Treap::getSum(int k, int n){
        if(!n) return 0;
        split(k - 1, root, rx, ry);
        split(n, ry, rz, ry);
        int res = sum(rz);
        root = merger(merger(rx, rz), ry);
        return res;
    }

    inline int Treap::getMxSum(){
        return mx(root);
    }
}

const int maxN = 5E5 + 5;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k, v;
    std::string op;
    std::cin >> n >> m;
    BST::Treap treap(maxN);
    treap.ins(0, n);
    for(int i = 0; i < m; i++){
        std::cin >> op;
        if(op[0] == 'I'){
            std::cin >> k >> n;
            treap.ins(k, n);
        }
        else if(op[0] == 'D'){
            std::cin >> k >> n;
            treap.del(k, n);
        }
        else if(op[0] == 'M' && op[2] == 'K'){
            std::cin >> k >> n >> v;
            treap.modify(k, n, v);
        }
        else if(op[0] == 'R'){
            std::cin >> k >> n;
            treap.reverse(k, n);
        }
        else if(op[0] == 'G'){
            std::cin >> k >> n;
            std::cout << treap.getSum(k, n) << '\n';
        }
        else{
            std::cout << treap.getMxSum() << '\n';
        }
    }
    return 0;
}