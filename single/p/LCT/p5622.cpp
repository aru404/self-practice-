// # [DBOI2019] 巫女的职责

// ## 题目背景

// 作为八重村的巫女，樱承担着守卫村庄的责任，村子里受到了崩坏的威胁，八重樱，出击！

// ![bachongyingyingying](http://i0.hdslb.com/bfs/article/81e9465c02e29053f9fbe7c70d3c2644691abda2.png)

// ## 题目描述

// 八重古村有 $n$ 座房屋，一开始所有的房子之间都没有路，随着古村的发展，慢慢会出现连接两栋房屋的双向道路。

// 村民们原本过着无忧无虑的幸福生活，直到与文明作对——崩坏来了，慢慢地，某栋房屋也许会在遭受崩坏兽的侵袭，每只崩坏兽都有着一定的崩坏能，每户人家也许会存在着多只崩坏兽。

// 樱来了，她接受了驱魔委托，每个委托都是从驱逐某个房子到另一个房子的崩坏兽，樱只能走已有的路，由于这样的路径也许有很多条，聪明的樱只会选择在它们所有路径中都会走过的某些点，即必经点，每次委托樱会在两点间的所有必经点驱魔。

// ## 输入格式

// 第一行两个整数：$n,m$ 表示房屋数和事件数

// 接下来 $m$ 行，每行三个正整数：$opt,x,y$

// $opt=1 $时，表示房子 $x$ 和房子 $y$ 间修了一条双向道路(保证没有重边，但不保证没有自环，如有请忽略。)

// $opt=2$ 时，表示房子 $x$ 来了一只崩坏能为 $y$ 的崩坏兽

// $opt=3$ 时，表示樱完成了一次从 $x$ 到 $y$ 的驱魔委托(不保证 $x$ 与 $y$ 连通，不连通输出 $0$ 即可)

// 强制在线：记上次$3$的答案为 $\text{lastans}$，初值为 $0$，实际上的$x,y$ 用函数解码：
// ```cpp
// inline const void decode(int &x)
// {
// 	x^=lastans%n;
// 	if (x>n)x%=n;
// 	if (!x)x=1;
// }
// ```

// ## 输出格式

// 对于每个 $3$ 事件，输出一行一个数表示樱清除的崩坏能的值，答案保证在 $[0,2^{63})$

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 7
// 1 1 2
// 1 1 3
// 1 3 4
// 2 1 1
// 2 1 2
// 3 1 4
// 3 3 4
// ```

// ### 样例输出 #1

// ```
// 3
// 0
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 4 8
// 2 1 629
// 3 3 1
// 2 4 923
// 1 4 2
// 2 4 542
// 2 1 918
// 1 2 3
// 3 4 3
// ```

// ### 样例输出 #2

// ```
// 0
// 5
// ```

// ## 提示

// 【样例 $1$ 说明】

// 第四个事件使 $1$ 号房屋有 $1$ 点的崩坏能。

// 第五个事件使 $1$ 号房屋增加了 $2$ 点的崩坏能，此时其崩坏能值为 $3$。

// 第六个事件显然答案为 $3$，更新 $\text{lastans}=3$ 。

// 第七个事件真实的 $x=1$，$y=3$，由于第六个事件已经在 $1$ 驱魔，所以没有崩坏能。

// $Subtask$ #$1$（$20$ 分）： 

// $1\leq n,m\leq 100000$。

// $Subtask$ #$2$（$70$ 分）： 

// $1\leq n,m\leq 200000$。

// $Subtask$ #$3$（$10$ 分）： 

// $1\leq n,m\leq 500000$。

// 所有测试点的时间限制统一为 $1.5 \text s$，内存限制统一为 $125 \text{MiB}$。

// ### 题目提供者：[$\color{red}{zhengrunzhe}$](https://www.luogu.org/space/show?uid=14374)
#include <iostream>
#include <bits/stdc++.h>
#define ll unsigned long long
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
#define get(x) (rs(f[x]) == x)
#define isRoot(x) (ch[f[x]][get(x)] != x)

