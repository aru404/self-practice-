// # [NOIP2020] 字符串匹配

// ## 题目描述

// 小 C 学习完了字符串匹配的相关内容，现在他正在做一道习题。

// 对于一个字符串 $S$，题目要求他找到 $S$ 的所有具有下列形式的拆分方案数：

// $S = ABC$，$S = ABABC$，$S = ABAB \ldots ABC$，其中 $A$，$B$，$C$ 均是非空字符串，且 $A$ 中出现奇数次的字符数量不超过 $C$ 中出现奇数次的字符数量。

// 更具体地，我们可以定义 $AB$ 表示两个字符串 $A$，$B$ 相连接，例如 $A = \texttt{aab}$，$B = \texttt{ab}$，则 $AB = \texttt{aabab}$。

// 并递归地定义 $A^1=A$，$A^n = A^{n - 1} A$（$n \ge 2$ 且为正整数）。例如 $A = \texttt{abb}$，则 $A^3=\texttt{abbabbabb}$。

// 则小 C 的习题是求 $S = {(AB)}^iC$ 的方案数，其中 $F(A) \le F(C)$，$F(S)$ 表示字符串 $S$ 中出现奇数次的字符的数量。两种方案不同当且仅当拆分出的 $A$、$B$、$C$ 中有至少一个字符串不同。

// 小 C 并不会做这道题，只好向你求助，请你帮帮他。

// ## 输入格式

// 本题有多组数据，输入文件第一行一个正整数 $T$ 表示数据组数。

// 每组数据仅一行一个字符串 $S$，意义见题目描述。$S$ 仅由英文小写字母构成。

// ## 输出格式

// 对于每组数据输出一行一个整数表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3
// nnrnnr
// zzzaab
// mmlmmlo
// ```

// ### 样例输出 #1

// ```
// 8
// 9
// 16
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 5
// kkkkkkkkkkkkkkkkkkkk
// lllllllllllllrrlllrr
// cccccccccccccxcxxxcc
// ccccccccccccccaababa
// ggggggggggggggbaabab
// ```

// ### 样例输出 #2

// ```
// 156
// 138
// 138
// 147
// 194
// ```

// ## 样例 #3

// ### 样例输入 #3

// ```
// 见附件中的 string/string3.in
// ```

// ### 样例输出 #3

// ```
// 见附件中的 string/string3.ans
// ```

// ## 样例 #4

// ### 样例输入 #4

// ```
// 见附件中的 string/string4.in
// ```

// ### 样例输出 #4

// ```
// 见附件中的 string/string4.ans
// ```

// ## 提示

// **【样例 #1 解释】**

// 对于第一组数据，所有的方案为

// 1. $A=\texttt{n}$，$B=\texttt{nr}$，$C=\texttt{nnr}$。
// 2. $A=\texttt{n}$，$B=\texttt{nrn}$，$C=\texttt{nr}$。
// 3. $A=\texttt{n}$，$B=\texttt{nrnn}$，$C=\texttt{r}$。
// 4. $A=\texttt{nn}$，$B=\texttt{r}$，$C=\texttt{nnr}$。
// 5. $A=\texttt{nn}$，$B=\texttt{rn}$，$C=\texttt{nr}$。
// 6. $A=\texttt{nn}$，$B=\texttt{rnn}$，$C=\texttt{r}$。
// 7. $A=\texttt{nnr}$，$B=\texttt{n}$，$C=\texttt{nr}$。
// 8. $A=\texttt{nnr}$，$B=\texttt{nn}$，$C=\texttt{r}$。

// **【数据范围】**

// | 测试点编号 | $\lvert S \rvert \le$ | 特殊性质 |
// |:-:|:-:|:-:|
// | $1 \sim 4$ | $10$ | 无 |
// | $5 \sim 8$ | $100$ | 无 |
// | $9 \sim 12$ | $1000$ | 无 |
// | $13 \sim 14$ | $2^{15}$ | $S$ 中只包含一种字符 |
// | $15 \sim 17$ | $2^{16}$ | $S$ 中只包含两种字符 |
// | $18 \sim 21$ | $2^{17}$ | 无 |
// | $22 \sim 25$ | $2^{20}$ | 无 |

// 对于所有测试点，保证 $1 \le T \le 5$，$1 \le |S| \le 2^{20}$。
#include <bits/stdc++.h>
#define ll long long
const int maxN = 1 << 20 | 16;

int z[maxN];
char s[maxN];
inline void exKMP(int n)
{
    int mx_l = 0, mx_r = 0;
    z[1] = 0;
    for(int i = 2; i <= n; ++i)
    {
        z[i] = 0;
        if(mx_r > i) z[i] = std::min(mx_r - i + 1, z[i - mx_l + 1]);
        while(i + z[i] - 1 < n && s[i + z[i]] == s[1 + z[i]]) ++z[i];
        if(mx_r < i + z[i] - 1) mx_r = i + z[i] - 1, mx_l = i; 
    }
}

inline ll cntRes(int n)
{
    int suf = 0, pre = 0;
    for(int i = 1; i <= n; ++i)
    {
        int k = 1 << (s[i] - 'a');
        suf ^= k;
    }

    int totR = 0;
    for(int i = 0; i < 26; ++i) if(suf & (1 << i)) ++totR;

    int bucket[26] = {};
    int cnt1 = 0, cnt2 = 0, pre_cnt = 0, suf_cnt = totR;
    
    ll res = 0;
    for(int i = 2; i <= n; ++i)
    {
        int k = 1 << (s[i - 1] - 'a');
        suf ^= k, pre ^= k;
        if(suf & k) cnt1 += bucket[++suf_cnt];
        else cnt1 -= bucket[suf_cnt--];
        if(pre & k) ++bucket[++pre_cnt];
        else ++bucket[--pre_cnt];

        int mx = std::min(z[i], n - i) / (i - 1) + 1;
        int l = (mx + 1) >> 1, r = mx >> 1;

        res += 1ll * l * cnt1 + 1ll * r * cnt2;

        if(pre_cnt <= totR) ++cnt2;
        if(pre_cnt <= suf_cnt) ++cnt1;
    }
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
    {
        scanf("%s", s + 1);
        int m = ::strlen(s + 1);
        exKMP(m);
        printf("%lld\n", cntRes(m));
    }
    return 0;
}