// # [NOI2022] 众数

// ## 题目描述

// **对于一个序列，定义其众数为序列中出现次数严格大于一半的数字。注意该定义与一般的定义有出入，在本题中请以题面中给出的定义为准。**

// 一开始给定 $n$ 个长度不一的正整数序列，编号为 $1 \sim n$，初始序列可以为空。这 $n$ 个序列被视为存在，其他编号对应的序列视为不存在。

// 有 $q$ 次操作，操作有以下类型:

// - $1 \ x \ y$：在 $x$ 号序列末尾插入数字 $y$。保证 $x$ 号序列存在，且 $1 \le x, y \le n + q$。
// - $2 \ x$：删除 $x$ 号序列末尾的数字，保证 $x$ 号序列存在、非空，且 $1 \le x \le n + q$。
// - $3 \ m \ x_1 \ x_2 \ x_m$：将 $x_1, x_2, \ldots, x_m$ 号序列顺次拼接，得到一个新序列，并询问其众数。如果不存在满足上述条件的数，则返回 $-1$。数据保证对于任意 $1 \le i \le m$，$x_i$ 是一个仍然存在的序列，$1 \le x_i \le n + q$，且拼接得到的序列非空。**注意：不保证 $\boldsymbol{x_1, \ldots, x_m}$ 互不相同，询问中的合并操作不会对后续操作产生影响。**
// - $4 \ x_1 \ x_2 \ x_3$：新建一个编号为 $x_3$ 的序列，其为 $x_1$ 号序列后顺次添加 $x_2$ 号序列中数字得到的结果，然后删除 $x_1, x_2$ 对应的序列。此时序列 $x_3$ 视为存在，而序列 $x_1, x_2$ 被视为不存在，在后续操作中也不会被再次使用。保证 $1 \le x_1, x_2, x_3 \le n + q$、$x_1 \ne x_2$、序列 $x_1, x_2$ 在操作前存在、且在操作前没有序列使用过编号 $x_3$。

// ## 输入格式

// 输入的第一行包含两个正整数 $n$ 和 $q$，分别表示数列的个数和操作的次数，保证 $n \le 5 \times {10}^5$、$q \le 5 \times {10}^5$。

// 接下来 $n$ 行，第 $i$ 行表示编号为 $i$ 的数列。每一行的第一个非负整数 $l_i$ 表示初始第 $i$ 号序列的数字个数，接下来有 $l_i$ 个非负整数 $a_{i,j}$ 按顺序表示数列中的数字。假定 $C_l = \sum l_i$ 代表输入序列长度之和，则保证 $C_l \le 5 \times {10}^5$、$a_{i,j} \le n + q$。

// 接下来 $q$ 行，每行若干个正整数，表示一个操作，并按照题面描述中的格式输入。

// 假定 $C_m = \sum m$ 代表所有操作 $3$ 需要拼接的序列个数之和，则保证 $C_m \le 5 \times {10}^5$。

// ## 输出格式

// 对于每次询问，一行输出一个整数表示对应的答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 2 8
// 3 1 1 2
// 3 3 3 3
// 3 1 1
// 3 1 2
// 4 2 1 3
// 3 1 3
// 2 3
// 3 1 3
// 1 3 1
// 3 1 3
// ```

// ### 样例输出 #1

// ```
// 1
// 3
// -1
// 3
// -1
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 4 9
// 1 1
// 1 2
// 1 3
// 1 4
// 3 4 1 2 3 4
// 1 1 2
// 3 2 1 2
// 2 3
// 3 3 1 2 3
// 1 4 4
// 1 4 4
// 1 4 4
// 3 4 1 2 3 4
// ```

// ### 样例输出 #2

// ```
// -1
// 2
// 2
// 4
// ```

// ## 提示

// **【样例解释 \#1】**

// 第一次询问查询序列 $1$ 的众数。由于序列包含两个 $1$，超过序列长度的一半，因此众数为 $1$。

// 第二次询问查询序列 $2$ 的众数。由于序列只包含 $3$，因此众数为 $3$。

