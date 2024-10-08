// # [NOI2014] 动物园

// ## 题目描述

// 近日，园长发现动物园中好吃懒做的动物越来越多了。例如企鹅，只会卖萌向游客要吃的。为了整治动物园的不良风气，让动物们凭自己的真才实学向游客要吃的，园长决定开设算法班，让动物们学习算法。

// 某天，园长给动物们讲解 KMP 算法。

// 园长：“对于一个字符串 $S$，它的长度为 $L$。我们可以在 $O(L)$ 的时间内，求出一个名为 $\mathrm{next}$ 的数组。有谁预习了 $\mathrm{next}$ 数组的含义吗？”

// 熊猫：“对于字符串 $S$ 的前 $i$ 个字符构成的子串，既是它的后缀又是它的前缀的字符串中（它本身除外），最长的长度记作 $\mathrm{next}[i]$。”

// 园长：“非常好！那你能举个例子吗？”

// 熊猫：“例 $S$ 为 $\verb!abcababc!$，则 $\mathrm{next}[5]=2$。因为$S$的前$5$个字符为 $\verb!abcab!$，$\verb!ab!$ 既是它的后缀又是它的前缀，并且找不到一个更长的字符串满足这个性质。同理，还可得出 $\mathrm{next}[1] = \mathrm{next}[2] = \mathrm{next}[3] = 0$，$\mathrm{next}[4] = \mathrm{next}[6] = 1$，$\mathrm{next}[7] = 2$，$\mathrm{next}[8] = 3$。”

// 园长表扬了认真预习的熊猫同学。随后，他详细讲解了如何在 $O(L)$ 的时间内求出 $\mathrm{next}$ 数组。

// 下课前，园长提出了一个问题：“KMP 算法只能求出 $\mathrm{next}$ 数组。我现在希望求出一个更强大 $\mathrm{num}$ 数组一一对于字符串 $S$ 的前 $i$ 个字符构成的子串，既是它的后缀同时又是它的前缀，并且该后缀与该前缀不重叠，将这种字符串的数量记作 $\mathrm{num}[i]$。例如 $S$ 为 $\verb!aaaaa!$，则 $\mathrm{num}[4] = 2$。这是因为$S$的前 $4$ 个字符为 $\verb!aaaa!$，其中 $\verb!a!$ 和 $\verb!aa!$ 都满足性质‘既是后缀又是前缀’，同时保证这个后缀与这个前缀不重叠。而 $\verb!aaa!$ 虽然满足性质‘既是后缀又是前缀’，但遗憾的是这个后缀与这个前缀重叠了，所以不能计算在内。同理，$\mathrm{num}[1] = 0,\mathrm{num}[2] = \mathrm{num}[3] = 1,\mathrm{num}[5] = 2$。”

// 最后，园长给出了奖励条件，第一个做对的同学奖励巧克力一盒。听了这句话，睡了一节课的企鹅立刻就醒过来了！但企鹅并不会做这道题，于是向参观动物园的你寻求帮助。你能否帮助企鹅写一个程序求出$\mathrm{num}$数组呢？

// 特别地，为了避免大量的输出，你不需要输出 $\mathrm{num}[i]$ 分别是多少，你只需要输出所有 $(\mathrm{num}[i]+1)$ 的乘积，对 $10^9 + 7$ 取模的结果即可。

// ## 输入格式

// 第 $1$ 行仅包含一个正整数 $n$，表示测试数据的组数。  
// 随后 $n$ 行，每行描述一组测试数据。每组测试数据仅含有一个字符串 $S$，$S$ 的定义详见题目描述。数据保证 $S$ 中仅含小写字母。输入文件中不会包含多余的空行，行末不会存在多余的空格。

// ## 输出格式

// 包含 $n$ 行，每行描述一组测试数据的答案，答案的顺序应与输入数据的顺序保持一致。对于每组测试数据，仅需要输出一个整数，表示这组测试数据的答案对 $10^9+7$ 取模的结果。输出文件中不应包含多余的空行。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// aaaaa
// ab
// abcababc
// ```

// ### 样例输出 #1

// ```
// 36
// 1
// 32
// ```

// ## 提示

// 测试点编号| 约定
// -|-  
// 1| $n \le 5, L \le 50$  
// 2| $n \le 5, L \le 200$  
// 3| $n \le 5, L \le 200$  
// 4| $n \le 5, L \le 10,000$  
// 5| $n \le 5, L \le 10,000$  
// 6| $n \le 5, L \le 100,000$  
// 7| $n \le 5, L \le 200,000$   
// 8| $n \le 5, L \le 500,000$  
// 9| $n \le 5, L \le 1,000,000$  
// 10| $n \le 5, L \le 1,000,000$
#include <bits/stdc++.h>
#define ll long long

const int mod = 1E9 + 7;
const int maxN = 1E6 + 5;

struct edge
{
    int to, next;
}edges[maxN];

int kmp[maxN], head[maxN], cnt[maxN], stk[maxN], noe = 0, top = 0;
char s[maxN];
int res = 0;

inline void add(int u, int v)
{
    edges[++noe].to = v, edges[noe].next = head[u];
    head[u] = noe;
}

inline void KMP(int n)
{
    kmp[1] = 0;
    add(0, 1);
    for(int i = 2; i <= n; ++i)
    {
        int k = kmp[i - 1];
        while(k && s[k + 1] != s[i]) k = kmp[k];
        kmp[i] = k + (s[k + 1] == s[i]);
        add(kmp[i], i);
    }
}

inline void dfs(int u, int mid)
{
    if(u) stk[++top] = u;
    while(mid < top && stk[mid + 1] <= (u >> 1)) ++mid;
    res = 1ll * res * (mid + 1) % mod;
    for(int e = head[u]; e; e = edges[e].next)
    {
        int &to = edges[e].to;
        dfs(to, mid);
    }
    stk[top--];
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
    {
        noe = 0, res = 1, top = 0;
        scanf("%s", s + 1);
        int m = strlen(s + 1);
        KMP(m);
        dfs(0, 0);
        std::cout << res << '\n';
        memset(head, 0, sizeof(int) * (m + 1));
    }
    return 0;
}