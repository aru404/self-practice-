// # [CQOI2011] 动态逆序对

// ## 题目描述

// 对于序列 $a$，它的逆序对数定义为集合  
// $$\{(i,j)| i<j \wedge a_i > a_j \}$$
// 中的元素个数。  

// 现在给出 $1\sim n$ 的一个排列，按照某种顺序依次删除 $m$ 个元素，你的任务是在每次删除一个元素**之前**统计整个序列的逆序对数。

// ## 输入格式

// 第一行包含两个整数 $n$ 和 $m$，即初始元素的个数和删除的元素个数。  
// 以下 $n$ 行，每行包含一个 $1 \sim n$ 之间的正整数，即初始排列。  
// 接下来 $m$ 行，每行一个正整数，依次为每次删除的元素。

// ## 输出格式

// 输出包含 $m$ 行，依次为删除每个元素之前，逆序对的个数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 4
// 1
// 5
// 3
// 4
// 2
// 5
// 1
// 4
// 2
// ```

// ### 样例输出 #1

// ```
// 5
// 2
// 2
// 1
// ```

// ## 提示

// 【数据范围】   
// 对于 $100\%$ 的数据，$1\le n \le 10^5$，$1\le m \le 50000$。

// 【样例解释】  
// 删除每个元素之前的序列依次为：  
// $$1,5,3,4,2$$  
// $$1,3,4,2$$  
// $$3,4,2$$  
// $$3,2$$
#include <iostream>
#include <bits/stdc++.h>
#define ll long long
#define lowbit(x) (x & -x)

const int maxN = 1E5 + 5;
int t[maxN], rk[maxN], inv[maxN], s[maxN], s1[maxN], s2[maxN], cnt1[maxN], cnt2[maxN], n;
ll res[maxN], tot = 0;

inline void updata(int x, int v, int* cnt){
    while(x <= n) cnt[x] += v, x += lowbit(x);
}

inline int query(int x, int* cnt){
    int res = 0;
    while(x) res += cnt[x], x -= lowbit(x);
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
    for(int i = l ;i <= r; i++){
        if(t[s1[idx1]] >= t[s2[idx2]]){
            updata(rk[s1[idx1]], 1, cnt1);
            res[s1[idx1]] += idx2 - 1 - query(rk[s1[idx1]], cnt2);
            s[i] = s1[idx1++];
        }
        else{
            updata(rk[s2[idx2]], 1, cnt2);
            res[s2[idx2]] += query(rk[s2[idx2]] - 1, cnt1);
            s[i] = s2[idx2++];
        }
    }
    for(int i = 1; i <= m - l + 1; i++) updata(rk[s1[i]], -1, cnt1);
    for(int i = 1; i <= r - m; i++) updata(rk[s2[i]], -1, cnt2);
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int m, v;
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++){
        std::cin >> v;
        rk[v] = i;
    }
    std::fill_n(t + 1, n, m + 1);
    for(int i = 1; i <= m; i++){
        std::cin >> inv[i];
        t[inv[i]] = i;
    }
    t[0] = -1;
    for(int i = 1; i <= n; i++) s[i] = n - i + 1;
    cdq(1, n);
    for(int i = 1; i <= n; i++) tot += res[i];
    for(int i = 1; i <= m; i++){
        std::cout << tot << std::endl;
        tot -= res[inv[i]];
    }
    return 0; 
}