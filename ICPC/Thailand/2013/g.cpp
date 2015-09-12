#include <cstdio>

int n, start[20], end[20];

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		n = 0;
		int u, v;
		while(scanf("%d %d", &u, &v), v != 0) {
			start[n] = u, end[n] = v;
			n++;
		}

		int ans = 0, cur = 0;
		while(true) {
			int ind = -1, curLast = 11;
			for(int i = 0; i < n; i++) {
				if(start[i] >= cur and end[i] < curLast) {
					ind = i;
					curLast = end[i];
				}
			}

			if(ind == -1) break;
			cur = curLast;
			ans++;
		}

		printf("%d\n", ans);
	}

	return 0;
}
