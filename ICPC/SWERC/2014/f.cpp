#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <tuple>
#include <cstring>

using namespace std;

int data[50000][4];
int n;

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

vector<int> edges[50000];
bool isVisited[50000];

int main(void) {
	vector<int> xs, ys;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < 4; j++)
			scanf("%d", data[i] + j);
		xs.push_back(data[i][0]);
		xs.push_back(data[i][0] + data[i][2]);
		ys.push_back(data[i][1]);
		ys.push_back(data[i][1] + data[i][3]);
	}

	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());

	map<tuple<int, int, int>, bool> cands;
	for(int x: xs) {
		cands.clear();
		for(int i = 0; i < n; i++)
			if(data[i][0] == x or data[i][0] + data[i][2] == x)
				cands[make_tuple(data[i][1], data[i][1] + data[i][3], i)] = false;
		while(!q.empty()) q.pop();
		for(auto &cand: cands) {
			int s, e, nth;
			tie(s, e, nth) = cand.first;
			while(!q.empty() and q.top().first < s) q.pop();
			if(!q.empty()) {
				edges[q.top().second].push_back(nth);
				edges[nth].push_back(q.top().second);
			}
			q.push(make_pair(e, nth));
		}
	}
	for(int y: ys) {
		cands.clear();
		for(int i = 0; i < n; i++)
			if(data[i][1] == y or data[i][1] + data[i][3] == y)
				cands[make_tuple(data[i][0], data[i][0] + data[i][2], i)] = false;;
		while(!q.empty()) q.pop();
		for(auto &cand: cands) {
			int s, e, nth;
			tie(s, e, nth) = cand.first;
			while(!q.empty() and q.top().first < s) q.pop();
			if(!q.empty()) {
				edges[q.top().second].push_back(nth);
				edges[nth].push_back(q.top().second);
			}
			q.push(make_pair(e, nth));
		}
	}
	
	int ans = 0;
	queue<int> q;
	for(int i = 0; i < n; i++) {
		if(isVisited[i]) continue;
		int curAns = 0;
		q.push(i);
		isVisited[i] = true;
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			curAns += data[u][2] * data[u][3];
			for(int v: edges[u]) {
				if(isVisited[v]) continue;
				isVisited[v] = true;
				q.push(v);
			}
		}

		ans = max(ans, curAns);
	}

	printf("%d\n", ans);

	return 0;
}
