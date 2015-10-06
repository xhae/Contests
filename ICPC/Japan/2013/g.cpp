#include <cstdio>
#include <tuple>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int a, b, C = ~(1 << 31), M = (1 << 16) - 1;
tuple<int, int, int> data[300000];
int n, m;

int r() {
	a = 36969 * (a & M) + (a >> 16);
	b = 18000 * (b & M) + (b >> 16);
	return (C & ((a << 16) + b)) % 1000000;
}

const int base = (1 << 20);

int dp[300000];
map<int, int> ansList[300001];

bool isPossible(int ind, int v) {
	if(ansList[v].size() == 0) return false;

	int x, y, z;
	tie(x, y, z) = data[ind];

	auto it = ansList[v].lower_bound(y);
	if(it != ansList[v].begin()) {
		it--;
		return (*it).second < z;
	}

	return false;
}

int main(void) {
	while(scanf("%d %d %d %d", &m, &n, &a, &b), (n + m) > 0) {
		for(int i = 0; i < m; i++) {
			int x, y, z;
			scanf("%d %d %d", &x, &y, &z);
			data[i] = make_tuple(x, y, z);
		}

		for(int i = m; i < n + m; i++) {
			int x = r(), y = r(), z = r();
			data[i] = make_tuple(x, y, z);
		}

		n += m;
		sort(data, data + n);

		int ans = 0;

		for(int i = 0; i <= n; i++) ansList[i].clear();

		for(int i = 0; i < n; ) {
			int s = i, e = i;
			while(e < n and get<0>(data[e]) == get<0>(data[s])) e++;
			i = e;

			for(int j = s; j < e; j++) {
				dp[j] = 1;

				int start = 1, end = n;
				while(start < end) {
					int mid = (start + end) / 2;
					if(isPossible(j, mid)) dp[j] = start = mid + 1;
					else end = mid;
				}

				ans = max(ans, dp[j]);
			}

			for(int j = s; j < e; j++) {
				int x, y, z;
				tie(x, y, z) = data[j];
				auto nv = make_pair(y, z);

				if(ansList[dp[j]].size() > 0) {
					auto it = ansList[dp[j]].lower_bound(y + 1);
					if(it != ansList[dp[j]].begin()) {
						it--;
						if(it->second <= z) continue;
						if(it->first < y) it++;
					}
					while(it != ansList[dp[j]].end() and (*it).second >= z) ansList[dp[j]].erase(it++);
				}
				ansList[dp[j]][y] = z;
			}
		}

		printf("%d\n", ans);
	}

	return 0;
}
