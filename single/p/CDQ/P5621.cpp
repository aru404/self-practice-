// # [DBOI2019] 德丽莎世界第一可爱

// ## 题目背景

// ```cpp
// 众所周知，德丽莎世界第一可爱。
// ——zhengrunzhe
// ```

// 你正在打崩坏$3$，突然家长来了，于是你装作在打数据结构题。

// ![神恩颂歌](https://cdn.luogu.com.cn/upload/pic/70922.png)

// ## 题目描述

// 有$n$个崩坏兽，每个崩坏兽有五个属性值：$health$生命力，$energy$能量力，$attack$攻击力，$defense$防御力，$collapse$崩坏能。

// 德丽莎可以任选一只崩坏兽展开攻击 假如她干掉了崩坏兽$i$ 那么她会收获$collapse[i]$的可爱值 由于德丽莎越战越勇 她打的下一只崩坏兽$j$ 需要满足$health[j]\geq health[i] , energy[j]\geq energy[i] , attack[j]\geq attack[i] , defense[j]\geq defense[i]$。

// 请你帮帮德丽莎计算一下她能够获得的最大可爱值。

// ## 输入格式

// 第一行一个正整数$n$。

// 接下来$n$行，第$i+1$行五个整数$health[i],energy[i],attack[i],defense[i],collapse[i]$，代表着第$i$只崩坏兽的属性值。

// ## 输出格式

// 一行一个整数，代表最大可爱值（必须击杀至少一只崩坏兽），答案保证不会超过long long范围($2^{63}-1$)。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5
// 1 9 2 6 233
// 0 8 1 7 666
// -3 9 4 2 810
// 2 3 3 3 -100
// 1 9 8 9 604
// ```

// ### 样例输出 #1

// ```
// 1414
// ```

// ## 提示

// 【样例#$1$说明】

// 打第三只崩坏兽之后再打第五只。

// $Subtask$ #$1$（$20$分）： 

// $1\leq n\leq 100$。

// $Subtask$ #$2$（$20$分）： 

// $1\leq n\leq 10000$。

// $Subtask$ #$3$（$60$分）： 

// $1\leq n\leq 50000$。

// 对于 $100\%$ 的数据，满足 $|\mathrm{health}_i|, |\mathrm{energy}_i|, |\mathrm{attack_i}|, |\mathrm{defense}_i| \le 10^5$，$| \mathrm{collapse}_i|\le 10^9$。

// ### 题目提供者：[$\color{red}{zhengrunzhe}$](https://www.luogu.org/space/show?uid=14374)
#include <iostream>
#include <bits/stdc++.h>
#define ll long long
#define lowbit(x) (x & -x)
#define hp(x) monsters[x].h
#define en(x) monsters[x].e
#define def(x) monsters[x].d
#define atk(x) monsters[x].a
#define col(x) monsters[x].c

const int maxN = 5e4 + 5, inf = 0X3f3f3f3f;
int rk[maxN], s[maxN], tmp[maxN], s1[maxN], s2[maxN], inv[maxN];
ll mx[maxN], ans[maxN], k;
bool tag[maxN];

struct node{
    int h, e, a, d, c;
    node(int hp = 0, int en = 0, int atk = 0, int def = 0, ll col = 0):h(hp), e(en), a(atk), d(def), c(col){}
    
    bool operator<(const node& b) const{
        if(h ^ b.h) return h < b.h;
        if(e ^ b.e) return e < b.e;
        if(d ^ b.d) return d < b.d;
        return a < b.a;
    }

    bool operator==(const node& b) const{
        return h == b.h && e == b.e && d == b.d && a == b.a;
    }
}monsters[maxN];

inline int init(int n){
    std::iota(s, s + n + 1, 0);
    std::sort(s + 1, s + n + 1, [&](const int& a, const int& b){return def(a) < def(b);});
    int pre = -inf;
    for(int i = 1; i <= n; i++){
        if(def(s[i]) > pre) pre = def(s[i]), ++k;
        rk[s[i]] = k;
    }
    atk(0) = def(0) = en(0) = inf;
    std::iota(s, s + n + 1, 0);
    std::sort(s + 1, s + n + 1, [&](const int& a, const int& b){return monsters[a] < monsters[b];});
    int m = 0; pre = 0;
    for(int i = 1; i <= n; i++){
        if(monsters[pre] == monsters[s[i]]) col(pre) = std::max({col(pre), col(s[i]), col(pre) + col(s[i])});
        else ++m, pre = s[m] = s[i];
    }
    for(int i = 1; i <= n; i++) ans[i] = col(i);
    return m;
}

inline void updata(int x, ll v){
    while(x <= k) mx[x] = std::max(mx[x], v), x += lowbit(x);
}

inline void clear(int x){
    while(x <= k) mx[x] = 0, x += lowbit(x);
}

inline ll query(int x){
    ll res = 0;
    while(x) res = std::max(res, mx[x]), x -= lowbit(x);
    return res;
}

inline void cdq1(int l, int r){
    if(l >= r) return ;
    int m = (l + r) >> 1;
    cdq1(l, m);
    for(int i = l; i <= m; i++) s1[i - l + 1] = tmp[i];
    for(int i = m + 1; i <= r; i++) s2[i - m] = tmp[i];
    std::sort(s1 + 1, s1 + m - l + 2, [&](const int& a, const int& b){return atk(a) < atk(b);});
    std::sort(s2 + 1, s2 + r - m + 1, [&](const int& a, const int& b){return atk(a) < atk(b);});
    int idx1 = 1, idx2 = 1; s1[m - l + 2] = s2[r - m + 1] = 0;
    for(int i = l; i <= r; i++){
        if(atk(s1[idx1]) <= atk(s2[idx2])){
            if(!tag[s1[idx1]]) updata(rk[s1[idx1]], ans[s1[idx1]]);
            idx1++;
        }
        else{
            if(tag[s2[idx2]]) ans[s2[idx2]] = std::max(ans[s2[idx2]], query(rk[s2[idx2]]) + col(s2[idx2]));
            idx2++;
        }
    }
    for(int i = 1; i <= m - l + 1; i++) if(!tag[s1[i]]) clear(rk[s1[i]]);
    cdq1(m + 1, r);
}

inline void cdq2(int l, int r){
    if(l == r) return ;
    int m = (l + r) >> 1;
    cdq2(l, m);
    for(int i = l; i <= m; i++) s1[i - l + 1] = s[i];
    for(int i = m + 1; i <= r; i++) s2[i - m] = s[i];
    std::sort(s1 + 1, s1 + m - l + 2, [&](const int& a, const int& b){return en(a) < en(b);});
    std::sort(s2 + 1, s2 + r - m + 1, [&](const int& a, const int& b){return en(a) < en(b);});
    int idx1 = 1, idx2 = 1; s1[m - l + 2] = s2[r - m + 1] = 0;
    for(int i = l; i <= r; i++){
        if(en(s1[idx1]) <= en(s2[idx2])){
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

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    for(int i = 1; i <= n; i++) std::cin >> hp(i) >> en(i) >> atk(i) >> def(i) >> col(i);
    int m = init(n);
    cdq2(1, m);
    ll res = -inf;
    for(int i = 1; i <= n; i++) res = std::max(res, ans[i]);
    std::cout << res;
    return 0;
}