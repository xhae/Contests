#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, d;
int data[2000], sum[2000];

int dp[2000][21];

int getAns(int nth, int divider) {
	if(nth == n) return 0;
	int &ret = dp[nth][divider];
	if(ret != -1) return ret;

	ret = (sum[n - 1] - sum[nth] + data[nth] + 5) / 10 * 10;
	if(divider > 0)
		for(int i = nth; i < n; i++)
			ret = min(ret, (sum[i] - sum[nth] + data[nth] + 5) / 10 * 10 + getAns(i + 1, divider - 1));
	return ret;
}

int main(void) {
	scanf("%d %d", &n, &d);
	for(int i = 0; i < n; i++) {
		scanf("%d", data + i);
		sum[i] = data[i];
		if(i > 0) sum[i] += sum[i - 1];
	}

	memset(dp, -1, sizeof(dp));
	printf("%d\n", getAns(0, d));
	return 0;
}
