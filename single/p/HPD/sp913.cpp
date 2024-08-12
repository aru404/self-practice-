// # QTREE2 - Query on a tree II

// ## 题面翻译

// 给定一棵n个点的树，边具有边权。要求作以下操作：

// DIST a b 询问点a至点b路径上的边权之和

// KTH a b k 询问点a至点b有向路径上的第k个点的编号

// 有多组测试数据，每组数据以DONE结尾。

// 感谢@vegacx 提供的翻译

// ## 题目描述

// You are given a tree (an undirected acyclic connected graph) with **N** nodes, and edges numbered 1, 2, 3...**N**-1. Each edge has an integer value assigned to it, representing its length.

//  We will ask you to perfrom some instructions of the following form:

// - **DIST a b** : ask for the distance between node **a** and node **b**  
//    or
// - **KTH a b k** : ask for the **k**-th node on the path from node **a** to node **b**

//  **Example:**  
// **N** = 6   
//  1 2 1 // edge connects node 1 and node 2 has cost 1   
//  2 4 1   
//  2 5 2   
//  1 3 1   
//  3 6 2   
  
//  Path from node 4 to node 6 is 4 -> 2 -> 1 -> 3 -> 6   
// **DIST 4 6** : answer is 5 (1 + 1 + 1 + 2 = 5)   
// **KTH 4 6 4** : answer is 3 (the 4-th node on the path from node 4 to node 6 is 3)

// ## 输入格式

// The first line of input contains an integer **t**, the number of test cases (**t** <= 25). **t** test cases follow.

// For each test case:

// - In the first line there is an integer **N** (**N** <= 10000)
// - In the next **N**-1 lines, the i-th line describes the i-th edge: a line with three integers **a b c** denotes an edge between **a**, **b** of cost **c** (**c** <= 100000)
// - The next lines contain instructions **"DIST a b"** or **"KTH a b k"**
// - The end of each test case is signified by the string "**DONE**".

// There is one blank line between successive tests.

// ## 输出格式

// For each **"DIST"** or **"KTH"** operation, write one integer representing its result.

// Print one blank line after each test.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 1

// 6
// 1 2 1
// 2 4 1
// 2 5 2
// 1 3 1
// 3 6 2
// DIST 4 6
// KTH 4 6 4
// DONE
// ```

// ### 样例输出 #1

// ```
// 5
// 3
// ```
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E4 + 5;
int dfn[maxN], sz[maxN], f[maxN], top[maxN], son[maxN], depth[maxN], head[maxN], noe = 0, cnt = 0;
int w[maxN], sum[maxN], inv[maxN];

struct edge{
    int to, next;
}edges[maxN << 1];

inline void add(int u, int v){
    edges[++noe].to = v, edges[noe].next = head[u];
    head[u] = noe;
}

inline void dfs1(int now, int fa){
    f[now] = fa, depth[now] = depth[fa] + 1;
    for(int e = head[now]; e; e = edges[e].next){
        int& to = edges[e].to;
        if(to == fa) continue;
        sum[to] = sum[now] + w[(e + 1) >> 1];
        dfs1(to, now);
        if(sz[to] > sz[son[now]]) son[now] = to;
    }
    sz[now] = sz[son[now]] + 1;
}

inline void dfs2(int now, int topf){
    dfn[now] = ++cnt, inv[cnt] = now, top[now] = topf;
    if(!son[now]) return;
    dfs2(son[now], topf);
    for(int e = head[now]; e; e = edges[e].next){
        int& to = edges[e].to;
        if(dfn[to]) continue;
        dfs2(to, to);
    }
}

inline int LCA(int u, int v){
    while(top[u] != top[v]){
        if(depth[top[u]] < depth[top[v]]) std::swap(u, v);
        u = f[top[u]];
    }
    return dfn[u] > dfn[v]? v:u;
}

inline int queryDis(int u, int v){
    return sum[u] + sum[v] - 2 * sum[LCA(u, v)];
}

inline int queryKth(int u, int v, int k){
    int anc = LCA(u, v);
    if(depth[u] - depth[anc] + 1 < k) k = depth[u] + depth[v] - 2 * depth[anc] + 2 - k, u = v;
    while(k > depth[u] - depth[top[u]] + 1) k -= depth[u] - depth[top[u]] + 1, u = f[top[u]];
    return inv[dfn[u] - k + 1];
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, u, v, k, t;
    std::string op;
    std::cin >> t;
    for(int i = 0; i < t; i++){
        std::cin >> n;
        for(int i = 1; i < n; i++){
            std::cin >> u >> v >> w[i];
            add(u, v), add(v, u);
        }
    
        dfs1(1, 0), dfs2(1, 1);
        do{
            std::cin >> op;
            if(op == "DIST"){
                std::cin >> u >> v;
                std::cout << queryDis(u, v) << '\n';
            }
            else if(op == "KTH"){
                std::cin >> u >> v >> k;
                std::cout << queryKth(u, v, k) << '\n';
            }
        }while(op != "DONE");
        noe = cnt = 0;
        memset(head + 1, 0, sizeof(int) * n);
        memset(dfn + 1, 0, sizeof(int) * n);
        memset(son + 1, 0, sizeof(int) * n);
    }

    return 0;
}