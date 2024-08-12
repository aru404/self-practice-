// # [CH弱省胡策R2] TATT

// ## 题目描述

// 四维空间真是美妙。现在有 $n$ 个四维空间中的点，请求出一条最长的路径，满足任意一维坐标都是单调不降的。

// 注意路径起点是任意选择的，并且路径与输入顺序无关（路径顺序不一定要满足在输入中是升序）。

// **路径的长度是经过的点的数量，任意点只能经过一次。**

// ## 输入格式

// 第一行一个整数 $n$。接下来 $n$ 行，每行四个整数 $a_i,b_i,c_i,d_i$。表示四维坐标。

// ## 输出格式

// 一行一个整数，表示最长路径的长度。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4
// 2 3 33 2333
// 2 3 33 2333
// 2 3 33 2333
// 2 3 33 2333
// ```

// ### 样例输出 #1

// ```
// 4
// ```

// ## 提示

// 记 $m_i=\max(|a_i|,|b_i|,|c_i|,|d_i|),m=\max(m_i)$
// |  测试点编号| $n\le$ | $m\le$ | 特殊说明 |
// | :----------: | :----------: | :----------: | :----------: |
// | $1$ | $2000$ | $10^9$ |  |
// | $2$ |$5\times 10^4$  | $8$ |  |
// | $3\sim 4$ | $5\times 10^4$ | $10^5$ |  所有点的第三，四维坐标相同|
// | $5\sim 6$| $5\times 10^4$ | $10^5$ |  所有点的第四维坐标相同 |
// | $7\sim 8$ | $5\times 10^4$ |$100$  |  |
// |  $9\sim 10$| $5\times 10^4$ | $10^9$ |  |
// 记得用stable_sort,sort对于相同点有时会出现换位的情况
#include <iostream>
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define a(x) nodes[x].a
#define b(x) nodes[x].b
#define c(x) nodes[x].c
#define d(x) nodes[x].d

const int maxN = 5E4 + 5, inf = 0X3f3f3f3f;
int mx1[maxN], mx2[maxN], tmp[maxN], s[maxN], s1[maxN], s2[maxN], rk[maxN], cnt1[maxN], cnt2[maxN], k;
bool tag[maxN];

struct node{
    int a, b, c, d;
}nodes[maxN];

inline void updata(int x, int v, int* mx){
    while(x <= k) mx[x] = std::max(mx[x], v), x += lowbit(x);
}

inline void clear(int x, int* mx){
    while(x <= k) mx[x] = 0, x += lowbit(x);
}

inline int query(int x, int* mx){
    int res = 0;
    while(x) res = std::max(res, mx[x]), x -= lowbit(x);
    return res;
}

inline void init(int n){
    std::iota(s, s + n + 1, 0);
    std::sort(s + 1, s + n + 1, [&](const int& a, const int& b){return d(a) < d(b);});
    int pre = -inf;
    for(int i = 1; i <= n; i++){
        if(pre < d(s[i])) pre = d(s[i]), ++k;
        rk[s[i]] = k;
    }
    std::iota(s, s + n + 1, 0);
    std::sort(s + 1, s + n + 1, [&](const int& a, const int& b){
        if(a(a) ^ a(b)) return a(a) < a(b);
        if(b(a) ^ b(b)) return b(a) < b(b);
        if(c(a) ^ c(b)) return c(a) < c(b);
        if(d(a) ^ d(b)) return d(a) < d(b);
        return a < b;
    });
    a(0) = b(0) = c(0) = d(0) = inf;
}

inline void cdq1(int l, int r){
    if(l == r) return ;
    int m = (l + r) >> 1;
    cdq1(l, m);
    for(int i = l; i <= m; i++) s1[i - l + 1] = tmp[i];
    for(int i = m + 1; i <= r; i++) s2[i - m] = tmp[i];
    std::sort(s1 + 1, s1 + m - l + 2, [&](const int& a, const int& b){return c(a) < c(b);});
    std::sort(s2 + 1, s2 + r - m + 1, [&](const int& a, const int& b){return c(a) < c(b);});
    s1[m - l + 2] = s2[r - m + 1] = 0;
    int idx1 = 1, idx2 = 1;
    for(int i = l; i <= r; i++){
        if(c(s1[idx1]) <= c(s2[idx2])){
            if(!tag[s1[idx1]]) updata(rk[s1[idx1]], cnt1[s1[idx1]] + 1, mx1);
            idx1++;
        }
        else{
            if(tag[s2[idx2]]) cnt1[s2[idx2]] = std::max(cnt1[s2[idx2]], query(rk[s2[idx2]], mx1));
            idx2++;
        }
    }
    for(int i = 1; i <= m - l + 1; i++) if(!tag[s1[i]]) clear(rk[s1[i]], mx1);
    cdq1(m + 1, r);
}

