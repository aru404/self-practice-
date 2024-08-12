// # 封锁阳光大学

// ## 题目描述

// 曹是一只爱刷街的老曹，暑假期间，他每天都欢快地在阳光大学的校园里刷街。河蟹看到欢快的曹，感到不爽。河蟹决定封锁阳光大学，不让曹刷街。

// 阳光大学的校园是一张由 $n$ 个点构成的无向图，$n$ 个点之间由 $m$ 条道路连接。每只河蟹可以对一个点进行封锁，当某个点被封锁后，与这个点相连的道路就被封锁了，曹就无法在这些道路上刷街了。非常悲剧的一点是，河蟹是一种不和谐的生物，当两只河蟹封锁了相邻的两个点时，他们会发生冲突。

// 询问：最少需要多少只河蟹，可以封锁所有道路并且不发生冲突。

// ## 输入格式

// 第一行两个正整数，表示节点数和边数。
// 接下来 $m$ 行，每行两个整数 $u,v$，表示点 $u$ 到点 $v$ 之间有道路相连。

// ## 输出格式

// 仅一行如果河蟹无法封锁所有道路，则输出 `Impossible`，否则输出一个整数，表示最少需要多少只河蟹。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 3
// 1 2
// 1 3
// 2 3
// ```

// ### 样例输出 #1

// ```
// Impossible
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 3 2
// 1 2
// 2 3
// ```

// ### 样例输出 #2

// ```
// 1
// ```

// ## 提示

// 【数据规模】   
// 对于 $100\%$ 的数据，$1\le n \le 10^4$，$1\le m \le 10^5$，保证没有重边。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E4 + 5, maxM = 1E5 + 5;
int head[maxN], color[maxN], sz[maxN << 1], noe = 0;
bool cant = 0;

struct edge{
    int to, next;
}edges[maxM << 1];

inline void add(int u, int v){
    edges[++noe].to = v;
    edges[noe].next = head[u];
    head[u] = noe;
}

inline void dfs(int now, int c1, int c2){
    for(int e = head[now]; e; e = edges[e].next){
        int& to = edges[e].to;
        if(color[to] == c2) continue;
        else if(color[to] == c1){
            cant = 1;
            return ;
        }
        else{
            color[to] = c2, sz[c2]++;
            dfs(to, c2, c1);
            if(cant) return ;
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, u, v;
    std::cin >> n >> m;
    for(int i = 0; i < m; i++){
        std::cin >> u >> v;
        add(u, v), add(v, u);
    }
    int cnt = 1, res = 0;
    for(int i = 1; i <= n; i++){
        if(!color[i]){
            dfs(i, (cnt << 1) - 1, cnt << 1);
            if(cant){
                std::cout << "Impossible";
                return 0;
            }
            res += std::min(sz[cnt << 1], sz[(cnt << 1) - 1]);
            cnt++;
        }
    }
    std::cout << res;
    return 0;
}