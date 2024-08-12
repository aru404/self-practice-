// # [SDOI2011] 拦截导弹

// ## 题目描述

// 某国为了防御敌国的导弹袭击，发展出一种导弹拦截系统。但是这种导弹拦截系统有一个缺陷：虽然它的第一发炮弹能够到达任意的高度、并且能够拦截任意速度的导弹，但是以后每一发炮弹都不能高于前一发的高度，其拦截的导弹的飞行速度也不能大于前一发。某天，雷达捕捉到敌国的导弹来袭。由于该系统还在试用阶段，所以只有一套系统，因此有可能不能拦截所有的导弹。

// 在不能拦截所有的导弹的情况下，我们当然要选择使国家损失最小、也就是拦截导弹的数量最多的方案。但是拦截导弹数量的最多的方案有可能有多个，如果有多个最优方案，那么我们会随机选取一个作为最终的拦截导弹行动蓝图。

// 我方间谍已经获取了所有敌军导弹的高度和速度，你的任务是计算出在执行上述决策时，每枚导弹被拦截掉的概率。

// ## 输入格式

// ![](https://cdn.luogu.com.cn/upload/pic/1604.png)

// ## 输出格式

// ![](https://cdn.luogu.com.cn/upload/pic/1605.png)

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4
// 3 30
// 4 40
// 6 60
// 3 30
// ```

// ### 样例输出 #1

// ```
// 2
// 0.33333 0.33333 0.33333 1.00000
// ```

// ## 提示

// ![](https://cdn.luogu.com.cn/upload/pic/1606.png)

// 保证总方案数不超过 C++ 中 double 类型的存储范围。
#include <bits/stdc++.h>
#include <iostream>
#define lowbit(x) (x & -x)
#define ll long long

const int maxN = 5E4 + 5, inf = 0X3f3f3f3f;
int s[maxN], s1[maxN], s2[maxN], rk[maxN], tmp[maxN];
int h[maxN], v[maxN], cnt1[maxN], cnt2[maxN], mx1[maxN], mx2[maxN], k;
double cnt3[maxN], cnt4[maxN], mx3[maxN], mx4[maxN];

inline void init(int n){
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int& a, const int& b){return v[a] < v[b];});
    int pre = 0;
    for(int i = 1; i <= n; i++){
        if(pre < v[tmp[i]]) pre = v[tmp[i]], ++k;
        rk[tmp[i]] = k; 
    }
}

inline void updata(int x, int v1, double v2, int* mx, double* cnt){
    while(x <= k){
        if(mx[x] == v1) cnt[x] += v2;
        else if(mx[x] < v1) mx[x] = v1, cnt[x] = v2;
        x += lowbit(x);
    }
}

inline void clear(int x, int* mx, double* cnt){
    while(x <= k){
        mx[x] = 0, cnt[x] = 1;
        x += lowbit(x);
    }
}

inline std::pair<int, double> query(int x, int* mx, double* cnt){
    int res1 = 0; double res2 = 0;
    while(x){
        if(res1 == mx[x]){
            res2 += cnt[x];
        }
        else if(res1 < mx[x]){
            res1 = mx[x];
            res2 = cnt[x];
        }
        x -= lowbit(x);
    }
    return std::make_pair(res1, res2);
}

inline void cdq1(int l, int r){
    if(l == r) return ;
    int m = (l + r) >> 1;
    cdq1(m + 1, r);
    for(int i = l; i <= m; i++) s1[i - l + 1] = s[i];
    for(int i = m + 1; i <= r; i++) s2[i - m] = s[i];
    std::sort(s1 + 1, s1 + m - l + 2, [&](const int& a, const int& b){return h[a] < h[b];});
    std::sort(s2 + 1, s2 + r - m + 1, [&](const int& a, const int& b){return h[a] < h[b];});
    s1[m - l + 2] = s2[r - m + 1] = 0;
    int idx1 = 1, idx2 = 1;
    h[0] = inf;
    for(int i = l; i <= r; i++){
        if(h[s1[idx1]] < h[s2[idx2]]){
            auto it = query(rk[s1[idx1]], mx1, mx3);
            if(it.first && cnt1[s1[idx1]] == it.first) cnt3[s1[idx1]] += it.second;
            else if(cnt1[s1[idx1]] < it.first) cnt1[s1[idx1]] = it.first, cnt3[s1[idx1]] = it.second;
            idx1++;
        }
        else{
            updata(rk[s2[idx2]], 1 + cnt1[s2[idx2]], cnt3[s2[idx2]], mx1, mx3);
            idx2++;
        }
    }
    for(int i = 1; i <= r - m; i++) clear(rk[s2[i]], mx1, mx3);
    cdq1(l, m);
}

inline void cdq2(int l, int r){
    if(l == r) return ;
    int m = (l + r) >> 1;
    cdq2(l, m);
    for(int i = l; i <= m; i++) s1[i - l + 1] = s[i];
    for(int i = m + 1; i <= r; i++) s2[i - m] = s[i];
    std::sort(s1 + 1, s1 + m - l + 2, [&](const int& a, const int& b){return h[a] > h[b];});
    std::sort(s2 + 1, s2 + r - m + 1, [&](const int& a, const int& b){return h[a] > h[b];});
    s1[m - l + 2] = s2[r - m + 1] = 0;
    int idx1 = 1, idx2 = 1;
    h[0] = -inf;
    for(int i = l; i <= r; i++){
        if(h[s1[idx1]] >= h[s2[idx2]]){
            updata(k + 1 - rk[s1[idx1]], 1 + cnt2[s1[idx1]], cnt4[s1[idx1]], mx2, mx4);
            idx1++;
        }
        else{
            auto it = query(k + 1 - rk[s2[idx2]], mx2, mx4);
            if(it.first && cnt2[s2[idx2]] == it.first) cnt4[s2[idx2]] += it.second;
            else if(cnt2[s2[idx2]] < it.first) cnt2[s2[idx2]] = it.first, cnt4[s2[idx2]] = it.second;
            idx2++;
        }
    }
    for(int i = 1; i <= m - l + 1; i++) clear(k + 1 - rk[s1[i]], mx2, mx4);
    cdq2(m + 1, r);
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, mxCnt = 0;
    std::cin >> n;
    for(int i = 1; i <= n; i++) std::cin >> h[i] >> v[i];
    init(n);
    std::iota(s, s + n + 1, 0);
    for(int i = 1; i <= k; i++) mx3[i] = mx4[i] = 1;
    for(int i = 1; i <= n; i++) cnt3[i] = cnt4[i] = 1;
    cdq1(1, n), cdq2(1, n);
    for(int i = 1; i <= n; i++) mxCnt = std::max(mxCnt, cnt1[i] + cnt2[i]);
    double tot = 0;
    for(int i = 1; i <= n; i++){
        if(cnt1[i] == mxCnt){
            tot += cnt3[i] * cnt4[i];
        }
    }
    std::cout << mxCnt + 1 << std::endl;
    for(int i = 1; i <= n; i++){
        if(cnt1[i] + cnt2[i] == mxCnt) std::cout << std::fixed << std::setprecision(5) << cnt3[i] * cnt4[i] / tot << ' ';
        else std::cout << std::fixed << std::setprecision(5) << 0 << ' ';
    }
    return 0;
}