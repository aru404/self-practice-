// # 总统选举

// ## 题目背景

// 黑恶势力的反攻计划被小 C 成功摧毁，黑恶势力只好投降。秋之国的人民解放了，举国欢庆。此时，原秋之国总统因没能守护好国土，申请辞职，并请秋之国人民的大救星小 C 钦定下一任。

// 作为一名民主人士，小 C 决定举行全民大选来决定下一任。为了使最后成为总统的人得到绝大多数人认同，小 C 认为，一个人必须获得超过全部人总数的一半的票数才能成为总统。如果不存在符合条件的候选人，小 C 只好自己来当临时大总统。为了尽可能避免这种情况，小 C 决定先进行几次小规模预选，根据预选的情况，选民可以重新决定自己选票的去向。

// 由于秋之国人数较多，统计投票结果和选票变更也成为了麻烦的事情，小 C 找到了你，让你帮他解决这个问题。

// ## 题目描述

// 秋之国共有 $n$ 个人，分别编号为 $1,2,…,n$，一开始每个人都投了一票，范围 $1 \sim n$，表示支持对应编号的人当总统。

// 共有 $m$ 次预选，每次选取编号 $[l_i,r_i]$ 内的选民展开小规模预选，在该区间内获得超过区间大小一半的票的人获胜。如果没有人获胜，则由小 C 钦定一位候选者获得此次预选的胜利（获胜者可以不在该区间内），每次预选的结果需要公布出来，并且每次会有 $k_i$ 个人决定将票改投向该次预选的获胜者。

// 全部预选结束后，公布最后成为总统的候选人。

// ## 输入格式

// 第一行两个整数 $n,m$，表示秋之国人数和预选次数。

// 第二行 $n$ 个整数，分别表示编号 $1 \sim n$ 的选民投的票。

// 接下来 $m$ 行，每行先有四个整数，分别表示 $l_i,r_i,s_i,k_i$，$s_i$ 表示若此次预选无人胜选，视作编号为 $s_i$ 的人获得胜利，接下来 $k_i$ 个整数，分别表示决定改投的选民。

// ## 输出格式

// 共 $m+1$ 行，前 $m$ 行表示各次预选的结果，最后一行表示最后成为总统的候选人，若最后仍无人胜选，输出 $-1$。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 4
// 1 2 3 4 5
// 1 2 1 1 3
// 5 5 1 2 2 4
// 2 4 2 0
// 3 4 2 1 4
// ```

// ### 样例输出 #1

// ```
// 1
// 5
// 5
// 2
// -1
// ```

// ## 提示

// 对于前 $20 \%$ 的数据，$1 \leq n,m \leq 5000$。

// 对于前 $40 \%$ 的数据，$1 \leq n,m \leq 50000$，$\sum k_i \leq 50000$。

// 对于前 $50 \%$ 的数据，$1 \leq n,m \leq {10}^5$，$\sum k_i \leq 2 \times {10}^5$。

// 对于数据点 6~7，保证所有选票始终在 $1 \sim 10$ 之间。

// 对于 $100 \%$ 的数据，$1 \leq n,m \leq 5 \times {10}^5$，$\sum k_i \leq 10^6$，$1 \leq l_i \leq r_i \leq n$，$1 \leq s_i \leq n$。
#include <bits/stdc++.h>
#define ls(x) tree[x].ls
#define rs(x) tree[x].rs
#define sz(x) tree[x].sz
#define cnt(x) tree[x].cnt
#define nv(x) tree[x].nv
#define v(x) tree[x].v
#define rd(x) tree[x].rd

class set
{
private:
    struct node
    {
        int ls, rs, rd, sz, v;
    }*tree;

    int *rt, rx, ry, rz, cnt = 0;
    std::mt19937 rnd;

    inline void pushUp(int x)
    {
        sz(x) = sz(ls(x)) + sz(rs(x)) + 1;
    }

    inline int getNode(int v)
    {
        ++cnt;
        ls(cnt) = rs(cnt) = 0;
        sz(cnt) = 1, v(cnt) = v, rd(cnt) = rnd();
        return cnt;
    }

    inline void split(int v, int r, int& x, int& y)
    {
        if(!r)
        {
            x = y = 0;
            return ;
        }
        if(v(r) <= v)
        {
            x = r;
            split(v, rs(r), rs(x), y);
        }
        else
        {
            y = r;
            split(v, ls(r), x, ls(y));
        }
        pushUp(r);
    }

    inline int merger(int x, int y)
    {
        if(!x || !y) return x | y;
        if(rd(x) < rd(y))
        {
            rs(x) = merger(rs(x), y);
            pushUp(x);
            return x;
        }
        else
        {
            ls(y) = merger(x, ls(y));
            pushUp(y);
            return y;
        }
    }
public:
    set(int n): rnd(std::chrono::system_clock::now().time_since_epoch().count())
    {
        rt = new int[n + 10]{};
        tree = new node[n + 10];
        tree[0] = node{0, 0, 0, 0, 0};
    }

