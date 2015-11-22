#include <cstdio>

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		long long n;
		scanf("%lld", &n);
		long long ans = 0, s = 0, e = (1 << 30);
		while(s < e) {
			long long mid = (s + e) / 2;
			long long sum = mid * (mid + 1) / 2;
			if(sum <= n) ans = mid, s = mid + 1;
			else e = mid;
		}

		printf("%lld\n", ans);
	}

	return 0;
}
