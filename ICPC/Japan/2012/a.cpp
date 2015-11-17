#include <cstdio>

using namespace std;

int abs(int tar) {
	if(tar < 0) tar *= -1;
	return tar;
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		int p, q;
		scanf("%d %d", &p, &q);
		p = abs(p);
		q = abs(q);
		bool isPrime = true;
		int lim = p > q ? p : q;
		for(int m = -lim; m <= lim and isPrime; m++)
			for(int n = -lim; n <= lim; n++) {
				int cur = m * m + n * n;
				if(cur <= 1) continue;
				if(m == p and n == q) continue;
				if(m == -q and n == p) continue;
				if(m == -p and n == -q) continue;
				if(m == q and n == -p) continue;

				if((m * p + n * q) % cur == 0 and (m * q - n * p) % cur == 0) {
					isPrime = false;
					break;
				}
			}
		if(isPrime) printf("P\n");
		else printf("C\n");
	}

	return 0;
}
