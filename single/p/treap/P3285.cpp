// # [SCOI2014] 方伯伯的OJ

// ## 题目描述

// 方伯伯正在做他的 OJ。现在他在处理 OJ 上的用户排名问题。OJ 上注册了 $n$ 个用户，编号为 $1\sim n$，一开始他们按照编号排名。

// 方伯伯会按照心情对这些用户做以下四种操作，修改用户的排名和编号：

// 1. 操作格式为 $1\ \ x\ \ y$，意味着将编号为 $x$ 的用户编号改为 $y$，而排名不变，执行完该操作后需要输出该用户在队列中的位置，数据保证 $x$ 必然出现在队列中，同时，$y$ 是一个当前不在排名中的编号。
// 2. 操作格式为 $2\ \ x$，意味着将编号为 $x$ 的用户的排名提升到第一位，执行完该操作后需要输出执行该操作前编号为 $x$ 用户的排名。
// 3. 操作格式为 $3\ \ x$，意味着将编号为 $x$ 的用户的排名降到最后一位，执行完该操作后需要输出执行该操作前编号为 $x$ 用户的排名。
// 4. 操作格式为 $4\ \ k$，意味着查询当前排名为 $k$ 的用户编号，执行完该操作后需要输出当前操作用户的编号。

// 但同时为了防止别人监听自己的工作，方伯伯对他的操作进行了加密，即将四种操作的格式分别改为了：

// - $1\ \ x+a\ \ y+a$；
// - $2\ \ x+a$；
// - $3\ \ x+a$；
// - $4\ \ k+a$；
// - 其中 $a$ 为上一次操作得到的输出，一开始 $a=0$。

// 例如：上一次操作得到的输出是 $5$，这一次操作的输入为：$1\ \ 13\ \ 15$ 因为这个输入是经过加密后的，所以你应该处理的操作是 $1\ \ 8\ \ 10$。

// 现在你截获了方伯伯的所有操作，希望你能给出结果。

// ## 输入格式

// 输入的第 $1$ 行包含 $2$ 个用空格分隔的整数 $n$ 和 $m$，表示初始用户数和操作数。此后有 $m$ 行，每行是一个询问，询问格式如上所示。

// ## 输出格式

// 输出包含 $m$ 行。每行包含一个整数，其中第 $i$ 行的整数表示第 $i$ 个操作的输出。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 10 10
// 1 2 11
// 3 13
// 2 5
// 3 7
// 2 8
// 2 10
// 2 11
// 3 14
// 2 18
// 4 9
// ```

// ### 样例输出 #1

// ```
// 2
// 2
// 2
// 4
// 3
// 5
// 5
// 7
// 8
// 11
// ```

// ## 提示

// 对于 $100\%$ 的数据，$1 \le n \le 10^8$，$1 \le m \le 10^5$。

// 输入保证对于所有的操作 $1,2,3$，$x$ 必然已经出现在队列中，同时对于所有操作 $1$，$1 \le y \le 2\times 10^8$，并且 $y$ 没有出现在队列中。

// 对于所有操作 $4$，保证 $1 \le k \le n$。
#include <bits/stdc++.h>
#define ls(x) tree[x].ls
#define rs(x) tree[x].rs
#define sz(x) tree[x].sz
#define rd(x) tree[x].rd
#define l(x) tree[x].l
#define r(x) tree[x].r
#define f(x) tree[x].f
#define inv(x) tree[x].inv

const int maxN = 3E5 + 5;

std::mt19937 rnd;

class treap2
{
private:
    struct node
    {
        int ls, rs, l, r, inv, rd; 
    }*tree;
    int rt, rx, ry, rz, cnt = 0;
    std::stack<int> s;

    inline int& getNode(int& x, int l, int r, int inv);

    inline void split(int v, int r, int& x, int& y);

    inline int merger(int x, int y);
public:
    explicit treap2(int n);
    
    ~treap2();

    inline void earse(int l, int r);

    inline void ins(int l, int r, int v);

    inline int find(int v);
};

class treap1
{
private:
    struct node
    {
        int ls, rs, l, r, f, sz, rd;
    }*tree;
    int rt, cnt = 0;
    treap2 map;

    inline int getNode(int l, int r);

    inline void pushUp(const int& x);

    inline void breakUp(int v, int w, int& x, int& y, int& z);

    inline void split(int v, int r, int& x, int& y);

    inline int merger(int x, int y);
public:
    explicit treap1(int n);

    ~treap1();

    inline int getRk(int x);

    inline int up(int v);

    inline int down(int v);

    inline int getV(int rk);

    inline int modify(int v, int w);
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    rnd = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());

    int n, m, a = 0, t, x, y;
    std::cin >> n >> m;
    treap1 treap(n);

    for(int i = 0; i < m; ++i)
    {
        std::cin >> t >> x;
        x -= a;
        if(t == 1)
        {
            std::cin >> y;
            y -= a;
            a = treap.modify(x, y);
        }
        else if(t == 2) a = treap.up(x);
        else if(t == 3) a = treap.down(x);
        else if(t == 4) a = treap.getV(x);
        std::cout << a << '\n';
    }
    return 0;
}

treap1::treap1(int n): map(n)
{
    tree = new node[n + 10];
    tree[0] = node{0, 0, 0, 0, 0, 0, 0}; 
    rt = getNode(1, n);
    map.ins(1, n, rt);
}

treap1::~treap1()
{
    delete tree;
}

