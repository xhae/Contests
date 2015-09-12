#include <cstdio>
#include <algorithm>

using namespace std;

long long n, m;

int main(void) {
	while(scanf("%lld %lld", &n, &m), n > 0) {
		long long ans = 0;
		for(long long i = 1; i <= min(n, m); i += 2)
			ans += i * (n - i + 1) * (m - i + 1);
		printf("%lld\n", ans);
	}
	
	return 0;
}
