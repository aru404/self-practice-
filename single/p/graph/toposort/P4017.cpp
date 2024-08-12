// # 最大食物链计数

// ## 题目背景

// 你知道食物链吗？Delia 生物考试的时候，数食物链条数的题目全都错了，因为她总是重复数了几条或漏掉了几条。于是她来就来求助你，然而你也不会啊！写一个程序来帮帮她吧。

// ## 题目描述

// 给你一个食物网，你要求出这个食物网中最大食物链的数量。

// （这里的“最大食物链”，指的是**生物学意义上的食物链**，即**最左端是不会捕食其他生物的生产者，最右端是不会被其他生物捕食的消费者**。）

// Delia 非常急，所以你只有 $1$ 秒的时间。

// 由于这个结果可能过大，你只需要输出总数模上 $80112002$ 的结果。

// ## 输入格式

// 第一行，两个正整数 $n、m$，表示生物种类 $n$ 和吃与被吃的关系数 $m$。

// 接下来 $m$ 行，每行两个正整数，表示被吃的生物A和吃A的生物B。

// ## 输出格式

// 一行一个整数，为最大食物链数量模上 $80112002$ 的结果。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 7
// 1 2
// 1 3
// 2 3
// 3 5
// 2 5
// 4 5
// 3 4
// ```

// ### 样例输出 #1

// ```
// 5
// ```

// ## 提示

// 各测试点满足以下约定：

//  ![](https://cdn.luogu.com.cn/upload/pic/12011.png) 

// 【补充说明】

// 数据中不会出现环，满足生物学的要求。（感谢 @AKEE ）
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 5E3 + 5, maxM = 5E5 + 5, mod = 80112002;
int cnt[maxN], in[maxN], noe = 0;

std::vector<int> es[maxN];

inline int toposort(int n){
    std::queue<int> q;
    int res = 0;
    for(int i = 1; i <= n; i++) if(!in[i]) q.emplace(i), cnt[i] = 1;
    while(!q.empty()){
        int top = q.front();
        q.pop();
        for(auto to:es[top]){
            in[to]--;
            cnt[to] = (cnt[to] + cnt[top]) % mod;
            if(!in[to]) q.emplace(to);
        }
        if(es[top].empty()) res = (res + cnt[top]) % mod;
    }
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, u, v;
    std::cin >> n >> m;
    for(int i = 0; i < m; i++){
        std::cin >> u >> v;
        es[v].push_back(u), in[u]++;
    }
    std::cout << toposort(n);
    return 0;
}