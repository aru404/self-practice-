// # 电车

// ## 题目描述

// 在一个神奇的小镇上有着一个特别的电车网络，它由一些路口和轨道组成，每个路口都连接着若干个轨道，每个轨道都通向一个路口（不排除有的观光轨道转一圈后返回路口的可能）。在每个路口，都有一个开关决定着出去的轨道，每个开关都有一个默认的状态，每辆电车行驶到路口之后，只能从开关所指向的轨道出去，如果电车司机想走另一个轨道，他就必须下车切换开关的状态。

// 为了行驶向目标地点，电车司机不得不经常下车来切换开关，于是，他们想请你写一个程序，计算一辆从路口 $A$ 到路口 $B$ 最少需要下车切换几次开关。

// ## 输入格式

// 第一行有 $3$ 个整数 $N,A,B$（$2 \leq N \leq 100, 1 \leq A,B \leq N$），分别表示路口的数量，和电车的起点，终点。

// 接下来有 $N$ 行，每行的开头有一个数字 $K_i$（$0 \leq K_i \leq N-1$），表示这个路口与 $K_i$ 条轨道相连，接下来有 $K_i$ 个数字表示每条轨道所通向的路口，开关默认指向第一个数字表示的轨道。

// ## 输出格式

// 输出文件只有一个数字，表示从 $A$ 到 $B$ 所需的最少的切换开关次数，若无法从 $A$ 前往 $B$，输出 $-1$。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 2 1
// 2 2 3
// 2 3 1
// 2 1 2
// ```

// ### 样例输出 #1

// ```
// 0
// ```
#include <iostream>
#include <bits/stdc++.h>
const int maxN = 105;
int dis[maxN];
bool vis[maxN];
std::vector<int> es[maxN];

struct v{
    int p, d;
    v(int p = 0, int d = 0): p(p), d(d){}
    bool operator< (const v& other) const{
        return this->d > other.d;
    }
};

inline int dijkstra(int st, int ed, int n){
    std::priority_queue<v> pq;
    memset(dis + 1, 0X3f3f3f3f, sizeof(int) * n);
    pq.emplace(v(st, 0)), dis[st] = 0;
    while(!pq.empty()){
        auto top = pq.top();
        pq.pop();
        if(vis[top.p]) continue;
        vis[top.p] = 1;
        if(top.p == ed) return dis[ed];
        int m = es[top.p].size();
        for(int i = 0; i < m; i++){
            int& to = es[top.p][i];
            if(dis[to] > dis[top.p] + (i > 0)){
                dis[to] = dis[top.p] + (i > 0);
                pq.emplace(v(to, dis[to]));
            }
        }
    }
    return -1;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, st, ed, k, to;
    std::cin >> n >> st >> ed;
    for(int i = 1; i <= n; i++){
        std::cin >> k;
        for(int j = 0; j < k; j++) std::cin >> to, es[i].push_back(to);
    }
    std::cout << dijkstra(st, ed, n);
    return 0;
}