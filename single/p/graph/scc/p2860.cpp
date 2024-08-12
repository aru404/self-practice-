// // 
// # [USACO06JAN] Redundant Paths G

// ## 题面翻译

// 为了从 $F(1 \le F \le 5000)$ 个草场中的一个走到另一个，贝茜和她的同伴们有时不得不路过一些她们讨厌的可怕的树．奶牛们已经厌倦了被迫走某一条路，所以她们想建一些新路，使每一对草场之间都会至少有两条相互分离的路径，这样她们就有多一些选择。

// 每对草场之间已经有至少一条路径．给出所有 $R\ (F-1 \le R \le 10000)$ 条双向路的描述，每条路连接了两个不同的草场，请计算最少的新建道路的数量，路径由若干道路首尾相连而成．两条路径相互分离，是指两条路径没有一条重合的道路．但是，两条分离的路径上可以有一些相同的草场．对于同一对草场之间，可能已经有两条不同的道路，你也可以在它们之间再建一条道路，作为另一条不同的道路。

// ## 题目描述

// In order to get from one of the F (1 <= F <= 5,000) grazing fields (which are numbered 1..F) to another field, Bessie and the rest of the herd are forced to cross near the Tree of Rotten Apples.  The cows are now tired of often being forced to take a particular path and want to build some new paths so that they will always have a choice of at least two separate routes between any pair of fields. They currently have at least one route between each pair of fields and want to have at least two. Of course, they can only travel on Official Paths when they move from one field to another.


// Given a description of the current set of R (F-1 <= R <= 10,000) paths that each connect exactly two different fields, determine the minimum number of new paths (each of which connects exactly two fields) that must be built so that there are at least two separate routes between any pair of fields. Routes are considered separate if they use none of the same paths, even if they visit the same intermediate field along the way.


// There might already be more than one paths between the same pair of fields, and you may also build a new path that connects the same fields as some other path.

// ## 输入格式

// Line 1: Two space-separated integers: F and R




// Lines 2..R+1: Each line contains two space-separated integers which are the fields at the endpoints of some path.

// ## 输出格式

// Line 1: A single integer that is the number of new paths that must be built.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 7 7
// 1 2
// 2 3
// 3 4
// 2 5
// 4 5
// 5 6
// 5 7
// ```

// ### 样例输出 #1

// ```
// 2
// ```

// ## 提示

// Explanation of the sample:




// One visualization of the paths is:

// ![](https://cdn.luogu.com.cn/upload/image_hosting/cubnel5k.png)

// Building new paths from 1 to 6 and from 4 to 7 satisfies the conditions.

// ![](https://cdn.luogu.com.cn/upload/image_hosting/rgguiytp.png)

// Check some of the routes:

// - 1 – 2:  1 –> 2 and 1 –> 6 –> 5 –> 2
// - 1 – 4:  1 –> 2 –> 3 –> 4 and 1 –> 6 –> 5 –> 4
// - 3 – 7:  3 –> 4 –> 7 and 3 –> 2 –> 5 –> 7

// Every pair of fields is, in fact, connected by two routes.

// It's possible that adding some other path will also solve the problem (like one from 6 to 7). Adding two paths, however, is the minimum.
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 5E3 + 5, maxM = 1E4 + 5;
int head[maxN], dfn[maxN], low[maxN], in[maxN], inv[maxN], s1[maxN], s2[maxM], top1 = 0, top2 = 0, cnt = 0, noe = 0, tot = 0;

struct edge{
    int to, next;
}edges[maxM << 1];

inline void add(int u, int v){
    edges[noe].to = v;
    edges[noe].next = head[u];
    head[u] = noe++;
}

inline void tarjan(int now, int pre){
    dfn[now] = low[now] = ++cnt;
    s1[++top1] = now;
    for(int e = head[now]; ~e; e = edges[e].next){
        if(e == (pre ^ 1)) continue;
        int& to = edges[e].to;
        if(!dfn[to]){
            tarjan(to, e);
            low[now] = std::min(low[to], low[now]);
            if(low[to] > dfn[now]){
                s2[++top2] = e;
            }
        }
        else low[now] = std::min(low[now], dfn[to]);
    }
    if(low[now] == dfn[now]){
        ++tot;
        do{
            inv[s1[top1]] = tot;
        }while(s1[top1--] != now);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, u, v;
    std::cin >> n >> m;
    memset(head, -1, sizeof(int) * (n + 1));
    for(int i = 0; i < m; i++){
        std::cin >> u >> v;
        add(u, v), add(v, u);
    }
    tarjan(1, -1);
    while(top2){
        u = inv[edges[s2[top2]].to], v = inv[edges[s2[top2] ^ 1].to];
        ++in[u], ++in[v];
        top2--;
    }
    int res = 0;
    for(int i = 1; i <= tot; i++) if(in[i] == 1) res++;
    std::cout << ((res + 1) >> 1);
    return 0;
}