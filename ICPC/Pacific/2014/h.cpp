#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int dp[5001][101];
int n, m, data[10];

int getAns(int left, int step) {
	if(left < 0) return -2;

	int &ret = dp[left][step];
	if(ret != -1) return ret;

	ret = -2;
	if(step == 0) {
		if(left == 0) ret = 0;
	} else {
		for(int i = 0; i < m; i++) {
			int next = getAns(left - data[i] * step, step - 1);
			if(next >= 0) ret = max(ret, next + data[i]);
		}
	}

	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		for(int i = 0; i < m; i++) scanf("%d", data + i);
		memset(dp, -1, sizeof(dp));

		int ans = -1;
		for(int i = 1; i <= 100; i++) ans = max(ans, getAns(n, i));
		printf("%d\n", ans);
	}

	return 0;
}

