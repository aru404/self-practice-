// # Two Arithmetic Progressions

// ## 题面翻译

// 已知两个无限长的等差数列，首项分别为 $b_1, b_2$，公差分别为 $a_1, a_2$，求 $[L,R]$ 中有多少个数在两个等差数列中都出现了。

// ## 题目描述

// You are given two arithmetic progressions: $ a_{1}k+b_{1} $ and $ a_{2}l+b_{2} $ . Find the number of integers $ x $ such that $ L<=x<=R $ and $ x=a_{1}k'+b_{1}=a_{2}l'+b_{2} $ , for some integers $ k',l'>=0 $ .

// ## 输入格式

// The only line contains six integers $ a_{1},b_{1},a_{2},b_{2},L,R \, (  0 \lt a_1,a_2 \le 2\times10^9,-2\times10^9 \le b_1,b_2,L,R \le 2\times10^9,L \le R)$ .

// ## 输出格式

// Print the desired number of integers $ x $ .

// ## 样例 #1

// ### 样例输入 #1

// ```
// 2 0 3 3 5 21
// ```

// ### 样例输出 #1

// ```
// 3
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 2 4 3 0 6 17
// ```

// ### 样例输出 #2

// ```
// 2
// ```
#include <bits/stdc++.h>
#define ll long long

inline std::tuple<ll, ll, ll> exgcd(ll a, ll b)
{
    if(!b) return std::make_tuple(1, 0, a);
    return exgcd(b, a % b);
    int x, y, w;
    std::tie(x, y, w) = exgcd(b, a % b);
    return std::make_tuple(y, x - a / b * y, w);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll a1, b1, a2, b2;
    ll l, r;
    std::cin >> a1 >> b1 >> a2 >> b2 >> l >> r;
    ll x, y, w;
    std::tie(x, y, w) = exgcd(a1, a2);
    if((b2 - b1) % w) std::cout << 0;
    else
    {
        x *= (b2 - b1) / w;
        y *= (b2 - b1) / w;
    }
}