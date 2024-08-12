// # [THUPC2018] 绿绿和串串

// ## 题目背景

// 绿绿和 Yazid 是好朋友。他们在一起做串串游戏。

// ## 题目描述

// 绿绿有一个由小写字母组成的非空字符串 $R$，但 Yazid 不知道它具体是什么。

// 我们定义**翻转**的操作：把一个串以最后一个字符作对称轴进行翻转复制。形式化地描述就是，如果他翻转的串为 $R$，那么他会将前 $\left| R\right|-1$ 个字符倒序排列后，插入到串的最后。

// 举例而言，串`abcd`进行翻转操作后，将得到`abcdcba`；串`qw`连续进行 **$2$ 次**翻转操作后，将得到`qwqwq`；串`z`无论进行多少次翻转操作，都不会被改变。

// 贪玩的绿绿进行了若干次（可能为 $0$ 次）翻转操作。

// 淘气的绿绿又展示出了一个非空串 $S$，并表示 $S$ 是**最终**的串 $R$ 的前缀。现在，他想考考 Yazid，**初始**的串 $R$ 的长度可能是多少。

// Yazid 找到了正在参加清华校赛的你，请你来帮他解决这个问题。但聪明的 Yazid 发现，所有超过 $\left| S\right|$ 的整数都一定是 $R$ 的可能长度，因此你只需要告诉他不超过的 $\left| S\right|$ 的 $R$ 的可能长度即可。

// 为了帮助你理解问题，Yazid 还将对一些概念和记号做出解释：

// - 对于一个串 $S$，$\left| S\right|$ 表示的是该串的长度。
// - 对于一个串 $S$，我们定义串 $T$ 是它的前缀，当且仅当 $\left| T\right|\leq\left| S\right|$，且对于任意整数 $i$ 满足 $1\leq i\leq\left| T\right|$，都有 $T$ 的左起第 $i$ 个字符与 $S$ 的左起第 $i$ 个字符相同。（形象地理解，即 $T$ 在 $S$ 的前部出现）
//   - 如：`abc`是`abcdefg`的前缀，`aba`**不**为`abba`的前缀，`z`为`z`的前缀，空串为任意一个串的前缀。

// ## 输入格式

// 输入包含多组数据，第一行一个整数 $T$ 表示数据组数。接下来依次描述每组数据，对于每组数据：

// * 一行一个仅由小写字母组成的非空字符串 $S$。

// ## 输出格式

// 对于每组数据，输出 $1$ 行：

// * 从小到大输出 $\left| R\right|$ 的所有不超过 $\left| S\right|$ 的可能值，所有值之间用单个空格隔开。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4
// abcdcb
// qwqwq
// qaqaqqq
// carnation
// ```

// ### 样例输出 #1

// ```
// 4 6
// 2 3 4 5
// 6 7
// 9
// ```

// ## 提示

// ### 数据范围

// 保证 $\left| S\right|\leq 10^6$，$\sum\left| S\right|\leq 5\times 10^6$。

// $\sum\left| S\right|$ 表示的是单个测试点中所有数据 $\left| S\right|$ 的总和。

// ### 提示

// * 读入规模较大，请注意读入效率。

// * 样例中的最后一个字符串是什么意思呢？

// ### 版权信息

// 来自 2018 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2018），感谢 [Pony.ai](http://pony.ai/) 对此次比赛的支持。

// 题解等资源可在 <https://github.com/wangyurzee7/THUPC2018> 查看。
#include <bits/stdc++.h>

const int maxN = 1E6 + 5;
int r[maxN << 1];
char tmp[maxN], s[maxN << 1];
std::bitset<maxN> vis;

inline void manacher(int n)
{
    n = (n + 1) << 1;
    int mx_r = 0, mx_c = 0;
    for(int i = 1; i <= n; ++i)
    {
        r[i] = 0;
        if(mx_r > i) r[i] = std::min(mx_r - i, r[(mx_c << 1) - i]);
        while(s[i + r[i] + 1] == s[i - r[i] - 1]) ++r[i];
        if(mx_r < i + r[i]) mx_r = i + r[i], mx_c = i;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
    {
        scanf("%s", tmp + 1);
        int len = strlen(tmp + 1);
        for(int j = 1; j <= len; ++j)
        {
            s[j << 1] = tmp[j];
            s[j << 1 | 1] = '#';
        }
        s[0] = '~', s[1] = '#', s[(len + 1) << 1] = '!';
        manacher(len);

        vis = 0;
        for(int i = len; i; --i)
        {
            if(i + (r[i << 1] >> 1) == len)
            {
                vis[i] = 1;
            }
            else if((r[i << 1] >> 1) == i - 1 && vis[i + (r[i << 1] >> 1)]) vis[i] = 1;
        }
        for(int i = 1; i <= len; ++i)
        {
            if(vis[i]) printf("%d ", i);
        }
        printf("\n");
    }
    return 0;
}