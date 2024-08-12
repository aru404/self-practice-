// # Goodbye Souvenir

// ## 题面翻译

// 给定长度为$n$的数组, 定义数字$X$在$[l,r]$内的值为数字$X$在$[l,r]$内最后一次出现位置的下标减去第一次出现位置的下标  
// 给定$m$次询问, 每次询问有三个整数$a, b, c$,询问规则如下:  
// 当$a = 1$时, 将数组内第$b$个元素更改为$c$  
// 当$a = 2$时, 求区间$[b,c]$所有数字的值的和  

// 输入:  
// 第一行两个整数$n,m$  
// 第二行$n$个整数, 表示数组  
// 第$3-3 + m$行, 每行三个整数, 表示每次询问  

// 输出:  
// 对于每次$a = 2$的询问, 输出一个整数表示答案

// ## 题目描述

// I won't feel lonely, nor will I be sorrowful... not before everything is buried.

// A string of $ n $ beads is left as the message of leaving. The beads are numbered from $ 1 $ to $ n $ from left to right, each having a shape numbered by integers between $ 1 $ and $ n $ inclusive. Some beads may have the same shapes.

// The memory of a shape $ x $ in a certain subsegment of beads, is defined to be the difference between the last position and the first position that shape $ x $ appears in the segment. The memory of a subsegment is the sum of memories over all shapes that occur in it.

// From time to time, shapes of beads change as well as the memories. Sometimes, the past secreted in subsegments are being recalled, and you are to find the memory for each of them.

// ## 输入格式

// The first line of input contains two space-separated integers $ n $ and $ m $ ( $ 1<=n,m<=100000 $ ) — the number of beads in the string, and the total number of changes and queries, respectively.

// The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=n $ ) — the initial shapes of beads $ 1,2,...,n $ , respectively.

// The following $ m $ lines each describes either a change in the beads or a query of subsegment. A line has one of the following formats:

// - 1 p x ( $ 1<=p<=n $ , $ 1<=x<=n $ ), meaning that the shape of the $ p $ -th bead is changed into $ x $ ;
// - 2 l r ( $ 1<=l<=r<=n $ ), denoting a query of memory of the subsegment from $ l $ to $ r $ , inclusive.

// ## 输出格式

// For each query, print one line with an integer — the memory of the recalled subsegment.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 7 6
// 1 2 3 1 3 2 1
// 2 3 7
// 2 1 3
// 1 7 2
// 1 3 2
// 2 1 6
// 2 5 7
// ```

// ### 样例输出 #1

// ```
// 5
// 0
// 7
// 1
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 7 5
// 1 3 2 1 4 2 3
// 1 1 4
// 2 2 3
// 1 1 7
// 2 4 5
// 1 1 7
// ```

// ### 样例输出 #2

// ```
// 0
// 0
// ```

// ## 提示

// The initial string of beads has shapes $ (1,2,3,1,3,2,1) $ .

// Consider the changes and queries in their order:

// 1. 2 3 7: the memory of the subsegment $ [3,7] $ is $ (7-4)+(6-6)+(5-3)=5 $ ;
// 2. 2 1 3: the memory of the subsegment $ [1,3] $ is $ (1-1)+(2-2)+(3-3)=0 $ ;
// 3. 1 7 2: the shape of the $ 7 $ -th bead changes into $ 2 $ . Beads now have shapes $ (1,2,3,1,3,2,2) $ respectively;
// 4. 1 3 2: the shape of the $ 3 $ -rd bead changes into $ 2 $ . Beads now have shapes $ (1,2,2,1,3,2,2) $ respectively;
// 5. 2 1 6: the memory of the subsegment $ [1,6] $ is $ (4-1)+(6-2)+(5-5)=7 $ ;
// 6. 2 5 7: the memory of the subsegment $ [5,7] $ is $ (7-6)+(5-5)=1 $ .

#include <iostream>
#include <bits/stdc++.h>
#define ll long long
#define lowbit(x) (x & -x)
#define v(x) treap[x].v
#define rd(x) treap[x].rd
#define ls(x) treap[x].l
#define rs(x) treap[x].r

const int maxN = 1E5 + 5;
int arr[maxN], s1[maxN << 2], s2[maxN << 2], s[maxN << 3], n;
ll tree[maxN], res[maxN];
int head[maxN], rx, ry, rz, tot = 0, cnt;
std::mt19937 rnd;
std::bitset<maxN> vis = 0;

