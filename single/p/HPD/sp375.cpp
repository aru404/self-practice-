// # QTREE - Query on a tree

// ## 题面翻译

// 给定 $n$ 个点的树，边按输入顺序编号为 $1,2, \ldots, n-1$，要求作以下操作：

// - `CHANGE i ti` 将第 $i$ 条边权值改为 $t_i$；
// - `QUERY a b` 询问从 $a$ 点到 $b$ 点路径上的最大边权。

// 有多组测试数据，每组数据以 `DONE` 结尾。

// 感谢@vegacx 提供的翻译

// ## 题目描述

// You are given a tree (an acyclic undirected connected graph) with **N** nodes, and edges numbered 1, 2, 3...**N**-1.

// We will ask you to perfrom some instructions of the following form:

// - **CHANGE i ti** : change the cost of the i-th edge to ti  
//    or
// - **QUERY a b** : ask for the maximum edge cost on the path from node a to node b

// ## 输入格式

// The first line of input contains an integer **t**, the number of test cases (**t** <= 20). t test cases follow.

// For each test case:

// - In the first line there is an integer **N** (**N** <= 10000),
// - In the next **N**-1 lines, the i-th line describes the i-th edge: a line with three integers **a b c** denotes an edge between **a**, **b** of cost **c** (**c** <= 1000000),
// - The next lines contain instructions **"CHANGE i ti"** or **"QUERY a b"**,
// - The end of each test case is signified by the string "**DONE**".

// There is one blank line between successive tests.

// ## 输出格式

// For each "**QUERY**" operation, write one integer representing its result.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 1

// 3
// 1 2 1
// 2 3 2
// QUERY 1 2
// CHANGE 1 3
// QUERY 1 2
// DONE
// ```

// ### 样例输出 #1

// ```
// 1
// 3
// ```
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E4 + 5;
int head[maxN], f[maxN], son[maxN], depth[maxN], sz[maxN], top[maxN], dw[maxN], w[maxN], dfn[maxN], cnt = 0, noe = 0, n;
int mx[maxN << 2];

struct edge{
    int to, next;
}edges[maxN << 1];

inline void add(int u, int v){
    edges[++noe].to = v, edges[noe].next = head[u];
    head[u] = noe;
}

inline void dfs1(int now, int fa){
    f[now] = fa, depth[now] = depth[fa] + 1, sz[now] = 1;
    for(int e = head[now]; e; e = edges[e].next){
        int& to = edges[e].to;
        if(to == fa) continue;
        dfs1(to, now);
        if(sz[to] > sz[son[now]]) son[now] = to;
        sz[now] += sz[to];
    }
}

inline void dfs2(int now, int topf){
    dfn[now] = ++cnt, top[now] = topf;
    if(!son[now]) return ;
    dfs2(son[now], topf);
    for(int e = head[now]; e; e = edges[e].next){
        int& to = edges[e].to;
        if(dfn[to]) continue;
        dfs2(to, to);
    }
}

inline void pushUp(int p){
    mx[p] = std::max(mx[p << 1], mx[p << 1 | 1]);
}

inline void buildTree(int s, int t, int p){
    if(s == t){
        mx[p] = dw[s];
        return ;
    }
    int m = (t + s) >> 1;
    buildTree(s, m, p << 1);
    buildTree(m + 1, t, p << 1 | 1);
    pushUp(p);
}

inline void updataTree(int id, int val, int s, int t, int p){
    if(s == t){
        mx[p] = val;
        return ;
    }
    int m = (t + s) >> 1;
    if(id <= m) updataTree(id, val, s, m, p << 1);
    else updataTree(id, val, m + 1, t, p << 1 | 1);
    pushUp(p);
}

inline int queryTree(int l, int r, int s, int t, int p){
    if(l <= s && r >= t) return mx[p];
    int res = INT32_MIN, m = (t + s) >> 1;
    if(l <= m) res = std::max(res, queryTree(l, r, s, m, p << 1));
    if(r > m) res = std::max(res, queryTree(l, r, m + 1, t, p << 1 | 1));
    return res;
}

inline int query(int u, int v){
    if(u == v) return 0;
    int res = INT32_MIN;
    while(top[u] != top[v]){
        if(depth[top[u]] < depth[top[v]]) std::swap(u, v);
        res = std::max(res, queryTree(dfn[top[u]], dfn[u], 1, n, 1));
        u = f[top[u]];
    }
    if(dfn[u] > dfn[v]) std::swap(u, v);
    res = std::max(res, queryTree(dfn[u] + 1, dfn[v], 1, n, 1));
    return res;
}

inline void updata(int id, int val){
    int u = edges[id << 1].to, v = edges[(id << 1) - 1].to;
    updataTree(std::max(dfn[u], dfn[v]), val, 1, n, 1);
}

inline void solve(){
    std::string op; int u, v;
    std::cin >> n;
    for(int i = 1; i < n; i++){
        std::cin >> u >> v >> w[i];
        add(u, v), add(v, u);
    }
    dfs1(1, 0), dfs2(1, 1);
    for(int i = 1; i < n; i++){
        u = edges[(i << 1) - 1].to, v = edges[i << 1].to;
        dw[std::max(dfn[u], dfn[v])] = w[i];
    }
    buildTree(1, n, 1);
    do{
        std::cin >> op;
        if(op[0] != 'D') std::cin >> u >> v;
        if(op[0] == 'C') updata(u, v);
        else if(op[0] == 'Q') std::cout << query(u, v) << '\n';
    }while(op[0] != 'D');
    memset(head + 1, 0, sizeof(int) * n);
    memset(son + 1, 0, sizeof(int) * n);
    memset(dfn + 1, 0, sizeof(int) * n);
    cnt = noe = 0;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    for(int i = 0; i < t; i++) solve();
    return 0;
}