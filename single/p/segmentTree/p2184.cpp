// # 贪婪大陆

// ## 题目背景

// 面对蚂蚁们的疯狂进攻，小 FF 的 Tower defence 宣告失败……人类被蚂蚁们逼到了 Greed Island 上的一个海湾。现在，小 FF 的后方是一望无际的大海，前方是变异了的超级蚂蚁。小 FF 还有大好前程，他可不想命丧于此， 于是他派遣手下最后一批改造 SCV 布置地雷以阻挡蚂蚁们的进攻。

// ## 题目描述

// 小 FF 最后一道防线是一条长度为 $n$ 的战壕，小 FF 拥有无数多种地雷，而 SCV 每次可以在 $[L, R]$ 区间埋放同一种不同于之前已经埋放的地雷。由于情况已经十万火急，小 FF 在某些时候可能会询问你在 $[L',R']$ 区间内有多少种不同的地雷，他希望你能尽快的给予答复。

// ## 输入格式

// 第一行为两个整数 $n$ 和 $m$，$n$ 表示防线长度，$m$ 表示 SCV 布雷次数及小 FF 询问的次数总和。

// 接下来有 $m$ 行，每行三个整数 $q,l,r$：

// - 若 $q=1$，则表示 SCV 在 $[l, r]$ 这段区间布上一种地雷；
// - 若 $q=2$，则表示小 FF 询问当前 $[l, r]$ 区间总共有多少种地雷。

// ## 输出格式

// 对于小 FF 的每次询问，输出一个答案（单独一行），表示当前区间地雷总数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 4
// 1 1 3
// 2 2 5
// 1 2 4
// 2 3 5
// ```

// ### 样例输出 #1

// ```
// 1
// 2
// ```

// ## 提示

// ### 数据规模与约定

// - 对于 $30\%$ 的数据，$0 \le n$，$m \le 1000$。
// - 对于 $100\%$ 的数据，$0 \le n$，$m \le 10^5$。
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

const int maxN = 1E5 + 5;
ll cnt1[maxN << 2], cnt2[maxN << 2], lz1[maxN << 2], lz2[maxN << 2];

inline void pushUp(int p, ll* cnt){
    cnt[p] = cnt[p << 1] + cnt[p << 1 | 1];
}

inline void pushDown(int s, int t, int m, int p){
    if(lz1[p]){
        lz1[p << 1] += lz1[p], lz1[p << 1 | 1] += lz1[p];
        cnt1[p << 1] += (m - s + 1) * lz1[p];
        cnt1[p << 1 | 1] += (t - m) * lz1[p];
        lz1[p] = 0;
    }
    if(lz2[p]){
        lz2[p << 1] += lz2[p], lz2[p << 1 | 1] += lz2[p];
        cnt2[p << 1] += (m - s + 1) * lz2[p];
        cnt2[p << 1 | 1] += (t - m) * lz2[p];
        lz2[p] = 0;
    }
}

inline void updata(int l, int r, int s, int t, int p, ll* cnt, ll* lz){
    if(l <= s && r >= t){
        cnt[p] += t - s + 1;
        lz[p]++;
        return ;
    }
    int m = (t + s) >> 1;
    pushDown(s, t, m, p);
    if(l <= m) updata(l, r, s, m, p << 1, cnt, lz);
    if(r > m) updata(l, r, m + 1, t, p << 1 | 1, cnt, lz);
    pushUp(p, cnt); 
}

inline ll query(int l, int r, int s, int t, int p, ll* cnt){
    if(l > r) return 0;
    if(l <= s && r >= t) return cnt[p];
    int m = (t + s) >> 1;
    pushDown(s, t, m, p);
    ll res = 0;
    if(l <= m) res += query(l, r, s, m, p << 1, cnt);
    if(r > m) res += query(l, r, m + 1, t, p << 1 | 1, cnt);
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, l, r, op;
    std::cin >> n >> m;
    for(int i = 0; i < m; i++){
        std::cin >> op >> l >> r;
        if(op == 1){
            updata(l, r, 1, n, 1, cnt1, lz1);
            updata(l, r - 1, 1, n, 1, cnt2, lz2);
        }
        else{
            std::cout << query(l, r, 1, n, 1, cnt1) - query(l, r - 1, 1, n, 1, cnt2) << std::endl;
        }
    }
    return 0;
}