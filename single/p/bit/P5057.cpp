// # [CQOI2006] 简单题

// ## 题目描述

// 有一个 $n$ 个元素的数组，每个元素初始均为 $0$。有 $m$ 条指令，每条指令为两种操作中的一种：
// 1. 让其中一段连续序列数字反转；（即 $0$ 变 $1$，$1$ 变 $0$）
// 2. 询问某个元素的值。

// 例如当 $n=20$ 时，$10$ 条指令如下：

// ![](https://cdn.luogu.com.cn/upload/pic/44663.png)

// ## 输入格式

// 第一行包含两个整数 $n,m$，表示数组的长度和指令的条数。

// 接下来 $m$ 行，每行的第一个数 $t$ 表示操作的种类：

// * 若 $t=1$，则接下来有两个数 $L,R$，表示反转区间 $[L,R]$ 的每个数；
// * 若 $t=2$，则接下来只有一个数 $i$，表示询问的下标。

// ## 输出格式

// 每个操作 $2$ 输出一行（非 $0$ 即 $1$），表示每次操作 $2$ 的回答。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 20 10
// 1 1 10
// 2 6
// 2 12
// 1 5 12
// 2 6
// 2 15
// 1 6 16
// 1 11 17
// 2 12
// 2 6
// ```

// ### 样例输出 #1

// ```
// 1
// 0
// 0
// 0
// 1
// 1
// ```

// ## 提示

// 对于 $50\%$ 的数据，$1 \le n \le 10^3$，$1 \le m \le 10^4$；

// 对于 $100\%$ 的数据，$1 \le n \le 10^5$，$1 \le m \le 5 \times 10^5$，保证 $L \le R$。
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

const int maxN = 1E5 + 5;
int n;
bool tree[maxN];

inline void updata(int x)
{
    while(x <= n) tree[x] ^= 1, x += lowbit(x);
}

inline bool query(int x)
{
    bool res = 0;
    while(x) res ^= tree[x], x -= lowbit(x);
    return res;
}

inline void reverseRange(int l, int r)
{
    updata(l), updata(r + 1);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, l, r, t;
    std::cin >> n >> m;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> t >> l;
        if(t == 1) std::cin >> r, reverseRange(l, r);
        else std::cout << query(l) << '\n';
    }
    return 0;
}