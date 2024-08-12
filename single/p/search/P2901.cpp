// # [USACO08MAR] Cow Jogging G

// ## 题目描述

// 贝西终于尝到了懒惰的后果，决定每周从谷仓到池塘慢跑几次来健身。当然，她不想跑得太累，所以她只打算从谷仓慢跑下山到池塘，然后悠闲地散步回谷仓。

// 同时，贝西不想跑得太远，所以她只想沿着通向池塘的最短路径跑步。一共有 $M$ 条道路，其中每一条都连接了两个牧场。这些牧场从 $1$ 到 $N$ 编号，如果 $X>Y$，则说明牧场 $X$ 的地势高于牧场 $Y$，即下坡的道路是从 $X$ 通向 $Y$ 的，$N$ 为贝西所在的牛棚（最高点），$1$ 为池塘（最低点）。

// 然而，一周之后，贝西开始对单调的路线感到厌烦，她希望可以跑不同的路线。比如说，她希望能有 $K$ 种不同的路线。同时，为了避免跑得太累，她希望这 $K$ 条路线是从牛棚到池塘的路线中最短的 $K$ 条。如果两条路线包含的道路组成的序列不同，则这两条路线被认为是不同的。

// 请帮助贝西算算她的训练强度，即将牧场网络里最短的 $K$ 条路径的长度分别算出来。你将会被提供一份牧场间路线的列表，每条道路用 $(X_i, Y_i, D_i)$ 表示，意为从 $X_i$ 到 $Y_i$ 有一条长度为 $D_i$ 的下坡道路。

// ## 输入格式

// 第一行三个用空格分开的整数 $N,M,K$，其中 。

// 第二行到第 $M+1$ 行每行有三个用空格分开的整数 $X_i,Y_i,D_i$，描述一条下坡的道路。

// ## 输出格式

// 共 $K$ 行，在第 $i$ 行输出第 $i$ 短的路线长度，如果不存在则输出 $-1$。如果出现多种有相同长度的路线，务必将其全部输出。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 8 7 
// 5 4 1 
// 5 3 1 
// 5 2 1 
// 5 1 1 
// 4 3 4 
// 3 1 1 
// 3 2 1 
// 2 1 1
// ```

// ### 样例输出 #1

// ```
// 1 
// 2 
// 2 
// 3 
// 6 
// 7 
// -1
// ```

// ## 提示

// #### 样例 1 解释

// 这些路线分别为 $(5\to 1)$、$(5\to 3\to 1)$、$(5\to 2\to 1)$、$(5\to 3\to 2\to 1)$、$(5\to 4\to 3\to 1)$ 和 $(5\to 4\to 3\to 2\to 1)$。

// #### 数据规模与约定

// 对于全部的测试点，保证 $1 \le N \le 1,000$，$1 \le M \le 1\times10^4$，$1 \le K \le 100$，$1 \le Y_i < X_i\le N$，$1 \le D_i \le 1\times 10^6$，
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

const int maxN = 1E3 + 5, maxM = 1E4 + 5, maxK = 105;
struct edge{
    int to, next;
}edges[maxN], invEdges[maxN];

int head[maxN], invHead[maxN], w[maxM], cnt[maxN], noe = 0;
ll dist[maxK], invDist[maxN];

inline void add(int u, int v){
    edges[++noe].to = v;
    edges[noe].next = head[u];
    head[u] = noe;

    invEdges[noe].to = u;
    invEdges[noe].next = invHead[v];
    invHead[v] = noe;
}

struct cmp1{
    bool operator()(const std::pair<ll, int>& a, const std::pair<ll, int>& b)const{
        return a.first > b.first;
    }
};

struct cmp2{
    bool operator()(const std::tuple<ll, ll, int>& a, const std::tuple<ll, ll, int>& b)const{
        return std::get<0>(a) > std::get<0>(b);
    }
};

inline void dijkstra(int st, int ed, int n){
    std::priority_queue<std::pair<ll, int>, std::vector<std::pair<ll, int> >, cmp1> pq;
    std::fill_n(invDist + 1, n, 0X3f3f3f3f3fll);
    invDist[ed] = 0;
    pq.emplace(std::make_pair(0, ed));
    std::bitset<maxN> vis = 0;
    while(!pq.empty()){
        auto [dis, u] = pq.top();
        pq.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(int e = invHead[u]; e; e = invEdges[e].next){
            int& v = invEdges[e].to;
            if(invDist[v] > dis + w[e]){
                invDist[v] = dis + w[e];
                pq.emplace(std::make_pair(invDist[v], v));
            }
        }
    }
}

inline void Astar(int st, int ed, int n, int k){
    std::priority_queue<std::tuple<ll, ll, int>, std::vector<std::tuple<ll, ll, int> >, cmp2> pq;
    pq.emplace(std::make_tuple(invDist[st], 0, st));
    while(!pq.empty() && cnt[ed] < k){
        int f, dis, u;
        std::tie(f, dis, u) = pq.top();
        pq.pop();
        ++cnt[u];
        if(u == ed) dist[cnt[u]] = dis;
        if(cnt[u] > k) continue;
        for(int e = head[u]; e; e = edges[e].next){
            int& v = edges[e].to;
            pq.emplace(std::make_tuple(dis + w[e] + invDist[v], dis + w[e], v));
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k, u, v;
    std::cin >> n >> m >> k;
    for(int i = 1; i <= m; ++i){
        std::cin >> u >> v >> w[i];
        add(u, v);
    }
    dijkstra(n, 1, n);
    Astar(n, 1, n, k);
    for(int i = 1; i <= k; ++i){
        if(!dist[i]) std::cout << -1 << '\n';
        else std::cout << dist[i] << '\n';
    }
    return 0;
}