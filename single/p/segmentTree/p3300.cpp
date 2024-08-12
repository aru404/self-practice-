// # [SDOI2013] 城市规划

// ## 题目描述

// A 市的市长打算在海边开发一段地带。这个地带看成是一个 $N \times M $ 的方格阵。每个格子可以是建筑、道路或者草地。这片地带是要出租给某些公司，但是这些公司的要求很奇怪。他们要求租给他们的建筑要通过道路形成一个连通块。同一个连通块只能租给一家公司。这个 $N\times M$ 的方格阵是用字符组成的：`O`，`.`，`+`，`|`，`-`，其中 `O` 表示建筑，'.' 表示草地。`|`，`-`，`+` 表示道路，分别表示把上下，左右、上下左右的格子连起来。相邻的 `O` 表示这是一个建筑物。

// 由于规划可能不太好，可能某些连通块里面只有道路，这里道路是不能出租的！由于最后这块地的选取可能有部分会与其他市共冋开发，所以最后会在这个 $N\times M$ 中选取一段出来，最后选取出来的是一个 $N_i\times M$（$0<N_1\le N$）的地段。A 市的市长想弄要一个规划软件，支持以下功能：

// 1. 改变一个格子。
// 2. 询问某块地带有多少个带建筑的连通块。

// ## 输入格式

// 第一行两个整数 $N, M$，如题意所示

// 接下来的 $N$ 行，每行 $M$ 个字符表示这片地带的初始情况。  

// 接下来的一行一个整数 $Q$，表示操作次数。接下来的 $Q$ 行，每行有两种格式：  
// - `C i j k` :  把第 $i$ 行第 $j$ 个格子修改成k；
// - `Q l r`:  询问 $(l, 1) (r, M)$ 这块地带连通块个数。

// ## 输出格式

// 对于每个询问中的 $Q$，输出一行，一个数字，表示当前的连通块个数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4  4
// .O..
// O+O|
// .O.. 
// ..OO
// 4
// Q 1 4
// C 2 4 + 
// C 3 4 | 
// Q 1 4
// ```

// ### 样例输出 #1

// ```
// 2 
// 1
// ```

// ## 提示

// 对于 $100\%$ 的数据，$N\le 100000, M\le 6, Q\le 10000$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E5 + 5, maxM = 6;

namespace UiT{
    int fa[maxN * maxM], r, c;
    bool isRoad[maxN * maxM];
    char mat[maxN][maxM];

    inline int find(int x){return x ^ fa[x]? (fa[x] = find(fa[x])):x;}

    inline void merger(int x, int y){fa[x] = y; isRoad[y] |= isRoad[x];}

    struct seg{
        int ls[maxM], rs[maxM];
        bool lr[maxM], rr[maxM];
        int cnt;
    }tree[maxN << 2];

    inline seg add(const seg& l, const seg& r, int m){
        seg res;
        for(int i = 0; i < c; i++){
            fa[l.ls[i]] = l.ls[i], fa[l.rs[i]] = l.rs[i];
            fa[r.ls[i]] = r.ls[i], fa[r.rs[i]] = r.rs[i];
            isRoad[l.ls[i]] = l.lr[i], isRoad[l.rs[i]] = l.rr[i];
            isRoad[r.ls[i]] = r.lr[i], isRoad[r.rs[i]] = r.rr[i];
        }
        res.cnt = l.cnt + r.cnt;
        for(int i = 0; i < c; i++){
            if((mat[m][i] == '+' || mat[m][i] == 'O' || mat[m][i] == '|') && (mat[m + 1][i] == '+' || mat[m + 1][i] == 'O' || mat[m + 1][i] == '|')){
                int x = find(l.rs[i]), y = find(r.ls[i]);
                if(x == y) continue;
                if(isRoad[x] && isRoad[y]) res.cnt--;
                merger(x, y);
            }
        }
        for(int i = 0; i < c; i++){
            res.ls[i] = find(l.ls[i]), res.rs[i] = find(r.rs[i]);
            res.lr[i] = isRoad[res.ls[i]], res.rr[i] = isRoad[res.rs[i]];
        }
        return res;
    }

