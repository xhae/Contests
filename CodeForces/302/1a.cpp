#include <cstdio>
#include <algorithm>

using namespace std;

int dp[2][501][501];
int a[500], n, m, b, MOD;

int main(void) {
	scanf("%d %d %d %d", &n, &m, &b, &MOD);
	for(int i = 0; i < n; i++) scanf("%d", a + i);

	for(int i = 0; i <= b; i++) dp[1][0][i] = 1;
	int from = 1, cur = 0;
	for(int lv = n - 1; lv >= 0; lv--) {
		for(int i = 0; i <= m; i++) {
			for(int j = 0; j <= b; j++) {
				dp[cur][i][j] = dp[from][i][j];
				if(i > 0 and j >= a[lv]) dp[cur][i][j] = (dp[cur][i][j] + dp[cur][i - 1][j - a[lv]]) % MOD;
			}
		}

		swap(from, cur);
	}

	printf("%d\n", dp[from][m][b]);
	return 0;
}