inline int treap1::getNode(int l, int r)
{
    int x = ++cnt;
    ls(x) = rs(x) = f(x) = 0;
    rd(x) = rnd();
    l(x) = l, r(x) = r, sz(x) = r - l + 1;
    return x;
}

inline void treap1::pushUp(const int& x)
{
    f(x) = 0;
    sz(x) = r(x) - l(x) + 1 + sz(ls(x)) + sz(rs(x));
    if(ls(x)) f(ls(x)) = x;
    if(rs(x)) f(rs(x)) = x;
}

inline void treap1::split(int v, int r, int& x, int& y)
{
    if(!r)
    {
        x = y = 0;
        return ;
    }
    int w = sz(ls(r)) + r(r) - l(r) + 1;
    if(w <= v)
    {
        x = r;
        split(v - w, rs(r), rs(x), y);
    }
    else
    {
        y = r;
        split(v, ls(r), x, ls(y));
    }
    pushUp(r);
}

inline int treap1::merger(int x, int y)
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

inline void treap1::breakUp(int v, int w, int& x, int& y, int& z)
{
    int r = r(x), l = l(x);
    map.earse(l, r);
    if(l < v)
    {
        r(x) = v - 1, sz(x) = v - l;
        map.ins(l(x), v - 1, x);
        y = getNode(w, w);
        map.ins(w, w, y);
    }
    else
    {
        r(x) = l(x) = w, sz(x) = 1;
        map.ins(w, w, x);
        std::swap(x, y);
    }
    if(v < r)
    {
        z = getNode(v + 1, r);
        map.ins(v + 1, r, z);
    }
}

inline int treap1::getRk(int x)
{
    int res = sz(ls(x)) + r(x) - l(x) + 1;
    while(f(x))
    {
        if(rs(f(x)) == x) res += sz(ls(f(x))) + r(f(x)) - l(f(x)) + 1;
        x = f(x);
    }
    return res;
}

inline int treap1::up(int v)
{
    int rx = 0, ry = 0, rz = 0, rw = 0, rv = 0;
    int inv = map.find(v), rk = getRk(inv);
    int res = rk - r(inv) + v;
    split(rk, rt, rx, ry);
    split(sz(rx) - r(inv) + l(inv) - 1, rx, rx, rz);
    breakUp(v, v, rz, rw, rv);
    rt = merger(merger(merger(merger(rw, rx), rz), rv), ry);
    return res;
}

inline int treap1::down(int v)
{
    int rx = 0, ry = 0, rz = 0, rw = 0, rv = 0;
    int inv = map.find(v), rk = getRk(inv);
    int res = rk - r(inv) + v;
    split(rk, rt, rx, ry);
    split(sz(rx) - r(inv) + l(inv) - 1, rx, rx, rz);
    breakUp(v, v, rz, rw, rv);
    rt = merger(merger(merger(merger(rx, rz), rv), ry), rw);
    return res;
}

inline int treap1::getV(int rk)
{
    int r = rt;
    while(rk <= sz(ls(r)) || rk > sz(ls(r)) + r(r) - l(r) + 1)
    {
        if(rk <= sz(ls(r))) r = ls(r);
        else
        {
            rk -= sz(ls(r)) + r(r) - l(r) + 1;
            r = rs(r);
        }
    }
    return l(r) + rk - 1 - sz(ls(r));
}

inline int treap1::modify(int v, int w)
{
    int rx = 0, ry = 0, rz = 0, rw = 0, rv = 0;
    int inv = map.find(v), rk = getRk(inv);
    int res = rk - r(inv) + v;
    split(rk, rt, rx, ry);
    split(sz(rx) - r(inv) + l(inv) - 1, rx, rx, rz);
    breakUp(v, w, rz, rw, rv);
    rt = merger(merger(merger(merger(rx, rz), rw), rv), ry);
    return res;
}

treap2::treap2(int n)
{
    tree = new node[n + 10];
    rt = 0;
    tree[0] = node{0, 0, 0, 0, 0, 0}; 
}

treap2::~treap2()
{
    delete tree;
}

inline int& treap2::getNode(int& x, int l, int r, int inv)
{
    if(s.empty()) x = ++cnt;
    else x = s.top(), s.pop();
    ls(x) = rs(x) = 0;
    l(x) = l, r(x) = r;
    inv(x) = inv, rd(x) = rnd();
    return x;
}

inline void treap2::split(int v, int r, int& x, int& y)
{
    if(!r)
    {
        x = y = 0;
        return ;
    }
    if(r(r) <= v)
    {
        x = r;
        split(v, rs(r), rs(x), y);
    }
    else
    {
        y = r;
        split(v, ls(r), x, ls(y));
    }
}

inline int treap2::merger(int x, int y)
{
    if(!x || !y) return x | y;
    if(rd(x) < rd(y))
    {
        rs(x) = merger(rs(x), y);
        return x;
    }
    else
    {
        ls(y) = merger(x, ls(y));
        return y;
    }
}

inline void treap2::earse(int l, int r)
{
    split(r, rt, rx, ry);
    split(l - 1, rx, rx, rz);
    s.push(rz);
    rt = merger(rx, ry);
}

inline void treap2::ins(int l, int r, int inv)
{
    split(l - 1, rt, rx, ry);
    rt = merger(merger(rx, getNode(rz, l, r, inv)), ry);
}

inline int treap2::find(int v)
{
    int r = rt;
    while(v < l(r) || v > r(r))
    {
        if(v < l(r)) r = ls(r);
        else r = rs(r);
    }
    return inv(r);
}