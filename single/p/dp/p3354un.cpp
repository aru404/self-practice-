// # [IOI2005] Riv 河流

// ## 题目描述

// 几乎整个 Byteland 王国都被森林和河流所覆盖。小点的河汇聚到一起，形成了稍大点的河。就这样，所有的河水都汇聚并流进了一条大河，最后这条大河流进了大海。这条大河的入海口处有一个村庄——名叫 Bytetown。

// 在 Byteland 国，有 $n$ 个伐木的村庄，这些村庄都座落在河边。目前在 Bytetown，有一个巨大的伐木场，它处理着全国砍下的所有木料。木料被砍下后，顺着河流而被运到 Bytetown 的伐木场。Byteland 的国王决定，为了减少运输木料的费用，再额外地建造 $k$ 个伐木场。这 $k$ 个伐木场将被建在其他村庄里。这些伐木场建造后，木料就不用都被送到 Bytetown 了，它们可以在运输过程中第一个碰到的新伐木场被处理。显然，如果伐木场座落的那个村子就不用再付运送木料的费用了。它们可以直接被本村的伐木场处理。

// 注：所有的河流都不会分叉，形成一棵树，根结点是 Bytetown。

// 国王的大臣计算出了每个村子每年要产多少木料，你的任务是决定在哪些村子建设伐木场能获得最小的运费。其中运费的计算方法为：每一吨木料每千米 $1$ 分钱。

// ## 输入格式

// 第一行包括两个整数 $n,k$。$n$ 为村庄数，$k$ 为要建的伐木场的数目。除了 Bytetown 外，每个村子依次被命名为 $1,2,3\ldots n$，Bytetown 被命名为 $0$。

// 第 $2$ 到第 $(n + 1)$ 行，每行 $3$ 个整数，第 $(i + 1)$ 行的整数分别代表，分别表示每年 $i$ 村子产的木料的块数 $w_i$，离 $i$ 村子下游最近的村子 $v_i$（即 $i$ 村子的父结点），$v_i$ 到 $i$ 的距离 $d_i$（千米）。

// ## 输出格式

// 输出最小花费，单位为分。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 2
// 1 0 1
// 1 1 10
// 10 2 5
// 1 2 3
// ```

// ### 样例输出 #1

// ```
// 4
// ```

// ## 提示

// #### 数据规模与约定

// - 对于 $50\%$ 的数据，保证 $n\le 20$。
// - 对于 $100\%$ 的数据，保证 $2\le n\le 100$，$1\le k\le \min(n,50)$，$0\le v_i\le n$，$0\le w_i\le 10^4$，$1\le d_i\le 10^4$。
// - 保证每年所有的木料流到 bytetown 的运费不超过 $2\times 10^9$ 分。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 105;
int dp[maxN][maxN][51], head[maxN], sz[maxN], noe = 0, k;

struct edge{
    int to, next, w;
}edges[maxN << 1];

inline void add(int u, int v, int w){
    edges[++noe].to = v;
    edges[noe].next = head[u];
    edges[noe].w = w;
    head[u] = noe;
}

inline void dfs(int u){
    sz[u] = 1;
    for(int e = head[u]; e; e = edges[e].next){
        int& v = edges[e].to, &w = edges[e].w;
        dfs(v);
        sz[u] += sz[v];
        for(int i = sz[u]; i >= 1; i--){
            for(int j = sz[v]; j; j--){
                for(int l = std::min(k, sz[u]); l; l--){
                    for(int r = std::min(l, sz[v]); r; r--){
                        dp[u][i][l] = std::min(1ll * dp[u][i][l], 1ll * w * j + dp[u][i - j][l - r] + dp[v][j][r]);
                    }
                }
            }
        }
    }
    for(int i = 1; i <= std::min(k, sz[u]); i++){
        for(int j = 1; j <= sz[u]; j++){
            dp[u][0][i] = std::min(dp[u][0][i], dp[u][j][i - 1]);
        }
    }
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    for(int i = 1; i <= n; i++)
}