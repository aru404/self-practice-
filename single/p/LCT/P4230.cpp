// # 连环病原体

// ## 题目背景

// ###（一）洞穴

// 顺着狭窄倾斜的溶洞向下走，这里，真有一番地心探险的感觉呢。

// 告诉你啊，地底有一片广阔的大世界，叫做旧地狱。

// 那里居住着被地面上的人厌恶的妖怪们。

// 虽然听着比较吓人，但实际上在地狱废弃后，一切都是井井有条的。

// 前方有一片开阔的空间啊，好像有人。

// "地面上的来客吗,你好啊"

// 终于遇到地底的居民了。

// 眼前的两只妖怪是黑谷山女和琪斯美。

// 琪斯美呆在一个小桶里，悬挂在空中，和山女讨论着什么。

// "哇，你们在讨论什么啊"

// "嗯，有关病毒的问题，你们不懂的"

// 忘记说了，山女可以操纵疾病，所以谈论这样的话题自然也就很平常了。

// 不过好奇心很难抵挡啊，那就假装自己能帮上忙，然后接着问下去吧。

// "好吧，你们要是能帮上忙的话就再好不过了"

// "嗯，主要是，想知道病原体之间的相互作用，会对疾病产生什么影响呢。你看啊，把不同种的病原体看做点，相互作用看成连接这些点的线，如果产生了环，那么病毒的威力就会大幅加强，我把它叫做加强环。"

// "病原体之间的相互作用也有很多种呢，我想研究的是，每种相互作用在产生加强环的过程中有多么重要。"

// 啊，听起来好复杂，不过如果帮了她的忙，地底的妖怪们大概会对我们友善一些吧。

// 而且，点，边，环？这些名词似乎见过呢，说不定我真的能帮上忙？

// 那么，继续详细地询问吧。

// 嗯，问出来的信息已经记录在这张纸上了。

// ## 题目描述

// 问题摘要:

// 有n 种病原体，它们之间会产生$m$种无方向性的影响，第$i$种影响发生在$u_i$,$v_i$ **两种**病原体之间。

// 我们把所有的**影响**按编号顺序排成一个序列，如果某一个区间包含有环，那么这个区间被称作加强区间。

// 求每种影响分别在多少个加强区间中出现过。

// 那么，到底怎样做才能高效的得出结果呢？

// (后续剧情见本题题解，接下来请看T2)

// ## 输入格式

// 第一行一个数$m$
// 接下来$m$行每行两个数$u_i$,$v_i$，用空格分隔

// ## 输出格式

// 一行$m$个数字，第$i$个数字代表第$i$种影响在多少个加强区间内出现过，数字之间用空格分隔

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5
// 1 2
// 2 3
// 3 4
// 1 4
// 4 2
// ```

// ### 样例输出 #1

// ```
// 2 3 3 3 2
// ```

// ## 提示

// ###样例解释：

// 第一种影响在[1,4]和[1,5]两个加强区间内出现

// 第二种影响在[1,4]、[1,5]和[2,5]三个加强区间内出现

// 第三种影响在[1,5]、[1,4]和[2,5]三个加强区间内出现

// 第四种影响在[1,4]、[2,5]和[1,5]三个加强区间内出现

// 第五种影响在[2,5]和[1,5]两个加强区间内出现

// 注意：加强区间是由“影响”构成的，而不是由“病原体”构成的

// $n\leqslant2m\leqslant400000$

// 测试点1~2总分10分，$m\leqslant5$

// 测试点3~6总分20分，$m\leqslant200$

// 测试点7~12总分30分，$m\leqslant5000$

// 测试点13~15总分15分，$m\leqslant50000$

// 测试点16~18总分15分，$m\leqslant50000$，捆绑测试

// 测试点19~22总分10分，$m\leqslant200000$，捆绑测试

// by oscar
#include <iostream>
#include <bits/stdc++.h>
#define ll long long

