#include <vector>
#include <queue>

using namespace std;

class Dinic {
private:
    struct Edge {
        long long c, f;
        int dest;
        Edge *inv;
    };

    vector<vector<Edge>> edge;
    vector<int> level;
    int s, e;
    const long long INF = 1000000000;

    bool leveling() {
        level = vector<int>(edge.size(), -1);
        level[s] = 0;

        queue<int> q;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(auto &e: edge[u])
                if(level[e.dest] == -1 and e.c - e.f > 0) {
                    level[e.dest] = level[u] + 1;
                    q.push(e.dest);
                }
        }
        
        return level[e] != -1;
    }

    long long fillAugpath(int u, long long have) {
        if(u == e) return have;

        for(auto &e: edge[u])
            if(level[e.dest] == level[u] + 1 and e.c - e.f > 0) {
                auto f = fillAugpath(e.dest, min(have, e.c - e.f));
                e.f += f;
                e.inv->f -= f;
                return f;
            }

        return 0ll;
    }

public:
    Dinic(int n, int _s, int _e): s(_s), e(_e) { edge.resize(n); }

    // Should be called once for unordered (u, v) pair. Unify them before you call in case of multiple edges.
    void addEdge(int u, int v, long long c, long long revc = 0) {
        edge[u].push_back({c, 0ll, v, NULL});
        edge[v].push_back({revc, 0ll, u, NULL});
        edge[u].back().inv = &edge[v].back();
        edge[v].back().inv = &edge[u].back();
    }

    long long flow() {
        long long ret = 0, res;
        while(leveling()) while(res = fillAugpath(s, INF), ret += res, res);
        return ret;
    }
};
