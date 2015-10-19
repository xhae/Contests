#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> edges[100000];
int parent[100000];
int dp[100000][30], n;

void dfs(int cur, int p) {
	parent[cur] = p;
	for(auto next: edges[cur]) {
		if(next == p) continue;
		dfs(next, cur);
	}
}

int getAns(int cur, int pc) {
	int &ret = dp[cur][pc];
	if(ret != -1) return ret;

	ret = 99999999;
	for(int i = 0; i < 30; i++) {
		if(i == pc) continue;
		int res = 0;
		for(auto next: edges[cur]) {
			if(next == parent[cur]) continue;
			res += getAns(next, i);
		}
		ret = min(ret, res + i + 1);
	}

	return ret;
}

int main(void) {
	scanf("%d", &n);
	for(int i = 0; i < n - 1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--, v--;
		edges[u].push_back(v);
		edges[v].push_back(u);
	}

	dfs(0, -1);

	memset(dp, -1, sizeof(dp));
    int res = getAns(0, 0);
    for(int i = 1; i < 30; i++) res = min(res, getAns(0, i));
	printf("%d\n", res);
	return 0;
}
