// # [NOIP2015 提高组] 信息传递

// ## 题目描述

// 有 $n$ 个同学（编号为 $1$ 到 $n$）正在玩一个信息传递的游戏。在游戏里每人都有一个固定的信息传递对象，其中，编号为 $i$ 的同学的信息传递对象是编号为 $T_i$ 的同学。

// 游戏开始时，每人都只知道自己的生日。之后每一轮中，所有人会同时将自己当前所知的生日信息告诉各自的信息传递对象（注意：可能有人可以从若干人那里获取信息，但是每人只会把信息告诉一个人，即自己的信息传递对象）。当有人从别人口中得知自己的生日时，游戏结束。请问该游戏一共可以进行几轮？

// ## 输入格式

// 输入共 $2$ 行。

// 第一行包含 $1$ 个正整数 $n$，表示 $n$ 个人。

// 第二行包含 $n$ 个用空格隔开的正整数 $T_1,T_2,\cdots,T_n$，其中第 $i$ 个整数 $T_i$ 表示编号为 $i$ 的同学的信息传递对象是编号为 $T_i$ 的同学，$T_i\leq n$ 且 $T_i\neq i$。

// ## 输出格式

// 共一行一个整数，表示游戏一共可以进行多少轮。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5
// 2 4 2 3 1
// ```

// ### 样例输出 #1

// ```
// 3
// ```

// ## 提示

// ### 样例 1 解释

// ![](https://cdn.luogu.com.cn/upload/image_hosting/3ca5zl3c.png)

// 游戏的流程如图所示。当进行完第 $3$ 轮游戏后，$4$ 号玩家会听到 $2$ 号玩家告诉他自己的生日，所以答案为 $3$。当然，第 $3$ 轮游戏后，$2$ 号玩家、 $3$ 号玩家都能从自己的消息来源得知自己的生日，同样符合游戏结束的条件。

// - 对于 $30\%$ 的数据，$n\le 200$；
// - 对于 $60\%$ 的数据，$n\le 2500$；
// - 对于 $100\%$ 的数据，$n\le 2\times 10^5$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 2E5 + 5;
int to[maxN], dfn[maxN], res = 0X3f3f3f3f, cnt = 0;
bool vis[maxN], in[maxN];

inline void dfs(int now, int pre){
    if(vis[now]){
        if(!in[now]) return ;
        int cnt = 0;
        res = std::min(res, dfn[pre] - dfn[now] + 1);
        return ;
    }
    vis[now] = 1, dfn[now] = ++cnt, in[now] = 1;
    dfs(to[now], now);
    in[now] = 0;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    for(int i = 1; i <= n; i++) std::cin >> to[i];
    for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i, 0);
    std::cout << res;
    return 0;
}