// # EntropyIncreaser 与 动态图

// ## 题目背景

// 话说 NaCly_Fish 在和  $\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 吃饭时，问过她一个问题：“一个无向图，支持动态加边，求两点间割点数，怎么做？” 

// $\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 想了几秒，说：“这不是sb题吗，随便怎么做都行吧。”然后三两句道出了一个算法。

// 而 NaCly_Fish 还是不会，请你来教教她这题怎么做吧。

// ## 题目描述

// 有一个 $n$ 个点的图，初始没有边。  
// 有 $q$ 个操作，分为 $3$ 种，具体如下：  

// - `1 u v` 表示在 $u,v$ 之间连一条无向边  
// - `2 u v` 表示求 $u,v$ 间的割边数量   
// - `3 u v` 表示求 $u,v$ 间的割点数量   

// 特别地，对于 $2$、$3$ 操作，若 $u,v$ 不连通，则输出 $-1$    
// ****
// 为了防止有歧义，这里给出对两点间割边和割点数量的定义：  
// 对于所有包含 $u,v$ 的路径的节点集合之交 $S$ ，定义 $S$ 中的元素数量为 $u,v$ 间的割点数。  
// 对于所有包含 $u,v$ 的路径的边集合之交 $T$ ，定义 $T$ 中的元素数量为 $u,v$ 间的割边数。  
// ****
// **本题强制在线。**  
// 从第二行开始，每次的输入的 $u,v$ 都需要异或上 $\text{last}$ ，才是实际操作的 $u,v$。  
//  $\text{last}$ 为最近一次**答案非 $-1$ 的**询问的答案，定义初始 $\text{last}=0$   
// ps：如果您不知道异或是什么意思，可以看这里：[xor](https://www.baidu.com/link?url=bhG_De1gZYsqrIq7dkhgGj8vP87xSSyoIwk0-5p1fyKmf58cznvq0oYJg0XGoyKNpuGk7EsvjUnyvgJ19_ZA3PhoMJ3hIufHZ5GXh1OaIoS&wd=&eqid=ab26bc160004324d000000035d1ed64e)

// ## 输入格式

// 第一行两个正整数 $n,q$，表示节点数和操作次数。   
// 接下来 $q$ 行，每行三个整数，表示一次操作。

// ## 输出格式

// 对于每个$2$、$3$ 操作，输出一行一个整数表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 10
// 1 1 2
// 1 2 3
// 2 1 3
// 3 0 1
// 1 3 1
// 1 1 6
// 2 3 7
// 1 6 7
// 1 7 1
// 3 3 6
// ```

// ### 样例输出 #1

// ```
// 2
// 2
// -1
// 3
// ```

// ## 提示

// ~~题目背景为真实事件~~

// ### 样例说明：  
// 实际操作为：  
// ```cpp
// 5 10
// 1 1 2
// 1 2 3
// 2 1 3
// 3 2 3
// 1 1 3
// 1 3 4
// 2 1 5
// 1 4 5
// 1 5 3
// 3 1 4
// ```

// 【数据范围】
  
// 对于 $20\%$ 的数据，$1\le n,q \le 2000$ ；   
// 对于另外 $30\%$ 的数据，所有 $2$、$3$ 操作均在 $1$ 操作之后；    
// 对于 $100\%$ 的数据，$1\le n \le 10^5$，$1\le q \le 3\times 10^5$。
    
// 对于 $1$ 操作，保证 $u\neq  v$。  

// By：NaCly_Fish

// ****

// 欢迎加入 EI队长粉丝裙，群号：$747262201$
#include <iostream>
#include <bits/stdc++.h>
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
#define get(x) (ch[f[x]][1] == x)
#define isRoot(x) (ch[f[x]][get(x)] != x)

const int maxN = 1E5 + 5;
int ch[maxN << 1][2], f[maxN << 1], w1[maxN << 1], w2[maxN << 1], s[maxN << 1], cnt = 0, n;
bool tag[maxN << 1], isCir[maxN << 1];

inline void pushUp(int x){
    w1[x] = w1[ls(x)] + w1[rs(x)] + (x <= n);
    w2[x] = (!isCir[x]) + w2[ls(x)] + w2[rs(x)];
}

inline void pushDown(int x){
    if(tag[x]){
        std::swap(ls(ls(x)), rs(ls(x)));
        std::swap(ls(rs(x)), rs(rs(x)));
        tag[ls(x)] ^= 1, tag[rs(x)] ^= 1;
        tag[x] = 0;
    }
}

inline void updata(int x){
    int idx = 0;
    s[++idx] = x;
    while(!isRoot(x)) x = f[x], s[++idx] = x;
    while(idx) pushDown(s[idx--]);
}

inline void rotate(int x){
    int y = f[x], z = f[y], k = get(x);
    if(!isRoot(y)) ch[z][get(y)] = x;
    if(ch[x][!k]) f[ch[x][!k]] = y;
    ch[y][k] = ch[x][!k], ch[x][!k] = y;
    f[x] = z, f[y] = x;
    pushUp(y), pushUp(x);
}

inline void splay(int x){
    updata(x);
    for(int fa = f[x]; !isRoot(x); rotate(x), fa = f[x]){
        if(!isRoot(fa)) rotate(get(x) ^ get(fa)? x:fa);
    }
}

inline int access(int x){
    int p;
    for(p = 0; x; p = x, x = f[x]){
        splay(x);
        rs(x) = p;
        pushUp(x);
    }
    return p;
}

inline void makeRoot(int x){
    access(x);
    splay(x);
    tag[x] ^= 1;
    std::swap(ls(x), rs(x));
}

inline int findRoot(int x){
    access(x);
    splay(x);
    while(ls(x)) pushDown(x), x = ls(x);
    splay(x);
    return x;
}

inline void split(int x, int y){
    makeRoot(x);
    access(y);
    splay(y);
}

inline void link(int x, int y){
    makeRoot(x);
    f[x] = y;
}

inline void modify(int x){
    int c, idx = 0;
    std::function<void(int)> dfs = [&](int y){
        if(!y) return ;
        if(y > n) c = y;
        s[++idx] = y;
        pushDown(y);
        dfs(ls(y)), dfs(rs(y));
    };
    pushDown(x);
    dfs(ls(x)), dfs(rs(x));
    ls(x) = rs(x) = 0, w1[x] = 1, w2[x] = 0;
    for(int i = 1; i <= idx; i++){
        if(s[i] != c) f[s[i]] = c;
        ls(s[i]) = rs(s[i]) = 0;
        isCir[s[i]] = 1;
        w2[s[i]] = 0;
        w1[s[i]] = s[i] <= n;
    }
    f[c] = x;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, u, v, op, res = 0;
    std::cin >> n >> m;
    cnt = n;
    for(int i = 1; i <= n; i++) isCir[i] = 1;
    for(int i = 0; i < m; i++){
        std::cin >> op >> u >> v;
        u ^= res, v ^= res;
        if(op == 1){
            makeRoot(u);
            if(findRoot(v) == u){
                modify(u);
            }
            else{
                ++cnt;
                link(cnt, u);
                link(cnt, v);
            }
        }
        else{
            makeRoot(u);
            if(findRoot(v) != u){
                std::cout << -1 << std::endl;
                continue;
            }
            if(op == 2) std::cout << w2[u] << std::endl, res = w2[u];
            else std::cout << w1[u] << std::endl, res = w1[u];
        }
    }
    return 0;
}