// 第三次询问询问序列 $3$ 的众数。此时序列 $3$ 为 $(3, 3, 3, 1, 1, 2)$，不存在出现次数大于 $3$ 次的数，因此输出为 $-1$。

// ----

// **【样例解释 \#2】**

// 第一次询问查询序列 $1, 2, 3, 4$ 拼接后得到的序列的众数。拼接的结果为 $(1, 2, 3, 4)$，不存在出现次数大于两次的数，因此输出为 $-1$。

// 第四次询问查询序列 $1, 2, 3, 4$ 拼接后得到的序列的众数。拼接的结果为 $(1, 2, 2, 4, 4, 4, 4)$，众数为 $4$。

// ----

// **【样例 \#3】**

// 见附件中的 `major/major3.in` 与 `major/major3.ans`。

// 该样例满足测试点 $1 \sim 3$ 的限制。

// ----

// **【样例 \#4】**

// 见附件中的 `major/major4.in` 与 `major/major4.ans`。

// 该样例满足测试点 $11 \sim 12$ 的限制。

// ----

// **【数据范围】**

// 对于所有测试数据，保证 $1 \le n, q, C_m, C_l \le 5 \times {10}^5$。

// | $n, q$ | $C_m, C_l$ | 测试点编号 | 特殊性质 A | 特殊性质 B | 特殊性质 C |
// |:-:|:-:|:-:|:-:|:-:|:-:|
// | $\le 300$ | $\le 300$ | $1 \sim 3$ | 否 | 否 | 是 |
// | $\le 4000$ | $\le 4000$ | $4 \sim 7$ | 否 | 否 | 是 |
// | $\le {10}^5$ | $\le {10}^5$ | $8$ | 是 | 是 | 是 |
// | $\le {10}^5$ | $\le {10}^5$ | $9$ | 是 | 否 | 否 |
// | $\le {10}^5$ | $\le {10}^5$ | $10$ | 否 | 是 | 否 |
// | $\le {10}^5$ | $\le {10}^5$ | $11 \sim 12$ | 否 | 否 | 是 |
// | $\le {10}^5$ | $\le {10}^5$ | $13$ | 否 | 否 | 否 |
// | $\le 5 \times {10}^5$ | $\le 5 \times {10}^5$ | $14$ | 是 | 是 | 是 |
// | $\le 5 \times {10}^5$ | $\le 5 \times {10}^5$ | $15$ | 是 | 否 | 否 |
// | $\le 5 \times {10}^5$ | $\le 5 \times {10}^5$ | $16$ | 否 | 是 | 否 |
// | $\le 5 \times {10}^5$ | $\le 5 \times {10}^5$ | $17 \sim 18$ | 否 | 否 | 是 |
// | $\le 5 \times {10}^5$ | $\le 5 \times {10}^5$ | $19 \sim 20$ | 否 | 否 | 否 |

// 特殊性质 A：保证 $n = 1$ 且没有操作 $4$。  
// 特殊性质 B：保证任意时刻任何序列中只有数字 $1$ 和 $2$。  
// 特殊性质 C：保证没有操作 $2$。
// 线段树合并, 然而treap根本写不了.
#include <bits/stdc++.h>
#define ls(x) tree[x].l
#define rs(x) tree[x].r
#define mx(x) tree[x].mx
#define f(x) tree[x].f
const int maxN = 5e5 + 5;

int head[maxN << 1];
int sz[maxN << 1], tot = 0, k;
int tmp[maxN];

struct Node
{
    int val;
    Node *pre, *next;
    Node(int val, Node* pre = nullptr, Node* next = nullptr): val(val), pre(pre), next(next){}
}*st[maxN << 1], *ed[maxN << 1];

struct TreeNode
{
    int l, r;
    int mx, f;
}tree[maxN << 7];

inline void getNode(int& x)
{
    x = ++tot;
    ls(x) = rs(x) = f(x) = 0;
}

inline void pushUp(int x)
{
    if(f(rs(x)) > f(ls(x))) mx(x) = mx(rs(x)), f(x) = f(rs(x)) - f(ls(x));
    else mx(x) = mx(ls(x)), f(x) = f(ls(x)) - f(rs(x));
}

