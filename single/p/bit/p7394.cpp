// # 「TOCO Round 1」History

// ## 题目描述

// 这里有一棵 $n$ 个结点根为 $1$ 号结点的树，每个结点上都有一盏灯，初始状态都是关闭。现在有 $m$ 次事件发生，有以下几种情况：

// `1 x` 将 $x$ 位置上的灯打开或关闭（原来如果打开就关闭，否则打开）。

// `2 x y` 询问树上与 $x$ 相同深度的点中与 $x$ 结点距离为 $y$ 的点中开着的灯的个数。

// `3 x` 回到第 $x$ 次事件发生之后的状态。

// 对于每个 $2$ 询问请给出回答。

// ## 输入格式

// 第一行一个数 $n$ 。
// 接下来 $n-1$ 行每行两个数 $u,v$ 表示 $u$ 与 $v$ 之间一条边。接下来一个数 $m$，下面的 $m$ 行每行二或三个数表示事件的发生。

// ## 输出格式

// 对于每次 $2$ 询问，给出答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// 1 2
// 1 3
// 6
// 1 3
// 2 2 2
// 1 2
// 2 2 2
// 1 3
// 2 2 2
// ```

// ### 样例输出 #1

// ```
// 1
// 1
// 0
// ```

// ## 提示

// **本题采用打包测评。**

// * Subtask 1（10 pts）：满足所有询问中 $y \bmod 2=1$。


// * Subtask 2（20 pts）：$n,m\leq 10$。

// * Subtask 3（30 pts）：$n,m\leq 10^3$。

// * Subtask 4（40 pts）：$n,m\leq 10^5$。

// 对于 $100\%$ 的数据，$1\leq n,m\leq 10^5$，$3$ 操作保证 $0 \leq x$。
#include <iostream>
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

const int maxN = 1E5 + 5;

int op[maxN], x[maxN], y[maxN], head[maxN], q1Head[maxN], q2Head[maxN], q3Head[maxN], dHead[maxN], res[maxN];
int len[maxN], s[maxN], son[maxN], bfn[maxN], inv[maxN], *f[maxN], st1[maxN], ed1[maxN], st2[maxN], ed2[maxN], tot = 0, cnt = 0, n, *id = s;

struct edge{
    int to, next;
}edges[maxN << 1], q1Edges[maxN], q2Edges[maxN], q3Edges[maxN], dEdges[maxN];

inline void add(int u, int v, int* h, edge* e, int t){
    e[t].to = v, e[t].next = h[u];
    h[u] = t;
}

inline void dfs1(int now, int fa){
    for(int e = head[now]; e; e = edges[e].next){
        int& to = edges[e].to;
        if(to == fa) continue;
        dfs1(to, now);
        if(len[to] > len[son[now]]) son[now] = to;
    }
    len[now] = 1 + len[son[now]];
}

inline void dfs2(int now, int fa){
    s[++tot] = now;
    for(int e = head[now]; e; e = edges[e].next){
        int& to = edges[e].to;
        if(to == fa) continue;
        dfs2(to, now);
    }
    for(int e = q1Head[now]; e; e = q1Edges[e].next){
        int& k = q1Edges[e].to;
        if(tot > k){
            add(s[tot - k], k, q2Head, q2Edges, e);
            if(k) add(s[tot - k], k, q3Head, q3Edges, e);
        }
    }
    s[tot--] = 0;
}

inline void dfs3(int now, int fa){
    f[now][0] = 1, inv[++cnt] = now;
    int tmp = cnt;
    if(son[now]) f[son[now]] = f[now] + 1, dfs3(son[now], now);
    for(int e = head[now]; e; e = edges[e].next){
        int& to = edges[e].to;
        if(to == fa || to == son[now]) continue;
        f[to] = id, id += len[to];
        dfs3(to, now);
        for(int i = 0; i < len[to]; i++) f[now][i + 1] += f[to][i];
    }
    for(int e = q2Head[now]; e; e = q2Edges[e].next){
        int& k = q2Edges[e].to;
        ed1[e] = f[now][k], st1[e] = inv[tmp + k];
    }
    for(int e = q3Head[now]; e; e = q3Edges[e].next){
        int& k = q3Edges[e].to;
        ed2[e] = f[now][k], st2[e] = inv[tmp + k];
    }
}

inline void bfs(){
    std::queue<int> q;
    q.emplace(1), bfn[1] = cnt = 1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        if(son[u]) q.push(son[u]), bfn[son[u]] = ++cnt;
        for(int e = head[u]; e; e = edges[e].next){
            int& to = edges[e].to;
            if(bfn[to]) continue;
            q.push(to), bfn[to] = ++cnt;
        }
    }
}

int tree[maxN];
bool w[maxN];

inline int query(int l, int r){
    if(l > r) return 0;
    l--; int ans = 0;
    while(r > l) ans += tree[r], r -= lowbit(r);
    while(l > r) ans -= tree[l], l -= lowbit(l);
    return ans; 
}

inline void updata(int x, int v){
    while(x <= n) tree[x] += v, x += lowbit(x);
}

inline void dfs4(int now){
    if(op[now] == 1) updata(bfn[x[now]], w[x[now]]? -1:1), w[x[now]] ^= 1;
    else if(st1[now]) res[now] = query(bfn[st1[now]], bfn[st1[now]] + ed1[now] - 1) - query(bfn[st2[now]], bfn[st2[now]] + ed2[now] - 1);
    for(int e = dHead[now]; e; e = dEdges[e].next){
        int& to = dEdges[e].to;
        dfs4(to);
    }
    if(op[now] == 1) updata(bfn[x[now]], w[x[now]]? -1:1), w[x[now]] ^= 1;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, u, v;
    std::cin >> n;
    for(int i = 0; i < n - 1; i++){
        std::cin >> u >> v;
        add(u, v, head, edges, i << 1 | 1), add(v, u, head, edges, (i + 1) << 1);
    }
    std::cin >> m;
    for(int i = 1; i <= m; i++){
        std::cin >> op[i] >> x[i];
        if(op[i] == 2){
            std::cin >> y[i];
            if(y[i] % 2 == 0) add(x[i], y[i] >> 1, q1Head, q1Edges, i);
        }
        add(op[i] == 3? x[i]:i - 1, i, dHead, dEdges, i);
    }
    dfs1(1, 0), dfs2(1, 0);
    f[1] = id, id += len[1], dfs3(1, 0);
    bfs(), dfs4(0);
    for(int i = 1; i <= m; i++) if(op[i] == 2) std::cout << res[i] << '\n';
    return 0;
}