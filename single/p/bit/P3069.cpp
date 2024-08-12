// # [USACO13JAN] Cow Lineup G

// ## 题目描述

// Farmer John's N cows (1 <= N <= 100,000) are lined up in a row.  Each cow is identified by an integer "breed ID" in the range 0...1,000,000,000; the breed ID of the ith cow in the lineup is B(i).  Multiple cows can share the same breed ID.

// FJ thinks that his line of cows will look much more impressive if there is a large contiguous block of cows that all have the same breed ID.  In order to create such a block, FJ chooses up to K breed IDs and removes from his lineup all the cows having those IDs.  Please help FJ figure out the length of the largest consecutive block of cows with the same breed ID that he can create by doing this.

// 农夫约翰的N(1 <= N <= 100,000)只奶牛排成了一队，每只牛都用编上了一个“血统编号”，该编号为范围0...1,000,000,000的整数。血统相同的奶牛有相同的编号，也就是可能有多头奶牛是相同的"血统编号"。

// 约翰觉得如果连续排列的一段奶牛有相同的血统编号的话，奶牛们看起来会更具有威猛。为了创造这样的连续段，约翰最多能选出k种血统的奶牛，并把他们全部从队列中赶走。


// 请帮助约翰计算这样做能得到的由相同血统编号的牛构成的连续段的长度最大是多少？

// ## 输入格式

// \* Line 1: Two space-separated integers: N and K.

// \* Lines 2..1+N: Line i+1 contains the breed ID B(i).

// ## 输出格式

// \* Line 1: The largest size of a contiguous block of cows with

// identical breed IDs that FJ can create.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 9 1 
// 2 
// 7 
// 3 
// 7 
// 7 
// 3 
// 7 
// 5 
// 7
// ```

// ### 样例输出 #1

// ```
// 4
// ```

// ## 提示

// There are 9 cows in the lineup, with breed IDs 2, 7, 3, 7, 7, 3, 7, 5, 7. FJ would like to remove up to 1 breed ID from this lineup.


// By removing all cows with breed ID 3, the lineup reduces to 2, 7, 7, 7, 7, 5, 7.  In this new lineup, there is a contiguous block of 4 cows with the same breed ID (7).
// 区间数颜色
#include <iostream>
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

const int maxN = 1E5 + 5;
int w[maxN], tmp[maxN], rk[maxN], tree[maxN], cnt[maxN], n, k;
int pre[maxN];
bool vis[maxN];

inline void updata(int x, int v){
    while(x <= n) tree[x] += v, x += lowbit(x);
}

inline int query(int x){
    int ans = 0;
    while(x) ans += tree[x], x -= lowbit(x);
    return ans;
}

inline void init(){
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int a, const int b){return w[a] < w[b];});
    int now = -1; k = 0;
    for(int i = 1; i <= n; i++){
        if(w[tmp[i]] > now) now = w[tmp[i]], ++k;
        rk[tmp[i]] = k;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, res = 1, tot = 0, st = 1;
    std::cin >> n >> m;
    init();

    for(int i = 1; i <= n; i++){
        if(!vis[rk[i]]) ++tot, vis[rk[i]] = 1;
        updata(i, 1), ++cnt[rk[i]];
        if(pre[rk[i]]) updata(pre[rk[i]], -1);
        while(tot - query(st - 1) > m + 1) cnt[rk[st++]]--;
        res = std::max(res, cnt[rk[i]]);
        pre[rk[i]] = i;
    }
    std::cout << res;
    return 0;
}