#include <cstdio>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>

using namespace std;

vector<int> edges[50001];
int n;

int level[50001], lvn;
vector<int> bccs[50001];
int bccn;
bool isArtic[50001];

int dfs(int u, int p) {
	level[u] = lvn++;
	int ret = level[u];
	int cnt = 0;
	for(auto v: edges[u]) {
		if(v == p) continue;
		if(level[v] >= 0) ret = min(ret, level[v]);
		else {
			int res = dfs(v, u);
			if(res >= level[u] && p != -1) isArtic[u] = true;
			ret = min(ret, res);
			cnt++;
		}
	}

	if((p == -1 and cnt >= 2)) isArtic[u] = true;
	return ret;
}

void findBcc(int u) {
	bccs[bccn].push_back(u);
	level[u] = bccn;
	if(!isArtic[u])
		for(auto v: edges[u]) {
			if(level[v] == bccn) continue;
			findBcc(v);
		}
}

int main(void) {
	int kase = 0;
	while(scanf("%d", &n), n > 0) {
		for(int i = 0; i < 50001; i++) {
			edges[i].clear();
			bccs[i].clear();
		}
		for(int i = 0; i < n; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			if(u == v) while(true);
			u--, v--;
			if(u >= 50001 or v >= 50001) while(true);
			edges[u].push_back(v);
			edges[v].push_back(u);
		}

		memset(level, -1, sizeof(level));
		lvn = 0;
		bccn = 0;
		memset(isArtic, false, sizeof(isArtic));
		dfs(0, -1);

		memset(level, -1, sizeof(level));
		for(int i = 0; i < 50001; i++) {
			if(edges[i].size() == 0) continue;
			if(level[i] != -1) continue;
			if(isArtic[i]) continue;

			bccs[bccn].clear();
			findBcc(i);
			bccn++;
		}

		long long ans;
		int cnt;
		if(bccn == 1) {
			ans = (long long)bccs[0].size() * (long long)(bccs[0].size() - 1) / 2;
			cnt = 2;
		} else {
			cnt = 0, ans = 1;
			for(int i = 0; i < bccn; i++) {
				int artcnt = 0;
				for(int u: bccs[i]) if(isArtic[u]) artcnt++;
				if(artcnt == 1) {
					cnt++;
					ans *= (bccs[i].size() - 1);
				}
			}
		}


		printf("Case %d: %d %lld\n", ++kase, cnt, ans);
	}

	return 0;
}
