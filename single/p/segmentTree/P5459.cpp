// # [BJOI2016] 回转寿司

// ## 题目描述

// 酷爱日料的小Z经常光顾学校东门外的回转寿司店。在这里，一盘盘寿司通过传送带依次呈现在小Z眼前。  

// 不同的寿司带给小Z的味觉感受是不一样的，我们定义小Z对每盘寿司都有一个满意度。  

// 例如小Z酷爱三文鱼，他对一盘三文鱼寿司的满意度为 $10$；小Z觉得金枪鱼没有什么味道，他对一盘金枪鱼寿司的满意度只有 $5$；小Z最近看了电影《美人鱼》，被里面的八爪鱼恶心到了，所以他对一盘八爪鱼刺身的满意度是 $-100$。   

// 特别地，小Z是个著名的吃货，他吃回转寿司有一个习惯，我们称之为“狂吃不止”。具体地讲，当他吃掉传送带上的一盘寿司后，他会毫不犹豫地吃掉它后面的寿司，直到他不想再吃寿司了为止。  

// 今天，小Z再次来到了这家回转寿司店，$N$ 盘寿司将依次经过他的面前。其中，小Z对第 $i$ 盘寿司的满意度为$a_i$。  

// 小Z可以选择从哪盘寿司开始吃，也可以选择吃到哪盘寿司为止。他想知道共有多少种不同的选择，使得他的满意度之和不低于 $L$，且不高于 $R$。

// 注意，虽然这是回转寿司，但是我们不认为这是一个环上的问题，而是一条线上的问题。即，小Z能吃到的是输入序列的一个连续子序列；最后一盘转走之后，第一盘并不会再出现一次。

// ## 输入格式

// 第一行三个正整数 $N,L,R$，表示寿司盘数，满意度的下限和上限。  
// 第二行包含 $N$ 个整数 $a_i$，表示小Z对寿司的满意度。

// ## 输出格式

// 一行一个整数，表示有多少种方案可以使得小Z的满意度之和不低于 $L$ 且不高于 $R$。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 5 9
// 1 2 3 4 5
// ```

// ### 样例输出 #1

// ```
// 6
// ```

// ## 提示

// 【数据范围】  

// $1\le N \le 10^5$  
// $|a_i| \le 10^5$   
// $0\le L,R \le 10^9$
#include <iostream>
#include <bits/stdc++.h>
#define ll long long
#define lowbit(x) (x & -x)

const int maxN = 1E5 + 5, inf = 0X3f3f3f3f;
int w[maxN], rk[maxN * 3], cnt[maxN * 3], k;
ll sums[maxN * 3];

inline void init(int n, int l, int r){
    for(int i = 1; i <= n; i++) sums[i] = sums[i - 1] + w[i], sums[i + n] = sums[i] - l, sums[i + n * 2] = sums[i] - r;
    std::iota(s, s + 3 * n + 1, 0);
    std::sort(s + 1, s + 3 * n + 1, [&](const int& a, const int& b){return sums[a] < sums[b];});
    ll pre = INT64_MIN;
    for(int i = 1; i <= 3 * n; i++){
        if(pre < sums[s[i]]) pre = sums[s[i]], ++k;
        rk[s[i]] = k;
    }
}

inline void updata(int x){
    while(x <= k) cnt[x]++, x += lowbit(x);
}

inline int query(int x){
    int res = 0;
    while(x) res += cnt[x], x -= lowbit(x);
    return res;
}

inline int query(int l, int r){
    return query(r) - query(l - 1);
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, l, r;
    ll res = 0;
    std::cin >> n >> l >> r;
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    init(n, l, r);
    for(int i = 1; i <= n; i++){
        res += query(rk[i + 2 * n], rk[i + n]) + (sums[i] >= l && sums[i] <= r);
        updata(rk[i]);
    }
    std::cout << res;
    return 0;
}