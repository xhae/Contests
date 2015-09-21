#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, r;
long long data[1000][1000];
long long dp[1000][1000];

long long getAns(int i1, int i2) {
	long long &ret = dp[i1][i2];
	if(ret != -1) return ret;

	if(i1 == n + 1 or i2 == n + 1) {
		if(i1 < n + 1) ret = data[i1][n + 1];
		else ret = data[i2][n + 1];
	}
	else {
		ret = (1ll << 60);
		int next = max(i1, i2) + 1;
		ret = min(ret, data[i1][next] + getAns(next, i2));
		ret = min(ret, data[i2][next] + getAns(i1, next));
	}

	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for(int kase = 1; kase <= T; kase++) {
		scanf("%d %d", &n, &r);
		for(int i = 0; i < n + 2; i++) {
			int cur;
			scanf("%d", &cur);
			data[cur][cur] = 0;
			for(int j = 0; j < n + 1; j++) {
				int tar;
				long long cost;
				scanf("%d %lld", &tar, &cost);
				data[cur][tar] = cost;
			}
		}

		memset(dp, -1, sizeof(dp));
		printf("Case %d: %lld\n", kase, getAns(0, 0) + r * (n + 1));
	}

	return 0;
}
