// # [Cnoi2019] 须臾幻境

// ## 题目背景

// 这曾今有一个凄婉哀伤的故事，但是被出题人删档弄丢了。

// ## 题目描述

// 你有一个无向图 $G( V, E )$, $E$ 中每一个元素用一个二元组 $( u, v )$ 表示。

// 现在把 $E$ 中的元素排成一个长度为 $|E|$ 序列 $A$。

// 然后给你 $q$ 个询问二元组 $( l, r )$,

// 表示询问 图 $ G'\big( V, \mathop{\bigcup}\limits_{ i \in [l, r] } \{A_i\} \big) $ 的联通块的个数。

// ## 输入格式

// 第一行， 四个整数, 表示 $|V|$, $|E|$, $q$, $t$, 其中 $t$ 表示强制在线参数.

// 以下$|E|$行， 每行一个二元组 $( u, v )$ , 表示 $A$ 序列.

// 再以下$q$行， 每行一个二元组 $( l' , r' )$ 表示一组加密后的询问.

// 解密方式:

// ```
// GetQuery( &l, &r, t, last_ans, |E| )
//     IF t > 0 THEN 
//         l <- (l + t * last_ans) Mod |E| + 1
//         r <- (r + t * last_ans) Mod |E| + 1
//     IF l > r THEN Swap( l, r )
// ```
// 初始时 last_ans = 0.

// ## 输出格式

// $q$ 行，表示每个询问的答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 80 100 100 0
// 25 73
// 4 10
// 9 27
// 19 26
// 52 55
// 4 18
// 19 31
// 25 29
// 14 72
// 10 13
// 17 23
// 13 63
// 25 46
// 9 11
// 40 64
// 32 48
// 1 2
// 19 34
// 7 39
// 9 14
// 57 59
// 6 47
// 8 36
// 40 66
// 15 67
// 66 76
// 21 49
// 15 38
// 13 25
// 4 61
// 6 32
// 52 58
// 1 12
// 26 44
// 12 68
// 1 37
// 2 45
// 5 22
// 47 77
// 21 60
// 7 28
// 29 69
// 10 78
// 39 43
// 11 50
// 5 6
// 76 79
// 5 7
// 64 70
// 27 33
// 1 51
// 15 75
// 19 24
// 46 56
// 1 3
// 30 42
// 23 35
// 28 57
// 21 41
// 11 53
// 61 65
// 13 15
// 28 30
// 20 49
// 6 8
// 1 5
// 18 40
// 1 9
// 34 62
// 7 16
// 46 54
// 56 74
// 1 17
// 16 20
// 11 71
// 7 19
// 3 4
// 13 21
// 2 80
// 28 52
// 29 7
// 55 27
// 6 71
// 46 27
// 2 68
// 50 75
// 37 41
// 17 13
// 62 57
// 72 51
// 1 54
// 49 33
// 1 14
// 58 29
// 11 53
// 1 38
// 17 46
// 78 33
// 1 47
// 61 5
// 76 91
// 99 29
// 64 67
// 65 32
// 85 8
// 77 57
// 62 19
// 42 37
// 51 41
// 57 71
// 79 63
// 9 17
// 21 16
// 87 43
// 1 77
// 53 37
// 38 37
// 25 69
// 1 1
// 97 72
// 27 31
// 1 95
// 66 29
// 29 63
// 27 74
// 18 63
// 73 11
// 63 81
// 33 46
// 85 19
// 91 78
// 15 66
// 36 89
// 61 63
// 21 9
// 59 23
// 5 61
// 41 59
// 97 79
// 21 41
// 81 51
// 33 57
// 49 27
// 37 71
// 1 9
// 59 73
// 16 6
// 53 41
// 61 37
// 3 88
// 43 43
// 11 3
// 41 27
// 43 30
// 67 5
// 1 33
// 67 15
// 26 35
// 21 45
// 7 65
// 1 41
// 25 82
// 51 4
// 70 60
// 15 1
// 87 77
// 21 83
// 63 51
// 46 43
// 1 41
// 99 28
// 41 17
// 11 44
// 45 56
// 8 31
// 81 43
// 37 71
// 69 6
// 79 75
// 1 46
// 6 75
// 29 34
// 21 21
// 61 39
// 90 26
// 76 88
// 77 41
// 71 53
// 25 71
// 71 43
// 99 88
// 5 41
// 15 51
// 41 61
// 37 86
// 14 47
// 70 35
// 81 3
// 98 4
// 25 1
// ```

// ### 样例输出 #1

// ```
// 64
// 15
// 76
// 46
// 5
// 59
// 36
// 74
// 69
// 65
// 63
// 71
// 74
// 35
// 3
// 63
// 78
// 35
// 79
// 54
// 75
// 1
// 42
// 45
// 32
// 34
// 17
// 61
// 66
// 13
// 66
// 28
// 28
// 77
// 67
// 43
// 23
// 61
// 61
// 59
// 49
// 55
// 57
// 45
// 71
// 65
// 69
// 67
// 55
// 2
// 79
// 71
// 65
// 66
// 17
// 47
// 27
// 70
// 55
// 21
// 39
// 22
// 32
// 69
// 65
// 69
// 17
// 67
// 76
// 39
// 15
// 55
// 46
// 68
// 56
// 41
// 45
// 16
// 75
// 34
// 10
// 74
// 79
// 57
// 18
// 67
// 43
// 61
// 33
// 51
// 68
// 43
// 43
// 59
// 30
// 46
// 44
// 2
// 2
// 55
// ```

