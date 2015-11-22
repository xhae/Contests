#include <cstdio>
#include <cstring>

long long dp[21][211];

long long getAns(int k, int n) {
	long long &ret = dp[k][n];
	if(ret != -1) return ret;

	ret = 0;
	if(k == 0) {
		if(n == 0) ret = 1;
	} else {
		for(int i = 0; i <= k; i++) {
			if(i > n) break;
			ret += getAns(k - 1, n - i);
		}
	}

	return ret;
}

int main(void) {
	memset(dp, -1, sizeof(dp));
	int k, n;
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &k, &n);
		printf("%lld\n", getAns(k, n));
	}
	return 0;
}

	
