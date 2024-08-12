// # [JLOI2013] 删除物品

// ## 题目描述

// 箱子再分配问题需要解决如下问题：

// 1. 一共有 $N$ 个物品，堆成 $M$ 堆。

// 2. 所有物品都是一样的，但是它们有不同的优先级。

// 3. 你只能够移动某堆中位于顶端的物品。

// 4. 你可以把任意一堆中位于顶端的物品移动到其它某堆的顶端。若此物品是当前所有物品中优先级最高的，可以直接将之删除而不用移动。

// 5. 求出将所有物品删除所需的最小步数。删除操作不计入步数之中。

// 6. 这是一个比较难解决的问题，这里你只需要解决一个比较简单的版本：不会有两个物品有着相同的优先级，且 $M=2$。

// ## 输入格式

// 第一行是包含两个整数 $N_1$, $N_2$ 分别表示两堆物品的个数。接下来有 $N_1$ 行整数按照从顶到底的顺序分别给出了第一堆物品中的优先级，数字越大，优先级越高。再接下来的 $N_2$ 行按照同样的格式给出了第二堆物品的优先级。

// ## 输出格式

// 对于每个数据，请输出一个整数，即最小移动步数。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 3
// 1
// 4
// 5
// 2
// 7
// 3
// ```

// ### 样例输出 #1

// ```
// 6
// ```

// ## 提示

// $1\leq N_1+N_2\leq 100000$
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 1E5 + 5;
int n;
struct node{
    int s, id, v;
}s[maxN];

namespace BIT{
    #define lowbit(x) (x & -x)

    int tree[maxN], tmp[maxN];
    
    inline void updata(int x, int v){
        while(x <= n) tree[x] += v, x += lowbit(x);
    }

    inline int query(int x){
        int res = 0;
        while(x) res += tree[x], x -= lowbit(x);
        return res;
    }

    inline int query(int l, int r){
        return l > r? 0:query(r) - query(l - 1);
    }

    inline void init(int n1, int n2){
        n = n1 + n2;
        for(int i = 1; i <= n; i++){
            std::cin >> s[i].v;
        }
        for(int i = 1; i <= n1; i++) s[i].s = 1, s[i].id = i;
        for(int i = 1; i <= n2; i++) s[i + n1].s = 2, s[i + n1].id = i;
        for(int i = 1; i <= n; i++) updata(i, 1);
        std::sort(s + 1, s + n + 1, [&](const node& a, const node& b){return a.v > b.v;});
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n1, n2;
    std::cin >> n1 >> n2;
    BIT::init(n1, n2);
    long long res = 0;
    int idx1 = n1, idx2 = n1 + 1;
    for(int i = 1; i <= n; i++){
        int id = s[i].s == 1? n1 + 1 - s[i].id:n1 + s[i].id;
        if(id <= idx1) res += BIT::query(id, idx1) - 1;
        else res += BIT::query(idx2, id) -1;
        BIT::updata(id, -1);
        idx1 = idx2 = id;
    }
    std::cout << res;
    return 0;
}