struct Count
{
    int l, r, w, t;
}nodes[maxN << 3];

struct Node
{
    int v, rd, l, r;
}treap[maxN];

inline void getNode(int& x, int v)
{
    x = ++tot;
    rd(x) = rnd(), v(x) = v, ls(x) = rs(x) = 0;
}

inline void split(int v, int r, int& x, int& y)
{
    if(!r)
    {
        x = y = 0;
        return ;
    }
    if(v(r) <= v) x = r, split(v, rs(r), rs(x), y);
    else y = r, split(v, ls(r), x, ls(y));
}

inline int merger(int x, int y)
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

inline void ins(int x, int idx)
{
    getNode(rz, idx);
    head[x] = merger(head[x], rz);
}

inline void change(int idx, int x, int t)
{
    if(arr[idx] == x) return ;
    split(idx, head[arr[idx]], rx, ry);
    split(idx - 1, rx, rx, rz);
    int pre = rx;
    while(rs(pre)) pre = rs(pre);
    if(pre) nodes[++cnt] = {v(pre), idx, v(pre) - idx, t};
    int suf = ry;
    while(ls(suf)) suf = ls(suf);
    if(suf) nodes[++cnt] = {idx, v(suf), idx - v(suf), t};
    if(pre && suf) nodes[++cnt] = {v(pre), v(suf), v(suf) - v(pre), t};
    head[arr[idx]] = merger(rx, ry);

    split(idx, head[x], rx, ry);
    pre = rx;
    while(rs(pre)) pre = rs(pre);
    if(pre) nodes[++cnt] = {v(pre), idx, idx - v(pre), t};
    suf = ry;
    while(ls(suf)) suf = ls(suf);
    if(suf) nodes[++cnt] = {idx, v(suf), v(suf) - idx, t};
    if(pre && suf) nodes[++cnt] = {v(pre), v(suf), v(pre) - v(suf), t};
    head[x] = merger(merger(rx, rz), ry);
    arr[idx] = x;
}

inline void updata(int x, int v)
{
    while(x <= n) tree[x] += v, x += lowbit(x);
}

inline ll query(int x)
{
    ll res = 0;
    while(x) res += tree[x], x -= lowbit(x);
    return res;
}

inline void clear(int x)
{
    while(x <= n) tree[x] = 0, x += lowbit(x);
}

inline void cdq(int l, int r)
{
    if(l == r) return ;
    int m = (l + r) >> 1;
    cdq(l, m);
    cdq(m + 1, r);
    std::copy(s + l, s + m + 1, s1 + 1);
    std::copy(s + m + 1, s + r + 1, s2 + 1);
    s1[m - l + 2] = s2[r - m + 1] = 0;
    int idx1 = 1, idx2 = 1;
    for(int i = l; i <= r; ++i)
    {
        if(nodes[s1[idx1]].l >= nodes[s2[idx2]].l)
        {
            if(!vis[nodes[s1[idx1]].t]) updata(nodes[s1[idx1]].r, nodes[s1[idx1]].w);
            s[i] = s1[idx1++];
        }
        else
        {
            if(vis[nodes[s2[idx2]].t]) res[nodes[s2[idx2]].t] += query(nodes[s2[idx2]].r);
            s[i] = s2[idx2++];
        }
    }
    for(int i = 1; i <= m - l + 1; ++i) if(!vis[nodes[s1[idx1]].t]) clear(nodes[s1[i]].r);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int m, a, b, c;
    std::cin >> n >> m;
    rnd = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
        ins(arr[i], i);
        if(s[arr[i]]) nodes[++cnt] = {s[arr[i]], i, i - s[arr[i]], 0};
        s[arr[i]] = i;
    }
    for(int i = 1; i <= m; ++i)
    {
        std::cin >> a >> b >> c;
        if(a == 1)
        {
            change(b, c, i);
        }
        else
        {
            nodes[++cnt] = {b, c, 0, i};
            vis[i] = 1;
        }
    }
    nodes[0] = {0, 0, 0, 0};
    std::iota(s + 1, s + cnt + 1, 1);
    cdq(1, cnt);
    for(int i = 1; i <= n; ++i) if(vis[i]) std::cout << res[i] << '\n';
    return 0;
}