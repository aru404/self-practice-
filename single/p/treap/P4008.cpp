// // # [NOI2003] 文本编辑器

// ## 题目描述

// 很久很久以前，$DOS3.x$ 的程序员们开始对 $EDLIN$ 感到厌倦。于是，人们开始纷纷改用自己写的文本编辑器⋯⋯

// 多年之后，出于偶然的机会，小明找到了当时的一个编辑软件。进行了一些简单的测试后，小明惊奇地发现：那个软件每秒能够进行上万次编辑操作（当然，你不能手工进行这样的测试） ！于是，小明废寝忘食地想做一个同样的东西出来。你能帮助他吗？

// 为了明确目标，小明对“文本编辑器”做了一个抽象的定义:

// 文本：由 $0$ 个或多个 ASCII 码在闭区间 [$32$, $126$] 内的字符构成的序列。

// 光标：在一段文本中用于指示位置的标记，可以位于文本首部，文本尾部或文本的某两个字符之间。


// 文本编辑器：由一段文本和该文本中的一个光标组成的，支持如下操作的数据结构。如果这段文本为空，我们就说这个文本编辑器是空的。

// | 操作名称  | 输入文件中的格式  | 功能  |
// | :------------ | :------------ | :------------ |
// | $\text{Move}(k)$  | Move k  |  将光标移动到第 $k$ 个字符之后，如果 $k=0$，将光标移到文本开头 |
// | $\text{Insert}(n,s)$  | Insert n s  | 在光标处插入长度为 $n$ 的字符串 $s$，光标位置不变$n\geq1$|
// | $\text{Delete}(n)$  | Delete n  | 删除光标后的 $n$ 个字符，光标位置不变，$n \geq 1$  |
// | $\text{Get}(n)$  | Get n  |输出光标后的 $n$ 个字符，光标位置不变，$n \geq 1$   |
// | $\text{Prev}()$  | Prev  | 光标前移一个字符  |
// | $\text{Next}()$  | Next |  光标后移一个字符 |


// 你的任务是：

// - 建立一个空的文本编辑器。

// - 从输入文件中读入一些操作并执行。

// - 对所有执行过的 `GET` 操作，将指定的内容写入输出文件。

// ## 输入格式

// 输入文件 `editor.in` 的第一行是指令条数 $t$，以下是需要执行的 $t$ 个操作。其中：

// 为了使输入文件便于阅读， `Insert` 操作的字符串中可能会插入一些回车符， 请忽略掉它们（如果难以理解这句话，可以参照样例） 。

// 除了回车符之外，输入文件的所有字符的 ASCII 码都在闭区间 [$32$, $126$] 内。且

// 行尾没有空格。

// 这里我们有如下假定：

// -  `MOVE` 操作不超过 $50000$ 个， `INSERT` 和 `DELETE` 操作的总个数不超过 $4000$，`PREV` 和 `NEXT` 操作的总个数不超过 $200000$。

// -  所有 `INSERT` 插入的字符数之和不超过 $2M$（$1M=1024\times 1024$ 字节） ，正确的输出文件长度不超过 $3M$ 字节。

// -  `DELETE` 操作和 `GET` 操作执行时光标后必然有足够的字符。 `MOVE` 、 `PREV` 、 `NEXT` 操作必然不会试图把光标移动到非法位置。

// -  输入文件没有错误。

// 对 C++ 选手的提示：经测试，最大的测试数据使用 `fstream` 进行输入有可能会比使用 `stdio` 慢约 $1$ 秒。

// ## 输出格式

// 输出文件 editor.out 的每行依次对应输入文件中每条 `Get` 指令的输出。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 15
// Insert 26
// abcdefghijklmnop
// qrstuv wxy
// Move 15
// Delete 11
// Move 5
// Insert 1
// ^
// Next
// Insert 1
// _
// Next
// Next
// Insert 4
// .\/.
// Get 4
// Prev
// Insert 1
// ^
// Move 0
// Get 22
// ```

// ### 样例输出 #1

// ```
// .\/.
// abcde^_^f.\/.ghijklmno
// ```
#include <iostream>
#include <bits/stdc++.h>

inline void read(int n, std::string& s){
    s.clear();
    char c;
    while(n){
        c = getchar();
        if(c < 32 || c > 126 || c == '\n' || c == '\r') continue;
        s.push_back(c);
        --n;
    }
}

