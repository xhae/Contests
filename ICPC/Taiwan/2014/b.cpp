#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <tuple>

using namespace std;

int n;
int dist[1000][1000];

int parent[1000];
int getGroup(int u) {
	if(u == parent[u]) return u;
	return parent[u] = getGroup(parent[u]);
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		int m;
		scanf("%d %d", &n, &m);
		memset(dist, -1, sizeof(dist));
		for(int i = 0; i < n; i++) dist[i][i] = 0;
		long long sum = 0;
		for(int i = 0; i < m; i++) {
			int u, v, d;
			scanf("%d %d %d", &u, &v, &d);
			if(dist[u][v] == -1 or dist[u][v] > d) dist[u][v] = dist[v][u] = d;
			sum += d;
		}

		for(int i = 0; i < n; i++) parent[i] = i;
		vector<tuple<int, int, int>> edges;
		for(int i = 0; i < n; i++)
			for(int j = i + 1; j < n; j++)
				if(dist[i][j] >= 0) edges.push_back(make_tuple(dist[i][j], i, j));
		sort(edges.begin(), edges.end());

		long long minCost = 0;
		for(auto &e: edges) {
			int c, u, v;
			tie(c, u, v) = e;
			u = getGroup(u), v = getGroup(v);
			if(u == v) continue;
			else {
				minCost += c;
				parent[v] = u;
			}
		}

		printf("%lld\n", sum - minCost);
	}

	return 0;
}