    inline void pushUp(int p, int m){
        tree[p] = add(tree[p << 1], tree[p << 1 | 1], m);
    }

    inline void buildTree(int s, int t, int p){
        if(s == t){
            tree[p].cnt = 0;
            for(int i = 0; i < c; i++){
                int v = c * (s - 1) + i;
                tree[p].ls[i] = fa[v] = v;
                if(mat[s][i] == 'O') tree[p].cnt++, isRoad[v] = 1;
                else isRoad[v] = 0;
            }
            for(int i = 0; i < c - 1; i++){
                if((mat[s][i] == '+' || mat[s][i] == 'O' || mat[s][i] == '-') && (mat[s][i + 1] == '+' || mat[s][i + 1] == 'O' || mat[s][i + 1] == '-')){
                    int x = find(c * (s - 1) + i), y = find(c * (s - 1) + i + 1);
                    if(isRoad[x] && isRoad[y]) tree[p].cnt--;
                    merger(x, y);
                }
            }
            for(int i = 0; i < c; i++){
                tree[p].ls[i] = tree[p].rs[i] = find(tree[p].ls[i]);
                tree[p].lr[i] = tree[p].rr[i] = isRoad[tree[p].ls[i]];
            }
            return ;
        }
        int m = (t + s) >> 1;
        buildTree(s, m, p << 1);
        buildTree(m + 1, t, p << 1 | 1);
        pushUp(p, m);
    }

    inline void updata(int x, int y, char op, int s, int t, int p){
        if(s == t){
            mat[x][y] = op;
            tree[p].cnt = 0;
            for(int i = 0; i < c; i++){
                int v = c * (s - 1) + i;
                tree[p].ls[i] = fa[v] = v;
                if(mat[s][i] == 'O') tree[p].cnt++, isRoad[v] = 1;
                else isRoad[v] = 0;
            }
            for(int i = 0; i < c - 1; i++){
                if((mat[s][i] == '+' || mat[s][i] == 'O' || mat[s][i] == '-') && (mat[s][i + 1] == '+' || mat[s][i + 1] == 'O' || mat[s][i + 1] == '-')){
                    int x = find(c * (s - 1) + i), y = find(c * (s - 1) + i + 1);
                    if(isRoad[x] && isRoad[y]) tree[p].cnt--;
                    merger(x, y);
                }
            }
            for(int i = 0; i < c; i++){
                tree[p].ls[i] = tree[p].rs[i] = find(tree[p].ls[i]);
                tree[p].lr[i] = tree[p].rr[i] = isRoad[tree[p].ls[i]];
            }
            return ;            
        }
        int m = (t + s) >> 1;
        if(x <= m) updata(x, y, op, s, m, p << 1);
        else updata(x, y, op, m + 1, t, p << 1 | 1);
        pushUp(p, m);
    }

    inline seg query(int l, int r, int s, int t, int p){
        if(l <= s && r >= t) return tree[p];
        int m = (t + s) >> 1;
        if(r <= m) return query(l, r, s, m, p << 1);
        if(l > m) return query(l, r, m + 1, t, p << 1 | 1);
        return add(query(l, r, s, m, p << 1), query(l, r, m + 1, t, p << 1 | 1), m);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, q, l, r, cnt = 0;
    char op, c;
    std::cin >> n >> m;
    UiT::r = n, UiT::c = m;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < m; j++) std::cin >> UiT::mat[i][j];
    }
    std::cin >> q;
    UiT::buildTree(1, n, 1);
    for(int i = 0; i < q; i++){
        std::cin >> op >> l >> r;
        if(op == 'C'){
            std::cin >> c;
            UiT::updata(l, r - 1, c, 1, n, 1);
        }
        else{
            std::cout <<  UiT::query(l, r, 1, n, 1).cnt << '\n';
        }
    }
    return 0;
}