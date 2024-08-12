// # [USACO5.1] 圈奶牛Fencing the Cows /【模板】二维凸包

// ## 题目背景

// upd: 新增一组 hack 数据。

// ## 题目描述

// 农夫约翰想要建造一个围栏用来围住他的奶牛，可是他资金匮乏。他建造的围栏必须包括他的奶牛喜欢吃草的所有地点。对于给出的这些地点的坐标，计算最短的能够围住这些点的围栏的长度。

// ## 输入格式

// 输入数据的第一行是一个整数。表示农夫约翰想要围住的放牧点的数目 $n$。

// 第 $2$ 到第 $(n + 1)$ 行，每行两个实数，第 $(i + 1)$ 行的实数 $x_i, y_i$ 分别代表第 $i$ 个放牧点的横纵坐标。

// ## 输出格式

// 输出输出一行一个四舍五入保留两位小数的实数，代表围栏的长度。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4
// 4 8
// 4 12
// 5 9.3
// 7 8
// ```

// ### 样例输出 #1

// ```
// 12.00
// ```

// ## 提示

// #### 数据规模与约定

// 对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^5$，$-10^6 \leq x_i, y_i \leq 10^6$。小数点后最多有 $2$ 位数字。
#include <bits/stdc++.h>

const int maxN = 1E5 + 5;

struct node
{
    double x, y;
    node(double x = 0, double y = 0):x(x), y(y){}

    bool operator<(const node& b) const
    {
        return x == b.x? y < b.y:x < b.x;
    }
}nodes[maxN];

int stk[maxN], top = 0;

inline double crossProduct(const node& a, const node& b, const node& c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

inline double dist(const node& a, const node& b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline void andrew(int n)
{
    std::sort(nodes + 1, nodes + n + 1, std::less<node>{});
    
    std::bitset<maxN> vis = 0;
    stk[++top] = 1;

    for(int i = 2; i <= n; ++i)
    {
        while(top >= 2 && crossProduct(nodes[stk[top - 1]], nodes[stk[top]], nodes[i]) <= 0.0)
        {
            vis[stk[top--]] = 0;
        }
        vis[i] = 1;
        stk[++top] = i;
    }

    int cnt = top;
    for(int i = n - 1; i; --i)
    {
        if(vis[i]) continue;
        while(top > cnt && crossProduct(nodes[stk[top - 1]], nodes[stk[top]], nodes[i]) <= 0.0)
        {
            --top;
        }
        stk[++top] = i;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    for(int i = 1; i <= n; ++i) std::cin >> nodes[i].x >> nodes[i].y;

    double res = 0;
    andrew(n);
    for(int i = 1; i < top; ++i) res += dist(nodes[stk[i]], nodes[stk[i + 1]]);
    std::cout << std::fixed << std::setprecision(2) << res;
    return 0;
}