const int maxN = 5E5 + 5;
int ch[maxN << 1][2], f[maxN << 1], s[maxN << 1], cnt, n;
ll w[maxN << 1], collapse[maxN << 1];
bool tag[maxN << 1], lz[maxN << 1];

inline void pushUp(int x){
    collapse[x] = w[x] + collapse[ls(x)] + collapse[rs(x)];
}

inline void pushDown(int x){
    if(tag[x]){
        std::swap(ls(ls(x)), rs(ls(x)));
        std::swap(ls(rs(x)), rs(rs(x)));
        tag[ls(x)] ^= 1, tag[rs(x)] ^= 1;
        tag[x] = 0;
    }
    if(lz[x]){
        lz[ls(x)] = lz[rs(x)] = 1;
        w[ls(x)] = w[rs(x)] = collapse[ls(x)] = collapse[rs(x)] = 0;
        lz[x] = 0;
    }
}

inline void rotate(int x){
    int y = f[x], z = f[y], k = get(x);
    if(!isRoot(y)) ch[z][get(y)] = x;
    if(ch[x][!k]) f[ch[x][!k]] = y;
    ch[y][k] = ch[x][!k], ch[x][!k] = y;
    f[y] = x, f[x] = z;
    pushUp(y), pushUp(x);
}

inline void updata(int x){
    int idx = 0;
    s[++idx] = x;
    while(!isRoot(x)) x = f[x], s[++idx] = x;
    while(idx) pushDown(s[idx--]);
}

inline void splay(int x){
    updata(x);
    for(int fa = f[x]; !isRoot(x); rotate(x), fa = f[x]){
        if(!isRoot(fa)) rotate(get(x) ^ get(fa)? x:fa);
    }
}

inline int access(int x){
    int p;
    for(p = 0; x; p = x, x = f[x]){
        splay(x);
        rs(x) = p;
        pushUp(x);
    }
    return p;
}

inline void makeRoot(int x){
    access(x);
    splay(x);
    tag[x] ^= 1;
    std::swap(ls(x), rs(x));
}

inline int findRoot(int x){
    access(x);
    splay(x);
    while(ls(x)) pushDown(x), x = ls(x);
    splay(x);
    return x;
}

inline void split(int x, int y){
    makeRoot(x);
    access(y);
    splay(y);
}

inline void link(int x, int y){
    makeRoot(x);
    f[x] = y;
}

inline void merger(int x){
    int idx = 0, c;
    std::function<void(int)> dfs = [&](int y)->void{
        if(!y) return ;
        s[++idx] = y;
        pushDown(y);
        if(y > n) c = y;
        dfs(ls(y)), dfs(rs(y));
    };
    pushDown(x);
    dfs(rs(x));
    f[c] = x, rs(x) = 0, collapse[x] = w[x];
    for(int i = 1; i <= idx; i++){
        if(s[i] != c) f[s[i]] = c;
        ls(s[i]) = rs(s[i]) = 0, collapse[s[i]] = w[s[i]];
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m, op;
    ll res = 0, u, v;
    std::cin >> n >> m;
    cnt = n;
    for(int i = 0; i < m; i++){
        std::cin >> op >> u >> v;
        std::function<void(ll&)> decode = [&](ll& x)->void{
            x ^= res % n;
            if(x > n) x %= n;
            if(!x) x = 1;
        };
        decode(u), decode(v);
        if(op == 1){
            if(u != v){
                makeRoot(u);
                int r = findRoot(v);
                if(r != u){
                    ++cnt;
                    link(cnt, v), link(cnt, u);
                }
                else{
                    merger(u);
                }
            }
        }
        else if(op == 2){
            splay(u), w[u] += v, collapse[u] += v;
        }
        else if(op == 3){
            if(u == v) res = w[u], splay(u), w[u] = 0, pushUp(u);
            else{
                makeRoot(u);
                if(findRoot(v) != u) res = 0;
                else res = collapse[u], w[u] = collapse[u] = 0, lz[u] = 1;
            }
            std::cout << res << std::endl;
        }
    }
    return 0;
}