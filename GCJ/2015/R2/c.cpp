#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <queue>

using namespace std;

int n;
vector<int> sentences[200];
map<string, int> words;

int cap[7000][7000], flow[7000][7000];
int parent[7000];

vector<int> edges[7000];

int getFlow(int n, int s, int e) {
	memset(parent, -1, sizeof(parent));
	queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int cur = q.front();
		q.pop();
		for(int i: edges[cur]) {
			int able = flow[i][cur] > 0 ? flow[i][cur] : cap[cur][i] - flow[cur][i];
			if(parent[i] == -1 and able > 0) {
				parent[i] = cur;
				q.push(i);
			}
		}
	}

	if(parent[e] == -1) return 0;
	int cur = e, f = 999999;
	while(cur != s) {
		int bef = parent[cur];
		int able = flow[cur][bef]  > 0 ? flow[cur][bef] : cap[bef][cur] - flow[bef][cur];
		f = min(f, able);
		cur = bef;
	}

	cur = e;
	while(cur != s) {
		int bef = parent[cur];
		if(flow[cur][bef] > 0) flow[cur][bef] -= f;
		else flow[bef][cur] += f;
		cur = bef;
	}

	return f;
}

int maxFlow(int n, int s, int e) {
	for(int i = 0; i < n; i++) {
		edges[i].clear();
		for(int j =0 ; j < n; j++)
			if(cap[i][j] or cap[j][i]) edges[i].push_back(j);
	}

	int ret = 0, cur;
	while(cur = getFlow(n, s, e), cur > 0)
		ret += cur;
	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for(int kase = 1; kase <= T; kase++) {
		scanf("%d", &n);
		string tmp;
		getline(cin, tmp);

		words.clear();
		for(int i = 0; i < n; i++) {
			getline(cin, tmp);
			stringstream it(tmp);
			string word;
			sentences[i].clear();
			while(it >> word) {
				if(words.count(word) == 0) {
					int wn = words.size();
					words[word] = wn;
				}
				sentences[i].push_back(words[word]);
			}
		}

		memset(cap, 0, sizeof(cap));
		memset(flow, 0, sizeof(flow));

		int wn = words.size();
		for(int i = 0; i < wn; i++) cap[i * 2][i * 2 + 1] = 1;
		for(int i = 0; i < n; i++)
			for(int word: sentences[i]) {
				cap[wn * 2 + i][word * 2] = 999999;
				cap[word * 2 + 1][wn * 2 + i] = 999999;
			}

		printf("Case #%d: %d\n", kase, maxFlow(wn * 2 + n, wn * 2, wn * 2 + 1));
	}

	return 0;
}
