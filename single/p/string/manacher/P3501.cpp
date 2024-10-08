// # [POI2010] ANT-Antisymmetry

// ## 题目描述

// Byteasar studies certain strings of zeroes and ones.

// Let ![](http://main.edu.pl/images/OI17/ant-en-tex.1.png) be such a string. By ![](http://main.edu.pl/images/OI17/ant-en-tex.2.png) we will denote the reversed (i.e., "read backwards") string ![](http://main.edu.pl/images/OI17/ant-en-tex.3.png),    and by ![](http://main.edu.pl/images/OI17/ant-en-tex.4.png) we will denote the string obtained from ![](http://main.edu.pl/images/OI17/ant-en-tex.5.png) by changing all the zeroes to ones and ones to zeroes.

// Byteasar is interested in antisymmetry, while all things symmetric bore him.

// Antisymmetry however is not a mere lack of symmetry.

// We will say that a (nonempty) string ![](http://main.edu.pl/images/OI17/ant-en-tex.6.png) is antisymmetric if, for every position ![](http://main.edu.pl/images/OI17/ant-en-tex.7.png) in ![](http://main.edu.pl/images/OI17/ant-en-tex.8.png),    the ![](http://main.edu.pl/images/OI17/ant-en-tex.9.png)-th last character is different than the ![](http://main.edu.pl/images/OI17/ant-en-tex.10.png)-th (first) character.

// In particular, a string ![](http://main.edu.pl/images/OI17/ant-en-tex.11.png) consisting of zeroes and ones is antisymmetric if and only if    ![](http://main.edu.pl/images/OI17/ant-en-tex.12.png).

// For example, the strings 00001111 and 010101 are antisymmetric, while 1001 is not.

// In a given string consisting of zeroes and ones we would like to determine the number of contiguous    nonempty antisymmetric fragments.

// Different fragments corresponding to the same substrings should be counted multiple times.

// 对于一个01字符串，如果将这个字符串0和1取反后，再将整个串反过来和原串一样，就称作“反对称”字符串。比如00001111和010101就是反对称的，1001就不是。

// 现在给出一个长度为N的01字符串，求它有多少个子串是反对称的。

// ## 输入格式

// The first line of the standard input contains an integer ![](http://main.edu.pl/images/OI17/ant-en-tex.13.png) (![](http://main.edu.pl/images/OI17/ant-en-tex.14.png)) that denotes the length of the string.

// The second line gives a string of 0 and/or 1 of length ![](http://main.edu.pl/images/OI17/ant-en-tex.15.png).

// There are no spaces in the string.

// ## 输出格式

// The first and only line of the standard output should contain a single integer,      namely the number of contiguous (non empty) fragments of the given string      that are antisymmetric.

// ## 样例 #1

// ### 样例输入 #1

// ```
// 8
// 11001011
// ```

// ### 样例输出 #1

// ```
// 7
// ```

// ## 提示

// 7个反对称子串分别是：01（出现两次），10（出现两次），0101，1100和001011

// $n \le 5 \times 10^5$

#include <bits/stdc++.h>

const int maxN = 5E5 + 5;
int s[maxN << 1];
int r[maxN << 1];

inline long long mancher(int n)
{
    int mx_c = 0, mx_r = 0;
    // 只有偶串是对的
    for(int i = 1; i < n; i += 2)
    {
        if(mx_r > i) r[i] = std::min(mx_r - i, r[(mx_c << 1) - i]);
        while(s[i + r[i] + 1] == 3 || s[i + r[i] + 1] + s[i - r[i] - 1] == 1) ++r[i];
        if(mx_r < r[i] + i) mx_r = r[i] + i, mx_c = i; 
    }

    long long res = 0;
    for(int i = 1; i < n; i += 2)
    {
        res += r[i] >> 1;
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    s[0] = 2;
    s[1] = 3;
    int n;
    std::cin >> n;
    std::string tmp_s;
    std::cin >> tmp_s;
    
    for(int i = 1; i <= n; ++i)
    {
        s[i << 1] = tmp_s[i - 1] ^ 48;
        s[i << 1 | 1] = 3;
    }
    s[(n + 1) << 1] = 4;
    std::cout << mancher((n + 1) << 1);
    return 0;
}