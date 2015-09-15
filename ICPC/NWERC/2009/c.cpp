#include <cstdio>
#include <algorithm>

using namespace std;

long long cnt[1000001];

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		int d, n;
		scanf("%d %d", &d, &n);
		fill(cnt, cnt + d, 0);
		long long sum = 0;
		for(int i = 0; i < n; i++) {
			int v;
			scanf("%d", &v);
			sum += v;
			cnt[sum % d]++;
		}

		long long ans = cnt[0];
		for(int i = 0; i < d; i++) ans += cnt[i] * (cnt[i] - 1) / 2;
		printf("%lld\n", ans);
	}

	return 0;
}
