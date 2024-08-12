// # 有趣的游戏

// ## 题目背景

// 小 A 和小 B 正在玩一个有趣的电脑游戏。

// ## 题目描述

// 游戏在一棵大小为 $n$ 的树上进行。其中每个点都有点权，第 $i$ 个点的点权为 $w_i$。

// 每一次系统会给出一条链，小 A 可以从这条链上找出两个**点权不同**的点 $x,y$，他的得分是 $w_x\bmod w_y$。然后小 B 会从**整棵树**中选取两个**小 A 没有选过**的点，计分方式同小 A。

// 为了保持游戏难度，系统有时会增加一个点的权值。

// 当然，小 A 会尽可能使自己得分最大，他想知道这个值是多少。同时，他想知道，在自己得分最大的情况下，小 B 的最大得分是多少。

// ## 输入格式

// 第一行一个整数 $n$ 表示树的节点个数。

// 接下来 $n-1$ 行，每行两个整数 $a,b$，表示 $a,b$ 之间有一条边。

// 接下来一行 $n$ 个整数，第 $i$ 个数表示第 $i$ 个点的点权。

// 接下来一行一个整数 $q$。

// 接下来 $q$ 行，每行三个整数 $opt,x,y$。

// 若 $opt=0$，将  $w_x$ 增加 $y$。

// 若 $opt=1$，表示系统给出一条从 $x$ 到 $y$ 的链。

// ## 输出格式

// 对于每一次 $opt=1$，输出一行两个整数 $suma,sumb$ 。分别表示小 A 的最大得分和在这情况下小 B 的最大得分 。

// **如果小 A 无法选出两个权值不同的点，那么只输出一个数 $-1$。**

// ## 样例 #1

// ### 样例输入 #1

// ```
// 7
// 1 2
// 2 3
// 2 4
// 1 5
// 5 6
// 5 7
// 5 4 3 2 1 4 3
// 6
// 1 3 4
// 1 2 5
// 1 2 1
// 0 2 1
// 1 2 5
// 1 2 1
// ```

// ### 样例输出 #1

// ```
// 3 4
// 4 3
// 4 3
// 1 4
// -1
// ```

// ## 提示

// 样例解释：

// 第一次：小 A 选择点 $3$ 和点 $2$，得分为 $3\bmod 4=3$，小 B 选择点 $6$ 和点 $1$ 得分为 $4\bmod 5=4$。

// 第二次：小 A 选择点 $2$ 和点 $1$，得分为 $4\bmod 5=4$，小 B 选择点 $7$ 和点 $6$ 得分为 $3\bmod 4=3$。

// 第三次：小 A 选择点 $2$ 和点 $1$，得分为 $4\bmod 5=4$，小 B 选择点 $7$ 和点 $6$ 得分为 $3\bmod 4=3$。

// 第四次：第 $2$ 个点点权变为 $5$。

// 第五次：小 A 选择点 $5$ 和点 $1$，得分为 $1\bmod 5=1$，小 B 选择点 $6$ 和点 $2$ 得分为 $4\bmod 5=4$。

// 第六次：小 A 可以选的点只有 $1,2$ ，点权都是 $5$，没有可以选的方案。

// **本题采用捆绑测试。**
// | Subtasks |$n,q$  |特殊性质  |分数  |
// | :----------: | :----------: | :----------: | :----------: |
// |Subtask1  |$\leq10^3$  |无  |$10$  |
// |Subtask2  |$\leq10^5$  |树的形态，点权随机  |$15$  |
// |Subtask3  |$\leq10^5$  |最多有 $5$ 种不同的点权，且没有修改 |$15$  |
// |Subtask4  |$\leq10^5$  |树为一条链，且第 $i$$(i>1)$ 个点的父亲为 $i-1$ |$25$  |
// |Subtask5  |$\leq10^5$  |无  |$35$  |

// 对于所有数据 $1 \leq n,q \leq 10^5$，$1 \leq w_i \leq 10^4$，增加的数为不大于 $10^3$ 的正整数，且输入为一棵合法的树。**保证任何时候不同种类的数大于等于 $4$。**
// 懒得写平衡树，用std::map
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E5 + 5;
int f[maxN], depth[maxN], son[maxN], sz[maxN], dfn[maxN], inv[maxN], top[maxN], fir[maxN << 2], sec[maxN << 2], n;
int head[maxN], w[maxN], noe = 0, cnt = 0;
std::map<int, int> st;