inline int find(int id, int v)
{
    std::function<int(int, int, int)> dfs = [&](int s, int t, int p)->int
    {
        if(!p) return 0;
        if(s == t) return f(p);
        int m = (t + s) >> 1;
        if(v <= m) return dfs(s, m, ls(p));
        else return dfs(m + 1, t, rs(p)); 
    };
    return dfs(0, k, head[id]);
}

inline void ins(int id, int v)
{
    std::function<void(int, int, int&)> dfs = [&](int s, int t, int& p)->void
    {
        if(!p) getNode(p);
        if(s == t)
        {
            mx(p) = s, ++f(p);
            return ;
        }
        int m = (t + s) >> 1;
        if(v <= m) dfs(s, m, ls(p));
        else dfs(m + 1, t, rs(p));
        pushUp(p);
    };
    dfs(0, k, head[id]);
    ++sz[id];
    if(st[id] != nullptr) ed[id]->next = new Node(v, ed[id]), ed[id] = ed[id]->next;
    else st[id] = ed[id] = new Node(v);
}

inline void del(int id)
{
    std::function<void(int, int, int, int)> dfs = [&](int v, int s, int t, int p)->void
    {
        if(s == t)
        {
            --f(p);
            return ;
        }
        int m = (t + s) >> 1;
        if(v <= m) dfs(v, s, m, ls(p));
        else dfs(v, m + 1, t, rs(p));
        pushUp(p);
    };
    dfs(ed[id]->val, 0, k, head[id]);
    --sz[id];
    if(st[id] == ed[id])
    {
        delete ed[id];
        st[id] = ed[id] = nullptr;
    }
    else
    {
        ed[id] = ed[id]->pre;
        delete ed[id]->next;
    }
}

inline void merger(int id1, int id2, int id3)
{
    std::function<int(int, int, int, int)>dfs = [&](int s, int t, int x, int y)->int
    {
        if(!x || !y) return x | y;
        if(s == t)
        {
            f(x) += f(y);
            return x;
        }
        int m = (t + s) >> 1;
        ls(x) = dfs(s, m, ls(x), ls(y));
        rs(x) = dfs(m + 1, t, rs(x), rs(y));
        pushUp(x);
        return x;
    };

    head[id3] = dfs(0, k, head[id1], head[id2]);
    if(st[id1] != nullptr && st[id2] != nullptr)
    {
        st[id2]->pre = ed[id1];
        ed[id1]->next = st[id2];
        st[id3] = st[id1];
        ed[id3] = ed[id2];
    }
    else if(st[id1] != nullptr) st[id3] = st[id1], ed[id3] = ed[id1]; 
    else if(st[id2] != nullptr) st[id3] = st[id2], ed[id3] = ed[id2];
    sz[id3] = sz[id1] + sz[id2];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, q, m, v;
    std::cin >> n >> q;
    k = q + n;
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> m;
        for(int j = 0; j < m; ++j) std::cin >> v, ins(i, v);
    }
    int t, x, y, z;
    for(int i = 0; i < q; ++i)
    {
        std::cin >> t;
        if(t == 1) std::cin >> x >> y, ins(x, y);
        else if(t == 2) std::cin >> x, del(x);
        else if(t == 3)
        {
            long long totSz = 0, f = 0;
            std::cin >> m;
            v = 0;
            for(int j = 0; j < m; ++j)
            {
                std::cin >> tmp[j];
                totSz += sz[tmp[j]];
                if(mx(head[tmp[j]]) == v) f += f(head[tmp[j]]);
                else if(f(head[tmp[j]]) > f) v = mx(head[tmp[j]]), f = f(head[tmp[j]]) - f;
                else f -= f(head[tmp[j]]);
            }
            long long totCnt = 0;
            for(int j = 0; j < m; ++j) totCnt += find(tmp[j], v);
            if((totCnt << 1) > totSz) std::cout << v << '\n';
            else std::cout << "-1\n";
        }
        else if(t == 4)
        {
            std::cin >> x >> y >> z;
            merger(x, y, z);
        }
    }
    return 0;
}