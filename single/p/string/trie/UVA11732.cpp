// # "strcmp()" Anyone?

// ## 题面翻译

// **【题意】**

// 共 $T$ 组数据，每组数据给出 $n$ 个字符串 $S_i$。对于每组数据，询问 $\sum_{i=1}^n\sum_{j=i+1}^n cnt(\operatorname{strcmp}(i,j))$ 的值。其中 $cnt(\operatorname{strcmp}(i,j))$ 表示对 $S_i,S_j$ 执行一次 $\operatorname{strcmp}$ 函数需要的比较次数，$\operatorname{strcmp}$ 的实现如下：

// ```cpp
// int strcmp(char *s, char *t)
// {
//     int i;
//     for (i=0; s[i]==t[i]; i++)
//         if (s[i]=='\0')
//             return 0;
//     return s[i] - t[i];
// }
// ```

// 注意并不读入 $T$，当 $n=0$ 时表示输入停止。对于第 $i$ 组数据，输出格式为 `Case i: Ans`，其中 `Ans` 表示该组数据对应的答案。

// **【数据范围】**

// $1\le T\le 10$，$1\le n\le4\times10^3$，$1\le |S|\le10^3$，$\Sigma=\{\mathtt{a\sim z},\mathtt{A\sim Z},\mathtt{0\sim 9}\}$，其中 $\Sigma$ 表示可能在 $S$ 中出现的字符集合

// ## 题目描述

// [problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2832

// [PDF](https://uva.onlinejudge.org/external/117/p11732.pdf)

// ![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11732/f9f4156b815a0febb856755194643aee4268928f.png)

// ## 输入格式

// ![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11732/eb2d36585a3a7d37aed581131a6ea2ce899370cb.png)

// ## 输出格式

// ![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11732/8c26b864fca1312c55a0ae313d6d122bb1a75557.png)

// ## 样例 #1

// ### 样例输入 #1

// ```
// 2
// a
// b
// 4
// cat
// hat
// mat
// sir
// 0
// ```

// ### 样例输出 #1

// ```
// Case 1: 1
// Case 2: 6
// ```
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

struct node{
    int cnt, isEnd;
    node** next;

    node(int cnt = 0, int isEnd = 0):cnt(cnt), isEnd(isEnd)
    {
        next = new node*[66]{nullptr};
    }
};

inline int hash(char c){
    if(isalpha(c)) return isupper(c)? c - 'A':c - 'a' + 26;
    return c - '0' + 52;
}

class Trie{
private:
    node* root;
public:
    Trie(){
        root = new node();
    }

    ~Trie(){
        delete root;
    }

    inline ll ins(std::string& s){
        node* r = root;
        ll res = 0;
        ++root->cnt;
        for(auto c:s){
            int h = hash(c);
            if(r->next[h] == nullptr) r->next[h] = new node();
            res += r->cnt - r->next[h]->cnt - 1;
            r = r->next[h];
            res += r->cnt << 1;
            ++r->cnt;
        }
        res += r->isEnd << 1;
        ++r->isEnd;
        return res;
    }
};


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, cnt = 1;
    std::string s;
    do{
        std::cin >> n;
        ll res = 0;
        Trie trie;
        for(int i = 0; i < n; ++i) std::cin >> s, res += trie.ins(s);
        if(n) std::cout << "Case " << cnt << ": " << res << '\n';
        ++cnt;
    }while(n);
    return 0;
}