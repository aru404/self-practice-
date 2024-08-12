// # 【模板】普通平衡树（数据加强版）

// ## 题目背景

// 本题是 P3369 数据加强版，**扩大数据范围**并增加了**强制在线**。

// **题目的输入、输出和原题略有不同**，但需要支持的操作相同。

// ## 题目描述

// 您需要写一种数据结构（可参考题目标题），来维护一些整数，其中需要提供以下操作：

// 1. 插入一个整数 $x$。
// 2. 删除一个整数 $x$（若有多个相同的数，只删除一个）。
// 3. 查询整数 $x$ 的排名（排名定义为比当前数小的数的个数 $+1$）。
// 4. 查询排名为 $x$ 的数（如果不存在，则认为是排名小于 $x$ 的最大数。保证 $x$ 不会超过当前数据结构中数的总数）。
// 5. 求 $x$ 的前驱（前驱定义为小于 $x$，且最大的数）。
// 6. 求 $x$ 的后继（后继定义为大于 $x$，且最小的数）。

// 本题**强制在线**，保证所有操作合法（操作 $2$ 保证存在至少一个 $x$，操作 $4,5,6$ 保证存在答案）。

// ## 输入格式

// 第一行两个正整数 $n,m$，表示**初始数的个数**和操作的个数。

// **第二行 $n$ 个整数 $a_1,a_2,a_3,\ldots,a_n$，表示初始的数**。

// 接下来 $m$ 行，每行有两个整数 $\text{opt}$ 和 $x'$，$\text{opt}$ 表示操作的序号（$ 1 \leq \text{opt} \leq 6 $），$x'$ 表示加密后的操作数。

// 我们记 $\text{last}$ 表示上一次 $3,4,5,6$ 操作的答案，则每次操作的 $x'$ 都要**异或**上 $\text{last}$ 才是真实的 $x$。初始 $\text{last}$ 为 $0$。

// ## 输出格式

// 输出一行一个整数，表示所有 $3,4,5,6$ 操作的答案的**异或和**。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6 7
// 1 1 4 5 1 4
// 2 1
// 1 9
// 4 1
// 5 8
// 3 13
// 6 7
// 1 4
// ```

// ### 样例输出 #1

// ```
// 6
// ```

// ## 提示

// ### 样例解释

// 样例加密前为：
// ```plain
// 6 7
// 1 1 4 5 1 4
// 2 1
// 1 9
// 4 1
// 5 9
// 3 8
// 6 1
// 1 0
// ```

// ### 限制与约定

// 对于 $100\%$ 的数据，$1\leq n\leq 10^5$，$1\leq m\leq 10^6$，$0\leq a_i,x\lt 2^{30}$。

// **本题输入数据较大，请使用较快的读入方式。**

// ---

// $\text{upd 2022.7.22}$：新增加 $9$ 组 Hack 数据。
// 有旋treap

// #include <iostream>
// #include <bits/stdc++.h>

// const int maxN = 1.1E6 + 5;

// namespace BST{
//     #define ls(x) tree[x].ch[0]
//     #define rs(x) tree[x].ch[1]
//     #define v(x) tree[x].val
//     #define cnt(x) tree[x].cnt
//     #define sz(x) tree[x].sz
//     #define rd(x) tree[x].rd
//     #define ch(x, y) (y? rs(x):ls(x))

//     struct node{
//         int ch[2], sz, val, rd, cnt;
//     }tree[maxN];

//     int seed = 114514, tot = 0, inf = INT32_MAX, root = 0;
//     std::stack<int> stk;

//     inline int rand(){
//         return seed = seed * 104831ll % 0X7fffffff;
//     }

//     inline void get(int& x){
//         if(!stk.empty()) x = stk.top(), stk.pop();
//         else x = ++tot;
//     }

//     inline void pushUp(int x){
//         sz(x) = cnt(x) + sz(ls(x)) + sz(rs(x));
//     }

//     inline void rotate(int& x, bool d){
//         int p = ch(x, d ^ 1);
//         ch(x, d ^ 1) = ch(p, d);
//         ch(p, d) = x;
//         pushUp(x), pushUp(p);
//         x = p;
//     }

//     inline void ins(int& x, int v){
//         if(!x){
//             get(x);
//             ls(x) = rs(x) = 0, sz(x) = cnt(x) = 1, v(x) = v;
//             rd(x) = rand();
//             return ;
//         }
//         if(v(x) == v){
//             sz(x)++, cnt(x)++;
//             return ;
//         }
//         bool d = v(x) < v;
//         ins(ch(x, d), v);
//         if(rd(x) < rd(ch(x, d))) rotate(x, !d);
//         pushUp(x);
//     }

//     inline void del(int& x, int v){
//         if(!x) return ;
//         if(v(x) != v) del(ch(x, v(x) < v), v);
//         else{
//             if(!ls(x) && !rs(x)){
//                 --cnt(x), --sz(x);
//                 if(!cnt(x)) stk.emplace(x), x = 0;
//             }
//             else{
//                 bool d = ls(x) && rs(x)? rd(ls(x)) > rd(rs(x)):ls(x);
//                 rotate(x, d);
//                 del(ch(x, d), v);
//             }
//         }
//         pushUp(x);
//     }

