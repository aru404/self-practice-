// # [HNOI2008] GT考试

// ## 题目描述

// 阿申准备报名参加 GT 考试，准考证号为 $N$ 位数$X_1,X_2…X_n\ (0\le X_i\le 9)$，他不希望准考证号上出现不吉利的数字。
// 他的不吉利数字$A_1,A_2,\cdots, A_m\ (0\le A_i\le 9)$ 有 $M$ 位，不出现是指 $X_1,X_2\cdots X_n$ 中没有恰好一段等于 $A_1,A_2,\cdots ,A_m$，$A_1$ 和 $X_1$ 可以为 $0$。

// ## 输入格式

// 第一行输入 $N,M,K$ 接下来一行输入 $M$ 位的数。

// ## 输出格式

// 阿申想知道不出现不吉利数字的号码有多少种，输出模 $K$ 取余的结果。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 4 3 100
// 111
// ```

// ### 样例输出 #1

// ```
// 81
// ```

// ## 提示

// ### 数据范围及约定

// 对于全部数据，$N\leq10^9$，$M\leq 20$，$K\leq1000$。
#include <bits/stdc++.h>

char s[22];
int kmp[22], mod;

struct matrix
{
    int** mat;
    int m, n;
    matrix(int m, int n):m(m), n(n)
    {
        mat = new int*[m]{};
        for(int i = 0; i < m; ++i) mat[i] = new int[n]{};
    }

    inline int*& operator[](int x)
    {
        return mat[x];
    }
};

inline matrix operator*(matrix a, matrix b)
{
    if(a.n != b.m) throw std::domain_error("Error matrix muliple\n");
    matrix res(a.m, b.n);
    for(int i = 0; i < a.m; ++i)
    {
        for(int j = 0; j < b.n; ++j)
        {
            for(int k = 0; k < a.n; ++k)
            {
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % mod;
            }
        }
    }
    return res;
}

inline void KMP(int m)
{
    kmp[0] = -1;
    for(int i = 2; i <= m; ++i)
    {
        int k = kmp[i - 1];
        while(k && s[k + 1] != s[i]) k = kmp[k];
        kmp[i] = k + (s[k + 1] == s[i]);
    }
}

inline matrix qpow(matrix a, int p)
{
    int m = a.m;
    matrix res(m, m);
    for(int i = 0; i < m; ++i) res[i][i] = 1;
    while(p)
    {
        if(p & 1) res = a * res;
        a = a * a;
        p >>= 1;
    }
    return res;
}

int main()
{
    int n, m;
    scanf("%d %d %d", &n, &m, &mod);
    scanf("%s", s + 1);

    KMP(m);

    matrix a(m, m);

    for(int i = 0; i < m; ++i)
    {
        std::bitset<10> vis = 0;
        
        if(i < m - 1) a[i][i + 1] = 1;
        vis[s[i + 1] - '0'] = 1;
        
        int k = kmp[i];
        while(~k)
        {
            int d = s[k + 1] - '0';
            if(!vis[d]) a[i][k + 1] = 1;
            vis[d] = 1;
            k = kmp[k];
        }
        a[i][0] = 10 - vis.count();
    }

    matrix b(1, m);
    b[0][0] = 1;
    auto res = b * qpow(a, n);
    int tot = 0;
    for(int i = 0; i < m; ++i) tot = (tot + res[0][i]) % mod;
    std::cout << tot;
    return 0;
}