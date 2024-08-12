// # 地震逃生

// ## 题目描述

// 汶川地震发生时，四川\*\*中学正在上课，一看地震发生，老师们立刻带领 $x$ 名学生逃跑，整个学校可以抽象地看成一个有向图，图中有 $n$ 个点，$m$ 条边。$1$ 号点为教室，$n$ 号点为安全地带，每条边都只能容纳一定量的学生，超过楼就要倒塌，由于人数太多，校长决定让同学们分成几批逃生，只有第一批学生全部逃生完毕后，第二批学生才能从 $1$ 号点出发逃生，现在请你帮校长算算，每批最多能运出多少个学生，$x$ 名学生分几批才能运完。

// ## 输入格式

// 第一行三个整数 $n,m,x$；  
// 以下 $m$ 行，每行三个整数 $a,b,c$（$1\leq a,b\leq n$，$0\leq c\leq x$）描述一条边，分别代表从 $a$ 点到 $b$ 点有一条边，且可容纳 $c$ 名学生。

// ## 输出格式

// 两个整数，分别表示每批最多能运出多少个学生，$x$ 名学生分几批才能运完。如果无法到达目的地（$n$ 号点）则输出 `Orz Ni Jinan Saint Cow!`。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6 7 7
// 1 2 1
// 1 4 2
// 2 3 1
// 4 5 1
// 4 3 1
// 3 6 2
// 5 6 1
// ```

// ### 样例输出 #1

// ```
// 3 3
// ```

// ## 提示

// **【注释】**

// 比如有图

// ```plain
// 1 2 100
// 2 3 1
// ```

// $100$ 个学生先冲到 $2$ 号点，然后一个一个慢慢沿 $2 \to 3$ 边走过去。

// 18 神牛规定这样是不可以的……

// 也就是说，每批学生必须同时从起点出发，并且同时到达终点。

// **【数据范围】**

// 对于 $100 \%$ 的数据，$0 \le x < 2^{31}$，$1 \le n \le 200$，$1 \le m \le 2000$。
#include <bits/stdc++.h>

const int maxN = 205, maxM = 2E3 + 5;

struct edge
{
    int to, next, cap , flow;
}edges[maxM << 1];

int head[maxN], noe = 0;
int depth[maxN], gap[maxN], cur[maxN], s, t, n;

inline void add(int u, int v, int w)
{
    edges[noe].to = v;
    edges[noe].next = head[u];
    edges[noe].cap = w;
    head[u] = noe++;
}

inline void bfs()
{
    std::queue<int> q;
    depth[t] = 1;
    q.push(t);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        ++gap[depth[u]];
        for(int e = head[u]; ~e; e = edges[e].next)
        {
            int &v = edges[e].to;
            if(depth[v]) continue;
            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }
}

inline int dfs(int u, int flow)
{
    if(u == t) return flow;
    int ret = 0;
    for(int& e = cur[u]; ~e; e = edges[e].next)
    {
        int &v = edges[e].to, &cap = edges[e].cap, &f = edges[e].flow;
        if(depth[v] + 1 == depth[u])
        {
            int reflow = dfs(v, std::min(flow - ret, cap - f));
            edges[e].flow += reflow;
            edges[e ^ 1].flow -= reflow;
            ret += reflow;
            if(ret == flow) return flow;
        }
    }

    --gap[depth[u]];
    if(!gap[depth[u]]) depth[s] = n + 1;
    ++gap[++depth[u]];
    cur[u] = head[u];
    return ret;
}

inline int ISPA()
{
    bfs();
    int mx_flow = 0;
    memcpy(cur + 1, head + 1, sizeof(int) * n);
    while(depth[s] && depth[s] <= n) mx_flow += dfs(s, INT32_MAX);
    return mx_flow;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, x, u, v, w;
    std::cin >> n >> m >> x;
    memset(head + 1, -1, sizeof(int) * n);
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, 0);
    }
    s = 1, t = n;
    int mx_flow = ISPA();
    if(!mx_flow) std::cout << "Orz Ni Jinan Saint Cow!";
    else std::cout << mx_flow << ' ' << (1ll * x + mx_flow - 1) / mx_flow;
    return 0; 
}