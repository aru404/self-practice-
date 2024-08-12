// # [ZJOI2006] 书架

// ## 题目描述

// 小 T 有一个很大的书柜。这个书柜的构造有些独特，即书柜里的书是从上至下堆放成一列。她用 $1$ 到 $n$ 的正整数给每本书都编了号。

// 小 T 在看书的时候，每次取出一本书，看完后放回书柜然后再拿下一本。由于这些书太有吸引力了，所以她看完后常常会忘记原来是放在书柜的什么位置。不过小 T 的记忆力是非常好的，所以每次放书的时候至少能够将那本书放在拿出来时的位置附近，比如说她拿的时候这本书上面有 $x$ 本书，那么放回去时这本书上面就只可能有 $x-1$、$x$ 或 $x+1$ 本书。

// 当然也有特殊情况，比如在看书的时候突然电话响了或者有朋友来访。这时候粗心的小 T 会随手把书放在书柜里所有书的最上面或者最下面，然后转身离开。

// 久而久之，小 T 的书柜里的书的顺序就会越来越乱，找到特定的编号的书就变得越来越困难。于是她想请你帮她编写一个图书管理程序，处理她看书时的一些操作，以及回答她的两个提问：
// - 编号为 $x$ 的书在书柜的什么位置。
// - 从上到下第 $i$ 本书的编号是多少。

// ## 输入格式

// 第一行有两个整数，分别表示书的个数 $n$ 以及命令条数 $m$。

// 第二行有 $n$ 个整数，第 $i$ 个整数表示初始时从上向下书第 $i$ 本书的编号 $p_i$。

// 接下来 $m$ 行，每行表示一个操作。每行初始时有一个字符串  $op$。

// - 若 $op$ 为 `Top`，则后有一个整数 $s$，表示把编号为 $s$ 的书放在最上面。
// - 若 $op$ 为 `Bottom`，则后有一个整数 $s$，表示把编号为 $s$ 的书放在最下面。
// - 若 $op$ 为 `Insert`，则后有两个整数 $s, t$，表示若编号为 $s$ 的书上面有 $x$ 本书，则放回这本书时他的上面有 $x + t$ 本书。
// - 若 $op$ 为 `Ask`，则后面有一个整数 $s$，表示询问编号为 $s$ 的书上面有几本书。
// - 若 $op$ 为 `Query`，则后面有一个整数 $s$，询问从上面起第 $s$ 本书的编号。

// ## 输出格式

// 对于每次查询，输出一行一个整数表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 10 10
// 1 3 2 7 5 8 10 4 9 6
// Query 3
// Top 5
// Ask 6
// Bottom 3
// Ask 3
// Top 6
// Insert 4 -1
// Query 5
// Query 2
// Ask 2
// ```

// ### 样例输出 #1

// ```
// 2
// 9
// 9
// 7
// 5
// 3
// ```

// ## 提示

// ### 数据规模与约定

// 对于 $100\%$ 的数据，保证：
// - $3 \leq n, m \leq 8 \times 10^4$。
// - $p_i$ 是一个 $1 \sim n$ 的排列。
// - $1 \leq s \leq n$，$-1 \leq t \leq 1$，$op$ 只可能是输入的五种字符串之一。
// - 当编号为 $s$ 的书上面没有书的时候，不会对它进行 `Insert s -1` 操作。
// - 当编号为 $s$ 的书下面没有书的时候，不会对它进行 `Insert s 1` 操作。
#include <iostream>
#include <bits/stdc++.h>

struct node{
    int ls, rs, sz, rd;
    node(int ls = 0, int rs = 0, int sz = 0, int rd = 0):
        ls(ls), rs(rs), sz(sz), rd(rd){}
};

class Treap{
private:
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define rd(x) tree[x].rd
    #define sz(x) tree[x].sz

    std::mt19937 rnd;
    node *tree;
    int *f, root = 0, rw, rx, ry, rz, n;

    inline void pushUp(int& x){
        sz(x) = sz(ls(x)) + sz(rs(x)) + 1;
    }

    inline void split(int key, int r, int& x, int& y){
        f[r] = 0;
        if(!r){
            x = y = 0;
            return ;
        }
        if(key > sz(ls(r))){
            x = r;
            split(key - sz(ls(r)) - 1, rs(r), rs(x), y);
            f[rs(x)] = x;
        }
        else{
            y = r;
            split(key, ls(r), x, ls(y));
            f[ls(y)] = y;
        }
        pushUp(r);
    }

    inline int merger(int x, int y){
        if(!x || !y) return x | y;
        if(rd(x) < rd(y)){
            rs(x) = merger(rs(x), y);
            f[rs(x)] = x;
            pushUp(x);
            return x;
        }
        else{
            ls(y) = merger(x, ls(y));
            f[ls(y)] = y;
            pushUp(y);
            return y;
        }
    }
public:
    Treap(int n, int* arr, int seed = 114514):n(n){
        rnd = std::mt19937(seed);
        tree = new node[n + 1];
        tree[0] = node();
        f = new int[n + 1]{};
        for(int i = 1; i <= n; i++){
            tree[arr[i]] = node(0, 0, 1, rnd());
            root = merger(root, arr[i]);
        }
    }

    ~Treap(){
        delete[] tree;
        delete[] f;
    }

    inline int ask(int id){
        int rk = sz(ls(id)) + 1, fa = f[id];
        while(fa){
            if(rs(fa) == id) rk += sz(ls(fa)) + 1;
            id = fa, fa = f[fa];
        }
        return rk;
    }

    inline void ins(int id, int d){
        if(!d) return;
        int rk = ask(id);
        split(rk - 1, root, rw, rx);
        split(1, rx, rx, ry);
        if(d > 0){
            split(d, ry, ry, rz);
            root = merger(merger(merger(rw, ry), rx), rz);
        }
        else{
            split(rk + d - 1, rw, rw, rz);
            root = merger(merger(merger(rw, rx), rz), ry);
        }
    }

    inline void insBottom(int id){
        int rk = ask(id);
        if(rk == n) return ;
        split(rk - 1, root, rw, rx);
        split(1, rx, rx, ry);
        root = merger(merger(rw, ry), rx);
    }

    inline void insTop(int id){
        int rk = ask(id);
        if(rk == 1) return ;
        split(rk - 1, root, rw, rx);
        split(1, rx, rx, ry);
        root = merger(merger(rx, rw), ry);
    }

    inline int query(int rk){
        int r = root;
        while(rk != sz(ls(r)) + 1){
            if(rk <= sz(ls(r))) r = ls(r);
            else rk -= sz(ls(r)) + 1, r = rs(r);
        }
        return r;
    }
};

const int maxN = 8E4 + 5;
int arr[maxN];

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, x, d;
    std::string op;
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++) std::cin >> arr[i];
    Treap treap(n, arr);

    for(int i = 0; i < m; i++){
        std::cin >> op >> x;
        if(op[0] == 'T') treap.insTop(x);
        else if(op[0] == 'B') treap.insBottom(x);
        else if(op[0] == 'I') std::cin >> d, treap.ins(x, d);
        else if(op[0] == 'A') std::cout << treap.ask(x) - 1<< '\n';
        else if(op[0] == 'Q') std::cout << treap.query(x) << '\n'; 
    }

    return 0;
}