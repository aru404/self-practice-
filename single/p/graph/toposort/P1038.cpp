// # [NOIP2003 提高组] 神经网络

// ## 题目背景

// 人工神经网络（Artificial Neural Network）是一种新兴的具有自我学习能力的计算系统，在模式识别、函数逼近及贷款风险评估等诸多领域有广泛的应用。对神经网络的研究一直是当今的热门方向，兰兰同学在自学了一本神经网络的入门书籍后，提出了一个简化模型，他希望你能帮助他用程序检验这个神经网络模型的实用性。

// ## 题目描述

// 在兰兰的模型中，神经网络就是一张有向图，图中的节点称为神经元，而且两个神经元之间至多有一条边相连，下图是一个神经元的例子：

// ![](https://cdn.luogu.com.cn/upload/image_hosting/31062648.png)

// 神经元〔编号为 $i$）


// 图中，$X_1 \sim X_3$ 是信息输入渠道，$Y_1 \sim Y_2$ 是信息输出渠道，$C_i$ 表示神经元目前的状态，$U_i$ 是阈值，可视为神经元的一个内在参数。

// 神经元按一定的顺序排列，构成整个神经网络。在兰兰的模型之中，神经网络中的神经元分为几层；称为输入层、输出层，和若干个中间层。每层神经元只向下一层的神经元输出信息，只从上一层神经元接受信息。下图是一个简单的三层神经网络的例子。

// ![](https://cdn.luogu.com.cn/upload/image_hosting/ng1ui4xw.png)

// 兰兰规定，$C_i$ 服从公式：（其中 $n$ 是网络中所有神经元的数目）

// $$C_i=\left(\sum\limits_{(j,i) \in E} W_{ji}C_{j}\right)-U_{i}$$

// 公式中的 $W_{ji}$（可能为负值）表示连接 $j$ 号神经元和 $i$ 号神经元的边的权值。当 $C_i$ 大于 $0$ 时，该神经元处于兴奋状态，否则就处于平静状态。当神经元处于兴奋状态时，下一秒它会向其他神经元传送信号，信号的强度为 $C_i$。

// 如此．在输入层神经元被激发之后，整个网络系统就在信息传输的推动下进行运作。现在，给定一个神经网络，及当前输入层神经元的状态（$C_i$），要求你的程序运算出最后网络输出层的状态。

// ## 输入格式

// 输入文件第一行是两个整数 $n$（$1 \le n \le 100$）和 $p$。接下来 $n$ 行，每行 $2$ 个整数，第 $i+1$ 行是神经元 $i$ 最初状态和其阈值（$U_i$），非输入层的神经元开始时状态必然为 $0$。再下面 $p$ 行，每行有两个整数 $i,j$ 及一个整数 $W_{ij}$，表示连接神经元 $i,j$ 的边权值为 $W_{ij}$。

// ## 输出格式

// 输出文件包含若干行，每行有 $2$ 个整数，分别对应一个神经元的编号，及其最后的状态，$2$ 个整数间以空格分隔。仅输出最后状态大于 $0$ 的输出层神经元状态，并且按照编号由小到大顺序输出。

// 若输出层的神经元最后状态均小于等于 $0$，则输出 `NULL`。

// ## 样例 #1

// ### 样例输入 #1

// ```
// 5 6
// 1 0
// 1 0
// 0 1
// 0 1
// 0 1
// 1 3 1
// 1 4 1
// 1 5 1
// 2 3 1
// 2 4 1
// 2 5 1
// ```

// ### 样例输出 #1

// ```
// 3 1
// 4 1
// 5 1
// ```

// ## 提示

// **【题目来源】**

// NOIP 2003 提高组第一题
#include <iostream>
#include <bits/stdc++.h>

const int maxN = 105;
int u[maxN], in[maxN], c[maxN];
std::vector<int> es[maxN], w[maxN];

inline void toposort(int n){
    std::queue<int> q;
    for(int i = 1; i <= n; i++){
        if(!in[i]) q.emplace(i), u[i] = 0;
    }
    while(!q.empty()){
        int top = q.front();
        q.pop();
        int m = es[top].size();
        for(int i = 0; i < m; i++){
            int& to = es[top][i], &we = w[top][i];
            in[to]--;
            c[to] += we * std::max(0, c[top] - u[top]);
            if(!in[to]) q.emplace(to);
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, p, from, to, we;
    std::cin >> n >> p;
    for(int i = 1; i <= n; i++){
        std::cin >> c[i] >> u[i];
    }
    for(int i = 0; i < p; i++){
        std::cin >> from >> to >> we;
        in[to]++, es[from].push_back(to), w[from].push_back(we);
    }
    toposort(n);
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        if(es[i].empty() && c[i] > u[i]){
            std::cout << i << ' ' << c[i] - u[i] << std::endl;
            cnt++;
        }
    }
    if(!cnt) std::cout << "NULL";
    return 0;
}