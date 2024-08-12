// # Array Queries

// ## 题面翻译

// - 给定长度为 $n$ 的序列 $a$。$q$ 次询问。
// - 每次询问给出 $p,k$。您要不断地执行操作 $p\gets p+a_p+k$，直到 $p>n$ 为止。询问的答案为操作次数。
// - $1\le n,q\le 10^5$，$1\le a_i\le n$，$1\le p,k\le n$。

// ## 题目描述

// $ a $ is an array of $ n $ positive integers, all of which are not greater than $ n $ .

// You have to process $ q $ queries to this array. Each query is represented by two numbers $ p $ and $ k $ . Several operations are performed in each query; each operation changes $ p $ to $ p+a_{p}+k $ . There operations are applied until $ p $ becomes greater than $ n $ . The answer to the query is the number of performed operations.

// ## 输入格式

// The first line contains one integer $ n $ $ (1<=n<=100000) $ .

// The second line contains $ n $ integers — elements of $ a $ ( $ 1<=a_{i}<=n $ for each $ i $ from $ 1 $ to $ n $ ).

// The third line containts one integer $ q $ $ (1<=q<=100000) $ .

// Then $ q $ lines follow. Each line contains the values of $ p $ and $ k $ for corresponding query $ (1<=p,k<=n) $ .

// ## 输出格式

// Print $ q $ integers, $ i $ th integer must be equal to the answer to $ i $ th query.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// 1 1 1
// 3
// 1 1
// 2 1
// 3 1
// ```

// ### 样例输出 #1

// ```
// 2
// 1
// 1
// ```

// ## 提示

// Consider first example:

// In first query after first operation $ p=3 $ , after second operation $ p=5 $ .

// In next two queries $ p $ is greater than $ n $ after the first operation.
#include <bits/stdc++.h>

const int maxN = 1E5 + 5, maxM = 320;
int dp[maxM][maxN], arr[maxN];
int m, n;

inline void initialize()
{
    m = static_cast<int>(std::sqrt(n));
    for(int i = 1; i <= m; ++i)
    {
        for(int j = n; j; --j)
        {
            int np = j + i + arr[j];
            if(np > n) dp[i][j] = 1;
            else dp[i][j] = dp[i][np] + 1;
        }
    }
}

inline int query(int p, int k)
{
    if(k <= m) return dp[k][p];
    int res = 0;
    while(p <= n)
    {
        ++res;
        p += arr[p] + k;
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q, p, k;
    std::cin >> n;
    for(int i = 1; i <= n; ++i) std::cin >> arr[i];
    initialize();
    std::cin >> q;
    for(int i = 0; i < q; ++i)
    {
        std::cin >> p >> k;
        std::cout << query(p, k) << '\n';
    }
    return 0;
}