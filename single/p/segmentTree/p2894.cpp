// # [USACO08FEB] Hotel G

// ## 题目描述

// The cows are journeying north to Thunder Bay in Canada to gain cultural enrichment and enjoy a vacation on the sunny shores of Lake Superior. Bessie, ever the competent travel agent, has named the Bullmoose Hotel on famed Cumberland Street as their vacation residence. This immense hotel has N (1 ≤ N ≤ 50,000) rooms all located on the same side of an extremely long hallway (all the better to see the lake, of course).

// The cows and other visitors arrive in groups of size Di (1 ≤ Di ≤ N) and approach the front desk to check in. Each group i requests a set of Di contiguous rooms from Canmuu, the moose staffing the counter. He assigns them some set of consecutive room numbers r..r+Di-1 if they are available or, if no contiguous set of rooms is available, politely suggests alternate lodging. Canmuu always chooses the value of r to be the smallest possible.

// Visitors also depart the hotel from groups of contiguous rooms. Checkout i has the parameters Xi and Di which specify the vacating of rooms Xi ..Xi +Di-1 (1 ≤ Xi ≤ N-Di+1). Some (or all) of those rooms might be empty before the checkout.

// Your job is to assist Canmuu by processing M (1 ≤ M < 50,000) checkin/checkout requests. The hotel is initially unoccupied.

// 第一行输入 $n,m$，$n$ 代表有 $n$ 个房间 $(1\leq n \leq 50,000)$，编号为 $1 \sim n$，开始都为空房，$m$ 表示以下有 $m$ 行操作 $(1\leq m < 50,000)$，以下每行先输入一个数 $i$ ，表示一种操作：

// 若 $i$ 为 $1$，表示查询房间，再输入一个数 $x$，表示在 $1,2,...,n$ 房间中找到长度为 $x$ 的连续空房，输出连续 $x$ 个房间中左端的房间号，尽量让这个房间号最小，若找不到长度为 $x$ 的连续空房，输出 $0$。若找得到，在这 $x$ 个空房间中住上人。

// 若 $i$ 为 $2$，表示退房，再输入两个数 $x,y$ 代表房间号 $x \sim x+y-1$ 退房，即让房间为空。

// 你需要对每个输入 $1$ 输出对应的答案。

// ## 输入格式

// \* Line 1: Two space-separated integers: N and M

// \* Lines 2..M+1: Line i+1 contains request expressed as one of two possible formats: (a) Two space separated integers representing a check-in request: 1 and Di (b) Three space-separated integers representing a check-out: 2, Xi, and Di

// ## 输出格式

// \* Lines 1.....: For each check-in request, output a single line with a single integer r, the first room in the contiguous sequence of rooms to be occupied. If the request cannot be satisfied, output 0.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 10 6
// 1 3
// 1 3
// 1 3
// 1 3
// 2 5 5
// 1 6
// ```

// ### 样例输出 #1

// ```
// 1
// 4
// 7
// 0
// 5
// ```
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 5E4 + 5, inf = 0X3f3f3f3f;
int mx[maxN << 2], lMx[maxN << 2], rMx[maxN << 2], idx[maxN << 2], cnt[maxN << 2], lz[maxN << 2];

inline void pushUp(int p, int s, int t, int m){
    mx[p] = std::max({mx[p << 1], mx[p << 1 | 1], rMx[p << 1] + lMx[p << 1 | 1]});
    if(mx[p] == mx[p << 1]) idx[p] = idx[p << 1];
    else if(mx[p] == rMx[p << 1] + lMx[p << 1 | 1]) idx[p] = m - rMx[p << 1] + 1;
    else idx[p] = idx[p << 1 | 1];
    cnt[p] = cnt[p << 1] + cnt[p << 1 | 1];
    lMx[p] = !cnt[p << 1]? lMx[p << 1] + lMx[p << 1 | 1]:lMx[p << 1];
    rMx[p] = !cnt[p << 1 | 1]? rMx[p << 1 | 1] + rMx[p << 1]:rMx[p << 1 | 1];
}

inline void pushDown(int p, int l, int r, int m){
    if(lz[p]){
        lz[p << 1] = lz[p << 1 | 1] = lz[p];
        if(lz[p] == 1){
            cnt[p << 1] = m - l + 1;
            cnt[p << 1 | 1] = r - m;
            mx[p << 1] = lMx[p << 1] = rMx[p << 1] = 0;
            mx[p << 1 | 1] = lMx[p << 1 | 1] = rMx[p << 1 | 1] = 0;
            idx[p << 1] = idx[p << 1 | 1] = inf;
        }
        else{
            cnt[p << 1] = cnt[p << 1 | 1] = 0;
            mx[p << 1] = lMx[p << 1] = rMx[p << 1] = m - l + 1;
            mx[p << 1 | 1] = lMx[p << 1 | 1] = rMx[p << 1 | 1] = r - m;
            idx[p << 1] = l, idx[p << 1 | 1] = m + 1;
        }
        lz[p] = 0;
    }
}

inline void buildTree(int s, int t, int p){
    if(s == t){
        idx[p] = s, lMx[p] = rMx[p] = mx[p] = 1;
        return ;
    }
    int m = (t + s) >> 1;
    buildTree(s, m, p << 1);
    buildTree(m + 1, t, p << 1 | 1);
    pushUp(p, s, t, m);
}

inline void updata(int l, int r, bool f, int s, int t, int p){
    if(l <= s && r >= t){
        if(f){
            cnt[p] = t - s + 1, lMx[p] = rMx[p] = mx[p] = 0;
            idx[p] = inf, lz[p] = 1;
        }
        else{
            cnt[p] = 0, lMx[p] = rMx[p] = mx[p] = t - s + 1;
            idx[p] = s, lz[p] = -1;
        }
        return ;
    }
    int m = (t + s) >> 1;
    pushDown(p, s, t, m);
    if(l <= m) updata(l, r, f, s, m, p << 1);
    if(r > m) updata(l, r, f, m + 1, t, p << 1 | 1);
    pushUp(p, s, t, m);
}

inline int query(int s, int t, int len, int p){
    if(mx[p] < len) return inf;
    if(!cnt[p]) return s;
    int m = (t + s) >> 1;
    pushDown(p, s, t, m);
    if(mx[p << 1] >= len) return query(s, m, len, p << 1);
    if(len <= rMx[p << 1] + lMx[p << 1 | 1]) return m + 1 - rMx[p << 1];
    return query(m + 1, t, len, p << 1 | 1);
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, op, x, y;
    std::cin >> n >> m;
    buildTree(1, n, 1);
    for(int i = 1; i <= m; i++){
        std::cin >> op >> x;
        if(op == 1){
            int s = query(1, n, x, 1);
            if(s == inf) std::cout << "0\n";
            else{
                std::cout << s << '\n';
                updata(s, s + x - 1, 1, 1, n, 1);
            }
        }
        else{
            std::cin >> y;
            updata(x, x + y - 1, 0, 1, n, 1);
        }
    }
    return 0;
}