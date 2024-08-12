// # [JLOI2011] 不等式组

// ## 题目描述

// 旺汪与旺喵最近在做一些不等式的练习。这些不等式都是形如 $ax+b>c$ 的一元不等式。当然，解这些不等式对旺汪来说太简单了，所以旺喵想挑战旺汪。旺喵给出一组一元不等式，并给出一个数值。旺汪需要回答的是 $x=k$ 时成立的不等式的数量。聪明的旺汪每次都很快就给出了答案。你的任务是快速的验证旺汪的答案是不是正确的。

// ## 输入格式

// 输入第一行为一个正整数 $n$，代表接下来有 $n$ 行。

// 接下来每一行可能有 $3$ 种形式：

// 1. `Add a b c`：表明要往不等式组添加一条不等式 $ax+b>c$。
// 2. `Del i`：代表删除第 $i$ 条添加的不等式（最先添加的是第 $1$ 条）。
// 3. `Query k`：代表一个询问，即当 $x=k$ 时，在当前不等式组内成立的不等式的数量。

// 注意：一开始不等式组为空，$a,b,c,i,k$ 均为整数，且保证所有操作均合法，不会出现要求删除尚未添加的不等式的情况，但可能重复删除同一条不等式。

// ## 输出格式

// 对于每一个询问 `Query k`，输出一行一个整数，代表询问的答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 9
// Add 1 1 1
// Add -2 4 3
// Query 0
// Del 1
// Query 0
// Del 2
// Query 0
// Add 8 9 100
// Query 10
// ```

// ### 样例输出 #1

// ```
// 1
// 1
// 0
// 0
// ```

// ## 提示

// #### 样例 1 说明

// 第 $1$ 条添加到不等式组的不等式为 $x+1>1$，第 $2$ 条为 $−2x+4>3$。所以第 $1$ 个询问的时候只有第 $2$ 条不等式可以成立，故输出 `1`。

// 然后删除第 $1$ 条不等式，再询问的时候依然是只有第 $2$ 条不等式可以成立，故输出 $1$ 。

// 再删除第 $2$ 条不等式后，因为不等式组里面没有不等式了，所以没有不等式可以被满足，故输出 $0$。

// 继续加入第 $3$ 条不等式 $8x+9>100$，当 $x=k=10$ 时有 $8\times 10+9=89<100$，故也没有不等式可以被满足，依然输出 $0$。

// #### 数据规模与约定

// - 对于 $20\%$ 的数据，保证 $n\leq 10^3$。
// - 对于 $40\%$ 的数据，保证 $n\leq 10^4$。
// - 对于 $100\%$ 的数据，保证 $1\leq n\leq 10^5$，$a,b,c\in[-10^8,10^8]$，$k\in[-10^6,10^6]$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E5 + 5;

namespace BST{
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define ch(x, k) (k? rs(x):ls(x))
    #define v(x) tree[x].val
    #define cnt(x) tree[x].cnt
    #define sz(x) tree[x].sz
    #define f(x) tree[x].f
    #define get(x) (rs(f(x)) == x)

    struct node{
        int ls, rs, f, sz, cnt, val;
    };

    class Splay{
        private:
            bool type;
            int root = 0, tot = 0;
            node* tree;
            std::stack<int> stk;

            inline void getNode(int&, int);

            inline void pushUp(int&);

            inline void rotate(int);

            inline void splay(int, int);

            inline void find(int);
        public:
            Splay(int, bool);
            
            ~Splay();

            inline void ins(int);

            inline int findBound(int, bool);

            inline void del(int);

            inline int queryKth(int);
    };

    Splay::Splay(int n, bool t):type(t){
        tree = new node[n + 5];
        ls(0) = rs(0) = cnt(0) = sz(0) = f(0) = v(0) = 0;
    }

    Splay::~Splay(){
        delete[] tree;
    }

    inline void Splay::pushUp(int& x){
        sz(x) = cnt(x) + sz(ls(x)) + sz(rs(x));
    }

