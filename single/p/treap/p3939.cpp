// # 数颜色

// ## 题目背景

// 大样例可在页面底部「附件」中下载。

// ## 题目描述

// 小 C 的兔子不是雪白的，而是五彩缤纷的。每只兔子都有一种颜色，不同的兔子可能有 相同的颜色。小 C 把她标号从 1 到 $n$ 的 $n$ 只兔子排成长长的一排，来给他们喂胡萝卜吃。 排列完成后，第 $i$ 只兔子的颜色是 $a_i$。

// 俗话说得好，“萝卜青菜，各有所爱”。小 C 发现，不同颜色的兔子可能有对胡萝卜的 不同偏好。比如，银色的兔子最喜欢吃金色的胡萝卜，金色的兔子更喜欢吃胡萝卜叶子，而 绿色的兔子却喜欢吃酸一点的胡萝卜……为了满足兔子们的要求，小 C 十分苦恼。所以，为 了使得胡萝卜喂得更加准确，小 C 想知道在区间 $[l_j,r_j]$ 里有多少只颜色为 $c_j$ 的兔子。

// 不过，因为小 C 的兔子们都十分地活跃，它们不是很愿意待在一个固定的位置；与此同 时，小 C 也在根据她知道的信息来给兔子们调整位置。所以，有时编号为 $x_j$ 和 $x_j+1$ 的两 只兔子会交换位置。  小 C 被这一系列麻烦事给难住了。你能帮帮她吗？

// ## 输入格式

// 从标准输入中读入数据。 输入第 1 行两个正整数 $n$,$m$。

// 输入第 2 行 $n$ 个正整数，第 $i$ 个数表示第 $i$ 只兔子的颜色 $a_i$。

// 输入接下来 $m$ 行，每行为以下两种中的一种：

// - “$1\ l_j\ r_j\ c_j$” ：询问在区间 $[l_j,r_j]$ 里有多少只颜色为 $c_j$ 的兔子；

// - “$2\ x_j$”： $x_j$ 和 $x_j+1$ 两只兔子交换了位置。

// ## 输出格式

// 输出到标准输出中。

// 对于每个 1 操作，输出一行一个正整数，表示你对于这个询问的答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 6 5 
// 1 2 3 2 3 3  
// 1 1 3 2 
// 1 4 6 3  
// 2 3 
// 1 1 3 2  
// 1 4 6 3
// ```

// ### 样例输出 #1

// ```
// 1 
// 2 
// 2 
// 3
// ```

// ## 提示

// 【样例 1 说明】

// 前两个 1 操作和后两个 1 操作对应相同；在第三次的 2 操作后，3 号兔子和 4 号兔子

// 交换了位置，序列变为 1 2 2 3 3 3。

// 【数据范围与约定】

// 子任务会给出部分测试数据的特点。如果你在解决题目中遇到了困难，可以尝试只解 决一部分测试数据。 对于所有测试点，有 $1 \le l_j < r_j \le n,1 \le x_j < n$。 每个测试点的数据规模及特点如下表：

//  ![](https://cdn.luogu.com.cn/upload/pic/9808.png) 

// 特殊性质 1：保证对于所有操作 1，有 $|r_j - l_j| \le 20$ 或 $|r_j - l_j| \le n - 20$。

// 特殊性质 2：保证不会有两只相同颜色的兔子。
#include <bits/stdc++.h>

const int maxN = 5E5 + 5;

class Treap
{
private:
    struct node
    {
        int ls, rs, sz, rd;
    }*tree;

    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define sz(x) tree[x].sz
    #define rd(x) tree[x].rd

    int *root, *colors, cnt; 
    static std::mt19937 rnd;

    inline void pushUp(int x);

    inline void split(int idx, int r, int &x, int &y);

    inline int merge(int x, int y);
public:
    explicit Treap(int n);

    ~Treap();

    inline void ins(int c);

    inline void swap(int idx1, int idx2);

    inline int query(int l, int r, int c);
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, c, t, l, r;
    std::cin >> n >> m;
    Treap treap(n);
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> c;
        treap.ins(c);
    }

    for(int i = 0; i < m; ++i)
    {
        std::cin >> t >> l;
        if(t == 1)
        {
            std::cin >> r >> c;
            std::cout << treap.query(l, r, c) << '\n';
        }
        else treap.swap(l, l + 1);
    }
    return 0;
}

std::mt19937 Treap::rnd(std::chrono::system_clock::now().time_since_epoch().count());

Treap::Treap(int n): cnt(0)
{
    root = new int[maxN]{};
    colors = new int[n + 10]{};
    tree = new node[n + 10];
    tree[0] = node{0, 0, 0, 0};
}

Treap::~Treap()
{
    delete[] root;
    delete[] colors;
    delete[] tree;    
}

void Treap::pushUp(int x)
{
    sz(x) = sz(ls(x)) + sz(rs(x)) + 1;
}

void Treap::split(int idx, int r, int &x, int &y)
{
    if(!r)
    {
        x = y = 0;
        return ;
    }
    if(r <= idx)
    {
        x = r;
        split(idx, rs(r), rs(x), y);
    }
    else
    {
        y = r;
        split(idx, ls(r), x, ls(y));
    }
    pushUp(r);
}

int Treap::merge(int x, int y)
{
    if(!x || !y) return x | y;
    if(rd(x) < rd(y))
    {
        rs(x) = merge(rs(x), y);
        pushUp(x);
        return x;
    }
    else
    {
        ls(y) = merge(x, ls(y));
        pushUp(y);
        return y;
    }
}

void Treap::ins(int c)
{
    tree[++cnt] = node{0, 0, 1, static_cast<int>(rnd())};
    colors[cnt] = c;
    root[c] = merge(root[c], cnt);
}

void Treap::swap(int idx1, int idx2)
{
    int rx, ry, rz, rw;
    split(idx1, root[colors[idx1]], rx, ry);
    split(idx1 - 1, rx, rx, rz);
    root[colors[idx1]] = merge(rx, ry);

    split(idx2, root[colors[idx2]], rx, ry);
    split(idx2 - 1, rx, rx, rw);
    root[colors[idx2]] = merge(rx, ry);

    split(idx2, root[colors[idx1]], rx, ry);
    root[colors[idx1]] = merge(merge(rx, rw), ry);
    split(idx1, root[colors[idx2]], rx, ry);
    root[colors[idx2]] = merge(merge(rx, rz), ry);
    std::swap(colors[idx1], colors[idx2]);
}

int Treap::query(int l, int r, int c)
{
    int rx, ry, rz;
    split(r, root[c], rx, ry);
    split(l - 1, rx, rx, rz);
    int res = sz(rz);
    root[c] = merge(merge(rx, rz), ry);
    return res;
}