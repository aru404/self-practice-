// # 排序

// ## 题目描述

// 有 $n$ 个人依次站在小 A 面前。小 A 会依次对这 $n$ 个人进行 $m$ 次操作。

// 每次操作选择一个位置 $k$，将这 $n$ 个人中的所有身高小于等于当前 $k$ 位置的人的身高的人从队伍里拎出，然后按照身高从矮到高的顺序从左到右依次插入到 这些人原本的位置当中。

// 小 A 对这 $n$ 个人身高构成的序列的逆序对很感兴趣。现在小 A 想要知道每一次操作后这个序列的逆序对数。

// ----

// Update（2021-01-17）：$a$ 序列中的逆序对的定义是满足 $i < j$ 且 $a_i > a_j$ 的数对 $(i, j)$。

// ## 输入格式

// 第一行两个整数 $n$ 和 $m$，表示人数和操作数。

// 接下来一行 $n$ 个整数 $a_i$，表示初始状态从左到右每个人的身高。

// 接下来 $m$ 行每行一个数，表示这次操作的 $k$。

// ## 输出格式

// 输出共 $m + 1$ 行，第一行表示未操作时的逆序对数量。

// 除第一行外第 $i$ 行表示第 $i - 1$ 次操作后序列的逆序对数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 2
// 1 5 3 4 2
// 3
// 4
// ```

// ### 样例输出 #1

// ```
// 5
// 4
// 3
// ```

// ## 提示

// **【样例解释 #1】**

// 第一次操作后序列为 $1, 5, 2, 4, 3$。

// 第二次操作后序列为 $1, 5, 2, 3, 4$。

// **【数据范围】**

// 对于 $100 \%$ 的数据，$1 \le n,m \le 3 \times {10}^5$，$1 \le k \le n$，$1 \le a_i \le {10}^9$。
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

const int maxN = 3E5 + 5;

namespace BITs{
    #define lowbit(x) (x & -x)

    class BIT{
        private:
            int n;
            ll *tree;
        public:
            BIT(int);

            ~BIT();

            inline void updata(int, int);

            inline ll query(int);

            inline ll query(int, int);
    };

    BIT::BIT(int m){
        n = m;
        tree = new ll[n + 1]{};
    }

    BIT::~BIT(){
        delete[] tree;
    }

    inline void BIT::updata(int x, int v){
        while(x <= n) tree[x] += v, x += lowbit(x);
    }

    inline ll BIT::query(int x){
        ll res = 0;
        while(x) res += tree[x], x -= lowbit(x);
        return res;
    }

    inline ll BIT::query(int l, int r){
        l--; int res = 0;
        while(r > l) res += tree[r], r -= lowbit(r);
        while(l > r) res -= tree[l], l -= lowbit(l);
        return res;
    }
}

int w[maxN], rk[maxN], tmp[maxN], k;

inline void diff(int n){
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int& a, const int& b){return w[a] < w[b];});
    int now = 0;
    for(int i = 1; i <= n; i++){
        if(w[tmp[i]] > now) ++k, now = w[tmp[i]];
        rk[tmp[i]] = k;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, t, idx = 0;
    std::cin >> n >> m;
    diff(n);

    BITs::BIT tree1(n), tree2(k);
    for(int i = n; i; i--){
        tree2.updata(rk[i], tree1.query(rk[i] - 1));
        tree1.updata(rk[i], 1);
    }

    ll tot = tree2.query(k);
    std::cout << tot << '\n';
    for(int i = 0; i < m; i++){
        std::cin >> t;
        idx = std::max(idx, rk[t]);
        std::cout << tot - tree2.query(idx) << '\n';
    }
    return 0;
}