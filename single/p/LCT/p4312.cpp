// # [COI2009] OTOCI

// ## 题目背景

// 注：本题原题通过**交互**的形式强制在线。但是在本题您不需要考虑交互的问题。

// ## 题目描述

// 不久之前，Mirko 建立了一个旅行社，名叫“极地之梦”。这家旅行社在北极附近购买了 $n$ 座冰岛，并且提供观光服务。

// 当地最受欢迎的当然是帝企鹅了，这些小家伙经常成群结队的游走在各个冰岛之间。Mirko 的旅行社遭受一次重大打击，以至于观光游轮已经不划算了。旅行社将在冰岛之间建造大桥，并用观光巴士来运载游客。

// Mirko 希望开发一个电脑程序来管理这些大桥的建造过程，以免有不可预料的错误发生。这些冰岛从1到N标号。一开始时这些岛屿没有大桥连接，并且所有岛上的帝企鹅数量都是知道的。每座岛上的企鹅数量虽然会有所改变，但是始终在 $[0, 1000]$ 之间。你的程序需要处理以下三种命令：  

// - `bridge u v`：询问结点 $u$ 与结点 $v$ 是否连通。如果是则输出 `no`；否则输出 `yes`，并且在结点 $u$ 和结点 $v$ 之间连一条无向边。 
// - `penguins u x`：将结点 $u$ 对应的权值 $w_u$ 修改为 $x$。 
// - `excursion u v`：如果结点 $u$ 和结点 $v$ 不连通，则输出 `impossible`。否则输出结点 $u$ 到结点 $v$ 的路径上的点对应的权值的和。 

// 共有 $q$ 个操作。

// ## 输入格式

// 第一行包含一个整数 $n$，表示节点的数目。 

// 第二行包含 $n$ 个整数，第 $i$ 个整数表示第 $i$ 个节点初始时的权值 $w_i$。 

// 第三行包含一个整数 $q$，表示操作的数目。 

// 以下 $q$ 行，每行包含一个操作，操作的类别见题目描述。

// ## 输出格式

// 输出所有 `bridge` 操作和 `excursion` 操作对应的输出，每个一行表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5
// 4 2 4 5 6
// 10
// excursion 1 1
// excursion 1 2
// bridge 1 2
// excursion 1 2
// bridge 3 4
// bridge 3 5
// excursion 4 5
// bridge 1 3
// excursion 2 4
// excursion 2 5
// ```

// ### 样例输出 #1

// ```
// 4
// impossible
// yes
// 6
// yes
// yes
// 15
// yes
// 15
// 16
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 6
// 1 2 3 4 5 6
// 10
// bridge 1 2
// bridge 2 3
// bridge 4 5
// excursion 1 3
// excursion 1 5
// bridge 3 4
// excursion 1 5
// penguins 3 10
// excursion 1 3
// bridge 1 5
// ```

// ### 样例输出 #2

// ```
// yes
// yes
// yes
// 6
// impossible
// yes
// 15
// 13
// no
// ```

// ## 提示

// 【数据范围】   
// 对于 $100\%$ 的数据，$1 \le n \le 3 \times 10^4$，$1 \le q \le 3\times 10^5$, $0 \le w_i \le 1000$。
#include <iostream>
#include <bits/stdc++.h>
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
#define get(x) (ch[f[x]][1] == x)
#define isRoot(x) (ch[f[x]][get(x)] != x)

const int maxN = 3E4 + 5;
int ch[maxN][2], f[maxN], w[maxN], tot[maxN], s[maxN];
bool tag[maxN];

inline void pushUp(int x){
    tot[x] = tot[ls(x)] + tot[rs(x)] + w[x];
}

inline void pushDown(int x){
    if(tag[x]){
        std::swap(ls(ls(x)), rs(ls(x)));
        std::swap(ls(rs(x)), rs(rs(x)));
        tag[ls(x)] ^= 1, tag[rs(x)] ^= 1;
        tag[x] = 0;
    }
}

inline void rotate(int x){
    int y = f[x], z = f[y], k = get(x);
    if(!isRoot(y)) ch[z][get(y)] = x;
    if(ch[x][!k]) f[ch[x][!k]] = y;
    ch[y][k] = ch[x][!k], ch[x][!k] = y;
    f[x] = z, f[y] = x;
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

inline int findRoot(int x){
    access(x);
    splay(x);
    while(ls(x)) pushDown(x), x = ls(x);
    splay(x);
    return x;
}

inline void makeRoot(int x){
    access(x);
    splay(x);
    std::swap(ls(x), rs(x));
    tag[x] ^= 1;
}

inline void split(int x, int y){
    makeRoot(x);
    access(y);
    splay(y);
}

inline bool link(int x, int y){
    makeRoot(x);
    if(findRoot(y) != x){
        f[x] = y;
        return 1;
    }
    else return 0;
}

inline bool cut(int x, int y){
    split(x, y);
    if(findRoot(y) != x || rs(x) != y || ls(y)) return 0;
    rs(x) = f[y] = 0;
    pushUp(x);
    return 1;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q, x, y;
    std::string op;
    std::cin >> n;
    for(int i = 1; i <= n; i++) std::cin >> w[i];
    std::cin >> q;
    for(int i = 0; i < q; i++){
        std::cin >> op >> x >> y;
        if(op[0] == 'b'){
            if(link(x, y)) std::cout << "yes" << '\n';
            else std::cout << "no" << '\n';
        }
        else if(op[0] == 'p'){
            splay(x);
            w[x] = y;
        }
        else if(op[0] == 'e'){
            split(x, y);
            if(findRoot(y) != x) std::cout << "impossible" << '\n';
            else std::cout << tot[x] << '\n';
        }
    }
    return 0;
}