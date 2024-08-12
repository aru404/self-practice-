// # 论如何玩转 Excel 表格

// ## 题目描述

// 有一个 $2 \times n$ 的表格，表格内不重不漏地填有 $1 \sim 2 \times n$ 这些数字。你可以进行若干次操作，每次操作可以选择一个 $2 \times 2$ 的正方形区域，然后旋转 $180\degree$。

// 给出现在的状态以及目标状态。问是否可以达到目标状态。如果能，最少操作次数是多少。

// ## 输入格式

// 第一行一个正整数 $n$。

// 接下来两行，每行 $n$ 个正整数表示表格现在的状态。

// 接下来两行，每行 $n$ 个正整数表示目标状态。

// ## 输出格式

// 若无解，输出一行 `dldsgay!!1`。

// 否则，输出一个整数，表示最少的操作次数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 1
// 1
// 2
// 2
// 1
// ```

// ### 样例输出 #1

// ```
// dldsgay!!1
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 2
// 1 2
// 3 4
// 4 3
// 2 1
// ```

// ### 样例输出 #2

// ```
// 1
// ```

// ## 样例 #3

// ### 样例输入 #3

// ```
// 2
// 1 2
// 3 4
// 1 2
// 4 3
// ```

// ### 样例输出 #3

// ```
// dldsgay!!1
// ```

// ## 样例 #4

// ### 样例输入 #4

// ```
// 3
// 1 6 2
// 4 3 5
// 2 4 3
// 5 1 6
// ```

// ### 样例输出 #4

// ```
// 2
// ```

// ## 提示

// #### 子任务

// 本题采用捆绑测试。

// 对于 $100\%$ 的数据：$1 \leq n \leq 10^6$。

// 本题共 $10$ 个子任务，各子任务的分值和限制如下：

// 子任务 $1$（$1$ 分）：保证输出一定为 `dldsgay!!1`。  
// 子任务 $2$（$1$ 分）：保证目标状态与现在状态一致。  
// 子任务 $3$（$4$ 分）：$n=1$。  
// 子任务 $4$（$5$ 分）：$n=2$。  
// 子任务 $5$（$14$ 分）：$1 \leq n \leq 20$。  
// 子任务 $6$（$19$ 分）：$1 \leq n \leq 100$。  
// 子任务 $7$（$19$ 分）：$1 \leq n \leq 1000$。  
// 子任务 $8$（$8$ 分）：保证目标状态第一行依次为 $1 \sim n$，第二行依次为  $n + 1 \sim 2n$。  
// 子任务 $9$（$10$ 分）：保证不存在无解情况。  
// 子任务 $10$（$19$ 分）：无特殊限制。
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

namespace BIT{
    #define lowbit(x) (x & -x)

    const int maxN = 1E6 + 5;
    int w[2][maxN], rk[maxN << 1];
    int tree1[maxN], tree2[maxN], n;
    bool in[maxN << 1];

    inline int query(int x, int* t){
        int res = 0;
        while(x) res += t[x], x -= lowbit(x);
        return res;
    }

    inline void updata(int x, int* t){
        while(x <= n) ++t[x], x += lowbit(x);
    }

    inline void solve(){
        std::cin >> n;
        ll cnt1 = 0, cnt2 = 0;
        for(int i = 1; i <= n; i++) std::cin >> w[0][i];
        for(int i = 1; i <= n; i++) std::cin >> w[1][i];
        int v;
        for(int i = 0; i < 2; i++){
            for(int j = 1; j <= n; j++) std::cin >> v, rk[v] = j, in[v] = i;
        }
        for(int i = 1; i <= n; i++){
            if(rk[w[0][i]] != rk[w[1][i]] || abs(rk[w[0][i]] - i) % 2 != in[w[0][i]]){
                std::cout << "dldsgay!!1";
                return ;
            }
        }
        for(int i = n; i; i--) cnt1 += query(rk[w[0][i]] - 1, tree1), updata(rk[w[0][i]], tree1);
        for(int i = n; i; i--) cnt2 += query(rk[w[1][i]] - 1, tree2), updata(rk[w[1][i]], tree2);
        std::cout << std::max(cnt1, cnt2);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    BIT::solve();
    return 0;
}