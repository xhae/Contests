#include <cstdio>
#include <algorithm>

using namespace std;

char field[1500][1501];
int w, h;
int bsum[1500][1500], lsum[1500][1500], rsum[1500][1500];
bool isLeft[1500][1500], isRight[1500][1500];

int mov[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int getSum(int sy, int sx, int ey, int ex, int arr[][1500]) {
	int ret = arr[ey][ex];
	if(sx > 0) ret -= arr[ey][sx - 1];
	if(sy > 0) ret -= arr[sy - 1][ex];
	if(sx > 0 and sy > 0) ret += arr[sy - 1][sx - 1];
	return ret;
}

int main(void) {
	scanf("%d %d", &w, &h);
	for(int i = 0; i < h; i++) {
		scanf("%s", field[i]);
		for(int j = 0; j < w; j++) {
			if(j > 0) bsum[i][j] = bsum[i][j - 1];
			bsum[i][j] += field[i][j] == '#';
		}
		if(i > 0)
			for(int j = 0; j < w; j++) 
				bsum[i][j] += bsum[i - 1][j];
	}

	int y = 0, x = 0, dir = 0;
	while(true) {
		isRight[y][x] = true;
		if(y == h - 1 and x == w - 1) break;
		for(int d = -1; d < 3; d++) {
			int ndir = (dir + d + 4) % 4;
			int ny = y + mov[ndir][0], nx = x + mov[ndir][1];
			if(ny >= 0 and ny < h and nx >= 0 and nx < w and field[ny][nx] == '.') {
				y = ny;
				x = nx;
				dir = ndir;
				break;
			}
		}
	}
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			if(j > 0) rsum[i][j] = rsum[i][j - 1];
			rsum[i][j] += isRight[i][j];
		}
		if(i > 0)
			for(int j = 0; j < w; j++)
				rsum[i][j] += rsum[i - 1][j];
	}

	y = 0, x = 0, dir = 1;
	while(true) {
		isLeft[y][x] = true;
		if(y == h - 1 and x == w - 1) break;
		for(int d = 1; d > -3; d--) {
			int ndir = (dir + d + 4) % 4;
			int ny = y + mov[ndir][0], nx = x + mov[ndir][1];
			if(ny >= 0 and ny < h and nx >= 0 and nx < w and field[ny][nx] == '.') {
				y = ny;
				x = nx;
				dir = ndir;
				break;
			}
		}
	}
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			if(j > 0) lsum[i][j] = lsum[i][j - 1];
			lsum[i][j] += isLeft[i][j];
		}
		if(i > 0)
			for(int j = 0; j < w; j++)
				lsum[i][j] += lsum[i - 1][j];
	}

	const int INF = 99999999;
	int ans = INF, ansy, ansx;
	for(int i = 0; i < h; i++)
		for(int j = 0; j < w; j++) {
			if(field[i][j] == '#') continue;
			if(i == 0 and j == 0) continue;

			int s = 1, e = min(h - i, w - j) + 1;
			int curans = INF;

			while(s < e) {
				int mid = (s + e) / 2;
				if(i + mid >= h and j + mid >= w) e = mid;
				else if(getSum(i, j, i + mid - 1, j + mid - 1, bsum) > 0) e = mid;
				else {
					if(	getSum(i, j, i + mid - 1, j + mid - 1, lsum) > 0 and
						getSum(i, j, i + mid - 1, j + mid - 1, rsum) > 0) {
						if(curans > mid) curans = mid;
						e = mid;
					} else s = mid + 1;
				}
			}

			if(curans < ans) {
				ans = curans;
				ansy = i;
				ansx = j;
			}
		}

	if(ans == INF) printf("Impossible\n");
	else printf("%d %d %d\n", ans, ansx + 1, ansy + 1);

	return 0;
}
