#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

vector<pair<long long, int>> types[19];

int main(void) {
	long long tar;
	int n;
	scanf("%lld %d", &tar, &n);
	for(int i = 0; i < n; i++) {
		int type;
		long long v;
		scanf("%d %lld", &type, &v);
		for(int j = 0; j < type; j++) v *= 10;
		types[type].push_back(make_pair(v, i));
	}

	for(int i = 0; i <= 18; i++) sort(types[i].rbegin(), types[i].rend());

	vector<int> ans;
	bool isPossible = true;
	long long cur = 0, base = 1, curTar = 0;
	priority_queue<pair<long long, int>> q;

	for(int nth = 0; nth <= 18 and tar > 0; nth++, base *= 10, tar /= 10) {
		for(auto &e: types[nth]) q.push(e);

		curTar += tar % 10 * base;
		if(cur < curTar) {
			while(!q.empty()) {
				cur += q.top().first;
				ans.push_back(q.top().second);
				q.pop();
				if(cur >= curTar) break;
			}

			if(cur < curTar) {
				isPossible = false;
				break;
			}
		}
	}

	if(isPossible) {
		printf("%d\n", (int)ans.size());
		for(int v: ans) printf("%d ", v + 1);
	} else printf("-1\n");

	return 0;
}
