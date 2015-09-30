#include <cstdio>

const long long MOD = 1000000007;

long long fact[51], invfact[51];

long long getPow(long long base, long long exp) {
	long long ret = 1;
	for(int i = 30; i >= 0; i--) {
		ret = ret * ret % MOD;
		if(exp & (1 << i)) ret = ret * base % MOD;
	}

	return ret;
}

int main(void) {
	fact[0] = 1;
	for(int i = 1; i <= 50; i++) {
		fact[i] = fact[i - 1] * i % MOD;
		infvact[i] = getPow(fact[i], MOD - 2);
	}

	return 0;
}
