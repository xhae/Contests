#include <string>
#include <iostream>

using namespace std;

int n, m, nn, mm;
string pat[2000], src[2000];

const long long MOD = 1000000007;
long long onedhash[2000][2000];

int main(void) {
	ios::sync_with_stdio(false);
	cin >> n >> m >> nn >> mm;
	for(int i = 0; i < n; i++) cin >> pat[i];
	for(int i = 0; i < nn; i++) cin >> src[i];

	long long ipat = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++) {
			ipat = ipat * 2;
			if(pat[i][j] == 'o') ipat++;
			ipat %= MOD;
		}

	long long onedbase = 1;
	for(int i = 0; i < m; i++) onedbase = onedbase * 2 % MOD;
	long long twodbase = 1;
	for(int i = 0; i < n; i++) twodbase = twodbase * onedbase % MOD;

	for(int i = 0; i < nn; i++) {
		long long cur = 0;
		for(int j = 0; j < m; j++) {
			cur *= 2;
			if(src[i][j] == 'o') cur++;
			cur %= MOD;
		}
		onedhash[i][0] = cur;
		for(int j = m; j < mm; j++) {
			long long v = onedhash[i][j - m] * 2;
			if(src[i][j] == 'o') v++;
			if(src[i][j - m] == 'o') v -= onedbase;
			onedhash[i][j - m + 1] = (v + MOD) % MOD;
		}
	}

	int ans = 0;
	for(int x = 0; x < mm - m + 1; x++) {
		long long cur = 0;
		for(int i = 0; i < n; i++) cur = (cur * onedbase + onedhash[i][x]) % MOD;
		if(cur == ipat) ans++;
		for(int y = n; y < nn; y++) {
			long long v = (cur * onedbase + onedhash[y][x]) % MOD;
			v = (v - onedhash[y - n][x] * twodbase % MOD + MOD) % MOD;
			cur = v;
			if(cur == ipat) ans++;
		}
	}

	printf("%d\n", ans);

	return 0;
}
