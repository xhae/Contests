#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int dist[2][10000];
vector<pair<int, int>> edge[10000];
int n;

void dijkstra(int s, int ind) {
	memset(dist[ind], -1, sizeof(dist[ind]));
	dist[ind][s] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	q.push(make_pair(0, s));
	while(!q.empty()) {
		int ccost = q.top().first, u = q.top().second;
		q.pop();
		if(dist[ind][u] != ccost) continue;

		for(auto &e: edge[u]) {
			int v = e.second;
			int ncost = ccost + e.first;
			if(dist[ind][v] == -1 or dist[ind][v] > ncost) {
				dist[ind][v] = ncost;
				q.push(make_pair(ncost, v));
			}
		}
	}
}

int main(void) {
	int m;
	scanf("%d %d", &n, &m);
	while(m--) {
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		edge[u].push_back(make_pair(c, v));
		edge[v].push_back(make_pair(c, u));
	}

	dijkstra(0, 0);
	dijkstra(n - 1, 1);
	
	long long ans = 0;
	for(int u = 0; u < n; u++) {
		if(dist[0][u] == -1) continue;
		for(auto &e: edge[u]) {
			int v = e.second, cost = e.first;
			if(dist[1][v] == -1) continue;
			if(dist[0][v] == dist[0][u] + cost and dist[0][n - 1] == dist[0][v] + dist[1][v]) {
				ans += cost;
			}
		}
	}

	ans *= 2;
	printf("%lld\n", ans);

	return 0;
}
