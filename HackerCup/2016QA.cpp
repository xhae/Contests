#include <cstdio>
#include <map>

using namespace std;

map<int, int> cnt[2000];

int main(void) {
	int T;
	scanf("%d", &T);
	for(int kase = 1; kase <= T; kase++) {
		int n, data[2000][2];
		scanf("%d", &n);
		for(int i = 0; i < n; i++) cnt[i].clear();
		for(int i = 0; i < n; i++) scanf("%d %d", data[i], data[i] + 1);
		for(int i = 0; i < n; i++)
			for(int j = i + 1; j < n; j++) {
				int gx = data[i][0] - data[j][0];
				int gy = data[i][1] - data[j][1];
				int dist = gx * gx + gy * gy;
				cnt[i][dist]++;
				cnt[j][dist]++;
			}

		long long ans = 0;
		for(int i = 0; i < n; i++)
			for(auto p: cnt[i])
				ans += p.second * (p.second - 1) / 2;
		printf("Case #%d: %lld\n", kase, ans);
	}

	return 0;
}