//     inline int queryRk(int& x, int v){
//         if(!x) return 1;
//         if(v(x) > v) return queryRk(ls(x), v);
//         if(v(x) < v) return queryRk(rs(x), v) + sz(ls(x)) + cnt(x);
//         return sz(ls(x)) + 1;
//     }

//     inline int find(int& x, int rk){
//         if(!x) return 0;
//         if(rk <= sz(ls(x))) return find(ls(x), rk);
//         if(rk > sz(ls(x)) + cnt(x)) return std::max(v(x), find(rs(x), rk - sz(ls(x)) - cnt(x)));
//         return v(x);
//     }

//     inline int pre(int& x, int v){
//         if(!x) return -inf;
//         if(v(x) >= v) return pre(ls(x), v);
//         return std::max(v(x), pre(rs(x), v));
//     }

//     inline int suf(int& x, int v){
//         if(!x) return inf;
//         if(v(x) <= v) return suf(rs(x), v);
//         return std::min(v(x), suf(ls(x), v));
//     }
// }

// int main(){
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);

//     int n, m, v, op, last = 0, res = 0;
//     std::cin >> n >> m;
//     for(int i = 0; i < n; i++) std::cin >> v, BST::ins(BST::root, v);
//     for(int i = 0; i < m; i++){
//         std::cin >> op >> v;
//         v ^= last;
//         if(op == 1) BST::ins(BST::root, v);
//         else if(op == 2) BST::del(BST::root, v);
//         else if(op == 3) last = BST::queryRk(BST::root, v);
//         else if(op == 4) last = BST::find(BST::root, v);
//         else if(op == 5) last = BST::pre(BST::root, v);
//         else if(op == 6) last = BST::suf(BST::root, v);
        
//         if(op >= 3) res ^= last;
//     }
//     std::cout << res;
//     return 0;
// }


#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1.1E6 + 5, inf = INT32_MAX;

namespace BST{
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define cnt(x) tree[x].cnt
    #define v(x) tree[x].val
    #define sz(x) tree[x].sz
    #define rd(x) tree[x].rd

    int tot = 0, root = 0, rx, ry, rz, seed = 114514;
    std::mt19937 rnd(seed);
    std::stack<int> stk;

    struct node{
        int val, cnt, sz, ls, rs, rd;
    }tree[maxN];

    inline void get(int& x, int v){
        if(!stk.empty()) x = stk.top(), stk.pop();
        else x = ++tot;
        v(x) = v, cnt(x) = sz(x) = 1, ls(x) = rs(x) = 0, rd(x) = rnd();
    }

    inline void pushUp(int& x){
        sz(x) = sz(ls(x)) + sz(rs(x)) + cnt(x);
    }

    inline void split(int key, int r, int& x, int& y){
        if(!r){
            x = y = 0;
            return ;
        }
        if(v(r) <= key) x = r, split(key, rs(r), rs(x), y);
        else y = r, split(key, ls(r), x, ls(y));
        pushUp(r);
    }

    inline int merger(int x, int y){
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

    inline void ins(int v){
        split(v, root, rx, ry);
        split(v - 1, rx, rx, rz);
        if(!rz) get(rz, v);
        else ++cnt(rz), ++sz(rz);
        root = merger(merger(rx, rz), ry);
    }

    inline void del(int v){
        split(v, root, rx, ry);
        split(v - 1, rx, rx, rz);
        if(rz){
            --cnt(rz), --sz(rz);
            if(!cnt(rz)) stk.push(rz), rz = 0;
        }
        root = merger(merger(rx, rz), ry);
    }

    inline int queryRk(int v){
        split(v - 1, root, rx, ry);
        int res = sz(rx) + 1;
        root = merger(rx, ry);
        return res;
    }

    inline int queryKth(int& x, int rk){
        if(!x) return -inf;
        if(sz(ls(x)) >= rk) return queryKth(ls(x), rk);
        if(sz(ls(x)) + cnt(x) < rk) return std::max(v(x), queryKth(rs(x), rk - sz(ls(x)) - cnt(x)));
        return v(x);
    }

    inline int pre(int v){
        split(v - 1, root, rx, ry);
        int tmp = rx;
        while(rs(tmp)) tmp = rs(tmp);
        root = merger(rx, ry);
        return tmp? v(tmp):-inf;
    }

    inline int suf(int v){
        split(v, root, rx, ry);
        int tmp = ry;
        while(ls(tmp)) tmp = ls(tmp);
        root = merger(rx, ry);
        return tmp? v(tmp):inf;
    }
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, m, res = 0, last = 0, op, v;
    std::cin >> n >> m;
    for(int i = 0; i < n; i++) std::cin >> v, BST::ins(v);
    for(int i = 0; i < m; i++){
        std::cin >> op >> v;
        v ^= last;
        if(op == 1) BST::ins(v);
        else if(op == 2) BST::del(v);
        else if(op == 3) last = BST::queryRk(v);
        else if(op == 4) last = BST::queryKth(BST::root, v);
        else if(op == 5) last = BST::pre(v);
        else if(op == 6) last = BST::suf(v);

        if(op > 2) res ^= last;
    }
    std::cout << res;
    return 0;
}