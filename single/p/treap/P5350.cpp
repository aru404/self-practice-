// # 序列

// ## 题目背景

// 搬运序列

// ## 题目描述

// 有一个序列$a_n$和若干操作。

// - $\mathrm{1\  l \  r \ }$ 求$a_l$到$a_r$的和 
// - $\mathrm{2\  l \  r \ val \ }$ 将$a_l$到$a_r$赋值为$\mathrm{val}$ 
// - $\mathrm{3\  l \  r \ val\ }$将$a_l$到$a_r$加上$\mathrm{val}$ 
// - $\mathrm{4\  l_1 \  r_1 \  l_2 \  r_2 }$将$a_{l_1}$到$a_{r_1}$复制到$a_{l_2}$到$a_{r_2}$处 
// - $\mathrm{5\  l_1 \  r_1 \  l_2 \  r_2 }$将$a_{l_1}$到$a_{r_1}$与$a_{l_2}$到$a_{r_2}$交换 
// - $\mathrm{6\  l \  r \ }$将$a_l$到$a_r$翻转

// ## 输入格式

// 第一行两个数$n$和$m$，为序列长度和操作个数。

// 第二行$n$个数，为$a_i$。

// 下面$m$行，每行为操作种类和相应的若干整数。

// ## 输出格式

// 若干行，对于每个$1$操作，输出答案。

// 由于答案可能过大，对$10^9+7$取模。

// 最后一行输出序列$a_n$。当然也要取模。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 10 10
// 7 1 3 2 2 4 0 1 2 2 
// 4 10 10 3 3
// 3 4 10 5
// 6 6 7
// 6 9 10
// 1 10 10
// 5 9 10 6 7
// 2 8 10 0
// 5 4 4 5 5
// 5 2 4 8 10
// 3 3 9 0
// ```

// ### 样例输出 #1

// ```
// 7
// 7 0 0 0 7 7 7 1 2 7
// ```

// ## 提示

// **请注意常数优化**

// 若是$\mathrm{copy}$和$\mathrm{swap}$操作，保证$r_1-l_1=r_2-l_2$且区间不重叠。


// 保证数据随机。

// 对于$30\%$的数据，保证$\ n,m\le 10^3\ $。

// 对于$50\%$的数据，保证$\ n,m\le 5\times 10^4\ $。

// 对于$70\%$的数据，保证$\ n,m\le 1.5\times 10^5\ $。

// 对于$100\%$的数据，保证$\ n,m\le 3\times 10^5\ ,\ 0\le a_i,\mathrm{val}\lt Mod\ $。
#include <iostream>
#include <bits/stdc++.h>

struct node{
    int v, sum, sz, add, cov, ls, rs;
    bool tag;
    node(int v = 0, int sum = 0, int sz = 0, int add = 0,
         int cov = -1, int ls = 0, int rs = 0, bool tag = 0):
        v(v), sum(sum), sz(sz), add(add), cov(cov), ls(ls), rs(rs), tag(tag){}
};

class Treap{
private:
    #define v(x) tree[x].v
    #define sum(x) tree[x].sum
    #define sz(x) tree[x].sz
    #define add(x) tree[x].add
    #define cov(x) tree[x].cov
    #define tag(x) tree[x].tag
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs

    const int mod = 1E9 + 7, maxP = 3.2E6;
    node *tree;
    int *vs, root = 0, rv, rw, rx, ry, rz, tot = 0, cnt = 0, n;
    std::mt19937 rnd;
    std::uniform_int_distribution<int> dist;

    inline void cpy(int& x, node& p){
        x = ++tot;
        tree[x] = p;
    }

    inline void pushUp(int& x){
        sz(x) = sz(ls(x)) + sz(rs(x)) + 1;
        sum(x) = ((sum(ls(x)) + sum(rs(x))) % mod + v(x)) % mod;
    }

    inline void pushInv(int& x){
        if(ls(x)) tag(ls(x)) ^= 1;
        if(rs(x)) tag(rs(x)) ^= 1;
        std::swap(ls(x), rs(x));
        tag(x) = 0;
    }

    inline void pushAdd(int& x){
        if(ls(x)){
            if(~cov(ls(x))) cov(ls(x)) = (cov(ls(x)) + add(x)) % mod;
            else add(ls(x)) = (add(ls(x)) + add(x)) % mod;
            v(ls(x)) = (v(ls(x)) + add(x)) % mod;
            sum(ls(x)) = (sum(ls(x)) + 1ll * add(x) * sz(ls(x))) % mod;
        }
        if(rs(x)){
            if(~cov(rs(x))) cov(rs(x)) = (cov(rs(x)) + add(x)) % mod;
            else add(rs(x)) = (add(rs(x)) + add(x)) % mod;
            v(rs(x)) = (v(rs(x)) + add(x)) % mod;
            sum(rs(x)) = (sum(rs(x)) + 1ll * add(x) * sz(rs(x))) % mod;
        }
        add(x) = 0;
    }

    inline void pushCov(int& x){
        if(ls(x)){
            add(ls(x)) = 0, cov(ls(x)) = cov(x);
            v(ls(x)) = cov(x);
            sum(ls(x)) = 1ll * cov(x) * sz(ls(x)) % mod;
        }
        if(rs(x)){
            add(rs(x)) = 0, cov(rs(x)) = cov(x);
            v(rs(x)) = cov(x);
            sum(rs(x)) = 1ll * cov(x) * sz(rs(x)) % mod;
        }
        cov(x) = -1;
    }

