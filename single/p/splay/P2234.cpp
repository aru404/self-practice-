// # [HNOI2002] 营业额统计

// ## 题目描述

// Tiger 最近被公司升任为营业部经理，他上任后接受公司交给的第一项任务便是统计并分析公司成立以来的营业情况。

// Tiger 拿出了公司的账本，账本上记录了公司成立以来每天的营业额。分析营业情况是一项相当复杂的工作。由于节假日，大减价或者是其他情况的时候，营业额会出现一定的波动，当然一定的波动是能够接受的，但是在某些时候营业额突变得很高或是很低，这就证明公司此时的经营状况出现了问题。经济管理学上定义了一种最小波动值来衡量这种情况：当最小波动值越大时，就说明营业情况越不稳定。

// 而分析整个公司的从成立到现在营业情况是否稳定，只需要把每一天的最小波动值加起来就可以了。你的任务就是编写一个程序帮助 Tiger 来计算这一个值。

// 我们定义，一天的最小波动值 = $\min\{|\text{该天以前某一天的营业额}-\text{该天营业额}|\}$。

// 特别地，第一天的最小波动值为第一天的营业额。

// ## 输入格式

// 第一行为正整数 $n$（$n \leq 32767$） ，表示该公司从成立一直到现在的天数，接下来的 $n$ 行每行有一个整数 $a_i$（$|a_i| \leq 10^6$) ，表示第 $i$ 天公司的营业额，可能存在负数。

// ## 输出格式

// 输出一个正整数，即每一天最小波动值的和，保证结果小于 $2^{31}$。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6
// 5
// 1
// 2
// 5
// 4
// 6
// ```

// ### 样例输出 #1

// ```
// 12
// ```

// ## 提示

// 结果说明：$5+|1-5|+|2-1|+|5-5|+|4-5|+|6-5|=5+4+1+0+1+1=12$
#include <iostream>
#include <bits/stdc++.h>

namespace BST{
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define f(x) tree[x].f
    #define v(x) tree[x].v
    #define cnt(x) tree[x].cnt
    #define get(x) (rs(f(x)) == x)
    #define ch(x, k) (k? rs(x):ls(x))
    #define inf 0X3f3f3f3f

    struct node{
        int ls, rs, f, v, cnt;
    };

    class Splay{
        private:
            int root = 0, tot = 0;
            node* tree;

            inline int getNode(int);

            inline void rotate(int);

            inline void splay(int, int);

            inline void find(int);
        public:
            Splay(int);

            ~Splay();

            inline void ins(int);

            inline int findBound(int, bool);

            inline int suf(int);

            inline int pre(int);

            inline int updata(int);
    };

    Splay::Splay(int n){
        tree = new node[n + 5];
        f(0) = ls(0) = rs(0) = cnt(0) = 0, v(0) = inf;
        ins(inf), ins(-inf);
    }

    Splay::~Splay(){
        delete[] tree;
    }

    inline int Splay::getNode(int v){
        int x = ++tot;
        ls(x) = rs(x) = f(x) = 0, v(x) = v, cnt(x) = 1;
        return x;
    }

    inline void Splay::rotate(int x){
        int y = f(x), z = f(y), k = get(x);
        if(z) ch(z, get(y)) = x;
        if(ch(x, !k)) f(ch(x, !k)) = y;
        ch(y, k) = ch(x, !k), ch(x, !k) = y;
        f(x) = z, f(y) = x;
    }

    inline void Splay::splay(int x, int r){
        if(!x) return ;
        for(int fa = f(x); fa != r; rotate(x), fa = f(x)){
            if(f(fa) != r) rotate(get(x) ^ get(fa)? fa:x);
        }
        if(!r) root = x; 
    }

    inline void Splay::find(int v){
        int r = root;
        while(v != v(r) && ch(r, v(r) < v)) r = ch(r, v(r) < v);
        splay(r, 0);
    }

    inline void Splay::ins(int v){
        int r = root, fa = 0;
        while(r && v(r) != v) fa = r, r = ch(r, v(r) < v);
        if(!r){
            r = getNode(v), f(r) = fa;
            if(fa) ch(fa, v(fa) < v) = r;
        }
        else ++cnt(r);
        splay(r, 0);
    }

    inline int Splay::findBound(int v, bool f){
        find(v);
        int r = root;
        if((v(r) < v && !f) || (v(r) > v && f)) return r;
        r = ch(r, f);
        while(ch(r, !f)) r = ch(r, !f);
        return r;
    }

    inline int Splay::updata(int v){
        find(v);
        int res = inf;
        if(v(root) == v){
            ins(v);
            return 0;
        }
        splay(findBound(v, 0), 0), res = std::min(res, v - v(root));
        splay(findBound(v, 1), 0), res = std::min(res, v(root) - v);
        ins(v);
        return res;
    }
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, v;
    std::cin >> n;
    BST::Splay splay(n);
    int res = 0;
    std::cin >> v;
    res = v, splay.updata(v);
    for(int i = 1; i < n; i++){
        std::cin >> v;
        res += splay.updata(v);
    }
    std::cout << res;
    return 0;
}