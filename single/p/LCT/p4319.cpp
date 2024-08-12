// # 变化的道路

// ## 题目描述

// 小 w 和小 c 在 H 国，近年来，随着 H 国的发展，H 国的道路也在不断变化着

// 根据 H 国的道路法，H 国道路都有一个值 $w$，表示如果小 w 和小 c 通过这条道路，那么他们的 L 值会减少 $w$，但是如果小 w 和
// 小 c 在之前已经经过了这条路，那么他们的 L 值不会减少

// H 国有 $N$ 个国家，最开始 H 国有 $N-1$ 条道路，这 $N-1$ 条道路刚好构成一棵树

// 小 w 将和小 c 从 H 国的城市 1 出发，游览 H 国的所有城市，总共游览 32766 天，对于每一天，他们都希望游览结束后 L 值还是一个正数，
// 那么他们出发时 L 值至少为多少

// H 国的所有边都是无向边，没有一条道路连接相同的一个城市

// ## 输入格式

// 输入第 1 行，一个整数$N$

// 输入第 2 至第 $N$ 行，每行三个正整数$u, v, w$，表示城市 $u$ 与城市 $v$ 有一条值为 $w$ 道路
	
// 输入第 $N+1$ 行，一个整数 $M$，表示 H 国有 $M$ 条正在变化的道路

// 输入第 $N+2$ 行到第 $N+M+1$ 行，每行 5 个整数 $u, v, w, l, r$，表示城市 $u$ 到城市 $v$ 有一条值为 $w$ 的道路，
// 这条道路存在于第 $l$ 天到第 $r$ 天

// ## 输出格式

// 输出共 32766 行，第 $i$ 行表示第 $i$ 天游览的 L 值至少为多少

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4
// 1 3 3
// 3 4 4
// 2 4 5
// 3
// 1 2 1 1 2
// 2 3 8 2 3
// 3 4 2 1 1
// ```

// ### 样例输出 #1

// ```
// 7
// 9
// 13
// 由于版面原因，仅显示三行，接下来32763行都是13
// ```

// ## 提示

// 第一天，选择 1 -(1)> 2 -(0)> 1 -(3)> 3 -(2)> 4，L 值总共减少了 6，所以 L 值至少为 7

// 第二天，选择 1 -(1)> 2 -(0)> 1 -(3)> 3 -(4)> 4，L 值总共减少了 8，所以 L 值至少为 9

// 第三天及之后，选择 1 -(3)> 3 -(4)> 4 -(5)> 2，L 值总共减少了 12，所以 L 值至少为 13

// subtask1 : 15分，$N = 100, rm = 233$

// subtask2 : 15分，$N = 1000, rm = 2333$

// subtask3 : 20分，$N = 49998, rm = 32766, l = r$

// subtask4：20分，$N = 49999, rm = 32766, r = rm$

// subtask5：30分，$N = 50000, rm = 32766$

// 对于subtask3 : $M = rm$，对于其他subtask：$M=3\times rm$

// 对于所有数据 : $1\leq N\leq 50000, 1\leq l\leq r\leq rm\leq 32766, 1\leq w\leq 10^9$
#include <iostream>
#include <bits/stdc++.h>
#define ll long long
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
#define l(x) tree[x].ls
#define r(x) tree[x].rs
#define get(x) (ch[f[x]][1] == x)
#define isRoot(x) (ch[f[x]][get(x)] != x)

const int maxN = 5E4 + 5, k = 32766, maxM = k * 3 + (maxN << 1);
int ch[maxM][2], f[maxM], w[maxM], fir[maxM], mx[maxM], from[maxM], to[maxM], stk1[maxM], stk2[maxM][2], cnt = 0, top = 0, n;
ll res = 0;
bool tag[maxM];

struct seg{
    int ls, rs;
}tree[k << 2];

std::vector<int> rs[k << 2];

inline void pushUp(int x){
    std::function<int(int, int)> cmp = [&](int a, int b)->int{
        return w[a] > w[b]? a:b;
    };
    fir[x] = cmp(cmp(fir[ls(x)], fir[rs(x)]), x);
}

inline void pushDown(int x){
    if(tag[x]){
        std::swap(ls(ls(x)), rs(ls(x)));
        std::swap(ls(rs(x)), rs(rs(x)));
        tag[ls(x)] ^= 1, tag[rs(x)] ^= 1;
        tag[x] = 0;
    }
}

inline void rotate(int x){
    int y = f[x], z = f[y], k = get(x);
    if(!isRoot(y)) ch[z][get(y)] = x;
    if(ch[x][!k]) f[ch[x][!k]] = y;
    ch[y][k] = ch[x][!k], ch[x][!k] = y;
    f[y] = x, f[x] = z;
    pushUp(y), pushUp(x);
}

inline void updata(int x){
    int idx = 0;
    stk1[++idx] = x;
    while(!isRoot(x)) x = f[x], stk1[++idx] = x;
    while(idx) pushDown(stk1[idx--]); 
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
    while(ls(x)) pushDown(x), x = ls(x);
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
    f[x] = ls(y) = 0;
    pushUp(y);
}

inline void ins(int l, int r, int id, int s, int t, int& p){
    if(!p) p = ++cnt;
    if(l <= s && r >= t){
        rs[p].push_back(id);
        return ;
    }
    int m = (t + s) >> 1;
    if(l <= m) ins(l, r, id, s, m, l(p));
    if(r > m) ins(l, r, id, m + 1, t, r(p));
}

inline void modify(int x){
    int &u = from[x], &v = to[x];
    split(u, v);
    int tmp = fir[v];
    if(w[tmp] > w[x + n]){
        cut(tmp, from[tmp - n]), cut(tmp, to[tmp - n]);
        link(x + n, u), link(x + n, v);
        res -= w[tmp] - w[x + n];
        stk2[++top][0] = tmp - n;
        stk2[top][1] = x;
    }
}

inline void query(int s, int t, int p){
    int pre = top;
    for(auto i:rs[p]){
        modify(i);
    }
    int m = (t + s) >> 1;
    if(l(p)) query(s, m, l(p));
    else for(int i = s; i <= m; i++) std::cout << res + 1 << '\n';
    if(r(p)) query(m + 1, t, r(p));
    else for(int i = m + 1;i <= t; i++) std::cout << res + 1 << '\n';
    while(top > pre){
        cut(stk2[top][1] + n, from[stk2[top][1]]), cut(stk2[top][1] + n, to[stk2[top][1]]);
        link(stk2[top][0] + n, from[stk2[top][0]]), link(stk2[top][0] + n, to[stk2[top][0]]);
        res += w[stk2[top][0] + n] - w[stk2[top][1] + n];
        top--;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, l, r;
    std::cin >> n;
    for(int i = 1; i < n; i++){
        std::cin >> from[i] >> to[i] >> w[i + n];
        link(from[i], i + n), link(to[i], i + n);
        res += w[i + n];
    }
    std::cin >> m;
    int root = 0;
    for(int i = 0; i < m; i++){
        std::cin >> from[n + i] >> to[n + i] >> w[i + (n << 1)] >> l >> r;
        ins(l, r, i + n, 1, k, root);
    }
    query(1, k, root);
    return 0;
}