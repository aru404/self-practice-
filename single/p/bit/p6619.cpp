// # [省选联考 2020 A/B 卷] 冰火战士

// ## 题目背景

// A 卷 D1T1，B 卷 D1T3。

// 时限 3s，内存 512MB。

// ## 题目描述

// 一场比赛即将开始。

// 每位战士有两个属性：温度和能量，有两派战士：冰系战士的技能会对周围造成降温冰冻伤害，因而要求场地温度不低于他的自身温度才能参赛；火系战士的技能会对周围造成升温灼烧伤害，因而要求场地温度不高于他的自身温度才能参赛。

// 当场地温度确定时，双方能够参赛的战士分别排成一队。冰系战士按自身温度从低到高排序，火系战士按自身温度从高到低排序，温度相同时能量大的战士排在前面。首先，双方的第一位战士之间展开战斗，两位战士消耗相同的能量，能量少的战士将耗尽能量退出比赛，而能量有剩余的战士将继续和对方的下一位战士战斗（能量都耗尽则双方下一位战士之间展开战斗）。如此循环，直至某方战士队列为空，比赛结束。

// 你需要寻找最佳场地温度：使冰火双方消耗总能量最高的温度的最高值。

// 现在，比赛还处于报名阶段，目前还没有任何战士报名，接下来你将不断地收到报名信息和撤回信息。其中，报名信息包含报名战士的派系和两个属性，撤回信息包含要撤回的报名信息的序号。每当报名情况发生变化（即收到一条信息）时，你需要立即报出当前局面下的最佳场地温度，以及该场地温度下双方消耗的总能量之和是多少。若当前局面下无论何种温度都无法开展比赛（某一方没有战士能参赛），则只要输出 `Peace`。

// ## 输入格式

// 第一行一个数 $Q$，表示信息的数量。

// 接下来 $Q$ 行，每行为 `1 t x y` $(t \in \{0, 1\}$，$x$ 和 $y$ 都是正整数 $)$ 或 `2 k`（$k$ 是正整数）：

// `1 t x y` 表示一条报名信息，$t = 0$ 时报名战士是冰系，$t = 1$ 时报名战士是火系，$x$ 表示战士的自身温度，$y$ 表示战士的能量。

// `2 k` 表示一条撤回信息，撤回的是第 $k$ 条信息。被撤回的信息一定是报名信息，已被撤回的信息不会再次被撤回。

// ## 输出格式

// 共 $Q$ 行，每行有两个用空格隔开的正整数，分别表示当前局面下的最佳温度和该温度下冰火双方消耗的总能量之和。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 8
// 1 1 103 150
// 1 0 100 100
// 1 1 102 150
// 1 0 103 300
// 2 1
// 1 1 101 100
// 1 1 104 350
// 1 0 100 400
// ```

// ### 样例输出 #1

// ```
// Peace
// 103 200
// 103 200
// 103 300
// 102 200
// 102 200
// 104 700
// 102 1000
// ```

// ## 提示

// #### 样例 1 解释
// 为说明方便，约定：若第 $k$ 条信息是报名信息，则该条报名信息对应战士 $k$。样例中含有战士 $1,2,3,4,6,7,8$，由于第 $5$ 条是撤回信息，所以没有战士 $5$。

// 下面逐个解释每个输出：

// 1. 只有火系战士：战士 $1$，无法比赛，输出 `Peace`。
// 2. 温度为 $100 \sim 103$ 都能消耗最多的能量 $200$：战士 $1$ 对阵战士 $2$ 消耗能量 $200$，最佳温度为 $103$。
// 3. 温度为 $100 \sim 103$ 都能消耗最多的能量 $200$：战士 $1$ 对阵战士 $2$ 消耗能量 $200$，最佳温度为 $103$。
// 4. 温度 $103$ 能消耗最多的能量 $300$：首先，战士 $1$ 对阵战士 $2$ 消耗能量 $200$；然后，战士 $1$ 对阵战士 $4$ 消耗能量 $100$，最佳温度为 $103$。
// 5. 从现在起战士 $1$ 不再存在。温度 $100 \sim 102$ 能消耗最多的能量 $200$：战士 $2$ 对阵战士 $3$ 消耗能量 $200$，最佳温度为 $102$。

