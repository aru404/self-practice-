// # [Code+#1] Yazid 的新生舞会

// ## 题目背景

// 这道题是没有舞伴的 Yazid 用新生舞会的时间出的。

// ## 题目描述

// Yazid 有一个长度为 $n$ 的序列 $A$，下标从 $1$ 至 $n$。显然地，这个序列共有 $\frac{n\left( n+1\right)}{2}$ 个子区间。

// 对于任意一个子区间 $[l,r]$，如果该子区间内的众数在该子区间的出现次数严格大于 $\frac{r-l+1}{2}$（即该子区间长度的一半），那么 Yazid 就说这个子区间是“新生舞会的”。

// 所谓众数，即为该子区间内出现次数最多的数。特别地，如果出现次数最多的数有多个，我们规定值最小的数为众数。

// 现在，Yazid 想知道，共有多少个子区间是“新生舞会的”。

// ## 输入格式

// 第一行两个用空格隔开的非负整数 $n, type$，表示序列的长度和**数据类型**。数据类型的作用将在「子任务」中说明。

// 第二行 $n$ 个用空格隔开的非负整数，依次为 $A_1,A_2,...,A_n$，描述这个序列。

// ## 输出格式

// 输出一行一个整数，表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 0
// 1 1 2 2 3
// ```

// ### 样例输出 #1

// ```
// 10
// ```

// ## 提示

// **【样例解释 #1】**

// “新生舞会的”子区间有 $[1,1],[1,2],[1,3],[2,2],[2,4],[3,3],[3,4],[3,5],[4,4],[5,5]$ 共 $10$ 个。

//  ![](https://cdn.luogu.com.cn/upload/pic/12825.png) 

// 对于所有数据，保证 $0\leq A_i\leq n-1$。

// 对于 $type=0$ 的数据，没有任何特殊约定。

// 对于 $type=1$ 的数据，保证 $A_i\in \{ 0, 1 \}$。

// 对于 $type=2$ 的数据，保证序列 $A$ 的众数在整个序列中的出现次数不超过 $15$。

// 对于 $type=3$ 的数据，保证 $A_i\leq 7$。

// 来自 CodePlus 2017 11 月赛，清华大学计算机科学与技术系学生算法与竞赛协会 荣誉出品。

// Credit：idea/郑林楷 命题/王聿中 验题/郑林楷

// Git Repo：https://git.thusaac.org/publish/CodePlus201711

// 感谢腾讯公司对此次比赛的支持。
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

namespace BITs{
    #define lowbit(x) (x & -x)

    class BIT{
    private:
        ll *tree1, *tree2, *tree3;
        int n;
    public:
        BIT(int);

        ~BIT();
        
        inline void updata(int, int);

        inline void updata(int, int, int);

        inline ll query(int);

        inline ll query(int, int);
    };

    BIT::BIT(int m){
        n = m;
        tree1 = new ll[m + 1]{};
        tree2 = new ll[m + 1]{};
        tree3 = new ll[m + 1]{};
    }
    
    BIT::~BIT(){
        delete[] tree1;
        delete[] tree2;
        delete[] tree3;
    }

    inline void BIT::updata(int x, int v){
        if(x <= 0) return ;
        ll v3 = 1ll * x * x * v, v2 = 1ll * x * v;
        while(x <= n) tree1[x] += v, tree2[x] += v2, tree3[x] += v3, x += lowbit(x);
    }

    inline void BIT::updata(int l, int r, int v){
        updata(l, v), updata(r + 1, -v);
    }

    inline ll BIT::query(int x){
        if(x <= 0) return 0;
        ll s1 = 0, s2 = 0, s3 = 0; int y = x;
        while(x) s1 += tree1[x], s2 += tree2[x], s3 += tree3[x], x -= lowbit(x);
        return (s3 - (2 * y + 3) * s2 + (1ll * y * y + 3 * y + 2) * s1) >> 1;
    }      

    inline ll BIT::query(int l, int r){
        return query(r) - query(l - 1);
    }        
} // namespace BITs

const int maxN = 5E5 + 5;

int w[maxN], tmp[maxN], st[maxN], ed[maxN];

inline int diff(int n){
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int& a, const int& b){return w[a] ^ w[b]? w[a] < w[b]:a < b;});
    int now = -1, k = 0;
    for(int i = 1; i <= n; i++){
        if(now < w[tmp[i]]) ++k, st[k] = ed[k] = i, now = w[tmp[i]];
        else ed[k]++;
    }
    return k;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, type, k;
    std::cin >> n >> type;
    k = diff(n);

    ll res = 0;
    BITs::BIT tree(n << 1 | 1);

    for(int i = 1; i <= k; i++){
        int cnt = 0;
        tree.updata(n + 2 - tmp[st[i]], n + 1, 1);
        for(int j = st[i]; j < ed[i]; j++){
            ++cnt;
            int l = 2 * cnt + n + 2 - tmp[j + 1], r = 2 * cnt + n + 1 - tmp[j];
            res += tree.query(l - 1, r - 1);
            tree.updata(l, r, 1);
        }
        cnt++, res += tree.query(2 * cnt, 2 * cnt + n - tmp[ed[i]]);
        cnt = 0;
        tree.updata(n + 2 - tmp[st[i]], n + 1, -1);
        for(int j = st[i]; j < ed[i]; j++){
            ++cnt;
            int l = 2 * cnt + n + 2 - tmp[j + 1], r = 2 * cnt + n + 1 - tmp[j];
            tree.updata(l, r, -1);
        }
    }
    std::cout << res;
    return 0;
}