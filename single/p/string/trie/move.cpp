#include <bits/stdc++.h>
#pragma GCC optimize(2)
const int inf = 0X3f3f3f3f;
const int n = 200;
const int robot_num = 5;

const int maxN = 4E4 + 5;
const int direction[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
const int inv_direction[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
const std::string symbol = "→←↑↓o";
int in_degree[n][n];
int edges[n][n][robot_num + 1][2], stk_idx[n][n];
int len[n][n], son[n][n][2];
int idx[10][2] = {{0, 0}, {0, 1}, {1, 1}, {0, 2}, {0, 4}, {0, 5}, {7, 1}, {8, 1}, {9, 1}, {5, 1}};

std::vector<std::pair<int, int> > f(robot_num);
std::vector<int> next_step(robot_num, 4);
std::bitset<maxN> vis = 0;
std::bitset<maxN> in_stk = 0;
std::bitset<maxN> occupy = 0;
std::unordered_map<int, int> inv_id;
std::mt19937 rnd;
std::uniform_int_distribution<int> un_dist(1, 100);

inline int getId(int x, int y)
{
    return 200 * x + y;
}

inline bool getRnd()
{
    return un_dist(rnd) <= 50;
}

inline int getNextStep(int x, int y, int tx, int ty)
{
    for(int i = 0; i < 4; ++i)
    {
        int nx = x + direction[i][0], ny = y + direction[i][1];
        if(nx == tx && ny == ty) return i;
    }
    return 4;
}

static inline bool checkMap(int x, int y)
{
    return x < 0 || y < 0 || x >= 200 || y >= 200;
}

inline void resetMove()
{
    f.clear();
    f.reserve(robot_num);
    std::fill(next_step.begin(), next_step.end(), 4);
    vis.reset();
    in_stk.reset();
    occupy.reset();
    inv_id.clear();

    for(int i = 0; i < robot_num; ++i)
    {
        auto &x = idx[i][0];
        auto &y = idx[i][1];
        inv_id[getId(x, y)] = i;
        in_degree[x][y] = 0;
        f.push_back(std::make_pair(x, y));
    }
}

inline void setEdges()
{
    for(int i = 0; i < robot_num; ++i)
    {
        int x = f[i].first, y = f[i].second;
        stk_idx[x][y] = 0;
        in_degree[x][y] = 0;
    }

    for(int i = 0; i < robot_num; ++i)
    {
        int x = f[i].first, y = f[i].second;
        if(x == idx[i][0] && y == idx[i][1]) continue;
        ++in_degree[idx[i][0]][idx[i][1]];
        ++stk_idx[x][y];

        edges[x][y][stk_idx[x][y]][0] = idx[i][0];
        edges[x][y][stk_idx[x][y]][1] = idx[i][1];
    }
}

// 链子
void dfs1(int x, int y, int fx = -1, int fy = -1)
{
    int mx_len = 0, tmp_id = getId(x, y);
    vis[tmp_id] = 1;
    son[x][y][0] = son[x][y][1] = -1;
    for(int i = 1; i <= stk_idx[x][y]; ++i)
    {
        auto &tx = edges[x][y][i][0];
        auto &ty = edges[x][y][i][1];
        if(tx == fx && ty == fy) continue;
        dfs1(tx, ty, x, y);
        if(len[tx][ty] > mx_len)
        {
            son[x][y][0] = tx;
            son[x][y][1] = ty;
            mx_len = len[tx][ty];
        }
    }
    len[x][y] = 1 + mx_len;
}
// 环
bool dfs2(int x, int y)
{
    bool hasCyle = 0;
    int tmp_id = getId(x, y);
    if(in_stk[tmp_id]) return 1;
    in_stk[tmp_id] = 1;
    for(int i = 1; i <= stk_idx[x][y]; ++i)
    {
        int tx = edges[x][y][i][0];
        int ty = edges[x][y][i][1];
        if(vis[getId(tx, ty)]) continue;
        son[x][y][0] = tx;
        son[x][y][1] = ty;
        if(dfs2(tx, ty))
        {
            hasCyle = 1;
            break;
        }
    }
    in_stk[tmp_id] = 0;
    vis[tmp_id] = 1;
    return hasCyle;
}

inline bool checkDirection(int x, int y, int nx, int ny)
{
    for(int i = 1; i <= stk_idx[x][y]; ++i)
    {
        if(nx == edges[x][y][i][0] && ny == edges[x][y][i][1]) return 0;
    }

    return 1;
}

inline bool checkNoObstacle(int x, int y, int fx, int fy)
{
    if(stk_idx[x][y] != 1) return 0;
    for(int i = 0; i < 4; ++i)
    {
        int nx = x + direction[i][0], ny = y + direction[i][1];
        if(checkMap(nx, ny) || (nx == fx && ny == fy)) continue;
        f[inv_id[getId(x, y)]] = std::make_pair(nx, ny);
        return 1;
    }
    return 0;
}

inline bool checkNoObstacle(int x, int y)
{
    for(int i = 0; i < 4; ++i)
    {
        int nx = x + direction[i][0], ny = y + direction[i][1];
        if(checkMap(nx, ny) || !checkDirection(x, y, nx, ny)) continue;
        f[inv_id[getId(x, y)]] = std::make_pair(nx, ny);
        return 1;
    }
    return 0;
}

inline void getNext(int x, int y, int fx, int fy)
{
    int tmp_id = inv_id[getId(x, y)];
    bool hasOne = 0, hasObstacle = 1;
    std::stack<std::pair<int, int> > tmp_s;
    for(int i = 0; i < 4; ++i)
    {
        int nx = x + direction[i][0], ny = y + direction[i][1];
        if(checkMap(nx, ny)) continue;
        if(checkDirection(x, y, nx, ny) && (nx != fx || ny != fx))
        {
            hasOne = 1;
            if(!inv_id.count(getId(nx, ny)) && (hasObstacle || getRnd()))
            {
                f[tmp_id] = std::make_pair(nx, ny);
                hasObstacle = 0;
            }
            else if(inv_id.count(getId(nx, ny)))
            {
                tmp_s.emplace(std::make_pair(nx, ny));
            }
        }
    }
    if(hasOne && hasObstacle)
    {
        f[tmp_id] = tmp_s.top();
        tmp_s.pop();
        while(tmp_s.empty())
        {
            if(getRnd()) f[tmp_id] = tmp_s.top();
            tmp_s.pop();
        }
        getNext(f[tmp_id].first, f[tmp_id].second, x, y);
    }
    else if(!hasOne)
    {
        dfs1(x, y);
        int mn_len = inf, mn_idx = -1;
        for(int i = 1; i <= stk_idx[x][y]; ++i)
        {
            int nx = edges[x][y][i][0], ny = edges[x][y][i][1];
            if(mn_len > len[nx][ny] || (mn_len == len[nx][ny] && getRnd()))
            {
                mn_len = len[nx][ny];
                mn_idx = i;
            }
        }
        f[tmp_id] = std::make_pair(edges[x][y][mn_idx][0], edges[x][y][mn_idx][1]);
    }
}

inline void move()
{
    resetMove();
    
    int m, id, next_x, next_y;
    std::cout << "Input the num of edges\n";
    std::cin >> m;

    for(int i = 0; i < m; ++i)
    {
        std::cin >> id >> next_x >> next_y;
        f[id] = std::make_pair(next_x, next_y);
    }

    setEdges();

    // 单对冲
    for(int i = 0; i < robot_num; ++i)
    {
        int x = idx[i][0], y = idx[i][1];
        int tx = f[i].first, ty = f[i].second;
        if((stk_idx[x][y] != 1 && stk_idx[tx][ty] != 1) || checkDirection(x, y, tx, ty)) continue;
        if(!checkNoObstacle(x, y, tx, ty)) checkNoObstacle(tx, ty, x, y);
    }
    setEdges();

    // 自环
    for(int i = 0; i < robot_num; ++i)
    {
        int x = f[i].first, y = f[i].second;
        if(x == idx[i][0] && y == idx[i][1])
        {
            if(!stk_idx[x][y]) continue;
            getNext(x, y, -1, -1);
        }
    }

    // 二元环
    for(int i = 0; i < robot_num; ++i)
    {
        int x = idx[i][0], y = idx[i][1];
        int tx = f[i].first, ty = f[i].second;
        bool hasC = 0;
        for(int j = 1; j <= stk_idx[x][y]; ++j)
        {
            if(edges[x][y][j][0] == tx && edges[x][y][j][1] == ty)
            {
                hasC = 1;
                break;
            }
        }

        if(hasC)
        {
            if(!checkNoObstacle(x, y) && !checkNoObstacle(tx, ty))
            {
                dfs1(x, y, tx, ty);
                dfs1(tx, ty, x, y);
                if(len[x][y] < len[tx][ty] || (len[x][y] == len[tx][ty] && getRnd()))
                {
                    std::swap(x, tx);
                    std::swap(y, ty);
                }
                int nx = son[tx][ty][0], ny = son[tx][ty][1];
                while(nx != -1){ 
                    int tmp_id = inv_id[getId(tx, ty)];
                    f[tmp_id] = std::make_pair(nx, ny);
                    tx = nx, ty = ny;
                    nx = son[tx][ty][0], ny = son[tx][ty][1];
                }
            }
        }
    }

    setEdges();
    vis.reset();
    in_stk.reset();

    for(int i = 0; i < robot_num; ++i)
    {
        int x = f[i].first, y = f[i].second;
        if(!vis[getId(x, y)] && !in_degree[x][y] && stk_idx[x][y])
        {
            dfs1(x, y);
            while(son[x][y][0] != -1)
            {
                auto &tx = son[x][y][0], &ty = son[x][y][1];
                occupy[getId(x, y)] = 1;
                next_step[inv_id[getId(tx, ty)]] = getNextStep(tx, ty, x, y);
                x = tx, y = ty;
            }
        }
    }
    // 带环

    for(int i = 0; i < robot_num; ++i)
    {
        int x = f[i].first, y = f[i].second;
        if(!vis[getId(x, y)] && dfs2(x, y))
        {
            int tmp_k = 0;
            int nx = x, ny = y;
            do{
                ++tmp_k;
                auto &tx = son[nx][ny][0], &ty = son[nx][ny][1];
                next_step[inv_id[getId(tx, ty)]] = getNextStep(tx, ty, nx, ny);
                nx = tx, ny = ty;
            }while(nx != x || ny != y);
        }
    }

    for(int i = 0; i < robot_num; ++i) std::cout << next_step[i];
}

int main()
{
    std::cin.tie(nullptr);
    rnd = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());
    move();
    return 0;
}