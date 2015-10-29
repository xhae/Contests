#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int w, h, n, m;

int data[2001][2001], sum[2001][2001];

int getSum(int y, int x, int d) {
	int ret = 0;
	if(y <= 2000 and x <= 2000) ret = sum[y][x];
	else if(y <= 2000) ret = sum[y][2000];
	else if(x <= 2000) ret = sum[2000][x];
	else ret = sum[2000][2000];
	if(y - d - 1 >= 0) {
		if(y - d - 1 <= 2000) ret -= sum[y - d - 1][min(x, 2000)];
		else ret -= sum[2000][min(x, 2000)];
	}
	if(x - d - 1 >= 0) {
		if(x - d - 1 <= 2000) ret -= sum[min(y, 2000)][x - d - 1];
		else ret -= sum[min(y, 2000)][2000];
	}
	if(y - d - 1 >= 0 and x - d - 1 >= 0) ret += sum[min(2000, y - d - 1)][min(2000, x - d - 1)];
	return ret;
}

int main(void) {
	int kase = 0;
	int w, h;
	while(scanf("%d %d %d %d", &w, &h, &n, &m), m > 0) {
		printf("Case %d:\n", ++kase);

		memset(data, 0, sizeof(data));

		for(int i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			int cy = y - x + 1000;
			int cx = y + x;
			data[cy][cx] = 1;
		}
		for(int i = 0; i <= 2000; i++) {
			for(int j = 0; j <= 2000; j++) {
				sum[i][j] = data[i][j];
				if(j > 0) sum[i][j] += sum[i][j - 1];
			}
			if(i > 0)
				for(int j = 0; j <= 2000; j++)
					sum[i][j] += sum[i - 1][j];
		}
			

		for(int q = 0; q < m; q++) {
			int dist;
			scanf("%d", &dist);
			dist *= 2;
			int ans = 0, ay, ax;
			for(int i = 0; i <= 2000; i++)
				for(int j = 0; j <= 2000; j++) {
					if((i + j) % 2) continue;
					int cy = (i - 1000 + j) / 2;
					int cx = (j - (i - 1000)) / 2;

					if(cy < 1 or cy > h or cx < 1 or cx > w) continue;

					int cur = getSum(i + dist / 2, j + dist / 2, dist);
					if(cur > ans) {
						ans = cur;
						ay = cy, ax = cx;
					} else if(cur == ans) {
						if(cy < ay or (cy == ay and cx < ax)) {
							ay = cy, ax = cx;
						}
					}
				}
			printf("%d (%d,%d)\n", ans, ax, ay);
		}
	}
	
	return 0;
}