inline void cdq2(int l, int r){
    if(l == r) return ;
    int m = (l + r) >> 1;
    cdq2(l, m);
    for(int i = l; i <= m; i++) s1[i - l + 1] = s[i];
    for(int i = m + 1; i <= r; i++) s2[i - m] = s[i];
    std::sort(s1 + 1, s1 + m - l + 2, [&](const int& a, const int& b){return b(a) ^ b(b)? b(a) < b(b):a < b;});
    std::sort(s2 + 1, s2 + r - m + 1, [&](const int& a, const int& b){return b(a) ^ b(b)? b(a) < b(b):a < b;});
    s1[m - l + 2] = s2[r - m + 1] = 0;
    int idx1 = 1, idx2 = 1;
    for(int i = l; i <= r; i++){
        if(b(s1[idx1]) <= b(s2[idx2])){
            tag[s1[idx1]] = 0;
            tmp[i] = s1[idx1++];
        }
        else{
            tag[s2[idx2]] = 1;
            tmp[i] = s2[idx2++];
        }
    }
    cdq1(l, r);
    cdq2(m + 1, r);
}

inline void cdq3(int l, int r){
    if(l == r) return ;
    int m = (l + r) >> 1;
    cdq3(m + 1, r);
    for(int i = l; i <= m; i++) s1[i - l + 1] = tmp[i];
    for(int i = m + 1; i <= r; i++) s2[i - m] = tmp[i];
    std::sort(s1 + 1, s1 + m - l + 2, [&](const int& a, const int& b){return c(a) > c(b);});
    std::sort(s2 + 1, s2 + r - m + 1, [&](const int& a, const int& b){return c(a) > c(b);});
    s1[m - l + 2] = s2[r - m + 1] = 0;
    int idx1 = 1, idx2 = 1;
    for(int i = l; i <= r; i++){
        if(c(s1[idx1]) > c(s2[idx2])){
            if(!tag[s1[idx1]]) cnt2[s1[idx1]] = std::max(cnt2[s1[idx1]], query(k + 1 - rk[s1[idx1]], mx2));
            idx1++;
        }
        else{
            if(tag[s2[idx2]]) updata(k + 1 - rk[s2[idx2]], cnt2[s2[idx2]] + 1, mx2);
            idx2++;
        }
    }
    for(int i = 1; i <= r - m; i++) if(tag[s2[i]]) clear(k + 1 - rk[s2[i]], mx2);
    cdq3(l, m);
}

inline void cdq4(int l, int r){
    if(l == r) return ;
    int m = (l + r) >> 1;
    cdq4(m + 1, r);
    for(int i = l; i <= m; i++) s1[i - l + 1] = s[i];
    for(int i = m + 1; i <= r; i++) s2[i - m] = s[i];
    std::sort(s1 + 1, s1 + m - l + 2, [&](const int& a, const int& b){return b(a) ^ b(b)? b(a) < b(b):a < b;});
    std::sort(s2 + 1, s2 + r - m + 1, [&](const int& a, const int& b){return b(a) ^ b(b)? b(a) < b(b):a < b;});
    s1[m - l + 2] = s2[r - m + 1] = 0;
    int idx1 = 1, idx2 = 1;
    for(int i = l; i <= r; i++){
        if(b(s1[idx1]) <= b(s2[idx2])){
            tag[s1[idx1]] = 0;
            tmp[i] = s1[idx1++];
        }
        else{
            tag[s2[idx2]] = 1;
            tmp[i] = s2[idx2++];
        }
    }
    cdq3(l, r);
    cdq4(l, m);
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    for(int i = 1; i <= n; i++) std::cin >> a(i) >> b(i) >> c(i) >> d(i);
    init(n);
    cdq2(1, n);
    c(0) = -inf;
    cdq4(1, n);
    int res = 0;
    for(int i = 1; i <= n; i++) res = std::max(res, cnt1[i] + cnt2[i] + 1);
    std::cout << res;
    return 0;
}