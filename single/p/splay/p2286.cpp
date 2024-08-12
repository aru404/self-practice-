// # [HNOI2004] 宠物收养场

// ## 题目描述

// 凡凡开了一间宠物收养场。收养场提供两种服务：收养被主人遗弃的宠物和让新的主人领养这些宠物。

// 每个领养者都希望领养到自己满意的宠物，凡凡根据领养者的要求通过他自己发明的一个特殊的公式，得出该领养者希望领养的宠物的特点值a（a是一个正整数，a<2^31），而他也给每个处在收养场的宠物一个特点值。这样他就能够很方便的处理整个领养宠物的过程了，宠物收养场总是会有两种情况发生：被遗弃的宠物过多或者是想要收养宠物的人太多，而宠物太少。

// 被遗弃的宠物过多时，假若到来一个领养者，这个领养者希望领养的宠物的特点值为a，那么它将会领养一只目前未被领养的宠物中特点值最接近a的一只宠物。（任何两只宠物的特点值都不可能是相同的，任何两个领养者的希望领养宠物的特点值也不可能是一样的）如果有两只满足要求的宠物，即存在两只宠物他们的特点值分别为a-b和a+b，那么领养者将会领养特点值为a-b的那只宠物。

// 收养宠物的人过多，假若到来一只被收养的宠物，那么哪个领养者能够领养它呢？能够领养它的领养者，是那个希望被领养宠物的特点值最接近该宠物特点值的领养者，如果该宠物的特点值为a，存在两个领养者他们希望领养宠物的特点值分别为a-b和a+b，那么特点值为a-b的那个领养者将成功领养该宠物。

// 一个领养者领养了一个特点值为a的宠物，而它本身希望领养的宠物的特点值为b，那么这个领养者的不满意程度为abs(a-b)。

// 你得到了一年当中，领养者和被收养宠物到来收养所的情况，请你计算所有收养了宠物的领养者的不满意程度的总和。这一年初始时，收养所里面既没有宠物，也没有领养者。

// ## 输入格式

// 第一行为一个正整数n，n<=80000，表示一年当中来到收养场的宠物和领养者的总数。接下来的n行，按到来时间的先后顺序描述了一年当中来到收养场的宠物和领养者的情况。每行有两个正整数a, b，其中a=0表示宠物，a=1表示领养者，b表示宠物的特点值或是领养者希望领养宠物的特点值。（同一时间呆在收养所中的，要么全是宠物，要么全是领养者，这些宠物和领养者的个数不会超过10000个）

// ## 输出格式

// 仅有一个正整数，表示一年当中所有收养了宠物的领养者的不满意程度的总和mod 1000000以后的结果。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5                  
// 0 2                      
// 0 4                         
// 1 3
// 1 2
// 1 5
// ```

// ### 样例输出 #1

// ```
// 3
// 注：abs(3-2) + abs(2-4)=3，
// 最后一个领养者没有宠物可以领养。
// ```
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 8E4 + 5;

namespace Splay{
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define f(x) tree[x].f
    #define v(x) tree[x].v
    #define cnt(x) tree[x].cnt
    #define son(x, f) (f? rs(x):ls(x))
    #define get(x) (rs(f(x)) == x)
    
    struct node{
        int ls, rs, f, v, cnt;
    };

    class BST{
        private:
            node* tree;
            std::stack<int> stk;
            int idx = 0, root = 0;

            inline void rotate(int);

            inline void getNew(int&);
        public:
            BST(int);

            ~BST();

            inline void splay(int, int);

            inline void find(int);

            inline int findBound(int, bool);

            inline void ins(int);

            inline void del(int);

            inline node& top();
    };

    BST::BST(int n){
        tree = new node[n + 1];
        tree[0] = {0, 0, 0, 0, 0};
    }

    BST::~BST(){
        delete[] tree;
    }

    inline void BST::rotate(int x){
        int y = f(x), z = f(y), k = get(x);
        if(z) son(z, get(y)) = x;
        if(son(x, !k)) f(son(x, !k)) = y;
        son(y, k) = son(x, !k), son(x, !k) = y;
        f(y) = x, f(x) = z;
    }

    inline void BST::splay(int x, int r){
        for(int fa = f(x); fa != r; rotate(x), fa = f(x)){
            if(f(fa) != r) rotate(get(x) ^ get(fa)? x:fa);
        }
        if(!r) root = x;
    }

    inline void BST::find(int v){
        int r = root;
        while(son(r, v(r) < v) && v(r) != v) r = son(r, v(r) < v);
        splay(r, 0);
    }

    inline void BST::getNew(int& x){
        if(!stk.empty()) x = stk.top(), stk.pop();
        else x = ++idx;
        ls(x) = rs(x) = cnt(x) = v(x) = f(x) = 0;
    }

    inline int BST::findBound(int v, bool f){
        find(v);
        if((v(root) < v && !f) || (v(root) > v && f)) return root;
        int r = f? rs(root):ls(root);
        while(son(r, !f)) r = son(r, !f);
        return r;
    }

    inline void BST::ins(int v){
        int r = root, fa = 0;
        while(r && v(r) != v) fa = r, r = son(r, v(r) < v);
        if(!r){
            getNew(r), v(r) = v, f(r) = fa;
            if(fa) son(fa, v(fa) < v) = r;
        }
        ++cnt(r);
        splay(r, 0);
    }

    inline void BST::del(int v){
        int pre = findBound(v, 0), suf = findBound(v, 1);
        if(pre) splay(pre, 0);
        if(suf) splay(suf, pre);
        int r = root;
        if(pre || suf) r = suf? ls(suf):rs(pre);
        --cnt(r);
        if(!cnt(r)){
            if(f(r)) son(f(r), get(r)) = 0;
            else root = 0;
            stk.emplace(r), r = 0;
        }
        else splay(r, 0);
    }

    inline node& BST::top(){
        return tree[root];
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int mod = 1E6, n, op, cnt1 = 0, cnt2 = 0, res = 0;
    long long v;
    std::cin >> n;
    using namespace Splay;

    BST tree(n);
    for(int i = 0; i < n; i++){
        std::cin >> op >> v;
        if(!op){
            if(!cnt2) ++cnt1, tree.ins(v);
            else{
                --cnt2;
                tree.find(v);
                if(tree.top().v == v) {tree.del(v); continue;}
                int pre = tree.findBound(v, 0);
                if(pre) tree.splay(pre, 0), pre = tree.top().v;
                else pre = INT32_MIN;
                int suf = tree.findBound(v, 1);
                if(suf) tree.splay(suf, 0), suf = tree.top().v;
                else suf = INT32_MAX;
                res = (res + std::min(suf - v, v - pre)) % mod;
                if(1ll * suf + pre >= v << 1) tree.del(pre);
                else tree.del(suf);
            }
        }
        else{
            if(!cnt1) ++cnt2, tree.ins(v);
            else{
                --cnt1;
                tree.find(v);
                if(tree.top().v == v) {tree.del(v); continue;}
                int pre = tree.findBound(v, 0);
                if(pre) tree.splay(pre, 0), pre = tree.top().v;
                else pre = INT32_MIN;
                int suf = tree.findBound(v, 1);
                if(suf) tree.splay(suf, 0), suf = tree.top().v;
                else suf = INT32_MAX;
                res = (res + std::min(suf - v, v - pre)) % mod;
                if(1ll * suf + pre >= v << 1) tree.del(pre);
                else tree.del(suf);
            }
        }
    }
    std::cout << res;
    return 0;
}