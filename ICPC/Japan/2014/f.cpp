#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<tuple<int, int, int>> edges;
int n, m;

int group[501];
int getGroup(int u) {
	if(group[u] == u) return u;
	return group[u] = getGroup(group[u]);
}

pair<vector<tuple<int, int, int>>, int> krus(int v1, int v2) {
	for(int i = 1; i <= n; i++) group[i] = i;

	pair<vector<tuple<int, int, int>>, int> ret;
	ret.second = 0;

	for(auto &e: edges) {
		int cost, u, v;
		tie(cost, u, v) = e;
		if(u == v1 and v == v2) continue;
		if((u = getGroup(u)) != (v = getGroup(v))) {
			group[v] = u;
			ret.second += cost;
			ret.first.push_back(e);
			if(ret.first.size() == n - 1) break;
		}
	}

	return ret;
}

int main(void) {
	scanf("%d %d", &n, &m);
	while(m--) {
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		edges.push_back(make_tuple(c, u, v));
	}

	sort(edges.begin(), edges.end());

	auto orig = krus(0, 0);
	int ans[2] = {0, 0};

	for(auto e: orig.first) {
		int u, v, cost;
		tie(cost, u, v) = e;
		auto cur = krus(u, v);
		if(cur.first.size() != n - 1 or cur.second != orig.second) {
			ans[0]++;
			ans[1] += cost;
		}
	}

	printf("%d %d\n", ans[0], ans[1]);
	return 0;
}
