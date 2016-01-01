#include <cstdio>
#include <cstring>

int n, m, p[500];
long long dist[500][500], initd[500][500];
int data[500][3];
bool seen[500];
int matched[500];

bool bpm(int u) {
	for(int v = 0; v < m; v++) {		
		int from = data[u][0], to = data[u][1];
		int nfrom = data[v][0];
		if(data[u][2] + initd[from][to] + p[to] + dist[to][nfrom] > data[v][2]) continue;
		if(seen[v]) continue;

		seen[v] = true;
		if(matched[v] == -1 or bpm(matched[v])) {
			matched[v] = u;
			return true;
		}
	}

	return false;
}

int main(void) {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%d", p + i);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			scanf("%lld", dist[i] + j);
			initd[i][j] = dist[i][j];
			dist[i][j] += (i == j ? 0 : p[j]);
		}
	for(int k = 0; k < n; k++)
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if(dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
	for(int i = 0; i < m; i++) {
		scanf("%d %d %d", data[i], data[i] + 1, data[i] + 2);
		data[i][0]--, data[i][1]--;
	}
	
	int cnt = 0;
	memset(matched, -1, sizeof(matched));
	for(int i = 0; i < m; i++) {
		memset(seen, 0, sizeof(seen));
		cnt += bpm(i);
	}

	printf("%d\n", m - cnt);

	return 0;
}
