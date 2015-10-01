#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> dp[2][40000];
vector<int> edges[2][40000];
int n, m;

long long getAns(int type, int u, int p) {
	long long &ret = dp[type][u][p];
	if(ret != -1) return ret;

	ret = 0;
	for(int i = 0; i < edges[type][u].size(); i++) {
		if(i == p) continue;
		int v = edges[type][u][i];
		for(int j = 0; j < edges[type][v].size(); j++)
			if(edges[type][v][j] == u) {
				ret = max(ret, getAns(type, v, j) + 1);
				break;
			}
	}

	return ret;
}

int main(void) {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n - 1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--, v--;
		edges[0][u].push_back(v);
		edges[0][v].push_back(u);
	}
	for(int i = 0; i < m - 1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--, v--;
		edges[1][u].push_back(v);
		edges[1][v].push_back(u);
	}

	for(int i = 0; i < n; i++) dp[0][i] = vector<long long>(edges[0][i].size() + 1, -1);
	for(int i = 0; i < m; i++) dp[1][i] = vector<long long>(edges[1][i].size() + 1, -1);

	vector<long long> farthest;
	long long orig = 0;
	for(int i = 0; i < m; i++) {
		farthest.push_back(getAns(1, i, edges[1][i].size()));
		orig = max(orig, getAns(1, i, edges[1][i].size()));
	}
	sort(farthest.begin(), farthest.end());
	vector<long long> fsums(farthest.size());
	for(int i = 0; i < m; i++) {
		fsums[i] = farthest[i];
		if(i > 0) fsums[i] += fsums[i - 1];
	}
	for(int i = 0; i < n; i++) orig = max(orig, getAns(0, i, edges[0][i].size()));

	long long sum = 0;
	for(int i = 0; i < n; i++) {
		long long curFarthest = getAns(0, i, edges[0][i].size());
		int from = lower_bound(farthest.begin(), farthest.end(), orig - 1 - curFarthest) - farthest.begin();
		sum += from * orig;
		
		long long uppercnt = m - from;
		sum += (curFarthest + 1) * uppercnt;
		sum += fsums[m - 1];
		if(from > 0) sum -= fsums[from - 1];
	}

	long long tot = n * m;
	vector<long long> ans;
	for(int i = 0; i < 4; i++) {
		ans.push_back(sum / tot);
		sum %= tot;
		sum *= 10;
	}

	if(sum / tot >= 5) {
		ans[3]++;
		for(int i = 3; i >= 1; i--) {
			if(ans[i] == 10) {
				ans[i] = 0;
				ans[i - 1]++;
			} else break;
		}
	}

	printf("%lld.", ans[0]);
	for(int i = 1; i <= 3; i++) printf("%lld", ans[i]);

	return 0;
}