    ~set()
    {
        delete tree;
    }

    inline void emplace(int v, int id)
    {
        rt[v] = merger(rt[v], getNode(id));
    }

    inline void modify(int v1, int v2, int idx)
    {
        int &r1 = rt[v1], &r2 = rt[v2];
        split(idx, r1, rx, ry);
        split(idx - 1, rx, rx, rz);
        r1 = merger(rx, ry);
        split(idx, r2, rx, ry);
        r2 = merger(merger(rx, rz), ry);
    }

    inline int query(int v, int l, int r)
    {
        int& r1 = rt[v];
        split(r, r1, rx, ry);
        split(l - 1, rx, rx, rz);
        int res = sz(rz);
        r1 = merger(merger(rx, rz), ry);
        return res;
    }
};

class treap
{
private:
    struct node{
        int ls, rs, sz, v, cnt, nv, rd;
    }*tree;
    int cnt = 0, rt = 0, rx, ry, rz;
    std::mt19937 rnd;
    set idx;
    int* arr;

    inline void pushUp(int x)
    {
        sz(x) = sz(ls(x)) + sz(rs(x)) + 1;
        nv(x) = v(x), cnt(x) = 1;
        if(nv(x) == nv(ls(x))) cnt(x) += cnt(ls(x));
        else
        {
            nv(x) = cnt(x) < cnt(ls(x))? nv(ls(x)):nv(x);
            cnt(x) = std::abs(cnt(x) - cnt(ls(x))); 
        }
        if(nv(x) == nv(rs(x))) cnt(x) += cnt(rs(x));
        else
        {
            nv(x) = cnt(x) < cnt(rs(x))? nv(rs(x)):nv(x);
            cnt(x) = std::abs(cnt(x) - cnt(rs(x)));
        }
    }

    inline void split(int sz, int r, int& x, int& y)
    {
        if(!r)
        {
            x = y = 0;
            return ;
        }
        if(sz <= sz(ls(r)))
        {
            y = r;
            split(sz, ls(r), x, ls(y));
        }
        else
        {
            x = r;
            split(sz - sz(ls(x)) - 1, rs(r), rs(x), y);
        }
        pushUp(r);
    }

    inline int merger(int x, int y)
    {
        if(!x || !y) return x | y;
        if(rd(x) < rd(y))
        {
            rs(x) = merger(rs(x), y);
            pushUp(x);
            return x;
        }
        else
        {
            ls(y) = merger(x, ls(y));
            pushUp(y);
            return y;
        }
    }

    inline int getNode(int v)
    {
        ++cnt;
        ls(cnt) = rs(cnt) = 0;
        sz(cnt) = cnt(cnt) = 1;
        rd(cnt) = rnd(), nv(cnt) = v(cnt) = v;
        return cnt;
    }
public:
    treap(int n): rnd(std::chrono::system_clock::now().time_since_epoch().count()), idx(n)
    {
        tree = new node[n + 10];
        arr = new int[n + 10];
        tree[0] = {0, 0, 0, 0, 0, 0, 0};
    }

    ~treap()
    {
        delete tree;
    }

    inline void ins(int id, int v)
    {
        rt = merger(rt, getNode(v));
        idx.emplace(v, id);
        arr[id] = v;
    }

    inline void modify(int id, int v)
    {
        if(arr[id] == v) return ;
        idx.modify(arr[id], v, id);
        arr[id] = v;
        split(id, rt, rx, ry);
        split(id - 1, rx, rx, rz);
        nv(rz) = v(rz) = v;
        rt = merger(merger(rx, rz), ry);
    }

    inline int query(int l, int r, int s)
    {
        split(r, rt, rx, ry);
        split(l - 1, rx, rx, rz);
        int k = 0;
        int v = nv(rz), cnt = cnt(rz);
        for(int i = l; i <= r; ++i) if(arr[i] == v) ++k;
        rt = merger(merger(rx, rz), ry);
        if(!cnt) return s;
        int m = idx.query(v, l, r);
        return m > (r - l + 1) / 2? v:s;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, v;
    std::cin >> n >> m;
    treap tree(n);
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> v;
        tree.ins(i, v);
    }
    int l, r, s, k, id;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> l >> r >> s >> k;
        s = tree.query(l, r, s);
        for(int j = 0; j < k; ++j)
        {
            std::cin >> id;
            tree.modify(id, s);
        }
        std::cout << s << '\n';
    }
    std::cout << tree.query(1, n, -1);
    return 0;
}