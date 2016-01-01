#include <cstdio>
#include <algorithm>

using namespace std;

double dp[10000001];

int main(void) {
	int e, es, ef;
	scanf("%d %d %d", &e, &es, &ef);
	for(int i = 1; i <= e; i++) {
		double v1 = i >= es ? dp[i - es] : 0;
		double v2 = i >= ef ? dp[i - ef] : 0;
		dp[i] = v1 + v2 + 1;
	}

	printf("%.6lf\n", min(225 / (dp[e] + 1), 200 / dp[e]));
	return 0;
}
