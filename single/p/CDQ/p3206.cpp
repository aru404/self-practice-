// # [HNOI2010] 城市建设

// ## 题目描述

// PS 国是一个拥有诸多城市的大国。国王 Louis 为城市的交通建设可谓绞尽脑汁。Louis 可以在某些城市之间修建道路，在不同的城市之间修建道路需要不同的花费。

// Louis 希望建造最少的道路使得国内所有的城市连通。但是由于某些因素，城市之间修建道路需要的花费会随着时间而改变。Louis 会不断得到某道路的修建代价改变的消息。他希望每得到一条消息后能立即知道使城市连通的最小花费总和。Louis 决定求助于你来完成这个任务。

// ## 输入格式

// 第一行包含三个整数 $n,m,q$，分别表示城市的数目，可以修建的道路个数，及收到的消息个数。

// 接下来 $m$ 行，第 $i+1$ 行有三个用空格隔开的整数 $x_i,y_i,z_i$，表示在城市 $x_i$ 与城市 $y_i$ 之间修建道路的代价为 $z_i$。接下来 $q$ 行，每行包含两个数 $k,d$，表示输入的第 $k$ 个道路的修建代价修改为 $d$（即将 $z_k$ 修改为 $d$）。

// ## 输出格式

// 输出包含 $q$ 行，第 $i$ 行输出得知前 $i$ 条消息后使城市连通的最小花费总和。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 5 3
// 1 2 1
// 2 3 2
// 3 4 3
// 4 5 4            
// 5 1 5
// 1 6
// 1 1
// 5 3
// ```

// ### 样例输出 #1

// ```
// 14
// 10
// 9
// ```

// ## 提示

// ### 数据规模与约定
// - 对于 $20\%$ 的数据，$n\le 10^3$，$m,q\le 6\times 10^3$。
// - 对于另外 $20\%$ 的数据，$n\le 10^3$，$m\le 5\times 10^4$，$q\le 8\times 10^3$。修改后的代价不会比之前的代价低。
// - 对于 $100\%$ 的数据，$1\le n\le 2\times 10^4$，$1\le m,q\le 5\times 10^4$，$1\le x_i,y_i\le n$，$0\le z_i\le 5\times 10^7$。
// 分治跑两次MGT,实现有点难我只能说
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

const int maxN = 2E4 + 5, maxM = 5E4 + 5, inf = 0X3f3f3f3f;
int f[maxN], rk[maxN], w[maxM], from[maxM], to[maxM], k[maxM], d[maxM];
int s1[maxM], s3[maxM], top1 = 0, top2 = 0;
bool s2[maxM], ban[maxM];
std::vector<int> e1[20], e2, e3;
ll res[maxM], tot = 0;

inline int find(int x){
    return f[x] ^ x? find(f[x]):x;
}

inline void merger(int x, int y){
    if(rk[x] < rk[y]) f[x] = y, s1[++top1] = x;
    else f[y] = x, s1[++top1] = y;
    if(rk[x] == rk[y]) rk[x]++, s2[top1] = 1;
}

inline void retreat(int cnt){
    while(top1 > cnt){
        if(s2[top1]) rk[f[s1[top1]]]--;
        f[s1[top1]] = s1[top1];
        top1--;
    }
}

inline bool cmp(const int& a, const int& b){
    return w[a] < w[b];
}

inline void cdq(int l, int r, int depth){
    int cnt1 = top1, cnt2 = top2;
    ll cnt3 = 0;
    if(l == r){
        w[k[l]] = d[l];
        e1[depth].emplace_back(k[l]);
        std::sort(e1[depth].begin(), e1[depth].end(), cmp);
        for(auto it:e1[depth]){
            int u = find(from[it]), v = find(to[it]);
            if(u == v) continue;
            else merger(u, v), cnt3 += w[it];
        }
        res[l] = tot + cnt3;
        retreat(cnt1);
        return ;
    }

    int m = (l + r) >> 1;
    std::sort(e1[depth].begin(), e1[depth].end(), cmp);
    
    //动态边-inf
    e3.clear();
    for(auto it:e2){
        int u = find(from[it]), v = find(to[it]);
        if(u != v) merger(u, v);
    }
    for(auto it:e1[depth]){
        int u = find(from[it]), v = find(to[it]);
        // 必选边
        if(u != v) merger(u, v), ban[it] = 1, cnt3 += w[it], s3[++top2] = it, e3.emplace_back(it);
    }
    tot += cnt3;
    retreat(cnt1);

    // 动态边inf
    for(auto it:e1[depth]){
        int u = find(from[it]), v = find(to[it]);
        if(u != v) merger(u, v);
        // 必不选
        else ban[it] = 1, s3[++top2] = it;
    }
    retreat(cnt1);

    for(auto it:e3) merger(find(from[it]), find(to[it]));

    e2.clear(), e1[depth + 1].clear();
    for(auto it:e1[depth]){
        if(!ban[it]) e1[depth + 1].emplace_back(it);
    }
    for(int i = l; i <= m; i++){
        if(!ban[k[i]]) ban[k[i]] = 1, e2.emplace_back(k[i]);
    }
    for(int i = m + 1; i <= r; i++) if(!ban[k[i]]) e1[depth + 1].emplace_back(k[i]), ban[k[i]] = 1;
    for(int i = l; i <= r; i++) ban[k[i]] = 0;
    cdq(l, m, depth + 1);

    e2.clear(), e1[depth + 1].clear();
    for(auto it:e1[depth]){
        if(!ban[it]) e1[depth + 1].emplace_back(it);
    }
    for(int i = m + 1; i <= r; i++){
        if(!ban[k[i]]) ban[k[i]] = 1, e2.emplace_back(k[i]);
    }
    for(int i = l; i <= m; i++) if(!ban[k[i]]) e1[depth + 1].emplace_back(k[i]), ban[k[i]] = 1;
    for(int i = l; i <= r; i++) ban[k[i]] = 0;
    cdq(m + 1, r, depth + 1);
    
    retreat(cnt1);
    while(top2 > cnt2) ban[s3[top2--]] = 0;
    tot -= cnt3;
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, m, q;
    std::cin >> n >> m >> q;
    std::iota(f, f + n + 1, 0);
    for(int i = 1; i <= m; i++) std::cin >> from[i] >> to[i] >> w[i];
    for(int i = 1; i <= q; i++) std::cin >> k[i] >> d[i];
    for(int i = 1; i <= q; i++) if(!ban[k[i]]) e2.emplace_back(k[i]), ban[k[i]] = 1;
    for(int i = 1; i <= m; i++) if(!ban[i]) e1[0].emplace_back(i);
    for(int i = 1; i <= q; i++) ban[k[i]] = 0;
    cdq(1, q, 0);
    for(int i = 1; i <= q; i++) std::cout << res[i] << '\n';
    return 0;
}