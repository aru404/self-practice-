// # 【模板】二逼平衡树（树套树）

// ## 题目描述

// 您需要写一种数据结构（可参考题目标题），来维护一个有序数列，其中需要提供以下操作：

// 1. 查询 $k$ 在区间内的排名

// 2. 查询区间内排名为 $k$ 的值

// 3. 修改某一位值上的数值

// 4. 查询 $k$ 在区间内的前驱（前驱定义为严格小于 $x$，且最大的数，**若不存在输出 `-2147483647`**）

// 5. 查询 $k$ 在区间内的后继（后继定义为严格大于 $x$，且最小的数，**若不存在输出 `2147483647`**）

// ## 输入格式

// 第一行两个数 $n,m$，表示长度为 $n$ 的有序序列和 $m$ 个操作。

// 第二行有 $n$ 个数，表示有序序列。

// 下面有 $m$ 行，$opt$ 表示操作标号。

// 若 $opt=1$，则为操作 $1$，之后有三个数 $l~r~k$，表示查询 $k$ 在区间 $[l,r]$ 的排名。

// 若 $opt=2$，则为操作 $2$，之后有三个数 $l~r~k$，表示查询区间 $[l,r]$ 内排名为    $k$ 的数。

// 若 $opt=3$，则为操作 $3$，之后有两个数 $pos~k$，表示将 $pos$ 位置的数修改为 $k$。

// 若 $opt=4$，则为操作 $4$，之后有三个数 $l~r~k$，表示查询区间 $[l,r]$ 内 $k$ 的前驱。

// 若 $opt=5$，则为操作 $5$，之后有三个数 $l~r~k$，表示查询区间 $[l,r]$ 内 $k$ 的后继。

// ## 输出格式

// 对于操作 $1,2,4,5$，各输出一行，表示查询结果。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 9 6
// 4 2 2 1 9 4 0 1 1
// 2 1 4 3
// 3 4 10
// 2 1 4 3
// 1 2 5 9
// 4 3 9 5
// 5 2 8 5
// ```

// ### 样例输出 #1

// ```
// 2
// 4
// 3
// 4
// 9
// ```

// ## 提示

// $1\le n,m\le5\times 10^4$，序列中的值在任何时刻 $\in[0,10^8]$。

// 题目来源：bzoj3196 / Tyvj1730 二逼平衡树，在此鸣谢。

// 此数据为洛谷原创。**（特别提醒：此数据不保证操作 4、5 一定存在，故请务必考虑不存在的情况。）**
// #include <iostream>
// #include <bits/stdc++.h>
// #define ls(x) tree2[x].ls
// #define rs(x) tree2[x].rs
// #define cnt(x) tree2[x].cnt
// #define lowbit(x) (x & -x)

// const int maxN = 1E5 + 5, inf = 2147483647;

// namespace Tit{
//     struct seg{
//         int cnt, ls, rs;
//     }tree2[maxN * 280];

//     int tree1[maxN >> 1], now[maxN >> 1], tmp1[20], tmp2[20], idx1, idx2, n, k, tot = 0;
//     std::stack<int> stk;

//     inline void pushUp(int& x){
//         cnt(x) = cnt(ls(x)) + cnt(rs(x));
//     }

//     inline void get(int& x){
//         if(!stk.empty()) x = stk.top(), stk.pop();
//         else x = ++tot;
//         ls(x) = rs(x) = cnt(x) = 0;
//     }

//     inline void clear(int& x){
//         stk.emplace(x);
//         x = 0;
//     }

//     inline void updataTree2(int id, int v, int s, int t, int& x){
//         if(!x) get(x);
//         if(s == t){
//             cnt(x) += v;
//             if(!cnt(x)) clear(x);
//             return ;
//         }
//         int m = (t + s) >> 1;
//         if(id <= m) updataTree2(id, v, s, m, ls(x));
//         else updataTree2(id, v, m + 1, t, rs(x));
//         pushUp(x);
//     }

//     inline void updataTree1(int x, int v){
//         int pre = now[x];
//         now[x] = v;
//         while(x <= n){
//             if(pre) updataTree2(pre, -1, 1, k, tree1[x]);
//             updataTree2(v, 1, 1, k, tree1[x]);
//             x += lowbit(x);
//         }
//     }

//     inline int queryTree1(int id, int s, int t, int& x){ 
//         if(t <= id || !x) return cnt(x);
//         int m = (t + s) >> 1;
//         if(id <= m) return queryTree1(id, s, m, ls(x));
//         return queryTree1(id, s, m, ls(x)) + queryTree1(id, m + 1, t, rs(x));
//     }
    
//     inline int queryTree2(int s, int t, int v){
//         if(s == t) return s;
//         int sum = 0, m = (t + s) >> 1;
//         for(int i = 1; i <= idx1; i++) sum -= cnt(ls(tmp1[i]));
//         for(int i = 1; i <= idx2; i++) sum += cnt(ls(tmp2[i]));
//         if(sum >= v){
//             for(int i = 1; i <= idx1; i++) tmp1[i] = ls(tmp1[i]);
//             for(int i = 1; i <= idx2; i++) tmp2[i] = ls(tmp2[i]);
//             return queryTree2(s, m, v);
//         }
//         for(int i = 1; i <= idx1; i++) tmp1[i] = rs(tmp1[i]);
//         for(int i = 1; i <= idx2; i++) tmp2[i] = rs(tmp2[i]);
//         return queryTree2(m + 1, t, v - sum);
//     }