struct edge{
    int to, next;
}edges[maxN << 1];

std::pair<int, int> operator+(const std::pair<int, int> a, const std::pair<int, int> b){
    std::pair<int, int> res(0, 0);
    res.first = std::max(a.first, b.first);
    res.second = std::max(a.second, b.second);
    if(res.first > a.first) res.second = std::max(res.second, a.first);
    if(res.first > b.first) res.second = std::max(res.second, b.first);
    return res;
}

inline void add(int u, int v){
    edges[++noe].to = v;
    edges[noe].next = head[u];
    head[u] = noe;
}

inline void dfs1(int u, int fa){
    sz[u] = 1, f[u] = fa, depth[u] = depth[fa] + 1;
    for(int e = head[u]; e; e = edges[e].next){
        int& v = edges[e].to;
        if(v == fa) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if(sz[son[u]] < sz[v]) son[u] = v;
    }
}

inline void dfs2(int u, int topf){
    dfn[u] = ++cnt, inv[cnt] = u, top[u] = topf;
    if(!son[u]) return ;
    dfs2(son[u], topf);
    for(int e = head[u]; e; e = edges[e].next){
        int& v = edges[e].to;
        if(dfn[v]) continue;
        dfs2(v, v);
    }
}

inline void pushUp(int p){
    fir[p] = std::max(fir[p << 1], fir[p << 1 | 1]);
    sec[p] = std::max(sec[p << 1], sec[p << 1 | 1]);
    if(fir[p] > fir[p << 1]) sec[p] = std::max(sec[p], fir[p << 1]);
    if(fir[p] > fir[p << 1 | 1]) sec[p] = std::max(sec[p], fir[p << 1 | 1]);
}

inline void buildTree(int s, int t, int p){
    if(s == t){
        fir[p] = w[inv[s]];
        return ;
    }
    int m = (t + s) >> 1;
    buildTree(s, m, p << 1);
    buildTree(m + 1, t, p << 1 | 1);
    pushUp(p);
}

inline void updata(int id, int v, int s, int t, int p){
    if(s == t){
        fir[p] += v;
        return ;
    }
    int m = (t + s) >> 1;
    if(id <= m) updata(id, v, s, m, p << 1);
    else updata(id, v, m + 1, t, p << 1 | 1);
    pushUp(p);
}    

inline std::pair<int, int> query(int l, int r, int s, int t, int p){
    if(l <= s && r >= t) return {fir[p], sec[p]};
    int m = (t + s) >> 1;
    std::pair<int, int> res = {0, 0};
    if(l <= m) res = query(l, r, s, m, p << 1);
    if(r > m){
        auto it = query(l, r, m + 1, t, p << 1 | 1);
        res = res + it;
    }
    return res;
}

inline void queryHPD(int u, int v){
    std::pair<int, int> res = {0, 0};
    while(top[u] != top[v]){
        if(depth[top[u]] < depth[top[v]]) std::swap(u, v);
        res = res + query(dfn[top[u]], dfn[u], 1, n, 1);
        u = f[top[u]];
    }
    if(depth[u] > depth[v]) std::swap(u, v);
    res = res + query(dfn[u], dfn[v], 1, n, 1);
    if(!res.second){
        std::cout << -1 << std::endl;
        return ;
    }
    int firV = 0, secV = 0;
    for(auto i = st.rbegin(); i != st.rend(); i++){
        if((*i).first == res.first && (*i).second == 1) continue;
        if((*i).first == res.second && (*i).second == 1) continue;
        if(!firV) firV = (*i).first;
        else secV = (*i).first;
        if(secV && firV) break;
    }
    std::cout << res.second << ' ' << secV << std::endl;
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int m, u, v, op, x, y;
    std::cin >> n;
    for(int i = 0; i < n - 1; i++){
        std::cin >> u >> v;
        add(u, v), add(v, u);
    }
    for(int i = 1; i <= n; i++) std::cin >> w[i], st[w[i]]++;
    dfs1(1, 0);
    dfs2(1, 1);
    buildTree(1, n, 1);
    std::cin >> m;
    for(int i = 0; i < m; i++){
        std::cin >> op >> x >> y;
        if(!op){
            updata(dfn[x], y, 1, n, 1);
            st[w[x]]--;
            if(!st[w[x]]) st.erase(w[x]);
            w[x] += y;
            st[w[x]]++;
        }
        else queryHPD(x, y);
    }
    return 0;
}