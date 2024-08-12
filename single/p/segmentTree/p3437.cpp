// # [POI2006] TET-Tetris 3D

// ## 题面翻译

// ### 题目描述

// 最近，有人发明了一种三维版的俄罗斯方块。和二维版本类似，一些立方体按照一定的顺序掉落，直到碰到别的方块或是地面才会停止掉落。立方体停止掉落后会一直保持掉落时的位置，直到游戏结束。

// 你的朋友决定以这个新版本的俄罗斯方块为背景，出一道题。给出每个立方体的掉落顺序和其掉落的轨迹，在所有方块完成掉落后求出最高方块的高度。在这个游戏中，方块均垂直下落，且方块不会旋转或翻转。为了方便描述，我们会建立一个空间直角坐标系，该坐标系的原点为地面的一角，并且坐标轴与地面边缘平行。

// 现在轮到你解决这个问题了。

// ### 输入格式

// 第一行三个整数 $D,S,N$，分别为地面的长度，宽度，和将要掉落的立方体数量。

// 接下来 $N$ 行，每行五个整数 $d_i,s_i,w_i,x_i,y_i$，描述一个掉落的立方体。其中 $d_i,s_i,w_i$ 分别代表立方体的长，宽，高。立方体的底面（即长 $\times$ 宽的那一面）将正对地面。立方体底面四个角在地面的投影坐标分别为 $(x_i,y_i)$，$(x_i+d_i,y_i)$，$(x_i,y_i+s_i)$，$(x_i+d_i,y_i+s_i)$。

// ### 输出格式

// 输出一个整数，即方块掉落结束后最高方块的高度。

// ### 数据范围

// $1 \leq N \leq 20\,000$，$1 \leq D,S \leq 1\,000$，$d_i,s_i \geq 1$，$1 \leq w_i \leq 100\,000$，$0 \leq x_i,d_i+x_i \leq D$，$0 \leq y_i,s_i+y_i \leq S$。

// ## 题目描述

// The authors of the game "Tetris" have decided to make a new, three-dimensional version, in which cuboids would fall down on a rectangular platform. The blocks fall down separately in a certain order, just like in the two-dimensional game. A block falls down until it reaches an obstacle: the platform or another block, that has already stopped - then it stops and remains in this exact position till the game is over.

// However, the authors wanted to change the spirit of the game, turning it from a simple arcade-game into a play far more puzzling. Knowing the order of the falling blocks and their flight path the player's task is to tell the height of the highest point of the arrangement after all blocks have fallen down (and stopped). All the blocks are falling down vertically and do not rotate while falling. For convenience we'll introduce a cartesian coordinate system on the platform, with the center in one of the platform's corners and the axes parallel to the platform's edges.

// Write a programme that automates verification of the player's answer.

// TaskWrite a programme that:

// reads the descriptions of subsequent falling blocks from the standard input,determines the height of the highest point of the arrangement of blocks after all have fallen down and stopped,writes the result to the standard output.

// ## 输入格式

// In the first line of the input there are three integers $D$, $S$ and $N$ ($1\le N\le 20\ 000$, $1\le D,S\le 1\ 000$), separated by single spaces and denoting respectively: the length and the depth of the platform and the number of blocks that are going to fall down on it. In the following $N$ lines the descriptions of subsequent blocks are given, one in each line.

// Each description of a block consists of five integers: $d$,$s$,$w$,$x$ and $y$ ($1\le d$, $0\le x$, $d+x\le D$, $1\le s$, $0\le y$, $s+y\le S$, $1\le w\le 100\ 000$), representing a block of length $d$ depth $s$ and height $w$. This very block will be be falling down on the platform with its $d\times s$ face as the bottom, where the length and depth of the block are parallel to those of the platform. The coordinates of the vertices of the projection of the block on the platform are: $(x,y)$, $(x+d,y)$, $(x,y+s)$ and $(x+d,y+s)$.

// ## 输出格式

// The first and only line of the standard output should contain exactly one integer, the height of the highest point of the arrangement of blocks after all have fallen down and stopped.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 7 5 4
// 4 3 2 0 0
// 3 3 1 3 0
// 7 1 2 0 3
// 2 3 3 2 2
// ```

// ### 样例输出 #1

// ```
// 6
// ```
// 树套树，写个四叉树的复杂度是假的（单次O(m + n)）
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E3 + 5;

namespace TiT{
    class Tree1{
        public:
        int mx[maxN << 2], tag[maxN << 2];

        void updata(int l, int r, int v, int s, int t, int p){
            mx[p] = std::max(v, mx[p]);
            if(l <= s && r >= t){
                tag[p] = std::max(tag[p], v);
                return ;
            }
            int m = (t + s) >> 1;
            if(l <= m) updata(l, r, v, s, m, p << 1);
            if(r > m) updata(l, r, v, m + 1, t, p << 1 | 1);
        }

        int query(int l, int r, int s, int t, int p){
            if(l <= s && r >= t) return mx[p];
            int m = (t + s) >> 1, res = tag[p];
            if(l <= m) res = std::max(res, query(l, r, s, m, p << 1));
            if(r > m) res = std::max(res, query(l, r, m + 1, t, p << 1 | 1));
            return res;
        }
    };

    class Tree2{
        private:
            int n, m;
        public:
            Tree1 *mx, *tag;
            Tree2(int n, int m): n(n), m(m){
                mx = (Tree1*)malloc(sizeof(Tree1) * (n << 2));
                tag = (Tree1*)malloc(sizeof(Tree1) * (n << 2));
            }

            inline void updata(int l1, int r1, int l2, int r2, int v, int s, int t, int p){
                mx[p].updata(l2, r2, v, 1, m, 1);
                if(l1 <= s && r1 >= t){
                    tag[p].updata(l2, r2, v, 1, m, 1);
                    return ;
                }
                int mid = (t + s) >> 1;
                if(l1 <= mid) updata(l1, r1, l2, r2, v, s, mid, p << 1);
                if(r1 > mid) updata(l1, r1, l2, r2, v, mid + 1, t, p << 1 | 1);
            }

            inline int query(int l1, int r1, int l2, int r2, int s, int t, int p){
                if(l1 <= s && r1 >= t) return mx[p].query(l2, r2, 1, m, 1);
                int mid = (t + s) >> 1, res = tag[p].query(l2, r2, 1, m, 1);
                if(l1 <= mid) res = std::max(res, query(l1, r1, l2, r2, s, mid, p << 1));
                if(r1 > mid) res = std::max(res, query(l1, r1, l2, r2, mid + 1, t, p << 1 | 1));
                return res;
            }
    };
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int d, s, n, x, y, dx, dy, h;
    std::cin >> d >> s >> n;
    TiT::Tree2 tree(d, s);
    for(int i = 0; i < n; i++){
        std::cin >> dx >> dy >> h >> x >> y;
        int mxH = tree.query(x + 1, x + dx, y + 1, y + dy, 1, d, 1);
        tree.updata(x + 1, x + dx, y + 1, y + dy, mxH + h, 1, d, 1);
    }
    std::cout << tree.query(1, d, 1, s, 1, d, 1);
    return 0;
}