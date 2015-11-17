#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int w, n;
long long data[50000], sum[50000];

long long getSum(int s, int e) {
	long long ret = sum[e];
	if(s > 0) ret -= sum[s - 1];
	return ret;
}

int dp[50001], dpsum[50001];

int main(void) {
	while(scanf("%d %d", &w, &n), w > 0) {
		for(int i = 0; i < n; i++) scanf("%lld", data + i);
		sum[0] = data[0];
		for(int i = 1; i < n; i++) sum[i] = sum[i - 1] + data[i];

		int s = 1, e = w + 1, ans;
		while(s < e) {
			long long mid = (s + e) / 2;

			dp[n] = dpsum[0] = 0;

			int least, most;
			bool isFirst = true;

			for(int i = n - 1; i >= 0; i--) {
				bool v = false;
				if(getSum(i, n - 1) + (n - 1 - i) <= w) v = true;
				else {
					if(isFirst) {
						isFirst = false;

						int ss = i + 1, ee = n;
						while(ss < ee) {
							int mid2 = (ss + ee) / 2;
							long long curLen = getSum(i, mid2) + (mid2 - i) * mid;
							if(curLen >= w) {
								least = mid2;
								ee = mid2;
							} else ss = mid2 + 1;
						}

						ss = i + 1, ee = n;
						while(ss < ee) {
							int mid2 = (ss + ee) / 2;
							long long curLen = getSum(i, mid2) + mid2 - i;
							if(curLen <= w) {
								most = mid2;
								ss = mid2 + 1;
							} else ee = mid2;
						}
					} else {
						while(getSum(i, most) + most - i > w) most--;
						while(least > i and getSum(i, least) + (least - i) * mid >= w) least--;
						least++;
					}

					if(dpsum[least + 1] != dpsum[most + 2]) v = true;
				}
				
				dp[i] = v;
				dpsum[i] = dpsum[i + 1] + dp[i];
			}

			if(dp[0]) ans = e = mid;
			else s = mid + 1;
		}

		printf("%d\n", ans);
	}

	return 0;
}
