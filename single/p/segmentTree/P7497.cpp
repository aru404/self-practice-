// # 四方喝彩

// ## 题目背景

// >念出他们的名字，让他们，再次回到舞台。

// 麦克要在月亮河马戏团表演全新的杂技节目了！

// ## 题目描述

// 麦克一共有 $n$ 个新节目，每个节目的惊险值为 $a_i$。

// 接下来麦克可以通过若干次操作来对每个节目的惊险值进行变换：

// + 麦克使用冰球，对于所有的 $l\leq i\leq r$，第 $i$ 个节目的惊险值会增加 $x$。

// + 麦克使用土球，对于所有的 $l\leq i\leq r$，第 $i$ 个节目的惊险值会乘以 $x$。

// + 麦克使用火球，对于所有的 $l\leq i\leq r$，第 $i$ 个节目的惊险值在接下来的 $x$ 个操作中**不会受到冰球和土球的影响**。火球效果**不会被替换**。

// 当然观众对每个节目的惊险值也很好奇，所以你需要在操作过程中帮麦克回答对于所有 $l\leq i\leq r$，第 $i$ 个节目的惊险值之和。当然观众不希望惊险值过大，所以你需要将结果对 $10^9+7$ 取模。

// ------------
// #### 简要题意：

// 给你一个长度为 $n$ 的数组 $a$，你需要支持如下几个操作：

// 1. `l r x`：对所有 $l\leq i\leq r$，令 $a_i$ 增加 $x$。
// 2. `l r x`：对所有 $l\leq i\leq r$，令 $a_i$ 乘上 $x$。
// 3. `l r x`：对所有 $l\leq i\leq r$，在接下来的 $x$ 个操作内，$a_i$ 将会被封锁，**不会受到操作 1 和操作 2 的影响**（设本次操作为第 $k$ 次操作，则第 $k+1,k+2,\cdots,k+x$ 次操作中的所有操作 1和操作 2 不会对区间 $\left[l,r\right]$ 产生影响）。已有的封锁效果**不会被替换**（即假设第 $3$ 次有一个操作 3 对某个位置进行封锁，封锁时间为 $5$，第 $5$ 次操作同样对这个位置进行封锁，封锁时间为 $2$ 那么实际上这个位置在第 $4$ 次操作到第 $8$ 次操作的时间内都会被封锁）（感性理解就是后面时间短的封锁不会使前面时间长的封锁失效）。
// 4. `l r`：询问 $\sum\limits_{l\leq i\leq r}a_i$，对 $10^9+7$ 取模。

// ## 输入格式

// 第一行有两个正整数 $n,m$，分别表示数组长度和操作数。

// 第二行会有 $n$ 个整数 $a_i$，表示数组 $a$。

// 接下来 $m$ 行，每行有三个整数 $opt,l,r$ 表示操作编号以及这次操作的 $l,r$，如果 $opt\leq 3$，那么还会有一个整数 $x$，表示这次操作的 $x$。

// ## 输出格式

// 对于所有的操作 4，一行一个整数表示结果，对 $10^9+7$ 取模。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 5
// 1 5 4 3 6
// 1 2 4 3
// 3 1 2 2
// 4 2 5
// 2 2 3 4
// 4 1 3
// ```

// ### 样例输出 #1

// ```
// 27
// 37
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 10 12
// 4 2 1 5 10 3 2 4 6 7
// 2 3 7 4
// 1 2 9 5
// 3 2 4 5
// 3 4 7 2
// 4 3 9
// 1 1 8 2
// 2 4 5 2
// 3 6 8 2
// 4 2 3
// 1 2 10 6
// 2 7 9 3
// 4 1 10
// ```

// ### 样例输出 #2

// ```
// 129
// 16
// 314
// ```

// ## 提示

// #### 样例一解释
// 一开始数组为 $\{1,5,4,3,6\}$。

// + 执行第 $1$ 次操作，此时数组变为 $\{1,8,7,6,6\}$。
// + 执行第 $2$ 次操作，此时数组不变。
// + 执行第 $3$ 次操作，询问结果为 $27$。
// + 执行第 $4$ 次操作，因为此时 $a_2$ 在第 $2$ 次操作中被封锁还未解除，所以这次操作只对 $a_3$ 产生影响，数组变为 $\{1,8,28,6,6\}$。
// + 执行第 $5$ 次操作，询问结果为 $37$。

// ------------
// #### 数据范围

// **本题采用捆绑测试**。

// + Subtask 1 ( $25\%$ )：$n,m\leq2\times10^3$。
// + Subtask 2 ( $8\%$ )：没有操作 3。
// + Subtask 3 ( $17\%$ )：对于所有操作 4，保证 $l=r$。
// + Subtask 4 ( $50\%$ )：无特殊限制。

// 对于所有数据，$1\leq n,m\leq 2\times 10^5,0\leq a_i<10^9+7,1\leq l\leq r\leq n$，对于所有操作 1 和操作 2，保证 $0\leq x<10^9+7$，对于所有操作 3，设其为第 $k$ 次操作，保证 $0\leq x\leq m-k$。a
#include <bits/stdc++.h>

struct node
{
    int sum1, sum2, len, cnt;
    int add, mult, loc;
};

struct unlock
{
    int l, r, t;
    bool operator<(const unlock& other) const
    {
        return t > other.t;
    }
};
const int maxN = 2E5 + 5;
int arr[maxN];

