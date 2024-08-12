// # Boring Queries

// ## 题面翻译

// 给定一个长度为 $n$ 的序列 $a$ 以及 $q$ 次询问  。  
// 每次询问包含 $2$ 个整数 $l,r$ ，你需要求出区间 $[l,r]$ 的最小公倍数对 $10^9 + 7$ 取模的结果。  
// 询问强制在线 。对于每次读入的 $x,y$ ，你需要进行以下操作得到 $l,r$ :  

// $l=(x+last)\ mod\ n+1,r=(y+last)\ mod\ n+1,$  
// 如果 $l$ 比 $r$ 大，你需要交换$l,r$。  
// 数据范围：
// $1\leq n,q\leq 10^5,1 \leq a_i\leq 2\cdot 10^5,1\leq x,y \leq 10^5$

// ## 题目描述

// Yura owns a quite ordinary and boring array $ a $ of length $ n $ . You think there is nothing more boring than that, but Vladik doesn't agree!

// In order to make Yura's array even more boring, Vladik makes $ q $ boring queries. Each query consists of two integers $ x $ and $ y $ . Before answering a query, the bounds $ l $ and $ r $ for this query are calculated: $ l = (last + x) \bmod n + 1 $ , $ r = (last + y) \bmod n + 1 $ , where $ last $ is the answer on the previous query (zero initially), and $ \bmod $ is the remainder operation. Whenever $ l > r $ , they are swapped.

// After Vladik computes $ l $ and $ r $ for a query, he is to compute the least common multiple (LCM) on the segment $ [l; r] $ of the initial array $ a $ modulo $ 10^9 + 7 $ . LCM of a multiset of integers is the smallest positive integer that is divisible by all the elements of the multiset. The obtained LCM is the answer for this query.

// Help Vladik and compute the answer for each query!

// ## 输入格式

// The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the array.

// The second line contains $ n $ integers $ a_i $ ( $ 1 \le a_i \le 2 \cdot 10^5 $ ) — the elements of the array.

// The third line contains a single integer $ q $ ( $ 1 \le q \le 10^5 $ ) — the number of queries.

// The next $ q $ lines contain two integers $ x $ and $ y $ each ( $ 1 \le x, y \le n $ ) — the description of the corresponding query.

// ## 输出格式

// Print $ q $ integers — the answers for the queries.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// 2 3 5
// 4
// 1 3
// 3 3
// 2 3
// 2 3
// ```

// ### 样例输出 #1

// ```
// 6
// 2
// 15
// 30
// ```

// ## 提示

// Consider the example:

// - boundaries for first query are $ (0 + 1) \bmod 3 + 1 = 2 $ and $ (0 + 3) \bmod 3 + 1 = 1 $ . LCM for segment $ [1, 2] $ is equal to $ 6 $ ;
// - boundaries for second query are $ (6 + 3) \bmod 3 + 1 = 1 $ and $ (6 + 3) \bmod 3 + 1 = 1 $ . LCM for segment $ [1, 1] $ is equal to $ 2 $ ;
// - boundaries for third query are $ (2 + 2) \bmod 3 + 1 = 2 $ and $ (2 + 3) \bmod 3 + 1 = 3 $ . LCM for segment $ [2, 3] $ is equal to $ 15 $ ;
// - boundaries for fourth query are $ (15 + 2) \bmod 3 + 1 = 3 $ and $ (15 + 3) \bmod 3 + 1 = 1 $ . LCM for segment $ [1, 3] $ is equal to $ 30 $ .
// 根号分治
#include <iostream>
#include <bits/stdc++.h>
#define ls(x) tree[x].l
#define rs(x) tree[x].r
#define v(x) tree[x].v

const int maxN = 1E5 + 5, maxV = 2E5 + 5, maxK = 87, mod = 1E9 + 7, maxP = 447, maxM = 2E4;
int mx[maxK][maxN << 2], fs[maxV], primes[maxM], w[maxN], pre[maxM], head[maxN], cnt = 0, idx = 0, preCnt = 0;
bool isCom[maxV];

struct seg{
    int l, r, v;
}tree[maxN * 40];