// ## 提示

// Subtask1( 15% ): $|V|, |E|, q \le 5000$

// Subtask2( 25% ): $t = 0$

// Subtask3( 22% ): $|V| \le 10^4, |E|, q \le 3*10^4$

// Subtask4( 38% ): 无特殊限制.

// 对于 100% 的数据保证, $|V| \le 10^5, |E| \le 2*10^5, q \le 10^5, t \in \{0,1\}$
#include <iostream>
#include <bits/stdc++.h>
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
#define l(x) tree[x].l
#define r(x) tree[x].r
#define cnt(x) tree[x].cnt
#define get(x) (ch[f[x]][1] == x)
#define isRoot(x) (ch[f[x]][get(x)] != x)

const int maxN = 1E5 + 5, maxE = 2E5 + 5, maxM = 3E5 + 5;
int ch[maxM][2], f[maxM], w[maxM], mn[maxM], stk[maxM], roots[maxE], from[maxE], to[maxE], tot = 0, pre = 0;
bool tag[maxM];

struct seg{
    int l, r, cnt;
}tree[maxE * 40];

inline void pushUp(int x){
    std::function<int(int, int)> cmp = [&](int a, int b)->int{
        return w[a] < w[b]? a:b;
    };
    mn[x] = cmp(x, cmp(mn[ls(x)], mn[rs(x)]));
}

inline void pushDown(int x){
    if(tag[x]){
        std::swap(ls(ls(x)), rs(ls(x)));
        std::swap(ls(rs(x)), rs(rs(x)));
        tag[ls(x)] ^= 1, tag[rs(x)] ^= 1;
        tag[x] = 0;
    }
}

inline void updata(int x){
    int idx = 0;
    stk[++idx] = x;
    while(!isRoot(x)) x = f[x], stk[++idx] = x;
    while(idx) pushDown(stk[idx--]);
}

inline void rotate(int x){
    int y = f[x], z = f[y], k = get(x);
    if(!isRoot(y)) ch[z][get(y)] = x;
    if(ch[x][!k]) f[ch[x][!k]] = y;
    ch[y][k] = ch[x][!k], ch[x][!k] = y;
    f[y] = x, f[x] = z;
    pushUp(y), pushUp(x);
}

inline void splay(int x){
    updata(x);
    for(int fa = f[x]; !isRoot(x); rotate(x), fa = f[x]){
        if(!isRoot(fa)) rotate(get(x) ^ get(fa)? x:fa);
    }
}

inline int access(int x){
    int p;
    for(p = 0; x; p = x, x = f[x]){
        splay(x);
        rs(x) = p;
        pushUp(x);
    }
    return p;
}

inline void makeRoot(int x){
    access(x);
    splay(x);
    tag[x] ^= 1;
    std::swap(ls(x), rs(x));
}

inline int findRoot(int x){
    access(x);
    splay(x);
    while(ls(x)){
        pushDown(x);
        x = ls(x);
    }
    splay(x);
    return x;
}

inline void split(int x, int y){
    makeRoot(x);
    access(y);
    splay(y);
}

inline void link(int x, int y){
    makeRoot(x);
    f[x] = y;
}

inline void cut(int x, int y){
    split(x, y);
    ls(y) = f[x] = 0;
    pushUp(y);
}

inline void ins(int s, int t, int id, int v, int& x, int& y){
    if(x <= pre) x = ++tot, tree[x] = tree[y];
    if(s == t){
        cnt(x) = v;
        return ;
    }
    int m = (t + s) >> 1;
    if(id <= m) ins(s, m, id, v, l(x), l(y));
    else ins(m + 1, t, id, v, r(x), r(y));
    cnt(x) = cnt(l(x)) + cnt(r(x));
}

int query(int l, int s, int t, int x){
    if(l <= s) return cnt(x);
    int res = 0, m = (t + s) >> 1;
    if(l <= m && l(x)) res += query(l, s, m, l(x));
    if(r(x)) res += query(l, m + 1, t, r(x));
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, q, t, res = 0, l, r;
    std::cin >> n >> m >> q >> t;
    for(int i = 0; i <= n; i++) w[i] = 0X3f3f3f3f;
    for(int i = 1; i <= m; i++){
        std::cin >> from[i] >> to[i];
        w[i + n] = i;
        int& u = from[i], &v = to[i];
        if(u != v){
            makeRoot(u);
            int root = findRoot(v);
            pre = tot;
            if(root == u){
                int p = mn[root];
                cut(from[p - n], p), cut(to[p - n], p);
                ins(1, m, p - n, 0, roots[i], roots[i - 1]);
            }
            link(u, i + n), link(v, i + n);
            ins(1, m, i, 1, roots[i], roots[i - 1]);
        }
        else roots[i] = roots[i - 1];
    }
    for(int i = 0; i < q; i++){
        std::cin >> l >> r;
        if(t > 0){
            l = (l + t * res) % m + 1;
            r = (r + t * res) % m + 1;
        }
        if(l > r) std::swap(l, r);
        res = n - query(l, 1, m, roots[r]);
        std::cout << res << std::endl;
    }
    return 0;
}