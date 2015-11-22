#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;
int graph[250][250];

int main(void) {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++)
		for(int j = i + 1; j < n; j++)
			graph[i][j] = graph[j][i] = n;

	while(m--) {
		int u, v, b;
		scanf("%d %d %d", &u, &v, &b);
		u--, v--;
		if(b == 1) graph[u][v] = graph[v][u] = 0;
		else graph[u][v] = 0, graph[v][u] = 1;
	}

	for(int k = 0; k < n; k++)
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);

	int k;
	scanf("%d", &k);
	while(k--) {
		int u, v;
		scanf("%d %d", &u, &v);
		printf("%d\n", graph[u - 1][v - 1]);
	}

	return 0;
}
