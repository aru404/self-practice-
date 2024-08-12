// # 【模板】有理数取余

// ## 题目描述

// 给出一个有理数 $c=\frac{a}{b}$，求 $c \bmod 19260817$ 的值。

// 这个值被定义为 $bx\equiv a\pmod{19260817}$ 的解。

// ## 输入格式

// 一共两行。

// 第一行，一个整数 $a$。  
// 第二行，一个整数 $b$。

// ## 输出格式

// 一个整数，代表求余后的结果。如果无解，输出 `Angry!`。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 233
// 666
// ```

// ### 样例输出 #1

// ```
// 18595654
// ```

// ## 提示

// 对于所有数据，保证 $0\leq a \leq 10^{10001}$，$1 \leq b \leq 10^{10001}$，且 $a, b$ 不同时是 $19260817$ 的倍数。
#include <iostream>
#include <bits/stdc++.h>

const int mod = 19260817;
int cst[9];

inline int getMod(std::string& s){
    int res = 0;
    auto it = s.begin();
    while(it != s.end()){
        int cnt = 0, tmp = 0;
        while(cnt < 8 && it != s.end()){
            tmp = (tmp << 3) + (tmp << 1) + (*(it++) ^ 48);
            cnt++;
        }
        res = (1ll * res * cst[cnt] % mod + tmp % mod) % mod;
    }
    return res;
}

inline int qpow(int a, int p){
    int res = 1;
    while(p){
        if(p & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        p >>= 1;
    }
    return res;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string a, b;
    std::cin >> a >> b;

    cst[0] = 1;
    for(int i = 0; i < 8; i++) cst[i + 1] = ((cst[i] << 3) + (cst[i] << 1)) % mod;
    int na = getMod(a), nb = getMod(b);
    if(nb) std::cout << 1ll * na * qpow(nb, mod - 2) % mod;
    else std::cout << "Angry!";
    return 0;
}