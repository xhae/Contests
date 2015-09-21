#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

long long dp[100][101];
int n;
struct Cand {
	long long takes, dept;
	bool operator < (const Cand &a) const {
		return dept < a.dept;
	}
} cands[100];

long long getAns(int nth, int left) {
	if(nth == -1) {
		if(left == 0) return 0;
		return -2;
	}

	long long &ret = dp[nth][left];
	if(ret != -1) return ret;

	ret = getAns(nth - 1, left);
	if(left > 0) {
		long long nret = getAns(nth - 1, left -1);
		if(nret >= 0 and nret + cands[nth].takes <= cands[nth].dept) {
			if(ret == -2) ret = nret + cands[nth].takes;
			else ret = min(ret, nret + cands[nth].takes);
		}
	}

	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for(int kase = 1; kase <= T; kase++) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%lld", &cands[i].takes);
		for(int i = 0; i < n; i++) {
			scanf("%lld", &cands[i].dept);
			cands[i].dept -= 30;
		}
		sort(cands, cands + n);
		int from = 0;
		while(from < n and cands[from].dept == -31) from++;
		for(int i = from; i < n; i++) cands[i - from] = cands[i];
		n -= from;

		printf("Case %d: ", kase);
		memset(dp, -1, sizeof(dp));
		for(int i = n; i >= 0; i--) if(getAns(n - 1, i) >= 0) { printf("%d\n", n - i); break; }
	}

	return 0;
}
