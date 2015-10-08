#include <cstdio>
#include <vector>

using namespace std;

vector<int> edges[100000], leaf;

void dfs(int u, int p) {
	int cnt = 0;
	for(int v: edges[u]) {
		if(v == p) continue;
		cnt++;
		dfs(v, u);
	}

	if(cnt == 0) leaf.push_back(u);
}

int main(void) {
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n - 1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--, v--;
		edges[u].push_back(v);
		edges[v].push_back(u);
	}

	for(int i = 0; i < n; i++)
		if(edges[i].size() > 1) {
			dfs(i, -1);
			break;
		}

	int mid = (leaf.size() + 1) / 2;
	printf("%d\n", mid);
	for(int i = 0; i < leaf.size() / 2; i++) printf("%d %d\n", leaf[i] + 1, leaf[i + mid] + 1);
	if(leaf.size() % 2 == 1) printf("%d %d\n", leaf[0] + 1, leaf[leaf.size() / 2] + 1);
	return 0;
}
