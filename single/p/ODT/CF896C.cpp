// # Willem, Chtholly and Seniorious

// ## 题面翻译

// 【题面】
// 请你写一种奇怪的数据结构，支持：
// - $1$  $l$  $r$  $x$ ：将$[l,r]$ 区间所有数加上$x$ 
// - $2$  $l$  $r$  $x$ ：将$[l,r]$ 区间所有数改成$x$ 
// - $3$  $l$  $r$  $x$ ：输出将$[l,r]$ 区间从小到大排序后的第$x$ 个数是的多少(即区间第$x$ 小，数字大小相同算多次，保证 $1\leq$  $x$  $\leq$  $r-l+1$  )
// - $4$  $l$  $r$  $x$  $y$ ：输出$[l,r]$ 区间每个数字的$x$ 次方的和模$y$ 的值(即($\sum^r_{i=l}a_i^x$ ) $\mod y$ )

// 【输入格式】
// 这道题目的输入格式比较特殊，需要选手通过$seed$ 自己生成输入数据。
// 输入一行四个整数$n,m,seed,v_{max}$ （$1\leq $  $n,m\leq 10^{5}$  ,$0\leq seed \leq 10^{9}+7$  $,1\leq vmax \leq 10^{9} $ ）
// 其中$n$ 表示数列长度，$m$ 表示操作次数，后面两个用于生成输入数据。
// 数据生成的伪代码如下
// ![](https://cdn.luogu.org/upload/pic/13887.png )

// 其中上面的op指题面中提到的四个操作。

// 【输出格式】
// 对于每个操作3和4，输出一行仅一个数。

// ## 题目描述

// — Willem...

// — What's the matter?

// — It seems that there's something wrong with Seniorious...

// — I'll have a look...





// ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF896C/98774bbeb6d46d43baff377283b5b8c924efc206.png)

// Seniorious is made by linking special talismans in particular order.

// After over 500 years, the carillon is now in bad condition, so Willem decides to examine it thoroughly.

// Seniorious has $ n $ pieces of talisman. Willem puts them in a line, the $ i $ -th of which is an integer $ a_{i} $ .

// In order to maintain it, Willem needs to perform $ m $ operations.

// There are four types of operations:

// - $ 1\ l\ r\ x $ : For each $ i $ such that $ l<=i<=r $ , assign $ a_{i}+x $ to $ a_{i} $ .
// - $ 2\ l\ r\ x $ : For each $ i $ such that $ l<=i<=r $ , assign $ x $ to $ a_{i} $ .
// - $ 3\ l\ r\ x $ : Print the $ x $ -th smallest number in the index range $ [l,r] $ , i.e. the element at the $ x $ -th position if all the elements $ a_{i} $ such that $ l<=i<=r $ are taken and sorted into an array of non-decreasing integers. It's guaranteed that $ 1<=x<=r-l+1 $ .
// - $ 4\ l\ r\ x\ y $ : Print the sum of the $ x $ -th power of $ a_{i} $ such that $ l<=i<=r $ , modulo $ y $ , i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF896C/78509e8cef6ae4ac71093ef3596987ee9ded5b23.png).

// ## 输入格式

// The only line contains four integers $ n,m,seed,v_{max} $ ( $ 1<=n,m<=10^{5},0<=seed<10^{9}+7,1<=vmax<=10^{9} $ ).

// The initial values and operations are generated using following pseudo code:
// ```
// def rnd():

//     ret = seed
//     seed = (seed * 7 + 13) mod 1000000007
//     return ret

// for i = 1 to n:

//     a[i] = (rnd() mod vmax) + 1

// for i = 1 to m:

//     op = (rnd() mod 4) + 1
//     l = (rnd() mod n) + 1
//     r = (rnd() mod n) + 1

//     if (l > r): 
//          swap(l, r)

//     if (op == 3):
//         x = (rnd() mod (r - l + 1)) + 1
//     else:
//         x = (rnd() mod vmax) + 1

//     if (op == 4):
//         y = (rnd() mod vmax) + 1
// ```
// Here $ op $ is the type of the operation mentioned in the legend.

// ## 输出格式