// #### 样例 2

// 见附加文件中 `icefire2.in` 与 `icefire2.ans`。

// #### 数据范围

// $10\%$ 的数据：$Q \leq 100$，$x \leq 10^3$。

// 另有 $20\%$ 的数据：$Q \leq 10^4$，$x \leq 5000$，不存在撤回信息，且输入的 $x$ 按顺序不降。

// $60\%$ 的数据（包含上述 $20\%$，下同）：$Q \leq 2 \times 10^5$，$x \leq 2 \times 10^5$。

// $90\%$ 的数据：$Q \leq 2 \times 10^6$，$x \leq 2 \times 10^6$。

// $100\%$ 的数据：$1 \leq Q \leq 2 \times 10^6$，$1 \leq x \leq 2 \times 10^9$，所有 $y$ 之和不超过 $2 \times 10^9$，保证不存在 $t, x, y$ 完全相同的两个战士。
// 树状数组二分
#include <iostream>
#include <bits/stdc++.h>
#define lowbit(p) (p & -p)

const int maxN = 2E6 + 5;
int energy1[maxN], energy2[maxN], op[maxN], pop[maxN >> 1], x[maxN], y[maxN], inv[maxN], rk[maxN], tmp[maxN], k = 0, tot = 0;
bool type[maxN];

inline void init(int m){
    std::sort(inv + 1, inv + m + 1, [&](const int a, const int b){
        return x[a] < x[b];
    });
    for(int i = 1; i <= m; i++){
        if(x[inv[i]] > tmp[k]) tmp[++k] = x[inv[i]];
        rk[inv[i]] = k;
    }
}

inline void updata(int p, int v, int* e){
    while(p <= k){
        e[p] += v;
        p += lowbit(p);
    }
}

inline int query(int p, int* e){
    int res = 0;
    while(p) res += e[p], p -= lowbit(p);
    return res;
}

inline std::pair<int, int> find1(){
    int ice = 0, fire = tot, p = 0;
    for(int i = 20; ~i; i--){
        if(p + (1 << i) > k) continue;
        int nIce = ice + energy1[p + (1 << i)];
        int nFire = fire + energy2[p + (1 << i)];
        if(nIce < nFire){
            ice = nIce, fire = nFire;
            p += 1 << i;
        }
    }
    return {ice, p};
}

inline std::pair<int, int> find2(int minV){
    int p = 0, fire = tot;
    for(int i = 20; ~i; i--){
        if(p + (1 << i) > k) continue;
        int nFire = fire + energy2[p + (1 << i)];
        if(nFire >= minV){
            fire = nFire;
            p += 1 << i;
        }
    }
    return {fire, p};
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, idx1 = 0, idx2 = 0;
    std::cin >> n;
    for(int i = 1; i <= n; i++){
        std::cin >> op[i];
        if(op[i] == 1){
            inv[++idx1] = i;
            std::cin >> type[i] >> x[i] >> y[i]; 
        }
        else{
            ++idx2;
            std::cin >> pop[idx2];
        }
    }
    init(idx1);
    idx1 = idx2 = 0;
    for(int i = 1; i <= n; i++){
        if(op[i] == 1){
            if(type[i]) updata(rk[i] + 1, -y[i], energy2), tot += y[i];
            else updata(rk[i], y[i], energy1);
        }
        else{
            if(type[pop[++idx2]]) updata(rk[pop[idx2]] + 1, y[pop[idx2]], energy2), tot -= y[pop[idx2]];
            else updata(rk[pop[idx2]], -y[pop[idx2]], energy1);
        }
        auto res1 = find1(), res2 = find2(tot + query(res1.second + 1, energy2));
        if(res1.first <= res2.first) std::swap(res1, res2);
        if(!res1.first) std::cout << "Peace" << std::endl;
        else std::cout << tmp[res1.second] << ' ' << (res1.first << 1) << std::endl;
    }
    return 0;
}