class SegmentTree
{
    #define sum1(x) tree[x].sum1
    #define sum2(x) tree[x].sum2
    #define len(x) tree[x].len
    #define cnt(x) tree[x].cnt
    #define lz1(x) tree[x].add
    #define lz2(x) tree[x].mult
public:
    inline void updataAdd(int l, int r, int v)
    {
        std::function<void(int, int, int)> updata = [&](int s, int t, int p)->void
        {
            if(l <= s && r >= t)
            {
                add(v, p);
                return ;
            }
            int m = (t + s) >> 1;
            pushDown(p);
            if(l <= m) updata(s, m, p << 1);
            if(r > m) updata(m + 1, t, p << 1 | 1);
            pushUp(p);
        };
        updata(1, n, 1);
    }

    inline void updataMult(int l, int r, int v)
    {
        std::function<void(int, int, int)> updata = [&](int s, int t, int p)->void
        {
            if(l <= s && r >= t)
            {
                mult(v, p);
                return ;
            }
            int m = (t + s) >> 1;
            pushDown(p);
            if(l <= m) updata(s, m, p << 1);
            if(r > m) updata(m + 1, t, p << 1 | 1);
            pushUp(p);
        };
        updata(1, n, 1);
    }

    inline void updataLock(int l, int r, int v)
    {
        std::function<void(int, int, int)> updata = [&](int s, int t, int p)->void
        {
            if(l <= s && r >= t)
            {
                lock(v, s, t, p);
                return ;
            }
            int m = (t + s) >> 1;
            pushDown(p);
            if(l <= m) updata(s, m, p << 1);
            if(r > m) updata(m + 1, t, p << 1 | 1);
            pushUp(p);
        };
        updata(1, n, 1);
    }

    inline int query(int l, int r)
    {
        std::function<int(int, int, int)> q = [&](int s, int t, int p)->int
        {
            if(l <= s && r >= t) return (sum1(p) + sum2(p)) % mod;
            int m = (t + s) >> 1, res = 0;
            pushDown(p);
            if(l <= m) res = q(s, m, p << 1);
            if(r > m) res = (res + q(m + 1, t, p << 1 | 1)) % mod;
            return res;
        };
        return q(1, n, 1);
    }

    explicit SegmentTree(int* arr, int n):n(n)
    {
        tree = new node[(n + 5) << 2];
        buildTree(1, n, 1, arr);
    }

    ~SegmentTree()
    {
        delete[] tree;
    }
private:
    node* tree;

    static const int mod = 1E9 + 7;
    const int n;

    inline void pushUp(int p)
    {
        if(cnt(p)) return ;
        sum1(p) = (sum1(p << 1) + sum1(p << 1 | 1)) % mod;
        sum2(p) = (sum2(p << 1) + sum2(p << 1 | 1)) % mod;
        len(p) = len(p << 1) + len(p << 1 | 1);
    }

    inline void mult(int v, int p)
    {
        if(cnt(p)) return ;
        sum1(p) = 1ll * v * sum1(p) % mod;
        if(lz1(p)) lz1(p) = 1ll * v * lz1(p) % mod;
        lz2(p) = 1ll * v * lz2(p) % mod; 
    }

    inline void add(int v, int p)
    {
        if(cnt(p)) return ;
        sum1(p) = (1ll * v * len(p) + sum1(p)) % mod;
        lz1(p) = (lz1(p) + v) % mod;
    }

    inline void lock(int v, int s, int t, int p)
    {
        cnt(p) += v;
        if(!cnt(p))
        {
            if(s == t)
            {
                len(p) = 1;
                std::swap(sum1(p), sum2(p));
            }
            else pushUp(p);
        }
        else if(cnt(p) == v)
        {
            if(s != t) pushDown(p);
            len(p) = 0;
            sum2(p) = (sum1(p) + sum2(p)) % mod, sum1(p) = 0;
        }
    }

    inline void pushDown(int p)
    {
        if(lz2(p) != 1)
        {
            mult(lz2(p), p << 1);
            mult(lz2(p), p << 1 | 1);
            lz2(p) = 1;
        }
        if(lz1(p))
        {
            add(lz1(p), p << 1);
            add(lz1(p), p << 1 | 1);
            lz1(p) = 0;
        }
    }

    inline void buildTree(int s, int t, int p, int* arr)
    {
        lz1(p) = cnt(p) = 0;
        lz2(p) = 1;
        if(s == t)
        {
            sum1(p) = arr[s];
            sum2(p) = 0;
            len(p) = 1;
            return ;
        }
        int m = (t + s) >> 1;
        buildTree(s, m, p << 1, arr);
        buildTree(m + 1, t, p << 1 | 1, arr);
        pushUp(p);
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    SegmentTree tree(arr, n);
    std::priority_queue<unlock> pq;

    int l, r, x, t;
    for(int i = 1; i <= m; ++i)
    {
        std::cin >> t >> l >> r;
        if(t != 4) std::cin >> x;
        if(t == 1) tree.updataAdd(l, r, x);
        else if(t == 2) tree.updataMult(l, r, x);
        else if(t == 3 && x)
        {
            tree.updataLock(l, r, 1);
            pq.emplace(unlock{l, r, i + x});
        }
        else if(t == 4) std::cout << tree.query(l, r) << '\n';
        while(!pq.empty() && pq.top().t == i)
        {
            tree.updataLock(pq.top().l, pq.top().r, -1);
            pq.pop();
        }
    }
    return 0;
}