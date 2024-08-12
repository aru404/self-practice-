// # 【模板】线段树分裂

// ## 题目描述

// 给出一个可重集 $a$（编号为 $1$），它支持以下操作：

// `0 p x y`：将可重集 $p$ 中大于等于 $x$ 且小于等于 $y$ 的值移动到一个新的可重集中（新可重集编号为从 $2$ 开始的正整数，是上一次产生的新可重集的编号+1）。

// `1 p t`：将可重集 $t$ 中的数放入可重集 $p$，且清空可重集 $t$（数据保证在此后的操作中不会出现可重集 $t$）。

// `2 p x q`：在 $p$ 这个可重集中加入 $x$ 个数字 $q$。

// `3 p x y`：查询可重集 $p$ 中大于等于 $x$ 且小于等于 $y$ 的值的个数。

// `4 p k`：查询在 $p$ 这个可重集中第 $k$ 小的数，不存在时输出 `-1`。

// ## 输入格式

// 第一行两个整数 $n,m$，表示可重集中的数在 $1\sim n$ 的范围内，有 $m$ 个操作。

// 接下来一行 $n$ 个整数，表示 $1 \sim n$ 这些数在 $a$ 中出现的次数 $(a_{i} \leq m)$。

// 接下来的 $m$ 行每行若干个整数，第一个数为操作的编号 $opt$（$0 \leq opt \leq 4$），以**题目描述**为准。

// ## 输出格式

// 依次输出每个查询操作的答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 12
// 0 0 0 0 0
// 2 1 1 1
// 2 1 1 2
// 2 1 1 3
// 3 1 1 3
// 4 1 2
// 2 1 1 4
// 2 1 1 5
// 0 1 2 4
// 2 2 1 4
// 3 2 2 4
// 1 1 2
// 4 1 3
// ```

// ### 样例输出 #1

// ```
// 3
// 2
// 4
// 3
// ```

// ## 提示

// 对于 $30\%$ 的数据，$1\leq n \leq {10}^3$，$1 \le m \le {10}^3$；  
// 对于 $100\%$ 的数据，$1 \le n \le 2 \times {10}^5$，$1 \le x, y, q \le m \le 2 \times {10}^5$。保证数据合法。

// 不开 `long long` 见祖宗！！

// ---

// 题面 by @[Limit](https://www.luogu.com.cn/user/86625)

// std by @[Limit](https://www.luogu.com.cn/user/86625)（线段树分裂）

// 验题 by @[Froggy](https://www.luogu.com.cn/user/100285)（平衡树，不过合并的复杂度假掉了，倒数第二个测试点就是 hack 数据）

// 数据 by @[Froggy](https://www.luogu.com.cn/user/100285)
#include <iostream>
#include <bits/stdc++.h>
#define ll long long 
#define ls(x) tree[x].l
#define rs(x) tree[x].r
#define cnt(x) tree[x].cnt

const int maxN = 2E5 + 5;
int head[maxN], cnt = 0, tot = 1;
std::stack<int> st;

struct seg{
    int l, r;
    ll cnt;
}tree[maxN * 20];

inline void pushUp(int p){
    cnt(p) = cnt(ls(p)) + cnt(rs(p));
}

inline void split(int l, int r, int s, int t, int& x, int& y){
    if(l <= s && r >= t){
        x = y, y = 0;
        return ;
    }
    if(!x){
        if(!st.empty()) x = st.top(), st.pop();
        else x = ++cnt;
        ls(x) = rs(x) = cnt(x) = 0;
    }
    int m = (t + s) >> 1;
    if(l <= m) split(l, r, s, m, ls(x), ls(y));
    if(r > m) split(l, r, m + 1, t, rs(x), rs(y));
    pushUp(x), pushUp(y);
}

inline void ins(int id, int v, int s, int t, int& x){
    if(!x){
        if(!st.empty()) x = st.top(), st.pop();
        else x = ++cnt;
        ls(x) = rs(x) = cnt(x) = 0;
    };
    if(s == t){
        cnt(x) += v;
        return ;
    }
    int m = (t + s) >> 1;
    if(id <= m) ins(id, v, s, m, ls(x));
    else ins(id, v, m + 1, t, rs(x));
    pushUp(x);
}

inline int merger(int s, int t, int x, int& y){
    if(!x || !y){
        x |= y, y = 0;
        return x;
    }
    if(s == t){
        cnt(x) += cnt(y);
        st.push(y), y = 0;
        return x;
    }
    int m = (t + s) >> 1;
    ls(x) = merger(s, m, ls(x), ls(y));
    rs(x) = merger(m + 1, t, rs(x), rs(y));
    pushUp(x);
    st.push(y), y = 0;
    return x;
}

inline ll query(int l, int r, int s, int t, int& x){
    if(!x) return 0;
    if(l <= s && r >= t) return cnt(x);
    int m = (t + s) >> 1;
    ll res = 0;
    if(l <= m) res += query(l, r, s, m, ls(x));
    if(r > m) res += query(l, r, m + 1, t, rs(x));
    return res;
}

inline int find(int k, int s, int t, int& x){
    if(s == t) return s;
    int m = (t + s) >> 1;
    if(k <= cnt(ls(x))) return find(k, s, m, ls(x));
    return find(k - cnt(ls(x)), m + 1, t, rs(x));
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, m, a, op, t, p, x, y;
    ll k;
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++){
        std::cin >> a;
        if(a) ins(i, a, 1, n, head[1]);
    }
    for(int i = 1; i <= m; i++){
        std::cin >> op >> p;
        if(!op){
            std::cin >> x >> y;
            split(x, y, 1, n, head[++tot], head[p]);
        }
        else if(op == 1){
            std::cin >> t;
            head[p] = merger(1, n, head[p], head[t]);
        }
        else if(op == 2){
            std::cin >> x >> t;
            ins(t, x, 1, n, head[p]);
        }
        else if(op == 3){
            std::cin >> x >> y;
            std::cout << query(x, y, 1, n, head[p]) << std::endl;
        }
        else{
            std::cin >> k;
            if(cnt(head[p]) < k) std::cout << -1 << std::endl;
            else std::cout << find(k, 1, n, head[p]) << std::endl;
        }
    }
    return 0;
}