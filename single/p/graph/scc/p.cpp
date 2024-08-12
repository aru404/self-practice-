#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int to, next;
    edge(int to, int next):to(to), next(next){}
};

class Solution {
public:
    int minMalwareSpread(const vector<vector<int>>& graph, const vector<int>& initial) {
        int n = graph.size(), tot = 0, scc = n, top = 0, m, k;
        vector<int> head(n, -1), new_head(n << 1, -1);
        vector<edge> edges, new_edges;
        vector<int> dfn(n, 0), low(n, 0), stk(n + 1, 0), sz(n << 1, 0), cnt(n << 1, 0), g(n << 1, 0);
        bitset<301> isVirus = 0;

        auto add = [](int u, int v, vector<edge>& es, vector<int>& hs)->void
        {
            es.push_back(edge(v, hs[u]));
            hs[u] = es.size() - 1;
        };

        function<void(int, int)> tarjan = [&](int u, int pre)->void
        {
            dfn[u] = low[u] = ++tot;
            stk[++top] = u;

            for(int e = head[u]; ~e; e = edges[e].next)
            {
                int &v = edges[e].to;
                if(!dfn[v])
                {
                    tarjan(v, e);
                    low[u] = min(low[u], low[v]);
                    if(dfn[u] == low[v])
                    {
                        do{
                            add(stk[top], scc, new_edges, new_head);
                            add(scc, stk[top], new_edges, new_head);
                        }while(stk[top--] != v);
                        add(u, scc, new_edges, new_head);
                        add(scc, u, new_edges, new_head);
                        ++scc;
                    }
                }
                else low[u] = min(low[u], dfn[v]);
            }
        };

        function<void(int, int)> dfs1 = [&](int u, int fa)->void
        {
            for(int e = new_head[u]; ~e; e = new_edges[e].next)
            {
                int &v = new_edges[e].to;
                if(v == fa) continue;
                dfs1(v, u);
                sz[u] += sz[v];
                cnt[u] += cnt[v];
                if(!cnt[v]) g[u] += sz[v];
            }
            if(u < n)
            {
                ++sz[u];
                cnt[u] += isVirus[u];
            }
        };

        function<void(int, int)> dfs2 = [&](int u, int fa)->void
        {
            for(int e = new_head[u]; ~e; e = new_edges[e].next)
            {
                int &v = new_edges[e].to;
                if(v == fa) continue;
                g[v] += (cnt[v] == k)? m - sz[v]:0;
                dfs2(v, u);
            }
        };

        for(int i = 0; i < n; ++i)
        {
            for(int j = i + 1; j < n; ++j)
            {
                if(!graph[i][j]) continue;
                add(i, j, edges, head);
                add(j, i, edges, head);
            }
        }
        for(auto u:initial)
        {
            isVirus[u] = 1;
        }

        for(int i = 0; i < n; ++i)
        {
            if(!dfn[i])
            {
                tarjan(i, -1);
                dfs1(i, -1);
                k = cnt[i], m = sz[i];
                dfs2(i, -1);
            }
        }
        int res = 0, mx = -1;
        
        for(auto u:initial)
        {
            if(mx < g[u])
            {
                mx = g[u];
                res = u;
            }
            else if(mx == g[u]) res = min(u, res);
        }

        return res;
    }
};

int main()
{
    Solution solve;
    std::cout << solve.minMalwareSpread({{1,1,0},{1,1,1},{0,1,1}}, {0, 1});
    return 0;
}