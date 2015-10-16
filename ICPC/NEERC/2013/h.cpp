#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<int, vector<int>> indexes;
int n, data[100000];
int closestZero[100001][31];
int xorsum[100000];

int main(void) {
	scanf("%d", &n);
	int v = 0;
	for(int i = 0; i < n; i++) {
		scanf("%d", data + i);
		v ^= data[i];
		xorsum[i] = v;
		indexes[v].push_back(i);
	}

	for(int i = 0; i <= 30; i++) closestZero[n][i] = n;
	for(int i = n - 1; i >= 0; i--)
		for(int j = 0; j <= 30; j++) 
			if((data[i] & (1 << j)) == 0) closestZero[i][j] = i;
			else closestZero[i][j] = closestZero[i + 1][j];

	long long ans = 0;
	for(int i = 0; i < n; i++) {
		vector<int> closests{i, n};
		for(int j = 0; j <= 30; j++) closests.push_back(closestZero[i][j]);
		sort(closests.begin(), closests.end());
		closests.erase(unique(closests.begin(), closests.end()), closests.end());

		int v = (1ll << 31) - 1;
		for(int j = 0; j < closests.size() - 1; j++) {
			int s = closests[j], e = closests[j + 1];
			v &= data[s];
			int tar = v;
			if(i > 0) tar ^= xorsum[i - 1];

			if(indexes.count(tar) == 0) continue;

			auto &arr = indexes[tar];
			int sind = lower_bound(arr.begin(), arr.end(), s) - arr.begin();
			int eind = lower_bound(arr.begin(), arr.end(), e) - arr.begin();

			ans += eind - sind;
		}
	}

	printf("%lld\n", ans);

	return 0;
}
