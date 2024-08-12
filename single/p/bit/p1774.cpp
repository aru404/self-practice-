// # 最接近神的人

// ## 题目描述

// 破解了符文之语，小 FF 开启了通往地下的道路。当他走到最底层时，发现正前方有一扇巨石门，门上雕刻着一幅古代人进行某种活动的图案。而石门上方用古代文写着“神的殿堂”。小 FF 猜想里面应该就有王室的遗产了。但现在的问题是如何打开这扇门……。

// 仔细研究后，他发现门上的图案大概是说：古代人认为只有智者才是最容易接近神明的。而最聪明的人往往通过一种仪式选拔出来。仪式大概是指，即将隐退的智者为他的候选人写下一串无序的数字，并让他们进行一种操作，即交换序列中相邻的两个元素。而用最少的交换次数使原序列变成不下降序列的人即是下一任智者。

// 小 FF 发现门上同样有着 $n$ 个数字。于是他认为打开这扇门的秘诀就是找到让这个序列变成不下降序列所需要的最小次数。但小 FF 不会……只好又找到了你，并答应事成之后与你三七分……

// ## 输入格式

// 第一行为一个整数 $n$，表示序列长度。

// 第二行为 $n$ 个整数，表示序列中每个元素。

// ## 输出格式

// 一个整数 $\mathit{ans}$，即最少操作次数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4
// 2 8 0 3
// ```

// ### 样例输出 #1

// ```
// 3
// ```

// ## 提示

// ### 数据范围及约定

// - 对于 $30\%$ 的数据 $1≤n≤10^4$。
// - 对于 $100\%$ 的数据 $1≤n≤5\times 10^5$，$A_i\in [-2^{31}, 2^{31})$。

// ### 样例解释

// 开始序列为 $[2,8,0,3]$，目标序列为 $[0, 2, 3, 8]$，可进行三次操作的目标序列：

// 1. 交换 $(8,0)$，序列变成 $[2,0,8,3]$；
// 2. 交换 $(2,0)$，序列变成 $[0,2,8,3]$；
// 3. 交换 $(8,3)$，序列变成 $[0,2,3,8]$。
#include <iostream>
#include <bits/stdc++.h>

namespace BIT{
    #define lowbit(x) (x & -x)
    const int maxN = 5E5 + 5;
    int w[maxN], rk[maxN], tmp[maxN], tree[maxN], k = 0;

    inline void updata(int x){
        while(x <= k) ++tree[x], x += lowbit(x);
    }

    inline int query(int x){
        int res = 0;
        while(x) res += tree[x], x -= lowbit(x);
        return res;
    }

    inline long long solve(int n){
        for(int i = 1; i <= n; i++) std::cin >> w[i];
        std::iota(tmp, tmp + n + 1, 0);
        std::sort(tmp + 1, tmp + n + 1, [&](const int& a, const int& b){return w[a] < w[b];});
        long long now = INT64_MIN;
        for(int i = 1; i <= n; i++){
            if(w[tmp[i]] > now) now = w[tmp[i]], ++k;
            rk[tmp[i]] = k;
        }

        long long res = 0;
        for(int i = n; i; i--){
            res += query(rk[i] - 1);
            updata(rk[i]);
        }
        return res;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::cout << BIT::solve(n);
    return 0;
}