    inline void Splay::rotate(int x){
        int y = f(x), z = f(y), k = get(x);
        if(z) ch(z, get(y)) = x;
        if(ch(x, !k)) f(ch(x, !k)) = y;
        ch(y, k) = ch(x, !k), ch(x, !k) = y;
        f(y) = x, f(x) = z;
        pushUp(y), pushUp(x);
    }

    inline void Splay::splay(int x, int r){
        for(int fa = f(x); fa != r; rotate(x), fa = f(x)){
            if(f(fa) != r) rotate(get(x) ^ get(fa)? x:fa);
        }
        if(!r) root = x;
    }

    inline void Splay::getNode(int& x, int val){
        if(!stk.empty()) x = stk.top(), stk.pop();
        else x = ++tot;
        ls(x) = rs(x) = f(x) = sz(x) = cnt(x) = 0, v(x) = val;
    }

    inline void Splay::ins(int val){
        int r = root, fa = 0;
        while(r && v(r) != val) fa = r, r = ch(r, v(r) < val);
        if(!r) getNode(r, val);
        ++cnt(r), ++sz(r), f(r) = fa;
        if(fa) ch(fa, v(fa) < val) = r;
        splay(r, 0);
    }

    inline void Splay::find(int val){
        int r = root;
        while(ch(r, v(r) < val) && v(r) != val) r = ch(r, v(r) < val);
        splay(r, 0);
    }

    inline int Splay::findBound(int val, bool t){
        find(val);
        int r = root;
        if((v(r) < val && !t) || (v(r) > val && t)) return r;
        r = ch(r, t);
        while(ch(r, !t)) r = ch(r, !t);
        return r;
    }

    inline void Splay::del(int val){
        int pre = findBound(val, 0), suf = findBound(val, 1);
        if(pre) splay(pre, 0);
        if(suf) splay(suf, pre);
        int r = root;
        if(pre || suf) r = suf? ls(suf):rs(pre);
        --cnt(r), --sz(r);
        if(!cnt(r)){
            stk.push(r);
            if(f(r)) ch(f(r), get(r)) = 0, pushUp(f(r));
            else root = 0;
        }
        else splay(r, 0);
    }

    inline int Splay::queryKth(int val){
        find(val);
        if(type) return val > v(root)? sz(ls(root)) + cnt(root):sz(ls(root));
        else return val < v(root)? sz(rs(root)) + cnt(root):sz(rs(root));
    }
}

int v[maxN], type[maxN];
bool del[maxN];

inline int divid(int x, int y, bool t){
    bool f = (x > 0) ^ (y > 0);
    x = abs(x), y = abs(y);
    if(t && !f) return (x + y - 1) / y;
    else if(t && f) return -(x / y);
    else if(!t && !f) return x / y;
    else return -((x + y - 1) / y);
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, a, b, c, cnt = 0, zeros = 0, tot = 0;
    std::string op;
    std::cin >> n;
    BST::Splay pos(n, 1), neg(n, 0);
    for(int i = 0; i < n; i++){
        std::cin >> op >> a;
        if(op[0] == 'A'){
            std::cin >> b >> c;
            ++tot;
            if(a > 0){
                v[++cnt] = divid(c - b, a, 0);
                type[cnt] = 1;
                pos.ins(v[cnt]);
            }
            else if(a < 0){
                v[++cnt] = divid(c - b, a, 1);
                type[cnt] = -1;
                neg.ins(v[cnt]);
            }
            else{
                if(b > c){
                    type[++cnt] = 2;
                    ++zeros;
                }
                else type[++cnt] = -2;
            }
        }
        else if(op[0] == 'D'){
            if(del[a]) continue;
            del[a] = 1, --tot;
            if(type[a] == 1) pos.del(v[a]);
            else if(type[a] == -1) neg.del(v[a]);
            else if(type[a] == 2) zeros--;
        }
        else{
            int res = zeros + pos.queryKth(a) + neg.queryKth(a);
            std::cout << res << '\n';
        }
    }
    return 0;
}