// For each operation of types $ 3 $ or $ 4 $ , output a line containing the answer.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 10 10 7 9
// ```

// ### 样例输出 #1

// ```
// 2
// 1
// 0
// 3
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 10 10 9 9
// ```

// ### 样例输出 #2

// ```
// 1
// 1
// 3
// 3
// ```

// ## 提示

// In the first example, the initial array is $ {8,9,7,2,3,1,5,6,4,8} $ .

// The operations are:

// - $ 2\ 6\ 7\ 9 $
// - $ 1\ 3\ 10\ 8 $
// - $ 4\ 4\ 6\ 2\ 4 $
// - $ 1\ 4\ 5\ 8 $
// - $ 2\ 1\ 7\ 1 $
// - $ 4\ 7\ 9\ 4\ 4 $
// - $ 1\ 2\ 7\ 9 $
// - $ 4\ 5\ 8\ 1\ 1 $
// - $ 2\ 5\ 7\ 5 $
// - $ 4\ 3\ 10\ 8\ 5 $
#include <bits/stdc++.h>
#include <iostream>
#define ll long long
#define IT std::set<node>::iterator

const int maxN = 1E5 + 5, inf = 1E9 + 7;

struct node{
    int l, r;
    mutable ll v;
    node(int l = 0, int r = -1, ll v = 0): l(l), r(r), v(v){}
    bool operator< (const node& b) const{
        return l < b.l;
    }
};

std::set<node> s;

inline IT split(int pos){
    auto it = s.lower_bound(node(pos));
    if(it != s.end() && it->l == pos) return it;
    --it;
    int l = it->l, r = it->r; ll v = it->v;
    s.erase(it);
    s.insert(node(l, pos - 1, v));
    return s.insert(node(pos, r, v)).first;
}

inline void assign_val(int l, int r, ll v){
    auto it2 = split(r + 1), it1 = split(l);
    s.erase(it1, it2);
    s.insert(node(l, r, v));
}

inline void add(int l, int r, int v){
    auto it2 = split(r + 1), it1 = split(l);
    while(it1 != it2) it1->v += v, ++it1;
}

inline ll rank(int l, int r, int k){
    std::vector<std::pair<ll, int>> vp;
    auto it2 = split(r + 1), it1 = split(l);
    vp.clear();
    while(it1 != it2) vp.push_back(std::make_pair(it1->v, it1->r - it1->l + 1)), ++it1;
    std::sort(vp.begin(), vp.end());
    auto it = vp.begin();
    while(it != vp.end()){
        if(k > it->second) k -= it->second;
        else break;
        it++;
    }
    return it->first;
}

inline int qpow(ll a, int p, int mod){
    a %= mod;
    int res = 1;
    while(p){
        if(p & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        p >>= 1;
    }
    return res;
}

inline int powRange(int l, int r, int x, int mod){
    auto it2 = split(r + 1), it1 = split(l);
    int res = 0;
    while(it1 != it2){
        int cnt = it1->r - it1->l + 1; ll a = it1->v;
        res = (res + 1ll * qpow(a, x, mod) * cnt) % mod;
        it1++;
    }
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, seed, vmax;
    int op, l, r, x, y;
    std::cin >> n >> m >> seed >> vmax;
    
    std::function<int()> rnd = [&]()->int{
        int ret = seed;
        seed = (1ll * seed * 7 + 13) % inf;
        return ret;
    };

    for(int i = 1; i <= n; i++){
        s.insert(node(i, i, rnd() % vmax + 1));
    }
    for(int i = 1; i <= m; i++){
        op = rnd() % 4 + 1;
        l = rnd() % n + 1, r = rnd() % n + 1;
        if(l > r) std::swap(l, r);
        if(op == 3) x = rnd() % (r - l + 1) + 1;
        else x = rnd() % vmax + 1;
        if(op == 4) y = rnd() % vmax + 1;

        if(op == 1){
            add(l, r, x);
        }
        else if(op == 2){
            assign_val(l, r, x);
        }
        else if(op == 3){
            std::cout << rank(l, r, x) << '\n';
        }
        else{
            std::cout << powRange(l, r, x, y) << '\n';
        }
    }
    return 0;
}