inline void euler(int n){
    for(int i = 2; i <= n; i++){
        if(!isCom[i]){
            primes[++idx] = i;
            fs[i] = idx;
        }
        for(int j = 1; j <= idx; j++){
            int m = i * primes[j];
            if(m > n) break;
            isCom[m] = 1, fs[m] = j;
            if(i % primes[j] == 0) break;
        }
    }
}

inline int qpow(int a, int p){
    int res = 1;
    while(p){
        if(p & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        p >>= 1;
    }
    return res;
}

inline void pushUp1(int p, int k){
    mx[k][p] = std::max(mx[k][p << 1], mx[k][p << 1 | 1]);
}

inline void pushUp2(int x){
    v(x) = 1ll * v(ls(x)) * v(rs(x)) % mod;
}

inline void updata1(int id, int v, int s, int t, int p, int k){
    if(s == t){
        mx[k][p] = v;
        return ;
    }
    int m = (t + s) >> 1;
    if(id <= m) updata1(id, v, s, m, p << 1, k);
    else updata1(id, v, m + 1, t, p << 1 | 1, k);
    pushUp1(p, k);
}

inline int query1(int l, int r, int s, int t, int p, int k){
    if((l <= s && r >= t) || !mx[k][p]) return mx[k][p];
    int res = 0, m = (t + s) >> 1;
    if(l <= m) res = std::max(res, query1(l, r, s, m, p << 1, k));
    if(r > m) res = std::max(res, query1(l, r, m + 1, t, p << 1 | 1, k));
    return res;
}

inline void ins(int id, int v, int s, int t, int& x, int& y){
    x = ++cnt;
    if(s == t){
        v(x) = v;
        return ;
    }
    int m = (t + s) >> 1;
    if(id <= m) ins(id, v, s, m, ls(x), ls(y)), rs(x) = rs(y);
    else ins(id, v, m + 1, t, rs(x), rs(y)), ls(x) = ls(y);
    pushUp2(x);
}

inline void updata2(int id, int s, int t, int& x){
    if(x <= preCnt) tree[++cnt] = tree[x], x = cnt;
    if(s == t){
        v(x) = 1;
        return ;
    }
    int m = (t + s) >> 1;
    if(id <= m) updata2(id, s, m, ls(x));
    else updata2(id, m + 1, t, rs(x));
    pushUp2(x);
}

inline int query2(int l, int r, int s, int t, int x){
    if(!x) return 1;
    if(l <= s && r >= t) return v(x);
    int m = (t + s) >> 1, res = 1;
    if(l <= m) res = 1ll * res * query2(l, r, s, m, ls(x)) % mod;
    if(r > m) res = 1ll * res * query2(l, r, m + 1, t, rs(x)) % mod;
    return res;
}

inline void init(int n){
    int mx = *std::max_element(w + 1, w + n + 1);
    v(0) = 1; 
    euler(mx);
    for(int i = 1; i <= n; i++){
        int v = w[i], p = 0, a = 0;
        while(v > 1){
            if(fs[v] > a){
                updata1(i, p, 1, n, 1, a);
                p = 1, a = fs[v];
            }
            else ++p;
            v /= primes[fs[v]];
        }
        if(a <= 86){
            if(p) updata1(i, p, 1, n, 1, a);
            head[i] = head[i - 1];
        }
        else{
            preCnt = cnt;
            ins(i, primes[a], 1, n, head[i], head[i - 1]);
            if(pre[a]) updata2(pre[a], 1, n, head[i]);
            pre[a] = i;
        }
    }
}

inline int getAns(int l, int r, int n){
    int res = query2(l, r, 1, n, head[r]);
    for(int i = 1; i <= std::min(86, idx); i++){
        int p = query1(l, r, 1, n, 1, i);
        res = 1ll * res * qpow(primes[i], p) % mod;
    }
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, l, r;
    std::cin >> n;
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    init(n);
    std::cin >> m;
    int res = 0;
    for(int i = 0; i < m; i++){
        std::cin >> l >> r;
        l = (l + res) % n + 1;
        r = (r + res) % n + 1;
        if(l > r) std::swap(l, r);
        res = getAns(l, r, n);
        std::cout << res << std::endl;
    }
    return 0;
}