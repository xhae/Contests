#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

double dp[3001][3001];
long long n;
long long a, b;
int type;

void fillDp(void) {
	for(int usedA = min(n, a); usedA >= 0; usedA--) {
		for(int usedB = min(n - usedA, b); usedB >= 0; usedB--) {
			double &ret = dp[usedA][usedB] = 0;
			if(usedA + usedB == n) 	continue;

			long long leftA = a - usedA, leftB = b - usedB;
			if((type == 0 and leftA == 0) or (type == 1 and leftB == 0)) continue;

			double selected = (type == 0 ? 2 : 1) / (double)(leftA * 2 + leftB);
			leftA -= !type;
			leftB -= type;

			if(leftA > 0) ret += leftA * 2 * dp[usedA + 1][usedB];
			if(leftB > 0) ret += leftB * dp[usedA][usedB + 1];
			if(leftA > 0 or leftB > 0) ret = ret / (leftA * 2 + leftB) * (1 - selected);

			ret += selected;
		}
	}
}

int main(void) {
	scanf("%lld %lld %lld", &n, &a, &b);

	type = 0, a++;
	fillDp();
	printf("%.20lf\n", dp[0][0]);

	a--, b++;
	type = 1;
	fillDp();
	printf("%.20lf\n", dp[0][0]);

	return 0;
}