inline void read(std::string& s){
    s.clear();
    char c = getchar();
    while(c == ' ' || c == '\n' || c == '\r') c = getchar();
    while(c != ' ' && c != '\n' && c != '\r') s.push_back(c), c = getchar();
}

inline void read(int& x){
    x = 0; bool f = 0; char c = getchar();
    while(c < '0' || c > '9') f = c == '-', c = getchar();
    while(c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    if(f) x = -x;
}

namespace BST{
    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define sz(x) tree[x].sz
    #define rd(x) tree[x].rd
    #define v(x) tree[x].val

    struct node{
        int ls, rs, sz, rd;
        char val;
    };

    std::mt19937 rnd(114514);

    class Treap{
        private:
            int tot = 0, root = 0, rx = 0, ry = 0, rz = 0, idx = 0;
            std::stack<int> stk;
            node* tree;

            inline int getNode(char);

            inline void pushUp(int&);

            inline void split(int, int, int&, int&);

            inline int merger(int, int);

            inline void reclaim(int);
        public:
            Treap(int);

            ~Treap();

            inline void move(int);

            inline void ins(int, std::string&);

            inline void del(int);

            inline void pre();

            inline void next();

            inline std::string get(int);
    };

    Treap::Treap(int n){
        tree = new node[n + 1];
        ls(0) = rs(0) = rd(0) = sz(0) = 0;
    }

    Treap::~Treap(){
        delete[] tree;
    }

    inline int Treap::getNode(char c){
        int x;
        if(!stk.empty()) x = stk.top(), stk.pop();
        else x = ++tot;
        rs(x) = ls(x) = 0, sz(x) = 1, rd(x) = rnd();
        v(x) = c;
        return x;
    }

    inline void Treap::pushUp(int& x){
        sz(x) = sz(ls(x)) + sz(rs(x)) + 1;
    }

    inline void Treap::split(int k, int r, int& x, int& y){
        if(!r){
            x = y = 0;
            return ;
        }
        if(k > sz(ls(r))) x = r, split(k - sz(ls(r)) - 1, rs(r), rs(x), y);
        else y = r, split(k, ls(r), x, ls(y));
        pushUp(r);
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

    inline void Treap::reclaim(int r){
        if(!r) return ;
        reclaim(ls(r)), reclaim(rs(r));
        stk.emplace(r);
    }

    inline void Treap::move(int k){
        if(k > idx){
            split(k - idx, ry, rz, ry);
            rx = merger(rx, rz);
        }
        else{
            split(k, rx, rx, rz);
            ry = merger(rz, ry);
        }
        idx = k;
    }

    inline void Treap::ins(int n, std::string& s){
        rz = 0;
        for(int i = 0; i < n; i++){
            rz = merger(rz, getNode(s[i]));
        }
        ry = merger(rz, ry);
    }

    inline void Treap::del(int n){
        split(n, ry, rz, ry);
        reclaim(rz);
    }

    inline std::string Treap::get(int n){
        std::string res = "";
        split(n, ry, rz, ry);

        std::function<void(int)> dfs = [&](int r){
            if(!r) return ;
            dfs(ls(r)), res.push_back(v(r)), dfs(rs(r));
        };

        dfs(rz);
        ry = merger(rz, ry);
        return res;
    }

    inline void Treap::pre(){
        split(--idx, rx, rx, rz);
        ry = merger(rz, ry);
    }

    inline void Treap::next(){
        ++idx;
        split(1, ry, rz, ry);
        rx = merger(rx, rz);
    }
}

const int maxN = 2.1E6;

int main(){
    int t, k;
    std::string op, s;
    read(t);
    BST::Treap treap(maxN);
    for(int i = 0; i < t; i++){
        read(op);
        if(op[0] == 'M') read(k), treap.move(k);
        else if(op[0] == 'I') read(k), read(k, s), treap.ins(k, s);
        else if(op[0] == 'D') read(k), treap.del(k);
        else if(op[0] == 'G') read(k), std::cout << treap.get(k) << '\n';
        else if(op[0] == 'P') treap.pre();
        else if(op[0] == 'N') treap.next();
    }
    return 0;
}