#include <cstdio>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <numeric>

using namespace std;

int dp[500001], data[1000];
unordered_map<int, vector<int>> cands;

int getAns(vector<int> &data) {
	int sum = accumulate(data.begin(), data.end(), 0);
	for(int i = 0; i <= sum; i++) dp[i] = -99999;
	dp[0] = 0;
	for(auto v: data)
		for(int tar = sum / v * v; tar >= v; tar -= v)
			dp[tar] = max(dp[tar], dp[tar - v] + 1);
	int ret = 0;
	for(int tar = 1; tar <= sum; tar *= 2) ret = max(ret, dp[tar]);
	return ret;
}

int main(void) {
	int n;
	while(scanf("%d", &n), n > 0) {
		cands.clear();
		for(int i = 0; i < n; i++) {
			scanf("%d", data + i);
			int v = 1;
			while(data[i] % 2 == 0) {
				data[i] /= 2;
				v *= 2;
			}
			cands[data[i]].push_back(v);
		}

		int ans = 0;
		for(auto &cand: cands) ans = max(ans, getAns(cand.second));

		printf("%d\n", ans);
	}

	return 0;
}
