// # 公路修建

// ## 题目描述

// 某国有 $n$ 个城市，它们互相之间没有公路相通，因此交通十分不便。为解决这一“行路难”的问题，政府决定修建公路。修建公路的任务由各城市共同完成。

// 修建工程分若干轮完成。在每一轮中，每个城市选择一个与它最近的城市，申请修建通往该城市的公路。政府负责审批这些申请以决定是否同意修建。

// 政府审批的规则如下：

// 1. 如果两个或以上城市申请修建同一条公路，则让它们共同修建；
// 2. 如果三个或以上的城市申请修建的公路成环。如下图，A 申请修建公路 AB，B 申请修建公路 BC，C 申请修建公路 CA。则政府将否决其中最短的一条公路的修建申请； 
// 3. 其他情况的申请一律同意。

// ![](https://cdn.luogu.com.cn/upload/pic/80.png)

// 一轮修建结束后，可能会有若干城市可以通过公路直接或间接相连。这些可以互相连通的城市即组成“城市联盟”。在下一轮修建中，每个“城市联盟”将被看作一个城市，发挥一个城市的作用。

// 当所有城市被组合成一个“城市联盟”时，修建工程也就完成了。

// 你的任务是根据城市的分布和前面讲到的规则，计算出将要修建的公路总长度。

// ## 输入格式

// 第一行一个整数 $n$，表示城市的数量。（$n \leq 5000$）

// 以下 $n$ 行，每行两个整数 $x$ 和 $y$，表示一个城市的坐标。（$-10^6 \leq x,y \leq 10^6$）

// ## 输出格式

// 一个实数，四舍五入保留两位小数，表示公路总长。（保证有惟一解）

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4
// 0 0
// 1 2
// -1 2
// 0 4
// ```

// ### 样例输出 #1

// ```
// 6.47
// ```

// ## 提示

// 修建的公路如图所示：

// ![](https://cdn.luogu.com.cn/upload/pic/81.png)
// 仔细想一下第二种情况只有环上每条边相等情况下才有可能，所以求个最小生成树
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 5E3 + 5, maxM = 1.3E7;
int x[maxN], y[maxN];
double dis[maxN];
bool vis[maxN];

inline double prim(int n){
    std::function<bool(const std::pair<int, double>, const std::pair<int, double>)> cmp = [&](const std::pair<int, double> a, const std::pair<int, double> b)->bool{
        return a.second > b.second;
    };
    std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, decltype(cmp)> pq(cmp);
    for(int i = 1; i <= n; i++) dis[i] = 0X3f3f3f3f;
    pq.emplace(std::make_pair(1, 0));
    double res = 0;
    while(!pq.empty()){
        auto it = pq.top();
        pq.pop();
        if(vis[it.first]) continue;
        vis[it.first] = 1;
        res += it.second;
        for(int i = 1; i <= n; i++){
            if(vis[i]) continue;
            double d = sqrt(1ll * (x[it.first] - x[i]) * (x[it.first] - x[i]) + 1ll * (y[it.first] - y[i]) * (y[it.first] - y[i]));
            if(d < dis[i]){
                dis[i] = d;
                pq.emplace(std::make_pair(i, dis[i]));
            }
        }
    }
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    for(int i = 1; i <= n; i++) std::cin >> x[i] >> y[i];
    std::cout << std::fixed << std::setprecision(2) <<  prim(n);
    return 0;
}