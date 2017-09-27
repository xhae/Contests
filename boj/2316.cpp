#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Dinic {
private:
    struct Edge {
        long long c, f;
        int dest;
        int inv;
    };

    vector<vector<Edge>> edge;
    vector<int> level;
    int src, sink;
    const long long INF = 1000000000;

    bool leveling() {
        fill(level.begin(), level.end(), -1);
        level[src] = 0;

        queue<int> q;
        q.push(src);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(auto &e: edge[u])
                if(level[e.dest] == -1 and e.c - e.f > 0) {
                    level[e.dest] = level[u] + 1;
                    q.push(e.dest);
                }
        }
        
        return level[sink] != -1;
    }

    long long fillAugpath(int u, long long have) {
        if(u == sink) return have;

        for(auto &e: edge[u])
            if(level[e.dest] == level[u] + 1 and e.c - e.f > 0) {
                auto f = fillAugpath(e.dest, min(have, e.c - e.f));
                if(f > 0) {
                    e.f += f;
                    edge[e.dest][e.inv].f -= f;
                    return f;
                }
            }

        return 0ll;
    }

public:
    Dinic(int n, int _s, int _e): src(_s), sink(_e) { edge.resize(n); level.resize(n); }

    // Should be called once for unordered (u, v) pair. Unify them before you call in case of multiple edges.
    void addEdge(int u, int v, long long c, long long revc = 0) {
        edge[u].push_back({c, 0ll, v, (int)edge[v].size()});
        edge[v].push_back({revc, 0ll, u, (int)edge[u].size() - 1});
    }

    long long flow() {
        long long ret = 0, res;
        while(leveling()) while(res = fillAugpath(src, INF), ret += res, res != 0ll);
        return ret;
    }
};

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<pair<int, int>> edges;
    while(m--) {
        int u, v;
        scanf("%d %d", &u, &v);
        if(u == v) continue;
        u--, v--;
        if(u > v) swap(u, v);
        edges.push_back({u, v});
    }

    sort(edges.begin(), edges.end());
    edges.erase(unique(edges.begin(), edges.end()), edges.end());

    Dinic graph(n * 2, 1, 2);
    for(int i = 0; i < n; i++) graph.addEdge(i * 2, i * 2 + 1, 1);
    for(auto &e: edges) {
        graph.addEdge(e.first * 2 + 1, e.second * 2, 1);
        graph.addEdge(e.second * 2 + 1, e.first * 2, 1);
    }
    printf("%lld\n", graph.flow());

    return 0;
}
