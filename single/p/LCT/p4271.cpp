// # [USACO18FEB] New Barns P

// ## 题目描述

// 给你一棵树，初始没有节点。你需要支持两种操作：  

// - `B p` 表示新建一个节点，将它与 $p$  节点连接；若 $p=-1$，则表示不与其它节点相连  

// - `Q k` 表示查询在 $k$ 节点所在的连通块中，距它最远的点的距离。这里距离的定义是两点间经过的边数。

// ## 输入格式

// 第一行一个正整数 $q$，表示操作个数。  
// 接下来 $q$ 行，每行表示一个操作。

// ## 输出格式

// 对于每个询问操作，输出一行一个整数表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 7
// B -1
// Q 1
// B 1
// B 2
// Q 3
// B 2
// Q 2
// ```

// ### 样例输出 #1

// ```
// 0
// 2
// 1
// ```

// ## 提示

// 【数据范围】  

// 对于 $100%$ 的数据，$1 \le q \le 10^5$。  
// 保证操作合法。

// The example input corresponds to this network of barns:
// ```
//   (1) 
//     \   
//      (2)---(4)
//     /
//   (3)
// ```
// In query 1, we build barn number 1. In query 2, we ask for the distance of 1 to the farthest connected barn. Since barn 1 is connected to no other barns, the answer is 0. In query 3, we build barn number 2 and connect it to barn 1. In query 4, we build barn number 3 and connect it to barn 2. In query 5, we ask for the distance of 3 to the farthest connected barn. In this case, the farthest is barn 1, which is 2 units away. In query 6, we build barn number 4 and connect it to barn 2. In query 7, we ask for the distance of 2 to the farthest connected barn. All three barns 1, 3, 4 are the same distance away, which is 1, so this is our answer.

// Problem credits: Anson Hu
#include <iostream>
#include <bits/stdc++.h>

namespace LCT{
    class UFS{
    private:
        int *f, *rk;
    public:
        UFS(int);

        ~UFS();

        inline void merger(int, int);

        inline int find(int);
    };

    class Splay{
    private:
        #define ls(x) ch[x][0]
        #define rs(x) ch[x][1]
        #define get(x) (rs(f[x]) == x)
        #define isRoot(x) (ch[f[x]][get(x)] != x)

        int **ch, *f, *s, n;
        bool *tag;
    public:
        int *sz;

        Splay(int);

        ~Splay();

        inline void pushUp(int);

        inline void pushDown(int);

        inline void rotate(int);

        inline void updata(int);

        inline void splay(int);

        inline int access(int);

        inline void makeRoot(int);

        inline void split(int, int);

        inline int findRoot(int);

        inline void link(int, int);
    };
    
    UFS::UFS(int n){
        f = new int[n + 1]{};
        rk = new int[n + 1]{};
        std::iota(f, f + n + 1, 0);
    }
    
    UFS::~UFS(){
        delete[] f;
        delete[] rk;
    }

    inline void UFS::merger(int x, int y){
        if(rk[x] < rk[y]) f[x] = y;
        else f[y] = x;
        if(rk[x] == rk[y]) ++rk[x];
    }

    inline int UFS::find(int x){
        return f[x] ^ x? (f[x] = find(f[x])):x;
    }

    Splay::Splay(int m){
        n = m, ch = new int*[n + 1];
        for(int i = 0; i <= n; i++) ch[i] = new int[2]{};
        f = new int[n + 1]{}, sz = new int[n + 1]{};
        tag = new bool[n + 1]{}, s = new int[n + 1]{};
    }

    Splay::~Splay(){
        for(int i = 0; i <= n; i++) delete[] ch[i];
        delete[] ch, delete[] sz, delete[] f, delete[] tag, delete[] s;
    }

    inline void Splay::pushUp(int x){
        sz[x] = 1 + sz[ls(x)] + sz[rs(x)];
    }

    inline void Splay::pushDown(int x){
        if(tag[x]){
            if(ls(x)) tag[ls(x)] ^= 1, std::swap(ls(ls(x)), rs(ls(x)));
            if(rs(x)) tag[rs(x)] ^= 1, std::swap(ls(rs(x)), rs(rs(x)));
            tag[x] = 0;
        }
    }

    inline void Splay::rotate(int x){
        int y = f[x], z = f[y], k = get(x);
        if(!isRoot(y)) ch[z][get(y)] = x;
        if(ch[x][!k]) f[ch[x][!k]] = y;
        ch[y][k] = ch[x][!k], ch[x][!k] = y;
        f[x] = z, f[y] = x;
        pushUp(y), pushUp(x);
    }

    inline void Splay::updata(int x){
        int idx = 0;
        s[++idx] = x;
        while(!isRoot(x)) x = f[x], s[++idx] = x;
        while(idx) pushDown(s[idx--]); 
    }

    inline void Splay::splay(int x){
        updata(x);
        for(int fa = f[x]; !isRoot(x); rotate(x), fa = f[x]){
            if(!isRoot(fa)) rotate(get(x) ^ get(fa)? x:fa);
        }
    }

    inline int Splay::access(int x){
        int p;
        for(p = 0; x; p = x, x = f[x]){
            splay(x), rs(x) = p, pushUp(x);
        }
        return p;
    }

    inline void Splay::makeRoot(int x){
        access(x);
        splay(x);
        tag[x] ^= 1, std::swap(ls(x), rs(x));
    }

    inline int Splay::findRoot(int x){
        access(x);
        splay(x);
        while(ls(x)) pushDown(x), x = ls(x);
        splay(x);
        return x;
    }

    inline void Splay::split(int x, int y){
        makeRoot(x);
        access(y);
        splay(y);
    }

    inline void Splay::link(int x, int y){
        makeRoot(x), f[x] = y;
    }

    class LCT{
    private:
        Splay* tree; UFS* ufs;
        int cnt = 0, *mx[2], *r;
    public:
        LCT(int);

        ~LCT();

        inline void link(int);

        inline int query(int);
    };

    LCT::LCT(int n){
        mx[0] = new int[n + 1]{}, mx[1] = new int[n + 1]{}, r = new int[n + 1]{};
        tree = new Splay(n), ufs = new UFS(n);
    }

    LCT::~LCT(){
        delete[] mx[0], delete[] mx[1], delete[] r;
        delete tree, delete ufs;
    }

    inline void LCT::link(int x){
        int y = ++cnt;
        mx[0][y] = mx[1][y] = y, tree->sz[y] = r[y] = 1;
        if(x == -1) return ;
        int z = ufs->find(x);

        tree->link(x, y), ufs->merger(z, y);
        tree->split(mx[0][z], y);
        int l1 = tree->sz[y];
        tree->split(mx[1][z], y);
        int l2 = tree->sz[y];
        r[z] = std::max({r[z], l1, l2});
        if(r[z] == l1) mx[1][z] = y;
        else if(r[z] == l2) mx[0][z] = y;
    }

    inline int LCT::query(int x){
        int y = ufs->find(x);
        tree->split(mx[0][y], x);
        int l1 = tree->sz[x];
        tree->split(mx[1][y], x);
        int l2 = tree->sz[x];
        return std::max(l1, l2) - 1;
    }
} // namespace LCT

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int p, q;
    char op;
    std::cin >> q;
    LCT::LCT lct(q);

    for(int i = 0; i < q; i++){
        std::cin >> op >> p;
        if(op == 'B') lct.link(p);
        else if(op == 'Q') std::cout << lct.query(p) << '\n';
    }
    return 0;
}