//     inline int query1(int l, int r, int v){
//         int res = 1;
//         while(r) res += queryTree1(v - 1, 1, k, tree1[r]), r -= lowbit(r);
//         --l;
//         while(l) res -= queryTree1(v - 1, 1, k, tree1[l]), l -= lowbit(l);
//         return res;
//     }

//     inline void getTree(int l, int r){
//         idx1 = idx2 = 0, --l;
//         while(l) tmp1[++idx1] = tree1[l], l -= lowbit(l);
//         while(r) tmp2[++idx2] = tree1[r], r -= lowbit(r);
//     }

//     inline int query2(int l, int r, int v){
//         getTree(l, r);
//         return queryTree2(1, k, v);
//     }

//     inline int query4(int l, int r, int v){
//         int s = 1, t = v, c = query1(l, r, v), m;
//         if(c == 1) return inf;
//         while(s < t){
//             m = (t + s) >> 1;
//             if(query1(l, r, m) == c) t = m;
//             else s = m + 1;
//         }
//         return s - 1;
//     }

//     inline int query5(int l, int r, int v){
//         int s = v + 1, t = k, c = query1(l, r, v + 1), m;
//         if(c == r - l + 2) return inf;
//         while(s < t){
//             m = (t + s + 1) >> 1;
//             if(query1(l, r, m) == c) s = m;
//             else t = m - 1;
//         }
//         return s;
//     }
// }

// int rk[maxN], op[maxN >> 1], left[maxN >> 1], right[maxN >> 1], w[maxN], tmp[maxN], val[maxN];

// namespace diff{    
//     inline void init(int n, int m){
//         int k = n;
//         std::iota(tmp, tmp + n + 1, 0);
//         for(int i = 1; i <= m; i++) if(op[i] != 2) tmp[++k] = n + i;
//         std::sort(tmp + 1, tmp + k + 1, [&](const int& a, const int& b){return w[a] < w[b];});
//         int pre = -inf;
//         for(int i = 1; i <= k; i++){
//             if(pre < w[tmp[i]]) pre = w[tmp[i]], val[++Tit::k] = w[tmp[i]];
//             rk[tmp[i]] = Tit::k;
//         }
//         Tit::n = n;
//         for(int i = 1; i <= n; i++){
//             Tit::updataTree1(i, rk[i]);
//         }
//     }
// }

// int main(){
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
       
//     int n, m;
//     std::cin >> n >> m;
//     for(int i = 1; i <= n; i++) std::cin >> w[i];
//     for(int i = 1; i <= m; i++){
//         std::cin >> op[i];
//         if(op[i] != 3) std::cin >> left[i] >> right[i] >> w[i + n];
//         else std::cin >> left[i] >> w[i + n];
//     }
//     diff::init(n, m);
//     for(int i = 1; i <= m; i++){
//         if(op[i] == 1) std::cout << Tit::query1(left[i], right[i], rk[i + n]) << '\n';
//         else if(op[i] == 2) std::cout << val[Tit::query2(left[i], right[i], w[i + n])] << '\n';
//         else if(op[i] == 3) Tit::updataTree1(left[i], rk[i + n]);
//         else if(op[i] == 4){
//             int res = Tit::query4(left[i], right[i], rk[i + n]);
//             if(res == inf) std::cout << -inf << '\n';
//             else std::cout << val[res] << '\n';
//         }
//         else{
//             int res = Tit::query5(left[i], right[i], rk[i + n]);
//             if(res == inf) std::cout << inf << '\n';
//             else std::cout << val[res] << '\n';
//         }
//     }
//     return 0;
// }

#include <iostream>
#include <bits/stdc++.h>
#define ls(x) tree2[x].ls
#define rs(x) tree2[x].rs
#define f(x) tree2[x].f
#define get(x) (rs(f(x)) == x)
#define son(x, k) (k? rs(x):ls(x))
#define v(x) tree2[x].val
#define cnt(x) tree2[x].cnt
#define tot(x) tree2[x].tot

const int maxN = 5E4 + 5, inf = 2147483647;

namespace Tit{
    int n, tree1[maxN << 2], now[maxN], *root, idx = 0;
    std::stack<int> stk;

    struct node{
        int ls, rs, f, cnt, val, tot;
    }tree2[maxN * 20];

    inline void pushUp(int x){
        tot(x) = cnt(x) + tot(ls(x)) + tot(rs(x));
    }

    inline void rotate(int x){
        int y = f(x), z = f(y), k = get(x);
        if(z) son(z, get(y)) = x;
        if(son(x, !k)) f(son(x, !k)) = y;
        son(y, k) = son(x, !k), son(x, !k) = y;
        f(y) = x, f(x) = z;
        pushUp(y), pushUp(x);
    }

