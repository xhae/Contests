#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int dp[600][600];

struct Alien {
	int start, end, dist;
} aliens[300];
int n;

vector<int> coords;

int getAns(int s, int e) {
	if(s >= e) return 0;
	int &ret = dp[s][e];
	if(ret != -1) return ret;

	int sx = coords[s], ex = coords[e];
	ret = 0;
	int farthest = 0, find = -1;
	for(int i = 0; i < n; i++) {
		if(sx <= aliens[i].start and aliens[i].end <= ex) {
			if(farthest < aliens[i].dist) {
				farthest = aliens[i].dist;
				find = i;
			}
		}
	}

	if(find >= 0) {
		int si = lower_bound(coords.begin(), coords.end(), aliens[find].start) - coords.begin();
		int ei = lower_bound(coords.begin(), coords.end(), aliens[find].end) - coords.begin();
		ret = 1 << 30;
		for(int ind = si; ind <= ei; ind++) ret = min(ret, farthest + getAns(s, ind - 1) + getAns(ind + 1, e)); // why from si + 1 WA?
	}

	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		coords.clear();
		for(int i = 0; i < n; i++) {
			scanf("%d %d %d", &aliens[i].start, &aliens[i].end, &aliens[i].dist);
			coords.push_back(aliens[i].start);
			coords.push_back(aliens[i].end);
		}

		sort(coords.begin(), coords.end());
		coords.erase(unique(coords.begin(), coords.end()), coords.end());

		memset(dp, -1, sizeof(dp));
		printf("%d\n", getAns(0, coords.size() - 1));
	}

	return 0;
}
