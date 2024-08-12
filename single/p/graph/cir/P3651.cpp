// # 展翅翱翔之时 (はばたきのとき)

// ## 题目背景

// **船が往くよミライへ旅立とう**

// **船只启航 朝未来展开旅途**

// **青い空笑ってる（なにがしたい?）**

// **湛蓝天空露出微笑（想做些什么?）**

// **ヒカリになろうミライを照らしたい**

// **化作光芒吧 想就此照亮未来**

// **輝きは心からあふれ出してもっと先の景色望むんだ**

// **光辉自内心满溢而出 愿能望见更加前方的景色**

// **Ah!やっと手にしたミライチケットかざして…！**

// **Ah!挥舞起终于得手的未来门票…！**



//  ![](https://cdn.luogu.com.cn/upload/pic/4529.png) 

// 我们Aqours，终于闪闪发亮了！


// 2月25和26日，将是我们登上横滨ARENA演唱的日子！


// 而且，还要在全日本、甚至全世界的好多影院进行转播呢！


// 转播好像还是通过中继卫星传输的呢！


// 未来ずら！

// ## 题目描述

// 不过，好像中继卫星上，出了一些问题呢……

// 我们的中继卫星一共有 $N$ 颗，编号成 $1$ 到 $N$。不过，好像一个中继卫星可以且仅可以单向地从另一颗中继卫星那儿接收数据。

// 第 $i$ 颗卫星现在已经被设定到了从第 $A_i$ 颗卫星（称为接收源）那儿接受数据。

// 不过这些中继卫星的接收源是可以修改的，只不过每次修改要花一定的资金呢。

// 听说要达成中继的话，这些卫星之间必须**两两之间能够互相（直接或间接）通信**才行啊。

// 虽然鞠莉家里很有钱，可是这么大的花费，也得提前准备一下呢。

// 所以，你能帮我们算算这样子一共最少要花多少钱吗？

// ## 输入格式

// 第一行一个整数 $N$。

// 接下来 $N$ 行，每行 $2$ 个整数 $A_i,C_i$，表示初始时，第 $i$ 个中继卫星从第 $A_i$ 颗卫星处接收数据，以及该卫星调整接收源的所需花费。

// ## 输出格式

// 输出一个整数，表示鞠莉所需准备的最小的花费。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4
// 2 2
// 1 6
// 1 3
// 3 1
// ```

// ### 样例输出 #1

// ```
// 5
// ```

// ## 提示

// ### 数据范围及约定

// - 对于 $10\%$ 的数据，满足 $N \le 10$。
// - 对于 $40\%$ 的数据，满足 $N \le 15$。
// - 对于 $70\%$ 的数据，满足 $N \le 3000$。
// - 对于 $100\%$ 的数据，满足 $2 \le N \le 100000,1 \le C_i \le 10^9$。

// ### 以下是彩蛋

// 事实上 LoveLive 的直播卫星中继只有一颗星，而且永远都是不加密的。

// 导致只要有一个卫星锅就可以在家偷偷看直播，也就是传说中的卫星源。

// lin_toto：万代南梦宫都把浅水湾给买了，居然只有回放，只好跑到香港 the sky 去看 + 手动滑稽。

// 至于为什么看转播，eplus 表示 LoveLive 系列演唱会的票大家尽管抽选尽管抢，买得到算我输。

// 于是 lin_toto 在去年 μ's Final LoveLive 的时候拿肉鸡把 eplus 搞趴下了，然后就买到了。

// 于是今年 eplus 连抢票都不让抢了，全抽选，抽得到算我输。

// 然后 lin_toto 就去看转播了。
#include <bits/stdc++.h>
#define ll long long

const int maxN = 1E5 + 5;

struct edge{
    int to, next;
}edges[maxN], invEdges[maxN];

int head[maxN], invHead[maxN], noe = 0;
int w[maxN], ban = 0;
int stk[maxN], stkW[maxN], cir[maxN], cirW[maxN], top = 0, cnt = 0;
bool vis[maxN], inStk[maxN];
ll res = 0;

inline void add(int u, int v)
{
    edges[++noe].to = v;
    edges[noe].next = head[u];
    head[u] = noe;
    invEdges[noe].to = u;
    invEdges[noe].next = invHead[v];
    invHead[v] = noe; 
}

inline bool dfs1(int u)
{
    if(inStk[u])
    {
        do
        {
            cir[++cnt] = stk[top];
            cirW[cnt] = stkW[top];
        }while(stk[top--] != u);
        return true;
    }
    if(vis[u]) return false;
    stk[++top] = u;
    inStk[u] = vis[u] = 1;
    for(int e = head[u]; e; e = edges[e].next)
    {
        int &v = edges[e].to;
        stkW[top] = w[e];
        if(dfs1(v)) return true;
    }
    --top;
    return false;
}

inline int dfs2(int u)
{
    ll tot = 0;
    int mx = 0;
    vis[u] = 1;
    for(int e = invHead[u]; e; e = invEdges[e].next)
    {
        int &v = invEdges[e].to;
        if(v == ban) continue;
        tot += w[e];
        mx = std::max(mx, w[e]);
        dfs2(v);
    }
    res += tot - mx;
    return mx;
}

inline void solveCir()
{
    cir[cnt + 1] = cir[1];
    cirW[cnt + 1] = cirW[1];
    int mn = 0X3f3f3f3f;
    for(int i = 1; i <= cnt; ++i)
    {
        ban = cir[i + 1];
        int v = std::min(dfs2(cir[i]), cirW[i + 1]);
        res += v;
        mn = std::min(mn, cirW[i + 1] - v);
    }
    res += mn;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, u;
    std::cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> u >> w[i];
        add(i, u);
    }
    for(int i = 1; i <= n; ++i)
    {
        if(!vis[i])
        {
            cnt = 0, top = 0;
            dfs1(i);
            solveCir();
        }
    }
    if(cnt == n)
    {
        std::cout << 0;
    }
    else std::cout << res;
    return 0;
}