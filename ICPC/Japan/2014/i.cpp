#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = (1ll << 60);
map<long long, int> dp[150];
int nutris[150], delis[150], deliSum[150];
int n;

int getAns(int nth, long long gap);

int search(int nth, long long gap) {
	int ret = deliSum[n - 1] - deliSum[nth] + delis[nth] - getAns(nth + 1, -(gap + nutris[nth]));
	if(gap > 0) ret = max(ret, getAns(nth + 1, (gap - 1 - nutris[nth])));
	return ret;
}

void buildTable(int nth) {
	for(int deli = 0; deli <= 150; deli++) {
		long long s = 0, e = INF, cand = INF;
		while(s < e) {
			long long mid = (s + e) / 2 - INF / 2;
			int curDeli = search(nth, mid);
			if(curDeli >= deli) cand = e = mid + INF / 2;
			else s = mid + 1 + INF / 2;
		}

		cand -= INF / 2;
		if(cand == INF) continue;
		dp[nth][cand] = deli;
	}
}

int getAns(int nth, long long gap) {
	if(nth == n) return 0;
	if(dp[nth].size() == 0) buildTable(nth);
	auto it = dp[nth].upper_bound(gap);
	if(it == dp[nth].begin()) return 0;
	--it;
	return it->second;
}


int main(void) {
	int a, b;
	cin >> n >> a >> b;
	for(int i = 0; i < n; i++) {
		cin >> nutris[i] >> delis[i];
		deliSum[i] = delis[i];
		if(i > 0) deliSum[i] += deliSum[i - 1];
	}

	int ret = getAns(0, a - b);
	cout << ret << " " << (deliSum[n - 1] - ret) << "\n";
	return 0;
}
