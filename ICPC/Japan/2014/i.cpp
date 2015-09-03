#include <cstdio>
#include <cstring>

using namespace std;

long long dp[2][150][151];
int n, nutris[2];
long long nutri[150], deli[150];

const long long INF = (1ll << 60);

int getAns(int type, int nth, int leftDeli) {
	if(nth == n) {
		if(leftDeli == 0) return nutris[type];
		return -INF;
	}

}

int main(void) {
	scanf("%d %d %d", &n, nutris, nutris + 1);
	for(int i = 0; i < n; i++) scanf("%lld %lld", nutri + i, deli + i);

	memset(dp, -1, sizeof(dp));
	int s = 0, e = 151, ans;
	while(s < e) {
		int mid = (s + e) / 2;
		long long anutri = getAns(0, 0, mid);
		if(anutri >= nutris[0]) {
			ans = mid;
			s = mid + 1;
		} else e = mid;
	}

	printf("%d %lld\n", ans, accumulate(deli, deli + n, 0) - ans);

	return 0;
}
