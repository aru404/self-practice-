// # 宝石管理系统

// ## 题目描述

// GY 君购买了一批宝石放进了仓库。有一天 GY 君心血来潮，想要清点他的宝石，于是把 $m$ 个宝石都取出来放进了宝石管理系统。每个宝石 $i$ 都有一个珍贵值 $v_i$，他希望你能编写程序查找到从大到小第 $n$ 珍贵的宝石。但是现在问题来了，他非常不小心的留了一些宝石在仓库里面，有可能要往现有的系统中添加宝石。这些宝石的个数比较少。他表示非常抱歉，但是还是希望你的系统能起作用。

// ## 输入格式

// 第一行两个整数 $m,q$，表示已经取出来的宝石个数以及接下来的查询或插入操作个数。

// 第二行 $m$ 个正整数，表示这 $m$ 个宝石的珍贵值。

// 以下 $q$ 行，每行两个整数 $c,n$。

// 若 $c=1$（即询问），则输出当前第 $n$ 珍贵的宝石。

// 若 $c=2$（即插入），则往系统中插入珍贵值为 $n$ 的宝石。

// ## 输出格式

// 对于每个 $c=1$（询问）,输出当前第 $n$ 珍贵的宝石的珍贵值 $v_i$。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 3
// 1 3 2 5 6
// 1 3
// 2 4
// 1 6
// ```

// ### 样例输出 #1

// ```
// 3
// 1
// ```

// ## 提示

// 对于 $50\%$ 的数据，没有 $c=2$ 的情况；

// 对于 $100\%$ 的数据，$m\leq 100000$，$c=2$ 的情况不超过 $10000$ 次，$q\leq 30000$，$1 \leq v_i \lt 2^{31}$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1.1E5 + 5;

namespace BST{
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define f(x) tree[x].f
    #define cnt(x) tree[x].cnt
    #define sz(x) tree[x].sz
    #define v(x) tree[x].val
    #define ch(x, k) (k? rs(x):ls(x))
    #define get(x) (rs(f(x)) == x)
    
    struct node{
        int ls, rs, cnt, val, sz, f;
    }tree[maxN];

    std::stack<int> s;
    int tot = 0, root = 0;

    inline void pushUp(int& x){
        sz(x) = sz(ls(x)) + sz(rs(x)) + cnt(x);
    }

    inline void getNode(int& x, int val){
        if(!s.empty()) x = s.top(), s.pop();
        else x = ++tot;
        ls(x) = rs(x) = f(x) = sz(x) = cnt(x) = 0;
        v(x) = val;
    }

    inline void rotate(int x){
        int y = f(x), z = f(y), k = get(x);
        if(z) ch(z, get(y)) = x;
        if(ch(x, !k)) f(ch(x, !k)) = y;
        ch(y, k) = ch(x, !k), ch(x, !k) = y;
        f(y) = x, f(x) = z;
        pushUp(y), pushUp(x);
    }

    inline void splay(int x, int r){
        for(int fa = f(x); fa != r; rotate(x), fa = f(x)){
            if(f(fa) != r) rotate(get(x) ^ get(fa)? x:fa);
        }
        if(!r) root = x;
    }

    inline void ins(int val){
        int r = root, fa = 0;
        while(r && v(r) != val) fa = r, r = ch(r, v(r) < val);
        if(!r) getNode(r, val);
        ++cnt(r), ++sz(r), f(r) = fa;
        if(fa) ch(fa, v(fa) < val) = r;
        splay(r, 0);
    }

    inline int queryRk(int rk){
        int r = root;
        while(1){
            if(rk > sz(rs(r)) + cnt(r)) rk -= sz(rs(r)) + cnt(r), r = ls(r);
            else if(rk <= sz(rs(r))) r = rs(r);
            else break;
        }
        splay(r, 0);
        return v(r);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, op, v;
    std::cin >> n >> m;
    for(int i = 0; i < n; i++) std::cin >> v, BST::ins(v);
    for(int i = 0; i < m; i++){
        std::cin >> op >> v;
        if(op == 1) std::cout << BST::queryRk(v) << '\n';
        else BST::ins(v);
    }
    return 0;
}