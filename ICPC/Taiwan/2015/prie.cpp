#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

int type[1000];
int n, m;
vector<int> edges[1000];

vector<pair<int, int>> data;
int dp[1000][1001];

int _abs(int arg) {
	if(arg < 0) return arg * -1;
	return arg;
}

int getAns(int ind, int gap) {
	if(ind == data.size()) return gap;
	int &ret = dp[ind][gap];
	if(ret != -1) return ret;

	int curGap = data[ind].first - data[ind].second;
	return ret = min(getAns(ind + 1, _abs(gap + curGap)), getAns(ind + 1, _abs(gap - curGap)));
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++) edges[i].clear();
		for(int i = 0; i < m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			u--, v--;
			edges[u].push_back(v);
			edges[v].push_back(u);
		}

		memset(type, -1, sizeof(type));
		bool isAble = true;
		data.clear();

		for(int i = 0; i < n; i++) {
			if(type[i] >= 0) continue;
			queue<int> q;
			q.push(i);
			type[i] = 0;
			int cnt[2] = {0, 0};
			while(!q.empty()) {
				int cur = q.front();
				q.pop();
				cnt[type[cur]]++;
				for(int next: edges[cur]) {
					if(type[next] == -1) {
						type[next] = !type[cur];
						q.push(next);
					} else if(type[next] == type[cur]) {
						isAble = false;
						break;
					}
				}
			}
			if(!isAble) break;
			data.push_back(make_pair(cnt[0], cnt[1]));
		}

		if(!isAble) {
			printf("-1\n");
			continue;
		}
		
		memset(dp, -1, sizeof(dp));
		int gap = getAns(0, 0);
		printf("%d\n", (n - gap) / 2 + gap);
	}

	return 0;
}
