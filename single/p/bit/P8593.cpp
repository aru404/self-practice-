// # 「KDOI-02」一个弹的投

// ## 题目背景

// - 前置芝士：[平抛运动](https://baike.baidu.com/item/%E5%B9%B3%E6%8A%9B%E8%BF%90%E5%8A%A8/974021?fr=aladdin)
// ~~（看到这个如果不想做可以直接开下一题）~~

// 「这群该死的外星人，肯定是来抢夺新矿资源的！」  
// 「这导弹什么鬼啊，研究不明白。」  
// 无数的水滴型武器从苍穹之外落下，猛击着无知的生命。

// ## 题目描述

// 经研究，该武器的运作方式是这样的。其中设重力方向为 $y$ 轴负半轴，$x$ 轴为地面，速度向右为正向左为负。  
// - 每颗导弹在 $(x_i,y_i)$ 的地方投放并悬浮，初始速度设置为 $v_i$。
// - 所有导弹投放完成后，于同一时刻开始照初始速度做平抛运动。其中 $g=9.8$。  
// - 每颗导弹与另一颗导弹碰撞时，不会改变原来的路线，并且将爆破威力 $p_i$ 增加 $1$，所有导弹初始时 $p_i=0$，**在接触到 $x$ 轴时碰撞也增加威力**。
// - 当武器落到 $x$ 轴时，会对落点造成 $p_i$ 点杀伤力。

// 地面指挥部提前预测了导弹的落点，并部署了反制武器。第 $i$ 台武器能将第 $i$ 枚导弹在降落至地面后的威力值减少 $a_i$（至多减少到 $0$）。但是，由于技术限制，只能启动其中 $m$ 台反制武器。地面指挥官想知道，导弹造成的爆炸威力值总和最小为多少。

// ## 输入格式

// 从标准输入中读入数据。

// 输入一共包含 $n+2$ 行。

// 第 $1$ 行输入两个正整数 $n,m$。

// 第 $2$ 行到第 $n+1$ 行每行包含三个整数 $x_i,y_i,v_i$，表示第 $i$ 颗导弹的起点坐标和水平速度。 

// 第 $n+2$ 行包含 $n$ 个非负整数 $a_1,a_2,\cdots,a_n$，含义见题目描述。

// ## 输出格式

// 输出到标准输出。

// 输出一行一个非负整数，表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 0
// 1 1 -2
// 1 2 -1
// 1 3 1
// 1 1 1
// ```

// ### 样例输出 #1

// ```
// 0
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 4 1
// -3 3 0
// 1 3 1
// 4 3 -4
// -9 3 -7
// 1 3 2 3
// ```

// ### 样例输出 #2

// ```
// 1
// ```

// ## 样例 #3

// ### 样例输入 #3

// ```
// 见附件中的 missile3.in
// ```

// ### 样例输出 #3

// ```
// 见附件中的 missile3.ans
// ```

// ## 样例 #4

// ### 样例输入 #4

// ```
// 见附件中的 missile4.in
// ```

// ### 样例输出 #4

// ```
// 见附件中的 missile4.ans
// ```

// ## 提示

// **【样例解释】**

// - **样例 1 解释：** 

// 	每颗导弹的爆炸威力值都是 $0$。
// - **样例 2 解释：** 

// 	四枚导弹的爆炸威力值分别是 $0,1,1,0$，启动第 $2$ 或第 $3$ 台反制武器，最后爆炸威力值的和为 $1$。
    
// - **样例 4 说明：**

//    该样例满足测试点 $13\sim16$ 的限制。
// ***
// **【数据范围】**

// 对于 $100\%$ 的数据，$1\le n\le5\times10^5$，$0\le a_i,m\le n$，$0\le |x_i|,y_i\le10^9$，$0\le |v_i|\le10^6$。  

// **保证所有导弹起始坐标不相等。**

// |测试点编号|$n\le$|特殊性质|
// |:-:|:-:|:-:|
// |$1\sim6$|$5000$|无|
// |$7\sim10$|$12000$|无|
// |$11\sim12$|$10^5$|有|
// |$13\sim16$|$10^5$|无|
// |$17\sim20$|$5\times10^5$|无|

// 特殊性质：保证所有 $y_i$ 均相同。  

// **【提示】**

// 本题 I/O 量较大，推荐使用较快的 I/O 方式。

// 附平抛运动落点公式：  
// $$x_t=x_i+v_i\sqrt{\dfrac{2y_i}g}$$
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 5E5 + 5;

int x[maxN], y[maxN], v[maxN], tree[maxN], a[maxN], rk[maxN], tmp[maxN], f[maxN], k = 0;
double ed[maxN];

namespace BIT{
    #define lowbit(x) (x & -x)

    inline void init(int n){
        for(int i = 1; i <= n; i++) std::cin >> x[i] >> y[i] >> v[i];
        for(int i = 1; i <= n; i++) std::cin >> a[i];
        for(int i = 1; i <= n; i++) ed[i] = x[i] + v[i] * sqrt(y[i] / 4.9);
        std::iota(tmp, tmp + n + 1, 0);
        std::sort(tmp + 1, tmp + n + 1, [&](const int& p, const int& q){return ed[p] < ed[q];});
        double now = -DBL_MAX;
        for(int i = 1; i <= n; i++){
            if(now < ed[tmp[i]]) now = ed[tmp[i]], ++k;
            rk[tmp[i]] = k;
        }
        std::iota(tmp, tmp + n + 1, 0);
        std::stable_sort(tmp + 1, tmp + n + 1, [&](const int& q, const int& p){return y[q] ^ y[p]? y[q] < y[p]:x[q] < x[p];});
    }

    inline void updata(int p, int w){
        while(p <= k) tree[p] += w, p += lowbit(p);
    }

    inline int query(int p){
        int res = 0;
        while(p) res += tree[p], p -= lowbit(p);
        return res;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    BIT::init(n);
    int fast = 1, slow = 1;
    while(fast <= n){
        while(fast <= n && y[tmp[fast]] == y[tmp[slow]]) fast++;
        for(int i = slow; i < fast; i++){
            f[tmp[i]] += BIT::query(k + 1 - rk[tmp[i]]);
            BIT::updata(k + 1 - rk[tmp[i]], 1);
        }
        for(int i = slow; i < fast; i++) BIT::updata(k + 1 - rk[tmp[i]], -1);
        for(int i = fast - 1; i >= slow; i--){
            f[tmp[i]] += BIT::query(rk[tmp[i]]);
            BIT::updata(rk[tmp[i]], 1);
        }
        for(int i = fast - 1; i >= slow; i--) BIT::updata(rk[tmp[i]], -1);
        slow = fast;
    }
    long long res = 0;
    for(int i = 1; i <= n; i++) a[i] = std::min(a[i], f[i]), res += f[i];
    std::sort(a + 1, a + n + 1, std::greater<int>{});
    for(int i = 1; i <= m; i++) res -= a[i];
    std::cout << res;
    return 0;
}