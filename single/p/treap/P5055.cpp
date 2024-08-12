// # 【模板】可持久化文艺平衡树

// ## 题目背景

// 这是一道模板题。

// ## 题目描述

// 您需要写一种数据结构，来维护一个序列，其中需要提供以下操作（**对于各个以往的历史版本**）：

// 1. 在第 $p$ 个数后插入数 $x$。
// 2. 删除第 $p$ 个数。
// 3. 翻转区间 $[l,r]$，例如原序列是 $\{5,4,3,2,1\}$，翻转区间 $[2,4]$ 后，结果是 $\{5,2,3,4,1\}$。
// 4. 查询区间 $[l,r]$ 中所有数的和。

// **和原本平衡树不同的一点是，每一次的任何操作都是基于某一个历史版本，同时生成一个新的版本（操作 $4$ 即保持原版本无变化），新版本即编号为此次操作的序号。**

// **本题强制在线。**

// ## 输入格式

// 第一行包含一个整数 $n$，表示操作的总数。

// 接下来 $n$ 行，每行前两个整数 $v_i, \mathrm{opt}_i$，$v_i$ 表示基于的过去版本号（$0 \le v_i < i$），$\mathrm{opt}_i$ 表示操作的序号（$1 \le \mathrm{opt}_i \le 4$）。

// 若 $\mathrm{opt}_i=1$，则接下来两个整数 $p_i, x_i$，表示操作为在第 $p_i$ 个数后插入数 $x$ 。  
// 若 $\mathrm{opt}_i=2$，则接下来一个整数 $p_i$，表示操作为删除第 $p_i$ 个数。  
// 若 $\mathrm{opt}_i=3$，则接下来两个整数 $l_i, r_i$，表示操作为翻转区间 $[l_i, r_i]$。  
// 若 $\mathrm{opt}_i=4$，则接下来两个整数 $l_i, r_i$，表示操作为查询区间 $[l_i, r_i]$ 的和。

// **强制在线规则：**  
// **令当前操作之前的最后一次 $4$ 操作的答案为 $lastans$（如果之前没有 $4$ 操作，则 $lastans=0$）。**  
// **则此次操作的 $p_i,x_i$ 或 $l_i,r_i$ 均按位异或上 $lastans$ 即可得到真实的 $p_i,x_i$ 或 $l_i,r_i$。**

// ## 输出格式

// 对于每个序号为 $4$ 的查询操作，输出一行一个数表示区间的和。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 10
// 0 1 0 1
// 1 1 1 2
// 2 4 1 2
// 3 1 2 0
// 4 4 2 1
// 5 3 5 7
// 6 4 5 6
// 4 1 7 1
// 8 3 4 6
// 9 4 4 1
// ```

// ### 样例输出 #1

// ```
// 3
// 4
// 5
// 10
// ```

// ## 提示

// **强制在线：以下针对 $p_i, x_i, l_i, r_i$ 的限制均是按位异或 $lastans$ 后的限制。**

// - 对于 $6$ 个测试点，$n \le 5000$。
// - 对于另外 $6$ 个测试点，$v_i = i - 1$。
// - 欢迎用户加强数据，可联系管理员或出题人。

// 对于 $100\%$ 的数据，$1 \le n \le 2 \times {10}^5$，$|x_i| < {10}^6$。

// 假设基于的历史版本的序列长度为 $len \ge 1$，有：  
// 若 $\mathrm{opt}_i=1$，则 $0 \le p_i \le len$。  
// 若 $\mathrm{opt}_i=2$，则 $1 \le p_i \le len$。  
// 若 $\mathrm{opt}_i=3$，则 $1 \le l_i \le r_i \le len$。  
// 若 $\mathrm{opt}_i=4$，则 $1 \le l_i \le r_i \le len$。

// 假设基于的历史版本的序列长度为 $0$，有：  
// $\mathrm{opt}_i=1$，$p_i=0$。
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

struct node{
    int v; ll sum; 
    int rd, sz, ls, rs;
    bool tag;
    node(int v = 0, ll sum = 0, int rd = 0, int sz = 0, int ls = 0, int rs = 0, bool tag = 0):
        v(v), sum(sum), rd(rd), sz(sz), ls(ls), rs(rs), tag(tag){}
};

class Treap{
private:
    #define v(x) tree[x].v
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define sz(x) tree[x].sz
    #define rd(x) tree[x].rd
    #define sum(x) tree[x].sum
    #define tag(x) tree[x].tag

    node *tree;
    int *root, rx, ry, rz, tot = 0, cnt = 0;
    std::mt19937 rnd;

    inline void getNode(int& x, int v){
        tree[x = ++tot] = node(v, v, rnd(), 1);
    }

    inline void getNode(int& x, node& cpy){
        tree[x = ++tot] = cpy;
    }

    inline void pushUp(int& x){
        sz(x) = sz(ls(x)) + sz(rs(x)) + 1;
        sum(x) = sum(ls(x)) + sum(rs(x)) + v(x);
    }

    inline void pushDown(int& x){
        if(tag(x)){
            if(ls(x)) getNode(ls(x), tree[ls(x)]), tag(ls(x)) ^= 1;
            if(rs(x)) getNode(rs(x), tree[rs(x)]), tag(rs(x)) ^= 1;
            std::swap(ls(x), rs(x));
            tag(x) = 0;
        }
    }

    inline void split(int key, int r, int& x, int& y){
        if(!r){
            x = y = 0;
            return ;
        }
        pushDown(r);
        getNode(r, tree[r]);
        if(key > sz(ls(r))) x = r, split(key - sz(ls(r)) - 1, rs(r), rs(x), y);
        else y = r, split(key, ls(r), x, ls(y));
        pushUp(r);
    }

    inline int merger(int x, int y){
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
public:
    Treap(int n, int seed = 114514){
        root = new int[n + 1]{};
        tree = new node[n << 6];
        rnd = std::mt19937(seed);
    }

    ~Treap(){
        delete[] root;
        delete[] tree;
    }

    inline void ins(int f, int p, int v){
        split(p, root[f], rx, ry);
        getNode(rz, v);
        root[++cnt] = merger(merger(rx, rz), ry);
    }

    inline void del(int f, int p){
        split(p, root[f], rx, ry);
        split(p - 1, rx, rx, rz);
        root[++cnt] = merger(rx, ry);
    }

    inline void reverse(int f, int l, int r){
        split(r, root[f], rx, ry);
        split(l - 1, rx, rx, rz);
        tag(rz) ^= 1;
        root[++cnt] = merger(merger(rx, rz), ry);
    }

    inline ll query(int f, int l, int r){
        split(r, root[f], rx, ry);
        split(l - 1, rx, rx, rz);
        ll res = sum(rz);
        root[++cnt] = merger(merger(rx, rz), ry);
        return res;
    }
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, op;
    ll ans = 0, v, p, x;
    std::cin >> n;
    Treap treap(n);
    for(int i = 1; i <= n; i++){
        std::cin >> v >> op;
        if(op == 1){
            std::cin >> p >> x;
            p ^= ans, x ^= ans;
            treap.ins(v, p, x);
        }
        else if(op == 2){
            std::cin >> p;
            p ^= ans;
            treap.del(v, p);
        }
        else if(op == 3){
            std::cin >> p >> x;
            p ^= ans, x ^= ans;
            treap.reverse(v, p, x);
        }
        else if(op == 4){
            std::cin >> p >> x;
            p ^= ans, x ^= ans;
            ans = treap.query(v, p, x);
            std::cout << ans << '\n';
        }
    }
    return 0;
}