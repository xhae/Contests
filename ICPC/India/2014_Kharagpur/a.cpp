#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

int main(void) {
	int T;
	scanf("%d", &T);
	for(int kase = 1; kase <= T; kase++) {
		int n, data[2][100];
		scanf("%d", &n);
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < n; j++) scanf("%d", data[i] + j);
			sort(data[i], data[i] + n);
		}

		int ans = 0;
		for(int i = 0; i < n; i++) {
			int v = data[0][i] - data[1][i];
			if(v < 0) v *= -1;
			ans += v;
		}
		printf("Case %d: %d\n", kase, ans);
	}

	return 0;
}
