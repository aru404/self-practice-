// # [NOIP2004 提高组] 合并果子 加强版

// ## 题目背景

// 本题除【数据范围与约定】外与 [P1090](https://www.luogu.com.cn/problem/P1090) **完  全  一  致**。

// ## 题目描述

// 在一个果园里，多多已经将所有的果子打了下来，而且按果子的不同种类分成了不同的堆。多多决定把所有的果子合成一堆。

// 每一次合并，多多可以把两堆果子合并到一起，消耗的体力等于两堆果子的重量之和。可以看出，所有的果子经过 $(n - 1)$ 次合并之后， 就只剩下一堆了。多多在合并果子时总共消耗的体力等于每次合并所耗体力之和。

// 因为还要花大力气把这些果子搬回家，所以多多在合并果子时要尽可能地节省体力。假定每个果子重量都为 $1$，并且已知果子的种类数和每种果子的数目，你的任务是设计出合并的次序方案，使多多耗费的体力最少，并输出这个最小的体力耗费值。

// 例如有 $3$ 堆果子，数目依次为 $1,~2,~9$。可以先将 $1$、$2$ 堆合并，新堆数目为 $3$，耗费体力为 $3$。接着，将新堆与原先的第三堆合并，又得到新的堆，数目为 $12$，耗费体力为 $12$。所以多多总共耗费体力为 $3+12=15$。可以证明 $15$ 为最小的体力耗费值。

// ## 输入格式

// 输入的第一行是一个整数 $n$，代表果子的堆数。
// 输入的第二行有 $n$ 个用空格隔开的整数，第 $i$ 个整数代表第 $i$ 堆果子的个数 $a_i$。

// ## 输出格式

// 输出一行一个整数，表示最小耗费的体力值。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 
// 1 2 9
// ```

// ### 样例输出 #1

// ```
// 15
// ```

// ## 提示

// **【数据规模与约定】**

// **本题采用多测试点捆绑测试，共有四个子任务**。

// - Subtask 1（10 points）：$1 \leq n \leq 8$。
// - Subtask 2（20 points）：$1 \leq n \leq 10^3$。
// - Subtask 3（30 points）：$1 \leq n \leq 10^5$。
// - Subtask 4（40 points）：$1 \leq n \leq 10^7$。

// 对于全部的测试点，保证 $1 \leq a_i \leq 10^5$。

// **【提示】**

// - 请注意常数因子对程序效率造成的影响。
// - 请使用类型合适的变量来存储本题的结果。
// - 本题输入规模较大，请注意数据读入对程序效率造成的影响。
#include <bits/stdc++.h>

struct node
{
    long long v;
    int cnt;
    node(long long v = 0, int cnt = 0):v(v), cnt(cnt){}
    bool operator<(const node& b) const
    {
        return v < b.v;
    }
};

const int maxN = 1E5 + 5;
int bucket[maxN];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, v, mx = 0;
    std::cin >> n;
    for(int i = 0; i < n; ++i)
    {
        std::cin >> v;
        ++bucket[v];
        mx = std::max(mx, v);
    }
    std::queue<node> q1, q2;
    for(int i = 1; i <= mx; ++i)
    {
        if(bucket[i]) q1.push(node(i, bucket[i]));
    }
    long long res = 0;

    std::function<node()> getFir = [&]()->node
    {
        if(q1.empty())
        {
            node res = q2.front();
            q2.pop();
            return res;
        }
        if(q2.empty())
        {
            node  res = q1.front();
            q1.pop();
            return res;
        }
        node res = q1.front();
        if(q2.front() < res)
        {
            res = q2.front();
            q2.pop();
            return res;
        }
        q1.pop();
        return res;
    };

    node n1, n2;
    while(!q1.empty() || !q2.empty() || n1.cnt)
    {
        if(!n1.cnt) n1 = getFir();
        if(n1.cnt == 1 && q1.empty() && q2.empty())
        {
            std::cout << res;
            break;
        }
        if(n1.cnt > 1)
        {
            q2.push(node(n1.v << 1, n1.cnt >> 1));
            res += (n1.v << 1) * (n1.cnt >> 1);
            n1.cnt -= (n1.cnt >> 1) << 1;
        }
        if(!n2.cnt) n2 = getFir();
        if(n1.cnt)
        {
            q2.push(node(n1.v + n2.v, 1));
            res += n1.v + n2.v;
            --n1.cnt, --n2.cnt;
        }
        std::swap(n1, n2);
    }
    return 0;
}