    inline void splay(int x, int r){
        for(int fa = f(x); fa != r; rotate(x), fa = f(x)){
            if(f(fa) != r) rotate(get(fa) ^ get(x)? x:fa);
        }
        if(!r) *root = x;
    }

    inline void getNew(int& x){
        if(!stk.empty()) x = stk.top(), stk.pop();
        else x = ++idx;
        ls(x) = rs(x) = cnt(x) = v(x) = tot(x) = 0;
    }

    inline void ins(int v){
        int r = *root, fa = 0;
        while(r && v(r) != v){
            fa = r;
            if(v(r) > v) r = ls(r);
            else r = rs(r);
        }
        if(!r){
            getNew(r), v(r) = v, f(r) = fa;
            if(fa) son(fa, v > v(fa)) = r;
        }
        ++cnt(r);
        splay(r, 0);
    }

    inline void find(int v){
        int r = *root;
        while(son(r, v > v(r)) && v(r) != v) r = son(r, v > v(r));
        if(r) splay(r, 0);
    }

    inline int findBound(int v, bool f){
        find(v);
        int r = *root;
        if((v > v(r) && !f) || (v < v(r) && f)) return r;
        r = son(r, f);
        while(son(r, !f)) r = son(r, !f);
        return r;
    }

    inline void del(int v){
        int pre = findBound(v, 0), suf = findBound(v, 1);
        if(pre) splay(pre, 0);
        if(suf) splay(suf, pre);
        if(!suf && !pre){
            cnt(*root)--;
            if(!cnt(*root)) *root = 0;
            return ;
        }
        int r = suf? ls(suf):rs(pre);
        cnt(r)--;
        if(cnt(r)) splay(r, 0);
        else{
            stk.emplace(r);
            son(f(r), get(r)) = 0;
        }
    }

    inline int find1(int l, int r, int k, int s, int t, int p){
        if(l <= s && r >= t){
            root = &tree1[p];
            find(k);
            return tot(ls(*root)) + (v(*root) < k? cnt(*root):0);
        }
        int m = (t + s) >> 1, res = 0;
        if(l <= m) res += find1(l, r, k, s, m, p << 1);
        if(r > m) res += find1(l, r, k, m + 1, t, p << 1 | 1);
        return res;
    }

    inline int find2(int l, int r, int k){
        int s = 0, t = 1E8 + 1, m, res = inf;
        while(s <= t){
            m = (t + s) >> 1;
            int rk = find1(l, r, m, 1, n, 1) + 1;
            if(rk > k){
                t = m - 1;
                res = std::min(m, res);
            }
            else s = m + 1;
        }
        return res - 1;
    }

    inline int find4(int l, int r, int k, int s, int t, int p){
        if(l <= s && r >= t){
            root = &tree1[p];
            int res = findBound(k, 0);
            return res? v(res):-inf;
        }
        int m = (t + s) >> 1, res = -inf;
        if(l <= m) res = std::max(res, find4(l, r, k, s, m, p << 1));
        if(r > m) res = std::max(res, find4(l, r, k, m + 1, t, p << 1 | 1));
        return res;
    }

    inline int find5(int l, int r, int k, int s, int t, int p){
        if(l <= s && r >= t){
            root = &tree1[p];
            int res = findBound(k, 1);
            return res? v(res):inf;
        }
        int m = (t + s) >> 1, res = inf;
        if(l <= m) res = std::min(res, find5(l, r, k, s, m, p << 1));
        if(r > m) res = std::min(res, find5(l, r, k, m + 1, t, p << 1 | 1));
        return res;
    }

    inline void updata(int id, int v, int s, int t, int p){
        root = &tree1[p];
        if(~now[id]) del(now[id]);
        ins(v);
        if(s == t){
            now[s] = v;
            return ;
        }
        int m = (t + s) >> 1;
        if(id <= m) updata(id, v, s, m, p << 1);
        else updata(id, v, m + 1, t, p << 1 | 1);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k, l, r, op;
    // std::freopen("C:\\Users\\admin\\Downloads\\P3380_8.in", "r", stdin);
    std::cin >> n >> m;
    memset(Tit::now + 1, -1, sizeof(int) * n);
    Tit::n = n;
    for(int i = 1; i <= n; i++){
        std::cin >> k;
        Tit::updata(i, k, 1, n, 1);
    }
    for(int i = 0; i < m; i++){
        std::cin >> op >> l >> r;
        if(op != 3) std::cin >> k;
        if(op == 1){
            std::cout << Tit::find1(l, r, k, 1, n, 1) + 1 << '\n';
        }
        else if(op == 2){
            std::cout << Tit::find2(l, r, k) << '\n';
        }
        else if(op == 3){
            Tit::updata(l, r, 1, n, 1);
        }
        else if(op == 4){
            std::cout << Tit::find4(l, r, k, 1, n, 1) << '\n';
        }
        else{
            std::cout << Tit::find5(l, r, k, 1, n, 1) << '\n';
        }
    }
    return 0;
}