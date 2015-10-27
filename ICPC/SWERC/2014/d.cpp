#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int seen[10000], skase;
int n, m, match[10000];
vector<int> edges[10000];

bool bpm(int u) {
	for(int v: edges[u]) {
		if(seen[v] == skase) continue;
		seen[v] = skase;
		if(match[v] == -1 or bpm(match[v])) {
			match[v] = u;
			return true;
		}
	}

	return false;
}

int main(void) {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		edges[u].push_back(v);
	}

	int cnt = 0;
	memset(match, -1, sizeof(match));
	for(int i = 0; i < n; i++) {
		skase++;
		if(bpm(i)) 
			cnt++;
	}

	if(cnt == n) printf("YES\n");
	else printf("NO\n");

	return 0;
}