    inline void pushDown(int& x){
        if(tag(x) || add(x) || ~cov(x)){
            if(ls(x)) cpy(ls(x), tree[ls(x)]);
            if(rs(x)) cpy(rs(x), tree[rs(x)]);
        }
        if(tag(x)) pushInv(x);
        if(~cov(x)) pushCov(x);
        if(add(x)) pushAdd(x);
    };

    inline void split(int k, int r, int& x, int& y){
        if(!r){
            x = y = 0;
            return ;
        }
        pushDown(r);
        cpy(r, tree[r]);
        if(sz(ls(r)) < k) x = r, split(k - sz(ls(x)) - 1, rs(r), rs(x), y);
        else y = r, split(k, ls(r), x, ls(y));
        pushUp(r);
    }

    inline int merger(int x, int y){
        if(!x || !y) return x | y;
        if((dist(rnd) % (sz(x) + sz(y))) < sz(x)){
            pushDown(x), cpy(x, tree[x]);
            rs(x) = merger(rs(x), y);
            pushUp(x);
            return x;
        }
        else{
            pushDown(y), cpy(y, tree[y]);
            ls(y) = merger(x, ls(y));
            pushUp(y);
            return y;
        }
    }

    inline void dfs(int r){
        if(!r) return ;
        pushDown(r);
        if(ls(r)) dfs(ls(r));
        vs[++cnt] = v(r);
        if(rs(r)) dfs(rs(r));
    }

    inline void build(int s, int t, int& r){
        if(s > t) return ;
        int m = (t + s) >> 1;
        r = ++tot;
        tree[r] = node(vs[m], vs[m], 1);
        build(s, m - 1, ls(r));
        build(m + 1, t, rs(r));
        pushUp(r);
    }

    inline void check(){
        if(tot < maxP) return ;
        getArr();
        build(1, n, root);
    }
public:
    Treap(int n, int* arr):n(n){
        rnd = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());
        dist = decltype(dist)(0, INT32_MAX);
        tree = new node[(int)4E6];
        vs = arr;
        build(1, n, root);
    }

    ~Treap(){
        delete[] tree;
    }

    inline int query(int l, int r){
        split(r, root, rw, rx);
        split(l - 1, rw, rw, ry);
        int res = sum(ry);
        root = merger(merger(rw, ry), rx);
        check();
        return res;
    }

    inline void covRange(int l, int r, int v){
        split(r, root, rw, rx);
        split(l - 1, rw, rw, ry);
        cov(ry) = v, add(ry) = 0;
        v(ry) = v, sum(ry) = 1ll * sz(ry) * v % mod;
        root = merger(merger(rw, ry), rx);
        check();
    }

    inline void addRange(int l, int r, int v){
        if(!v) return ;
        split(r, root, rw, rx);
        split(l - 1, rw, rw, ry);
        if(~cov(ry)) cov(ry) = (cov(ry) + v) % mod;
        else add(ry) = (add(ry) + v) % mod;
        v(ry) = (v(ry) + v) % mod;
        sum(ry) = (sum(ry) + 1ll * sz(ry) * v) % mod;
        root = merger(merger(rw, ry), rx);
        check();
    }

    inline void cpyRange(int l1, int r1, int l2, int r2){
        if(r2 > r1){
            split(r2, root, rv, rw);
            split(l2 - 1, rv, rv, rx);
            split(r1, rv, rv, ry);
            split(l1 - 1, rv, rv, rz);
            cpy(rx, tree[rz]);
        }
        else{
            split(r1, root, rv, rw);
            split(l1 - 1, rv, rv, rx);
            split(r2, rv, rv, ry);
            split(l2 - 1, rv, rv, rz);
            cpy(rz, tree[rx]);
        }
        root = merger(merger(merger(merger(rv, rz), ry), rx), rw);
        check();
    }

    inline void swapRange(int l1, int r1, int l2, int r2){
        if(r1 > r2) std::swap(r1, r2), std::swap(l1, l2);
        split(r2, root, rv, rw);
        split(l2 - 1, rv, rv, rx);
        split(r1, rv, rv, ry);
        split(l1 - 1, rv, rv, rz);
        root = merger(merger(merger(merger(rv, rx), ry), rz), rw);
        check();
    }

    inline void invRange(int l, int r){
        split(r, root, rw, rx);
        split(l - 1, rw, rw, ry);
        tag(ry) ^= 1;
        root = merger(merger(rw, ry), rx);
        check();
    }

    inline void getArr(){
        dfs(root);
        tot = cnt = 0;
    }
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, *arr, op, l1, l2, r1, r2;
    std::cin >> n >> m;
    arr = new int[n + 1];
    for(int i = 1; i <= n; i++) std::cin >> arr[i];
    Treap treap(n, arr);

    for(int i = 0; i < m; i++){
        std::cin >> op >> l1 >> r1;
        if(op == 1) std::cout << treap.query(l1, r1) << '\n';
        else if(op == 6) treap.invRange(l1, r1);
        else{
            std::cin >> l2;
            if(op == 2) treap.covRange(l1, r1, l2);
            else if(op == 3) treap.addRange(l1, r1, l2);
            else{
                std::cin >> r2;
                if(op == 4) treap.cpyRange(l1, r1, l2, r2);
                else treap.swapRange(l1, r1, l2, r2);
            }
        }
    }

    treap.getArr();
    for(int i = 1; i <= n; i++) std::cout << arr[i] << ' ';
    return 0;
}