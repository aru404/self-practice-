// # Time to Raid Cowavans

// ## 题面翻译

// 给一个序列 $a$ ，$m$ 次询问，每次询问给出 $t, k$ 。求 $a_t + a_{t+k}+a_{t+2k}+\cdots+a_{t+pk}$ 其中 $t+pk \leq n$ 且 $t+(p+1)k > n$

// $n,m \leq 300000,a_i \leq 10^9$

// ## 题目描述

// As you know, the most intelligent beings on the Earth are, of course, cows. This conclusion was reached long ago by the Martian aliens, as well as a number of other intelligent civilizations from outer space.

// Sometimes cows gather into cowavans. This seems to be seasonal. But at this time the cows become passive and react poorly to external stimuli. A cowavan is a perfect target for the Martian scientific saucer, it's time for large-scale abductions, or, as the Martians say, raids. Simply put, a cowavan is a set of cows in a row.

// If we number all cows in the cowavan with positive integers from $ 1 $ to $ n $ , then we can formalize the popular model of abduction, known as the  $ (a,b) $ -Cowavan Raid: first they steal a cow number $ a $ , then number $ a+b $ , then — number $ a+2·b $ , and so on, until the number of an abducted cow exceeds $ n $ . During one raid the cows are not renumbered.

// The aliens would be happy to place all the cows on board of their hospitable ship, but unfortunately, the amount of cargo space is very, very limited. The researchers, knowing the mass of each cow in the cowavan, made $ p $ scenarios of the $ (a,b) $ -raid. Now they want to identify the following thing for each scenario individually: what total mass of pure beef will get on board of the ship. All the scenarios are independent, in the process of performing the calculations the cows are not being stolen.

//  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF103D/4a1176c97b389958360cf53dc3c4234ea51fce54.png)

// ## 输入格式

// The first line contains the only positive integer $ n $ ( $ 1<=n<=3·10^{5} $ ) — the number of cows in the cowavan.

// The second number contains $ n $ positive integer $ w_{i} $ , separated by spaces, where the $ i $ -th number describes the mass of the $ i $ -th cow in the cowavan ( $ 1<=w_{i}<=10^{9} $ ).

// The third line contains the only positive integer $ p $ — the number of scenarios of $ (a,b) $ -raids ( $ 1<=p<=3·10^{5} $ ).

// Each following line contains integer parameters $ a $ and $ b $ of the corresponding scenario ( $ 1<=a,b<=n $ ).

// ## 输出格式

// Print for each scenario of the $ (a,b) $ -raid the total mass of cows, that can be stolen using only this scenario.

// Please, do not use the %lld specificator to read or write 64-bit integers in С++. It is recommended to use the cin, cout streams of the %I64d specificator.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// 1 2 3
// 2
// 1 1
// 1 2
// ```

// ### 样例输出 #1

// ```
// 6
// 4
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 4
// 2 3 5 7
// 3
// 1 3
// 2 3
// 2 2
// ```

// ### 样例输出 #2

// ```
// 9
// 3
// 10
// ```
#include <bits/stdc++.h>

const int maxN = 3E5 + 5, maxB = 550;
typedef long long ll;

struct Query
{
    int a, b;
    bool operator<(const Query& other) const
    {
        return a > other.a;
    }
}qs[maxN];

int arr[maxN], idx[maxB][maxB], rk[maxN], sq, n;
ll pre[maxB][maxB], res[maxN];

inline ll query(int a, int b)
{
    if(b <= sq)
    {
        int r = a % b;
        while(idx[b][r] >= a)
        {
            pre[b][r] += arr[idx[b][r]];
            idx[b][r] -= b;
        }
        return pre[b][r];
    }
    ll res = 0;
    while(a <= n) res += arr[a], a += b;
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    sq = static_cast<int>(sqrt(n));
    for(int i = 1; i <= sq; ++i)
        for(int j = 0; j < i; ++j)
        {
            idx[i][j] = n / i * i + j;
            if(idx[i][j] > n) idx[i][j] -= i;
        }
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    int p;
    std::cin >> p;
    for(int i = 0; i < p; ++i)
        std::cin >> qs[i].a >> qs[i].b;
    std::iota(rk, rk + p, 0);
    std::sort(rk, rk + p, [&](const int& a, const int& b){
        return qs[a] < qs[b];
    });
    for(int i = 0; i < p; ++i)
        res[rk[i]] = query(qs[rk[i]].a, qs[rk[i]].b);
    for(int i = 0; i < p; ++i)
        std::cout << res[i] << '\n';
    return 0;
}