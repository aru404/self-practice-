// # 八数码难题

// ## 题目描述

// 在 $3\times 3$ 的棋盘上，摆有八个棋子，每个棋子上标有 $1$ 至 $8$ 的某一数字。棋盘中留有一个空格，空格用 $0$ 来表示。空格周围的棋子可以移到空格中。要求解的问题是：给出一种初始布局（初始状态）和目标布局（为了使题目简单,设目标状态为 $123804765$），找到一种最少步骤的移动方法，实现从初始布局到目标布局的转变。

// ## 输入格式

// 输入初始状态，一行九个数字，空格用 $0$ 表示。

// ## 输出格式

// 只有一行，该行只有一个数字，表示从初始状态到目标状态需要的最少移动次数。保证测试数据中无特殊无法到达目标状态数据。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 283104765
// ```

// ### 样例输出 #1

// ```
// 4
// ```

// ## 提示

// ### 样例解释

// ![](https://cdn.luogu.com.cn/upload/image_hosting/7rhxbnup.png)

// 图中标有 $0$ 的是空格。绿色格子是空格所在位置，橙色格子是下一步可以移动到空格的位置。如图所示，用四步可以达到目标状态。

// 并且可以证明，不存在更优的策略。
#include <iostream>
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

const int maxN = 4E5 + 5;
int dist[maxN], fact[10], tree[10], ed[9][2], edHash, maxD = 0;
int direction[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

inline int query(int x){
    int res = 0;
    while(x) res += tree[x], x -= lowbit(x);
    return res;
}

inline void updata(int x, int v){
    while(x <= 9) tree[x] += v, x += lowbit(x);
}

inline int hash(std::string& s){
    int hash = 1;
    for(size_t i = 0; i < s.size(); ++i){
        int k = s[i] - '0' + 1;
        updata(k, 1);
        hash += fact[8 - i] * (k - query(k));
    }
    memset(tree + 1, 0, sizeof(int) * 9);
    return hash;
}

inline int f(std::string& s){
    int res = 0;
    for(int i = 0; i < 9; ++i){
        if(s[i] == '0') continue;
        int k = s[i] - '0';
        res += std::abs(i / 3 - ed[k][0]) + std::abs(i % 3 - ed[k][1]);
    }
    return res;
}

typedef std::tuple<std::string, int, int, int> tpl;
struct cmp{
    bool operator()(const tpl& a, const tpl& b){
        return std::get<3>(a) > std::get<3>(b);
    }
};

inline void Astar(std::string& st){
    std::priority_queue<tpl, std::vector<tpl>, cmp> pq;
    pq.emplace(std::make_tuple(st, hash(st), 0, f(st)));
    memset(dist + 1, 0X3f3f3f3f, sizeof(int) * 400000);
    dist[hash(st)] = 0;
    std::bitset<maxN> vis = 0;
    while(!pq.empty() && !vis[edHash]){
        std::string s;
        int h, dis, fv;

        std::tie(s, h, dis, fv) = pq.top();
        pq.pop();
        if(vis[h]) continue;
        vis[h] = 1;

        int id = s.find('0'), x = id / 3, y = id % 3;
        for(int i = 0; i < 4; ++i){
            int nx = x + direction[i][0], ny = y + direction[i][1];
            if(nx < 0 || ny < 0 || nx >= 3 || ny >= 3) continue;
            std::string ns(s);
            std::swap(ns[id], ns[nx * 3 + ny]);
            int nh = hash(ns);
            if(dist[nh] > dis + 1){
                dist[nh] = dis + 1;
                pq.emplace(std::make_tuple(ns, nh, dist[nh], dist[nh] + f(ns)));
            }
        }
    }
}

inline void bidirectionBFS(std::string& st, std::string& ed){\

}

inline bool IDAstar(std::string& st, int now, int pre){
    int est = f(st);
    if(!est) return 1;
    if(est + now > maxD) return 0;
    int id = st.find('0'), x = id / 3, y = id % 3;
    for(int i = 0; i < 4; ++i){
        int nx = x + direction[i][0], ny = y + direction[i][1];
        int nid = nx * 3 + ny;
        if(nx < 0 || ny < 0 || nx >= 3 || ny >= 3 || nid == pre) continue;
        std::swap(st[id], st[nid]);
        if(IDAstar(st, now + 1, id)) return 1;
        std::swap(st[id], st[nid]);
    }
    return 0;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    fact[0] = 1;
    for(int i = 1; i < 9; ++i) fact[i] = fact[i - 1] * i;
    std::string fin = "123804765", st;
    std::cin >> st;
    for(int i = 0; i < 9; ++i){
        int k = fin[i] - '0';
        ed[k][0] = i / 3, ed[k][1] = i % 3;
    }
    edHash = hash(fin);
    // Astar(st);
    while(maxD <= 27 && !IDAstar(st, 0, -1)) ++maxD;
    std::cout << maxD;
    return 0;
}