// # H(n)

// ## 题目描述

// [problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2521

// [PDF](https://uva.onlinejudge.org/external/115/p11526.pdf)

// ![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11526/9afb4a892766896248d693ae925d518ab86d3d10.png)

// ## 输入格式

// ![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11526/0f8c27b2e2d3e2232a7828505b7e1038020abc96.png)

// ## 输出格式

// ![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11526/b8e0b2b685195f97c03927b5f479ece353c14d6f.png)

// ## 样例 #1

// ### 样例输入 #1

// ```
// 2
// 5
// 10
// ```

// ### 样例输出 #1

// ```
// 10
// 27
// ```
#include <bits/stdc++.h>
#define ll long long

const int mod = 998244353;

int H(ll n)
{
    int res = 0;
    ll i = 1;
    while(i <= n)
    {
        ll j = n / (n / i);
        res = (res + (n / i) * (j - i + 1) % mod) % mod;
        i = j + 1;
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ll l, r;
    std::cin >> l >> r;
    std::cout << (H(r) - H(l - 1) + mod) % mod;
    return 0;
}