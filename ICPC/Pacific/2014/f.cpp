#include <cstdio>
#include <cstring>

long long dp[5][31][1 << 8][1 << 8];
const long long MOD = 1000000009;

int mov[4][2] = {{-2, 1}, {2, 1}, {-1, 2}, {1, 2}};
bool isValid[5][1 << 8];

int main(void) {
	for(int m = 1; m <= 4; m++) {
		for(int bef = 0; bef < (1 << (m * 2)); bef++) {
			int stat[2] = {bef & ((1 << m) - 1), bef >> m};
			for(int j = 0; j < (1 << (2 * m)); j++) isValid[m][j] = true;
			for(int j = 0; j < m; j++)
				if(stat[0] & (1 << j)) {
					if(j - 2 >= 0 and (stat[1] & (1 << (j - 2)))) isValid[m][bef] = false;
					if(j + 2 < m and (stat[1] & (1 << (j + 2)))) isValid[m][bef] = false;
				}
		}

		for(int bef = 0; bef < (1 << (m * 2)); bef++) {
			if(!isValid[m][bef]) continue;

			int stat[2] = {bef & ((1 << m) - 1), bef >> m};

			int invalids = 0;
			for(int j = 0; j < m; j++) {
				if(stat[0] & (1 << j)) {
					if(j - 1 >= 0) invalids |= (1 << (j - 1));
					if(j + 1 < m) invalids |= (1 << (j + 1));
				}
				if(stat[1] & (1 << j)) {
					if(j - 2 >= 0) invalids |= (1 << (j - 2));
					if(j + 2 < m) invalids |= (1 << (j + 2));
				}
			}

			for(int aft = 0; aft < (1 << (m * 2)); aft++) {
				if(!isValid[m][aft]) continue;

				int nstat[2] = {aft & ((1 << m) - 1), aft >> m};
				if(stat[1] != nstat[0]) continue;
				if(nstat[1] & invalids) continue;
				dp[m][0][bef][aft] = 1;
			}
		}

		for(int nth = 1; nth <= 30; nth++) {
			for(int bef = 0; bef < (1 << (m * 2)); bef++) {
				if(!isValid[m][bef]) continue;
				for(int aft = 0; aft < (1 << (m * 2)); aft++) {
					if(!isValid[m][aft]) continue;
					for(int mid = 0; mid < (1 << (m * 2)); mid++) {
						if(!isValid[m][mid]) continue;
						
						dp[m][nth][bef][aft] += (dp[m][nth - 1][bef][mid] * dp[m][nth - 1][mid][aft]);
						dp[m][nth][bef][aft] %= MOD;
					}
				}
			}
		}
	}

	int T;
	scanf("%d", &T);
	while(T--) {
		int n, m;
		scanf("%d %d", &m, &n);
		long long cur[1 << 8] = {0, }, next[1 << 8];
		cur[0] = 1;
		for(int i = 0; i < 31; i++) 
			if(n & (1 << i)) {
				memset(next, 0, sizeof(next));
				for(int from = 0; from < (1 << (m * 2)); from++) {
					if(!isValid[m][from]) continue;
					for(int to = 0; to < (1 << (m * 2)); to++) {
						if(!isValid[m][to]) continue;
						next[to] = (next[to] + cur[from] * dp[m][i][from][to]) % MOD;
					}
				}
				for(int i = 0; i < (1 << (m * 2)); i++) cur[i] = next[i];
			}

		long long sum = 0;
		for(int i = 0; i < (1 << (2 * m)); i++) sum = (sum + cur[i]) % MOD;
		printf("%lld\n", sum);
	}

	return 0;
}
