// # 【模板】三维偏序（陌上花开）

// ## 题目背景

// 这是一道模板题，可以使用 bitset，CDQ 分治，KD-Tree 等方式解决。

// ## 题目描述

// 有 $ n $ 个元素，第 $ i $ 个元素有 $ a_i,b_i,c_i $ 三个属性，设 $ f(i) $ 表示满足 $ a_j \leq a_i $ 且 $ b_j \leq b_i $ 且 $ c_j \leq c_i $ 且 $ j \ne i $ 的 $j$ 的数量。

// 对于 $ d \in [0, n) $，求 $ f(i) = d $ 的数量。

// ## 输入格式

// 第一行两个整数 $ n,k $，表示元素数量和最大属性值。

// 接下来 $ n $ 行，每行三个整数 $ a_i ,b_i,c_i $，分别表示三个属性值。

// ## 输出格式

// $ n $ 行，第 $ d + 1 $ 行表示 $ f(i) = d $ 的 $ i $ 的数量。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 10 3
// 3 3 3
// 2 3 3
// 2 3 1
// 3 1 1
// 3 1 2
// 1 3 1
// 1 1 2
// 1 2 2
// 1 3 2
// 1 2 1
// ```

// ### 样例输出 #1

// ```
// 3
// 1
// 3
// 0
// 1
// 0
// 1
// 0
// 0
// 1
// ```

// ## 提示

// $ 1 \leq n \leq 10^5$，$1 \leq a_i, b_i, c_i \le k \leq 2 \times 10^5 $。
#include <iostream>
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

const int maxN = 1E5 + 5;
int s1[maxN], s2[maxN], s[maxN], tree[maxN], tmp[maxN], rk[maxN], inv[maxN], w[maxN], res[maxN], invRes[maxN], k, cnt;

struct node{
    int a, b, c;
    bool operator== (node& other)const {
        return this->a == other.a && this->b == other.b && this-> c == other.c;
    }
}nodes[maxN];

inline void init(int n){
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int a, const int b){
        if(nodes[a].a ^ nodes[b].a) return nodes[a].a < nodes[b].a;
        if(nodes[a].b ^ nodes[b].b) return nodes[a].b < nodes[b].b;
        if(nodes[a].c ^ nodes[b].c) return nodes[a].c < nodes[b].c;
        return a < b;
    });
    nodes[0].a = nodes[0].b = nodes[0].c = 0X3f3f3f3f;
    int pre = 0;
    for(int i = 1; i <= n; i++){
        if(nodes[tmp[i]] == nodes[pre]) inv[tmp[i]] = inv[pre];
        else pre = tmp[i], inv[tmp[i]] = tmp[i], s[++cnt] = tmp[i];
        ++w[pre];
    }
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int a, const int b){
        return nodes[a].b < nodes[b].b;
    });
    pre = 0, k = 0;
    for(int i = 1; i <= n; i++){
        if(pre != nodes[tmp[i]].b) pre = nodes[tmp[i]].b, ++k;
        rk[tmp[i]] = k;
    }
}

inline void updata(int x, int v){
    while(x <= k) tree[x] += v, x += lowbit(x);
}

inline int query(int x){
    int res = 0;
    while(x) res += tree[x], x -= lowbit(x);
    return res;
}

inline void cdq(int l, int r){
    if(l == r) return ;
    int m = (l + r) >> 1;
    cdq(l, m), cdq(m + 1, r);
    for(int i = l; i <= m; i++) s1[i - l + 1] = s[i];
    for(int i = m + 1; i <= r; i++) s2[i - m] = s[i];
    s1[m - l + 2] = s2[r - m + 1] = 0;
    int idx1 = 1, idx2 = 1;
    for(int i = l; i <= r; i++){
        if(nodes[s1[idx1]].c <= nodes[s2[idx2]].c){
            updata(rk[s1[idx1]], w[s1[idx1]]);
            s[i] = s1[idx1++];
        }
        else{
            res[s2[idx2]] += query(rk[s2[idx2]]);
            s[i] = s2[idx2++];
        }
    }
    for(int i = 1; i <= m - l + 1; i++) updata(rk[s1[i]], -w[s1[i]]);
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n;
    std::cin >> n >> k;
    for(int i = 1; i <= n; i++){
        std::cin >> nodes[i].a >> nodes[i].b >> nodes[i].c;
    }
    init(n);
    cdq(1, cnt);
    for(int i = 1; i <= n; i++) if(w[i]) invRes[res[i] += w[i] - 1] += w[i];
    for(int i = 0; i < n; i++) std::cout << invRes[i] << std::endl;
    return 0;
}