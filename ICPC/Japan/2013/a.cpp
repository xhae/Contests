#include <cstdio>
#include <cstring>

int n, K, s;
int dp[21][21][11][156];

int getAns(int n, int from, int left, int tar) {
	if(left == 0) {
		if(tar == 0) return 1;
		return 0;
	}
	if(tar == 0) return 0;
	if(from > n) return 0;

	int &ret = dp[n][from][left][tar];
	if(ret != -1) return ret;

	ret = getAns(n, from + 1, left, tar);
	if(from <= tar) ret += getAns(n, from + 1, left - 1, tar - from);
	return ret;
}

int main(void) {
	memset(dp, -1, sizeof(dp));
	while(scanf("%d %d %d", &n, &K, &s), n > 0)
		printf("%d\n", getAns(n, 1, K, s));

	return 0;
}
