#include <bits/stdc++.h>

using namespace std;

const int maxN = 1E4 + 5;
class Graph {
private:
    #define ls(x) ch[x][0]
    #define rs(x) ch[x][1]
    #define get(x) (rs(f[x]) == x)
    #define isRoot(x) (ch[f[x]][get(x)] != x)

    int w[maxN], ch[maxN][2], f[maxN], tot[maxN], mx[maxN], cnt = 0, n;
    int from[maxN], to[maxN];
    int *stk;
    bool tag[maxN];

    inline int getMx(int x, int y, int z)
    {
        int mx_v = max({w[x], w[y], w[z]});
        if(mx_v == w[x]) return x;
        if(mx_v == w[y]) return y;
        return z;
    }

    inline void pushUp(int x)
    {
        tot[x] = w[x] + tot[ls(x)] + tot[rs(x)];
        mx[x] = getMx(x, mx[ls(x)], mx[rs(x)]);
    }

    inline void pushDown(int x)
    {
        if(tag[x])
        {
            if(ls(x))
            {
                swap(ls(ls(x)), rs(ls(x)));
                tag[ls(x)] ^= 1;
            }
            if(rs(x))
            {
                swap(ls(rs(x)), rs(rs(x)));
                tag[rs(x)] ^= 1;
            }
            tag[x] = 0;
        }
    }

    inline void rotate(int x)
    {
        int y = f[x], z = f[y], k = get(x);
        if(!isRoot(y)) ch[z][get(y)] = x;
        if(ch[x][!k]) f[ch[x][!k]] = y;
        ch[y][k] = ch[x][!k], ch[x][!k] = y;
        f[y] = x, f[x] = z;
        pushUp(y), pushUp(x);
    }

    inline void updata(int x)
    {
        int top = 0;
        stk[++top] = x;
        if(!isRoot(x)) x = f[x], stk[++top] = x;
        while(top) pushDown(stk[top--]);
    }

    inline void splay(int x)
    {
        updata(x);
        for(int fa = f[x]; !isRoot(x); rotate(x), fa = f[x])
        {
            if(!isRoot(fa)) rotate(get(x) ^ get(fa)? x:fa);
        }
    }

    inline int access(int x)
    {
        int p;
        for(p = 0; x; p = x, x = f[x])
        {
            splay(x);
            rs(x) = p;
            pushUp(x);
        }
        return p;
    }

    inline void makeRoot(int x)
    {
        access(x);
        splay(x);
        tag[x] ^= 1;
        swap(ls(x), rs(x));
    }

    inline int findRoot(int x)
    {
        access(x);
        splay(x);
        while(ls(x)) pushDown(x), x = ls(x);
        splay(x);
        return x;
    }

    inline void split(int x, int y)
    {
        makeRoot(x);
        access(y);
        splay(y);
    }

    inline void link(int x, int y)
    {
        makeRoot(x);
        f[x] = y;
    }

    inline void cut(int x, int y)
    {
        split(x, y);
        ls(y) = f[x] = 0;
        pushUp(y);
    }
public:
    Graph(int n, vector<vector<int>>& edges):n(n){
        stk = new int[n << 1 | 1];
        memset(f, 0, sizeof(f));
        memset(w, 0, sizeof(w));
        memset(ch, 0, sizeof(ch));
        for(auto e:edges)
        {
            addEdge(e);
        }
    }
    
    void addEdge(vector<int> edge) {
        ++cnt;
        w[cnt + n] = edge[2];
        from[cnt] = edge[0] + 1;
        to[cnt] = edge[1] + 1;

        split(from[cnt], to[cnt]);
        if(findRoot(to[cnt]) == from[cnt])
        {
            int mx_id = mx[from[cnt]];
            if(w[mx_id] <= w[cnt + n]) return ;
            cut(from[mx_id - n], mx_id);
            cut(to[mx_id - n], mx_id);
        }
        link(from[cnt], cnt + n);
        link(to[cnt], cnt + n);
    }
    
    int shortestPath(int node1, int node2) {
        ++node1, ++node2;
        split(node1, node2);
        if(findRoot(node2) != node1) return -1;
        return tot[node1];
    }
};

int main()
{
    vector<vector<int>> g = {{0,2,5},{0,1,2},{1,2,1},{3,0,3}};
    Graph gs(4, g);
    std::cout << gs.shortestPath(3, 2) << endl;
    std::cout << gs.shortestPath(3, 0) << endl;
    gs.addEdge({1,3,4});
    std::cout << gs.shortestPath(3, 0) << endl;
    return 0;
}