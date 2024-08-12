// # [TJOI2019] 甲苯先生的滚榜

// ## 题目描述

// 甲苯先生在制作一个 Online Judge，他发现做比赛的人们很关心自己的排名（显而易见）。

// 在 ACM 赛制的比赛中，如果通过题目数量不相等，则通过题目数量多的人排名更靠前；  
// 如果通过题目数量相等，则罚时更少的人排名更高。

// 甲苯先生想让大家帮忙设计一个程序，每次有人通过之后，就告诉他排名在他的前面有多少人。  
// （不包括和他罚时题数都相同的同学）

// ## 输入格式

// 第一行输入一个整数 $T$ 表示测试样例的个数。

// 对于每一个样例，输入三个整数 $m, n, \text{seed}$。  
// $m$ 表示参赛总人数（编号 $1 \sim m$），$n$ 表示一共有 $n$ 次 AC（假设 AC 已经去重，即不存在相同人的相同题目提交）。  
// $\text{seed}$ 表示生成数据的种子。

// 接下来要求同学们使用之下的函数生成数据：
// ```cpp
// typedef unsigned int ui ;
// ui randNum( ui& seed , ui last , const ui m){ 
//     seed = seed * 17 + last ; return seed % m + 1; 
// }
// ```
// （$\texttt{last}$ 为上一次输出的结果，在没有输出结果时 $\texttt{last} = 7$，多组数据时 $\texttt{last}$ 不需要重新赋值）  
// 要求每次生成两个数据 $\texttt{Ria}, \texttt{Rib}$，表示第 $\texttt{Ria}$ 个人 AC 了一道题目，他的罚时为 $\texttt{Rib}$。  
// （也就是说 $\texttt{Ria}$ 的题目数量 $+1$，罚时长度 $+\texttt{Rib}$）。

// 要求一共生成 $n$ 组数据，代表一共有 $n$ 次提交。

// 对于所有数据，保证罚时总和不超过 $1.5\times 10^6$。

// ## 输出格式

// 每次提交输出一行整数，表示在第 $\texttt{Ria}$ 个人 AC 后，比 $\texttt{Ria}$ 成绩高的有多少个选手。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 1
// 7 3 1
// ```

// ### 样例输出 #1

// ```
// 0
// 1
// 0
// ```

// ## 提示

// | 测试点# | 1, 2 | 3, 4 | 5 |6, 7, 8 | 9, 10 |
// | :-: | :-: | :-: | :-: | :-: |:-:|
// | $T$ | $\le10$ | $\le5$ | $\le15$ | $\le5$ | $\le5$ |
// | $m$ | $\le1000$ | $\le10000$ | $\le10^5$ | $\le10^4$ |$\le10^5$|
// | $n$ | $\le1000$ | $\le10000$ | $\le10^5$ | $\le10^6$ |$\le10^6$|
#include <iostream>
#include <bits/stdc++.h>

namespace BST{
    #define rs(x) tree[x].rs
    #define ls(x) tree[x].ls
    #define cnt(x) tree[x].cnt
    #define sz(x) tree[x].sz
    #define ac(x) tree[x].ac
    #define t(x) tree[x].time  
    #define rd(x) tree[x].rd

    struct node{
        int ls, rs, cnt, sz, ac, time, rd;
    };
    std::mt19937 rnd(114514);

    class Treap{
    private:
        node* tree;
        std::stack<int> s;
        std::pair<int, int>* memo;
        int root = 0, tot = 0;

        inline void getNode(int&, int, int);

        inline void pushUp(int&);

        inline void split(int, int, int, int&, int&);

        inline int merger(int, int);
    public:
        Treap(int);

        ~Treap();

        inline int updata(int, int);
    };
    
    Treap::Treap(int n){
        tree = new node[n + 1];
        memo = new std::pair<int, int>[n + 1];
        t(0) = ls(0) = rs(0) = cnt(0) = sz(0) = ac(0) = rd(0) = 0;
    }
    
    Treap::~Treap(){
        delete[] tree;
        delete[] memo;
    }

    inline void Treap::getNode(int& x, int ac, int time){
        if(!s.empty()) x = s.top(), s.pop();
        else x = ++tot;
        ls(x) = rs(x) = cnt(x) = sz(x) = 0;
        t(x) = time, ac(x) = ac, rd(x) = rnd();
    }
    
    inline void Treap::pushUp(int& x){
        sz(x) = sz(ls(x)) + sz(rs(x)) + cnt(x);
    }

    inline void Treap::split(int ac, int time, int r, int& x, int& y){
        if(!r){
            x = y = 0;
            return ;
        }
        if(ac > ac(r) || (ac == ac(r) && time <= t(r))) x = r, split(ac, time, rs(r), rs(x), y);
        else y = r, split(ac, time, ls(r), x, ls(y));
        pushUp(r);
        return ;
    }

    inline int Treap::merger(int x, int y){
        if(!x || !y) return x | y;
        if(rd(x) < rd(y)){
            rs(x) = merger(rs(x), y), pushUp(x);
            return x;
        }
        else{
            ls(y) = merger(x, ls(y)), pushUp(y);
            return y;
        }
    }

    inline int Treap::updata(int id, int time){
        int& ac = memo[id].first, &t = memo[id].second;
        int rx = 0, ry = 0, rz = 0, rw = 0;
        split(ac, t, root, rx, ry);
        split(ac, t + 1, rx, rx, rz);
        if(rz){
            --cnt(rz), --sz(rz);
            if(!cnt(rz)) s.emplace(rz), rz = 0;
        }
        
        ac++, t += time;
        rx = merger(rx, rz), rz = 0;

        split(ac, t, ry, ry, rz);
        split(ac, t + 1, ry, ry, rw);
        int res = sz(rz);
        if(!rw) getNode(rw, ac, t);
        ++cnt(rw), ++sz(rw);

        root = merger(rx, merger(merger(ry, rw), rz));
        return res;
    }
}

typedef unsigned int ui;
inline ui randNum(ui& seed, ui last, const ui m){
    seed = seed * 17 + last;
    return seed % m + 1;
}


int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    ui n, m, seed, epoches, last = 7;
    std::cin >> epoches;
    for(ui i = 0; i < epoches; i++){
        std::cin >> m >> n >> seed;
        BST::Treap treap(m);
        for(ui j = 0; j < n; j++){
            int id = randNum(seed, last, m), t = randNum(seed, last, m);
            std::cout << (last = treap.updata(id, t)) << '\n';
        }
    }
    return 0;
}