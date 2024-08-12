// # [NOI2004] 郁闷的出纳员

// ## 题目描述

// OIER 公司是一家大型专业化软件公司，有着数以万计的员工。作为一名出纳员，我的任务之一便是统计每位员工的工资。这本来是一份不错的工作，但是令人郁闷的是，我们的老板反复无常，经常调整员工的工资。如果他心情好，就可能把每位员工的工资加上一个相同的量。反之，如果心情不好，就可能把当前在公司的所有员工的工资扣除一个相同的量。我真不知道除了调工资他还做什么其它事情。

// 工资的频繁调整很让员工反感，尤其是集体扣除工资的时候，一旦某位员工发现自己的工资已经低于了合同规定的工资下界，他就会立刻气愤地离开公司，并且再也不会回来了。每位员工的工资下界都是统一规定的。每当一个人离开公司，我就要从电脑中把他的工资档案删去，同样，每当公司招聘了一位新员工，我就得为他新建一个工资档案。

// 老板经常到我这边来询问工资情况，他并不问具体某位员工的工资情况，而是问现在工资第 $k$ 多的员工拿多少工资。每当这时，我就不得不对数万个员工进行一次漫长的排序，然后告诉他答案。

// 好了，现在你已经对我的工作了解不少了。正如你猜的那样，我想请你编一个工资统计程序。怎么样，不是很困难吧？

// 如果某个员工的初始工资低于最低工资标准，那么将不计入最后的答案内。

// ## 输入格式

// 第一行有两个整数 $n$ 和 $\min$。$n$ 表示下面有多少条命令，$\min$ 表示工资下界。

// 接下来的 $n$ 行，每行一个字符 $x$ 和一个整数 $k$，表示一条命令。命令可以是以下四种之一：

// - `I k`  新建一个工资档案，初始工资为 $k$。如果某员工的初始工资低于工资下界，他将立刻离开公司。
// - `A k`   把每位员工的工资加上 $k$。
// - `S k`   把每位员工的工资扣除 $k$。
// - `F k`    查询第 $k$ 多的工资。

// 在初始时，可以认为公司里一个员工也没有。

// ## 输出格式

// 对于每条 `F` 命令，你的程序要输出一行，仅包含一个整数，为当前工资第  $k$ 多的员工所拿的工资数，如果 $k$ 大于目前员工的数目，则输出 $-1$。

// 输出的最后一行包含一个整数，为离开公司的员工的总数。

// 请注意，初始工资低于工资下界的员工不算做离开公司的员工。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 9 10
// I 60
// I 70
// S 50
// F 2
// I 30
// S 15
// A 5
// F 1
// F 2
// ```

// ### 样例输出 #1

// ```
// 10
// 20
// -1
// 2
// ```

// ## 提示

// #### 数据规模与约定

// 对于全部的测试点，保证：

// - `I` 命令的条数不超过 $10^5$；
// - `A` 和 `S` 命令的总条数不超过 $100$；
// - `F` 命令的条数不超过 $10^5$；
// - 每次工资调整的调整量不超过 $10^3$；
// - 新员工的工资不超过 $10^5$。
// - $0 \leq n \leq 3 \times 10^5$，$0 \leq \text{min} \leq 10^9$，输入的所有数字均在 $32$ 位带符号整形范围内。
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E5 + 5, inf = INT32_MAX;

namespace BST{
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define sz(x) tree[x].sz
    #define cnt(x) tree[x].cnt
    #define v(x) tree[x].val
    #define lz(x) tree[x].lz
    #define rd(x) tree[x].rd
    #define ch(x, k) (k? rs(x):ls(x))

    struct node{
        int ls, rs, sz, cnt, val, lz, rd;
    };
    std::mt19937 rnd(114514);

    class Treap{
        private:
            int root = 0, rx = 0, ry = 0, rz = 0, tot = 0, min;
            node* tree;

            inline void getNode(int&, int);

            inline void pushUp(int&);

            inline void pushDown(int&);

            inline void split(int, int, int&, int&);

            inline int merger(int, int);

            inline int query(int, int);
        public:
            Treap(int, int);

            ~Treap();

            inline void ins(int);

            inline void add(int);

            inline void reduce(int);

            inline int query(int);

            inline node& top();
    };

    Treap::Treap(int n, int m):min(m){
        tree = new node[n + 5];
        ls(0) = rs(0) = sz(0) = cnt(0) = 0;
    }

    Treap::~Treap(){
        delete[] tree;
    }

    inline void Treap::getNode(int& x, int val){
        x = ++tot;
        ls(x) = rs(x) = sz(x) = cnt(x) = lz(x) = 0, v(x) = val;
        rd(x) = rnd();
    }

    inline void Treap::pushUp(int& x){
        sz(x) = sz(ls(x)) + sz(rs(x)) + cnt(x);
    }

    inline void Treap::pushDown(int& x){
        if(lz(x)){
            if(ls(x)) v(ls(x)) += lz(x), lz(ls(x)) += lz(x);
            if(rs(x)) v(rs(x)) += lz(x), lz(rs(x)) += lz(x);
            lz(x) = 0; 
        }
    }

    inline void Treap::split(int key, int r, int& x, int& y){
        if(!r){
            x = y = 0;
            return ;
        }
        pushDown(r);
        if(v(r) <= key) x = r, split(key, rs(r), rs(x), y);
        else y = r, split(key, ls(r), x, ls(y));
        pushUp(r);
    }

    inline int Treap::merger(int x, int y){
        if(!x || !y) return x | y;
        pushDown(x), pushDown(y);
        if(rd(x) < rd(y)){
            rs(x) = merger(rs(x), y), pushUp(x);
            return x;
        }
        else{
            ls(y) = merger(x, ls(y)), pushUp(y);
            return y;
        }
    }

    inline void Treap::ins(int val){
        split(val, root, rx, ry);
        split(val - 1, rx, rx, rz);
        if(!rz) getNode(rz, val);
        ++cnt(rz), ++sz(rz);
        root = merger(merger(rx, rz), ry);
    }

    inline void Treap::add(int val){
        if(root) lz(root) += val, v(root) += val;
    }

    inline void Treap::reduce(int val){
        split(min + val - 1, root, rx, ry);
        root = ry;
        if(root) v(root) -= val, lz(root) -= val;
    }

    inline int Treap::query(int x, int rk){
        if(!x) return -1;
        pushDown(x);
        if(rk <= sz(rs(x))) return query(rs(x), rk);
        else if(rk > cnt(x) + sz(rs(x))) return query(ls(x), rk - cnt(x) - sz(rs(x)));
        return v(x);
    }

    inline int Treap::query(int rk){
        return rk > sz(root)? -1:query(root, rk);
    }

    inline node& Treap::top(){
        return tree[root];
    }
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, m, k;
    char op;
    std::cin >> n >> m;
    BST::Treap treap(n, m);
    for(int i = 0; i < n; i++){
        std::cin >> op >> k;
        if(op == 'I'){
            if(k >= m) treap.ins(k);
        }
        else if(op == 'S') treap.reduce(k);
        else if(op == 'A') treap.add(k);
        else if(op == 'F') std::cout << treap.query(k) << '\n';
    }
    std::cout << treap.top().sz;
    return 0;
}