const int maxN = 2E5 + 5, maxM = 6E5 + 5;

namespace LCT{
    #define ls(x) ch[x][0]
    #define rs(x) ch[x][1]
    #define get(x) (ch[f[x]][1] == x)
    #define isRoot(x) (ch[f[x]][get(x)] != x)

    int f[maxM], ch[maxM][2], mn[maxM], id[maxM], s[maxM];
    bool tag[maxM];

    inline void pushUp(int x){
        mn[x] = std::min({id[x], mn[ls(x)], mn[rs(x)]});
    }

    inline void pushDown(int x){
        if(tag[x]){
            if(ls(x)) tag[ls(x)] ^= 1, std::swap(ls(ls(x)), rs(ls(x)));
            if(rs(x)) tag[rs(x)] ^= 1, std::swap(ls(rs(x)), rs(rs(x)));
            tag[x] = 0;
        }
    }

    inline void rotate(int x){
        int y = f[x], z = f[y], k = get(x);
        if(!isRoot(y)) ch[z][get(y)] = x;
        if(ch[x][!k]) f[ch[x][!k]] = y;
        ch[y][k] = ch[x][!k], ch[x][!k] = y;
        f[x] = z, f[y] = x;
        pushUp(y), pushUp(x);
    }

    inline void updata(int x){
        int idx = 0;
        s[++idx] = x;
        while(!isRoot(x)) x = f[x], s[++idx] = x;
        while(idx) pushDown(s[idx--]);
    }

    inline void splay(int x){
        updata(x);
        for(int fa = f[x]; !isRoot(x); rotate(x), fa = f[x]){
            if(!isRoot(fa)) rotate(get(x) ^ get(fa)? x:fa);
        }
    }

    inline int access(int x){
        int p;
        for(p = 0; x; p = x, x = f[x]){
            splay(x), rs(x) = p, pushUp(x);
        }
        return p;
    }

    inline void makeRoot(int x){
        access(x);
        splay(x);
        tag[x] ^= 1, std::swap(ls(x), rs(x));
    }

    inline int findRoot(int x){
        access(x);
        splay(x);
        while(ls(x)) pushDown(x), x = ls(x);
        splay(x);
        return x;
    }

    inline void split(int x, int y){
        makeRoot(x);
        access(y);
        splay(y);
    }

    inline void link(int x, int y){
        makeRoot(x);
        f[x] = y;
    }
    
    inline void cut(int x, int y){
        split(x, y);
        ls(y) = f[x] = 0;
        pushUp(y);
    }
}

int u[maxN], v[maxN];
ll diff[maxN];

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m;
    std::cin >> m;
    for(int i = 1; i <= m; i++){
        std::cin >> u[i] >> v[i];
        u[i] += m, v[i] += m;
        LCT::mn[u[i]] = LCT::mn[v[i]] = LCT::id[u[i]] = LCT::id[v[i]] = 0X3f3f3f3f;
    }
    for(int i = 1; i <= m; i++) LCT::mn[i] = LCT::id[i] = i;
    LCT::mn[0] = LCT::id[0] = 0X3f3f3f3f;

    int pre = 0;

    for(int i = 1; i <= m; i++){
        if(u[i] == v[i]) pre = i;
        else{
            LCT::split(u[i], v[i]);
            if(LCT::findRoot(v[i]) == u[i]){
                int l = LCT::mn[u[i]];
                LCT::cut(l, u[l]), LCT::cut(l, v[l]);
                pre = std::max(pre, l);
            }
            LCT::link(i, u[i]);
            LCT::link(i, v[i]);
        }
        diff[1] += 1, diff[pre + 1] -= 1, diff[i + 1] -= pre, diff[i + 2] += pre;
    }

    ll cnt = 0, sum = 0;
    for(int i = 1; i <= m; i++) cnt += diff[i], sum += cnt, std::cout << sum << ' ';
    return 0;
}