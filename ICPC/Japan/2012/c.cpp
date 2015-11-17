#include <cstdio>
#include <cstring>

long long mul[33][50][50];
long long n, m, a, b, c, T;
long long res[50][50];

int main(void) {
	while(scanf("%lld %lld %lld %lld %lld %lld", &n, &m, &a, &b, &c, &T), n > 0) {
		memset(mul[0], 0, sizeof(mul[0]));
		for(int i = 0; i < n; i++)
			for(int j = -1; j <= 1; j++) {
				int cur = i + j;
				if(cur < 0 or cur >= n) continue;
				if(j == -1) mul[0][i][cur] = a;
				else if(j == 0) mul[0][i][cur] = b;
				else mul[0][i][cur] = c;
			}

		int lvlim = 0;
		while((1ll << lvlim) <= T) lvlim++;
		lvlim--;

		for(int lv = 1; lv <= lvlim; lv++) {
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++) {
					mul[lv][i][j] = 0;
					for(int k = 0; k < n; k++)
						mul[lv][i][j] += mul[lv - 1][i][k] * mul[lv - 1][k][j];
					mul[lv][i][j] %= m;
				}
		}

		memset(res, 0, sizeof(res));
		for(int i = 0; i < n; i++) res[i][i] = 1;

		long long ans = 0;
		long long tmp[50][50] = {0, };
		for(int lv = 0; lv <= lvlim; lv++)
			if(T & (1 << lv)) {
				for(int i = 0; i < n; i++)
					for(int j = 0; j < n; j++) {
						tmp[i][j] = 0;
						for(int k = 0; k < n; k++)
							tmp[i][j] += res[i][k] * mul[lv][k][j];
						tmp[i][j] %= m;
					}
				for(int i = 0; i < n; i++)
					for(int j = 0; j < n; j++)
						res[i][j] = tmp[i][j];
			}

		long long inp[50];
		for(int i = 0; i < n; i++) scanf("%lld", inp + i);
		for(int i = 0; i < n; i++) {
			long long cur = 0;
			for(int j = 0; j < n; j++) {
				cur += inp[j] * res[i][j];
				cur %= m;
			}
			printf("%lld ", cur);
		}

		printf("\n");
	}

	return 0;
}
