// # [SHOI2007] 园丁的烦恼

// ## 题目背景

// 很久很久以前，在遥远的大陆上有一个美丽的国家。统治着这个美丽国家的国王是一个园艺爱好者，在他的皇家花园里种植着各种奇花异草。

// 有一天国王漫步在花园里，若有所思，他问一个园丁道： “最近我在思索一个问题，如果我们把花坛摆成六个六角形，那么……”

// “那么本质上它是一个深度优先搜索，陛下。”园丁深深地向国王鞠了一躬。

// “嗯……我听说有一种怪物叫九头蛇，它非常贪吃苹果树……”

// “是的，显然这是一道经典的动态规划题，早在 N 元 $4002$ 年我们就已经发现了其中的奥秘了，陛下。”

// “该死的，你究竟是什么来头？”

// “陛下息怒，干我们的这行经常莫名其妙地被问到和 OI 有关的题目，我也是为了预防万一啊！” 王者的尊严受到了伤害，这是不可容忍的。

// ## 题目描述

// 看来一般的难题是难不倒这位园丁的，国王最后打算用车轮战来消耗他的实力： “年轻人，在我的花园里有 $n$ 棵树，每一棵树可以用一个整数坐标来表示，一会儿，我的 $m$ 个骑士们会来轮番询问你某一个矩阵内有多少树，如果你不能立即答对，你就准备走人吧！”说完，国王气呼呼地先走了。

// 这下轮到园丁傻眼了，他没有准备过这样的问题。所幸的是，作为“全国园丁保护联盟”的会长——你，可以成为他的最后一根救命稻草。

// ## 输入格式

// 第一行有两个整数 $n, m$，分别表示树木个数和询问次数。

// 接下来 $n$ 行，每行两个整数 $x, y$，表示存在一棵坐标为 $(x, y)$ 的树。有可能存在两棵树位于同一坐标。

// 接下来 $m$ 行，每行四个整数 $a, b, c, d$，表示查询以 $(a, b)$ 为左下角，$(c, d)$ 为右上角的矩形内部（包括边界）有多少棵树。

// ## 输出格式

// 对于每个查询，输出一行一个整数表示答案。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 3 1
// 0 0 
// 0 1
// 1 0
// 0 0 1 1
// ```

// ### 样例输出 #1

// ```
// 3
// ```

// ## 提示

// #### 数据规模与约定

// - 对于 $30\%$ 的数据，保证 $n, m \leq 10$。
// - 对于 $100\%$ 的数据，保证 $0 \leq n \leq 5 \times 10^5$，$1 \leq m \leq 5 \times 10^5$，$0 \leq x, y, a, b, c, d \leq 10^7$，$a \leq c$，$b \leq d$。
#include <iostream>
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)

const int maxN = 5E5 + 5, maxM = 15E5 + 5, inf = 0X3f3f3f3f;
int x[maxM], y[maxM], a[maxN], b[maxN], c[maxN], d[maxN];
int s1[maxM], s2[maxM], s[maxM], res[maxN];
int cnt[maxM], rk[maxM], k, n, m;

inline void init(int t){
    std::iota(s, s + t + 1, 0);
    std::sort(s + 1, s + t + 1, [&](const int& a1, const int& a2){return y[a1] < y[a2];});
    int pre = -1;
    for(int i = 1; i <= t; i++){
        if(pre < y[s[i]]) ++k, pre = y[s[i]];
        rk[s[i]] = k;
    }
    x[0] = inf;
}

inline void updata(int x, int v){
    while(x <= k) cnt[x] += v, x += lowbit(x);
}

inline int query(int x){
    int res = 0;
    while(x) res += cnt[x], x -= lowbit(x);
    return res;
}

inline void cdq(int l, int r, bool f){
    if(l == r) return ;
    int mid = (l + r) >> 1;
    cdq(l, mid, f), cdq(mid + 1, r, f);
    for(int i = l; i <= mid; i++) s1[i - l + 1] = s[i];
    for(int i = mid + 1; i <= r; i++) s2[i - mid] = s[i];
    s1[mid - l + 2] = s2[r - mid + 1] = 0;
    int idx1 = 1, idx2 = 1;
    for(int i = l; i <= r; i++){
        if(x[s1[idx1]] <= x[s2[idx2]]){
            if(s1[idx1] <= n) updata(rk[s1[idx1]], 1);
            s[i] = s1[idx1++];
        }
        else{
            if(s2[idx2] > n){
                if(f) res[(s2[idx2] - n - 1) % m + 1] += query(rk[s2[idx2]]);
                else res[(s2[idx2] - n - 1) % m + 1] -= query(rk[s2[idx2]]);
            }
            s[i] = s2[idx2++];
        }
    }
    for(int i = 1; i <= mid - l + 1; i++) if(s1[i] <= n) updata(rk[s1[i]], -1);
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n >> m;
    int t = n + 2 * m;
    for(int i = 1; i <= n; i++) std::cin >> x[i] >> y[i];
    for(int i = 1; i <= m; i++) std::cin >> a[i] >> b[i] >> c[i] >> d[i];
    for(int i = n + 1; i <= n + m; i++) x[i] = a[i - n] - 1, y[i] = b[i - n] - 1;
    for(int i = n + m + 1; i <= t; i++) x[i] = c[i - n - m], y[i] = d[i - n - m];
    init(t);
    std::iota(s, s + t + 1, 0);
    cdq(1, t, 1);
    for(int i = n + 1; i <= n + m; i++) x[i] = c[i - n];
    for(int i = n + m + 1; i <= t; i++) x[i] = a[i - n - m] - 1;
    std::iota(s, s + t + 1, 0);
    cdq(1, t, 0);
    for(int i = 1; i <= m; i++) std::cout << res[i] << '\n';
    return 0;
}