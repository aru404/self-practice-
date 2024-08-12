// # AI robots

// ## 题面翻译

// 火星上有$N$个机器人排成一行，第$i$个机器人的位置为$x_{i}$，视野为$r_{i}$，智商为$q_{i}$。我们认为第$i$个机器人可以看到的位置是$[x_{i}-r_{i},x_{i}+r_{i}]$。	
// 如果一对机器人相互可以看到，且它们的智商$q_{i}$的差距**不大于**$K$，那么它们会开始聊天。	
// 为了防止它们吵起来，请计算有多少对机器人可能会聊天。

// ## 题目描述

// In the last mission, MDCS has successfully shipped $ N $ AI robots to Mars. Before they start exploring, system initialization is required so they are arranged in a line. Every robot can be described with three numbers: position ( $ x_i $ ), radius of sight ( $ r_i $ ) and IQ ( $ q_i $ ).

// Since they are intelligent robots, some of them will talk if they see each other. Radius of sight is inclusive, so robot can see other all robots in range $ [x_i - r_i, x_i + r_i] $ . But they don't walk to talk with anybody, but only with robots who have similar IQ. By similar IQ we mean that their absolute difference isn't more than $ K $ .

//  Help us and calculate how many pairs of robots are going to talk with each other, so we can timely update their software and avoid any potential quarrel.

// ## 输入格式

// The first line contains two integers, numbers $ N (1 \leq N \leq 10^5)  $ and $ K (0 \leq K \leq 20) $ .

// Next $ N $ lines contain three numbers each $ x_i, r_i, q_i (0 \leq x_i,r_i,q_i \leq 10^9) $ — position, radius of sight and IQ of every robot respectively.

// ## 输出格式

// Output contains only one number — solution to the problem.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 2
// 3 6 1
// 7 3 10
// 10 5 8
// ```

// ### 样例输出 #1

// ```
// 1
// ```

// ## 提示

// The first robot can see the second, but not vice versa. The first robot can't even see the third. The second and the third robot can see each other and their IQs don't differ more than 2 so only one conversation will happen.# AI robots

// ## 题面翻译

// 火星上有$N$个机器人排成一行，第$i$个机器人的位置为$x_{i}$，视野为$r_{i}$，智商为$q_{i}$。我们认为第$i$个机器人可以看到的位置是$[x_{i}-r_{i},x_{i}+r_{i}]$。	
// 如果一对机器人相互可以看到，且它们的智商$q_{i}$的差距**不大于**$K$，那么它们会开始聊天。	
// 为了防止它们吵起来，请计算有多少对机器人可能会聊天。

// ## 题目描述

// In the last mission, MDCS has successfully shipped $ N $ AI robots to Mars. Before they start exploring, system initialization is required so they are arranged in a line. Every robot can be described with three numbers: position ( $ x_i $ ), radius of sight ( $ r_i $ ) and IQ ( $ q_i $ ).

// Since they are intelligent robots, some of them will talk if they see each other. Radius of sight is inclusive, so robot can see other all robots in range $ [x_i - r_i, x_i + r_i] $ . But they don't walk to talk with anybody, but only with robots who have similar IQ. By similar IQ we mean that their absolute difference isn't more than $ K $ .

//  Help us and calculate how many pairs of robots are going to talk with each other, so we can timely update their software and avoid any potential quarrel.

// ## 输入格式

// The first line contains two integers, numbers $ N (1 \leq N \leq 10^5)  $ and $ K (0 \leq K \leq 20) $ .

// Next $ N $ lines contain three numbers each $ x_i, r_i, q_i (0 \leq x_i,r_i,q_i \leq 10^9) $ — position, radius of sight and IQ of every robot respectively.

// ## 输出格式

// Output contains only one number — solution to the problem.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 2
// 3 6 1
// 7 3 10
// 10 5 8
// ```

// ### 样例输出 #1

// ```
// 1
// ```

// ## 提示

// The first robot can see the second, but not vice versa. The first robot can't even see the third. The second and the third robot can see each other and their IQs don't differ more than 2 so only one conversation will happen.
#include <iostream>
#include <bits/stdc++.h>
#define ll long long
#define f q.front()
#define x(p) robots[p].x
#define r(p) robots[p].r
#define q(p) robots[p].q
#define lowbit(x) (x & -x)

const int maxN = 1E5 + 5, inf = 0X3f3f3f3f;
int cnt[maxN * 3], rk1[maxN], rk2[maxN], rk3[maxN], tmp[maxN * 3], s1[maxN], s2[maxN], k, m;
ll ans = 0;
std::deque<int> q;

struct node{
    int x, r, q;
    bool operator<(const node& b){
        if(x ^ b.x) return x < b.x;
        if(q ^ b.q) return q < b.q;
        return r < b.r;
    }
}robots[maxN];

inline void init(int n){
    std::iota(tmp, tmp + n * 3 + 1, 0);
    std::function<int(int)> get = [&](const int& a)->int{
        if(a <= n) return x(a) - r(a);
        if(a > 2 * n) return x(a - 2 * n) + r(a - 2 * n);
        return x(a - n);
    };
    std::sort(tmp + 1, tmp + 3 * n + 1, [&](const int& a, const int& b){
        return get(a) < get(b);
    });
    int pre = -inf;
    for(int i = 1; i <= 3 * n; i++){
        int now = get(tmp[i]);
        if(now > pre) pre = now, ++m;
        if(tmp[i] <= n) rk1[tmp[i]] = m;
        else if(tmp[i] <= 2 * n) rk2[tmp[i] - n] = m;
        else rk3[tmp[i] - 2 * n] = m;
    }
    std::iota(tmp, tmp + n + 1, 0);
    std::sort(tmp + 1, tmp + n + 1, [&](const int& a, const int& b){return r(a) > r(b);});
    q(0) = inf;
}

inline void updata(int x, int v){
    while(x <= m) cnt[x] += v, x += lowbit(x); 
}

inline int query(int x){
    int res = 0;
    while(x) res += cnt[x], x -= lowbit(x);
    return res;
}

inline int query(int l, int r){
    return query(r) - query(l - 1);
}

inline void  cdq(int l, int r){
    if(l == r) return ;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    for(int i = l; i <= mid; i++) s1[i - l + 1] = tmp[i];
    for(int i = mid + 1; i <= r; i++) s2[i - mid] = tmp[i];
    s1[mid - l + 2] = s2[r - mid + 1] = 0;
    int idx1 = 1, idx2 = 1;
    for(int i = l; i <= r; i++){
        if(q(s1[idx1]) - k <= q(s2[idx2])){
            updata(rk2[s1[idx1]], 1);
            q.emplace_back(s1[idx1++]);
        }
        else{
            while(!q.empty() && std::abs(q(f) - q(s2[idx2])) > k) updata(rk2[f], -1), q.pop_front();
            ans += query(rk1[s2[idx2]], rk3[s2[idx2]]);
            idx2++;
        }
    }
    idx1 = idx2 = 1;
    for(int i = l; i <= r; i++){
        if(q(s1[idx1]) <= q(s2[idx2])) tmp[i] = s1[idx1++];
        else tmp[i] = s2[idx2++];
    }
    while(!q.empty()) updata(rk2[f], -1), q.pop_front();
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n >> k;
    for(int i = 1; i <= n; i++) std::cin >> x(i) >> r(i) >> q(i);
    init(n);
    cdq(1, n);
    std::cout << ans;
    return 0;
}