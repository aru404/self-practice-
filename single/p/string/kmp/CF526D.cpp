// # Om Nom and Necklace

// ## 题面翻译

// 已知长度为 $n$ 的字符串 $s$，对于 $s$ 的每一个前缀子串（即对于每一个 $i$，$s$ 中从第 $1$ 个字符到第 $i$ 个的所有字符组成的字符串，$1\leq i\leq n$），如果满足 $\texttt{ABABA...BA}$ 的形式（$A$、$B$ 可以为空，也可以是一个字符串，$A$ 有 $k+1$ 个，$B$ 有 $k$ 个），则请输出 $1$；否则输出 $0$，注意：$n$ 和 $k$ 给定。

// ## 题目描述

// One day Om Nom found a thread with $ n $ beads of different colors. He decided to cut the first several beads from this thread to make a bead necklace and present it to his girlfriend Om Nelly.

//  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF526D/76315fd43cfbe5e147469d75b9c643c18f6f5673.png)Om Nom knows that his girlfriend loves beautiful patterns. That's why he wants the beads on the necklace to form a regular pattern. A sequence of beads $ S $ is regular if it can be represented as $ S=A+B+A+B+A+...+A+B+A $ , where $ A $ and $ B $ are some bead sequences, " $ + $ " is the concatenation of sequences, there are exactly $ 2k+1 $ summands in this sum, among which there are $ k+1 $ " $ A $ " summands and $ k $ " $ B $ " summands that follow in alternating order. Om Nelly knows that her friend is an eager mathematician, so she doesn't mind if $ A $ or $ B $ is an empty sequence.

// Help Om Nom determine in which ways he can cut off the first several beads from the found thread (at least one; probably, all) so that they form a regular pattern. When Om Nom cuts off the beads, he doesn't change their order.

// ## 输入格式

// The first line contains two integers $ n $ , $ k $ ( $ 1<=n,k<=1000000 $ ) — the number of beads on the thread that Om Nom found and number $ k $ from the definition of the regular sequence above.

// The second line contains the sequence of $ n $ lowercase Latin letters that represent the colors of the beads. Each color corresponds to a single letter.

// ## 输出格式

// Print a string consisting of $ n $ zeroes and ones. Position $ i $ ( $ 1<=i<=n $ ) must contain either number one if the first $ i $ beads on the thread form a regular sequence, or a zero otherwise.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 7 2
// bcabcab
// ```

// ### 样例输出 #1

// ```
// 0000011
// ```

// ## 样例 #2

// ### 样例输入 #2

// ```
// 21 2
// ababaababaababaababaa
// ```

// ### 样例输出 #2

// ```
// 000110000111111000011
// ```

// ## 提示

// In the first sample test a regular sequence is both a sequence of the first 6 beads (we can take $ A= $ "", $ B= $ "bca"), and a sequence of the first 7 beads (we can take $ A= $ "b", $ B= $ "ca").

// In the second sample test, for example, a sequence of the first 13 beads is regular, if we take $ A= $ "aba", $ B= $ "ba".
#include <bits/stdc++.h>

const int maxN = 1E6 + 5;
int z[maxN], border[maxN];
char s[maxN];
bool vis[maxN];

inline void exKMP(int n, int k)
{
    z[1] = 0;
    int mx_l = 1, mx_r = 1;
    for(int i = 2; i <= n; ++i)
    {
        if(mx_r > i) z[i] = std::min(mx_r - i + 1, z[i - mx_l + 1]);
        while(i + z[i] <= n && s[1 + z[i]] == s[i + z[i]])
        {
            ++z[i];
            border[i + z[i] - 1] = std::max(z[i], border[i + z[i] - 1]);
        }
        if(mx_r < i + z[i] - 1) mx_r = i + z[i] - 1, mx_l = i;
    }

    mx_l = 0, mx_r = 0;
    for(int i = 1; i <= n; ++i)
    {
        int len = i - border[i];
        if(i % len == 0 && (i / len) % k == 0)
        {
            int r = i + std::min(z[i + 1], i / k);
            if(mx_r < i)
            {
                for(int j = mx_l; j <= mx_r; ++j)
                {
                    vis[j] = 1;
                }
                mx_r = r, mx_l = i;
            }
            else mx_r = std::max(mx_r, r);
        }
    }

    for(int i = mx_l; i <= mx_r; ++i)
    {    
        vis[i] = 1;
    }
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    scanf("%s", s + 1);

    exKMP(n, k);
    for(int i = 1; i <= n; ++i) std::cout << vis[i];
    return 0;
}