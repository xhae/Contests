#include <cstdio>
#include <algorithm>

using namespace std;

int n, m, c;
int lim[10], botright[10], value[10][10], stat[10], covered[10][10];

int backtr(int nth, int left) {
	if(nth == m) {
		int ret = 0;
		bool isVisited[10][10] = {false, };
		for(int k = 0; k < m; k++) {
			int sy = botright[k] / n - (stat[k] - 1);
			int sx = botright[k] % n - (stat[k] - 1);
			int ey = sy + stat[k] * 2 - 1;
			int ex = sx + stat[k] * 2 - 1;

			sy = max(sy, 0);
			ey = min(n - 1, ey);
			sx = max(sx, 0);
			ex = min(n - 1, ex);
			for(int y = sy; y <= ey; y++)
				for(int x = sx; x <= ex; x++) {
					if(!isVisited[y][x]) {
						isVisited[y][x] = true;
						ret += value[y][x];
					}
				}
		}
		return ret;
	}

	int ret = -(1 << 30);
	for(int i = 0; i <= lim[nth] && i <= left; i++) {
		stat[nth] = i;
		ret = max(ret, backtr(nth + 1, left - i));
	}

	return ret;
}

int main(void) {
	int T;
	scanf("%d", &T);
	for(int kase = 1; kase <= T; kase++) {
		scanf("%d %d %d", &n, &m, &c);
		for(int i = 0; i < m; i++) scanf("%d", lim + i);
		for(int i = 0; i < m; i++) {
			scanf("%d", botright + i);
			botright[i]--;
		}
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				scanf("%d", value[i] + j);

		printf("Case %d: %d\n", kase, backtr(0, c));
	}

	return 0;
}
