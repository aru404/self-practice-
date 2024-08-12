// # Arithmetic Operations

// ## 题面翻译

// * 给定一个长度为 $n$ 的序列 $a$。
// * 问至少需要修改几个数才能使得 $a$ 变为一个等差数列。
// * $n\leq 10^5$，$1\leq a_i\leq 10^5$。

// ## 题目描述

// You are given an array of integers $ a_1, a_2, \ldots, a_n $ .

// You can do the following operation any number of times (possibly zero):

// - Choose any index $ i $ and set $ a_i $ to any integer (positive, negative or $ 0 $ ).

// What is the minimum number of operations needed to turn $ a $ into an arithmetic progression? The array $ a $ is an arithmetic progression if $ a_{i+1}-a_i=a_i-a_{i-1} $ for any $ 2 \leq i \leq n-1 $ .

// ## 输入格式

// The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ).

// The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^5 $ ).

// ## 输出格式

// Print a single integer: the minimum number of operations needed to turn $ a $ into an arithmetic progression.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 9
// 3 2 7 8 6 9 5 4 1
// ```

// ### 样例输出 #1

// ```
// 6
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 14
// 19 2 15 8 9 14 17 13 4 14 4 11 15 7
// ```

// ### 样例输出 #2

// ```
// 10
// ```

// ## 样例 #3

// ### 样例输入 #3

// ```
// 10
// 100000 1 60000 2 20000 4 8 16 32 64
// ```

// ### 样例输出 #3

// ```
// 7
// ```

// ## 样例 #4

// ### 样例输入 #4

// ```
// 4
// 10000 20000 10000 1
// ```

// ### 样例输出 #4

// ```
// 2
// ```

// ## 提示

// In the first test, you can get the array $ a = [11, 10, 9, 8, 7, 6, 5, 4, 3] $ by performing $ 6 $ operations:

// - Set $ a_3 $ to $ 9 $ : the array becomes $ [3, 2, 9, 8, 6, 9, 5, 4, 1] $ ;
// - Set $ a_2 $ to $ 10 $ : the array becomes $ [3, 10, 9, 8, 6, 9, 5, 4, 1] $ ;
// - Set $ a_6 $ to $ 6 $ : the array becomes $ [3, 10, 9, 8, 6, 6, 5, 4, 1] $ ;
// - Set $ a_9 $ to $ 3 $ : the array becomes $ [3, 10, 9, 8, 6, 6, 5, 4, 3] $ ;
// - Set $ a_5 $ to $ 7 $ : the array becomes $ [3, 10, 9, 8, 7, 6, 5, 4, 3] $ ;
// - Set $ a_1 $ to $ 11 $ : the array becomes $ [11, 10, 9, 8, 7, 6, 5, 4, 3] $ .

//  $ a $ is an arithmetic progression: in fact, $ a_{i+1}-a_i=a_i-a_{i-1}=-1 $ for any $ 2 \leq i \leq n-1 $ .

// There is no sequence of less than $ 6 $ operations that makes $ a $ an arithmetic progression.

// In the second test, you can get the array $ a = [-1, 2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35, 38] $ by performing $ 10 $ operations.

// In the third test, you can get the array $ a = [100000, 80000, 60000, 40000, 20000, 0, -20000, -40000, -60000, -80000] $ by performing $ 7 $ operations.
#include <bits/stdc++.h>

const int maxN = 1E5 + 5, maxM = 300, b = 3E7;

int arr[maxN], d[maxN * maxM + maxN];

inline int solve(int n)
{
    int mx = 1;
    for(int i = 0; i <= maxM; ++i)
    {
        for(int j = 0; j < n; ++j) mx = std::max(mx, ++d[arr[j] - j * i + b]);
        for(int j = 0; j < n; ++j) d[arr[j] - j * i + b] = 0;
    }

    for(int i = 0; i < n; ++i)
    {
        int m = std::min(n, i + 334), cnt = 0;
        for(int j = i + 1; j < m; ++j) if((arr[j] - arr[i]) % (j - i) == 0) cnt = std::max(++d[(arr[j] - arr[i]) / (j - i) + 100000], cnt);
        for(int j = i + 1; j < m; ++j) if((arr[j] - arr[i]) % (j - i) == 0) d[(arr[j] - arr[i]) / (j - i) + 100000] = 0;
        mx = std::max(cnt + 1, mx);
    }
    return n - mx;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    for(int i = 0; i < n; ++i) std::cin >> arr[i];
    int res = solve(n);
    std::reverse(arr, arr + n);
    res = std::min(res, solve(n));
    std::cout << res;
    return 0;
}