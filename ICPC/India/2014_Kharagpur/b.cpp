#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;
char str[2][1001];
int dp[1001][1001];

int getAns(int i1, int i2) {
	int &ret = dp[i1][i2];
	if(ret != -1) return ret;

	if(i1 == n and i2 == m) ret = 0;
	else if(i1 == n) ret = m - i2;
	else if(i2 == m) ret = n - i1;
	else {
		ret = 20000;
		if(str[0][i1] == str[1][i2]) ret = 1 + getAns(i1 + 1, i2 + 1);
		ret = min(ret, 1 + getAns(i1 + 1, i2));
		ret = min(ret, 1 + getAns(i1, i2 + 1));
	}

	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for(int kase = 1; kase <= T; kase++) {
		scanf("%d %d %s %s", &n, &m, str[0], str[1]);
		memset(dp, -1, sizeof(dp));
		printf("Case %d: %d\n", kase, getAns(0, 0));
	}

	return 0;
}
