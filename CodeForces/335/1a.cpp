#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> arr;
int n, data[100000];
int dp[100000], _hash[100001];

int main(void) {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", data + i);
		arr.push_back(make_pair(data[i], i));
		_hash[data[i]] = i;
	}

	sort(arr.begin(), arr.end());
	dp[0] = 1;
	int longest = 1;
	for(int i = 1; i < n; i++) {
		int ind = arr[i].second;
		int befInd = _hash[arr[i].first - 1];
		if(ind < befInd) dp[i] = 1;
		else dp[i] = dp[i - 1] + 1;
		longest = max(longest, dp[i]);
	}

	printf("%d\n", n - longest);
	return 0;
}
