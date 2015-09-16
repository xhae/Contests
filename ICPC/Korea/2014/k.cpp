#include <cstdio>
#include <algorithm>

using namespace std;

long long dp[2][31][31];
int n;
long long data[10000][2];

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%lld %lld", data[i], data[i] + 1);
		int bef = 1, cur = 0;
		memset(dp[1], 0, sizeof(dp[1]));
		for(int day = n - 1; day >= 0; day--) {
			for(int bus = 0; bus < 30; bus++) {
				for(int tr = 0; tr < 30; tr++) {
					long long &ret = dp[cur][bus][tr];
					long long &natural = dp[bef][max(bus - 1, 0)][max(tr - 1, 0)];

					long long busPay = bus == 0 ? data[day][0] : 0;
					long long trainPay = tr == 0 ? data[day][1] * 2 : 0;

					ret = busPay + trainPay + natural;
					ret = min(ret, 3 + trainPay + natural);
					ret = min(ret, 6 + natural);

					ret = min(ret, 18 + trainPay + dp[bef][max(6, bus - 1)][max(tr - 1, 0)]);
					ret = min(ret, 18 + 6 + dp[bef][max(6, bus - 1)][max(tr - 1, 0)]);
					ret = min(ret, 36 + dp[bef][max(6, bus - 1)][max(6, tr - 1)]);

					ret = min(ret, 45 + trainPay + dp[bef][29][max(tr - 1, 0)]);
					ret = min(ret, 45 + 6 + dp[bef][29][max(tr - 1, 0)]);
					ret = min(ret, 90 + dp[bef][29][29]);
				}
			}
			swap(bef, cur);
		}
		printf("%lld\n", dp[bef][0][0]);
	}


	return 0;
}
