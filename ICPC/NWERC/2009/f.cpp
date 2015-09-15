#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

int n;
vector<tuple<int, long long>> edges[50000];

int m;
long long toVisit[50000], sum;
long long underCount[50000], dp[50000];

long long dfs(int cur, int from) {
	underCount[cur] = toVisit[cur];

	long long ret = 0;
	for(auto &e: edges[cur]) {
		int next;
		long long cost;
		tie(next, cost) = e;
		if(next == from) continue;

		long long v = dfs(next, cur);
		ret += v + cost * 2 * underCount[next];
		underCount[cur] += underCount[next];
	}

	return ret;
}

void solveDp(int cur, int from) {
	for(auto &e: edges[cur]) {
		int next;
		long long cost;
		tie(next, cost) = e;

		if(next == from) continue;
		dp[next] = dp[cur] + (sum - underCount[next] * 2) * 2 * cost;
		solveDp(next, cur);
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) edges[i].clear();
		fill(toVisit, toVisit + n, 0);

		for(int i = 0; i < n - 1; i++) {
			int u, v;
			long long cost;
			scanf("%d %d %lld", &u, &v, &cost);
			u--, v--;
			edges[u].push_back(make_tuple(v, cost));
			edges[v].push_back(make_tuple(u, cost));
		}
		scanf("%d", &m);
		sum = 0;
		for(int i = 0; i < m; i++) {
			int v;
			long long cost;
			scanf("%d %lld", &v, &cost);
			sum += cost;
			toVisit[v - 1] = cost;
		}

		dp[0] = dfs(0, -1);
		solveDp(0, -1);

		long long ans = dp[0];
		for(int i = 1; i < n; i++) ans = min(ans, dp[i]);
		printf("%lld\n", ans);
		for(int i = 0; i < n; i++) if(ans == dp[i]) printf("%d ", i + 1);
		printf("\n");
	}

	return 0;
}
