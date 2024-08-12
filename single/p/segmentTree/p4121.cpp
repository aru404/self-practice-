// # [WC2005] 双面棋盘

// ## 题目描述

// 佳佳有一个 $n$ 行 $n$ 列的黑白棋盘，每个格子都有两面，一面白色，一面黑色。佳佳把棋盘平放在桌子上，因此每个格子恰好一面朝上，如下图所示：

// ![QQ20180116200234.png](https://www.z4a.net/images/2018/01/16/QQ20180116200234.png)

// 我们把每行从上到下编号为 $1$，$2$，$3$，……，$n$，各列从左到右编号为 $1$，$2$，$3$，……，$n$，则每个格子可以用棋盘坐标$(x, y)$表示。在上图中，有 $8$ 个格子黑色朝上，另外 $17$ 个格子白色朝上。

// 如果两个同色格子有一条公共边，我们称这两个同色格子属于同一个连通块。上图共有 $5$ 个黑色连通块和 $3$ 个白色连通块。

// 佳佳可以每分钟将一个格子翻转（即白色变成黑色，黑色变成白色），然后计算当前有多少个黑色连通块和白色连通块，你能算得更快吗？

// ## 输入格式

// 输入文件的第一行包含一个正整数 $n$，为格子的边长。以下 $n$ 行每行 $n$ 个整数，非 $0$ 即 $1$，表示初始状态。$0$ 表示白色，$1$ 表示黑色。  

// 下一行包含一个整数 $m$，表示操作的数目。以下 $m$ 行每行两个整数 $x$, $y$ ( $1 \le x,y \le n$ )，表示把坐标为 $(x, y)$ 的格子翻转。

// ## 输出格式

// 输出文件包含 $m$ 行，每行对应一个操作。该行包括两个整数 $b$, $w$，表示黑色区域和白色区域数目。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5
// 0 1 0 0 0
// 0 1 1 1 0
// 1 0 0 0 1
// 0 0 1 0 0
// 1 0 0 0 0
// 2
// 3 2
// 2 3
// ```

// ### 样例输出 #1

// ```
// 4 3
// 5 2
// ```

// ## 提示

// 【样例说明】

// 翻转 $(3, 2)$ 之后，棋盘变为：

// ![QQ20180116200629.png](https://www.z4a.net/images/2018/01/16/QQ20180116200629.png)

// 有 $4$ 个黑色区域和 $3$ 个白色区域

// 翻转 $(2, 3)$ 之后，棋盘变为：

// ![QQ20180116200639.png](https://www.z4a.net/images/2018/01/16/QQ20180116200639.png)

// 有 $5$ 个黑色区域和 $2$ 个白色区域

// 【数据范围】   
// 对于 $100\%$ 的数据，$1\le n \le 200$，$1\le m \le 10^4$。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 205;
bool col[maxN][maxN];

namespace Tit{
    int n;
    class UFS{
        private:
            int *fa; 
        public:
            UFS(int m = 0);
            
            // ~UFS();

            inline int find(int);

            inline void merger(int, int);

            inline void modify(int);
    };

    UFS::UFS(int m){
        fa = new int[m + 1];
    }

    // UFS::~UFS(){
    //     delete[] fa;
    // }

    inline int UFS::find(int x){
        return x == fa[x]? x:(fa[x] = find(fa[x]));
    }

    inline void UFS::merger(int x, int y){
        fa[x] = y;
    }

    inline void UFS::modify(int x){
        fa[x] = x;
    }

    UFS ufs;

    struct seg{
        int w, b;
        int ls[maxN], rs[maxN];
    }tree[maxN << 2];

    inline void pushUp(int p, int m){
        for(int i = 1; i <= n; i++){
            tree[p].ls[i] = tree[p << 1].ls[i];
            tree[p].rs[i] = tree[p << 1 | 1]. rs[i];
            ufs.modify(tree[p << 1].ls[i]), ufs.modify(tree[p << 1].rs[i]);
            ufs.modify(tree[p << 1 | 1].ls[i]), ufs.modify(tree[p << 1 | 1].rs[i]);
        }
        tree[p].b = tree[p << 1].b + tree[p << 1 | 1].b;
        tree[p].w = tree[p << 1].w + tree[p << 1 | 1].w;
        for(int i = 1; i <= n; i++){
            if(col[m][i] == col[m + 1][i]){
                int x = ufs.find(tree[p << 1].rs[i]), y = ufs.find(tree[p << 1 | 1].ls[i]);
                if(x != y){
                    ufs.merger(x, y);
                    if(col[m][i]) tree[p].b--;
                    else tree[p].w--;
                }
            }
        }
        for(int i = 1; i <= n; i++){
            tree[p].ls[i] = ufs.find(tree[p].ls[i]), tree[p].rs[i] = ufs.find(tree[p].rs[i]);
        }
    }

    inline void buildTree(int s, int t, int p){
        if(s == t){
            tree[p].b = tree[p].w = 0;
            for(int i = 1; i <= n; i++){
                ufs.modify(n * (s - 1) + i);
                if(col[s][i]) tree[p].b++;
                else tree[p].w++;
            }
            for(int i = 1; i <= n - 1; i++){
                if(col[s][i] == col[s][i + 1]){
                    ufs.merger(ufs.find(n * (s - 1) + i), ufs.find(n * (s - 1) + i + 1));
                    if(col[s][i]) tree[p].b--;
                    else tree[p].w--;
                }
            }
            for(int i = 1; i <= n; i++){
                tree[p].ls[i] = tree[p].rs[i] = ufs.find(n * (s - 1) + i);
            }
            return ;
        }
        int m = (t + s) >> 1;
        buildTree(s, m, p << 1);
        buildTree(m + 1, t, p << 1 | 1);
        pushUp(p, m);
    }

    inline void updataRev(int x, int y, int s, int t, int p){
        if(s == t){
            col[x][y] = !col[s][y];
            tree[p].b = tree[p].w = 0;
            for(int i = 1; i <= n; i++){
                ufs.modify(n * (s - 1) + i);
                if(col[s][i]) tree[p].b++;
                else tree[p].w++;
            }
            for(int i = 1; i <= n - 1; i++){
                if(col[s][i] == col[s][i + 1]){
                    ufs.merger(ufs.find(n * (s - 1) + i), ufs.find(n * (s - 1) + i + 1));
                    if(col[s][i]) tree[p].b--;
                    else tree[p].w--;
                }
            }
            for(int i = 1; i <= n; i++){
                tree[p].ls[i] = tree[p].rs[i] = ufs.find(n * (s - 1) + i);
            }
            return ;           
        }
        int m = (t + s) >> 1;
        if(x <= m) updataRev(x, y, s, m, p << 1);
        else updataRev(x, y, m + 1, t, p << 1 | 1);
        pushUp(p, m);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, c, r;
    std::cin >> n;
    Tit::n = n;
    Tit::ufs = Tit::UFS(n * n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++) std::cin >> col[i][j];
    }
    Tit::buildTree(1, n, 1);
    std::cin >> m;
    for(int i = 1; i <= m; i++){
        std::cin >> r >> c;
        Tit::updataRev(r, c, 1, n, 1);
        std::cout << Tit::tree[1].b << ' ' << Tit::tree[1].w << '\n';
    }
    return 0;
}